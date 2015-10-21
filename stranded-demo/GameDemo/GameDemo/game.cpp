/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#include"game.h"
#include"gameEngine.h"
#include"menu.h"
#include"level.h"
#include"main.h"

#define SPEED 0.05
#define SPEED1 0.005

// Mouse button state information.
bool g_LMBDown = false;
int g_mouseX = 0, g_mouseY = 0;

// Game level.
stGameWorld g_gameWorld;

// Game states.
GAME_STATE g_gameState = GS_MENU;

// Camera.
CCamera g_camera;
CRay g_viewRay;


// Sound id for weapon shot.
int g_shotSound = -1;

int g_proSound  = 0;
int g_ringSound = 1;
int g_jumpSound = 2;
int g_goodsSound = 3;

bool GameInitialize()
{
   if(!InitializeMainMenu()) return false;

   if(!g_SoundSystem->IsPlaying(g_menuSound))
      g_SoundSystem->Play(g_menuSound);

   // Load menu sound.
   if(g_shotSound == -1)
      {
         if(!g_SoundSystem->AddSound("sounds/shot.wav", 1,
            &g_shotSound)) return false;
      }
   if(g_proSound == 0)
      {
         if(!g_SoundSystem->AddSound("sounds/pro.wav", UGP_INFINITE,
            &g_proSound)) return false;
      }
   if(g_ringSound == 1)
      {
         if(!g_SoundSystem->AddSound("sounds/ring.wav", 1,
            &g_ringSound)) return false;
      }
   if(g_jumpSound == 2)
      {
         if(!g_SoundSystem->AddSound("sounds/jump.wav", 1,
            &g_jumpSound)) return false;
      }
   if(g_goodsSound == 3)
      {
         if(!g_SoundSystem->AddSound("sounds/goods.wav", 1,
            &g_goodsSound)) return false;
      }

   return true;
}


bool ObjectsTestCollision(int i)
{
   CBoundingSphere sphere;
   int index = g_gameWorld.m_models[i].m_id;

   g_Render->GetXModelBoundingSphere(index,
      &sphere.m_center, &sphere.m_radius);

   CMatrix4x4 *worldMat = &g_gameWorld.m_models[i].worldMat;
   sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

   sphere.m_radius -= 0.5f;
   if(sphere.isPointInside(g_camera.m_pos))
      return true;

   return false;
}


bool CharacterTestCollision(int i)
{
   CBoundingSphere sphere;
   int index = g_gameWorld.m_characters[i].m_id;

   if(!g_gameWorld.m_characters[i].m_visible)
      return false;

   g_Render->GetXModelBoundingSphere(index,
      &sphere.m_center, &sphere.m_radius);

   CMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
   sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

   if(sphere.isPointInside(g_camera.m_pos))
      return true;

   return false;
}


bool CharacterTestCollision(int i, CRay &ray)
{
   CBoundingSphere sphere;
   int index = g_gameWorld.m_characters[i].m_id;

   if(!g_gameWorld.m_characters[i].m_visible)
      return false;

   g_Render->GetXModelBoundingSphere(index,
      &sphere.m_center, &sphere.m_radius);

   CMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
   sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

   if(ray.Intersect(sphere.m_center, sphere.m_radius, NULL))
      return true;

   return false;
}


bool CharacterProcess(int i)
{
   CBoundingSphere sphere;
   int index = g_gameWorld.m_characters[i].m_id;

   if(!g_gameWorld.m_characters[i].m_visible)
      return false;

   g_Render->GetXModelBoundingSphere(index,
      &sphere.m_center, &sphere.m_radius);

   CMatrix4x4 *worldMat = &g_gameWorld.m_characters[i].worldMat;
   sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

   sphere.m_radius *= 5;

   if(sphere.isPointInside(g_camera.m_pos))
      return true;

   return false;
}


void GameProcessInput()
{
   if(!g_InputSystem) return;

   // Update all devices.
   g_InputSystem->UpdateDevices();
   
   // Keyboard Input.
   if(g_InputSystem->KeyUp(DIK_ESCAPE))
      {
         if(g_gameState == GS_MENU)
            {
               switch(g_currentGUI)
                  {
                     case GUI_MAIN_SCREEN:
                        PostQuitMessage(0);
                        break;

                     default:
                        g_currentGUI = GUI_MAIN_SCREEN;
                        break;
                  }
            }
         else if(g_gameState == GS_LEVEL)
            {
               GameReleaseAll();

               InitializeMainMenu();
               g_SoundSystem->Play(g_menuSound);
			   if(g_SoundSystem->IsPlaying(g_proSound))
					g_SoundSystem->Stop(g_proSound);
               g_gameState = GS_MENU;
               g_currentGUI = GUI_MAIN_SCREEN;
            }
      }

   if(g_gameState == GS_LEVEL &&
      g_gameWorld.m_missionStatus == MISSION_ONGOING)
      {
		 
         if(g_InputSystem->KeyDown(DIK_W))
            {
               g_camera.MoveCamera(SPEED);

               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(-SPEED);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(-SPEED);
                                 break;
                              }
                        }
                  }
            }

         if(g_InputSystem->KeyDown(DIK_S))
            {
               g_camera.MoveCamera(-SPEED);
               
               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(SPEED);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(SPEED);
                                 break;
                              }
                        }
                  }
            }

         if(g_InputSystem->KeyDown(DIK_A))
            {
				g_camera.CrossCamera(SPEED);

				if(g_InputSystem->KeyDown(DIK_W))
            {
               g_camera.MoveCamera(SPEED1);

               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(-SPEED1);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(-SPEED1);
                                 break;
                              }
                        }
                  }
            }
		 for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.CrossCamera(-SPEED);
                           break;
                        }
                  }

		for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
		{
			if(CharacterProcess(i))
			{
				if(!g_gameWorld.m_characterSpot[i])
					g_gameWorld.m_spottedCount++;

				g_gameWorld.m_characterSpot[i] = 1;
				g_SoundSystem->Play(g_ringSound);
				if(CharacterTestCollision(i))
					{
						g_camera.CrossCamera(-SPEED);
						break;
					}
			}
		}
         if(g_InputSystem->KeyDown(DIK_S))
            {
               g_camera.MoveCamera(-SPEED1);
               
               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(SPEED1);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(SPEED1);
                                 break;
                              }
                        }
                  }
            }
            }

         if(g_InputSystem->KeyDown(DIK_D))
            {
               g_camera.CrossCamera(-SPEED);

			   if(g_InputSystem->KeyDown(DIK_W))
            {
               g_camera.MoveCamera(SPEED1);

               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(-SPEED1);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(-SPEED1);
                                 break;
                              }
                        }
                  }
			   for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.CrossCamera(SPEED);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.CrossCamera(SPEED);
                                 break;
                              }
                        }
                  }
            }
				for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.CrossCamera(SPEED);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.CrossCamera(SPEED);
                                 break;
                              }
                        }
                  }
			if(g_InputSystem->KeyDown(DIK_S))
            {
               g_camera.MoveCamera(-SPEED);
               
               for(int i = 0; i < g_gameWorld.m_totalModels; i++)
                  {
                     if(ObjectsTestCollision(i))
                        {
                           g_camera.MoveCamera(SPEED);
                           break;
                        }
                  }

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(CharacterProcess(i))
                        {
                           if(!g_gameWorld.m_characterSpot[i])
                              g_gameWorld.m_spottedCount++;

                           g_gameWorld.m_characterSpot[i] = 1;
						   g_SoundSystem->Play(g_ringSound);
                           if(CharacterTestCollision(i))
                              {
                                 g_camera.MoveCamera(SPEED);
                                 break;
                              }
                        }
                  }
            }
            }

         // Update view ray.
         g_viewRay.m_origin = g_camera.m_pos;
         g_viewRay.m_direction = g_camera.m_view - g_camera.m_pos;
         g_viewRay.m_direction.Normal();

         if(g_InputSystem->MouseButtonUp(UGP_LEFT_BUTTON))
            {
               g_SoundSystem->Play(g_shotSound);

               for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
                  {
                     if(g_gameWorld.m_characters[i].m_visible)
                        {
                           if(CharacterTestCollision(i, g_viewRay))
                              {
                                 g_gameWorld.m_characters[i].m_visible = 0;
                                 g_gameWorld.g_totalEnemiesKilled++;
                              }
                        }
                  }
            }
       
		POINT spos = {0,0};

		GetCursorPos(&spos);
		float mX = spos.x;
		float mY = spos.y;
		float temp = g_viewRay.m_direction.x/g_viewRay.m_direction.z;
		g_camera.RotateCamera(( mX - WIN_WIDTH/2 ) / ( WIN_WIDTH/2 ) * 0.8,0,1,0);
		
		SetCursorPos(WIN_WIDTH/2,WIN_HEIGHT/2);
	    ShowCursor(false);
		

		
      }
   
   // Mouse Input
   
   

   POINT pos = { 0, 0 };
   GetCursorPos(&pos);
   g_mouseX = pos.x;
   g_mouseY = pos.y;
   //SetCursorPos(0, 0);
 
	  

   if(g_InputSystem->MouseButtonDown(UGP_LEFT_BUTTON))
      g_LMBDown = true;
   if(!g_InputSystem->MouseButtonDown(UGP_LEFT_BUTTON))
      g_LMBDown = false;

}


void GameLoop()
{
   GameProcessInput();

   if(g_gameState == GS_LEVEL)
      LevelRender();
   else if(g_gameState == GS_MENU)
      MainMenuRender();
   else if(g_gameState == GS_LEVEL_1_SWITCH)
      {
         // Render menu for loading screen.
         MainMenuRender();
         GameReleaseAll();

         // Start first level.
         if(LoadLevel("maps/level1/level1.lvl"))
            g_gameState = GS_LEVEL;
         else
            g_gameState = GS_MENU;
      }

   if(g_gameState == GS_LEVEL)
      {
         int time = (int)(g_gameWorld.m_totalTime -
                          g_gameWorld.m_currentTime);

         if(time <= 0)
            g_gameWorld.m_missionStatus = MISSION_FAIL;

         if(g_gameWorld.m_numArtifactsCollected >=
            g_gameWorld.m_totalArtifacts)
            g_gameWorld.m_missionStatus = MISSION_COMPLETE;
      }
}


void GameShutdown()
{
   GameReleaseAll();
}


void GameReleaseAll()
{
   if(!g_Render) return;

   g_Render->ReleaseAllStaticBuffers();
   g_Render->ReleaseAllXModels();
   g_Render->ReleaseAllGUIs();
   
   g_gameWorld.Shutdown();

   g_mainGui = -1;
   g_startGui = -1;
   g_creditsGui = -1;
   g_currentGUI = GUI_MAIN_SCREEN;

   if(!g_SoundSystem) return;

   if(g_gameState != GS_MENU && g_gameState != GS_LEVEL)
      g_SoundSystem->Stop(g_menuSound);
}