#ifndef PIE_MATRIX
#define PIE_MATRIX
#include"main.h"
class CCamera
{
public:
	CCamera();
	void SetTarget(Vector3 _at){memcpy(&At,&_at,sizeof(Vector3));}
	void SetUp(Vector3 _up){memcpy(&Up,&_up,sizeof(Vector3));}
	void SetPos(Vector3 _pos){memcpy(&Pos,&_pos,sizeof(Vector3));}
	void SetFA(FLOAT _fov,FLOAT _aspect){
		memcpy(&Aspect,&_aspect,4);
		memcpy(&FOV,&_fov,4);
	}
	void SetCPlanes(FLOAT _znear,FLOAT _zfar){
		memcpy(&ZNear,&_znear,4);
		memcpy(&ZFar,&_zfar,4);
	}
//	void Assign(LPDIRECT3DDEVICE9 _d3dd);
	void Set();
	Vector3 Pos,At,Up;
	FLOAT FOV,Aspect,ZNear,ZFar;
protected:
};
typedef CCamera *PCamera;
PCamera GetCurrentCamera();

#endif PIE_MATRIX