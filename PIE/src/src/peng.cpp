#include"stdafx.h"
#include"peng.h"
//this is pie engine main sector
//Variables only(!!!!!) for model loading!
//Place your variables anywhere, but not here)
const char ERRONEOUS_STRING[]= "00000";
LIT main;
Vector3 *fn=NULL;
TVertex3D *va=NULL;
WORD *ic=NULL;
DWORD pc,mc,ccc;
DWORD _fnum,_vnum,rr,_pos1;
WORD nv;
WORD nf,tfpos,len;
DWORD voffsets[256],foffsets[256];
D3DMATERIAL9 _mat[256];
char tfnames[2048];	
bool skipmat=0;
bool INv=0;
FLOAT anglethreshold=30.0f,vertexthreshold=0.001f,texturethreshold=0.0f;
WORD				tvertex		[65000];
Vector3				tvert		[65000];
Vector2				txtr		[65000];
TVertex3D			result		[65000];
WORD				fbuff		[150000];
DWORD				_stack		[200][3];
DWORD				_stack1		[200][3];
bool				_canweld	[200];
WORD				stacksize;
WORD				stacksize1;
DWORD				__vnum=0,dvnum=0;
Vector3				cn,*bboxmin,*bboxmax;

//<--Files-->
HANDLE PIEOpenFile(LPCSTR fname,BOOL Read)
{ 
	HANDLE result;
	if (Read)
		result=CreateFileA(fname,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	else
		result=CreateFileA(fname,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	return result;
}
BOOL PIECloseFile(HANDLE file)
{
	return CloseHandle(file);
}

/*BOOL PIEReadFile(HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnor,LPOVERLAPPED lpov)
{
	return ReadFile(file,lpBuffer,ntr,lpnor,lpov);
}*/
BOOL  PIEReadFile(HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnor,LPOVERLAPPED lpov)
{
	return ReadFile(file,lpBuffer,ntr,lpnor,lpov);
}
BOOL PIEWriteFile(HANDLE file,LPVOID lpBuffer,DWORD ntr,LPDWORD lpnow,LPOVERLAPPED lpov)
{
	return WriteFile(file,lpBuffer,ntr,lpnow,lpov);
}
void PIESkipBytes(HANDLE file,DWORD bytes)
{
	char *c=new char[bytes];
	DWORD rr;
	PIEReadFile(file,c,bytes,&rr,NULL);
}
DWORD PIESetOffset(HANDLE file,LONG offset,unsigned short int pos)
{
//	lpov->hEvent=CreateEvent(NULL,TRUE,TRUE,NULL);
//	if (lpov->hEvent=NULL) return false;
	if (pos==0)
		return SetFilePointer(file,offset,NULL,FILE_BEGIN);
	if (pos==1)
		return SetFilePointer(file,offset,NULL,FILE_CURRENT);
	if (pos==2)
		return SetFilePointer(file,offset,NULL,FILE_END);
	return SetFilePointer(file,offset,NULL,FILE_BEGIN);
//	lpov->Offset=offset;
}
LONG PIEFindByte(HANDLE file,LONG offset,BYTE data)
{
	DWORD rd=0,pos=0;
	BYTE buff=0;
	PIESetOffset(file,offset,0);
	PIEReadFile(file,&buff,1,&rd,NULL);
	while (rd==1&&!buff==data)
	{
		pos++;
		PIEReadFile(file,&buff,1,&rd,NULL);
	}
	PIESetOffset(file,offset,0);
	if (buff!=data)
		return -1;
	else
		return pos+offset;
}



//<--Ini-files-->
bool PIEReadIni(char* section,char* key,char* path,char* result)
{
	if FAILED(GetPrivateProfileStringA(section, key,ERRONEOUS_STRING,
           result, 1024, path))
		   return 0;
	return 1;
}
bool PIEWriteIni(char* section,char* key,char* path,char* str)
{
	return WritePrivateProfileStringA(section,key,str,
           path);
}
//<--Functions-->
D3DCOLORVALUE PIEMakeColor(BYTE a,BYTE r,BYTE g,BYTE b)
{
	D3DCOLORVALUE res;
	res.a=(float)a/255;
	res.b=(float)b/255;
	res.g=(float)g/255;
	res.r=(float)r/255;
	return res;
}
D3DMATERIAL9 PIEMakeMaterial(D3DCOLORVALUE a,D3DCOLORVALUE d,D3DCOLORVALUE s,D3DCOLORVALUE e,FLOAT p)
{
	D3DMATERIAL9 res;
	res.Ambient=a;
	res.Diffuse=d;
	res.Specular=s;
	res.Emissive=e;
	res.Power=p;
	return res;
}
D3DMATERIAL9 PIEReadMaterial(HANDLE file)
{
	BYTE a,r,g,b;
	DWORD rr;
	D3DMATERIAL9 m,def;
	def=PIEMakeMaterial(PIEMakeColor(255,0,0,0),PIEMakeColor(255,255,255,255),PIEMakeColor(255,0,0,0),PIEMakeColor(255,0,0,0),0.0f);
	if (!PIEReadFile(file,&a			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&r			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&g			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&b			,1,&rr,NULL)) return def;
	m.Ambient=PIEMakeColor(a,r,g,b);
	if (!PIEReadFile(file,&a			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&r			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&g			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&b			,1,&rr,NULL)) return def;
	m.Diffuse=PIEMakeColor(a,r,g,b);
	if (!PIEReadFile(file,&a			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&r			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&g			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&b			,1,&rr,NULL)) return def;
	m.Specular=PIEMakeColor(a,r,g,b);
	if (!PIEReadFile(file,&a			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&r			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&g			,1,&rr,NULL)) return def;
	if (!PIEReadFile(file,&b			,1,&rr,NULL)) return def;
	m.Emissive=PIEMakeColor(a,r,g,b);
	if (!PIEReadFile(file,&m.Power ,4,&rr,NULL)) return def;
	/*if (!PIEReadFile(file,&a,1,&rr,NULL);
	if (!PIEReadFile(file,&r,1,&rr,NULL);
	PIEReadFile(file,&g,1,&rr,NULL);
	PIEReadFile(file,&b,1,&rr,NULL);
	m.Ambient=PIEMakeColor(a,r,g,b);
	PIEReadFile(file,&a,1,&rr,NULL);
	PIEReadFile(file,&r,1,&rr,NULL);
	PIEReadFile(file,&g,1,&rr,NULL);
	PIEReadFile(file,&b,1,&rr,NULL);
	m.Diffuse=PIEMakeColor(a,r,g,b);
	PIEReadFile(file,&a,1,&rr,NULL);
	PIEReadFile(file,&r,1,&rr,NULL);
	PIEReadFile(file,&g,1,&rr,NULL);
	PIEReadFile(file,&b,1,&rr,NULL);
	m.Specular=PIEMakeColor(a,r,g,b);
	PIEReadFile(file,&a,1,&rr,NULL);
	PIEReadFile(file,&r,1,&rr,NULL);
	PIEReadFile(file,&g,1,&rr,NULL);
	PIEReadFile(file,&b,1,&rr,NULL);
	m.Emissive=PIEMakeColor(a,r,g,b);
	PIEReadFile(file,&m.Power,4,&rr,NULL);*/
	return m;
//	ecvt
}
LPDIRECT3D9 PIECreate3D()
{
	return Direct3DCreate9(D3D_SDK_VERSION);
}
BOOL PIEInitDirect3D(HWND hwnd,LPDIRECT3D9 pd3d,LPDIRECT3DDEVICE9 *d3dd,D3DPRESENT_PARAMETERS d3dp,DWORD vp,D3DDEVTYPE dt)
{
    if( FAILED( pd3d -> CreateDevice( D3DADAPTER_DEFAULT, dt, hwnd,
                                      vp,
                                      &d3dp, d3dd ) ) )
									  return 0;
	return 1;
}
void PIESetParams(D3DPRESENT_PARAMETERS *d3dp,HWND hwnd,D3DFORMAT BackBufferFormat,int Width,int Height,int RefreshRate,bool Windowed,
	short int BackBufferCount,D3DMULTISAMPLE_TYPE MultiSampleType,DWORD MultiSamleQuality)
{
	ZeroMemory(d3dp,sizeof(D3DPRESENT_PARAMETERS));
	d3dp->Windowed=Windowed;
	d3dp->BackBufferFormat				= BackBufferFormat;
	d3dp->Windowed						= Windowed;
	d3dp->BackBufferCount				= BackBufferCount;
	d3dp->BackBufferWidth				= Width;
	d3dp->BackBufferHeight				= Height;
	d3dp->SwapEffect					= D3DSWAPEFFECT_DISCARD;
	d3dp->hDeviceWindow					= hwnd;
//    d3dp.SwapEffect					= D3DSWAPEFFECT_DISCARD;
//	d3dpp.BackBufferFormat				= D3DFMT_UNKNOWN;
    d3dp->EnableAutoDepthStencil		= TRUE;
	d3dp->AutoDepthStencilFormat		= D3DFMT_D32;
	d3dp->PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;
//	d3dp.EnableAutoDepthStencil			= TRUE;
//	d3dp.AutoDepthStencilFormat			= D3DFMT_D32;
	d3dp->MultiSampleType				= MultiSampleType;//D3DMULTISAMPLE_NONMASKABLE;//D3DMULTISAMPLE_NONE;
	d3dp->MultiSampleQuality			= MultiSamleQuality;
	d3dp->Flags							= 2;
	d3dp->FullScreen_RefreshRateInHz	= D3DPRESENT_RATE_DEFAULT;
}
//<--Matrices-->
void PIETransform(LPDIRECT3DDEVICE9 d3dd,D3DTRANSFORMSTATETYPE t,D3DXMATRIX *Matrix)
{
	d3dd->SetTransform(t,Matrix);
}
void PIESetCamera(LPDIRECT3DDEVICE9 d3dd,D3DXVECTOR3 Eye,D3DXVECTOR3 At,D3DXVECTOR3 Up,FLOAT FieldOfView,
									  FLOAT Aspect,FLOAT ZNear,FLOAT ZFar)
{
	D3DXMATRIXA16 MP;
    D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH( &matView, &Eye, &At, &Up );
    PIETransform(d3dd, D3DTS_VIEW, &matView );
	D3DXMatrixPerspectiveFovLH(&MP,FieldOfView,Aspect,ZNear,ZFar);
	PIETransform(d3dd,D3DTS_PROJECTION,&MP);
}
//<--Light-->
void PIECreateLight(D3DLIGHT9 *Light,D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
										D3DVECTOR Direction,D3DVECTOR Position,float Fallof,float Phi,float Range,
										float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled)
{
	Light->Ambient=Ambient;
	Light->Attenuation0=Attenuation0;
	Light->Attenuation1=Attenuation1;
	Light->Attenuation2=Attenuation2;
	Light->Diffuse=Diffuse;
	Light->Direction=Direction;
	Light->Falloff=Fallof;
	Light->Phi=Phi;
	Light->Position=Position;
	Light->Range=Range;
	Light->Specular=Specular;
	Light->Theta=Theta;
	Light->Type=Type;
}
void PIESetLight(LPDIRECT3DDEVICE9 d3dd,D3DLIGHT9 Light,DWORD Index,bool Enabled)
{
	d3dd->SetLight(Index,&Light);
	d3dd->LightEnable(Index,Enabled);
}
//<--Windows-->
HWND PIECreateWindow(HINSTANCE hinst,DWORD Style,DWORD dwStyle,char* ClassName,char* Caption,int X,int Y,int Width,int Height,bool ShowCursor)
{
	HWND hwnd;
	if (!ShowCursor) SetCursor(NULL);//
	if (!(hwnd = CreateWindowEx(Style, L"PIEWndClass",
		L"pie",dwStyle,X,Y,Width,Height,NULL,NULL,hinst,NULL)))
	{
			return NULL;
	}
	return hwnd; 
}
bool PIERegisterWNDClass(HINSTANCE hinst,UINT style,WNDPROC WndProc,char* ClassName,HICON Icon)
{
	WNDCLASSEX wc = {sizeof(WNDCLASSEX), style, (WNDPROC)WndProc, 0L, 0L,
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		L"123123213", NULL
	};
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hIcon=Icon;
	if (!(RegisterClassEx(&wc))){
		return 0;
	}
	return 1;
}
//And now.....<--Models-->!!!!
bool ReadHeader(HANDLE file,Header* h)
{
	char b;
	DWORD r;
	PIEReadFile(file,&b,1,&r,NULL);
	if (b!='P')
        return 0;	
	PIEReadFile(file,&b,1,&r,NULL);
	if (b!='I')
        return 0;	
	PIEReadFile(file,&b,1,&r,NULL);
	if (b!='E')
        return 0;	
	if (!PIEReadFile(file,&h->Version			,1,&r,NULL)) return 0;
/*	if (!PIEReadFile(file,&a			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&rr			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&g			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&b			,1,&r,NULL)) return 0;
	h->mat.Ambient=PIEMakeColor(a,rr,g,b);
	if (!PIEReadFile(file,&a			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&rr			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&g			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&b			,1,&r,NULL)) return 0;
	h->mat.Diffuse=PIEMakeColor(a,rr,g,b);
	if (!PIEReadFile(file,&a			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&rr			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&g			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&b			,1,&r,NULL)) return 0;
	h->mat.Specular=PIEMakeColor(a,rr,g,b);
	if (!PIEReadFile(file,&a			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&rr			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&g			,1,&r,NULL)) return 0;
	if (!PIEReadFile(file,&b			,1,&r,NULL)) return 0;
	h->mat.Emissive=PIEMakeColor(a,rr,g,b);
	if (!PIEReadFile(file,&h->mat.Power ,4,&r,NULL)) return 0;*/
	if (!PIEReadFile(file,&h->mn				,1,&r,NULL)) return 0;
	for (BYTE i=0;i<h->mn;i++)
	{
		if (!PIEReadFile(file,&h->vnum[i]		,4,&r,NULL)) return 0;
		if (!PIEReadFile(file,&h->fnum[i]		,4,&r,NULL)) return 0;
		h->mat[i]=PIEReadMaterial(file);
		h->totalfnum+=h->fnum[i];
		h->totalvnum+=h->vnum[i];
//		if (!PIEReadFile(file,&h->offset[i]		,4,&r,NULL)) return 0;
	}
	return 1;
	
}
bool ReadChunkHeader(HANDLE file,ChunkHeader *h)
{
	DWORD rr;
	PIEReadFile(file,&h->ID,2,&rr,NULL);
	if (rr!=2)
	{
		return 0;
	}
	PIEReadFile(file,&h->Length,4,&rr,NULL);
	if (rr!=4)
	{
		return 0;
	}
	return 1;
}
float cang(Vector3 v0,Vector3 v1)
{
	return RadToDeg(acos(v0*v1));
}
inline FLOAT Abs(FLOAT x)
{
	if (x<0)
		return -x;
	return x;
}
inline bool Compare(Vector3 x,Vector3 y)
{
	if (Abs(x.x-y.x)>vertexthreshold)
		return 0;
	if (Abs(x.y-y.y)>vertexthreshold)
		return 0;
	if (Abs(x.z-y.z)>vertexthreshold)
		return 0;
	return 1;
}
inline bool Compare(Vector2 x,Vector2 y)
{
	if (Abs(x.x-y.x)>texturethreshold)
		return 0;
	if (Abs(x.y-y.y)>texturethreshold)
		return 0;
	return 1;
}
void Put(WORD index,Vector3 x)
{
	for (DWORD i=0;i<__vnum;i++)
	{
		if (Compare(x,tvert[i]))
		{
			tvertex[index]=i;
			return;
		}
	}
	tvert[__vnum]=x;
    tvertex[index]=__vnum;
	__vnum++;
}
inline WORD GetByInd(WORD index)
{
	return tvertex[index];
}
void Clr()
{
	__vnum=0;
	dvnum=0;
}
void PutToStack1(DWORD x, DWORD y, DWORD z)
{
	_stack1[stacksize1][0]=x;
	_stack1[stacksize1][1]=y;
	_stack1[stacksize1][2]=z;
	stacksize1++;
}
void PutToStack(DWORD x, DWORD y, DWORD z)
{
	_stack[stacksize][0]=x;
	_stack[stacksize][1]=y;
	_stack[stacksize][2]=z;
	stacksize++;
}
void _delete(WORD indx)
{
	if (indx<stacksize-1)
	{
		swap(_stack[indx][0],_stack[stacksize-1][0]);
		swap(_stack[indx][1],_stack[stacksize-1][1]);
		swap(_stack[indx][2],_stack[stacksize-1][2]);
	}
	stacksize--;
}
void _delete1(WORD indx)
{
	if (indx<stacksize1-1)
	{
		swap(_stack1[indx][0],_stack1[stacksize1-1][0]);
		swap(_stack1[indx][1],_stack1[stacksize1-1][1]);
		swap(_stack1[indx][2],_stack1[stacksize1-1][2]);
	}
	stacksize1--;
}
void PickGroup()
{
	stacksize1=0;
	Vector3 a=fn[(DWORD)_stack[stacksize-1][2]/3],x=a;
	Vector3 b;
	PutToStack1(_stack[stacksize-1][0],_stack[stacksize-1][1],_stack[stacksize-1][2]);
	if (stacksize==0)return;
	stacksize--;
	if (stacksize==0)return;
	for (WORD i=0;i<stacksize;i++)
	{
		b=fn[(DWORD)_stack[i][2]/3];
		if (cang(a,b)<=anglethreshold)
		{
			x=x+b;
			PutToStack1(_stack[i][0],_stack[i][1],_stack[i][2]);
			_delete(i);
			i--;
		}
	}
	x.Normalise();
	cn=x;
}
WORD AddVertex(WORD ind)
{
	result[dvnum].p=tvert[_stack1[ind][0]];
	result[dvnum].n=cn;
	result[dvnum].tu=txtr[_stack1[ind][1]].x;
	result[dvnum].tv=txtr[_stack1[ind][1]].y;
	dvnum++;
	return dvnum-1;
}
void AddGroup()
{
	while (stacksize1!=0)
	{
		_canweld[0]=1;
		WORD ind1=_stack1[0][1],ind2;
		for (WORD i=1;i<stacksize1;i++)
		{
			ind2=_stack1[i][1];
			if (Compare(txtr[ind1],txtr[ind2]))
				_canweld[i]=1;
			else
				_canweld[i]=0;
		}
		WORD ind=AddVertex(0);
		for (WORD i=0;i<stacksize1;i++)
		{
            if (_canweld[i])
			{
				ic[_fnum+_stack1[i][2]]=ind;
				_delete1(i);
				i--;
			}
		}
	}
}
Vector3 GetNormal(TNode n)
{
	return fn[n.fn/3];
}
/*LIT PickGroup(LIT *node,Vector3 *norm)
{
	LIT res;
	res.push_back(node->front());
	node->remove(res.front());
	TNode x=res.front();
	*norm=Vector3(0.0f,0.0f,0.0f);
	Vector3 v0=GetNormal(x),v1;
	*norm+=v0;
	DWORD c=1;
	for (LIT::iterator i=node->begin();i!=node->end();i++)
	{
		v1=GetNormal(*i);
		if (cang(v0,v1)<=threshold){
			res.push_back(*i);
			*norm+=v1;
			c++;
//			node->remove(res.back());
		}
	}
	for (LIT::iterator i=res.begin();i!=res.end();i++)
	{
			node->remove(*i);
	}
	*norm/=(SCALAR)c;
/*	TNode *nod=node;
	Add(res,nod->fn,nod->vn);
	len--;
	Del(node,0);
	return res;
}*/
DWORD ReadChunk(HANDLE file)
{
	if (_pos1==GetFileSize(file,NULL))
		return 0;
	ChunkHeader h;
	ZeroMemory(&h,sizeof(ChunkHeader));
	if (!ReadChunkHeader(file,&h))
		return 0;
	_pos1=_pos1+6;
	if (h.ID==MAIN_3DS)
	{
		ReadChunk(file);
		return 0;
	}
	if (h.ID==EDIT_3DS)
	{
		ReadChunk(file);
		return 0;
	}
	if (h.ID==EDIT_OBJECT)
	{
		char buff=1;
		DWORD i=0;
		while (buff!=0)
		{
			PIEReadFile(file,&buff,1,&rr,NULL);
			i++;
		}
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==OBJ_TRIMESH)
	{
		pc++;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==TRI_VERTEXLIST)
	{
		if (pc>1)
			return 0;
		Vector3 pp;
		PIEReadFile(file,&nv,2,&rr,NULL);
		Clr();
//		TVertex3D *buff=new TVertex3D[_vnum+nv];
//		if (_vnum>0) memcpy(buff,va,_vnum*sizeof(TVertex3D));
//		DELETE(va);
//		va=new TVertex3D[_vnum+nv];
//		memcpy(va,buff,_vnum*sizeof(TVertex3D));
//		DELETE(buff);
		for (WORD i=0;i<nv;i++)
		{
			PIEReadFile(file,&pp.x,4,&rr,NULL);
			PIEReadFile(file,&pp.z,4,&rr,NULL);
			PIEReadFile(file,&pp.y,4,&rr,NULL);
			Put(i,pp);
		}
//		voffsets[pc-1]=_vnum;
//		_vnum+=nv;
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==TRI_FACELIST)
	{
		ccc=0;
        PIEReadFile(file,&nf,2,&rr,NULL);
//		DWORD *buff=new DWORD[(_fnum+nf)*3];
//		if (_fnum>0) memcpy(buff,ic,_fnum*6);
//		DELETE(ic);
//		ic=new WORD[(_fnum+nf)*3];
		ic=new WORD[nf*3];
//		memcpy(ic,buff,_fnum*2);
//		DELETE(buff);
		DWORD tempt;
		DELETE(fn);
		fn=new Vector3[nf];
		foffsets[pc-1]=_fnum;
		for (DWORD i=0;i<nf*3;i+=3)
		{
			WORD b=0;
			PIEReadFile(file,&b,2,&rr,NULL);
			ic[_fnum+i]=b;
			fbuff[i]=GetByInd(b);
			PIEReadFile(file,&b,2,&rr,NULL);
			ic[_fnum+i+1]=b;
			fbuff[i+1]=GetByInd(b);
			PIEReadFile(file,&b,2,&rr,NULL);
			ic[_fnum+i+2]=b;
			fbuff[i+2]=GetByInd(b);
/*			PIEReadFile(file,&ic[_fnum+i+1],2,&rr,NULL);
			PIEReadFile(file,&ic[_fnum+i+2],2,&rr,NULL);*/
			PIEReadFile(file,&tempt,2,&rr,NULL);
			if (INv)
				fn[(DWORD)i/3]=CalcNorm(tvert[fbuff[i+2]],tvert[fbuff[i+1]],tvert[fbuff[i]]);
			else
				fn[(DWORD)i/3]=CalcNorm(tvert[fbuff[i]],tvert[fbuff[i+1]],tvert[fbuff[i+2]]);
/*				fn[(DWORD)i/3]=CalcNorm(va[ic[i+2]].p,va[ic[i+1]].p,va[ic[i]].p);
			else
				fn[(DWORD)i/3]=CalcNorm(va[ic[i]].p,va[ic[i+1]].p,va[ic[i+2]].p);*/
		}
		for (DWORD i=0;i<__vnum;i++)
		{
			stacksize=0;
			for (DWORD j=_fnum*3;j<(nf)*3;j+=3)
			{
				if (fbuff[j+0]==i)
				{
                    PutToStack(i,ic[j+0],j+0);
				}
				if (fbuff[j+1]==i)
				{
                    PutToStack(i,ic[j+1],j+1);
				}
				if (fbuff[j+2]==i)
				{
                    PutToStack(i,ic[j+2],j+2);
				}
			}
			while (stacksize!=0)
			{
				PickGroup();
				AddGroup();
			}
		}
//		TVertex3D *buff1=new TVertex3D[_vnum+dvnum];
//		if (_vnum>0) memcpy(buff1,va,_vnum*sizeof(TVertex3D));
//		DELETE(va);
		va=new TVertex3D[dvnum];
//		memcpy(va,buff1,_vnum*sizeof(TVertex3D));
//		DELETE(buff1);
		*bboxmin=result[0].p;
		*bboxmax=result[0].p;
		for (WORD i=0;i<dvnum;i++)
		{
			memcpy(&va[i],&result[i],32);
			bboxmin->x=min(result[i].p.x,bboxmin->x);
			bboxmin->y=min(result[i].p.y,bboxmin->y);
			bboxmin->z=min(result[i].p.z,bboxmin->z);
			bboxmax->x=max(result[i].p.x,bboxmax->x);
			bboxmax->y=max(result[i].p.y,bboxmax->y);
			bboxmax->z=max(result[i].p.z,bboxmax->z);
		}
		_vnum+=dvnum;
/*		LITC nota;
		for (DWORD i=voffsets[pc-1];i<_vnum;i++)
		{
			len=0;
			TNode val;
            for (DWORD j=_fnum*3;j<(_fnum+nf)*3;j+=3)
			{
				val.fn=j;
				if (ic[j+0]==i)
				{
					val.vn=0;
					main.push_back(val);
					len++;
				}
				if (ic[j+1]==i)
				{
					val.vn=1;
					main.push_back(val);
					len++;
				}
				if (ic[j+2]==i)
				{
					val.vn=2;
					main.push_back(val);
					len++;
				}
			}
			//DWORD c=0;
			LIT group;
			Vector3 nnn;
			group=PickGroup(&main,&nnn);
			va[i].n=nnn;
			group.erase(group.begin(),group.end());
			while (main.size()!=0)
			{
				group=PickGroup(&main,&nnn);
				ToCh ttt;
				ttt.ind=i;
				ttt.Normal=nnn;
				nota.push_back(ttt);
				for (DWORD k=0;k<group.size();k++)
				{
					TNode tttt=group.front();
					group.pop_front();
					ic[tttt.fn+tttt.vn]=_vnum+ccc;
				}
				ccc++;
			}

		}
		if (ccc>0){
			TVertex3D *buff1=new TVertex3D[_vnum];
			if (_vnum>0) memcpy(buff1,va,_vnum*sizeof(TVertex3D));
			DELETE(va);
			va=new TVertex3D[_vnum+ccc];
			memcpy(va,buff1,_vnum*sizeof(TVertex3D));
			DELETE(buff);
			for (DWORD i=_vnum;i<_vnum+ccc;i++)
			{
				ToCh b=nota.front();
				nota.pop_front();
				va[i].n=b.Normal;
				va[i].p=va[b.ind].p;
				va[i].tu=va[b.ind].tu;
				va[i].tv=va[b.ind].tv;
			}
			_vnum+=ccc;
		}*/
		_fnum+=nf;
		DELETE(fn);
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==TRI_MAPPINGCOORS)
	{
		WORD tempt;
		PIEReadFile(file,&tempt,2,&rr,NULL);
		for (WORD i=0;i<tempt;i++)
		{
			PIEReadFile(file,&txtr[i].x,4,&rr,NULL);
			PIEReadFile(file,&txtr[i].y,4,&rr,NULL);
			txtr[i].y=1.0f-txtr[i].y;
		}
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_MAIN)
	{
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_NAME)
	{
		char buff=1;
		DWORD i=6;
		if (mc==pc)
			skipmat=true;
		else
			skipmat=false;
		if (mc==0)
			skipmat=false;
		if (!skipmat){
			_mat[mc].Emissive.a=0;
			_mat[mc].Emissive.r=0;
			_mat[mc].Emissive.g=0;
			_mat[mc].Emissive.b=0;
			mc++;
			while (buff!=0||h.Length>i)
			{
				PIEReadFile(file,&buff,1,&rr,NULL);
				i++;
			}
		}
		else
		{
			while (buff!=0||h.Length>i)
			{
				PIEReadFile(file,&buff,1,&rr,NULL);
				i++;
			}
		}
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_AMBIENT)
	{
		BYTE r=0,g=0,b=0;
		ChunkHeader a;
		ReadChunkHeader(file,&a);
		PIEReadFile(file,&r,1,&rr,NULL);
		PIEReadFile(file,&g,1,&rr,NULL);
		PIEReadFile(file,&b,1,&rr,NULL);
		if (!skipmat)
			_mat[mc-1].Ambient=PIEMakeColor(255,r,g,b);
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_DIFFUSE)
	{
		BYTE r=0,g=0,b=0;
		ChunkHeader a;
		ReadChunkHeader(file,&a);
		PIEReadFile(file,&r,1,&rr,NULL);
		PIEReadFile(file,&g,1,&rr,NULL);
		PIEReadFile(file,&b,1,&rr,NULL);
		if (!skipmat)
		_mat[mc-1].Diffuse=PIEMakeColor(255,r,g,b);
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_SPECULAR)
	{
		BYTE r=0,g=0,b=0;
		ChunkHeader a;
		ReadChunkHeader(file,&a);
		PIEReadFile(file,&r,1,&rr,NULL);
		PIEReadFile(file,&g,1,&rr,NULL);
		PIEReadFile(file,&b,1,&rr,NULL);
		if (!skipmat)
		_mat[mc-1].Specular=PIEMakeColor(255,r,g,b);
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_SHININESS)
	{
		WORD buff;
		ChunkHeader a;
		ReadChunkHeader(file,&a);
		PIEReadFile(file,&buff,2,&rr,NULL);
		if (!skipmat)
		_mat[mc-1].Power=buff;
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_OPAQUE)
	{
		WORD buff;
		ChunkHeader a;
		ReadChunkHeader(file,&a);
		PIEReadFile(file,&buff,2,&rr,NULL);
		if (!skipmat)
		_mat[mc-1].Diffuse.a=(float)(100-buff)/100;
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	if (h.ID==MAT_TEXTURE_NAME)
	{
		BYTE buff=1;
		WORD i=6;
//		ReadChunkHeader(file,&a);
		if (!skipmat)
			while (i<h.Length)
			{
				PIEReadFile(file,&buff,1,&rr,NULL);
				tfnames[tfpos]=buff;
				tfpos++;
				i++;
			}
		else
			while (i<h.Length)
			{
				PIEReadFile(file,&buff,1,&rr,NULL);
				i++;
			}
		_pos1+=h.Length-6;
		ReadChunk(file);
		return 0;
	}
	PIESkipBytes(file,h.Length-6);
	_pos1+=h.Length-6;
	ReadChunk(file);
	return 0;
}
/*Vector3 vtv(TVertex3D a)
{
	return Vector3(a.x,a.y,a.z);
}*/
void GetBBox(LPCSTR fname,float *mx,float *my,float *mz,float *_mx,float *_my,float *_mz)
{
	HANDLE modf=PIEOpenFile(fname,1);
	anglethreshold=60;
	vertexthreshold=0.01f;
	texturethreshold=0.0f;
	INv=0;
	bboxmin=NULL;
	bboxmin=new Vector3;
	bboxmax=NULL;
	bboxmax=new Vector3;


	ReadChunk(modf);


	*mx=bboxmin->x;
	*my=bboxmin->y;
	*mz=bboxmin->z;
	*_mx=bboxmax->x;
	*_my=bboxmax->y;
	*_mz=bboxmax->z;
	delete bboxmin;
	delete bboxmax;
	PIECloseFile(modf);
}


BOOL PIELoadModel (LPCSTR fname,DWORD ModelKind,
											   DWORD *vnum,DWORD *fnum,D3DMATERIAL9 *mat,
											   WORD **IndexData,LPVOID VertexData,
											   Vector3 *Min,Vector3 *Max,
											   FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals)
{
	//0 means GTM file
	//1 means 3ds file
	//2 means obj file may be later
	//3 May be later...^_^ T_T o_O O_o O_O o_o !_!
	bboxmin=Min;
	bboxmax=Max;
	HANDLE modf=PIEOpenFile(fname,1);
	anglethreshold=athres;
	vertexthreshold=vthres;
	texturethreshold=txtrthres;
	INv=InvertNormals;
	if (ModelKind==0)
	{
		Header head;
		DWORD rr;
		ZeroMemory(&head,sizeof(head));
		if (!ReadHeader(modf,&head)){
			PIECloseFile(modf);
			return 0;
		}
//		*ModelNumber=head.mn;
		memcpy(vnum,head.vnum,4*head.mn);
		memcpy(fnum,head.fnum,4*head.mn);
		memcpy(mat,head.mat,sizeof(D3DMATERIAL9)*head.mn);
		//Now reading index data(that's fun=) 
		DWORD *indic=new DWORD[head.totalfnum*3];
		//Loading vertex data:3
		for (DWORD i=0;i<head.totalfnum;i++)
		{
			if (!PIEReadFile(modf,&indic[i*3]  ,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&indic[i*3+1],4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&indic[i*3+2],4,&rr,NULL)) return 0;
		}
		memcpy(IndexData,indic,12*head.totalfnum);
		TVertex3D *data=new TVertex3D[head.totalvnum*sizeof(TVertex3D)];
		for (DWORD i=0;i<head.totalvnum;i++)
		{
			if (!PIEReadFile(modf,&data[i].p.x		,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&data[i].p.y		,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&data[i].p.z		,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&data[i].n.x		,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&data[i].n.y		,4,&rr,NULL)) return 0;
			if (!PIEReadFile(modf,&data[i].n.z		,4,&rr,NULL)) return 0;
			if (head.Textured){
				if (!PIEReadFile(modf,&data[i].tu	,4,&rr,NULL)) return 0;
				if (!PIEReadFile(modf,&data[i].tv	,4,&rr,NULL)) return 0;
			}
			else
			{
				data[i].tu=0.0f;
				data[i].tv=0.0f;
			}
		}
	}
	if (ModelKind==1)
	{
		pc=0;
		mc=0;
		_fnum=0;
		_vnum=0;
		skipmat=0;
		tfpos=0;
		if (ic)
			delete[] ic;
		if (va)
			delete[] va;
		ic=NULL;
		va=NULL;
		ZeroMemory(tvertex,sizeof(tvertex));
		ZeroMemory(tvert,sizeof(tvert));
		ZeroMemory(txtr,sizeof(txtr));
		ZeroMemory(result,sizeof(result));
		ZeroMemory(fbuff,sizeof(fbuff));
		ZeroMemory(_stack,sizeof(_stack));
		ZeroMemory(_stack1,sizeof(_stack1));
		ZeroMemory(_canweld,sizeof(_canweld));
		ZeroMemory(&_mat,256*sizeof(D3DMATERIAL9));
		ZeroMemory(&tfnames,2048);
		bboxmin=Min;
		bboxmax=Max;
		_mat[0].Ambient=_mat[0].Specular=_mat[0].Emissive=PIEMakeColor(0,0,0,0);
		_mat[0].Diffuse=PIEMakeColor(255,128,128,128);
//		if (va!=NULL)
//			Delete(va);
//		if (ic!=NULL)
//			Delete(ic);
        ReadChunk(modf);
/*		for (DWORD i=0;i<_vnum;i++)
		{
			WORD c=0;
			Vector3 res=Vector3(0.0f,0.0f,0.0f);
			for (DWORD j=0;j<_fnum*3;j+=3)
			{
                if (ic[j]==i)
				{
					res+=fn[(DWORD)j/3];
					c++;
				}
                if (ic[j+1]==i)
				{
					res+=fn[(DWORD)j/3];
					c++;
				}
                if (ic[j+2]==i)
				{
					res+=fn[(DWORD)j/3];
					c++;
				}
			}
			if (c!=0)
				res/=c;
			else
				res=Vector3(1.0f,0.0f,0.0f);
			va[i].n=res;
		}*/
//		Delete(fn);
/*		memcpy(VertexData,va,_vnum*sizeof(TVertex3D));
		memcpy(IndexData,ic,_fnum*12);*/
		*IndexData=ic;
		memcpy(VertexData,&va,8);
//		VertexData=va;
		if (mc==0)
			mc=1;
		memcpy(mat,_mat,sizeof(D3DMATERIAL9));
		*fnum=_fnum;
		*vnum=_vnum;
	}
	if (ModelKind==2)
	{
	}
//	memcpy(offset,head.offset,4*head.mn);
	return PIECloseFile(modf);
}
LPDIRECT3DINDEXBUFFER9 PIECreateIndexBuffer(LPDIRECT3DDEVICE9 d3dd,WORD *indices,DWORD fnum,LPDIRECT3DINDEXBUFFER9 ind)
{
	LPDIRECT3DINDEXBUFFER9 _ind=NULL;
	if (ind) {ind->Release();}
	d3dd->CreateIndexBuffer(fnum*3*sizeof(WORD), D3DUSAGE_WRITEONLY
		, D3DFMT_INDEX16 , D3DPOOL_MANAGED, &_ind,NULL);// | D3DUSAGE_DYNAMIC D3DPOOL_DEFAULT
	VOID *data;
	_ind->Lock(0,fnum*3*sizeof(WORD),(void**)&data,0);
	memcpy(data,indices,3*sizeof(WORD)*fnum);
	_ind->Unlock();
	return _ind;
}
LPDIRECT3DVERTEXBUFFER9 PIECreateVertexBuffer(LPDIRECT3DDEVICE9 d3dd,LPVOID vertices,DWORD vnum,DWORD FVF,DWORD size,LPDIRECT3DVERTEXBUFFER9 vb)
{
	LPDIRECT3DVERTEXBUFFER9 _vb=NULL;
	if (vb) vb->Release();
	if (FAILED(d3dd->CreateVertexBuffer(vnum*size, D3DUSAGE_WRITEONLY | D3DUSAGE_DYNAMIC, FVF , D3DPOOL_DEFAULT, &_vb,NULL))) return 0;
	VOID *data;
	if (FAILED(_vb->Lock(0,vnum*size,(void**)&data,D3DLOCK_NOSYSLOCK | D3DLOCK_DISCARD))) return 0;
	memcpy(data,vertices,vnum*size);
	_vb->Unlock();
	return _vb;
}
void D3DMtoM3M(D3DXMATRIX m,Matrix3x3 *res)
{
	*res=Matrix3x3(Vector3(m(0,0),m(1,0),m(2,0)),Vector3(m(0,1),m(1,1),m(2,1)),Vector3(m(0,2),m(1,2),m(2,2)));
//	*res=Matrix3x3(Vector3(m(0,0),m(0,1),m(0,2)),Vector3(m(1,0),m(1,1),m(1,2)),Vector3(m(2,0),m(2,1),m(2,2)));
}
/*BOOL PIEGetModelData (HANDLE modf,BYTE ModelKind,BYTE ModelNumber,
											   DWORD vnum,DWORD fnum,DWORD offset,LPVOID dest)
{
	return 1;
}
BOOL PIEEndModelProcess (HANDLE modf){
	return CloseHandle(modf);
}*/
