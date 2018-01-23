#include "RectangleCreation.h"
#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <ctime>
#define SCREEN_WIDTH  800
#define SCREEN_HEIGHT 600
#pragma comment (lib, "d3d9.lib")



// function prototypes
GameProperties* initD3D(HWND hWnd, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev);   // sets up and initializes Direct3D
void render_frame(GameProperties* k);    // renders a single frame
void updateRectangles(GameProperties* gameprop); //updating rectangles
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


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
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW);
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
		SCREEN_WIDTH,    // width of the window
		SCREEN_HEIGHT,    // height of the window
		NULL,    // we have no parent window, NULL
		NULL,    // we aren't using menus, NULL
		hInstance,    // application handle
		NULL);    // used with multiple windows, NULL

				  // display the window on the screen
	ShowWindow(hWnd, nCmdShow);

	// set up and initialize Direct3D
	GameProperties* gameprop;
	gameprop = initD3D(hWnd, d3d, d3ddev);

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

		//update rectangles info and then pass it to render method
		updateRectangles(gameprop);
		//calling render method
		render_frame(gameprop);
	}

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

GameProperties* initD3D(HWND hWnd, LPDIRECT3D9 d3d, LPDIRECT3DDEVICE9 d3ddev)
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

	vector<CustomRectangle> rectangles = RectangleCreation().createRectangle();

	GameProperties* gameprop;
	gameprop = new GameProperties;
	gameprop->d3ddev = d3ddev;
	gameprop->rectangles = rectangles;

	return gameprop;
}


/* this is the function used to render a single frame*/
void render_frame(GameProperties* gameprop)
{
	int numberOfPoints = gameprop->rectangles.size() * 4;
	Point *points = new Point[numberOfPoints];

	for (int i = 0; i < gameprop->rectangles.size(); i++) {
		points[i * 4] = gameprop->rectangles[i].points[0];
		points[(i * 4) + 1] = gameprop->rectangles[i].points[1];
		points[(i * 4) + 2] = gameprop->rectangles[i].points[2];
		points[(i * 4) + 3] = gameprop->rectangles[i].points[3];
	}

	LPDIRECT3DVERTEXBUFFER9 v_buffer;
	gameprop->d3ddev->CreateVertexBuffer(numberOfPoints * sizeof(Point),
		0,
		CUSTOMFVF,
		D3DPOOL_MANAGED,
		&v_buffer,
		NULL);
	VOID* pVoid;

	v_buffer->Lock(0, 0, (void**)&pVoid, 0);    // locks v_buffer, the buffer we made earlier
	memcpy(pVoid, points, numberOfPoints * sizeof(Point));
	v_buffer->Unlock();

	gameprop->d3ddev->Clear(0, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	gameprop->d3ddev->BeginScene();

	// select the vertex buffer to display
	gameprop->d3ddev->SetFVF(CUSTOMFVF);
	gameprop->d3ddev->SetStreamSource(0, v_buffer, 0, sizeof(Point));
	for (int i = 0; i < gameprop->rectangles.size(); i++) {
		// copy the vertex buffer to the back buffer
		gameprop->d3ddev->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	gameprop->d3ddev->EndScene();

	gameprop->d3ddev->Present(NULL, NULL, NULL, NULL);

	v_buffer->Release();    // close and release the vertex buffer
	delete[] points;

}

/*updating the rectangles speed and movement*/
void updateRectangles(GameProperties* gameprop) {
	for (int i = 0; i < gameprop->rectangles.size(); i++) {
		if (gameprop->rectangles[i].direction == LEFT) {
			gameprop->rectangles[i].points[0].x -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[1].x -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[2].x -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[3].x -= gameprop->rectangles[i].speed;

			if (gameprop->rectangles[i].points[0].x <= 0) {
				gameprop->rectangles[i].direction = RIGHT;
			}
		}
		else if (gameprop->rectangles[i].direction == RIGHT) {
			gameprop->rectangles[i].points[0].x += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[1].x += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[2].x += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[3].x += gameprop->rectangles[i].speed;

			if (gameprop->rectangles[i].points[1].x >= 800) {
				gameprop->rectangles[i].direction = LEFT;
			}
		}
		else if (gameprop->rectangles[i].direction == UP) {
			gameprop->rectangles[i].points[0].y += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[1].y += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[2].y += gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[3].y += gameprop->rectangles[i].speed;

			if (gameprop->rectangles[i].points[2].y >= 600) {
				gameprop->rectangles[i].direction = DOWN;
			}
		}
		else {
			gameprop->rectangles[i].points[0].y -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[1].y -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[2].y -= gameprop->rectangles[i].speed;
			gameprop->rectangles[i].points[3].y -= gameprop->rectangles[i].speed;

			if (gameprop->rectangles[i].points[0].y <= 0) {
				gameprop->rectangles[i].direction = UP;
			}
		}
	}

}