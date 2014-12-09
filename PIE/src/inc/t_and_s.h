#ifndef PIE_TANDS
#define PIE_TANDS
#include"main.h"
#include"files.h"
#include"grtypes.h"


void THAssignDevice(LPDIRECT3DDEVICE9 _d3dd,char *CDir);
LPDIRECT3DDEVICE9	__GetDevice();
typedef enum _TEXTURE_STAGE
{
	TEXTURE_DIFFUSE = 0x0,
	TEXTURE_GLOW	= 0x1,
} TEXTURE_STAGE;
char *GetDir();
DWORD BlendC(DWORD Color1,DWORD Color2,float Val);
class CTexture
{
public:
	CTexture();
	bool						LoadFromFile(LPCSTR Fname);
	void						Release();
	bool						Reset();
	void						SetTexture(DWORD num);
	void						SetStage(D3DTEXTURESTAGESTATETYPE type,DWORD Value);
	bool						Created;
	char						name[32];
	D3DPOOL						Pool;
	DWORD						Usage;
	DWORD						dtNum;
	char						FName[MAX_PATH];
	void						SetNullTexture();
	LPDIRECT3DTEXTURE9			_GetTexture(int ind){ return d3ddt[ind%dtNum];}
protected:
	LPDIRECT3DTEXTURE9			*d3ddt;

	LPDIRECT3DTEXTURE9			_ttext;
};
typedef CTexture *PTexture;
class CSurface
{
public:
	CSurface();
protected:
	LPDIRECT3DSURFACE9			d3ds;
};
class CTiles
{
public:
	CTiles();
	bool LoadFromFile(LPCSTR fname);
};
typedef CSurface *PSurface;
bool _CopyBytes(LPDIRECT3DTEXTURE9 _txt,BYTE* data,DWORD texturew,DWORD textureh,DWORD tilew,DWORD tileh,DWORD tnum);
bool CopyBytes(LPDIRECT3DTEXTURE9 _txt,BYTE* data,DWORD texturew,DWORD textureh,DWORD tilew,DWORD tileh,DWORD tnum);
DWORD Blend(DWORD Color1,DWORD Color2);//Color1 - is the upper
#endif PIE_TANDS