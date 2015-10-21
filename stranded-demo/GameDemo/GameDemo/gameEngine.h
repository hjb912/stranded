/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _UGP_GAME_ENGINE_H_
#define _UGP_GAME_ENGINE_H_

// Includes...
#include"StrandedEngine/engine.h"

// Function Prototypes...
bool InitializeEngine();
void ShutdownEngine();

// Globals...
extern CRenderInterface *g_Render;
extern CInputInterface *g_InputSystem;
extern CSoundSystemInterface *g_SoundSystem;


// Font id.
extern int g_arialID;
extern int g_arial24ID;
extern int g_arial36ID;

#endif