#pragma once
#ifndef MAIN_H
#define MAIN_H
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
//#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
//#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_DIFFUSE)
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <vector>
using namespace std;

enum Direction { RIGHT, LEFT, UP, DOWN };

struct Point
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};

struct CustomRectangle
{
	Point points[4];
	Direction direction;
};
struct kuta {
	vector<CustomRectangle> rectangles;
	LPDIRECT3DDEVICE9 d3ddev;
};
class CreatingRectangle
{
public:
	CreatingRectangle();
	vector<CustomRectangle> createRectangle();
	Point OurVertices;

	~CreatingRectangle();
private:
	int width = 800;
	int height = 600;
	float numberOfRectanglesToGenerate();
	float startingPointX();
	float startingPointY();
	float getRandomRectangleWidth();
	float getRandomRectangleHeight();
	int getRandomColor();
};
#endif

