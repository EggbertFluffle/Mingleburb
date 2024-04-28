#pragma once

namespace Perlin {
	struct perlinOffsets {
		int x;
		int y;
		int z;
		int octave;
	};

	struct vec2 {
		float x;
		float y;
	};

	vec2 createVector(float x, float y);
	vec2 normalize(vec2 vec);
	float magnitude(vec2* vec);
	float dot(vec2 v1, vec2 v2);
	float lerp(float a, float b, float i);
	float easeInOutCubic(float x);
	float getGradient(int seed);
	vec2 getGradient(int x, int y, int xSeed, int ySeed);
	perlinOffsets* createPerlinOffsets(int octave);
	float getNoise(perlinOffsets* offsets, float p, int octave);
	float getPerlinNoise(perlinOffsets* offsets, float p);
	float getNoise(perlinOffsets* offsets, float u, float v, int octave);
	float getPerlinNoise(perlinOffsets* offsets, float u, float v);
}
