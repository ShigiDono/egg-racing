#include"stdafx.h"
#include"Resources.h"
//LPDIRECT3DDEVICE9 rd3dd=NULL;
char AppPath[MAX_PATH];
CRModel *CM;
bool rGlow=0;
DWORD _sWidth,_sHeight;
CSceneManager *_scm=NULL;
CPSysInfoManager		Presets;
CResourceManager		_rm;
CPSysInfoManager* _Presets(){return &Presets;}
PTexture ldtxt(LPCSTR fname)
{
	_rm.AddResource(RESOURCE_TEXTURE,fname,"smn");
	return ((CRTexture*)_rm.LastCreatedResource)->Texture;
}
bool _LoadPresets(char* fname)
{
	Presets._load=ldtxt;
	return Presets.LoadPresets(fname);
}
void RRelease()
{
	_rm.Destroy();
	Presets.Clear();
}
/*void AssignDevice(LPDIRECT3DDEVICE9 _d3dd,DWORD w,DWORD h,char* CDir)
{
	ZeroMemory(AppPath,MAX_PATH);
	strcpy(AppPath,CDir);
	_sWidth=w;
	_sHeight=h;
	MHAssignDevice(_d3dd,CDir);
	THAssignDevice(_d3dd,CDir);
	FilesAssign(CDir);
	rd3dd=_d3dd;
	FAssign(_d3dd,w,h);
}*/
CRMesh::CRMesh()
{
	Mesh=new CMesh;
//	ZeroMemory(Mesh,sizeof(CMesh));
}
bool  CRMesh::LoadFromFile(LPCSTR FName,LPCSTR rname)
{
	PFile f=new CPFile;
	if (!f->Open(FName,FILE_READ))
		return 0;
	char fname[MAX_PATH];
	ZeroMemory(fname,MAX_PATH);
	float athres,vthres,txtrthres;
	BYTE invnorm,sillumin;
	f->Read(&athres,4);
	f->Read(&vthres,4);
	f->Read(&txtrthres,4);
	f->Read(&invnorm,1);
	f->Read(&sillumin,1);
	int i=0;
	fname[0]=1;
	char c=1;
	while (c!=0)
	{
		f->Read(&c,1);
		fname[i]=c;
		i++;
	}
	if (!Mesh->LoadMesh(fname,athres,vthres,txtrthres,invnorm,sillumin)){
		f->Close();
		return 0;
	}
	strcpy(name,rname);
	f->Close();
	delete f;
	return 1;
}
void  CRMesh::Destroy()
{
	Mesh->Destroy();
	delete Mesh;
}
bool  CRMesh::Reset()
{
	return Mesh->Reset();
}
void  CRMesh::Release()
{
	Mesh->Release();
}
void CRMesh::Draw()
{
	Mesh->Draw();
}
CRTexture::CRTexture()
{
	//ZeroMemory(this,sizeof(CRTexture));
	Texture=new CTexture;
}
bool  CRTexture::LoadFromFile(LPCSTR FName,LPCSTR rname)
{
	if (FName[0]!=0)
		if (!Texture->LoadFromFile(FName))
			return 0;
	strcpy(name,Texture->name);
	return 1;
}
void  CRTexture::Release()
{
	Texture->Release();
}
bool  CRTexture::Reset()
{
	return Texture->Reset();
}
void  CRTexture::Destroy()
{
	Release();
	delete Texture;
}
void CRTexture::Set(DWORD num)
{
	Texture->SetTexture(num);
}
#if 0
void CRTexture::SetState(D3DTEXTURESTAGESTATETYPE type,DWORD Value)
{
	Texture->SetStage(type,Value);
}
#endif
CRModel::CRModel()
{
//	ZeroMemory(this,sizeof(CRModel));
	Scaling=Vector3(1.0f,1.0f,1.0f);
	Rotation=Vector3(0.0f,0.0f,0.0f);
	Translation=Vector3(0.0f,0.0f,0.0f);
	Rot=Vector3(0.0f,0.0f,0.0f);
	this->Texture=NULL;
	Ps=NULL;
	this->Mesh=NULL;
	this->PHmesh=NULL;
	this->rm=NULL;
}
void CRModel::UpdatePS(scalar dt)
{
	PCamera cam=GetCurrentCamera();
	if (Ps == NULL) return;
	SetEmitter(Ps);
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));
/*bool CullBox(Vector3 min, Vector3 max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);*/
	if (Ps->Created==0&&dt!=0)
	{
		Ps->Mi=Translation;
		Ps->Ma=Translation;
//		Ps->Update(dt);
	}
//	else
		if (CullBox(Ps->Mi,Ps->Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,cam->FOV,cam->Aspect,cam->ZNear,cam->ZFar,cam->Pos,cam->At,cam->Up))
		{
			Ps->Update(dt);
		}
}

void CRModel::DrawBMesh(DWORD color)
{
#if 0
	if (PHmesh!=NULL){
	    D3DXMATRIX xx,yy,rx,ry,rz,rx1,ry1,rz1,res,xx1,yy1,rr1,res1;
	    D3DXMatrixTranslation(&xx,Translation.x,Translation.y,Translation.z);
	    D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
	    D3DXMatrixRotationX(&rx,Rotation.x);
	    D3DXMatrixRotationY(&ry,Rotation.y);
	    D3DXMatrixRotationZ(&rz,Rotation.z);
	    D3DXMatrixRotationX(&rx1,Rot.x);
	    D3DXMatrixRotationY(&ry1,Rot.y);
	    D3DXMatrixRotationZ(&rz1,Rot.z);
    //	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
	    D3DXMatrixMultiply(&res,&ry,&ry1);
	    D3DXMatrixMultiply(&res,&res,&rx);
	    D3DXMatrixMultiply(&res,&res,&rx1);
	    D3DXMatrixMultiply(&res,&res,&rz);
	    D3DXMatrixMultiply(&res,&res,&rz1);
	    D3DXMatrixMultiply(&res,&res,&yy);
	    D3DXMatrixMultiply(&res,&res,&xx);



		D3DXMatrixTranslation(&xx1,0,0,0);
		D3DXMatrixScaling(&yy1,1,1,1);
		D3DXMatrixRotationYawPitchRoll(&rr1,0,0,0);
		D3DXMatrixMultiply(&res1,&yy1,&rr1);
		D3DXMatrixMultiply(&res1,&res1,&xx1);
	
		rd3dd->SetTransform(D3DTS_WORLD,&res);
		PHmesh->Mesh->DrawAsLines(color);
		rd3dd->SetTransform(D3DTS_WORLD,&res1);
	}
#endif
}
void CRModel::Draw(DWORD tind)
{
#if 0
//	time1 = timeGetTime();
	PCamera cam=GetCurrentCamera();
//	D3DXMATRIX rx,ry,rz,rx1,ry1,rz1,res,res1,res2,xx,yy,rr1,xx1,yy1;
//	D3DXMatrixTranslation(&xx,Translation.x,Translation.y,Translation.z);
//	D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
/*	D3DXMatrixRotationX(&rx,Rotation.x);
	D3DXMatrixRotationY(&ry,Rotation.y);
	D3DXMatrixRotationZ(&rz,Rotation.z);
	D3DXMatrixRotationX(&rx1,Rot.x);
	D3DXMatrixRotationY(&ry1,Rot.y);
	D3DXMatrixRotationZ(&rz1,Rot.z);
//	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
	D3DXMatrixMultiply(&res,&ry,&ry1);
	D3DXMatrixMultiply(&res,&res,&rx);
	D3DXMatrixMultiply(&res,&res,&rx1);
	D3DXMatrixMultiply(&res,&res,&rz);
	D3DXMatrixMultiply(&res2,&res,&rz1);
	D3DXMatrixMultiply(&res,&res2,&yy);
	D3DXMatrixMultiply(&res,&res,&xx);*/
//	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
//	D3DXMatrixMultiply(&res,&yy,&rx);
//	D3DXMatrixMultiply(&res,&res,&xx);
//	D3DXMatrixMultiply(&res,&res2,&yy);
	D3DXMATRIXA16 rx, ry, rz, tr, sc, res;
	D3DXMatrixRotationX(&rx,Rotation.x);
	D3DXMatrixRotationY(&ry,Rotation.y);
	D3DXMatrixRotationZ(&rz,Rotation.z);
	D3DXMatrixTranslation(&tr,Translation.x,Translation.y,Translation.z);
	D3DXMatrixScaling(&sc,Scaling.x,Scaling.y,Scaling.z);
	D3DXMatrixMultiply(&res,&sc,&tr);
	D3DXMatrixMultiply(&res,&rz,&res);
	D3DXMatrixMultiply(&res,&rx,&res);
	D3DXMatrixMultiply(&res,&ry,&res);

	Matrix3x3 m0;
	D3DMtoM3M(res,&m0);
	Vector3 Mi=Mesh->Mesh->BMin,Ma=Mesh->Mesh->BMax;
	if (!CullBox(Mi,Ma,Translation,Scaling, m0,
		cam->FOV, cam->Aspect, cam->ZNear,cam->ZFar,
		cam->Pos, cam->At, cam->Up))
						return;
/*	Mi.Rotate(Vector3(0,Rot.y,0));
	Mi.Rotate(Vector3(0,Rotation.y,0));
	Mi.Rotate(Vector3(Rot.x,0,0));
	Mi.Rotate(Vector3(Rotation.x,0,0));
	Mi.Rotate(Vector3(0,0,Rot.z));
	Mi.Rotate(Vector3(0,0,Rotation.z));
	Mi.x*=Scaling.x;
	Mi.y*=Scaling.y;
	Mi.z*=Scaling.z;  
	Mi+=Translation;
	Ma.Rotate(Vector3(0,Rot.y,0));
	Ma.Rotate(Vector3(0,Rotation.y,0));
	Ma.Rotate(Vector3(Rot.x,0,0));
	Ma.Rotate(Vector3(Rotation.x,0,0));
	Ma.Rotate(Vector3(0,0,Rot.z));
	Ma.Rotate(Vector3(0,0,Rotation.z));
	Ma.x*=Scaling.x;
	Ma.y*=Scaling.y;
	Ma.z*=Scaling.z;  
	Ma+=Translation;
	DWORD ICl=0xff0000ff;
		DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Mi.x,Mi.y,Ma.z),ICl,ICl);
		DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Mi.x,Ma.y,Mi.z),ICl,ICl);
		DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Ma.x,Mi.y,Mi.z),ICl,ICl);

		DrawLine(Vector3(Ma.x,Ma.y,Ma.z),Vector3(Ma.x,Ma.y,Mi.z),ICl,ICl);
		DrawLine(Vector3(Ma.x,Ma.y,Ma.z),Vector3(Ma.x,Mi.y,Ma.z),ICl,ICl);
		DrawLine(Vector3(Ma.x,Ma.y,Ma.z),Vector3(Mi.x,Ma.y,Ma.z),ICl,ICl);

		DrawLine(Vector3(Ma.x,Mi.y,Ma.z),Vector3(Ma.x,Mi.y,Mi.z),ICl,ICl);
		DrawLine(Vector3(Ma.x,Mi.y,Ma.z),Vector3(Mi.x,Mi.y,Ma.z),ICl,ICl);

		DrawLine(Vector3(Mi.x,Ma.y,Mi.z),Vector3(Mi.x,Ma.y,Ma.z),ICl,ICl);
		DrawLine(Vector3(Mi.x,Ma.y,Mi.z),Vector3(Ma.x,Ma.y,Mi.z),ICl,ICl);

		DrawLine(Vector3(Mi.x,Mi.y,Ma.z),Vector3(Mi.x,Ma.y,Ma.z),ICl,ICl);

		DrawLine(Vector3(Ma.x,Mi.y,Mi.z),Vector3(Ma.x,Ma.y,Mi.z),ICl,ICl);*/
	D3DXMATRIXA16 r, _tr, _sc, res1;
	D3DXMatrixTranslation(&_tr,0,0,0);
	D3DXMatrixScaling(&_sc,1,1,1);
	D3DXMatrixRotationYawPitchRoll(&r,0,0,0);
	D3DXMatrixMultiply(&res1,&_sc,&_tr);
	D3DXMatrixMultiply(&res1,&res1,&r);
	
	rd3dd->SetTransform(D3DTS_WORLD,&res);
	if (Texture)
		Texture->Set(tind);
	else
		rd3dd->SetTexture(0,NULL);
	if (Mesh)
		Mesh->Draw();
	rd3dd->SetTransform(D3DTS_WORLD,&res1);
	rd3dd->SetTexture(0,NULL);
	if (Texture)
		rd3dd->SetTexture(tind,NULL);
#endif
}
Vector3 CRModel::GetVertex(WORD ind)
{
	Vector3 _res=Mesh->Mesh->vertices[ind].p;
#if 0
//	_res.Rotate(Vector3(0,Rot.y,0));
//	_res.Rotate(Vector3(0,0,Rotation.z));
//	_res.Rotate(Vector3(0,Rotation.y,0));
//	_res.Rotate(Vector3(Rotation.x,0,0));

//	_res.Rotate(Vector3(Rot.x,0,0));
//	_res.Rotate(Vector3(0,0,Rot.z));
/*	_res.RotateX(Rotation.x);
	_res.RotateX(Rotation.y);
	_res.RotateX(Rotation.z);*/
	D3DXMATRIXA16 rx, ry, rz, tr, sc, res;
	D3DXMatrixRotationX(&rx,Rotation.x);
	D3DXMatrixRotationY(&ry,Rotation.y);
	D3DXMatrixRotationZ(&rz,Rotation.z);
	D3DXMatrixTranslation(&tr,Translation.x,Translation.y,Translation.z);
	D3DXMatrixScaling(&sc,Scaling.x,Scaling.y,Scaling.z);
	D3DXMatrixMultiply(&res,&sc,&tr);
	D3DXMatrixMultiply(&res,&rz,&res);
	D3DXMatrixMultiply(&res,&rx,&res);
	D3DXMatrixMultiply(&res,&ry,&res);
	D3DXVECTOR3 v3;
	v3.x = _res.x;
	v3.y = _res.y;
	v3.z = _res.z;
	D3DXVECTOR4 out;

	D3DXVec3Transform(&out, &v3, &res);
/*	_res.x*=Scaling.x;
	_res.y*=Scaling.y;
	_res.z*=Scaling.z;  
	_res+=Translation;*/
//	D3DXMATRIX xx,yy,rx,res,xx1,yy1,rx1,res1;
//	D3DXMatrixTranslation(&xx,Translation.x,Translation.y,Translation.z);
//	D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
//	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
//	D3DXMatrixMultiply(&res,&yy,&rx);
//	D3DXMatrixMultiply(&res,&res,&xx);
//	D3DXVECTOR3 v1;
//	v1=D3DXVECTOR3(_res.x,_res.y,_res.z);
//	v1=res*v1;
	_res.x = out.x;
	_res.y = out.y;
	_res.z = out.z;


#endif
	return _res;//Mesh->Mesh->vertices[ind].p;
}
void	CRModel::DrawPS()
{
/*	D3DXMATRIX xx,yy,rx,res,xx1,yy1,rx1,res1;
	D3DXMatrixTranslation(&xx,Translation.x,Translation.y,Translation.z);
	D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
	D3DXMatrixMultiply(&res,&yy,&rx);
	D3DXMatrixMultiply(&res,&res,&xx);
	D3DXMatrixTranslation(&xx1,0,0,0);
	D3DXMatrixScaling(&yy1,1,1,1);
	D3DXMatrixRotationYawPitchRoll(&rx1,0,0,0);
	D3DXMatrixMultiply(&res1,&yy1,&rx1);
	D3DXMatrixMultiply(&res1,&res1,&xx1);
	
	rd3dd->SetTransform(D3DTS_WORLD,&res);*/
	PCamera c=GetCurrentCamera();
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));
/*bool CullBox(Vector3 min, Vector3 max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);*/

//	if (CullBox(Ps->Mi,Ps->Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
//	DrawLine(Ps->Mi, Ps->Mi + Vector3(0, 100, 0.0f) , 0xffff0000, 0xffff0000);
	if (Ps == NULL) 
		return;
//	if (((Vector3)(Ps->Mi - c->Pos)).Length() < c->ZFar)
	if (CullBox(Ps->Mi,Ps->Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
	{
		Ps->Render();
	}
//	rd3dd->SetTransform(D3DTS_WORLD,&res1);
}
bool CRModel::LoadFromFile(LPCSTR FName,LPCSTR rname){
	PFile f=new CPFile;
	if (!f->Open(FName,FILE_READ))
	{
		PutError("Cannot open file %s!",FName);
		f->Close();
		delete f;
		return 0;
	}
	char c=0;
	f->Read(&c,1);
	if (c!='P')
	{
		PutError("Error! File %s has unknown format or damaged!",FName);
		f->Close();
		delete f;
		return 0;
	}
	f->Read(&c,1);
	if (c!='M')
	{
		PutError("Error! File %s has unknown format or damaged!",FName);
		f->Close();
		delete f;
		return 0;
	}
	f->Read(&c,1);
	if (c!='D')
	{
		PutError("Error! File %s has unknown format or damaged!",FName);
		f->Close();
		delete f;
		return 0;
	}
	ZeroMemory(name,sizeof(name));
	ZeroMemory(Fname,sizeof(Fname));
	strcpy(Fname,FName);
	f->ReadNullTerminatedString(name);
	char _name[32],_fn[MAX_PATH],_fn1[MAX_PATH];
	ZeroMemory(_name,sizeof(_name));
	ZeroMemory(_fn,sizeof(_fn));
	ZeroMemory(_fn1,sizeof(_fn1));
	float x,ath,vth,tth;
	byte b;
	f->ReadNullTerminatedString(_name);
	f->ReadNullTerminatedString(_fn);
	f->ReadNullTerminatedString(_fn1);
	CResource *rrr;
	PScene _sc;
	if (rm!=NULL){
//		_sc=(PScene)((CResourceManager*)this->rm)->Scene;
		rrr=((CResourceManager*)rm)->GetResource(RESOURCE_MESH,_name);
	}
	else
		rrr=NULL;

	CRMesh *_m1;
	if (rm!=NULL){
		if (rrr!=NULL)
			_m1=(CRMesh*)rrr;
		else
		{
//			rrr=_sc->ResourceManager.GetResource(RESOURCE_MESH,_fn);
			if (rrr!=NULL)
				_m1=(CRMesh*)rrr;
			else
			{
				((CResourceManager*)rm)->AddResource(RESOURCE_MESH,_name);
				_m1=(CRMesh*)((CResourceManager*)rm)->LastCreatedResource;
			}
		}
	}
	else
	{
		this->Mesh=new CRMesh;
		_m1=this->Mesh;
	}
	f->Read(&b,1);
	if (rrr==NULL)	_m1->Mesh->DrawMesh=b;
	f->Read(&b,1);
	if (rrr==NULL)	_m1->Mesh->CreateBuffers=b;
	f->Read(&ath,4);
	f->Read(&vth,4);
	f->Read(&tth,4);
	f->Read(&b,1);
	if (rrr==NULL){
		if (!_m1->Mesh->LoadMesh(_fn,ath,vth,tth,b,1))
		{
			PutError("An unknown error has occured! File %s has unknown format or damaged!",FName);
			f->Close();
			((CResourceManager*)rm)->RemoveResource(RESOURCE_MESH,_name);
			delete f;
			return 0;
		}
	}
	f->Read(&b,1);
	if (rrr==NULL)	_m1->Mesh->SelfIllumination=b;
	this->Mesh=_m1;
	this->PHmesh=NULL;
	if (strlen(_fn1)!=0)
	{
		rrr=((CResourceManager*)rm)->GetResource(RESOURCE_MESH,_fn1);
		if (rrr!=NULL)
			_m1=(CRMesh*)rrr;
		else
		{
			((CResourceManager*)rm)->AddResource(RESOURCE_MESH,_fn1);
			_m1=(CRMesh*)((CResourceManager*)rm)->LastCreatedResource;
			_m1->Mesh->DrawMesh=0;
			_m1->Mesh->CreateBuffers=0;
			if (!_m1->Mesh->LoadMesh(_fn1,90,0.01,0.001,0,0))
			{
				PutError("An unknown error has occured while loading physical model! File %s has unknown format or damaged!",FName);
				f->Close();
				_sc->ResourceManager.RemoveResource(RESOURCE_MESH,_name);
				_sc->ResourceManager.RemoveResource(RESOURCE_MESH,_fn1);
				delete f;
				return 0;
			}
		}
		this->PHmesh=_m1;

	}
	else
		this->PHmesh=NULL;
	f->Read(&b,1);
	CRTexture *txtr;
	if (!b)
		this->Texture=NULL;
	else
	{
		ZeroMemory(_name,sizeof(_name));
		ZeroMemory(_fn,sizeof(_fn));
		f->ReadNullTerminatedString(_name);
		f->ReadNullTerminatedString(_fn);
		rrr=((CResourceManager*)rm)->GetResource(RESOURCE_TEXTURE,_name);
		if (rrr!=NULL)
			txtr=(CRTexture*)rrr;
		else
		{
			rrr=((CResourceManager*)rm)->GetResource(RESOURCE_TEXTURE,_fn);
			if (rrr!=NULL)
				txtr=(CRTexture*)rrr;
			else
			{
				((CResourceManager*)rm)->AddResource(RESOURCE_TEXTURE,_name);
				txtr=(CRTexture*)((CResourceManager*)rm)->LastCreatedResource;
				txtr->LoadFromFile(_fn,_name);
			}
		}
	}
			this->Texture=txtr;
	char psp[100];
	ZeroMemory(psp,sizeof(psp));
	f->ReadNullTerminatedString(psp);
	((CResourceManager*)rm)->psm.Presets=_Presets();
	if (strlen(psp)>0){
		((CResourceManager*)rm)->psm.NewParticleSystem("ps",psp);
		Ps=((CResourceManager*)rm)->psm.LastCreatedPS;
		this->SetEmitter(Ps);
	}


	f->Close();
	delete f;
	return 1;
}
void CRModel::DrawEx(DWORD tind,Vector3 pos)
{
#if 0
    D3DXMATRIX res,res1;
	D3DXMatrixTranslation(&res,pos.x,pos.y,pos.z);
//	D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
//	D3DXMatrixRotationYawPitchRoll(&rx,Rotation.y,Rotation.x,Rotation.z);
//	D3DXMatrixMultiply(&res,&yy,&rx);
//	D3DXMatrixMultiply(&res,&res,&xx);
	D3DXMatrixTranslation(&res1,0,0,0);
//	D3DXMatrixScaling(&yy1,1,1,1);
//	D3DXMatrixRotationYawPitchRoll(&rx1,0,0,0);
//	D3DXMatrixMultiply(&res1,&yy1,&rx1);
//	D3DXMatrixMultiply(&res1,&res1,&xx1);
	rd3dd->SetTransform(D3DTS_WORLD,&res);
	if (Texture)
		Texture->Set(tind);
	if (Mesh)
		Mesh->Draw();
	rd3dd->SetTransform(D3DTS_WORLD,&res1);
	rd3dd->SetTexture(0,NULL);
#endif
}
void CRModel::DrawExx(DWORD tind,Vector3 pos,Vector3 rot)
{
#if 0
	D3DXMATRIX xx,rx,res,xx1,rx1,res1;
	D3DXMatrixTranslation(&xx,pos.x,pos.y,pos.z);
//	D3DXMatrixScaling(&yy,Scaling.x,Scaling.y,Scaling.z);
	D3DXMatrixRotationYawPitchRoll(&rx,rot.y,rot.x,rot.z);
	D3DXMatrixMultiply(&res,&xx,&rx);
//	D3DXMatrixMultiply(&res,&res,&xx);
	D3DXMatrixTranslation(&xx1,0,0,0);
//	D3DXMatrixScaling(&yy1,1,1,1);
	D3DXMatrixRotationYawPitchRoll(&rx1,0,0,0);
	D3DXMatrixMultiply(&res1,&xx1,&rx1);
//	D3DXMatrixMultiply(&res1,&res1,&xx1);
	rd3dd->SetTransform(D3DTS_WORLD,&res);
	if (Texture)
		Texture->Set(tind);
	if (Mesh)
		Mesh->Draw();
	rd3dd->SetTransform(D3DTS_WORLD,&res1);
	rd3dd->SetTexture(0,NULL);
#endif
}
/*CRParticleSystem::CRParticleSystem()
{
//	ZeroMemory(this,sizeof(CRParticleSystem));
	ParticleSystem=new CDParticleSystem;
}
bool  CRParticleSystem::LoadFromFile(LPCSTR FName,LPCSTR rname)
{
	char temp[MAX_PATH];
	ZeroMemory(temp,MAX_PATH);
	strcpy(temp,AppPath);
	strcat(temp,FName);
	if (!FileExists(temp))
		return 0;
	ParticleSystem->ReadFromFile(temp);
	strcpy(name,rname);
	return 1;
}*/
Vector3 Getvertex(WORD ind)
{
	return CM->GetVertex(ind);
}
WORD Getindex(WORD ind)
{
	return CM->GetIndex(ind);
}
void CRModel::SetEmitter(PDParticleSystem ps){
	CM=this;
	ps->emitter.getindex=Getindex;
	ps->emitter.getvertex=Getvertex;
	ps->emitter.fnum=this->Mesh->Mesh->fnum;
	ps->emitter.vnum=this->Mesh->Mesh->vnum;

}
/*void CRParticleSystem::AssignEmitter(CRModel *_emitter)
{
	ParticleSystem->SetEmitter(_emitter->GetVnum(),_emitter->GetFnum(),Getvertex,Getindex);
	Emitter=_emitter;
}
void  CRParticleSystem::Destroy()
{
	delete ParticleSystem;
}
void CRParticleSystem::Draw()
{
	if (Texture->Texture->dtNum>1)
		Texture->Set(0);//ParticleSystem->info);
	ParticleSystem->Render();
}
void CRParticleSystem::Update(FLOAT dt)
{
	CM=Emitter;
	ParticleSystem->Update(dt);
}*/
CResourceManager::CResourceManager()
{
	psm.Presets=&Presets;
	this->MeshesCount=0;
	this->ModelsCount=0;
	this->TexturesCount=0;
	this->psm.Presets=_Presets();
	ZeroMemory(this,sizeof(CResourceManager));
}
bool CResourceManager::AddResource(RESOURCE_TYPE type,LPCSTR fname,LPCSTR name)
{
	bool b=0;
	int j=0;
	WriteMsg("-->Loading resource %d '%s' as '%s'.",type,fname,name);
	AddTab();
	switch (type)
	{
		case RESOURCE_MESH:
			//Mesh loading
			Meshes[MeshesCount]=new CRMesh;
			Meshes[MeshesCount]->rm=(DWORD)this;
			if (!Meshes[MeshesCount]->LoadFromFile(fname,name)){
				RemTab();
				delete Meshes[MeshesCount];
				return 0;
			}
			LastCreatedResource=Meshes[MeshesCount];
			MeshesCount++;
			break;
		case RESOURCE_MODEL:
			//Model
			Models[ModelsCount]=new CRModel;
			Models[ModelsCount]->rm=(DWORD)this;
			if (!Models[ModelsCount]->LoadFromFile(fname,NULL)){
				RemTab();
				delete Models[ModelsCount];
				return 0;
			}
/*			char mname[32];
			char tname[32];
			ZeroMemory(mname,32);
			ZeroMemory(tname,32);
			for (int i=0;i<strlen(fname);i++)
			{
				if (fname[i]=='|')
				{
					b=1;
					j=0;
				}
				else
					if (b){
						tname[j]=fname[i];
						j++;
					}
					else
					{
						mname[i]=fname[i];
					}
			}
			Models[ModelsCount]->Mesh=(CRMesh*)GetResource(RESOURCE_MESH,mname);
			Models[ModelsCount]->Texture=(CRTexture*)GetResource(RESOURCE_TEXTURE,tname);*/
			LastCreatedResource=Models[ModelsCount];
			ModelsCount++;
			break;
		case RESOURCE_TEXTURE:
			//texture
			Textures[TexturesCount]=new CRTexture;
			Textures[TexturesCount]->rm=(DWORD)this;
			if (!Textures[TexturesCount]->LoadFromFile(fname,name)){
				delete Textures[TexturesCount];
				RemTab();
				return 0;
			}
			LastCreatedResource=Textures[TexturesCount];
			TexturesCount++;
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			ParticleSystems[ParticleSystemsCount]=new CRParticleSystem;
			if (!ParticleSystems[ParticleSystemsCount]->LoadFromFile(fname,name))
			{
				delete ParticleSystems[ParticleSystemsCount];
				return 0;
			}
			ParticleSystemsCount++;
			break;*/
	}
	RemTab();

	WriteMsg("-->Success.");
	return 1;
}
void CResourceManager::AddResource(RESOURCE_TYPE type,CResource *resource)
{
	WriteMsg("-->Adding resource %d with adress %d.",type,resource);
	switch(type)
	{
		case RESOURCE_MESH:
			Meshes[MeshesCount]=(CRMesh*)resource;
			LastCreatedResource=Meshes[MeshesCount];
			MeshesCount++;
			break;
		case RESOURCE_MODEL:
			Models[ModelsCount]=(CRModel*)resource;
			LastCreatedResource=Models[ModelsCount];
			ModelsCount++;
			break;
		case RESOURCE_TEXTURE:
			Textures[TexturesCount]=(CRTexture*)resource;
			LastCreatedResource=Textures[TexturesCount];
			TexturesCount++;
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			ParticleSystems[ParticleSystemsCount]=(CRParticleSystem*)resource;
			ParticleSystemsCount++;
			break;*/
	}
	LastCreatedResource->rm=(DWORD)this;
	WriteMsg("-->Success.");
}
void CResourceManager::AddResource(RESOURCE_TYPE type,LPCSTR name)
{
	WriteMsg("-->Adding resource %d with name '%s'.",type,name);
	switch (type)
	{
		case RESOURCE_MESH:
			//Mesh loading
			Meshes[MeshesCount]=new CRMesh;
			strcpy(Meshes[MeshesCount]->name,name);
			LastCreatedResource=Meshes[MeshesCount];
			MeshesCount++;
			break;
		case RESOURCE_MODEL:
			//Model
			Models[ModelsCount]=new CRModel;
//			strcpy(Models[ModelsCount]->name,name);
			LastCreatedResource=Models[ModelsCount];
			ModelsCount++;
			break;
		case RESOURCE_TEXTURE:
			//texture
			Textures[TexturesCount]=new CRTexture;
//			strcpy(Textures[TexturesCount]->name,name);
			LastCreatedResource=Textures[TexturesCount];
			TexturesCount++;
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			ParticleSystems[ParticleSystemsCount]=new CRParticleSystem;
			strcpy(ParticleSystems[ParticleSystemsCount]->name,name);
			ParticleSystemsCount++;
			break;*/
	}
	LastCreatedResource->rm=(DWORD)this;
	WriteMsg("-->Success.");
}
CResource * CResourceManager::GetResource(RESOURCE_TYPE type,LPCSTR name)
{
	switch(type)
	{
		case RESOURCE_MESH:
			for (WORD i=0;i<MeshesCount;i++)
			{
				if (Meshes[i])
				{
					if (strcmp(name,Meshes[i]->name)==0)
						return Meshes[i];
					if (strcmp(name,Meshes[i]->Mesh->__fname)==0)
						return Meshes[i];
				}
			}
			break;
		case RESOURCE_MODEL:
			for (WORD i=0;i<ModelsCount;i++)
			{
				if (Models[i])
				{
					if (strcmp(name,Models[i]->name)==0)
						return Models[i];
					if (strcmp(name,Models[i]->Fname)==0)
						return Models[i];
				}
			}
			break;
		case RESOURCE_TEXTURE:
			for (WORD i=0;i<TexturesCount;i++)
			{
				if (Textures[i])
				{
					if (strcmp(name,Textures[i]->Texture->name)==0)
						return Textures[i];
					if (strcmp(name,Textures[i]->Texture->FName)==0)
						return Textures[i];
				}
			}
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			for (WORD i=0;i<ParticleSystemsCount;i++)
			{
				if (ParticleSystems[i])
				{
					if (strcmp(name,ParticleSystems[i]->name)==0)
						return ParticleSystems[i];
				}
			}
			break;*/
	}
	return NULL;
}
CResource *CResourceManager::GetResource(RESOURCE_TYPE type,WORD index)
{
	switch (type)
	{
		case RESOURCE_MESH:
			return Meshes[index];
		case RESOURCE_MODEL:
			return Models[index];
		case RESOURCE_TEXTURE:
			return Textures[index];
/*		case RESOURCE_PARTICLESYSTEM:
			return ParticleSystems[index];*/
	}
	return NULL;
}
void CResourceManager::RemoveResource(RESOURCE_TYPE type,LPCSTR name)
{
	WORD i=0;
	switch (type)
	{
		case RESOURCE_MESH:
			if (MeshesCount==0)
				return;
			while (strcmp(Meshes[i]->name,name)!=0)
			{
				i++;
				if (i==MeshesCount)
					return;
			}
			swap(Meshes[i],Meshes[MeshesCount-1]);
			Meshes[MeshesCount-1]->Destroy();
			delete Meshes[MeshesCount-1];
			Meshes[MeshesCount-1]=NULL;
			MeshesCount--;
			break;
		case RESOURCE_MODEL:
			if (ModelsCount==0)
				return;
			while (strcmp(Models[i]->name,name)!=0)
			{
				i++;
				if (i==ModelsCount)
					return;
			}
			swap(Models[i],Models[ModelsCount-1]);
			Models[ModelsCount-1]->Destroy();
			delete Models[ModelsCount-1];
			Models[ModelsCount-1]=NULL;
			ModelsCount--;
			break;
		case RESOURCE_TEXTURE:
			if (TexturesCount==0)
				return;
			while (strcmp(Textures[i]->name,name)!=0)
			{
				i++;
				if (i==TexturesCount)
					return;
			}
			swap(Textures[i],Textures[TexturesCount-1]);
			Textures[TexturesCount-1]->Destroy();
			delete Textures[TexturesCount-1];
			Textures[TexturesCount-1]=NULL;
			TexturesCount--;
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			if (ParticleSystemsCount==0)
				return;
			while (strcmp(ParticleSystems[i]->name,name)!=0)
			{
				i++;
				if (i==ParticleSystemsCount)
					return;
			}
			swap(ParticleSystems[i],ParticleSystems[ParticleSystemsCount-1]);
			ParticleSystems[ParticleSystemsCount-1]->Destroy();
			delete ParticleSystems[ParticleSystemsCount-1];
			ParticleSystems[ParticleSystemsCount-1]=NULL;
			ParticleSystemsCount--;
			break;*/
	}
}
void CResourceManager::RemoveResource(RESOURCE_TYPE type,WORD index)
{
	switch (type)
	{
		case RESOURCE_MESH:
			if (MeshesCount==0)
				return;
			if (index!=MeshesCount-1)
				swap(Meshes[index],Meshes[MeshesCount-1]);
			Meshes[MeshesCount-1]->Destroy();
			delete Meshes[MeshesCount-1];
			Meshes[MeshesCount-1]=NULL;
			MeshesCount--;
			break;
		case RESOURCE_MODEL:
			if (ModelsCount==0)
				return;
			if (index!=ModelsCount-1)
				swap(Models[index],Models[ModelsCount-1]);
			Models[ModelsCount-1]->Destroy();
			delete Models[ModelsCount-1];
			Models[ModelsCount-1]=NULL;
			ModelsCount--;
			break;
		case RESOURCE_TEXTURE:
			if (TexturesCount==0)
				return;
			if (index!=TexturesCount-1)
				swap(Textures[index],Textures[TexturesCount-1]);
			Textures[TexturesCount-1]->Destroy();
			delete Textures[TexturesCount-1];
			Textures[TexturesCount-1]=NULL;
			TexturesCount--;
			break;
/*		case RESOURCE_PARTICLESYSTEM:
			if (ParticleSystemsCount==0)
				return;
			if (index!=ParticleSystemsCount-1)
				swap(ParticleSystems[index],ParticleSystems[ParticleSystemsCount-1]);
			ParticleSystems[ParticleSystemsCount-1]->Destroy();
			delete ParticleSystems[ParticleSystemsCount-1];
			ParticleSystems[ParticleSystemsCount-1]=NULL;
			ParticleSystemsCount--;
			break;*/
	}
}
void CResourceManager::Release()
{
	for (WORD i=0;i<MeshesCount;i++)
	{
		Meshes[i]->Release();
	}
	for (WORD i=0;i<ModelsCount;i++)
	{
		Models[i]->Release();
	}
	for (WORD i=0;i<TexturesCount;i++)
	{
		Textures[i]->Release();
	}
/*	for (WORD i=0;i<ParticleSystemsCount;i++)
	{
		ParticleSystems[i]->Release();
	}*/
}
bool CResourceManager::Reset()
{
	for (WORD i=0;i<MeshesCount;i++)
	{
		if (Meshes[i]!=NULL)
			if (!Meshes[i]->Reset())
				return 0;
	}
	for (WORD i=0;i<ModelsCount;i++)
	{
		if (Models[i]!=NULL)
			if (!Models[i]->Reset())
				return 0;
	}
	for (WORD i=0;i<TexturesCount;i++)
	{
		if (Textures[i]!=NULL)
			if (!Textures[i]->Reset())
				return 0;
	}
/*	for (WORD i=0;i<ParticleSystemsCount;i++)
	{
		if (!ParticleSystems[i]->Reset())
			return 0;
	}*/
	return 1;
}
void CResourceManager::Destroy()
{
	while (MeshesCount!=0)
		RemoveResource(RESOURCE_MESH,MeshesCount-1);
	while (ModelsCount!=0)
		RemoveResource(RESOURCE_MODEL,ModelsCount-1);
	while (TexturesCount!=0)
		RemoveResource(RESOURCE_TEXTURE,TexturesCount-1);
	psm.Clear();
/*	while (ParticleSystemsCount!=0)
		RemoveResource(RESOURCE_PARTICLESYSTEM,ParticleSystemsCount-1);*/
}
CScene::CScene()
{
	ZeroMemory(this,sizeof(CScene));
	this->ResourceManager.Scene=(DWORD)this;
}

PTexture GetPSTexture(LPCSTR name)
{
	CRTexture* txt=((CRTexture*)_scm->rm.GetResource(RESOURCE_TEXTURE,name));
	if (txt==NULL)
	{
/*		PFile f=new CPFile;
		//if file doesn't exist trying to find file with same texture name and load it;
		delete f;*/
		_scm->rm.AddResource(RESOURCE_TEXTURE,name,"n");
		txt=(CRTexture*)_scm->rm.LastCreatedResource;
	}
	return txt->Texture;
}
void CScene::Render()
{
#if 0
	if (Camera)
		Camera->Assign(rd3dd);
#endif
	if (Draw)
		(Draw)((DWORD)this);
}
void CScene::Update(FLOAT dt)
{
	if (Step)
		(Step)((DWORD)this,dt);
}
/*void CScene::Draw()
{
	//user draw func
	//UI draw func:)
}*/
bool CScene::LoadFromFile(LPCSTR FName)
{
	char temp[MAX_PATH];
	ZeroMemory(temp,MAX_PATH);
	strcpy(temp,AppPath);
	strcat(temp,FName);
	if (!FileExists(temp))
		return 0;
	return 1;
}
void CScene::Destroy()
{
	ResourceManager.Destroy();
}
void CScene::Release()
{
	ResourceManager.Release();
}
bool CScene::Reset()
{
	return ResourceManager.Reset();
}
CSceneManager::CSceneManager()
{
	ZeroMemory(this,sizeof(CSceneManager));
	UI=new CUI;
	SRect=new CPRect;
	SRect->SetColor(0,0xFFFFFFFF);
	SRect->SetColor(1,0xFFFFFFFF);
	SRect->SetColor(2,0xFFFFFFFF);
	SRect->SetColor(3,0xFFFFFFFF);
	SRect->SetTCoord(0,0,0);
	SRect->SetTCoord(1,0,1);
	SRect->SetTCoord(2,1,0);
	SRect->SetTCoord(3,1,1);
	_scm=this;
}
void CSceneManager::NewScene(LPCSTR name)
{
	Scenes[ScenesCount]=new CScene;
	if (CurrentScene==NULL) CurrentScene=Scenes[ScenesCount];
	strcpy(Scenes[ScenesCount]->name,name);
	ScenesCount++;
}
bool CSceneManager::NewSceneFromFile(LPCSTR FName,LPCSTR name)
{
	NewScene(name);
	if (!Scenes[ScenesCount-1]->LoadFromFile(FName)){
        RemoveScene(ScenesCount-1);
		return 0;
	}
	return 1;
}
void CSceneManager::RemoveScene(WORD index)
{
	if (ScenesCount==0)
		return;
	if (index!=ScenesCount-1)
		swap(Scenes[index],Scenes[ScenesCount-1]);
	Scenes[ScenesCount-1]->Destroy();
	delete Scenes[ScenesCount-1];
	Scenes[ScenesCount-1]=NULL;
	ScenesCount--;
}
void CSceneManager::RemoveSceneEx(LPCSTR name)
{
	for (WORD i=0;i<ScenesCount;i++)
	{
		if (strcmp(name,Scenes[i]->name)==0)
			RemoveScene(i);
	}
}
PScene CSceneManager::GetScene(WORD index)
{
	return Scenes[index];
}
PScene CSceneManager::GetSceneEx(LPCSTR name)
{
	for (WORD i=0;i<ScenesCount;i++)
	{
		if (strcmp(name,Scenes[i]->name)==0)
			return Scenes[i];
	}
	return NULL;
}
void CSceneManager::Clear()
{
	while (ScenesCount!=0)
		RemoveScene(0);
}
void CSceneManager::Release()
{
    for (WORD i=0;i<ScenesCount;i++)
	{
		Scenes[i]->Release();
	}
	UI->Release();
/*	GlowTexture->Release();
	_GlowTexture->Release();
	_GlowTexture=NULL;
	__GlowTexture->Release();
	__GlowTexture=NULL;
	RELEASE(GMap);
	GMap=NULL;
	GlowTexture=NULL;*/

}
bool CSceneManager::Reset()
{
//	GlowTexture
	DELETE(_f);
	_f=new CFilter;
	(*_f)+=(float)1/25;
/*	if (FAILED(D3DXCreateTexture(rd3dd,_sWidth/8,_sHeight/8,1, D3DUSAGE_RENDERTARGET, D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT/*DEFAULT*, &_GlowTexture)))
		return 0;
	if (FAILED(D3DXCreateTexture(rd3dd,_sWidth/8,_sHeight/8,1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &GlowTexture)))
		return 0;
	if (FAILED(D3DXCreateTexture(rd3dd,_sWidth/8,_sHeight/8,1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &__GlowTexture)))
		return 0;*/
/*	if (FAILED(rd3dd->CreateOffscreenPlainSurface(_sWidth/8,_sHeight/8,D3DFMT_A8R8G8B8,D3DPOOL_DEFAULT,&GMap,NULL)))
		return 0;*/
    for (WORD i=0;i<ScenesCount;i++)
	{
		if (Scenes[i]!=NULL)
			if (!Scenes[i]->Reset())
				return 0;
	}
	if (SRect==NULL)
	{
		SRect=new CPRect;
		SRect->SetColor(0,0xFFFFFFFF);
		SRect->SetColor(1,0xFFFFFFFF);
		SRect->SetColor(2,0xFFFFFFFF);
		SRect->SetColor(3,0xFFFFFFFF);
		SRect->SetTCoord(0,0,0);
		SRect->SetTCoord(1,0,1);
		SRect->SetTCoord(2,1,0);
		SRect->SetTCoord(3,1,1);
	}
	SRect->SetPos(0,Vector3(0,0,0));
	SRect->SetPos(1,Vector3(0,_sHeight,0));
	SRect->SetPos(2,Vector3(_sWidth,0,0));
	SRect->SetPos(3,Vector3(_sWidth,_sHeight,0));
	UI->Reset();
	return 1;
}
void CSceneManager::Update(FLOAT dt)
{
	if (CurrentScene==NULL)
		CurrentScene=Scenes[0];
	if (CurrentScene==NULL)
		return;
	CurrentScene->Update(dt);
}
void CSceneManager::Draw()
{
	if (CurrentScene==NULL)
		CurrentScene=Scenes[0];
	if (CurrentScene==NULL)
		return;
/*	D3DVIEWPORT9 vp;
		D3DVIEWPORT9 vp1;
	rd3dd->GetViewport(&vp);

/*	if (GlowEnable)
	{

		vp1=vp;
		vp1.Width/=8;
		vp1.Height/=8;
		LPDIRECT3DSURFACE9 ot,nt;
		//,nt;
		if (FAILED(_GlowTexture->GetSurfaceLevel(0,&nt)))
			return;
//		rd3dd->SetViewport(&vp);
		rd3dd->GetRenderTarget(0,&ot);
//		rd3dd->SetRenderTarget(0,nt);
//		rd3dd->SetViewport(&vp);
		rd3dd->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                       0xFF000000, 1.0f, 0L );
		rGlow=1;
		rd3dd->SetRenderState(D3DRS_LIGHTING,		   0);
		CurrentScene->Render();
//		RECT r1,r2;
/*		r1.left=r2.left=0;
		r1.top=r2.top=0;
		r1.bottom=vp.Height-1;
		r2.bottom=vp.Height/8-1;
		r1.right=vp.Width-1;
		r2.right=vp.Width/8-1;
		rd3dd->StretchRect(ot,NULL,nt,NULL,D3DTEXF_LINEAR);
//		rd3dd->StretchRect(ot,NULL,GMap,NULL,D3DTEXF_LINEAR);
//		D3DLOCKED_RECT lr1,lr2;
//		rd3dd->UpdateSurface(nt,NULL,GMap,NULL);
//		if (FAILED(GlowTexture->GetSurfaceLevel(0,&nt1)))
//			return;
//		nt->LockRect(&lr1,NULL,D3DLOCK_READONLY);
//		rd3dd->UpdateTexture(_GlowTexture,__GlowTexture);
		//_GlowTexture->LockRect(0,&lr1,NULL,D3DLOCK_READONLY);
//		GMap->LockRect(&lr1,NULL,D3DLOCK_READONLY);
//		nt1->LockRect(&lr2,NULL,D3DLOCK_DISCARD);
//		_GlowTexture->LockRect(0,&lr1,0,0);
//		GlowTexture->LockRect(0,&lr2,NULL,D3DLOCK_DISCARD);
//		_f->ApplyEffect((BYTE*)lr1.pBits,(BYTE*)lr2.pBits,_sWidth/8,_sHeight/8);
//		memcpy(lr2.pBits,lr1.pBits,_sWidth*_sHeight/16);
		//GlowTexture->UnlockRect(0);
//		GlowTexture->UnlockRect(0);
//		_GlowTexture->UnlockRect();
//		nt1->UnlockRect();
//		GMap->UnlockRect();
//		nt->UnlockRect();
//		rd3dd->EndScene();
//		HRESULT xxx=rd3dd->Present(NULL,NULL,NULL,NULL);
//		rd3dd->BeginScene();
//		rd3dd->SetRenderTarget(0,ot);
	}
	rGlow=0;
	rd3dd->Clear( 0L, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,
                       0x00000000, 1.0f, 0L );
//		rd3dd->SetViewport(&vp);*/
	CurrentScene->Render();
/*	if (GlowEnable)
	{
		rd3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE);
		rd3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_ONE );
		rd3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_ONE );

		rd3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
		rd3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
		rd3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
		rd3dd->SetTexture(0,_GlowTexture);
		SRect->Update();
		SRect->Draw();
		rd3dd->SetTexture(0,NULL);

		rd3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
		rd3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
	}*/
}
void CSceneManager::Destroy()
{
	Clear();
//	GlowTexture->Release();
	UI->Destroy();
	rm.Destroy();
	Presets.Clear();
	delete SRect;
	delete UI;
}
