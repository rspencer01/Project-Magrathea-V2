g++ -ggdb main.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o main.o
g++ -ggdb game.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o game.o
g++ -ggdb graphics.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o graphics.o
g++ -ggdb heightmap.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o heightmap.o
g++ -ggdb vector3.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o vector3.o
g++ -ggdb camera.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o camera.o
g++ -ggdb region.cpp -c -I"C:\Program Files\Common Files\MinGW\freeglut\include" -I include -o region.o

g++  -o a.exe main.o graphics.o game.o camera.o heightmap.o vector3.o region.o -L"C:\Program Files\Common Files\MinGW\freeglut\lib" -lfreeglut -lopengl32 -lglu32
