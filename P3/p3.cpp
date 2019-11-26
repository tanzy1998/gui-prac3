#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <iostream>
#include <conio.h>
#include <string>

#pragma comment (lib, "OpenGL32.lib")

#define WINDOW_TITLE "Practical 3"
float spd = 0, acc = 0, lvl = 0;
float left = 0.0, right = 0.0, up = 0.0, down = 0.0;
int page = 0, noOfFan = 4;
float rotatedegree = 0.0;
void body();
void circle(float x, float y, float radius);
void fansword();
void sun(float x_trans, float y_trans);
void branch();
void drawfan(int noOfFan, float acc);

LRESULT WINAPI WindowProcedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CHAR:
		switch (wParam)
		{
		case 0x77:
			down -= 0.1;
			up += 0.1;
			break;
		case 0x61:
			left -= 0.1;
			right += 0.1;
			break;
		case 0x73:
			down += 0.1;
			up -= 0.1;
			break;
		case 0x64:
			left += 0.1;
			right -= 0.1;
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;

		case VK_LEFT:
			if (spd < 0.5)
			{
				spd -= 0.05f;
			}
			break;

		case VK_RIGHT:
			if (spd > -0.5)
			{
				spd += 0.05f;
			}
			break;

		case VK_SPACE:
			spd = 0.00f;
			down = 0.0;
			up = 0.0;
			left = 0.0;
			right = 0.0;
			glLoadIdentity();
			break;

		case VK_F1:
			page = 1;
			break;

		case VK_F2:
			page = 2;
			break;

		case VK_ADD:
			if (noOfFan < 6) {
				noOfFan += 1;
				break;
			}
		case VK_SUBTRACT:
			if (noOfFan > 4) {
				noOfFan -= 1;
				break;
			}
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}
//--------------------------------------------------------------------

bool initPixelFormat(HDC hdc)
{
	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.cAlphaBits = 8;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 24;
	pfd.cStencilBits = 0;

	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;

	pfd.iLayerType = PFD_MAIN_PLANE;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// choose pixel format returns the number most similar pixel format available
	int n = ChoosePixelFormat(hdc, &pfd);

	// set pixel format returns whether it sucessfully set the pixel format
	if (SetPixelFormat(hdc, n, &pfd))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void demo() {
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.5, 0.0, 0.0);
	glScalef(0.5, 0.5, 0.0);
	glBegin(GL_TRIANGLES);
	glVertex2f(-0.5, 0.0);
	glVertex2f(0.0, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
	glPopMatrix();

	glTranslatef(-0.5, 0.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2f(-0.5, 0.0);
	glVertex2f(-0.5, 0.5);
	glVertex2f(0.5, 0.5);
	glVertex2f(0.5, 0.0);
	glEnd();
}

void redRectangle() {
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1, 0, 0);
	glLoadIdentity();

	glPushMatrix();
	glTranslatef(left, up, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.2, 0.15);
	glVertex2f(-0.2, -0.15);
	glVertex2f(0.2, -0.15);
	glVertex2f(0.2, 0.15);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(right, down, 0);
	glBegin(GL_QUADS);
	glVertex2f(-0.2, 0.15);
	glVertex2f(-0.2, -0.15);
	glVertex2f(0.2, -0.15);
	glVertex2f(0.2, 0.15);
	glEnd();
	glPopMatrix();
}

void body() {

	glColor3ub(102, 51, 0);

	glBegin(GL_QUADS);
	glVertex2f(0.05, -0.05);
	glVertex2f(0.3, -1.0);
	glVertex2f(-0.3, -1.0);
	glVertex2f(-0.05, -0.05);
	glEnd();
}

void circle(float x, float y, float radius) {

	float x1 = x, y1 = y;
	float angle = 0.0;

	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(102, 51, 0);
	glVertex2f(x1, y1);

	for (angle = 0; angle <= 360.0; angle += 0.2) {
		x1 = x + cos(angle) * radius;
		y1 = y + sin(angle) * radius;
		glVertex2f(x1, y1);
	}
	glEnd();

}


void branch() {
	glColor3ub(255, 153, 51);

	glBegin(GL_QUADS);
	glVertex2f(0.0, 0.03);
	glVertex2f(0.1, 0.03);
	glVertex2f(0.1, 0.01);
	glVertex2f(0.0, 0.01);

	glEnd();
}

void fansword() {

	glColor3ub(255, 153, 51);

	glBegin(GL_QUADS);
	glVertex2f(0.1, 0.03);
	glVertex2f(0.6, 0.03);
	glVertex2f(0.6, -0.07);
	glVertex2f(0.1, -0.07);

	glEnd();
}

void sun(float x_trans, float y_trans) {

	float x1 = 0.0, y1 = 0.0, x2 = 0.0, y2 = 0.0;
	float angle = 0.0;
	float radius = 0.2;
	glColor3ub(255, 128, 0);
	glTranslatef(x_trans, y_trans, 0);
	glBegin(GL_TRIANGLE_FAN);


	for (angle = 0; angle <= 360.0; angle += 0.2) {
		x2 = x1 + cos(angle) * radius;
		y2 = y1 + sin(angle) * radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawfan(int noOfFan, float spd) {
	float degree = 360 / noOfFan;
	for (int i = 0; i < noOfFan; i++) {

		glPushMatrix();
		glRotatef(rotatedegree, 0, 0, 1);
		branch();
		glPopMatrix();

		glPushMatrix();
		glRotatef(rotatedegree, 0, 0, 1);
		fansword();
		glPopMatrix();

		rotatedegree = fmod((rotatedegree - degree - spd),360.0f);
	}
}

void bird(float x_trans, float y_trans) {
	float x, y;
	glColor3f(1, 1, 1);
	glTranslatef(x_trans, y_trans, 0);
	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glPointSize(1.0);
	for (int i = 240; i < 300; i++)
	{
		glBegin(GL_POINTS);
		x = cos((2 * i * 3.14) / 360) * .2;
		y = sin((2 * i * 3.14) / 360) * .7 + 0.4;
		glVertex2f(x, y);
		glEnd();
	}
	glPopMatrix();

	glPushMatrix();
	glRotatef(180, 0, 0, 1);
	glTranslatef(0.2, 0, 0);
	glPointSize(1.0);
	for (int i = 240; i < 300; i++)
	{
		glBegin(GL_POINTS);
		x = cos((2 * i * 3.14) / 360) * .2;
		y = sin((2 * i * 3.14) / 360) * .7 + 0.4;
		glVertex2f(x, y);
		glEnd();
	}
	glPopMatrix();

	glBegin(GL_LINES);
	glVertex2f(-0.05, 0.2);
	glVertex2f(-0.15, 0.2);
	glEnd();
}

void windwheel() {
	glClear(GL_COLOR_BUFFER_BIT);


	glLoadIdentity();
	sun(0.8f, 0.8f);

	glLoadIdentity();
	bird(0.0, 0.6);

	glLoadIdentity();
	bird(0.5, 0.5);

	glLoadIdentity();
	bird(-0.5, 0.4);

	glLoadIdentity();
	body();

	drawfan(noOfFan, acc);

	glPushMatrix();
	circle(0, 0, 0.05);
	glPopMatrix();

}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	switch (page)
	{
	case 1:
		redRectangle();
		break;
	case 2:
		windwheel();
		break;

	default:
		break;
	}

}
//--------------------------------------------------------------------

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance,
	_In_ LPSTR cmdLine, _In_ int nCmdShow) // FIXED
{
	WNDCLASSEX wc;
	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.hInstance = GetModuleHandle(NULL);
	wc.lpfnWndProc = WindowProcedure;
	wc.lpszClassName = WINDOW_TITLE;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wc)) return false;

	HWND hWnd = CreateWindow(WINDOW_TITLE, WINDOW_TITLE, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
		NULL, NULL, wc.hInstance, NULL);

	//--------------------------------
	//	Initialize window for OpenGL
	//--------------------------------

	HDC hdc = GetDC(hWnd);

	//	initialize pixel format for the window
	initPixelFormat(hdc);

	//	get an openGL context
	HGLRC hglrc = wglCreateContext(hdc);

	//	make context current
	if (!wglMakeCurrent(hdc, hglrc)) return false;

	//--------------------------------
	//	End initialization
	//--------------------------------

	ShowWindow(hWnd, nCmdShow);

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		rotatedegree += spd;
		display();

		SwapBuffers(hdc);
	}

	UnregisterClass(WINDOW_TITLE, wc.hInstance);

	return true;
}
//--------------------------------------------------------------------
