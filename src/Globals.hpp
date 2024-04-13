#pragma once

// #define FULLSCREEN

#ifndef FULLSCREEN
const int WIDTH = 800;
const int HEIGHT = 600;
#else
const int WIDTH = 1920;
const int HEIGHT = 1080;
#endif

const int CHUNK_WIDTH = 16;
const int BUILD_HEIGHT = 64;

// #define MOUSE_CONTROLS

#ifndef MOUSE_CONTROLS
const bool MOUSE_CONTROLS = false;
#else
const bool MOUSE_CONTROLS = true;
#endif
