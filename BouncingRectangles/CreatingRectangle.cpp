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
		rectangle.points.reserve(4);

		rectangle.points.push_back({ startingX, startingY, 0.0f,0.0f, D3DCOLOR_XRGB(getRandomColor(), getRandomColor(), getRandomColor()) });
		rectangle.points.push_back({ startingX + rectangleHeight , startingY, 0.0f, 0.0f,D3DCOLOR_XRGB(getRandomColor(), getRandomColor(), getRandomColor())});
		rectangle.points.push_back({ startingX, startingY + rectangleWidth, 0.0f, 1.0f,D3DCOLOR_XRGB(getRandomColor(), getRandomColor(), getRandomColor())});
		rectangle.points.push_back({ (startingX + rectangleHeight), (startingY + rectangleWidth), 0.0f, 0.0f,D3DCOLOR_XRGB(getRandomColor(), getRandomColor(), getRandomColor())});

		rectangle.direction = getRandomDirection();
		rectangle.speed = getRandomSpeed();

		rectangles[i] = rectangle;
	}
	
	return rectangles;
}
float CreatingRectangle::numberOfRectanglesToGenerate() {
	return (float)(3 + (rand() % 7));
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
Direction CreatingRectangle::getRandomDirection() {
	int random = rand() % 4;
	if (random == 0) {
		return LEFT;
	} else if (random == 1) {
		return RIGHT;
	} else if (random == 2) {
		return UP;
	} else {
		return DOWN;
	}
}
float CreatingRectangle::getRandomSpeed() {
	return (10.0f + (rand() % 90)) / 50.f;
}