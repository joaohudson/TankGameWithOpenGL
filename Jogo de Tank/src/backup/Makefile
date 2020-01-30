#Compilador:
COMPILER = g++
#Linker:
LINKER = g++
#Opções de ligação:
LINKER_OPTIONS = -lSDLmain -lSDL -lGL -lSDL_image -lSDL_mixer
#Nome do jogo:
NAME = ../dist/Game

$(NAME) : main.o Renderer.o Game.o Object.o Audio.o Tank.o Projectile.o Demo.o
	$(LINKER) main.o Renderer.o Game.o Object.o Audio.o Tank.o Projectile.o Demo.o $(LINKER_OPTIONS) -o $(NAME)
main.o : main.cpp ScreenDimension.h Renderer.h Game.h Object.h
	$(COMPILER) -c main.cpp -o main.o
Renderer.o : Renderer.cpp Renderer.h ScreenDimension.h Object.h Game.h
	$(COMPILER) -c Renderer.cpp -o Renderer.o
Game.o : Game.cpp Game.h Renderer.h ScreenDimension.h Object.h EventListener.h Demo.h
	$(COMPILER) -c Game.cpp -o Game.o
Object.o : Object.cpp Object.h
	$(COMPILER) -c Object.cpp -o Object.o
Audio.o : Audio.cpp Audio.h
	$(COMPILER) -c Audio.cpp -o Audio.o
Tank.o : Tank.cpp Tank.h Object.h Game.h Renderer.h
	$(COMPILER) -c Tank.cpp -o Tank.o
Projectile.o : Projectile.cpp Projectile.h Object.h Tank.h Game.h Renderer.h
	$(COMPILER) -c Projectile.cpp -o Projectile.o
Demo.o : Demo.cpp Demo.h Renderer.h ScreenDimension.h Object.h Audio.h EventListener.h
	$(COMPILER) -c Demo.cpp -o Demo.o