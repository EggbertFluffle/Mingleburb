CPPC = g++
CPPFLAGS = -g -std=c++20
LINKS = -lglfw3 -lpthread
WARNINGS = -Wall
BINARY = main
GLAD_VERSION = 43

OBJECTS = ./obj/glad$(GLAD_VERSION).o ./obj/App.o ./obj/GameManager.o ./obj/GraphicsManager.o ./obj/InputManager.o ./obj/main.o ./obj/Player.o ./obj/Shader.o ./obj/stb_image.o

all: $(BINARY)

$(BINARY): $(OBJECTS)
	$(CPPC) $(CPPFLAGS) $(WARNINGS) -o $@ $^ $(LINKS)

./obj/%.o: %.cpp
	$(CPPC) $(CPPGLAGS) $(WARNINGS) -c -o $@ $^

./obj/glad$(GLAD_VERSION).o: glad$(GLAD_VERSION).c
	$(CPPC) $(CPPGLAGS) $(WARNINGS) -c -o $@ $^

clean:
	rm -f $(BINARY) $(OBJECTS)
