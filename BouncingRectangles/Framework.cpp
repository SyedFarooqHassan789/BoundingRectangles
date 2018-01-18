//#include "Framework.h"
//#include "SystemDefs.h"
//
//#include <iostream>
//using namespace std;
//
//LRESULT CALLBACK WindProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
//
//Framework::Framework(void)
//{
//}
//
//
//Framework::~Framework(void)
//{
//	UnregisterClass(applicationName, m_hinstance);
//	m_hinstance = NULL;
//}
//
//bool Framework::Initialize() {
//	if (!createWindow("BoundingRectangles", WINDOW_POSX, WINDOW_POSY, SCREEN_WIDTH, SCREEN_HEIGHT)) {
//		return false;
//	}
//
//	return true;
//
//}
//
//void Framework::Run(){
//	MSG msg;
//	ZeroMemory(&msg, sizeof(MSG));
//
//	while (msg.message != WM_QUIT) {
//
//	}
//}