# MinerCPP

To get main.o run in terminal: g++ -Wall -o main.o main.cpp sha256.cpp -I ./

For Output, eg syntax: Run Command for output eg: ./main.o neeraj http://lochan.website 21e8 1

Output is based on 4 inputs: ./main.o {keyword} {data} {target} {mining mode}



extern "C" {} was added to 'mine'



In Terminal: cd emsdk
source ./emsdk_env.sh (To set the environment)


Emscripten Syntax: emcc ./main.cpp ./sha256.cpp -I . -o mine.js -DENABLE_WASM=true -s NO_EXIT_RUNTIME=1 -s ALLOW_MEMORY_GROWTH=1  -s "EXPORTED_FUNCTIONS=['_mine']"
