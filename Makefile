#OBJS specifies which files to compile as part of the project
OBJS = src/Pong.cpp src/PongMenu.cpp src/PongGame.cpp src/WinnerScreen.cpp src/Ball.cpp src/Collisions.cpp src/InputHandler.cpp src/Paddle.cpp src/Window.cpp src/Texture.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
# -std=c++11 compiles with C++ 11 standard
COMPILER_FLAGS = -w -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf

#INCLUDE_FLAGS
INCLUDE = include

#OBJ_NAME specifies the name of our executable
OBJ_NAME = Pong

#This is the target that compiles our executable
all: $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -I$(INCLUDE) -o $(OBJ_NAME)
