#ifndef PIE_FONT
#define PIE_FONT
#include"main.h"
#include"mesh.h"
#include"t_and_s.h"
#include"grtypes.h"
#define LetterSpace (float)18/270
//void FAssign(LPDIRECT3DDEVICE9 _d3dd,DWORD w,DWORD h);
class CFont
{
public:
	CFont();
	bool						LoadFont(LPCSTR Fname);
	void						Release();
	bool						Reset();
	void						Destroy();
	FLOAT						Width;
	FLOAT						Height;
	FLOAT						spx,spy;
	bool						Sm;
	DWORD						Color;
	void						PDrawText(DWORD xpos,DWORD ypos,LPCSTR text);
	void						PDrawTextEx(DWORD lx,DWORD ly,DWORD rx,DWORD ry,DWORD Color1,DWORD Color2,GRADIENT type,LPCSTR Text);
	bool						Create(FLOAT _Width,FLOAT _Height,FLOAT _spx,FLOAT _spy,DWORD _Color,LPCSTR Fname,bool Smooth);
protected:
	PRect						rect;
	PTexture					txt;
};
typedef CFont *PFont;

#endif PIE_FONT