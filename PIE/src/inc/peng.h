#ifndef PIE_ENGINE__
#define PIE_ENGINE__
#include"stdafx.h"
#include<list>
#include<mathutils.h>
using namespace std;
//definitions
#define MAIN3DS 0x4D4D//Идентификатор *.3DS файла
#define EDIT_3DS 0x3D3D//Блок редактора (this is the start of the editor config)
#define MAIN_3DS 0x4D4D
#define EDIT_OBJECT 0x4000//Объект (сетка, источник света, камера)
//------ sub defines of EDIT_OBJECT
#define OBJ_TRIMESH 0x4100
//------ sub defines of OBJ_TRIMESH
#define TRI_VERTEXLIST 0x4110
#define TRI_VERTEXOPTIONS 0x4111
#define TRI_MAPPINGCOORS 0x4140
#define TRI_MAPPINGSTANDARD 0x4170
#define TRI_FACELIST 0x4120
#define TRI_SMOOTH 0x4150
#define MAT_MAIN 0xAFFF
#define MAT_NAME 0xA000
#define MAT_DIFFUSE 0xA020
#define MAT_AMBIENT 0xA010
#define MAT_SPECULAR 0xA030
#define MAT_SHININESS 0xA040
#define MAT_OPAQUE 0xA050
#define MAT_TEXTURE_NAME 0xA200
#define TRI_LOCAL 0x4160
#define TRI_VISIBLE 0x4165
#define MESH_GTM 0
#define MESH_3DS 1
#define MESH_OBJ 2
#define	DELETE(X){if (X) {delete[] X;X=NULL;}}
#define RELEASE(X){if (X){X->Release();X=NULL;}}
//#define Delete(x) {if (x) {delete[] x;x=NULL;}}

//Files
HANDLE PIEOpenFile  (LPCSTR fname,BOOL Read);
BOOL   PIECloseFile (HANDLE file);
BOOL   PIEReadFile  (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnor,LPOVERLAPPED lpov);
BOOL   PIEWriteFile (HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnow,LPOVERLAPPED lpov);
DWORD  PIESetOffset (HANDLE file,LONG offset,unsigned short int pos);
LONG   PIEFindByte  (HANDLE file,LONG offset,BYTE data);
void PIESkipBytes(HANDLE file,DWORD bytes); 

//funcs ( i dont know why i gave this name to this)))
//D3DCOLORVALUE PIEMakeColor(BYTE a,BYTE r,BYTE g,BYTE b);
//D3DMATERIAL9  PIEMakeMaterial(D3DCOLORVALUE a,D3DCOLORVALUE d,D3DCOLORVALUE s,D3DCOLORVALUE e,FLOAT p);
//D3DMATERIAL9  PIEReadMaterial(HANDLE file);
//LPDIRECT3D9 PIECreate3D();
//BOOL PIEInitDirect3D(HWND hwnd,LPDIRECT3D9 pd3d,LPDIRECT3DDEVICE9 *d3dd,D3DPRESENT_PARAMETERS d3dp,DWORD vp,D3DDEVTYPE dt);
//void PIESetParams(D3DPRESENT_PARAMETERS *d3dp,HWND hwnd,D3DFORMAT BackBufferFormat,int Width,int Height,int RefreshRate,bool Windowed,
//	short int BackBufferCount,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD MultiSamleQuality);
//Ini
bool PIEReadIni(char* section,char* key,char* path,char* result);
bool PIEWriteIni(char* section,char* key,char* path,char* str);
//Light
//void PIECreateLight(D3DLIGHT9 *Light,D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
										//D3DVECTOR Direction,D3DVECTOR Position,float Fallof,float Phi,float Range,
										//float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
//void PIESetLight(LPDIRECT3DDEVICE9 d3dd,D3DLIGHT9 Light,DWORD Index,bool Enabled);
//matrix
//void PIETransform(LPDIRECT3DDEVICE9 d3dd,D3DTRANSFORMSTATETYPE t,D3DXMATRIX *Matrix);
//void PIESetCamera(LPDIRECT3DDEVICE9 d3dd,D3DXVECTOR3 Eye,D3DXVECTOR3 At,D3DXVECTOR3 Up,FLOAT FieldOfView,
//									  FLOAT Aspect,FLOAT ZNear,FLOAT ZFar);
//<--Models-->
struct TVertex3D
{
	Vector3 p;
	Vector3 n;
    GLfloat tu, tv;
};
struct TNode
{
	DWORD fn;
	BYTE vn;
	inline bool operator ==(const TNode a)
	{return (fn==a.fn)&&(vn==a.vn);}
};
struct ToCh
{
	Vector3 Normal;
	DWORD ind;
};
typedef list<TNode> LIT;
typedef list<ToCh> LITC;
struct Header
{
	char Version;
	DWORD vnum[256],fnum[256],totalfnum,totalvnum;
	//D3DMATERIAL9 mat[256];
	BYTE mn;
	char tfname[256];
	BYTE Textured;
};
struct ChunkHeader
{
	WORD ID;
	DWORD Length;
};
/*BOOL PIELoadModel (LPCSTR fname,DWORD ModelKind,
											   DWORD *vnum,DWORD *fnum,D3DMATERIAL9 *mat,
											   WORD **IndexData,LPVOID VertexData,
											   Vector3 *Min,Vector3 *Max,
											   FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals);*/
//LPDIRECT3DINDEXBUFFER9 PIECreateIndexBuffer(LPDIRECT3DDEVICE9 d3dd,WORD *indices,DWORD fnum,LPDIRECT3DINDEXBUFFER9 ind);
//LPDIRECT3DVERTEXBUFFER9 PIECreateVertexBuffer(LPDIRECT3DDEVICE9 d3dd,LPVOID vertices,DWORD vnum,DWORD FVF,DWORD size,LPDIRECT3DVERTEXBUFFER9 vb);
//Windows
//HWND PIECreateWindow(HINSTANCE hinst,DWORD Style,DWORD dwStyle,char* ClassName,char* Caption,int X,int Y,int Width,int Height,bool ShowCursor);
//bool PIERegisterWNDClass(HINSTANCE hinst,UINT style,WNDPROC WndProc,char* ClassName,HICON Icon);
//void D3DMtoM3M(D3DXMATRIX m,Matrix3x3 *res);

#endif PIE_ENGINE__