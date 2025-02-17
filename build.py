# run with python3 build.py in terminal!
# source/credit to mike shah 
import os
import platform

# common configuration options -- 
COMPILER="g++ -g -std=c++17"
SOURCE="src/*.cpp"     # edit cc or cpp as needed
EXECUTABLE="prog"

# platform specific configuration options --
ARGUMENTS=""
INCLUDE_DIR=""
LIBRARIES=""

if platform.system()=="Linux":
    ARGUMENTS="-D LINUX"
    INCLUDE_DIR="-I ./include/ -I ./../../common/thirdparty/glm/"
    LIBRARIES="-lSDL2 -ldl"
elif platform.system()=="Darwin": # set to work with my local machine and may need to be edited when compiling
    ARGUMENTS="-D MAC"
    INCLUDE_DIR="-I ./include/ -I/opt/homebrew/Cellar/sdl2/2.30.8/include/SDL2 -I./../../common/thirdparty/old/glm"
    LIBRARIES="-L/opt/homebrew/Cellar/sdl2/2.30.8/lib -lSDL2 -ldl"
elif platform.system()=="Windows":
    ARGUMENTS="-D MINGW -static -libgcc -static-libstdc++"
    INCLUDE_DIR="-I./INCLUDE/ -I./../../common/thirdparty/old/glm/"
    EXECUTABLE="prog.exe"
    LIBRARIES="-lmingw32 -lSDL2main -lSDL2 -mwindows"

# build executable with a string!
compileString=COMPILER+" "+ARGUMENTS+" "+SOURCE+" -o "+EXECUTABLE+" " # +INCLUDE_DIR+" "+LIBRARIES

# run command
exit_code = os.system(compileString)
exit(0 if exit_code==0 else 1)



