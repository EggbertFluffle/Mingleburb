#pragma once

// #define FULLSCREEN
// #define ENABLE_MOUSE_CONTROLS

#ifndef FULLSCREEN
inline const int WIDTH = 800;
inline const int HEIGHT = 600;
#else
inline const int WIDTH = 1920;
inline const int HEIGHT = 1080;
#endif

// World config
inline const int CHUNK_WIDTH = 16;
inline const int BUILD_HEIGHT = 16;

// Graphics config
inline const int SQUARE_RENDER_DISTANCE = 4; 

#ifndef ENABLE_MOUSE_CONTROLS
inline const bool MOUSE_CONTROLS = false;
#else
inline const bool MOUSE_CONTROLS = true;
#endif

inline const int NOISE_FREQUENCY = 2;
inline const int NOISE_OCTAVES = 2;
