#include "CreatingRectangle.h"
#include <vector>
using namespace std;


CreatingRectangle::CreatingRectangle()
{
}


CreatingRectangle::~CreatingRectangle()
{
}
vector<CustomRectangle> CreatingRectangle::createRectangle() {
	int numberOfRectangles = numberOfRectanglesToGenerate();
	vector<CustomRectangle> rectangles(numberOfRectangles);

	for (int i = 0; i < numberOfRectangles; i ++) {
		float startingX = startingPointX();
		float startingY = startingPointY();

		float rectangleHeight = getRandomRectangleHeight();
		float rectangleWidth = getRandomRectangleWidth();
		int randomRectColor = getRandomColor();

		CustomRectangle rectangle;
		rectangle.points[0] = { startingX, startingY, 0.0f,0.0f, D3DCOLOR_XRGB(255, 255, 0), };
		rectangle.points[1] = { startingX + rectangleHeight , startingY, 0.0f, 0.0f,D3DCOLOR_XRGB(255, 255, 0), };
		rectangle.points[2] = { startingX, startingY + rectangleWidth, 0.0f, 1.0f,D3DCOLOR_XRGB(255, 255, 0), };
		rectangle.points[3] = { (startingX + rectangleHeight), (startingY + rectangleWidth), 0.0f, 0.0f,D3DCOLOR_XRGB(255, 255, 0), };

		rectangles[i] = rectangle;
	}
	
	return rectangles;
}
float CreatingRectangle::numberOfRectanglesToGenerate() {
	//return (float)(3 + (rand() % 7));
	return 9;
}
float CreatingRectangle::startingPointX() {
	return (float)(rand() % 752);
}
float CreatingRectangle::startingPointY() {
	return (float)(rand() % 540);
}
int CreatingRectangle::getRandomColor() {
	return rand() % 255;
}
float CreatingRectangle::getRandomRectangleWidth() {
	return  (float)(16 + (rand() % 32));
}
float CreatingRectangle::getRandomRectangleHeight() {
	return (float)(24 + (rand() % 36));
}
