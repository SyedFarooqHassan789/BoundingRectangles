#ifndef WINDOWCREATION_H
#define _WINDOWCREATION_H
#pragma once
class WindowCreation
{
public:
	WindowCreation();
	~WindowCreation();

private:
	MSG windowCreation(HINSTANCE hInstance, int nCmdShow);
};

#endif