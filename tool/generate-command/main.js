var fs_ = require('fs');
var mustache_ = require('mustache');
var path_ = require('path');
var snakeCase_ = require('snake-case');

function render(locals, inPath, outPath){
	var h =  fs_.readFileSync(inPath, {
		encoding : 'utf8'
	});

	h = mustache_.render(h, locals);

	fs_.writeFileSync(outPath, h);
}




var commands = [];
var files = fs_.readdirSync('E:\\Projects\\hope\\samples\\toy\\src\\command');

var commandIndex = 1;

files.forEach(function (file) {
	if (!file.match(/^Command\./)) {
		var name = path_.parse(file).name; 
		commands.push({
			name: name,
			define_name: snakeCase_(name).toUpperCase(),
			define_value: '0x'+commandIndex.toString(16)
		});
		commandIndex++;
	}	
});

var locals = {
	commands: commands
};

render(
	locals,
	'E:\\Projects\\hope\\samples\\toy\\src\\command\\Command.template.h',
	'E:\\Projects\\hope\\samples\\toy\\src\\command\\Command.h');

render(
	locals,
	'E:\\Projects\\hope\\samples\\toy\\src\\command\\Command.template.cpp',
	'E:\\Projects\\hope\\samples\\toy\\src\\command\\Command.cpp');