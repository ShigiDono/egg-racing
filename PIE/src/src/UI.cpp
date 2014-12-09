#include"stdafx.h"
#include"ui.h"
CUI::CUI()
{
	ZeroMemory(this,sizeof(CUI));
	Font=new CFont;
}
void CUI::Destroy()
{
	Font->Destroy();
	delete Font;
}
void CUI::Release()
{
	Font->Release();
}
bool CUI::Reset()
{
	if (!Font->Reset())
		return 0;
	return 1;
}