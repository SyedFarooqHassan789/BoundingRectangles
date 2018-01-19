#include "CreatingRectangle.h"



CreatingRectangle::CreatingRectangle()
{
}


CreatingRectangle::~CreatingRectangle()
{
}
d3ddev_vBuffer* CreatingRectangle::createRectangle(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer) {
	CUSTOMVERTEX OurVertices[] =
	{
		{ 0, 20.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 0, 255), },
		{ 100.0f, 20.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0), },
		{ 0.0f, 70.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },
		{ 100.0f, 70.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0), },

	};
	d3ddev->CreateVertexBuffer(4 * sizeof(CUSTOMVERTEX),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	VOID* pVoid;    // the void* we were talking about

	v_buffer->Lock(0, 0, (void**)&pVoid, 0);    // locks v_buffer, the buffer we made earlier
	memcpy(pVoid, OurVertices, sizeof(OurVertices));    // copy vertices to the vertex buffer
	v_buffer->Unlock();    // unlock v_buffer

	d3ddev->SetFVF(CUSTOMFVF);
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));

	d3ddev_vBuffer* d3dv_buffer = new d3ddev_vBuffer();
	d3dv_buffer->d3ddev = d3ddev;
	d3dv_buffer->v_buffer = v_buffer;
	return d3dv_buffer;
}