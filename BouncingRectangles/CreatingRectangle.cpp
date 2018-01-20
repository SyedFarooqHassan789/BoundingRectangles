#include "CreatingRectangle.h"



CreatingRectangle::CreatingRectangle()
{
}


CreatingRectangle::~CreatingRectangle()
{
}
d3ddev_vBuffer* CreatingRectangle::createRectangle(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer) {
	int numberOfRectangles = numberOfRectanglesToGenerate();
	//OurVertices = new CUSTOMVERTEX*[numberOfRectangles];

	CUSTOMVERTEX *z = new CUSTOMVERTEX[numberOfRectangles * 4];

	//generate starting vertice 
	/*1 ... 0->752
	2 ... 16-48

	3 ... 0-540
	4 ... 24-60*/




	for (int i = 0; i < numberOfRectangles; i ++) {
		/*float x1 = startingPointX();
		float x2 = endingPointX();

		float y1 = startingPointY();
		float y2 = endingPointY();*/

		float startingX = startingPointX();
		float startingY = startingPointY();

		float rectangleHeight = getRandomRectangleHeight();
		float rectangleWidth = getRandomRectangleWidth();

		z[i*4] = { startingX, startingY, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), };
		z[(i*4) + 1] = { startingX + rectangleHeight , startingY, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), };
		z[(i*4) + 2] = { startingX, startingY + rectangleWidth, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), };
		z[(i*4) + 3] = { (startingX + rectangleHeight), (startingY + rectangleWidth), 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), };
	}

	/*CUSTOMVERTEX OurVertices1[] = {
		{ 0, 0, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), },

	{ 100, 0, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), },

	{ 0, 100, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 0), },


	{ 100, 100, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 0), },
	{ 200, 200, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },

	{ 400, 200, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },

	{ 200, 400, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },


	{ 400, 400, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },



		};*/

	//generate starting vertice 
/*1 ... 0->752
2 ... 16-48

3 ... 0-540
4 ... 24-60*/


//int x1 = startingPointX();
//int x2 = endingPointX();

//int y1 = startingPointY();
//int y2 = endingPointY();


d3ddev->CreateVertexBuffer(numberOfRectangles * 4 * sizeof(CUSTOMVERTEX),
	0,
	CUSTOMFVF,
	D3DPOOL_MANAGED,
	&v_buffer,
	NULL);
VOID* pVoid;    // the void* we were talking about

v_buffer->Lock(0, 0, (void**)&pVoid, 0);    // locks v_buffer, the buffer we made earlier
memcpy(pVoid, z, numberOfRectangles * 4 * sizeof(CUSTOMVERTEX));    // copy vertices to the vertex buffer
v_buffer->Unlock();    // unlock v_buffer

d3ddev->SetFVF(CUSTOMFVF);
d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

d3ddev_vBuffer* d3dv_buffer = new d3ddev_vBuffer();
d3dv_buffer->d3ddev = d3ddev;
d3dv_buffer->v_buffer = v_buffer;
d3dv_buffer->numberOfRectangles = numberOfRectangles;
return d3dv_buffer;
}
int CreatingRectangle::numberOfRectanglesToGenerate() {
	return 3 + (rand() % 7);
}
int CreatingRectangle::startingPointX() {
	return rand() % 752;
}
int CreatingRectangle::startingPointY() {
	return rand() % 540;
}
int CreatingRectangle::getRandomRectangleWidth() {
	return  16 + (rand() % 32);
	
}

int CreatingRectangle::getRandomRectangleHeight() {
	return 24 + (rand() % 36);
}

/*CUSTOMVERTEX OurVertices2[] = {
{ 200, 200, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },

{ 400, 200, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },

{ 200, 400, 0.0f, 1.0f, D3DCOLOR_XRGB(255, 255, 255), },


{ 400, 400, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 255, 255), },

};*/

//OurVertices[0] = OurVertices1;
//OurVertices[1] = OurVertices2;

//for (int i = 0; i < numberOfRectangles; i++) {
//generate starting vertice 
/*1 ... 0->752
2 ... 16-48

3 ... 0-540
4 ... 24-60*/


//int x1 = startingPointX();
//int x2 = endingPointX();

//int y1 = startingPointY();
//int y2 = endingPointY();
//}