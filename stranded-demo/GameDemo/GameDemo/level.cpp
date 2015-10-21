/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#include"level.h"
#include"gameEngine.h"
#include"game.h"
#include"StrandedEngine/CommandScript.h"
#include"StrandedEngine/LogSystem.h"
#include"main.h"


bool LoadLevel(char *file)
{
   if(!g_Render || !file) return false;

   CLogSystem gameLog;
   CCommandScript script;

   char command[MAX_COMMAND_SIZE];
   char param[MAX_PARAM_SIZE];
   int totalModels = 0;
   int currentModelNum = 0;
   int totalArtifacts = 0;
   int currentArtifactNum = 0;
   int totalCharacters = 0;
   int currentCharacterNum = 0;

  
   
   if(!script.LoadScriptFile(file))
      return false;

   for(int i = 0; i < script.GetTotalLines(); i++)
      {
         script.ParseCommand(command);

         if(stricmp(command, "LoadSkyBoxAsX") == 0) { }
         else if(stricmp(command, "LoadTerrainAsX") == 0) { }
         else if(stricmp(command, "LoadStaticModelAsX") == 0)
            {
               totalModels++;
            }
         else if(stricmp(command, "LoadAnimatedModelAsX") == 0)
            {
               totalModels++;
            }
         else if(stricmp(command, "LoadArtifactModelAsX") == 0)
            {
               totalArtifacts++;
            }
         else if(stricmp(command, "LoadCharacterModelAsX") == 0)
            {
               totalCharacters++;
            }
         else if(stricmp(command, "SetTimer") == 0) { }
         else if(stricmp(command, "#") == 0) { }
         else if(stricmp(command, "SetCamera") == 0) { }
         else
            {
               gameLog.AppendLog("ErrorLog.txt",
                                 "Error loading level on %d.\n",
                                 script.GetCurrentLineNum() + 1);

               script.Shutdown();
               return false;
            }

         script.MoveToNextLine();
      }

   script.MoveToStart();

   if(g_gameWorld.m_models)
      delete[] g_gameWorld.m_models;

   g_gameWorld.m_models = new stGameObject[totalModels];
   g_gameWorld.m_artifacts = new stGameObject[totalArtifacts];
   g_gameWorld.m_artifactsCollected = new int[totalArtifacts];
   ZeroMemory(g_gameWorld.m_artifactsCollected, sizeof(int) * totalArtifacts);

   g_gameWorld.m_characters = new stGameObject[totalCharacters];
   g_gameWorld.m_characterSpot = new int[totalCharacters];
   ZeroMemory(g_gameWorld.m_characterSpot, sizeof(int) * totalCharacters);

   for(int i = 0; i < script.GetTotalLines(); i++)
      {
         script.ParseCommand(command);

         if(stricmp(command, "LoadSkyBoxAsX") == 0)
            {
               script.ParseStringParam(param);
               
               if(g_gameWorld.m_skyBoxID == -1)
                  {
                     if(!g_Render->LoadXModel(param, &g_gameWorld.m_skyBoxID))
                        return false;
                  }
               else
                  {
                     if(!g_Render->LoadXModel(param, g_gameWorld.m_skyBoxID))
                        return false;
                  }
            }
         else if(stricmp(command, "LoadTerrainAsX") == 0)
            {
               script.ParseStringParam(param);
               
               if(g_gameWorld.m_levelID == -1)
                  {
                     if(!g_Render->LoadXModel(param, &g_gameWorld.m_levelID))
                        return false;
                  }
               else
                  {
                     if(!g_Render->LoadXModel(param, g_gameWorld.m_levelID))
                        return false;
                  }
            }
         else if(stricmp(command, "LoadStaticModelAsX") == 0)
            {
               stGameObject *obj = NULL;
               obj = &g_gameWorld.m_models[currentModelNum++];

               if(obj)
                  {
                     script.ParseStringParam(param);

                     if(!g_Render->LoadXModel(param, &obj->m_id))
                        return false;

                     obj->m_type = X_MESH;
                     obj->m_x = script.ParseFloatParam();
                     obj->m_y = script.ParseFloatParam();
                     obj->m_z = script.ParseFloatParam();
                     obj->m_rotX = script.ParseFloatParam();
                     obj->m_rotY = script.ParseFloatParam();
                     obj->m_rotZ = script.ParseFloatParam();
                  }
            }
         else if(stricmp(command, "LoadAnimatedModelAsX") == 0)
            {
               stGameObject *obj = NULL;
               obj = &g_gameWorld.m_models[currentModelNum++];

               if(obj)
                  {
                     script.ParseStringParam(param);

                     if(!g_Render->LoadXModel(param, &obj->m_id))
                        return false;

                     obj->m_type = X_ANIMATED_MESH;
                     obj->m_x = script.ParseFloatParam();
                     obj->m_y = script.ParseFloatParam();
                     obj->m_z = script.ParseFloatParam();
                     obj->m_rotX = script.ParseFloatParam();
                     obj->m_rotY = script.ParseFloatParam();
                     obj->m_rotZ = script.ParseFloatParam();
                  }
            }
         else if(stricmp(command, "LoadCharacterModelAsX") == 0)
            {
               stGameObject *obj = NULL;
               obj = &g_gameWorld.m_characters[currentCharacterNum++];

               if(obj)
                  {
                     script.ParseStringParam(param);

                     if(!g_Render->LoadXModel(param, &obj->m_id))
                        return false;

                     obj->m_type = X_ANIMATED_MESH;
                     obj->m_x = script.ParseFloatParam();
                     obj->m_y = script.ParseFloatParam();
                     obj->m_z = script.ParseFloatParam();
                     obj->m_rotX = script.ParseFloatParam();
                     obj->m_rotY = script.ParseFloatParam();
                     obj->m_rotZ = script.ParseFloatParam();
                  }
            }
         else if(stricmp(command, "#") == 0) { }
         else if(stricmp(command, "SetCamera") == 0)
            {
               g_camera.SetCamera(script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam(),
                                  script.ParseFloatParam());
            }
		
         else if(stricmp(command, "LoadArtifactModelAsX") == 0)
            {
               stGameObject *obj = NULL;
               obj = &g_gameWorld.m_artifacts[currentArtifactNum++];

               if(obj)
                  {
                     script.ParseStringParam(param);

                     if(!g_Render->LoadXModel(param, &obj->m_id))
                        return false;

                     obj->m_type = X_ANIMATED_MESH;
                     obj->m_x = script.ParseFloatParam();
                     obj->m_y = script.ParseFloatParam();
                     obj->m_z = script.ParseFloatParam();
                     obj->m_rotX = script.ParseFloatParam();
                     obj->m_rotY = script.ParseFloatParam();
                     obj->m_rotZ = script.ParseFloatParam();
                  }
            }
         else if(stricmp(command, "SetTimer") == 0)
            {
               g_gameWorld.m_totalTime = script.ParseFloatParam();
            }

         script.MoveToNextLine();
      }
   g_camera.SetCamera(0,1,0,1,1,0,0,1,0);
   g_gameWorld.m_totalModels = totalModels;
   g_gameWorld.m_totalArtifacts = totalArtifacts;
   g_gameWorld.m_totalCharacters = totalCharacters;

   for(int i = 0; i < g_gameWorld.m_totalModels; i++)
      {
         CMatrix4x4 trans, rotX, rotY, rotZ;

         trans.Translate(g_gameWorld.m_models[i].m_x,
                           g_gameWorld.m_models[i].m_y,
                           g_gameWorld.m_models[i].m_z);

         if(g_gameWorld.m_models[i].m_rotX)
            rotX.Rotate(g_gameWorld.m_models[i].m_rotX, 1, 0, 0);

         if(g_gameWorld.m_models[i].m_rotY)
            rotY.Rotate(g_gameWorld.m_models[i].m_rotY, 0, 1, 0);

         if(g_gameWorld.m_models[i].m_rotZ)
            rotZ.Rotate(g_gameWorld.m_models[i].m_rotZ, 0, 1, 0);

         g_gameWorld.m_models[i].worldMat = trans * (rotX * rotY * rotZ);
      }

   for(int i = 0; i < g_gameWorld.m_totalArtifacts; i++)
      {
         CMatrix4x4 trans, rotX, rotY, rotZ;

         trans.Translate(g_gameWorld.m_artifacts[i].m_x,
                         g_gameWorld.m_artifacts[i].m_y,
                         g_gameWorld.m_artifacts[i].m_z);

         if(g_gameWorld.m_artifacts[i].m_rotX)
            rotX.Rotate(g_gameWorld.m_artifacts[i].m_rotX, 1, 0, 0);

         if(g_gameWorld.m_artifacts[i].m_rotY)
            rotY.Rotate(g_gameWorld.m_artifacts[i].m_rotY, 0, 1, 0);

         if(g_gameWorld.m_artifacts[i].m_rotZ)
            rotZ.Rotate(g_gameWorld.m_artifacts[i].m_rotZ, 0, 1, 0);

         g_gameWorld.m_artifacts[i].worldMat = trans * (rotX * rotY * rotZ);
      }

   for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
      {
         CMatrix4x4 trans, rotX, rotY, rotZ;

         trans.Translate(g_gameWorld.m_characters[i].m_x,
                         g_gameWorld.m_characters[i].m_y,
                         g_gameWorld.m_characters[i].m_z);

         if(g_gameWorld.m_characters[i].m_rotX)
            rotX.Rotate(g_gameWorld.m_characters[i].m_rotX, 1, 0, 0);

         if(g_gameWorld.m_characters[i].m_rotY)
            rotY.Rotate(g_gameWorld.m_characters[i].m_rotY, 0, 1, 0);

         if(g_gameWorld.m_characters[i].m_rotZ)
            rotZ.Rotate(g_gameWorld.m_characters[i].m_rotZ, 0, 1, 0);

         g_gameWorld.m_characters[i].worldMat = trans * (rotX * rotY * rotZ);
      }

   g_gameWorld.m_levelStartTime = (float)timeGetTime();

   script.Shutdown();

   return true;
}


bool TestArtifactCollision(int i)
{
   CBoundingSphere sphere;
   int index = g_gameWorld.m_artifacts[i].m_id;

   g_Render->GetXModelBoundingSphere(index,
      &sphere.m_center, &sphere.m_radius);

   CMatrix4x4 *worldMat = &g_gameWorld.m_artifacts[i].worldMat;
   sphere.m_center = worldMat->VectorMatrixMultiply(sphere.m_center);

   if(sphere.isPointInside(g_camera.m_pos))
      return true;

   return false;
}


void LevelRender()
{
   float time = (float)timeGetTime();

   g_SoundSystem->Play(g_proSound);

   if(g_gameWorld.m_missionStatus == MISSION_ONGOING)
      g_gameWorld.m_currentTime = (time -
         g_gameWorld.m_levelStartTime) * 0.001f;

   time = (time - g_gameWorld.m_startTime) * 0.001f;
   g_gameWorld.m_startTime = (float)timeGetTime();

   if(!g_Render || g_gameState != GS_LEVEL) return;

   CMatrix4x4 world;

   g_Render->StartRender(1, 1, 0);

      g_Render->ApplyView(g_camera.m_pos,
                          g_camera.m_view,
                          g_camera.m_up);

      g_Render->SetWorldMatrix(&world);
      g_Render->RenderXModel(g_gameWorld.m_levelID);
      
      world.Translate(g_camera.m_pos.x, g_camera.m_pos.y,
                      g_camera.m_pos.z);

      g_Render->SetWorldMatrix(&world);
      g_Render->RenderXModel(g_gameWorld.m_skyBoxID);

      if(g_gameWorld.m_models)
         {
            for(int i = 0; i < g_gameWorld.m_totalModels; i++)
               {
                  g_Render->SetWorldMatrix(&g_gameWorld.m_models[i].worldMat);

                  if(g_gameWorld.m_models[i].m_type == X_ANIMATED_MESH)
                     g_Render->UpdateXAnimation(g_gameWorld.m_models[i].m_id,
                                                time,
                                                &g_gameWorld.m_models[i].worldMat);
                  else
                     g_Render->UpdateXAnimation(g_gameWorld.m_models[i].m_id, 0,
                                                &g_gameWorld.m_models[i].worldMat);

                  g_Render->RenderXModel(g_gameWorld.m_models[i].m_id);
               }
         }
         
      if(g_gameWorld.m_artifacts)
         {
            for(int i = 0; i < g_gameWorld.m_totalArtifacts; i++)
               {
                  if(g_gameWorld.m_artifactsCollected)
                     {
                        if(!g_gameWorld.m_artifactsCollected[i])
                           {
                              if(TestArtifactCollision(i))
                                 {
                                    g_gameWorld.m_artifactsCollected[i] = 1;
                                    g_gameWorld.m_numArtifactsCollected++;
									g_SoundSystem->Play(g_goodsSound);
                                 }
                           }
                     }

                  if(!g_gameWorld.m_artifactsCollected[i])
                     {
                        g_Render->UpdateXAnimation(g_gameWorld.m_artifacts[i].m_id,
                                                   time,
                                                   &g_gameWorld.m_artifacts[i].worldMat);
                        g_Render->SetWorldMatrix(&g_gameWorld.m_artifacts[i].worldMat);
                        g_Render->RenderXModel(g_gameWorld.m_artifacts[i].m_id);
                     }
               }
         }

   if(g_gameWorld.m_characters)
      {
         for(int i = 0; i < g_gameWorld.m_totalCharacters; i++)
            {
               if(g_gameWorld.m_characters[i].m_visible)
                  {
                     g_Render->SetWorldMatrix(&g_gameWorld.m_characters[i].worldMat);

                     if(g_gameWorld.m_characterSpot[i])
                        g_Render->UpdateXAnimation(
                           g_gameWorld.m_characters[i].m_id, time,
                           &g_gameWorld.m_characters[i].worldMat);
                     else
                        g_Render->UpdateXAnimation(
                           g_gameWorld.m_characters[i].m_id, 0,
                           &g_gameWorld.m_characters[i].worldMat);

                     g_Render->RenderXModel(g_gameWorld.m_characters[i].m_id);
                  }
            }
      }


   unsigned long col = UGPCOLOR_ARGB(255, 255, 255, 255);
   int displayTime = (int)(g_gameWorld.m_totalTime -
                           g_gameWorld.m_currentTime);
   if(displayTime < 0) displayTime = 0;

   int tempValue1,tempValue2,tempValue3;
   tempValue1 = g_gameWorld.m_numArtifactsCollected * 5;
   displayTime += tempValue1;
   tempValue2 = g_gameWorld.m_spottedCount * (30);
   displayTime -= tempValue2;
   tempValue3 = g_gameWorld.g_totalEnemiesKilled * 15;
   displayTime -= tempValue3;

   if(displayTime < 0) 
   {
	   displayTime = 0;
	   g_gameWorld.m_missionStatus = MISSION_FAIL;
   }
   if(g_gameWorld.m_missionStatus == MISSION_ONGOING)
      {
         // Render cross hair.
		 
         g_Render->DisplayText(g_arial36ID, WIN_WIDTH / 2 -10 ,
            WIN_HEIGHT / 2 - 30 , col, "+");

         g_Render->DisplayText(g_arial24ID, 0, 10, col, "WIN32 3D MARIO: The Game");
         g_Render->DisplayText(g_arial24ID, 0, 50, col, "Time Left: %d",
                              displayTime);
         g_Render->DisplayText(g_arial24ID, 0, 80, col,
                              "Total Artifacts found: %d out of %d",
                              g_gameWorld.m_numArtifactsCollected,
                              g_gameWorld.m_totalArtifacts);
         g_Render->DisplayText(g_arial24ID, 0, 100, col,
                              "Total eneimes spot you: %d out of %d",
                              g_gameWorld.m_spottedCount,
                              g_gameWorld.m_totalCharacters);
         g_Render->DisplayText(g_arial24ID, 0, 120, col,
                              "Total eneimes killed: %d out of %d",
                              g_gameWorld.g_totalEnemiesKilled,
                              g_gameWorld.m_totalCharacters);
      }
   else if(g_gameWorld.m_missionStatus == MISSION_COMPLETE)
      {
         g_Render->DisplayText(g_arial36ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2, col, "YOU WIN! Press escape to quit.");

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 70, col, "Total Times Spotted: %d",
            g_gameWorld.m_spottedCount);

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 120, col, "Time Taken: %d(%d,%d,%d)",
            (int)g_gameWorld.m_totalTime - displayTime,tempValue1,tempValue2,tempValue3);

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 170, col, "Enemies killed: %d",
            g_gameWorld.g_totalEnemiesKilled);
      }
   else if(g_gameWorld.m_missionStatus == MISSION_FAIL)
      {
         g_Render->DisplayText(g_arial36ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2, col, "YOU LOSE! Press escape to quit.");

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 70, col, "Total Times Spotted: %d",
            g_gameWorld.m_spottedCount);

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 120, col,
            "Total Artifacts found: %d out of %d",
            g_gameWorld.m_numArtifactsCollected,
            g_gameWorld.m_totalArtifacts);

         g_Render->DisplayText(g_arial24ID, WIN_WIDTH / 6,
            WIN_HEIGHT / 2 + 170, col, "Enemies killed: %d",
            g_gameWorld.g_totalEnemiesKilled);
      }

   g_Render->EndRendering();
}