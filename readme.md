$> emcc main.c -s USE_SDL=2 -s FULL_ES2=1 -o main.html

$> emcc nanovg.c nanovg/src/nanovg.c nanovg/example/demo.c -s USE_SDL=2 -s FULL_ES2=1 -o nanovg.html -I nanovg/src -I nanovg/example --embed-file nanovg/example 
$> emcc ..\src\nanovg.c ..\lib\nanovg\src\nanovg.c ..\src\nanovg\demo.c -s USE_SDL=2 -s FULL_ES2=1 -o nanovg.html -I ..\lib\nanovg\src --embed-file ..\lib\nanovg\example


$> emcc ..\..\src\main.cpp ..\..\src\entry\emsdl.cpp -s USE_SDL=2 -s FULL_ES2=1 -o main.html --embed-file asset


$> emcc ..\..\src\nanovg.cpp ..\..\src\nanovg\demo.cpp ..\..\src\entry\emsdl.cpp ..\..\src\input\mouse.cpp ..\..\src\asset\asset.cpp ..\..\src\core_sdl.cpp ..\..\lib\nanovg\src\nanovg.c -s USE_SDL=2 -s FULL_ES2=1 -o nanovg.html -I ..\..\lib\nanovg\src -I ..\..\lib\flatbuffers\include


$> "C:\Program Files (x86)\CMake\bin\cmake" .. -G "Visual Studio 12 2013"

$> git clone https://github.com/google/flatbuffers.git


$> node .\tool\asset-packer\pack.js  -i asset -o aaaaaaa -s .\src\asset\assets.fbs


$> git clone https://github.com/google/liquidfun.git