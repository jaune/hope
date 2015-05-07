#!/usr/bin/env node

var _ = require('lodash'),
	cli_ = require('cli'),
	path_ = require('path'),
	fs_ = require('fs'),
	async_ = require('async'),
	filesize_ = require('file-size'),
	walk_ = require('walk'),
	flatc_ = require('flatc'),
	tmp_ = require('tmp');

	spawn = require('child_process').spawn;

function AssetPackage (fbs_schema_path, input_path, output_path) {
	this.fbs_schema_path = fbs_schema_path;
	this.input_path = input_path;

	this.headers_json_path = output_path+'.headers.json';
	this.headers_bin_path = output_path+'.headers.bin';
	this.content_path = output_path+'.content.bin';
	this.temp_path = output_path+'.tmp';

	this.output_stream = fs_.createWriteStream(this.content_path);
	this.headers = [];
	this.cursor = 0;
}


AssetPackage.prototype.writeFile = function (identifier, path, done) {
	var me = this,
		position = this.cursor,
		data_size = 0,
		input_stream = fs_.createReadStream(path);

	input_stream.on('data', function (data) {
		data_size += data.length;
	});

	input_stream.on('end', function () {


		me.headers.push({
			identifier: identifier,
			position: position,
			size: data_size
		});

		me.cursor += data_size;

		cli_.info('write '+identifier+' '+position+' ('+filesize_(data_size).human()+')');
		done();
	});

	input_stream.pipe(this.output_stream, { end: false });
};


AssetPackage.prototype.end = function (done) {
	var me = this;

	this.output_stream.end(function () {
		fs_.writeFile(me.headers_json_path, JSON.stringify({ assets: me.headers }, null, '  '), function (error) {
			if (error) {
				done(error);
			}

			var s = new flatc_.Schema(me.fbs_schema_path);
			s.encode(me.headers_json_path, me.headers_bin_path, function (error) {
				if (error) {
					done(error);
				}
				done(null, me);
			});
		});
	});
};







var cwebp_path = 'cwebp';

function transform_webp_lossless(input_path, ouput_path, done) {
	var child = spawn(cwebp_path, ['-lossless', input_path, '-o', ouput_path], {
		cwd: path_.dirname(input_path)
	});

	var error = '';

	child.stderr.on('data', function (data) {
		error += data.toString();
	});

	child.on('exit', function (code, signal) {
		if (code === 0) {
			return done(null);
		} else {
			return done(error);
		}
	});
}

transform_webp_lossless.extension = '.webp';
transform_webp_lossless.identifier = 'webp';


function transform_flatc_builder(config, options){
	var fn = function (input_path, ouput_path, done) {

		var fbs_schema_path = options.schema;
		if (!path_.isAbsolute(fbs_schema_path)) {
			fbs_schema_path = path_.join(config['@dirname'], fbs_schema_path);
		}

		var schema = new flatc_.Schema(fbs_schema_path);

		schema.encode(input_path, ouput_path, done);
	};

	fn.extension = '.bin';
	fn.identifier = 'flatc';
	
	return fn;
}


var configs = {};

function findConfig(path) {
	var config_path = path_.join(path_.dirname(path), '.asset');

	if (!configs.hasOwnProperty(config_path)) {
		configs[config_path] = null;
		try {
			if (fs_.existsSync(config_path)) {
				configs[config_path] = JSON.parse(fs_.readFileSync(config_path));
				configs[config_path]['@path'] = config_path;
				configs[config_path]['@dirname'] = path_.dirname(config_path);
			}
		} catch (error) {
			cli_.error(config_path);
			cli_.error(error);
		}
	}

	return configs[config_path];
}


function findTransforms(path) {
	var config = findConfig(path);

	var result  = [];

	if (config) {
		Object.keys(config).forEach(function (pattern) {
			var re = new RegExp(pattern);

			if (re.test(path)) {
				var transform = config[pattern].transform || null;

				if (_.isArray(transform)) {

				} else if (_.isString(transform)) {

					if (transform === 'webp-lossless') {
						result.push(transform_webp_lossless);
					}

				} else if (_.isObject(transform)) {
					if (transform.type === "flatc"){
						result.push(transform_flatc_builder(config, transform));
					}
				} 

//				console.log(transform);

				
			}
		});	
	}
	return result;
}

function applyTransforms(path, transforms, done) {
	var last_path = path;
	var last_cleanupCallback = null;

	async_.eachSeries(transforms, function (transform, next) {

		tmp_.tmpName({ postfix: transform.extension }, function (error, output_path) {
			if (error) {
				return next(error);
			}

			transform(last_path, output_path, function (error) {
				cli_.info('transform '+last_path+' ==> '+output_path);
				if (last_cleanupCallback) {
					// last_cleanupCallback();	
				}
				if (error) {
					// cleanupCallback();
					return next(error);
				} else {
//					last_cleanupCallback = cleanupCallback;
					last_path = output_path;
					return next();
				}
			});
		});

	}, function (error) {
		if (error) {
			return done(error, null);
		}
		done(null, last_path, last_cleanupCallback || function () {});
	});

}


cli_.parse({
	input: ['i', 'Input path', 'path', './'],
	output: ['o', 'Output path', 'path'],
	schema: ['s', 'Flatbuffers schema path', 'path']
});

cli_.main(function (args, options) {
	var input_path = options.input;
	var output_path = options.output;
	var fbs_schema_path = options.schema;

	if (!output_path || !fbs_schema_path) {
		cli_.getUsage();
		cli_.exit(1);
	}

	if (!path_.isAbsolute(input_path)) {
		input_path = path_.join(process.cwd(), input_path);
	}

	if (!path_.isAbsolute(output_path)) {
		output_path = path_.join(process.cwd(), output_path);
	}

	if (!path_.isAbsolute(fbs_schema_path)) {
		fbs_schema_path = path_.join(process.cwd(), fbs_schema_path);
	}

	var assetPackage = new AssetPackage(fbs_schema_path, input_path, output_path);

	var walker = walk_.walk(input_path, {
		followLinks: false
	});
	walker.on("file", function (root, fileStat, next) {
		var filename = fileStat.name,
			
			path = path_.resolve(root, filename);

		if (filename === '.asset') {
			return next();
		}

		var relative_path = path_.relative(input_path, path),
			identifier = relative_path.replace(/\\/g, '/');

		var transforms = findTransforms(path);

		if (transforms.length > 0) {
			identifier += '(' + transforms[transforms.length - 1].identifier +')';
		}

		applyTransforms(path, transforms, function (error, new_path, cleanup) {
			if (error) {
				cli_.error(error);
				return next();
			}

			assetPackage.writeFile(identifier, new_path, function (error) {
				cleanup();
				if (error) {
					cli_.error(error);
					return next();
				}
				next();
			});

		});
	});
	
	walker.on("errors", function (root, nodeStatsArray, next) {
		nodeStatsArray.forEach(function (n) {
			cli_.error(n.name);
			cli_.error(n.error.message || (n.error.code + ": " + n.error.path));
		});
		next();
	});

	walker.on("end", function () {
		assetPackage.end(function (error, me) {
			if (error) {
				cli_.error(error);
				cli_.exit(1);
			}
			cli_.ok('Done !');
			cli_.exit(0);
		});
	});

});