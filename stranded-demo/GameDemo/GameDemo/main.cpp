/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#include"main.h"
#include"game.h"
#include"gameEngine.h"

#pragma comment(lib, "winmm.lib")


// Globals...
HWND g_hwnd = 0;
HINSTANCE g_hInstance = 0;


LRESULT WINAPI MsgProc(HWND hd, UINT msg, WPARAM wp, LPARAM lp)
{
   switch(msg)
      {
         case WM_DESTROY:
         case WM_CLOSE:
            PostQuitMessage(0);
            return 0;
            break;
      }

   return DefWindowProc(hd, msg, wp, lp);
}


int WINAPI WinMain(HINSTANCE h, HINSTANCE p, LPSTR cmd, int show)
{
   // Register the window class
   WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,
                     0L, 0L, GetModuleHandle(NULL), NULL, NULL,
                     NULL, NULL, WINDOW_CLASS, NULL };
   RegisterClassEx(&wc);

   // Create the application's window
   if(FULLSCREEN)
      {
         g_hwnd = CreateWindowEx(NULL, WINDOW_CLASS, WINDOW_NAME,
                     WS_POPUP | WS_SYSMENU | WS_VISIBLE, 0, 0,
                     WIN_WIDTH, WIN_HEIGHT, NULL, NULL, h, NULL);
      }
   else
      {
         g_hwnd = CreateWindowEx(NULL, WINDOW_CLASS, WINDOW_NAME,
                     WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0,
                     WIN_WIDTH, WIN_HEIGHT, NULL, NULL, h, NULL);
      }

   if(g_hwnd)
      {
         // Show the window
         ShowWindow(g_hwnd, SW_SHOWDEFAULT);
         UpdateWindow(g_hwnd);
      }

   // Set copy.
   g_hInstance = wc.hInstance;

   // Initialize the Stranded Engine.
   if(InitializeEngine())
      {
         // Initialize Stranded game.
         if(GameInitialize())
            {
               // Enter the message loop
               MSG msg;
               ZeroMemory(&msg, sizeof(msg));
               SetCursorPos(0, 0);

               while(msg.message != WM_QUIT)
                  {
                     if(PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
                        {
                           TranslateMessage(&msg);
                           DispatchMessage(&msg);
                        }
                     else GameLoop();
                  }
            }
      }

   // Release any and all resources.
   GameShutdown();
   ShutdownEngine();
   UnregisterClass(WINDOW_CLASS, wc.hInstance);
   return 0;
}