/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef CCAMERA_H
#define CCAMERA_H

#include<math.h>
#include"Vector.h"


class CCamera
{
   public:
      CCamera() {}

      void SetCamera(float x, float y, float z,
                     float xv, float yv, float zv,
                     float xu, float yu, float zu);

      void MoveCamera(float amount);
      void RotateCamera(float angle, float X, float Y, float Z);
	  void CrossCamera(float amount);

      CVector3 m_pos, m_view, m_up;
};

#endif