#include "framework.h"
#include "RayTracing.h"
#include <Windows.h>
#include <iostream>

#include <glad/glad.h>

#include <cmath>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <ctime>
#include <chrono>

#pragma comment(lib, "opengl32.lib")

#include "Actor.h"

#define _size 6

HDC MyDC;
GLuint prog;

LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

double DeltaSeconds;
double TotalSeconds;

int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    WNDCLASSEX wcex;
    HWND hwnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
        L"GLSample",
        L"OpenGL Sample",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        1700,
        1700 * 9.0 / 16.0,
        NULL,
        NULL,
        hInstance,
        NULL);

    ShowWindow(hwnd, nCmdShow);

    srand(time(0));
    // Camera

    auto start = std::chrono::high_resolution_clock::now();
    auto end = start;
    
    EnableOpenGL(hwnd, &hDC, &hRC);
    gladLoadGL();

    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 1, 8);
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    Actor Serdechko;
    Serdechko.InitMesh("Boss-Lustra.obj");
    Serdechko.InitMaterialShader("BaseMat");

    while (true) {
        end = std::chrono::high_resolution_clock::now();
        DeltaSeconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0f;
        TotalSeconds += 12.0f / 360;
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                break;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(prog);

        glPushMatrix();
        glTranslatef(0, 0, -4 - sin(TotalSeconds) / 3);
        glRotatef(90, 0, 1, 0);
        glRotatef(TotalSeconds * 10, 0.0f, 1.0f, 0.0f);
        glScalef(2, 2, 2);

        glEnableClientState(GL_VERTEX_ARRAY);
        {
            Serdechko.Tick(DeltaSeconds);
        }
        glDisableClientState(GL_VERTEX_ARRAY);

        glPopMatrix();

        SwapBuffers(hDC);

        glUseProgram(0);

        start = end;
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        return 0;

    case WM_MOUSEMOVE:
        break;

    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            break;
        }
    }
    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
        PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL(HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}