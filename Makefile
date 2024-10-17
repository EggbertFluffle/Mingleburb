BINARY = main

GLAD_VERSION = 46

SOURCES = ./src/glad$(GLAD_VERSION).cpp ./src/App.cpp ./src/GameManager.cpp ./src/GraphicsManager.cpp ./src/InputManager.cpp ./src/main.cpp ./src/Player.cpp ./src/Shader.cpp ./src/Chunk.cpp ./src/perlin.cpp ./src/stb_image.cpp

IMGUI_DIR = ./imgui
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp $(IMGUI_DIR)/misc/cpp/imgui_stdlib.cpp

OBJECTS = $(addprefix ./obj/, $(addsuffix .o, $(basename $(notdir $(SOURCES)))))

CPPC=g++
CPPFLAGS=-g -std=c++20
WARNINGS = -Wall

LINKS = `pkg-config --libs --cflags glfw3`

all: $(BINARY)

# Real man's rules
$(BINARY): $(OBJECTS)
	$(CPPC) $(LINKS) $(CPPFLAGS) $(WARNINGS) -o $@ $^

./obj/%.o: ./src/%.cpp
	$(CPPC) $(CPPFLAGS) $(WARNINGS) -c -o $@ $^ 

# All ImGui spesific rules
./obj/%.o: $(IMGUI_DIR)/%.cpp
	$(CPPC) $(CPPFLAGS) $(WARNINGS) -c -o $@ $^

./obj/%.o: $(IMGUI_DIR)/backends/%.cpp
	$(CPPC)  $(CPPFLAGS) $(WARNINGS) -c -o $@ $^

./obj/%.o: $(IMGUI_DIR)/misc/cpp/%.cpp
	$(CPPC)  $(CPPFLAGS) $(WARNINGS) -c -o $@ $^

./obj/glad$(GLAD_VERSION).o: ./src/glad$(GLAD_VERSION).c
	$(CPPC) $(WARNINGS) -c -o $@ $^ $(CPPFLAGS)

clean:
	rm -f $(BINARY) $(OBJECTS)
