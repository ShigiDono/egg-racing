#include"stdafx.h"
#include"terrain.h"
float Blend(float x,float y,float k)
{
  return (float)x*(1-k)+(float)k*y;
}
/*class CHeightMap
{
public:
	CHeightMap();
	void				CreateHeightMap(WORD w,WORD h);
	void				LoadHeightMap(PFile f);
	void				GenerateNormals();
	void				LightIt(Vector3 LD);
	BYTE				*HMap;
	Vector3				*Normals;
	Vector3				*FaceNormals;
	DWORD				*ColorMap;
	DWORD				Ambient;
	DWORD				Diffuse;
	WORD				Width,Height; 
	void				Release(){
		DELETE(Normals);
		DELETE(FaceNormals);
		DELETE(HMap);
		DELETE(ColorMap);
	}
};
typedef	CHeightMap *PHeightMap;
class	CTile
{
public:
	CTile();
    void						Draw();
	void						Create();
	Vector3						Mi,Ma;
	LPDIRECT3DVERTEXBUFFER9		buff;
	int							xt,yt;
	PHeightMap					HMap;
	void						Release(){buff->Release();}
};
typedef CTile *PTile;
class CTerrain
{
public:
	CTerrain();
	void						Load(PFile	f);
    PHeightMap					HMap;
	PTile						Tiles;
private:
};
typedef CTerrain* PTerrain;
*/
CPTile::CPTile()
{
	this->buff=NULL;
	this->HMap=NULL;
	this->Ma=Vector3(0,0,0);
	this->Mi=Vector3(0,0,0);
	this->xt=0;
	this->yt=0;
}
CHeightMap::CHeightMap()
{
//	this->Texture=NULL;
	this->Ambient=0xff000000;
	this->ColorMap=NULL;
	this->Diffuse=0xffffffff;
	this->FaceNormals=NULL;
	this->Height=0;
	this->HMap=NULL;
	this->Normals=NULL;
	this->HScale=2;
	this->VScale=0.1;
	this->Width=0;
	this->LightVector=Vector3(-1,-1,-1);
	this->LightVector.Normalise();
}
float				CHeightMap::GetHeightValue(float x,float z)
{
float xx=x,zz=z;
	int _x=x/HScale,_z=z/HScale;
	xxx=_x;
	zzz=_z;
	if (_x<0) _x=0;
	if (_z<0) _z=0;
	if (_x>=Width)		_x=Width-1;
	if (_z>=Height)		_z=Height-1;
	float x1=(float)_x*HScale;
/*	float z1=(float)(_z+1)*HScale;
	float x2=(float)(_x+1)*HScale;*/
	float z1=(float)_z*HScale;
	xx-=x1;
	zz-=z1;
	if (xx<0) xx=0;
	if (zz<0) zz=0;
	while (xx>HScale) xx-=HScale;
	while (zz>HScale) zz-=HScale;
/*	float d1=(x-x1)*(x-x1)+(z-z1)*(z-z1);
	float d2=(x-x2)*(x-x2)+(z-z2)*(z-z2);*/
	int _xx=_x+1,_zz=_z+1;
	xx=(float)xx/HScale;
	zz=(float)zz/HScale;
	if (_xx>=Width)		_xx=Width-1;
	if (_zz>=Height)	_zz=Height-1;
/*	return (float)(Blend((float)HMap[_z*Width+_x]*VScale,(float)HMap[_z*Width+_xx]*VScale,1-xx)
		+Blend((float)HMap[_z*Width+_xx]*VScale,(float)HMap[_zz*Width+_xx]*VScale,1-zz))/2;*/
	float y0=HMap[_z*Width+_x]*VScale;
	float y2=HMap[_zz*Width+_xx]*VScale;
	if ((float)((float)(1-xx)*(1-xx)+(float)zz*zz)>=(float)((float)xx*xx+(float)(1-zz)*(1-zz)))//x>=z)
	{
		iii=0;
		float y1 = HMap[_zz*Width+_x]*VScale;
		float a = y1-y2;
		float b = 1;
		float c = y0-y1;
		float d = -y0*b;
		return -(a*xx+c*zz+d);
/*		float d=(float)(zz-xx);
		float o1=zz-d/2;
		float o2=sqrt((float)(d*d-d*d/sqrt(2.0f))/2);
		return Blend(Blend((float)HMap[_z*Width+_x]*VScale,(float)HMap[_zz*Width+_xx]*VScale,o1),(float)HMap[_zz*Width+_x]*VScale,o2);

/*        return (float)(Blend((float)HMap[_z*Width+_xx]*VScale,(float)HMap[_z*Width+_x]*VScale,1-xx)
			+Blend((float)HMap[_z*Width+_xx]*VScale,(float)HMap[_zz*Width+_xx]*VScale,zz));*/
	}
	else
	{
		iii=1;
		float y1 = HMap[_z*Width+_xx]*VScale;
		float a = y1-y0;
		float b = -1;
		float c = y2-y1;
		float d = -y0*b;
		return (a*xx+c*zz+d);
/*		float d=(float)(xx-zz);
		float o1=xx-d/2;
		float o2=sqrt((float)(d*d-d*d/sqrt(2.0f))/2);
		return Blend(Blend((float)HMap[_z*Width+_x]*VScale,(float)HMap[_zz*Width+_xx]*VScale,o1),(float)HMap[_z*Width+_xx]*VScale,o2);
/*        return (float)(Blend((float)HMap[_zz*Width+_x]*VScale,(float)HMap[_zz*Width+_xx]*VScale,xx)
			+ Blend((float)HMap[_zz*Width+_x]*VScale,(float)HMap[_z*Width+_x]*VScale,1-zz))
			;*/
	}
//	return HMap[_z*Width+_x]*VScale;
}
void				CHeightMap::CreateHeightMap(WORD w,WORD h)
{
}
void				CHeightMap::LoadHeightMap(PFile f)
{
	DELETE(HMap);
	this->HMap=new BYTE[this->Width*this->Height];
	this->FaceNormals=new Vector3[this->Width*this->Height*2];
	this->Normals=new Vector3[(this->Width+1)*(this->Height+1)];
	this->ColorMap=new DWORD[(this->Width+1)*(this->Height+1)];
	float prog=0;
	(prg)(prog,"1");
	for (int i=0;i<Width*Height;i++)
	{
		f->Read(&HMap[i],1);
	}
	prog=0.1f;
	(prg)(prog,"2");
	int pos=0;
	for (int y=0;y<Height;y++)
	{
		for (int x=0;x<Width;x++)
/*	for (int y=0;y<Height;y++)
	{
		for (int x=0;x<Width;x++)*/
		{
			int x1=x+1;
			int y1=y+1;
			if (x1==Width) x1=Width-1;
			if (y1==Height) y1=Height-1;
			if (x1<0) x1=0;
			if (y1<0) y1=0;
			float xx=x*this->HScale;
			float yy=y*this->HScale;
			float xx1=x1*this->HScale;
			float yy1=y1*this->HScale;
			this->FaceNormals[(x+y*Width)*2]	= CalcNorm(	Vector3(xx,GetHeightValue(xx,yy),yy),
															Vector3(xx1,GetHeightValue(xx1,yy),yy),
															Vector3(xx1,GetHeightValue(xx1,yy1),yy1)
															);
			this->FaceNormals[(x+y*Width)*2+1]	= CalcNorm(	Vector3(xx,GetHeightValue(xx,yy),yy),
															Vector3(xx1,GetHeightValue(xx1,yy1),yy1),
															Vector3(xx,GetHeightValue(xx,yy1),yy1)
															);
		}
	}
	prog=0.2f;
	(prg)(prog,"3");
	for (int y=0;y<Height+1;y++)
	{
		for (int x=0;x<Width+1;x++)
		{
			int x1=x;
			int y1=y;
			int x2=x-1;
			int y2=y-1;
			if (x2<0)		x2=0;
			if (y2<0)		y2=0;
			if (x1==Width)	x1=Width-1;
			if (y1==Height) y1=Height-1;
			Normals[x+y*(Width+1)]=GetFaceNormal(x1,y1,1)+GetFaceNormal(x1,y1,0)+GetFaceNormal(x1,y2,1)+GetFaceNormal(x2,y1,0)+GetFaceNormal(x2,y2,0)+GetFaceNormal(x2,y2,1);
			Normals[x+y*(Width+1)].Normalise();//=Normals[x+y*(Width+1)]/6.0f;
			float l1 = LightVector.Length();
			float l2 = Normals[x+y*(Width+1)].Length();
			float t=(LightVector*Normals[x+y*(Width+1)])/(l1*l2);//*Normals[x+y*(Width+1)].Length());
			if (t>=0)
			{
				ColorMap[x+y*(Width+1)]=this->Ambient;
			}
			else
			{
				ColorMap[x+y*(Width+1)]=BlendC((DWORD)Diffuse,(DWORD)Ambient,1+t);
			}
//			t/=10;
		}
	}
	prog=0.3f;
	(prg)(prog,"4");
	this->TempT=new WORD[this->Width*this->Height];
	/*for (int y=0;y<this->Height;y++)
	{
		for (int x=0;x<this->Width;x++)
		{
			f->Read(&this->TempT[y*this->Width+x],2);
		}
	}*/
	DWORD sz=this->Width*this->Height*2;
	f->Read(this->TempT,sz);
	f->Read(&this->TS,4);
	f->Read(&this->TWidth,4);
	f->Read(&this->THeight,4);
	f->Read(&this->TCount,4);
//	TDef--;
	Tdata *dat=new Tdata[TCount];
	for (int i=0;i<TCount;i++){
		char c;
		WORD x,y;
		f->Read(&dat[i].n,1);
		for (int j=0;j<dat[i].n;j++){
			f->Read(&dat[i].num[j],2);
			f->Read(&dat[i].coord[j],2);
		}
	}
	prog=0.35f;
	(prg)(prog,"5");
	int n=0;
	f->Read(&this->TDef,4);
	f->Read(&this->TDef1,4);
	f->Read(&n,4);
	CTexture *_txt=new CTexture[n];
	char fname[MAX_PATH];
	for (int i=0;i<n;i++)
	{
		ZeroMemory(fname,sizeof(fname));
		f->ReadNullTerminatedString(fname);
		_txt[i].LoadFromFile(fname);
	}
	prog=0.42f;
	(prg)(prog,"6");
#if 0
	D3DLOCKED_RECT rect;
	LPDIRECT3DTEXTURE9			txt;
	D3DXCreateTexture(__GetDevice(),this->TS*this->TWidth,this->TS*this->THeight,D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &txt);
	//D3DXCreateTexture(__GetDevice(),this->TS*this->TWidth,this->TS*this->THeight,D3DX_DEFAULT, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &Texture);
	txt->LockRect(0,&rect,NULL,D3DLOCK_DISCARD);
	DWORD *TText=new DWORD[this->TWidth*this->THeight*this->TS*this->TS];
	ZeroMemory(TText,this->TWidth*this->THeight*this->TS*this->TS*4);
	DWORD *dta1=(DWORD*)rect.pBits;
/*	for (int i=TCount;i<TWidth*THeight;i++)
	{
//		__GetDevice()->StretchRect(ot,NULL,nt,NULL,D3DTEXF_LINEAR);
		for (int j=0;j<dat[i].n;j++)
		{
			D3DLOCKED_RECT _rect;
			_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j])->LockRect(0,&_rect,NULL,D3DLOCK_READONLY);

//			int xx=i%this->TWidth,yy=i/this->TWidth;
//			TText[i*this->TS+(i/this->TWidth)*this->TS+x+y*this->TS*this->TWidth]=0x00000000;
			DWORD *dta2=(DWORD*)_rect.pBits;
			for (int y=0;y<this->TS;y++){
				for (int x=0;x<this->TS;x++){
					DWORD ind=
						(i%this->TWidth)*this->TS
						+(i/this->TWidth)*this->TS*this->TS*this->TWidth
						+x
						+y*this->TS*this->TWidth;
					if (TText[ind]==0) TText[ind]=dta2[y*TS+x]; else	TText[ind]=Blend (dta2[y*TS+x],TText[ind]);
				}
			}

			_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j])->UnlockRect(0);
//			_CopyBytes(_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j]),(BYTE*)rect.pBits,this->TS*this->TWidth,this->TS*this->THeight,this->TS,this->TS,i);
		}
	}*/
	for (int i=0;i<TWidth*THeight;i++)//
	{
//		__GetDevice()->StretchRect(ot,NULL,nt,NULL,D3DTEXF_LINEAR);
		prog=0.42f+0.2f*(float)i/(TWidth*THeight);
		(prg)(prog,"7");
		if (i<TCount){
			for (int j=0;j<dat[i].n;j++)
			{
				D3DLOCKED_RECT _rect;
				_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j])->LockRect(0,&_rect,NULL,D3DLOCK_READONLY);
	
	//			int xx=i%this->TWidth,yy=i/this->TWidth;
	//			TText[i*this->TS+(i/this->TWidth)*this->TS+x+y*this->TS*this->TWidth]=0x00000000;
				DWORD *dta2=(DWORD*)_rect.pBits;
				for (int y=0;y<this->TS;y++){
					for (int x=0;x<this->TS;x++){
						DWORD ind=
							(i%this->TWidth)*this->TS
							+(i/this->TWidth)*this->TS*this->TS*this->TWidth
							+x
							+y*this->TS*this->TWidth;
						/*if (TText[ind]==0) TText[ind]=dta2[y*TS+x]; else	*/TText[ind]=Blend (dta2[y*TS+x],TText[ind]);
					}
				}
	
				_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j])->UnlockRect(0);
	//			_CopyBytes(_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j]),(BYTE*)rect.pBits,this->TS*this->TWidth,this->TS*this->THeight,this->TS,this->TS,i);
			}
		}
		else
		{
			D3DLOCKED_RECT _rect;
			_txt[dat[TDef].num[0]]._GetTexture(dat[TDef].coord[TDef1])->LockRect(0,&_rect,NULL,D3DLOCK_READONLY);

//			int xx=i%this->TWidth,yy=i/this->TWidth;
//			TText[i*this->TS+(i/this->TWidth)*this->TS+x+y*this->TS*this->TWidth]=0x00000000;
			DWORD *dta2=(DWORD*)_rect.pBits;
			for (int y=0;y<this->TS;y++){
				for (int x=0;x<this->TS;x++){
					DWORD ind=
						(i%this->TWidth)*this->TS
						+(i/this->TWidth)*this->TS*this->TS*this->TWidth
						+x
						+y*this->TS*this->TWidth;
					/*if (TText[ind]==0) TText[ind]=dta2[y*TS+x]; else	*/TText[ind]=dta2[y*TS+x];//,TText[ind]);
				}
			}
			_txt[dat[TDef].num[0]]._GetTexture(dat[TDef].coord[TDef1])->UnlockRect(0);
//			_CopyBytes(_txt[dat[i].num[j]]._GetTexture(dat[i].coord[j]),(BYTE*)rect.pBits,this->TS*this->TWidth,this->TS*this->THeight,this->TS,this->TS,i);
		}
	}
	prog=0.62f;
	(prg)(prog,"7");
	memcpy(rect.pBits,TText,this->TWidth*this->THeight*this->TS*this->TS*4);
	txt->UnlockRect(0);
	for (int i=0;i<n;i++)
	{
		_txt[i].Release();
	}
	LPDIRECT3DSURFACE9 surf;
	txt->GetSurfaceLevel(0,&surf);
	//Texture->GetSurfaceLevel(0,&surf1);
	//__GetDevice()->StretchRect(surf,NULL,surf1,NULL,D3DTEXF_LINEAR);
	D3DXSaveSurfaceToFileA("Temp\\terrain.~tmp",D3DXIFF_BMP,surf,NULL,NULL);
	D3DXIMAGE_INFO Info;
	D3DXGetImageInfoFromFileA("Temp\\terrain.~tmp", &Info);
	D3DXCreateTextureFromFileExA(__GetDevice(), "Temp\\terrain.~tmp", Info.Width, Info.Height, D3DX_DEFAULT, 0, D3DFMT_X8R8G8B8, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &Texture);
	txt->Release();
	DELETE(TText);
	DELETE(_txt);
	DELETE(dat);
#endif
}
void				CHeightMap::GenerateNormals()
{
}
void				CHeightMap::LightIt(Vector3 LD)
{
}
CTerrain::CTerrain()
{
	this->HMap=new CHeightMap;
	this->TileCount=0;
	this->Tiles=NULL;
}
void CTerrain::Draw()
{
	this->HMap->dr=0;
	this->HMap->undr=0;
//	WriteMsg("-->Drawing terrain& gettin device& setting up texture");
	__GetDevice()->SetRenderState(D3DRS_CULLMODE,		  D3DCULL_CW); 

	__GetDevice()->SetTexture(0,HMap->Texture);//HMap->txt);NULL);//
/*	float _t=this->HMap->GetHeightValue(c->Pos.x,c->Pos.z);
	if (c->Pos.y-_t<=c->ZNear+0.01f)
	{
		c->Pos.y=_t+0.01f;
	}*/
//	WriteMsg("-->Drawing tiles");
	__GetDevice()->SetRenderState( D3DRS_LIGHTING, FALSE );
	for (int i=0;i<this->TileCount;i++)
	{
//		WriteMsg("-->Drawing tile:%d",i);
//		if (i==100||i==101){
//			WriteMsg("-->Drawing tile:%d",i);
//		}
//		else
		{
			Tiles[i].Draw();
		}
	}
	__GetDevice()->SetRenderState( D3DRS_LIGHTING, TRUE );
//	__GetDevice()->SetRenderState(D3DRS_CULLMODE,		  D3DCULL_CW); 
//	__GetDevice()->SetRenderState( D3DRS_CLIPPING,        FALSE );
//	SkyBox->Draw(0);
//	__GetDevice()->SetRenderState( D3DRS_CLIPPING,        TRUE );
}
void CTerrain::Load(PFile	f)
{
	this->HMap->LoadHeightMap(f);
	TileCount=(HMap->Width*HMap->Height)/(TILE_SIZE*TILE_SIZE);
	Tiles=new CPTile[TileCount];
	int w=HMap->Width/TILE_SIZE;
	int h=HMap->Height/TILE_SIZE;
//	SkyBox=new CRModel;
	TeVertex *v=new TeVertex[(TILE_SIZE)*(TILE_SIZE)*4];
	float prog=0.62f;
	(prg)(prog,"8");
	for (int i=0;i<TileCount;i++)
	{
/*		if (i==101){
			WriteMsg("-->Loading tile:%d",i);
		}*/
		prog=0.62f+0.1f*(float)i/TileCount;
		(prg)(prog," ");
		Tiles[i].HMap=HMap;
		Tiles[i].xt=i%w;
		Tiles[i].yt=i/w;
		Tiles[i].Ma=Vector3(0,0,0);
		Tiles[i].Mi=Vector3(HMap->Width*HMap->HScale+10,255*HMap->VScale+10,HMap->Height*HMap->HScale+10);
		Tiles[i].Create(v);
	}
	prog=0.72f;
	(prg)(prog,"8");
	DELETE(v);
//	ZeroMemory(SkyBoxTexture,sizeof(SkyBoxTexture));
//	f->ReadNullTerminatedString(SkyBoxTexture);
//	f->Read(&Cl,4);
/*	SkyBox->LoadFromFile("models\\system\\skybox.pmd","SkyBox");
	SkyBox->Translation=Vector3(HMap->Width*HMap->HScale/2.0f,0,HMap->Height*HMap->HScale/2.0f);
	SkyBox->Scaling=Vector3(max(HMap->Width*HMap->HScale*2.0f,HMap->Height*HMap->HScale*2.0f),
		max(HMap->Width*HMap->HScale*2.0f,HMap->Height*HMap->HScale*2.0f),
		max(HMap->Width*HMap->HScale*2.0f,HMap->Height*HMap->HScale*2.0f)
		);
	SkyBox->Mesh->Mesh->mats.Diffuse.a=1.0f;
	SkyBox->Mesh->Mesh->mats.Diffuse.r=GetRValue(Cl)/255.0f;
	SkyBox->Mesh->Mesh->mats.Diffuse.g=GetGValue(Cl)/255.0f;
	SkyBox->Mesh->Mesh->mats.Diffuse.b=GetBValue(Cl)/255.0f;
	if (strlen(SkyBoxTexture)>0){
		SkyBox->Texture=new CRTexture;
		SkyBox->Texture->LoadFromFile(SkyBoxTexture,"SkyBox");
	}
	else
	{
		SkyBox->Texture=NULL;
	}*/
}
CPMap::CPMap()
{
	Terrain=new CTerrain;
	Width=Height=0;
	ZeroMemory(name,sizeof(name));
}
void CPMap::Render()
{
	TerrainTime = timeGetTime();
	this->Terrain->Draw();
	TerrainTime = timeGetTime() - TerrainTime;
//	__GetDevice()->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_ONE );
//	__GetDevice()->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_ONE );
//		__GetDevice()->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_WIREFRAME  );
	ModelsTime = timeGetTime();
	for (int i=0;i<RM.ModelsCount;i++)
	{
//		RM.Models[i]->Rotation.z-=0.000f;
//		DrawLine(RM.Models[i]->Translation,RM.Models[i]->Translation+Vector3(0,10,0),0xffff0000,0xffff0000);
		RM.Models[i]->Draw(0);
//		RM.Models[i]->DrawBMesh(0xffff0000);
	}
	ModelsTime = timeGetTime() - ModelsTime;
#ifdef 0
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,false);
	for (int i=0;i<RM.ModelsCount;i++)
	{
		RM.Models[i]->DrawPS();
	}
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,true);
#endif
}
Vector3 GetEulerAnglesFromNormal(Vector3 n)
{
    Vector3 xyz_rot;
//    float d1 = sqrt( n.x*n.x + n.z * n.z );
//  float cos1 = n.x / d1;
//   float sin1 = n.z / d1;
//    xyz_rot.x = 0.0f;
//    xyz_rot.y = asin( sin1 );

//    float x1 = cos1 * n.x - sin1 * n.z;

  //  float d2 = sqrt ( x1*x1 + n.y*n.y );
//    float cos2 = n.y / d2;
//    float sin2 = x1 / d2;
//    xyz_rot.z = asin( sin2 );
#ifdef 0
	xyz_rot.x=-atan2(n.y,n.z)+D3DX_PI/2.0f;
#endif
	xyz_rot.y=atan2(n.x,n.z);//D3DX_PI/6;//atan2(n.z,n.x);
	xyz_rot.z=-atan2(n.x,n.y);//D3DX_PI/6;//atan2(n.z,n.x);-D3DX_PI/2.0f-
//	xyz_rot.z=0;//atan2(-n.x,n.y);
	return xyz_rot;


}
void CPMap::Update(scalar dt){
	for (int i=0;i<RM.ModelsCount;i++)
	{
//		RM.Models[i]->Rotation.z-=0.000f;
//		DrawLine(RM.Models[i]->Translation,RM.Models[i]->Translation+Vector3(0,10,0),0xffff0000,0xffff0000);
		RM.Models[i]->UpdatePS(dt);
	}
}
bool CPMap::LoadFromFile(LPCSTR Fname)
{
	PFile f=new CPFile;
	f->Open(Fname,FILE_READ);
	byte b=0;
	f->Read(&b,1);
	if (b!='P')
	{
		f->Close();
		DELETE(f);
		PutError("Cannot load map!File %s has unkown format or damaged!",Fname);
		return 0;
	}
	f->Read(&b,1);
	if (b!='M')
	{
		f->Close();
		DELETE(f);
		PutError("Cannot load map!File %s has unkown format or damaged!",Fname);
		return 0;
	}
	f->Read(&b,1);
	if (b!='P')
	{
		f->Close();
		DELETE(f);
		PutError("Cannot load map!File %s has unkown format or damaged!",Fname);
		return 0;
	}
	f->ReadNullTerminatedString(name);
	f->Read(&Width,4);
	f->Read(&Height,4);
	f->Read(&this->Terrain->HMap->HScale,4);
	f->Read(&this->Terrain->HMap->VScale,4);
	DWORD cc;
	f->Read(&cc,4);
#ifdef 0
	this->BGcolor=D3DCOLOR_XRGB(GetRValue(cc),GetGValue(cc),GetBValue(cc));
#endif
	f->Read(&this->fnear,4);
	f->Read(&this->ffar,4);
	this->Terrain->HMap->Width=this->Width;
	this->Terrain->HMap->Height=this->Height;
	this->Terrain->Load(f);
	//loading scenery
	int n=0;
	f->Read(&n,4);
	WORD xx=0;
	float x,z,sc,rot;
	BYTE ng;
	ZeroMemory(_path,sizeof(_path));
	float prog=0.72f;
	(prg)(prog,"9");
	for (int i=0;i<n;i++)
	{
		f->ReadNullTerminatedString(_path[i]);
	}
	int nn=0;
	f->Read(&nn,4);
	prog=0.725f;
	(prg)(prog,"10");
	for (int i=0;i<nn;i++)
	{
/*      f.writeword(doods[x]);
        f.WriteFloat(coord[x,0]);
        f.WriteFloat(coord[x,1]);
        f.WriteFloat(sc[x]);
        f.WriteFloat(Rot[x]);
        f.WriteBool(ng[x]);
*/
		prog=0.725f+0.225f*(float)i/nn;
		(prg)(prog,"11");
		f->Read(&xx,2);
		if (xx>=n) xx=n-1;
		f->Read(&x,4);
		f->Read(&z,4);
		f->Read(&sc,4);
		f->Read(&rot,4);
		f->Read(&ng,1);
		if ((z >= 0 && z <= this->Terrain->HMap->Width * this->Terrain->HMap->HScale)&&
			(x >= 0 && x <= this->Terrain->HMap->Height * this->Terrain->HMap->HScale))
		{
			RM.AddResource(RESOURCE_MODEL,_path[xx],"smt");
			CRModel* mm=(CRModel*)RM.LastCreatedResource;
			mm->Translation.z=x*this->Terrain->HMap->HScale;
			mm->Translation.x=z*this->Terrain->HMap->HScale;
			mm->Translation.y=this->Terrain->HMap->GetHeightValue(mm->Translation.x,mm->Translation.z);
				mm->Rot.y=rot;
				Vector3 v0=Vector3(-this->Terrain->HMap->GetFaceNormal(z,x,x>=z).x,this->Terrain->HMap->GetFaceNormal(z,x,x>=z).y,-this->Terrain->HMap->GetFaceNormal(z,x,x>=z).z);
				if (ng)
				mm->Rotation=GetEulerAnglesFromNormal(this->Terrain->HMap->GetFaceNormal(z,x,x>=z));
			mm->Scaling.x=sc;
			mm->Scaling.y=sc;
			mm->Scaling.z=sc;
		}
	}
	prog=1.0f;
	(prg)(prog,"11");
	f->Read(&n,4);
	f->Close();
	DELETE(f);
	return 1;
}
/*class CPMap
{
public:
	CPMap();
	bool						LoadFromFile(LPCSTR Fname);
	PTerrain					Terrain;
};

*/