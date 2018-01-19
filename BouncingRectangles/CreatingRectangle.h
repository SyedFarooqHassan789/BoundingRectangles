#pragma once
#ifndef MAIN_H
#define MAIN_H
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>

struct CUSTOMVERTEX
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};
struct d3ddev_vBuffer {
	LPDIRECT3DDEVICE9 d3ddev;
	LPDIRECT3DVERTEXBUFFER9 v_buffer;
};
class CreatingRectangle
{
public:
	CreatingRectangle();
	d3ddev_vBuffer* createRectangle(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer);
	~CreatingRectangle();
private:

};
#endif

