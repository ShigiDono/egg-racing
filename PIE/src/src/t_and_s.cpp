#include"stdafx.h"
#include"t_and_s.h"
LPDIRECT3DDEVICE9 td3dd=NULL;
char _tszAppPath[MAX_PATH];
int cnt=0;
LPDIRECT3DTEXTURE9 Null_texture=NULL;
__forceinline DWORD D3DColor(DWORD c24)
{
	return D3DCOLOR_XRGB(GetRValue(c24),GetGValue(c24),GetBValue(c24));
}
void THAssignDevice(LPDIRECT3DDEVICE9 _d3dd,char *CDir)
{
	td3dd=_d3dd;
	strcpy(_tszAppPath,CDir);
	RELEASE(Null_texture);
//	D3DXCreateTexture(td3dd,1,1,D3DX_DEFAULT, 0, D3DFMT_UNKNOWN, D3DPOOL_MANAGED, &Null_texture);
//	D3DLOCKED_RECT lr;
//	Null_texture->LockRect(0,&lr,NULL,D3DLOCK_DISCARD);
//	Null_texture->UnlockRect(0);
}
LPDIRECT3DDEVICE9	__GetDevice()
{
	return td3dd;
}
CTexture::CTexture()
{
	ZeroMemory(this,sizeof(CTexture));
	Pool=D3DPOOL_MANAGED;
}
void CTexture::SetStage(D3DTEXTURESTAGESTATETYPE type,DWORD Value)
{
	td3dd->SetTextureStageState(0,type,Value);
}
DWORD Blend(DWORD Color1,DWORD Color2)//Color1 - is the upper
{
	float Val=(float)GetAValue(Color1)/255;
	short int a=255;//GetAValue(Color1)*Val+GetAValue(Color2)*(1-Val);
	short int r=GetRValue(Color1)*Val+GetRValue(Color2)*(1-Val);
	short int g=GetGValue(Color1)*Val+GetGValue(Color2)*(1-Val);
	short int b=GetBValue(Color1)*Val+GetBValue(Color2)*(1-Val);
	return D3DCOLOR_ARGB(a,b,g,r);
}
bool CopyBytes(LPDIRECT3DTEXTURE9 _txt,BYTE* data,DWORD texturew,DWORD textureh,DWORD tilew,DWORD tileh,DWORD tnum)
{
	D3DLOCKED_RECT lr;
	if (FAILED(_txt->LockRect(0,&lr,NULL,D3DLOCK_DISCARD)))
		return 0;
	{
		//copying data

		/*	^_^_^_^_^_^_^_^_^_^ */
//		  |						  |
//		 /|\					 /|\
		//|\\ {o_O} {x_x} {O_o} //|\\
//		|---|^^^^^^^^^^^^^^^^^^^|---|
//		| O	|^^^^^|		  |^^^^^| O	|
//		|	|  #  |	O	O |	 #	|	|
//		| #	|	  |_______|	  H	| #	|
//		|	|	 /#########\  H	|	|
//		| #	|	|###########| H | #	|
//		|___|___|\#########/|_H_|___|
/////\////////////.....\/..//////\///////// <-this is grass
/////////\///////..........///\////////////
//////////////////..\/......///////////////
//really...
		//:3
		//T_T
		//let's go)
		//go go go...
		//go go...
		//go...
		//go to hell!!!!
		//=)
		//hmmmm....
		//i'm so lazy
		//so lazy....
		//so laZzzzzy.....
		DWORD y1=tnum/texturew,x1=tnum%texturew;
		BYTE *_data=(BYTE*)lr.pBits;
		for (DWORD i=0;i<tileh;i++){
			memcpy(_data+i*tilew*4,data+((y1*texturew*tileh*tilew+x1*tilew+i*texturew*tilew)*4),tilew*4);//((y1*tilew*tileh*texturew)+x1*tilew+i*tilew*texturew)*4
		}
	}
	_txt->UnlockRect(0);
	return 1;
}
bool _CopyBytes(LPDIRECT3DTEXTURE9 _txt,BYTE* data,DWORD texturew,DWORD textureh,DWORD tilew,DWORD tileh,DWORD tnum)
{
	D3DLOCKED_RECT lr;
	if (FAILED(_txt->LockRect(0,&lr,NULL,D3DLOCK_READONLY)))
		return 0;
	{
		//copying data

		/*	^_^_^_^_^_^_^_^_^_^ */
//		  |						  |
//		 /|\					 /|\
		//|\\ {o_O} {x_x} {O_o} //|\\
//		|---|^^^^^^^^^^^^^^^^^^^|---|
//		| O	|^^^^^|		  |^^^^^| O	|
//		|	|  #  |	O	O |	 #	|	|
//		| #	|	  |_______|	  H	| #	|
//		|	|	 /#########\  H	|	|
//		| #	|	|###########| H | #	|
//		|___|___|\#########/|_H_|___|
/////\////////////.....\/..//////\///////// <-this is grass
/////////\///////..........///\////////////
//////////////////..\/......///////////////
//really...
		//:3
		//T_T
		//let's go)
		//go go go...
		//go go...
		//go...
		//go to hell!!!!
		//=)
		//hmmmm....
		//i'm so lazy
		//so lazy....
		//so laZzzzzy.....
		DWORD y1=tnum/texturew,x1=tnum%texturew;
		BYTE *_data=(BYTE*)lr.pBits;
		for (DWORD i=0;i<tileh;i++){
			memcpy(data+((y1*texturew*tileh*tilew+x1*tilew+i*texturew*tilew)*4),_data+i*tilew*4,tilew*4);//((y1*tilew*tileh*texturew)+x1*tilew+i*tilew*texturew)*4
		}
	}
	_txt->UnlockRect(0);
	return 1;
}
char *GetDir()
{
	return _tszAppPath;
}
DWORD BlendC(DWORD Color1,DWORD Color2,float Val)
{
	short int a=GetAValue(Color1)*Val+GetAValue(Color2)*(1-Val);
	short int r=GetRValue(Color1)*Val+GetRValue(Color2)*(1-Val);
	short int g=GetGValue(Color1)*Val+GetGValue(Color2)*(1-Val);
	short int b=GetBValue(Color1)*Val+GetBValue(Color2)*(1-Val);
	return D3DCOLOR_ARGB(a,b,g,r);
}
bool CTexture::LoadFromFile(LPCSTR Fname)
{
/*	char temp[MAX_PATH];
	ZeroMemory(temp,sizeof(temp));
	strcpy(temp,_tszAppPath);
	strcat(temp,Fname);
	strcpy(FName,Fname);
	if (!FileExists(temp))
		return 0;
	Created=1;
	return SUCCEEDED(D3DXCreateTextureFromFile(td3dd,temp,&d3dt));*/
//	WriteMsg("-->text%d",cnt);
//	cnt++;
	char temp[MAX_PATH];
	char temp1[MAX_PATH];
	Created=0;
//	ZeroMemory(FName,sizeof(FName));
	strcpy(FName,Fname);
	strcpy(temp,_tszAppPath);
	strcat(temp,Fname);
	if (!FileExists(temp)){
		PutError("Can't locate texture %s;",temp);
		return 0;
	}
	dtNum=0;
	PFile f=new CPFile;
	{
		f->Open(Fname,FILE_READ);
		{
			//reading header;
			char b;
			f->Read(&b,1);
			if (b!='P')
				return 0;
			f->Read(&b,1);
			if (b!='T')
				return 0;
			f->Read(&b,1);
			if (b!='T')
				return 0;
			//success
		}
		//now loading diffuse map
		//that is it
		{
			f->ReadNullTerminatedString(name);
			//reading name
			ZeroMemory(temp,MAX_PATH);
			ZeroMemory(temp1,MAX_PATH);
			strcpy(temp1,_tszAppPath);
			f->ReadNullTerminatedString(temp);
			strcat(temp1,temp);
			byte b;
			f->Read(&b,1);
			DWORD colorkey=0;
			if (b)
			{
				f->Read(&colorkey,4);
				colorkey=D3DColor(colorkey);
			}
			DWORD tw,th;
			f->Read(&b,1);
			if (b)
			{
				f->Read(&tw,4);
				f->Read(&th,4);
			}
			RELEASE(_ttext);
			_ttext=NULL;
			D3DXIMAGE_INFO Info;
			if (strlen(temp1)==0)
				return 0;
			D3DXGetImageInfoFromFileA(temp1, &Info);
			if (FAILED(D3DXCreateTextureFromFileExA(td3dd, temp1, Info.Width, Info.Height, D3DX_DEFAULT, Usage, D3DFMT_A8R8G8B8, Pool, D3DX_DEFAULT, D3DX_DEFAULT, colorkey, NULL, NULL, &_ttext)))
			{
				PutError("Failed to load %s;",temp1);
				return 0;
			}
			dtNum=1;
			if (b)
			{
				//subdividing it
				//getting number of tiles
				DWORD xt=Info.Width/tw;
				DWORD yt=Info.Height/th;
				dtNum=xt*yt;
				//clearing data
				DELETE(d3ddt);
				//creating array for textures
				d3ddt=new LPDIRECT3DTEXTURE9[xt*yt];
				//building tiles
				D3DLOCKED_RECT lr;
				if (FAILED(_ttext->LockRect(0,&lr,NULL,D3DLOCK_READONLY)))
				{
					_ttext->Release();
					return 0;
				}
				for (DWORD i=0;i<xt*yt;i++)
				{
					if (FAILED(D3DXCreateTexture(td3dd,tw,th,D3DX_DEFAULT, Usage, D3DFMT_A8R8G8B8, Pool, &d3ddt[i]))){
						_ttext->Release();
						for (DWORD j=0;j<i;j++)
						{
							d3ddt[i]->Release();
							DELETE(d3ddt);
						}
						f->Close();
						delete f;
						return 0;
					}
					if (!CopyBytes(d3ddt[i],(BYTE*)lr.pBits,xt,yt,tw,th,i))
					{
						_ttext->Release();
						for (DWORD j=0;j<=i;j++)
						{
							d3ddt[i]->Release();
							DELETE(d3ddt);
						}
						f->Close();
						delete f;
						return 0;
					}
				}
				_ttext->UnlockRect(0);
				_ttext->Release();
				_ttext=NULL;
			}
			else
			{
				d3ddt=&_ttext;
			}
/*HRESULT D3DXCreateTextureFromFileEx(
  LPDIRECT3DDEVICE9 pDevice,
  LPCTSTR pSrcFile,
  UINT Width,
  UINT Height,
  UINT MipLevels,
  DWORD Usage,
  D3DFORMAT Format,
  D3DPOOL Pool,
  DWORD Filter,
  DWORD MipFilter,
  D3DCOLOR ColorKey,
  D3DXIMAGE_INFO * pSrcInfo,
  PALETTEENTRY * pPalette,
  LPDIRECT3DTEXTURE9 * ppTexture
);*/
		}
	}
	f->Close();
	delete f;
	Created=1;
	return 1;
}
void CTexture::SetNullTexture()
{
	td3dd->SetTexture(0,NULL);
}
void CTexture::Release()
{
	for (DWORD i=0;i<dtNum;i++)
	{
		RELEASE(d3ddt[i]);
	}
}
bool CTexture::Reset()
{
    Release();
	return LoadFromFile(FName);
}
void CTexture::SetTexture(DWORD num)
{
//	td3dd->SetTexture(0,d3dt);
	if (d3ddt!=NULL){
		if (num==0&&dtNum==1)
			td3dd->SetTexture(0,*d3ddt);
		else
			td3dd->SetTexture(0,d3ddt[num%dtNum]);
	}
	else
		td3dd->SetTexture(0,NULL);
	return;
}
CSurface::CSurface()
{
	ZeroMemory(this,sizeof(CSurface));
}