#ifndef MAIN_H
#define MAIN_H
#define CUSTOMFVF (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
struct Point
{
	FLOAT x, y, z, rhw;    // from the D3DFVF_XYZRHW flag
	DWORD color;    // from the D3DFVF_DIFFUSE flag
};
class main {
private:
	//LPDIRECT3DDEVICE9 d3ddev;
	//LPDIRECT3DVERTEXBUFFER9 v_buffer;
	//LPDIRECT3D9 d3d;
	//void init_display();
	//void render_frame();
	//void cleanD3D();
	//void initD3D(HWND hWnd);
	//LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	// global declarations
	LPDIRECT3D9 d3d = NULL;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev = NULL;    // the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer

												// function prototypes
	void initD3D(HWND hWnd);    // sets up and initializes Direct3D
	void render_frame(void);    // renders a single frame
	void cleanD3D(void);    // closes Direct3D and releases memory
	void init_display(void);    // 3D declarations

	
};
#endif
