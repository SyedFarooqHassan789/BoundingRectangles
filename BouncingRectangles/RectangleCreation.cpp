#include "RectangleCreation.h"


RectangleCreation::RectangleCreation()
{
}


RectangleCreation::~RectangleCreation()
{
}
/*generating the vertices and properties of rectangle */
vector<CustomRectangle> RectangleCreation::createRectangle() {
	int numberOfRectangles = numberOfRectanglesToGenerate();

	vector<CustomRectangle> rectangles(numberOfRectangles);

	for (int i = 0; i < numberOfRectangles; i++) {
		float startingX = startingPointX();
		float startingY = startingPointY();

		float rectangleHeight = getRandomRectangleHeight();
		float rectangleWidth = getRandomRectangleWidth();
		int randomRectColor = getRandomColor();

		CustomRectangle rectangle;
		rectangle.points.reserve(4);

		rectangle.points.push_back({ startingX, startingY, 0.0f,0.0f, D3DCOLOR_XRGB(rectangleAlpha,getRandomColor(), getRandomColor(), getRandomColor()) });
		rectangle.points.push_back({ startingX + rectangleHeight , startingY, 0.0f, 0.0f,D3DCOLOR_XRGB(rectangleAlpha,getRandomColor(), getRandomColor(), getRandomColor()) });
		rectangle.points.push_back({ startingX, startingY + rectangleWidth, 0.0f, 1.0f,D3DCOLOR_XRGB(rectangleAlpha,getRandomColor(), getRandomColor(), getRandomColor()) });
		rectangle.points.push_back({ (startingX + rectangleHeight), (startingY + rectangleWidth), 0.0f, 0.0f,D3DCOLOR_XRGB(rectangleAlpha,getRandomColor(), getRandomColor(), getRandomColor()) });


		rectangle.direction = getRandomDirection();
		rectangle.speed = getRandomSpeed();

		rectangles[i] = rectangle;
	}

	return rectangles;
}
/*generate random rectangle b/w 3 and 9*/
float RectangleCreation::numberOfRectanglesToGenerate() {
	return (float)(3 + (rand() % 7));
}
/*generate the random X point inside the window*/
float RectangleCreation::startingPointX() {
	return (float)(rand() % 752);
}
/*generate the random Y point inside the window*/
float RectangleCreation::startingPointY() {
	return (float)(rand() % 540);
}
/*generate the random color of rectangle*/
int RectangleCreation::getRandomColor() {
	return  rand() % 255;
}
/*generate the random width between 16 and 48*/
float RectangleCreation::getRandomRectangleWidth() {
	return  (float)(16 + (rand() % 32));
}
/*generate the random height between 24 and 64*/
float RectangleCreation::getRandomRectangleHeight() {
	return (float)(24 + (rand() % 36));
}
/*get the enum value for random number generation*/
Direction RectangleCreation::getRandomDirection() {
	int random = rand() % 4;
	if (random == 0) {
		return LEFT;
	}
	else if (random == 1) {
		return RIGHT;
	}
	else if (random == 2) {
		return UP;
	}
	else {
		return DOWN;
	}
}
/*get the random speed b/w 10 and 100*/
float RectangleCreation::getRandomSpeed() {
	return (10.0f + (rand() % 90)) / 25.0f;
}