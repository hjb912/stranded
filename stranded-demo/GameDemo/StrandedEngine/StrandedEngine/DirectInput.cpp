/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#include"DirectInput.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#define MOUSE_BUFF_SIZE 16



bool CreateDIInput(CInputInterface **pObj, HWND hwnd, HINSTANCE hInst, bool exclusive)
{
   if(!*pObj) *pObj = new CDirectInputSystem(hwnd, hInst, exclusive);
   else return false;
   
   return true;
}



CKeyboard::CKeyboard(LPDIRECTINPUT8 input, HWND hwnd)
{
   // Initialize the keyboard.
   if(input->CreateDevice(GUID_SysKeyboard, &m_device, NULL) == DI_OK)
      {
         if(m_device->SetDataFormat(&c_dfDIKeyboard) == DI_OK)
            {
               if(m_device->SetCooperativeLevel(hwnd,
                  DISCL_FOREGROUND |DISCL_NONEXCLUSIVE) == DI_OK)
                  {
                     m_device->Acquire();
                  }
            }
   }

   // Clear keys will clear out the array of keys we have.
   memset(m_keys, 0, sizeof(m_keys));
}

int CKeyboard::ButtonUp(unsigned int key)
{
   // If the key in the variable is not pressed then return false.
   return (!(m_keys[key] & 0x80) && m_keys[key] != m_oldKeys[key]);
}


int CKeyboard::ButtonDown(unsigned int key)
{
   // If the key in the variable is not pressed then return false.
   return m_keys[key] & 0x80;
}


POINT CKeyboard::GetPosition()
{
   // Doesn't have position.
   POINT p = { 0, 0 };
   return p;
}


POINT CKeyboard::GetZPosition()
{
   // Doesn't have position.
   POINT p = { 0, 0 };
   return p;
}


bool CKeyboard::UpdateDevice()
{
   if(m_device)
      {
         // Save old state for input comparing.
         memcpy(m_oldKeys, m_keys, sizeof(m_keys));

         // If error getting device state, re-aquire.
         if(FAILED(m_device->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
            {
               if(FAILED(m_device->Acquire())) return false;
               if(FAILED(m_device->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
                  return false;
            }
       }

   return true;
}


void CKeyboard::Shutdown()
{
   if(m_device)
      {
         m_device->Unacquire();
         m_device->Release();
         m_device = NULL;
      }
}


CMouse::CMouse(LPDIRECTINPUT8 input, HWND hwnd, bool exclusive)
{
   // Initialize the Mouse.
   DWORD flags;

   if(input->CreateDevice(GUID_SysMouse, &m_device, NULL) == DI_OK)
      {
         if(m_device->SetDataFormat(&c_dfDIMouse) == DI_OK)
            {
               if(exclusive) flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
               else flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;

               if(m_device->SetCooperativeLevel(hwnd, flags) == DI_OK)
                  {
                     m_device->Acquire();
                  }
            }
      }
}


int CMouse::ButtonUp(unsigned int button)
{
   // If the button is not clicked we return false.
   return (!(m_mouseState.rgbButtons[button] & 0x80) &&
           m_mouseState.rgbButtons[button] != m_oldMouseState.rgbButtons[button]);
}


int CMouse::ButtonDown(unsigned int button)
{
   // If the button is clicked we return true.
   return m_mouseState.rgbButtons[button] & 0x80;
}


bool CMouse::UpdateDevice()
{
   // Get the device state.
   if(m_device)
      {
         // Save old state for input comparing.
         memcpy(&m_oldMouseState, &m_mouseState, sizeof(m_mouseState));

         // If error getting device state, re-aquire.
         if(FAILED(m_device->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
            {
               if(FAILED(m_device->Acquire())) return false;
               if(FAILED(m_device->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
                  return false;
            }

         m_xMPos += m_mouseState.lX;
         m_yMPos += m_mouseState.lY;
         m_zMPos = m_mouseState.lZ;
      }

   return true;
}

POINT CMouse::GetPosition()
{
   POINT pos;

   pos.x = m_xMPos;
   pos.y = m_yMPos;
   return pos;
}


POINT CMouse::GetZPosition()
{
   POINT p = { m_zMPos, m_zMPos };
   return p;
}


void CMouse::Shutdown()
{
   if(m_device)
      {
         m_device->Unacquire();
         m_device->Release();
         m_device = NULL;
      }
}




CDirectInputSystem::CDirectInputSystem(HWND hwnd, HINSTANCE hInst, bool exclusive)
{
   // Initialize objects...
   m_keyboard = NULL;
   m_mouse = NULL;

   // Create input system.
   if(DirectInput8Create(hInst, DIRECTINPUT_VERSION,
      IID_IDirectInput8, (void **)&m_system, NULL) == DI_OK)
   {
      m_keyboard = new CKeyboard(m_system, hwnd);
      m_mouse = new CMouse(m_system, hwnd, exclusive);

   }
}


CDirectInputSystem::~CDirectInputSystem()
{
   // Shut everything down.
   Shutdown();
}


bool CDirectInputSystem::Initialize()
{
   // Everything took place in the constructor.
   // Force keyboard and mouse before considering the
   // system initialized.
   return (m_keyboard && m_mouse);
}


bool CDirectInputSystem::UpdateDevices()
{
   int hr;

   // Get the device state.
   if(m_mouse) hr = m_mouse->UpdateDevice();
   if(m_keyboard) hr = m_keyboard->UpdateDevice();

   return true;
}


int CDirectInputSystem::KeyUp(unsigned int key)
{
   if(!m_keyboard) return 0;
   return m_keyboard->ButtonUp(key);
}


int CDirectInputSystem::KeyDown(unsigned int key)
{
   if(!m_keyboard) return 0;
   return m_keyboard->ButtonDown(key);
}


int CDirectInputSystem::MouseButtonUp(unsigned int button)
{
   if(!m_mouse) return 0;
   return m_mouse->ButtonUp(button);
}


int CDirectInputSystem::MouseButtonDown(unsigned int button)
{
   if(!m_mouse) return 0;
   return m_mouse->ButtonDown(button);
}


POINT CDirectInputSystem::GetMousePos()
{
   POINT null = {0, 0};
   if(!m_mouse) return null;

   return m_mouse->GetPosition();
}


long CDirectInputSystem::GetMouseWheelPos()
{
   if(!m_mouse) return 0;

   POINT wheel =  m_mouse->GetZPosition();
   return wheel.y;
}


void CDirectInputSystem::Shutdown()
{
   // Delete each object...
   if(m_keyboard)
      {
         m_keyboard->Shutdown();
         delete m_keyboard;
         m_keyboard = NULL;
      }

   if(m_mouse)
      {
         m_mouse->Shutdown();
         delete m_mouse;
         m_mouse = NULL;
      }


   if(m_system)
      {
         m_system->Release();
         m_system = NULL;
      }
}