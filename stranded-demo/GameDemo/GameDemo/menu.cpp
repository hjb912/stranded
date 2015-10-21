/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#include"menu.h"
#include"gameEngine.h"
#include"game.h"
#include"main.h"


// GUI ids.
int g_mainGui = -1;
int g_startGui = -1;
int g_creditsGui = -1;
int g_loadingGui = -1;
int g_currentGUI = GUI_MAIN_SCREEN;

// Sound id.
int g_menuSound = -1;


bool InitializeMainMenu()
{
   // Create gui screens.
   if(!g_Render->CreateGUI(g_mainGui)) return false;
   if(!g_Render->CreateGUI(g_startGui)) return false;
   if(!g_Render->CreateGUI(g_creditsGui)) return false;
   if(!g_Render->CreateGUI(g_loadingGui)) return false;

   // Load backdrops.
   if(!g_Render->AddGUIBackdrop(g_mainGui, "menu/mainMenu.jpg"))
      return false;
   if(!g_Render->AddGUIBackdrop(g_startGui, "menu/startMenu.jpg"))
      return false;
   if(!g_Render->AddGUIBackdrop(g_creditsGui,
      "menu/creditsMenu.jpg")) return false;
   if(!g_Render->AddGUIBackdrop(g_loadingGui,
      "menu/loadingMenu.jpg")) return false;

   // Set main screen elements.
   if(!g_Render->AddGUIStaticText(g_mainGui, STATIC_TEXT_ID,
      "Version: 1.0", PERCENT_OF(WIN_WIDTH, 0.85),
      PERCENT_OF(WIN_WIDTH, 0.05),
      UGPCOLOR_ARGB(255,255,255,255), g_arialID)) return false;

   if(!g_Render->AddGUIButton(g_mainGui, BUTTON_START_ID,
      PERCENT_OF(WIN_WIDTH, 0.05), PERCENT_OF(WIN_HEIGHT, 0.40),
      "menu/startUp.png", "menu/StartOver.png",
      "menu/startDown.png")) return false;

   if(!g_Render->AddGUIButton(g_mainGui, BUTTON_CREDITS_ID,
      PERCENT_OF(WIN_WIDTH, 0.05), PERCENT_OF(WIN_HEIGHT, 0.50),
      "menu/creditsUp.png", "menu/creditsOver.png",
      "menu/creditsDown.png")) return false;

   if(!g_Render->AddGUIButton(g_mainGui, BUTTON_QUIT_ID,
      PERCENT_OF(WIN_WIDTH, 0.05), PERCENT_OF(WIN_HEIGHT, 0.60),
      "menu/quitUp.png", "menu/quitOver.png",
      "menu/quitDown.png")) return false;


   // Set start screen elements.
   if(!g_Render->AddGUIButton(g_startGui, BUTTON_LEVEL_1_ID,
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.15),
      "menu/level1Up.png", "menu/level1Over.png",
      "menu/level1Down.png")) return false;

   if(!g_Render->AddGUIButton(g_startGui, BUTTON_BACK_ID,
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.80),
      "menu/backUp.png", "menu/backOver.png",
      "menu/backDown.png")) return false;


   // Set credits screen elements.
   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "Game Design -",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.15),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "              HUANGJAINGBO",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.20),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "Programming -",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.25),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "              HUANGJAINGBO",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.30),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "Sound -",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.35),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "              HUANGJAINGBO",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.40),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "Level Design -",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.45),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "              HUANGJAINGBO",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.50),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "Speical Thanks -",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.55),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;

   if(!g_Render->AddGUIStaticText(g_creditsGui, STATIC_TEXT_ID,
      "              MANY BOOKS!!",
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.60),
      UGPCOLOR_ARGB(255,255,255,255),
      g_arialID)) return false;



   if(!g_Render->AddGUIButton(g_creditsGui, BUTTON_BACK_ID,
      PERCENT_OF(WIN_WIDTH, 0.1), PERCENT_OF(WIN_HEIGHT, 0.80),
      "menu/backUp.png", "menu/backOver.png",
      "menu/backDown.png")) return false;


   // Load menu sound.
   if(g_menuSound == -1)
      {
         if(!g_SoundSystem->AddSound("sounds/menu.wav", UGP_INFINITE,
            &g_menuSound)) return false;
      }

   g_SoundSystem->Play(g_menuSound);

   return true;
}


void MainMenuCallback(int id, int state)
{
   switch(id)
      {
         case BUTTON_START_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_START_SCREEN;
            break;

         case BUTTON_CREDITS_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_CREDITS_SCREEN;
            break;

         case BUTTON_BACK_ID:
            if(state == UGP_BUTTON_DOWN)
               g_currentGUI = GUI_MAIN_SCREEN;
            break;

         case BUTTON_QUIT_ID:
            if(state == UGP_BUTTON_DOWN)
               {
                  GameReleaseAll();
                  PostQuitMessage(0);
               }
            break;

         case BUTTON_LEVEL_1_ID:
            if(state == UGP_BUTTON_DOWN)
               {
                  g_currentGUI = GUI_LOADING_SCREEN;
                  g_gameState = GS_LEVEL_1_SWITCH;
               }
            break;
      }
}


void MainMenuRender()
{
   if(!g_Render || g_gameState != GS_MENU &&
       g_gameState != GS_LEVEL_1_SWITCH) return;

   g_Render->StartRender(1, 1, 0);

      if(g_currentGUI == GUI_MAIN_SCREEN)
         g_Render->ProcessGUI(g_mainGui, g_LMBDown, g_mouseX,
                              g_mouseY, MainMenuCallback);
      else if(g_currentGUI == GUI_START_SCREEN)
         g_Render->ProcessGUI(g_startGui, g_LMBDown, g_mouseX,
                              g_mouseY, MainMenuCallback);
      else if(g_currentGUI == GUI_CREDITS_SCREEN)
         g_Render->ProcessGUI(g_creditsGui, g_LMBDown, g_mouseX,
                              g_mouseY, MainMenuCallback);
      else if(g_currentGUI == GUI_LOADING_SCREEN)
         g_Render->ProcessGUI(g_loadingGui, g_LMBDown, g_mouseX,
                              g_mouseY, MainMenuCallback);

   g_Render->EndRendering();
}