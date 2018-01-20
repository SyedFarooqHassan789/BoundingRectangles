
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include "CreatingRectangle.h"
#include <ctime>
#pragma comment (lib, "d3d9.lib")



// function prototypes
d3ddev_vBuffer* initD3D(HWND hWnd, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer);   // sets up and initializes Direct3D
void render_frame(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer, int numberOfRectangle);    // renders a single frame
void cleanD3D(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer);    // closes Direct3D and releases memory

						// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


void cleanD3D(LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer)
{
	v_buffer->Release();    // close and release the vertex buffer
	d3ddev->Release();    // close and release the 3D device
	d3d->Release();    // close and release Direct3D
}
// the entry point for any Windows program
int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{
	srand(time(NULL));
	LPDIRECT3D9 d3d = NULL;    // the pointer to our Direct3D interface
	LPDIRECT3DDEVICE9 d3ddev = NULL;    // the pointer to the device class
	LPDIRECT3DVERTEXBUFFER9 v_buffer = NULL;    // the pointer to the vertex buffer
	// the handle for the window, filled by a function
	HWND hWnd;
	// this struct holds information for the window class
	WNDCLASSEX wc;

	// clear out the window class for use
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	// fill in the struct with the needed information
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = "WindowClass1";

	// register the window class
	RegisterClassEx(&wc);

	//register Over
	// create the window and use the result as the handle
	hWnd = CreateWindowEx(NULL,
		"WindowClass1",    // name of the window class
		"Bounded",   // title of the window
		WS_OVERLAPPEDWINDOW,    // window style
		0,    // x-position of the window
		0,    // y-position of the window
		800,    // width of the window
		600,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

	// display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	d3ddev_vBuffer* d3dv_buffer = initD3D(hWnd, d3d, d3ddev, v_buffer);

	// this struct holds Windows event messages
	MSG msg;

	// wait for the next message in the queue, store the result in 'msg'
	while (TRUE)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
			break;

		render_frame(d3dv_buffer->d3ddev, d3dv_buffer->v_buffer, d3dv_buffer->numberOfRectangles);
	}

	// clean up DirectX and COM
	cleanD3D(d3d, d3dv_buffer->d3ddev, d3dv_buffer->v_buffer);

	// return this part of the WM_QUIT message to Windows
	return msg.wParam;

}
// this is the main message handler for the program
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// sort through and find what code to run for the message given
	switch (message)
	{
		// this message is read when the window is closed
	case WM_DESTROY:
	{
		// close the application entirely
		PostQuitMessage(0);
		return 0;
	} break;
	}

	// Handle any messages the switch statement didn't
	return DefWindowProc(hWnd, message, wParam, lParam);
}

d3ddev_vBuffer* initD3D(HWND hWnd, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer)
{

	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = hWnd;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferWidth = 800;
	d3dpp.BackBufferHeight = 600;

	// create a device class using this information and the info from the d3dpp stuct
	d3d->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&d3ddev);

	CreatingRectangle* creatingRectangle = new CreatingRectangle();
	d3ddev_vBuffer* d3dv_buffer = creatingRectangle->createRectangle(d3ddev, v_buffer);    // call the function to initialize the triangle
	
	

	return d3dv_buffer;
}


//// this is the function used to render a single frame
void render_frame(LPDIRECT3DDEVICE9 d3ddev, LPDIRECT3DVERTEXBUFFER9 v_buffer, int numberOfRectangle)
{
	d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

	d3ddev->BeginScene();

	// select which vertex format we are using
	


	// select the vertex buffer to display
	d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(CUSTOMVERTEX));
	d3ddev->SetFVF(CUSTOMFVF);
	// copy the vertex buffer to the back buffer
	
	//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0 * 4, 2);
	//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 1 * 4, 2);

	for(int i=0; i< numberOfRectangle; i++){
		d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4, 2);
	}

	// copy the vertex buffer to the back buffer
	//d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4, 2);

	d3ddev->EndScene();

	d3ddev->Present(NULL, NULL, NULL, NULL);
}
// this is the function that cleans up Direct3D and COM
