var fs_ = require('fs');
var mustache_ = require('mustache');
var path_ = require('path');
var snakeCase_ = require('snake-case');
var camelCase_ = require('camel-case');
var walk_ = require('walk');

function render(locals, inPath, outPath){
	var h =  fs_.readFileSync(inPath, {
		encoding : 'utf8'
	});

	h = mustache_.render(h, locals);

	fs_.writeFileSync(outPath, h);
}

var actions = [];
var actionIndex = 1;


var actions_path = 'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action';

var walker = walk_.walk(actions_path);

walker.on('file', function(root, fileStats, next) {
	var cpp_path = path_.join(root, fileStats.name);

	if (cpp_path.match(/\.cpp$/) && !cpp_path.match(/generated\.cpp$/) && !cpp_path.match(/template\.cpp$/)) {

		var path = cpp_path.substr(0, cpp_path.length - 4);
		var h_path = path_.relative(actions_path, path+'.h').split(path_.sep).join('/');
		var relative_path = path_.relative(actions_path, path);
		var parts = relative_path.split(path_.sep);

		actions.push({
			cpp_path: cpp_path,
			h_path: h_path,
			name: parts.join('::'),
			define_name: snakeCase_(parts.join('_')).toUpperCase(),
			define_value: '0x'+actionIndex.toString(16)
		});
		actionIndex++;
	}	
	
	next();
});

walker.on('errors', function (root, nodeStatsArray, next) {
	console.log('error!!!!');
	next();
});

walker.on('end', function () {
	var locals = {
		actions: actions
	};

	render(
		locals,
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\options.template.h',
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\options_generated.h');

	render(
		locals,
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\functions.template.h',
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\functions_generated.h');

	render(
		locals,
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\functions.template.cpp',
		'E:\\Projects\\hope\\samples\\toy\\src\\logic\\action\\functions_generated.cpp');

});
