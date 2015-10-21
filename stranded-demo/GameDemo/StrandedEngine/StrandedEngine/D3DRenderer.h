/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _D3D_RENDERER_H_
#define _D3D_RENDERER_H_

#include<windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include"RenderInterface.h"
#include"UMFLoader.h"
#include"OBJLoader.h"
#include"XMesh.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


struct stD3DStaticBuffer
{
   stD3DStaticBuffer() : vbPtr(0), ibPtr(0), numVerts(0),
                         numIndices(0), stride(0), fvf(0),
                         primType(NULL_TYPE) {}

   LPDIRECT3DVERTEXBUFFER9 vbPtr;
   LPDIRECT3DINDEXBUFFER9 ibPtr;
   int numVerts;
   int numIndices;
   int stride;
   unsigned long fvf;
   PrimType primType;
};

struct stD3DTexture
{
   stD3DTexture() : fileName(0), image(0), width(0), height(0) {}

   char *fileName;
   int width, height;
   LPDIRECT3DTEXTURE9 image;
};


class CD3DRenderer : public CRenderInterface
{
   public:
      CD3DRenderer();
      ~CD3DRenderer();
      
      bool Initialize(int w, int h, WinHWND mainWin,
                      bool fullScreen, UGP_MS_TYPE ms);
      void Shutdown();
      
      void SetClearCol(float r, float g, float b);
      void StartRender(bool bColor, bool bDepth, bool bStencil);
      void ClearBuffers(bool bColor, bool bDepth, bool bStencil);
      void EndRendering();

      void SetMaterial(stMaterial *mat);

      void SetLight(stLight *light, int index);
      void DisableLight(int index);

      void SetDepthTesting(RenderState state);
      void SetTransparency(RenderState state, TransState src,
                           TransState dst);

      void EnableFog(float start, float end, UGP_FOG_TYPE type,
                     unsigned long color, bool rangeFog);
      void DisableFog();

      int AddTexture2D(char *file, int *texId);
      void SetTextureFilter(int index, int filter, int val);
      void SetMultiTexture();
      void SetDetailMapping();
      void ApplyTexture(int index, int texId);
      void SaveScreenShot(char *file);

      void EnablePointSprites(float size, float min, float a,
                              float b, float c);
      void DisablePointSprites();

      bool CreateText(char *font, int weight, bool italic,
                      int size, int &id);
      void DisplayText(int id, long x, long y, int r,
                       int g, int b, char *text, ...);
      void DisplayText(int id, long x, long y,
                       unsigned long color, char *text, ...);

      bool AddGUIBackdrop(int guiId, char *fileName);
      bool AddGUIStaticText(int guiId, int id, char *text,
                            int x, int y, unsigned long color,
                            int fontID);
      bool AddGUIButton(int guiId, int id, int x, int y,
                        char *up, char *over, char *down);
      void ProcessGUI(int guiID, bool LMBDown, int mouseX,
                      int mouseY, void(*funcPtr)(int id, int state));

      void CalculateProjMatrix(float fov, float n, float f);
      void CalculateOrthoMatrix(float n, float f);

      int CreateStaticBuffer(VertexType, PrimType,
         int totalVerts, int totalIndices,
         int stride, void **data, unsigned int *indices,
         int *staticId);

      int LoadUMFAsStaticBuffer(char *file, int meshIndex, int *staticID);
      int LoadUMFAsStaticBuffer(char *file, int meshIndex, int staticID);
      int LoadOBJAsStaticBuffer(char *file, int *staticID);
      int LoadOBJAsStaticBuffer(char *file, int staticID);
      int LoadXModel(char *file, int *xModelId);
      int LoadXModel(char *file, int xModelId);

      void ReleaseAllStaticBuffers();
      void ReleaseAllXModels();
      int ReleaseStaticBuffer(int staticID);
      int ReleaseXModel(int xModelId);

      int RenderStaticBuffer(int staticId);
      int RenderXModel(int xModelId);

      void GetXModelBoundingSphere(int xModelId, CVector3 *origin, float *radius)
      {
         if(xModelId < 0 || xModelId >= m_numXModels || !m_xModels)
            return;

         D3DXVECTOR3 center;
         float r;

         m_xModels[xModelId].GetBoundingSphere(&center, &r);

         if(origin)
            {
               origin->x = center.x;
               origin->y = center.y;
               origin->z = center.z;
            }
         
         if(radius)
            *radius = r;
      }
      
      void UpdateXAnimation(int xModelId, float time, CMatrix4x4 *mat)
      {
         if(xModelId < 0 || xModelId >= m_numXModels || !m_xModels)
            return;
        if(!mat) return;

         m_xModels[xModelId].Update(time, (D3DXMATRIX*)&mat->matrix);
      }

      void ApplyView(CVector3 pos, CVector3 view, CVector3 up);
      void SetWorldMatrix(CMatrix4x4 *mat);

      void CameraToViewMatrix(CCamera *cam, CMatrix4x4 *mat);
      void GetProjectionMatrix(CMatrix4x4 *mat);

   private:
      void OneTimeInit();

   
   private:
      D3DCOLOR m_Color;
      LPDIRECT3D9 m_Direct3D;
      LPDIRECT3DDEVICE9 m_Device;
      bool m_renderingScene;

      D3DXMATRIX m_projection;

      LPD3DXFONT *m_fonts;
      // Total fonts in base class.

      stD3DStaticBuffer *m_staticBufferList;
      int m_numStaticBuffers;
      int m_activeStaticBuffer;

      CXModel *m_xModels;
      int m_numXModels;

      stD3DTexture *m_textureList;
      int m_numTextures;
};

bool CreateD3DRenderer(CRenderInterface **pObj);

#endif