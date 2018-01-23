#pragma once
#ifndef MAIN_H
#define MAIN_H
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <vector>
using namespace std;

enum Direction { RIGHT, LEFT, UP, DOWN };
/*"Point" containing a single vertex information*/
struct Point
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};
/*"CustomRectangle" contain rectangle's 4 vertices and its properties*/
struct CustomRectangle
{
	vector<Point> points;
	Direction direction;
	float speed;
};
/*"gameProperties" contains all the required features*/
struct GameProperties {
	vector<CustomRectangle> rectangles;
	LPDIRECT3DDEVICE9 d3ddev;
};
class RectangleCreation
{
public:
	RectangleCreation();
	vector<CustomRectangle> createRectangle();

	~RectangleCreation();
private:
	int width = 800; //width of screen
	int height = 600; //height of screen
	float numberOfRectanglesToGenerate(); // rectangle generated b/w 3 and 9 
	float startingPointX(); //get the random X value
	float startingPointY(); //get the random Y value
	float getRandomRectangleWidth(); //get the random width between 16 and 48
	float getRandomRectangleHeight(); //get the random height b/w 24 and 64
	int getRandomColor(); //generate random color
	Direction getRandomDirection(); //generate random direction
	float getRandomSpeed(); //generate random speed
	const int rectangleAlpha = 65; // 25% of 255
};
#endif

