/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _UGP_DIRECTINPUT_H_
#define _UGP_DIRECTINPUT_H_

#include<dinput.h>
#include"InputInterface.h"
#include"defines.h"


class CKeyboard : public CDeviceInterface
{
   public:
      CKeyboard(LPDIRECTINPUT8 input, HWND hwnd);
      ~CKeyboard() { Shutdown(); }

      bool UpdateDevice();

      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);

      POINT GetPosition();
      POINT GetZPosition();

      void Shutdown();

      // Keyboard device.
      LPDIRECTINPUTDEVICE8 m_device;
      char m_keys[KEYS_SIZE];
      char m_oldKeys[KEYS_SIZE];
};


class CMouse : public CDeviceInterface
{
   public:
      CMouse(LPDIRECTINPUT8 input, HWND hwnd, bool exclusive);
      ~CMouse() { Shutdown(); }

      bool UpdateDevice();

      int ButtonUp(unsigned int key);
      int ButtonDown(unsigned int key);

      POINT GetPosition();
      POINT GetZPosition();

      void Shutdown();

      // Mouse device.
      LPDIRECTINPUTDEVICE8 m_device;
      DIMOUSESTATE m_mouseState;
      DIMOUSESTATE m_oldMouseState;
      bool m_button[3];

      // Mouse x, y, and wheel position.
      long m_xMPos;
      long m_yMPos;
      long m_zMPos;

      // Max x (width) and y (height)
      // Restrict means to cap at width/height.
      bool m_restrict;
      int m_width;
      int m_height;
};

class CDirectInputSystem : public CInputInterface
{
   public:
      CDirectInputSystem(HWND hwnd, HINSTANCE hInst, bool exclusive);
      ~CDirectInputSystem();

      // Init devics, update devices states.
      bool Initialize();
      bool UpdateDevices();
      
      // Keyboard functions.
      int KeyUp(unsigned int key);
      int KeyDown(unsigned int key);

      // Mouse functions.
      int MouseButtonUp(unsigned int button);
      int MouseButtonDown(unsigned int button);

      // Get mouse position (x, y) and mouse wheel data (z).
      POINT GetMousePos();
      long GetMouseWheelPos();


      void Shutdown();

   protected:
      LPDIRECTINPUT8 m_system;

      // Devices.
      CKeyboard *m_keyboard;
      CMouse *m_mouse;
    
};

bool CreateDIInput(CInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive);

#endif