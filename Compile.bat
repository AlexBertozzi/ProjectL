g++ -Wall main.cpp game.cpp Tools/*.cpp entities/*.cpp entities/enemies/*.cpp -I./ -ITools/headers -Ientities/enemies/headers -ISDL/include/SDL2 -Ientities/headers -LSDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -mwindows -mconsole -o ProjectL.exe

ProjectL.exe