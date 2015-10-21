/*
   Game Name:  Stranded
      Author:  Allen Sherrod
     Chapter:  Chapter 16
*/


#ifndef _UGP_STRUCTS_H_
#define _UGP_STRUCTS_H_


// A structure for our custom vertex type.
struct stGUIVertex
{
    float x, y, z, rhw;
    unsigned long color;
    float tu, tv;
};


// A general structure for our models.
struct stModelVertex
{
    float x, y, z;
    float nx, ny, nz;
    unsigned long color;
    float tu, tv;
};

#endif