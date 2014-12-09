#include"stdafx.h"
#include"matrix.h"
PCamera ccc=NULL;
CCamera::CCamera()
{
	ZeroMemory(this,sizeof(CCamera));
	if (ccc==NULL&&this!=NULL) ccc=this;
}
PCamera GetCurrentCamera()
{
	return ccc;
}
void CCamera::Assign(LPDIRECT3DDEVICE9 _d3dd)
{
	ccc=this;
	PIESetCamera(_d3dd,D3DXVECTOR3(Pos.x,Pos.y,Pos.z),D3DXVECTOR3(At.x,At.y,At.z),D3DXVECTOR3(Up.x,Up.y,Up.z)
		,FOV,Aspect,ZNear,ZFar);
}
void CCamera::Set()
{
	ccc=this;
}