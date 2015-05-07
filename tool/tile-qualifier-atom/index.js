var $ = require('jquery'),
	remote = require('remote');

function htmlSelectOptions(options) {
	var html = '';
	Object.keys(options).forEach(function (key) {
		html += '<option value="'+key+'">'+key+'</option>';
	});

	return html;
}

function htmlSelectCenter() {
	var id = 'tileType';
	var html = '<select id="'+id+'" name="'+id+'">';

	html += '<option value=""></option>';
	html += htmlSelectOptions({
		'VOID': 'VOID',
		'WALL': 'WALL',
		'FLOOR': 'FLOOR',
		'DOOR': 'DOOR'
	});

	return html + '</select>';
}

function htmlSelect(vValue, hValue) {
	var id = 'tileType-'+vValue+hValue;
	var html = '<select id="'+id+'" name="'+id+'" multiple>';

	html += htmlSelectOptions({
		'VOID': 'VOID',
		'WALL': 'WALL',
		'FLOOR': 'FLOOR',
		'DOOR': 'DOOR'
	});
	
	return html + '</select>';
}

function htmlTileDetail() {
	var h = ['left', '', 'right'],
		v = ['top', '', 'bottom'];

	var html = '<table>';

	v.forEach(function (vValue) {
		html += '<tr>';
		h.forEach(function (hValue) {
			if (vValue === hValue) {
				html += '<td>'+htmlSelectCenter()+'</td>';	
			} else {
				html += '<td>'+htmlSelect(vValue, hValue)+'</td>';	
			}
		});
		html += '</tr>';
	});

	html += '</table>';
	html += '<button type="submit">Save</button>';

	return html;
}

function htmlTileQualifier(){
		var html = [
'<canvas id="tileset" width="100" height="100"></canvas>',
'<div id="tileDetail">',
	'<div>',
		'<canvas id="tileThumb" width="100" height="100"></canvas>',
	'</div>',
	'<div id="tileDetailText"></div>',
	'<form id="selects">',
		'<input type="hidden" id="tileX" name="tileX" value="">',
		'<input type="hidden" id="tileY" name="tileY" value="">',
		htmlTileDetail(),
	'</form>',
'</div>',
'<div>',
	'<input type="checkbox" id="show-already-qualified" name="show-already-qualified" /><label>Show already qualified</label>',
'</div>'
	].join('\n');

	return html;
}
  
function fieldsToTile (fields) {

	var tile = {
		'x': null,
		'y': null,
		'type': null,
		'index': null,

		'top': [],
		'topright': [],
		'right': [],
		'bottomright': [],
		'bottom': [],
		'bottomleft': [],
		'left': [],
		'topleft': []
	};

	fields.forEach(function (field) {
		switch (field.name) {
			case 'tileX': tile.x = parseInt(field.value); break;
			case 'tileY': tile.y = parseInt(field.value); break;
			case 'tileType': tile.type = field.value; break;
			default:
				var matches = field.name.match(/^tileType\-([a-z]+)$/i);
				if (matches) {
					tile[matches[1]].push(field.value);
				}
		}
	});

	return tile;
}


function TileQualifier () {
	this.currentPath = null;
	this.currentImage = null;
	this.currentData = null;

	this.tilesetEl = null;
	this.tilesetCtx = null;

	this.thumbEl = null;
	this.thumbCtx = null;

	this.selectedTileX = null;
	this.selectedTileY = null;

	this.showAlreadyQualified = false;
}

TileQualifier.prototype.selectTile = function (tileX, tileY) {
	var keys = ['top', 'topright', 'right', 'bottomright', 'bottom', 'bottomleft', 'left', 'topleft'];

	var tileKey = tileX+','+tileY;

	if (this.currentData.tiles.hasOwnProperty(tileKey)) {
		var tile = this.currentData.tiles[tileKey];

		keys.forEach(function (key) {
			$('#tileType-'+key).val(tile[key]);
		});

		$('#tileType').val(tile.type);
	} else {
		keys.forEach(function (key) {
			$('#tileType-'+key).val(null);
		});
		$('#tileType').val(null);
	}

	this.selectedTileX = tileX;
	this.selectedTileY = tileY;

	this.drawTileset();

	this.thumbEl.width = this.thumbEl.width;

	$('#tileDetailText').text(tileX+'; '+tileY);
	$('#tileX').val(tileX);
	$('#tileY').val(tileY);

	this.thumbCtx.drawImage(this.currentImage, 
		tileX * 32, tileY * 32, 32, 32,
		(100 / 2) - (32 / 2), (100 / 2) - (32 / 2), 32, 32);
};


TileQualifier.prototype.drawTileset = function () {
	var me = this;

	this.tilesetEl.height = this.currentImage.height;
	this.tilesetEl.width = this.currentImage.width;

	this.tilesetCtx.drawImage(this.currentImage, 0, 0, this.tilesetEl.width, this.tilesetEl.height);

	if (this.showAlreadyQualified) {
		this.tilesetCtx.fillStyle = "rgba(0, 255, 0, 0.33)";

		Object.keys(me.currentData.tiles).forEach(function(key) {
			var tile = me.currentData.tiles[key];

			me.tilesetCtx.fillRect(tile.x * 32, tile.y * 32, 32, 32);
		});
	}

	if (this.selectedTileX !== null) {
		this.tilesetCtx.fillStyle = "rgba(255, 0, 255, 0.33)";
		this.tilesetCtx.fillRect(this.selectedTileX * 32, this.selectedTileY * 32, 32, 32);
	}


};

TileQualifier.prototype.loadFile = function (path, next) { // next(error, image, data)
	var me = this;

	var json_path = path+'.tiles.json',
		image_path = path+'.png';

	me.currentPath = path;

	function loadImage(){
		var image = new Image();
		
		image.src = image_path;
		image.onload = function() {
			me.currentImage = image;

			me.drawTileset();

			next(null);
		};
	}

	me.currentData = { tiles: {} };

	remote.require('fs').exists(json_path, function (exists) {
		if (exists) {
			remote.require('fs').readFile(json_path, function(error, data) {
				try {
					me.currentData = JSON.parse(data);
				} catch (exception) {
				}
				if (error){ next(error); return; }
				loadImage();
			});
		} else {
			loadImage();
		}
	});


};

TileQualifier.prototype.saveFile = function (next) { // next(error)
	var json = '';

	try {
		json = JSON.stringify(this.currentData, null, 2);
	} catch (exception) {
		return next(exception);
	}
	
	remote.require('fs').writeFile(this.currentPath+'.tiles.json', json, function(error) {
		if (error) {
			return next(error);
		}
	});
};


TileQualifier.prototype.appendTo = function (selector) {
	var me = this;

	$(selector).append(htmlTileQualifier());

	this.tilesetEl = document.getElementById('tileset');
	this.tilesetCtx = this.tilesetEl.getContext('2d');

	this.thumbEl = document.getElementById('tileThumb');
	this.thumbCtx = this.thumbEl.getContext('2d');

	$('#tileset').on('click', function (e) {
		var tileX = Math.floor(e.originalEvent.layerX / 32),
			tileY = Math.floor(e.originalEvent.layerY / 32);

		me.selectTile(tileX, tileY);
	});

	$('#selects').on('submit', function(e) {
		try{
			var fields = $('#selects').serializeArray();
			var tile = fieldsToTile(fields);

			me.currentData.tiles[tile.x+','+tile.y] = tile;

			me.saveFile(function(error) {
				if (error) {
					console.error(error);
					return;
				}

				me.drawTileset();
			});
		} catch (error) {
			console.error(error);
		}
		e.preventDefault();
	});

	$('#show-already-qualified').on('change', function(e) {
		me.showAlreadyQualified = $(this).is(':checked');
		me.drawTileset();
	});
	
};


var app = new TileQualifier();

app.appendTo('body');

app.loadFile('./tiles', function (error) {
	if (error) {
		console.error(error);
		return;
	}
});
