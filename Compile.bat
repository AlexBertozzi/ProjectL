g++ -Wall main.cpp game.cpp Tools/*.cpp entities/*.cpp -I./ -ITools/headers -ISDL/include/SDL2 -Ientities/headers -LSDL/lib -lmingw32 -lSDL2main -lSDL2 -mwindows -mconsole -o ProjectL.exe

ProjectL.exe