#ifndef PIE_UI
#define PIE_UI
#include"main.h"
#include"font.h"
#include"mesh.h"
class CUI
{
public:
	CUI();
	PFont				Font;
	void				Destroy();
	void				Release();
	bool				Reset();
};
typedef CUI *GUI;
class CImage
{
public:
	void LoadTexture(LPCSTR FName);
protected:
};
#endif PIE_UI