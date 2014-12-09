#ifndef PIE_MAIN
#define PIE_MAIN
#include"stdafx.h"
#include"perror.h"
#include"peng.h"
#include<mathutils.h>
using namespace std;
#pragma warning(disable : 4005)
#pragma warning(disable : 4018)
#pragma warning(disable : 4311)
#pragma warning(disable : 4312)
#define MAX_PATH 1024
#define DEFAULT_DEVICE D3DDEVTYPE_HAL
inline DWORD FtoDW( FLOAT f ) { return *((DWORD*)&f); }
//<--------------------------|PIE = probably it's engine|------------------------->
//<-|Lead programmers: DreamCathcer(Denis Rotanov),Ghost Team(Pete Khrapchenkov)|->
//<---------------|Physics, Input, Sound programming:DreamCatcher|---------------->
//<------------------------|Graphic programming:GhostTeam|------------------------>
//<------------------|PIE Engine uses MS DIRECTX, FMOD library|------------------->
//<-------------------------|Compiled with MSVC++ 2003|--------------------------->
//<------------------------------------------------------------------------------->
//<------------------------------------------------------------------------------->
//                                                     
//      ***  *            *   *****                    
//     *   * **   *   ** ***  * * *  *   *** * *       
//     *     * * * * *    *     *   * * *  * ****      
//     * **  * * * * **   *     *   *** *  * * * *     
//     *   * * * * *   *  *     *   *   * ** * * *     
//      ***  * *  *  **   *     *    **  * * * * *     
//                                                     
//# # # # # # # # # # # # # # # # # # # # # # # # # # #
//                                                     
// ***                     **                          
// *  *                   *  *      *      *           
// *  * **  ***  *  * *   *     *  ***  *  **  *** **  
// *  * * * *   * * ****  *    * *  *  * * * * *   * * 
// *  * *** **  *** * * * *    ***  *  *   * * **  *** 
// *  * **  *   * * * * * *  * * *  *  * * * * *   **  
// ***  * * *** * * * * *  **  * *  *   *  * * *** * * 
//-----------------------------------------------------
/*
				 *     *                
           *     *     *                
           *    ***   ***    *          
       *  ***    ¦     ¦ *   *    *     
       *   ¦ *   ¦  *  ¦ *  ****  *     
      ***  ¦ *   ¦  *  ¦***  ¦ * ***    
       ¦   ¦***  ¦ *** ¦ ¦   ¦*** ¦     
       ¦   ¦ ¦   ¦  ¦  ¦ ¦   ¦ ¦  ¦     
       ¦   ¦ ¦   ¦  ¦  ¦ ¦   ¦ ¦  ¦     
       ¦   ¦ ¦   ¦  ¦  ¦ ¦   ¦ ¦  ¦     
       ¦   ¦-¦---¦--¦--¦-¦-  ¦ ¦  ¦     
       ¦---¦ ¦   ¦  ¦  ¦ ¦ --¦-¦  ¦     
    ---¦     ¦      ¦    ¦   ¦ ¦--¦     
   -   ¦     ¦      ¦    ¦     ¦  ¦-    
   -         ¦      ¦    ¦     ¦   -    
   ----      ¦      ¦    ¦     ¦----    
   -   -----        ¦      ---------    
   -        ----------------------------    
   -        --------------------    
   -        ------------------------    
   -        ------------------------    
   -        ------------------------    
    ---     -----------------------     
       -------------------------        
            ---------------             
*//*#ifdef __cplusplus
#define IMPORT extern "C" __declspec (dllimport) 
#else*/
//#define IMPORT _declspec (dllimport)
#define CALL  __stdcall
#define DEFAULT_WND WS_CAPTION|WS_VISIBLE|WS_POPUP|WS_SYSMENU|WS_MINIMIZEBOX//WS_POPUP or WS_VISIBLE or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX
#define DIR3D_WND WS_VISIBLE|WS_POPUP
#define INI_FILE "config.ini"
#define LOG_FILE "system.log"
#define pressed(x)(x>0)
//#endif
/*IMPORT HANDLE PIEOpenFile  (LPCTSTR fname,BOOL Read);
IMPORT BOOL   PIECloseFile (HANDLE file);
IMPORT BOOL   PIEReadFile  (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnor,LPOVERLAPPED lpov);
IMPORT BOOL   PIEWriteFile (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnow,LPOVERLAPPED lpov);
IMPORT DWORD  PIESetOffset (HANDLE file,LONG offset,unsigned short int pos);
IMPORT LONG   PIEFindByte  (HANDLE file,LONG offset,BYTE data);
IMPORT void PIESkipBytes(HANDLE file,DWORD bytes); 
IMPORT char PIEGetVersion();
IMPORT void PIECreateLight(D3DLIGHT9 *Light,D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
										D3DVECTOR Direction,D3DVECTOR Position,float Fallof,float Phi,float Range,
										float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
IMPORT void PIESetLight(LPDIRECT3DDEVICE9 d3dd,D3DLIGHT9 Light,DWORD Index,bool Enabled);
IMPORT void PIETransform(LPDIRECT3DDEVICE9 d3dd,D3DTRANSFORMSTATETYPE t,D3DXMATRIX *Matrix);
IMPORT void PIESetCamera(LPDIRECT3DDEVICE9 d3dd,D3DXVECTOR3 Eye,D3DXVECTOR3 At,D3DXVECTOR3 Up,FLOAT FieldOfView,
									  FLOAT Aspect,FLOAT ZNear,FLOAT ZFar);
IMPORT D3DCOLORVALUE PIEMakeColor(BYTE a,BYTE r,BYTE g,BYTE b);
IMPORT D3DMATERIAL9  PIEMakeMaterial(D3DCOLORVALUE a,D3DCOLORVALUE d,D3DCOLORVALUE s,D3DCOLORVALUE e,FLOAT p);
IMPORT D3DMATERIAL9  PIEReadMaterial(HANDLE file);
IMPORT LPDIRECT3D9 PIECreate3D();
IMPORT BOOL PIEInitDirect3D(HWND hwnd,LPDIRECT3D9 pd3d,LPDIRECT3DDEVICE9 *d3dd,D3DPRESENT_PARAMETERS d3dp,D3DDEVTYPE dt);
IMPORT BOOL PIELoadModel (LPCSTR fname,DWORD ModelKind,BYTE *ModelNumber,
											   DWORD *vnum,DWORD *fnum,D3DMATERIAL9 *mat,char* _tfnames,
											   DWORD *IndexData,LPVOID VertexData);
IMPORT BOOL PIECreateIndexBuffer(LPDIRECT3DDEVICE9 d3dd,DWORD *indices,DWORD fnum,LPDIRECT3DINDEXBUFFER9 ind);
IMPORT BOOL PIECreateVertexBuffer(LPDIRECT3DDEVICE9 d3dd,LPVOID vertices,DWORD vnum,DWORD FVF,DWORD size,LPDIRECT3DVERTEXBUFFER9 vb);
IMPORT void PIESetParams(D3DPRESENT_PARAMETERS *d3dp,HWND hwnd,D3DFORMAT BackBufferFormat,int Width,int Height,int RefreshRate,bool Windowed,
	short int BackBufferCount,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD MultiSamleQuality);*/
/*IMPORT D3DCOLORVALUE				PIEMakeColor(BYTE a,BYTE r,BYTE g,BYTE b);
IMPORT D3DMATERIAL9					PIEMakeMaterial(D3DCOLORVALUE a,D3DCOLORVALUE d,D3DCOLORVALUE s,D3DCOLORVALUE e,FLOAT p);
IMPORT D3DMATERIAL9					PIEReadMaterial(HANDLE file);
IMPORT LPDIRECT3D9					PIECreate3D();
IMPORT BOOL							PIEInitDirect3D(HWND hwnd,LPDIRECT3D9 pd3d,LPDIRECT3DDEVICE9 *d3dd,D3DPRESENT_PARAMETERS d3dp,DWORD vp,D3DDEVTYPE dt);
IMPORT void							PIESetParams(D3DPRESENT_PARAMETERS *d3dp,HWND hwnd,D3DFORMAT BackBufferFormat,int Width,int Height,int RefreshRate,bool Windowed,
									short int BackBufferCount,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD MultiSamleQuality);
IMPORT HWND							PIECreateWindow(HINSTANCE hinst,DWORD Style,DWORD dwStyle,char* ClassName,char* Caption,int X,int Y,int Width,int Height,bool ShowCursor);
IMPORT bool							PIERegisterWNDClass(HINSTANCE hinst,UINT style,WNDPROC WndProc,char* ClassName,HICON Icon);
IMPORT HANDLE						PIEOpenFile  (LPCSTR fname,BOOL Read);
IMPORT BOOL							PIECloseFile (HANDLE file);
IMPORT BOOL							PIEReadFile  (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnor,LPOVERLAPPED lpov);
IMPORT BOOL							PIEWriteFile (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnow,LPOVERLAPPED lpov);
IMPORT DWORD						PIESetOffset (HANDLE file,LONG offset,unsigned short int pos);
IMPORT LONG							PIEFindByte  (HANDLE file,LONG offset,BYTE data);
IMPORT void							PIESkipBytes(HANDLE file,DWORD bytes); 
IMPORT BOOL PIELoadModel (LPCSTR fname,DWORD ModelKind,
											   DWORD *vnum,DWORD *fnum,D3DMATERIAL9 *mat,
											   WORD **IndexData,LPVOID VertexData,
											   Vector3 *Min,Vector3 *Max,
											   FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals);
IMPORT LPDIRECT3DINDEXBUFFER9		PIECreateIndexBuffer(LPDIRECT3DDEVICE9 d3dd,WORD *indices,DWORD fnum,LPDIRECT3DINDEXBUFFER9 ind);
IMPORT LPDIRECT3DVERTEXBUFFER9		PIECreateVertexBuffer(LPDIRECT3DDEVICE9 d3dd,LPVOID vertices,DWORD vnum,DWORD FVF,DWORD size,LPDIRECT3DVERTEXBUFFER9 vb);
IMPORT void							PIECreateLight(D3DLIGHT9 *Light,D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
										D3DVECTOR Direction,D3DVECTOR Position,float Fallof,float Phi,float Range,
										float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
IMPORT void							PIESetLight(LPDIRECT3DDEVICE9 d3dd,D3DLIGHT9 Light,DWORD Index,bool Enabled);
IMPORT void							PIETransform(LPDIRECT3DDEVICE9 d3dd,D3DTRANSFORMSTATETYPE t,D3DXMATRIX *Matrix);
IMPORT void							PIESetCamera(LPDIRECT3DDEVICE9 d3dd,D3DXVECTOR3 Eye,D3DXVECTOR3 At,D3DXVECTOR3 Up,FLOAT FieldOfView,
									  FLOAT Aspect,FLOAT ZNear,FLOAT ZFar);
IMPORT double						_benchmark(void(*pfunc)());
struct TVertex3D
{
	Vector3 p;
	Vector3 n;
	FLOAT tu, tv;
};*/
struct TVertex2D
{
    Vector4		p;
    DWORD       color;
    FLOAT       tu, tv;
};

#define VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define VERTEX2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)
inline bool FileExists(LPCSTR Path)
{
	HANDLE temp=PIEOpenFile(Path,1);
	if (temp==INVALID_HANDLE_VALUE)
		return 0;
	PIECloseFile(temp);
	return 1;
}

#endif PIE_MAIN
