#include"stdafx.h"
#include"mesh.h"
#include"ParticleSystem.h"
#include"terrain.h"
/*LPDIRECT3DDEVICE9 md3dd=NULL;
LPDIRECT3DINDEXBUFFER9	rib=NULL;
LPDIRECT3DINDEXBUFFER9	tib=NULL;
LPDIRECT3DVERTEXBUFFER9 pvb[128];*/
//LPDIRECT3DVERTEXBUFFER9 rvb=NULL;
//LPDIRECT3DVERTEXBUFFER9 lvb=NULL;
//LPD3DXLINE				_line = NULL;
LPVOID					vdata[128];
int						st[128];
bool					locked[128];
TPVertex				_vert[128][128];
const int DEFAULT_STEP=80;
WORD ic1[TILE_SIZE*6];

char _mszAppPath[MAX_PATH];
#if 0
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
	D3DXCreateLine(md3dd, &_line);
	RELEASE(lvb);
	int pos=0;
	for (int i=0;i<TILE_SIZE;i++)
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
/*
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
	for (int y=0;y<TILE_SIZE;y++)
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
	tib=PIECreateIndexBuffer(md3dd,ic1,TILE_SIZE*2,tib);
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
#endif
void MRelease()
{
#if 0
	RELEASE(rib);
	RELEASE(tib);
	RELEASE(rvb);
	for (int i=0;i<128;i++)
	{
		RELEASE(pvb[i]);
	}	
	RELEASE(lvb);
#endif
}
void DrawLine(Vector3 v1,Vector3 v2,DWORD cl1,DWORD cl2)
{
#if 0
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
#endif
}

void DrawLineEx(Vector3 v1, Vector3 v2, DWORD color, float width)
{
#if 0
	if (FAILED(_line->SetGLLines(TRUE)))
		return;
	if (FAILED(_line->SetWidth(width)))
		return;
	if (FAILED(_line->Begin()))
		return;
	D3DXVECTOR2 v[2];
	v[0].x = v1.x;
	v[0].y = v1.y;
	v[1].x = v1.x;
	v[1].y = v1.y;
	if (FAILED(_line->Draw(v, 2, color)))
		return;

//	_line->DrawTransform()
	_line->End();
#endif
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
#if 0
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
#endif
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
#if 0
	if (!PIELoadModel (_FName,1,&vnum,&fnum,&mats,__indices,__vertices,&BMin,&BMax,athres,vthres,txtrthres,InvertNormals)){
		PutError("Can't load mesh %s;",_FName);
		return 0;
	}
#endif
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
#if 0
	if (!DrawMesh) return;
	if (InvertN){
	    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	}
	else{
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	}
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
#endif
}
void CMesh::Draw1()
{
#if 0
	if (!DrawMesh) return;
	if (InvertN){
	    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, FALSE );
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	}
	else{
		md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_CW );
	    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
	}
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
	md3dd->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST,0,vnum,fnum,indices,D3DFMT_INDEX16,vertices,sizeof(TVertex3D));//(D3DPT_TRIANGLELIST,0,0,vnum,0,fnum);
#endif
}
CPRect::CPRect()
{
	ZeroMemory(this,sizeof(CPRect));
	for (int i=0;i<4;i++)
	{
		v[i].p.w=1.0f;
#if 0
		v[i].color=D3DCOLOR_XRGB(255,255,255);
#endif
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
#if 0
	rvb->Lock( 0, sizeof(v), (void**)&Vrt, 0 );
	memcpy(Vrt,v,sizeof(v));
    rvb->Unlock();
#endif
}
void CPRect::Draw()
{
#if 0
    md3dd->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

    // Turn off D3D lighting, since we are providing our own vertex colors
    md3dd->SetRenderState( D3DRS_LIGHTING, FALSE );
	md3dd->SetStreamSource(0,rvb,0,sizeof(TVertex2D));
	md3dd->SetFVF(VERTEX2D);
	md3dd->SetIndices(rib);
	md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,6,0,2);
#endif
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
#if 0
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
/*	DWORD ICl=0xff0000ff;
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
    md3dd->SetRenderState( D3DRS_POINTSPRITEENABLE, FALSE );
    md3dd->SetRenderState( D3DRS_POINTSCALEENABLE,  FALSE );
    md3dd->SetRenderState( D3DRS_CULLMODE,  D3DCULL_CCW );
    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
    md3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
//    md3dd->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCCOLOR );
//    md3dd->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INS );
	md3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
	md3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
#endif
}
void CPTile::Create(TeVertex *v)
{
#if 0
	int pos=0;
	byte r=rand()%128+127,g=rand()%128+127,b=rand()%128+127;
	Cl=D3DCOLOR_XRGB(r,g,b);
	ICl=D3DCOLOR_XRGB(255-r,255-g,255-b);
//					if (y==(TILE_SIZE-1)&&x==(TILE_SIZE-1))
//				{
//					WriteMsg("-->Tada!");
//				}

    for (int y=0;y<(TILE_SIZE);y++)
	{
		for (int x=0;x<(TILE_SIZE);x++)
		{
			int ind=xt*(TILE_SIZE)+x+(yt*(TILE_SIZE)+y)*this->HMap->Width;
			int _pos=this->HMap->TempT[ind];
			float dy=(float)1/(this->HMap->THeight),dx=(float)1/(this->HMap->TWidth);
			int x1=_pos%(this->HMap->TWidth);
			int y1=_pos/(this->HMap->TWidth);
			float _tu=(float)x1*dx;
			float _tv=(float)y1*dy;
			float px=(float)dx/this->HMap->TS;
			float py=(float)dy/this->HMap->TS;
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
				v[pos].tu=_tu+(float)((i)/2)*(dx-3.0f*px)+1.5f*px;
				v[pos].tv=_tv+(float)((i)%2)*(dy-3.0f*py)+1.5f*py;
				if (v[pos].tu<0.0f) v[pos].tu=0.0f;
				if (v[pos].tv<0.0f) v[pos].tv=0.0f;
				if (v[pos].tu>1.0f) v[pos].tu=1.0f;
				if (v[pos].tv>1.0f) v[pos].tv=1.0f;
				xx=x+xt*(TILE_SIZE)+i%2;
				yy=y+yt*(TILE_SIZE)+i/2;
				if (xx>HMap->Width) xx=HMap->Width;
				if (yy>HMap->Height) yy=HMap->Height;
				v[pos].Color=HMap->ColorMap[xx+yy*(HMap->Width+1)];//HMap->Diffuse;//this->Cl;//
				if (xt+yt*HMap->Width/TILE_SIZE==100)
				{
//					WriteMsg("X:%f; Y:%f; Z:%f; TU:%f; TV:%f; COLOR:%d",v[pos].p.x,v[pos].p.y,v[pos].p.z,v[pos].tu,v[pos].tv,v[pos].Color);
				}
				pos++;
			}
		}
	}
	RELEASE(buff);
	LPVOID dta;
	md3dd->CreateVertexBuffer((TILE_SIZE)*(TILE_SIZE)*4*sizeof(TeVertex),D3DUSAGE_WRITEONLY,TERRAIN_VERTEX,D3DPOOL_MANAGED,&buff,NULL);
	buff->Lock(0,(TILE_SIZE)*(TILE_SIZE)*4*sizeof(TeVertex),(void**)&dta,D3DLOCK_DISCARD);
	memcpy(dta,v,sizeof(TeVertex)*(TILE_SIZE)*(TILE_SIZE)*4);
	buff->Unlock();
#endif
}
void CPTile::Draw()
{
//	WriteMsg("Start!");
	PCamera c = GetCurrentCamera();//new CCamera;////
	/*c->SetCPlanes(2.0f,200.0f);
	c->SetFA((FLOAT)D3DX_PI/4,1);//(FLOAT)pd->GetScreenWidth()/pd->GetScreenHeight());
	c->SetPos(Vector3(100 + (float)(timeGetTime()%10000)/1000,100,100));
	c->SetTarget(Vector3(0,0,0));
	c->SetUp(Vector3(0,1,0));*/
//;//GetCurrentCamera();
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));

	if (CullBox(Mi,Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
	{
		/*if ((xt+yt)%4==0)
		{
			Vector3 p[8];
			p[0] = Mi;
			p[1] = Vector3(Ma.x, Mi.y, Mi.z);
			p[2] = Vector3(Ma.x, Ma.y, Mi.z);
			p[3] = Vector3(Mi.x, Ma.y, Mi.z);
			p[4] = Vector3(Mi.x, Mi.y, Ma.z);
			p[5] = Vector3(Ma.x, Mi.y, Ma.z);
			p[6] = Vector3(Ma.x, Ma.y, Ma.z);
			p[7] = Vector3(Mi.x, Ma.y, Ma.z);
			for (int i = 0; i < 8; i++)
			{
				DrawLine(p[i], c->Pos, 0xff0000ff, 0xffff0000);
				for (int j = i + 1; i < 8; i++)
				{
					DrawLine(p[i], p[j], 0xff0000ff, 0xffff0000);
				}
			}
			DrawLine(c->Pos, c->At, 0xff00ff00, 0xff00ff00);
//			DrawLine(c->Pos, Mi, 0xffff0000, 0xffff0000);
//			DrawLine(c->Pos, Ma, 0xffff0000, 0xffff0000);
			DrawLineEx(Vector3(0, 0, 0), Vector3(100, 100, 0), 0xff00ff00, 4.0f);
		}*/
#if 0
		if (SUCCEEDED(md3dd->SetStreamSource(0,buff,0,sizeof(TeVertex)))){
			md3dd->SetFVF(TERRAINVERTEX);
			if (SUCCEEDED(md3dd->SetIndices(tib))){
				for (int i=0;i<TILE_SIZE;i++)
				{
					md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,i*TILE_SIZE*4,0,TILE_SIZE*6,0,TILE_SIZE*2);
//					md3dd->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0,TILE_SIZE*TILE_SIZE*6,0,TILE_SIZE*TILE_SIZE*2);
				}
			}
		}
#endif
	//normals
		HMap->dr++;
	}
//	delete c;
//	WriteMsg("End!");
/*    for (int y=0;y<(TILE_SIZE);y++)
	{
		for (int x=0;x<(TILE_SIZE);x++)
		{
			for (int i=0;i<4;i++){
				int xx=xt*(TILE_SIZE)+x+i%2;
		        int yy=yt*(TILE_SIZE)+y+i/2;
				Vector3 nr=this->HMap->Normals[xx+yy*(HMap->Width+1)];
				if (xx>=HMap->Width) xx=HMap->Width-1;
				if (yy>=HMap->Height) yy=HMap->Height-1;
				Vector3 ps=Vector3((x+xt*(TILE_SIZE)+i%2)*HMap->HScale,
					HMap->HMap[yy*HMap->Width+xx]*HMap->VScale,
					(y+yt*(TILE_SIZE)+i/2)*HMap->HScale);
				DrawLine(ps,ps+nr,0xffff0000,0xff00ff00);
			}
		}
	}*/
//		md3dd->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_SOLID  );
//    md3dd->SetRenderState( D3DRS_ZWRITEENABLE, TRUE );
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
	/*else
	{
		WriteMsg("-->Failed");
		HMap->undr++;
	}*/

//	DrawLine(Vector3(Mi.x,Mi.y,Mi.z),Vector3(Mi.x,Mi.y,Ma.z),ICl,ICl);
}

/*void DrawPS(CParticleSystem ps,WORD num)
{
}*/