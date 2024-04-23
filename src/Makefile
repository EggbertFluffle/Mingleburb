CPPC = g++
CPPFLAGS = -g
LINKS = -lglfw3 -lpthread
WARNINGS = -Wall
BINARY = main

OBJECTS = App.o GameManager.o GraphicsManager.o InputManager.o main.o Player.o Shader.o stb_image.o

GLAD_OBJ = glad43.o
GLAD_SRC = glad43.c

all: $(BINARY)

$(BINARY): $(OBJECTS) $(GLAD_OBJ)
	$(CPPC) $(LINKS) $(WARNINGS) -o $@ $^

%.o: %.cpp
	$(CPPC) $(LINKS) $(CPPGLAGS) $(WARNINGS) -c -o $@ $^

$(GLAD_OBJ): $(GLAD_SRC)
	$(CPPC) $(CPPFLAGS) $(WARNINGS) -c -o $@ $^

clean:
	rm -f $(BINARY) $(OBJECTS)
