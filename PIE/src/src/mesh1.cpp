#include"stdafx.h"
#include"mesh.h"
#include"ParticleSystem.h"
#include"terrain.h"
LPDIRECT3DDEVICE9 md3dd=NULL;
const int DEFAULT_STEP=80;
LPDIRECT3DINDEXBUFFER9	rib=NULL;
LPDIRECT3DINDEXBUFFER9	tib=NULL;
LPDIRECT3DVERTEXBUFFER9 pvb[128];
LPVOID					vdata[128];
int						st[128];
TPVertex				_vert[128][128];
bool					locked[128];
LPDIRECT3DVERTEXBUFFER9 rvb=NULL;
LPDIRECT3DVERTEXBUFFER9 lvb=NULL;
WORD ic1[TILE_SIZE*TILE_SIZE*6];

char _mszAppPath[MAX_PATH];
void MHAssignDevice(LPDIRECT3DDEVICE9 _d3dd,char *CDir)
{
	md3dd=_d3dd;
	strcpy(_mszAppPath,CDir);
	if (rib)
		RELEASE(rib);
	if (rvb)
		RELEASE(rib);
	WORD ic[]={0,1,3,3,2,0};
	RELEASE(rib);
	RELEASE(tib);
	RELEASE(rvb);
	for (int i=0;i<128;i++)
	{
		RELEASE(pvb[i]);
		md3dd->CreateVertexBuffer(DEFAULT_STEP*sizeof(TPVertex), 
			D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, POINTVERTEX,
			D3DPOOL_DEFAULT, &pvb[i],NULL);
	}	
	RELEASE(lvb);
	int pos=0;
	for (int i=0;i<TILE_SIZE*TILE_SIZE;i++)
	{
		ic1[pos]=i*4;
		pos++;
		ic1[pos]=i*4+1;
		pos++;
		ic1[pos]=i*4+3;
		pos++;
		ic1[pos]=i*4+3;
		pos++;
		ic1[pos]=i*4+2;
		pos++;
		ic1[pos]=i*4;
		pos++;
	}
/*	for (int y=0;y<TILE_SIZE;y++)
	{
		for (int x=0;x<TILE_SIZE;x++)
		{
			ic1[pos]=x+y*(TILE_SIZE+1);
			pos++;
			ic1[pos]=x+y*(TILE_SIZE+1)+1;
			pos++;
			ic1[pos]=x+(y+1)*(TILE_SIZE+1)+1;
			pos++;
			ic1[pos]=x+(y+1)*(TILE_SIZE+1);
			pos++;
			ic1[pos]=x+(y+1)*(TILE_SIZE+1)+1;
			pos++;
			ic1[pos]=x+y*(TILE_SIZE+1);
			pos++;

/*			ic1[pos]=x+y*16+d;
			pos++;
			ic1[pos]=x+y*16+1+d;
			pos++;
			ic1[pos]=x+(y+1)*16+1+d;
			pos++;
			ic1[pos]=x+(y+1)*16+d;
			pos++;
			ic1[pos]=x+(y+1)*16+1+d;
			pos++;
			ic1[pos]=x+y*16+d;
			pos++;
		}
	}*/
	rib=PIECreateIndexBuffer(md3dd,ic,2,rib);
	tib=PIECreateIndexBuffer(md3dd,ic1,TILE_SIZE*TILE_SIZE*2,tib);
	md3dd->CreateVertexBuffer(4*sizeof(TVertex2D), 
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, VERTEX2D,
		D3DPOOL_DEFAULT, &rvb,NULL);
	md3dd->CreateVertexBuffer(2*sizeof(TPVertex), 
		D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, POINTVERTEX,
		D3DPOOL_DEFAULT, &lvb,NULL);
/*	md3dd->CreateVertexBuffer(DEFAULT_STEP*sizeof(TPVertex), 
		D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_POINTS, POINTVERTEX,
		D3DPOOL_DEFAULT, &pvb,NULL);*/
}
void MRelease()
{
	RELEASE(rib);
	RELEASE(tib);
	RELEASE(rvb);
	for (int i=0;i<128;i++)
	{
		RELEASE(pvb[i]);
	}	
	RELEASE(lvb);
}
void DrawLine(Vector3 v1,Vector3 v2,DWORD cl1,DWORD cl2)
{
	md3dd->SetRenderState(D3DRS_LIGHTING,0);
	TPVertex _t[2];
	_t[0].p=v1;
	_t[0].Color=cl1;
	_t[1].p=v2;
	_t[1].Color=cl2;
	void *xxx;
	md3dd->SetTexture(0,NULL);
	md3dd->SetStreamSource(0,lvb,0,sizeof(TPVertex));
	md3dd->SetFVF(POINTVERTEX);
	lvb->Lock(0,2*sizeof(TPVertex),(void**)&xxx,D3DLOCK_DISCARD);
	memcpy(xxx,_t,sizeof(_t));
	lvb->Unlock();
	md3dd->DrawPrimitive(D3DPT_LINELIST,0,1);
//	md3dd->SetRenderState(D3DRS_LIGHTING,1);
}
CMesh::CMesh()
{
	ZeroMemory(this,sizeof(CMesh));
//	txt=new CTexture;
}
void CMesh::AssignVertexData(TVertex3D *v,DWORD _vnum)
{
	DELETE(vertices);
	vertices=new TVertex3D[_vnum];
	memcpy(vertices,v,_vnum*sizeof(TVertex3D));
	vnum=_vnum;
}
void CMesh::AssignIndexData(WORD *i,DWORD _fnum)
{
	DELETE(indices);
	indices=new WORD[_fnum*3];
	memcpy(indices,i,_fnum*6);
	fnum=_fnum;
}
bool CMesh::MakeBuffers()
{
	if (!CreateBuffers) return 1;
	ib=PIECreateIndexBuffer(md3dd,indices,fnum,ib);
	if (!ib){
		PutError("Can't create index buffer");
		return 0;
	}
	vb=PIECreateVertexBuffer(md3dd,vertices,vnum,VERTEX3D,sizeof(TVertex3D),vb);
	if (!vb)
	{
		PutError("Can't create vertex buffer");
		RELEASE(ib);
		return 0;
	}
	return 1;
}
bool CMesh::LoadFromFile(LPCSTR FName,FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals)
{
	WORD **__indices=new WORD*;
	TVertex3D	**__vertices=new TVertex3D*;
	WORD *_indices=NULL;
	TVertex3D	*_vertices=NULL;
	char _FName[MAX_PATH];
	strcpy(_FName,_mszAppPath);
	strcat(_FName,FName);
	ZeroMemory(__fname,MAX_PATH);
	memcpy(__fname,FName,strlen(FName));
	if (!PIELoadModel (_FName,1,&vnum,&fnum,&mats,__indices,__vertices,&BMin,&BMax,athres,vthres,txtrthres,InvertNormals)){
		PutError("Can't load mesh %s;",_FName);
		return 0;
	}
/*EXPORT BOOL PIELoadModel (LPCSTR fname,DWORD ModelKind,
											   DWORD *vnum,DWORD *fnum,D3DMATERIAL9 *mat,
											   WORD **IndexData,LPVOID VertexData,
											   Vector3 *Min,Vector3 *Max,
											   FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals)*/
	_indices=*__indices;
	_vertices=*__vertices;
	indices=new WORD[fnum*3];
	vertices=new TVertex3D[vnum];
	memcpy(indices,_indices,6*fnum);
	memcpy(vertices,_vertices,sizeof(TVertex3D)*vnum);
	return 1;
}
bool CMesh::LoadMesh(LPCSTR FName,FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals,bool _SelfIllumination)
{
	SelfIllumination=_SelfIllumination;
	InvertN=InvertNormals;
	if (!LoadFromFile(FName,athres,vthres,txtrthres,InvertNormals))
		return 0;
	return MakeBuffers();
}
void CMesh::DrawAsLines(DWORD Color)
{
	for (int i=0;i<fnum;i++)
	{
		DrawLine(vertices[indices[i*3]].p,vertices[indices[i*3+1]].p,Color,Color);
		DrawLine(vertices[indices[i*3]].p,vertices[indices[i*3+2]].p,Color,Color);
		DrawLine(vertices[indices[i*3+1]].p,vertices[indices[i*3+2]].p,Color,Color);
	}
}
void CMesh::Draw()
{
	if (!DrawMesh) return;
	if (InvertN)
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	else
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	if (SelfIllumination)
	{
		md3dd->SetRenderState( D3DRS_LIGHTING, FALSE );
	}
	else
		md3dd->SetRenderState( D3DRS_LIGHTING, TRUE );
	md3dd->SetRenderState(D3DRS_ZENABLE,1);
	md3dd->SetRenderState(D3DRS_ZWRITEENABLE,1);
	md3dd->SetMaterial(&mats);
	md3dd->SetFVF(VERTEX3D);
	md3dd->SetStreamSource(0,vb,0,sizeof(TVertex3D));
	md3dd->SetIndices(ib);
	md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,vnum,0,fnum);
}
CPRect::CPRect()
{
	ZeroMemory(this,sizeof(CPRect));
	for (int i=0;i<4;i++)
	{
		v[i].p.w=1.0f;
		v[i].color=D3DCOLOR_XRGB(255,255,255);
	}
}
void CPRect::SetPos(int ind,Vector3 _p)
{
	v[ind].p.x=_p.x;
	v[ind].p.y=_p.y;
	v[ind].p.z=_p.z;
}
void CPRect::SetTCoord(int ind,FLOAT _tu,FLOAT _tv)
{
	v[ind].tu=_tu;
	v[ind].tv=_tv;
}
void CPRect::SetColor(int ind,DWORD _Color)
{
	v[ind].color=_Color;
}
void CPRect::Update()
{
	void* Vrt;
	rvb->Lock( 0, sizeof(v), (void**)&Vrt, 0 );
	memcpy(Vrt,v,sizeof(v));
    rvb->Unlock();
}
void CPRect::Draw()
{
    md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    md3dd->SetRenderState( D3DRS_LIGHTING, FALSE );
	md3dd->SetStreamSource(0,rvb,0,sizeof(TVertex2D));
	md3dd->SetFVF(VERTEX2D);
	md3dd->SetIndices(rib);
	md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,6,0,2);
//	md3dd->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);
}
CModel::CModel()
{
	ZeroMemory(this,sizeof(CModel));
}
void CModel::AssignMesh(PMesh _mesh,WORD index)
{
	Mesh=_mesh;
	ind=index;
	sc.x=1.0f;
	sc.y=1.0f;
	sc.z=1.0f;
}
void CModel::Draw(WORD index)
{
//    md3dd->SetRenderState( D3DRS_LIGHTING, TRUE );//md3dd->SetRenderState( D3DRS_ZENABLE ,true);
}
void CDParticleSystem::Render()
{
	//new version)
//	TPVertex _vert[128];
//	void *pp;
	TPVertex _temp;
	md3dd->SetRenderState(D3DRS_LIGHTING,0);
    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
    md3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	if (info->BlendKind)
	{
		md3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_ONE );
		md3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_ONE );
	}
	else
	{
		md3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
		md3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
	}
    md3dd->SetRenderState( D3DRS_CULLMODE,  D3DCULL_NONE );
    md3dd->SetRenderState( D3DRS_POINTSPRITEENABLE, TRUE );
    md3dd->SetRenderState( D3DRS_POINTSCALEENABLE,  TRUE );
//	md3dd->SetRenderState( D3DRS_POINTSIZE,     FtoDW(info.startsize) );
    md3dd->SetRenderState( D3DRS_POINTSIZE_MIN, FtoDW(0.00f) );
    md3dd->SetRenderState( D3DRS_POINTSCALE_A,  FtoDW(0.00f) );
    md3dd->SetRenderState( D3DRS_POINTSCALE_B,  FtoDW(0.00f) );
    md3dd->SetRenderState( D3DRS_POINTSCALE_C,  FtoDW(1.00f) );
//	md3dd->SetStreamSource(0,pvb,0,sizeof(TPVertex));
	md3dd->SetFVF(POINTVERTEX);
	int k=ParticlesActive;
	for (int i=0;i<128;i++)
	{
		locked[i]=0;
	}
	for (int i=0;i<k;i++)
	{
		int _p=info->startf+((float)particles[i].age/particles[i].life)*(info->fcount+info->txt->dtNum*(info->fcount==0));
        
		if (st[_p]==DEFAULT_STEP-1)
		{
			//unlocking AND drawing
			memcpy(vdata[_p],_vert[_p],sizeof(TPVertex)*DEFAULT_STEP);

			pvb[_p]->Unlock();
			locked[_p]=0;
			md3dd->SetStreamSource(0,pvb[_p],0,sizeof(TPVertex));
			info->txt->SetTexture(_p);
			md3dd->DrawPrimitive(D3DPT_POINTLIST,0,DEFAULT_STEP);
		}

		if (!locked[_p])
		{
			pvb[_p]->Lock(0,DEFAULT_STEP*sizeof(TPVertex),(void**)&vdata[_p],D3DLOCK_DISCARD);
			locked[_p]=1;
			st[_p]=0;
		}
		//copying data
		_temp.Color=D3DCOLOR_ARGB((BYTE)particles[i].a,(BYTE)particles[i].r,
				(BYTE)particles[i].g,(BYTE)particles[i].b);
		_temp.size=particles[i].size;
		_temp.p=particles[i].p;
		memcpy(&_vert[_p][st[_p]],&_temp,sizeof(TPVertex));
		st[_p]++;
        

	}
	//checking for undrawed particles;
	for (int i=0;i<128;i++)
	{
		if (locked[i])
		{
			memcpy(vdata[i],_vert[i],sizeof(TPVertex)*st[i]);
			pvb[i]->Unlock();
			locked[i]=0;
			md3dd->SetStreamSource(0,pvb[i],0,sizeof(TPVertex));
			info->txt->SetTexture(i);
			md3dd->DrawPrimitive(D3DPT_POINTLIST,0,st[i]);
		}
	}
/*	if (txtr->Created)
//		txtr->SetTexture(0);
	for (WORD i=0;i<k;i++)
	{
		if (FAILED(pvb->Lock(0,DEFAULT_STEP*sizeof(TPVertex),(void**)&pp,D3DLOCK_DISCARD)))
			return;
		for (BYTE j=0;j<DEFAULT_STEP;j++)
		{
			_vert[j].p=particles[i*DEFAULT_STEP+j].p;
//			DrawLine(particles[i+j].p,particles[i+j].p+particles[i+j].v,0xFFFFFFFF,0xFFFFFFFF);
/*			D3DXCOLOR clr,clr1,clr2;
			clr1=D3DXCOLOR(info.sr,info.sg,info.sb,info.sa);
			clr2=D3DXCOLOR(info.er,info.eg,info.eb,info.ea);
			D3DXColorLerp(&clr, &clr1, &clr2,(float)particles[i+j].age/particles[i+j].life);*/
/*			_vert[j].Color=D3DCOLOR_ARGB((BYTE)particles[i*DEFAULT_STEP+j].a,(BYTE)particles[i*DEFAULT_STEP+j].r,
				(BYTE)particles[i*DEFAULT_STEP+j].g,(BYTE)particles[i*DEFAULT_STEP+j].b);
		}
		memcpy(pp,_vert,DEFAULT_STEP*sizeof(TPVertex));
		pvb->Unlock();
/*		for (BYTE j=0;j<DEFAULT_STEP;j++)
		{
			md3dd->SetRenderState( D3DRS_POINTSIZE,     FtoDW(ps.particles[i*DEFAULT_STEP+j].size) );
			md3dd->DrawPrimitive(D3DPT_POINTLIST,j,1);
		}
		md3dd->DrawPrimitive(D3DPT_POINTLIST,0,DEFAULT_STEP);
	}
	if (info.ParticlesActive%DEFAULT_STEP!=0)
	{
		pvb->Lock(0,(info.ParticlesActive%DEFAULT_STEP)*sizeof(TPVertex)
			,(void**)&pp,D3DLOCK_DISCARD);
		for (BYTE j=0;j<info.ParticlesActive%DEFAULT_STEP;j++)
		{
			_vert[j].p=particles[k*DEFAULT_STEP+j].p;
//			DrawLine(particles[i+j].p,particles[i+j].p+particles[i+j].v,0xFFFFFFFF,0xFFFFFFFF);
			_vert[j].Color=D3DCOLOR_ARGB((BYTE)particles[k*DEFAULT_STEP+j].a,(BYTE)particles[k*DEFAULT_STEP+j].r,
				(BYTE)particles[k*DEFAULT_STEP+j].g,(BYTE)particles[k*DEFAULT_STEP+j].b);
		}
		memcpy(pp,_vert,(info.ParticlesActive%DEFAULT_STEP)*sizeof(TPVertex));
		pvb->Unlock();
/*		for (BYTE j=0;j<ps.info.ParticlesActive%DEFAULT_STEP;j++)
		{
			md3dd->SetRenderState( D3DRS_POINTSIZE,     FtoDW(ps.particles[i*DEFAULT_STEP+j].size) );
			md3dd->DrawPrimitive(D3DPT_POINTLIST,j,1);
		}
		md3dd->DrawPrimitive(D3DPT_POINTLIST,0,info.ParticlesActive%DEFAULT_STEP);
	}*/
    md3dd->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
    md3dd->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
    md3dd->SetRenderState( D3DRS_CULLMODE,  D3DCULL_CCW );
    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
    md3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
//    md3dd->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR );
//    md3dd->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INS );
	md3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
	md3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
}
void CPTile::Create()
{
	TeVertex v[(TILE_SIZE)*(TILE_SIZE)*4];
	int pos=0;
	byte r=rand()%128+127,g=rand()%128+127,b=rand()%128+127;
	Cl=D3DCOLOR_XRGB(r,g,b);
	ICl=D3DCOLOR_XRGB(255-r,255-g,255-b);
    for (int y=0;y<(TILE_SIZE);y++)
	{
		for (int x=0;x<(TILE_SIZE);x++)
		{
			int pos=this->HMap->TempT[xt*(TILE_SIZE)+x+(yt*(TILE_SIZE)+y)*this->HMap->Width];
			float dy=(float)1/this->HMap->THeight,dx=(float)1/this->HMap->TWidth;
			int __x=pos%this->HMap->TWidth;
			int __y=pos/this->HMap->TWidth;
			float _tu=(float)__x*dx;
			float _tv=(float)__y*dy;
			for (int i=0;i<4;i++){
				int xx=xt*(TILE_SIZE)+x+i%2;
		        int yy=yt*(TILE_SIZE)+y+i/2;
				v[pos].p.x=(float)(x+xt*(TILE_SIZE)+i%2)*HMap->HScale;
				v[pos].p.z=(float)(y+yt*(TILE_SIZE)+i/2)*HMap->HScale;
				if (xx>=HMap->Width)  xx=HMap->Width-1;
				if (yy>=HMap->Height) yy=HMap->Height-1;
				v[pos].p.y=(float)HMap->HMap[yy*HMap->Width+xx]*HMap->VScale;
				WORD tt=HMap->TempT[yy*HMap->Width+xx];
            
				Mi.x=min(v[pos].p.x,Mi.x);
				Ma.x=max(v[pos].p.x,Ma.x);
				Mi.y=min(v[pos].p.y,Mi.y);
				Ma.y=max(v[pos].p.y,Ma.y);
				Mi.z=min(v[pos].p.z,Mi.z);
				Ma.z=max(v[pos].p.z,Ma.z);
				v[pos].tu=_tu+(float)(i%2)*dx;
				v[pos].tv=_tv+(float)(i/2)*dy;
				v[pos].Color=HMap->Diffuse;//this->Cl;//HMap->Diffuse;
				pos++;
			}
		}
	}
	RELEASE(buff);
	LPVOID dta;
	md3dd->CreateVertexBuffer((TILE_SIZE)*(TILE_SIZE)*4*sizeof(TeVertex),D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC,TERRAIN_VERTEX,D3DPOOL_DEFAULT,&buff,NULL);
	buff->Lock(0,(TILE_SIZE)*(TILE_SIZE)*4*sizeof(TeVertex),(void**)&dta,D3DLOCK_DISCARD);
	memcpy(dta,v,sizeof(TeVertex)*(TILE_SIZE)*(TILE_SIZE)*4);
	buff->Unlock();
}
void CPTile::Draw(PCamera c)
{
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));
/*bool CullBox(Vector3 min, Vector3 max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);*/

	if (CullBox(Mi,Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
	{
		md3dd->SetRenderState( D3DRS_LIGHTING, FALSE );
		//md3dd->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_WIREFRAME  );
		md3dd->SetFVF(TERRAINVERTEX);
		md3dd->SetStreamSource(0,buff,0,sizeof(TeVertex));
		md3dd->SetIndices(tib);
	//	md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,6,0,2);
		md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,TILE_SIZE*TILE_SIZE*6,0,TILE_SIZE*TILE_SIZE*2);
		md3dd->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_SOLID  );
		//bbox
/*		DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Mi.x,Mi.y,Ma.z),ICl,ICl);
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
		HMap->dr++;
	}
	else
	{
		HMap->undr++;
	}

//	DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Mi.x,Mi.y,Ma.z),ICl,ICl);
}

/*void DrawPS(CParticleSystem ps,WORD num)
{
}*/