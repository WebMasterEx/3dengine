#pragma once

#include <d3d9.h>
#include <d3dx9.h>

struct VertexColor {
	VertexColor(float x, float y, float z, unsigned long color) : x(x), y(y), z(z), color(color) {
		
	};

	float x,y,z;
	unsigned long color;
};

struct FLOAT3 {
	FLOAT3(float x=0, float y=0, float z=0) : x(x), y(y), z(z) {
		
	}

	float x, y, z;
};

/**
struct COLOR4 {
	COLOR4(float r, float g=0, float b=0, float a=0) :r(r), g(g), b(b), a(a) {
		
	};

	float a,r,g,b;
};*/