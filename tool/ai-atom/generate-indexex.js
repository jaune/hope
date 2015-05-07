var path_ = require('path'),
	tmp_ = require('tmp'),
	fs_ = require('fs');
var Schema = require('flatc').Schema;

var schema = new Schema('E:/Projects/hope/src/asset/assets.fbs');
/*
schema.encode('E:/Projects/hope/samples/toy/build/assets.headers.json', path_.join(__dirname, 'assets.headers.bin'), function (error) {
     if (error) { return console.log(error); }
     console.log('---*---');
});
*/



		


function tilesToIndexesArray(tiles) {
	var indexes4 = [];
	var indexes8 = [];
	
	tiles.forEach(function (tile) {
		var index = tile.x + (tile.y * 16);

		tile.top.forEach(function (topType) {
			tile.right.forEach(function (rightType) {
				tile.bottom.forEach(function (bottomType) {
					tile.left.forEach(function (leftType) {

						if (tile.topright.length > 0 ) {
							tile.topright.forEach(function (toprightType) {
								tile.bottomright.forEach(function (bottomrightType) {
									tile.bottomleft.forEach(function (bottomleftType) {
										tile.topleft.forEach(function (topleftType) {
											indexes8.push({
												index: index,
												center: tile.type,
												
												top: topType,
												right: rightType,
												bottom: bottomType,
												left: leftType,

												topright: toprightType,
												bottomright: bottomrightType,
												bottomleft: bottomleftType,
												topleft: topleftType
											});
										});
									});
								});
							});
						} else {
							indexes4.push({
								index: index,

								center: tile.type,
								
								top: topType,
								right: rightType,
								bottom: bottomType,
								left: leftType
							});
						}
					});
				});
			});
		});

		
	});

	return {
		indexes4: indexes4,
		indexes8: indexes8
	};
}

function tilesToIndexesFile(tiles_path, indexes_path, next) { // next(error)

	fs_.readFile(tiles_path, function (error, data) {
		if (error) { return next(error); }

		var tiles = null;

		try {
			tilesObject = JSON.parse(data).tiles;

			tiles = Object.keys(tilesObject).map(function (key) {
				return tilesObject[key];
			});

		} catch (exception) {
			return next(exception);
		}

		var indexes = tilesToIndexesArray(tiles);

		fs_.writeFile(indexes_path, JSON.stringify(indexes, null, 2), function (error) {
			if (error) { return next(error); }

			next();
		});
		
	});
}

function tilesToIndexesBinary(schema_path, tiles_path, binary_path, next) { // next(error)
	var schema = new Schema(schema_path);



	tmp_.file({ postfix: '.indexes.json'}, function(error, indexes_path, fd, cleanupCallback) {
		if (error) { return next(error); }



		tilesToIndexesFile(tiles_path, indexes_path, function (error) {
			if (error) {
				cleanupCallback();
				return next(error); 
			}

			schema.encode(indexes_path, binary_path, function (error) {
				cleanupCallback();
				if (error) { return next(error); }
				return next();
			});
		});
	});
}

tilesToIndexesFile('tiles.tiles.json', 'tiles.indexes.json', function(error) {
	if (error) { return console.error(error); }
	console.log('----*----');
});


tilesToIndexesBinary('E:/Projects/hope/samples/toy/src/TileIndexes.fbs', 'tiles.tiles.json', 'tiles.indexes.bin', function(error) {
	if (error) { return console.error(error); }
	console.log('----*----');
});
