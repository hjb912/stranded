

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0497 */
/* Compiler settings for dxgitype.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

/* verify that the <rpcsal.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCSAL_H_VERSION__
#define __REQUIRED_RPCSAL_H_VERSION__ 100
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __dxgitype_h__
#define __dxgitype_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_dxgitype_0000_0000 */
/* [local] */ 

#define _FACDXGI    0x87a
#define MAKE_DXGI_HRESULT( code )    MAKE_HRESULT( 1, _FACDXGI, code )
#define MAKE_DXGI_STATUS( code )    MAKE_HRESULT( 0, _FACDXGI, code )
#define DXGI_STATUS_OCCLUDED                MAKE_DXGI_STATUS(1 )
#define DXGI_STATUS_CLIPPED                 MAKE_DXGI_STATUS(2 )
#define DXGI_STATUS_NO_REDIRECTION          MAKE_DXGI_STATUS(4 )
#define DXGI_STATUS_NO_DESKTOP_ACCESS       MAKE_DXGI_STATUS(5 )
#define DXGI_STATUS_GRAPHICS_VIDPN_SOURCE_IN_USE       MAKE_DXGI_STATUS(6 )
#define DXGI_STATUS_MODE_CHANGED            MAKE_DXGI_STATUS(7 )
#define DXGI_ERROR_INVALID_CALL    MAKE_DXGI_HRESULT( 1 )
#define DXGI_ERROR_NOT_FOUND    MAKE_DXGI_HRESULT( 2 )
#define DXGI_ERROR_MORE_DATA    MAKE_DXGI_HRESULT( 3 )
#define DXGI_ERROR_UNSUPPORTED    MAKE_DXGI_HRESULT( 4 )
#define DXGI_ERROR_DEVICE_REMOVED    MAKE_DXGI_HRESULT( 5 )
#define DXGI_ERROR_DEVICE_HUNG    MAKE_DXGI_HRESULT( 6 )
#define DXGI_ERROR_DEVICE_RESET    MAKE_DXGI_HRESULT( 7 )
#define DXGI_ERROR_WAS_STILL_DRAWING    MAKE_DXGI_HRESULT( 10 )
#define DXGI_ERROR_FRAME_STATISTICS_DISJOINT MAKE_DXGI_HRESULT( 11 )
#define DXGI_ERROR_DRIVER_INTERNAL_ERROR    MAKE_DXGI_HRESULT( 32 )
#define DXGI_ERROR_NONEXCLUSIVE    MAKE_DXGI_HRESULT( 33 )
#define DXGI_FORMAT_DEFINED 1


typedef struct DXGI_RGB
    {
    float Red;
    float Green;
    float Blue;
    } 	DXGI_RGB;

typedef struct DXGI_GAMMA_CONTROL
    {
    DXGI_RGB Scale;
    DXGI_RGB Offset;
    DXGI_RGB GammaCurve[ 1025 ];
    } 	DXGI_GAMMA_CONTROL;

typedef struct DXGI_GAMMA_CONTROL_CAPABILITIES
    {
    BOOL ScaleAndOffsetSupported;
    float MaxConvertedValue;
    float MinConvertedValue;
    UINT NumGammaControlPoints;
    float ControlPointPositions[ 1025 ];
    } 	DXGI_GAMMA_CONTROL_CAPABILITIES;

typedef struct DXGI_RATIONAL
    {
    UINT Numerator;
    UINT Denominator;
    } 	DXGI_RATIONAL;

typedef 
enum DXGI_MODE_SCANLINE_ORDER
    {	DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED	= 0,
	DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE	= 1,
	DXGI_MODE_SCANLINE_ORDER_UPPER_FIELD_FIRST	= 2,
	DXGI_MODE_SCANLINE_ORDER_LOWER_FIELD_FIRST	= 3
    } 	DXGI_MODE_SCANLINE_ORDER;

typedef 
enum DXGI_MODE_SCALING
    {	DXGI_MODE_SCALING_UNSPECIFIED	= 0,
	DXGI_MODE_SCALING_CENTERED	= 1,
	DXGI_MODE_SCALING_STRETCHED	= 2
    } 	DXGI_MODE_SCALING;

typedef 
enum DXGI_MODE_ROTATION
    {	DXGI_MODE_ROTATION_UNSPECIFIED	= 0,
	DXGI_MODE_ROTATION_IDENTITY	= 1,
	DXGI_MODE_ROTATION_ROTATE90	= 2,
	DXGI_MODE_ROTATION_ROTATE180	= 3,
	DXGI_MODE_ROTATION_ROTATE270	= 4
    } 	DXGI_MODE_ROTATION;

typedef struct DXGI_MODE_DESC
    {
    UINT Width;
    UINT Height;
    DXGI_RATIONAL RefreshRate;
    DXGI_FORMAT Format;
    DXGI_MODE_SCANLINE_ORDER ScanlineOrdering;
    DXGI_MODE_SCALING Scaling;
    } 	DXGI_MODE_DESC;

typedef struct DXGI_SAMPLE_DESC
    {
    UINT Count;
    UINT Quality;
    } 	DXGI_SAMPLE_DESC;



extern RPC_IF_HANDLE __MIDL_itf_dxgitype_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_dxgitype_0000_0000_v0_0_s_ifspec;

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


