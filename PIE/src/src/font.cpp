#include"stdafx.h"
#include"font.h"
DWORD _ScrWidth,_ScrHeight;
LPDIRECT3DDEVICE9 fd3dd;
void FAssign(LPDIRECT3DDEVICE9 _d3dd,DWORD w,DWORD h)
{
	_ScrWidth=w;
	_ScrHeight=h;
	fd3dd=_d3dd;
}
DWORD Blend(DWORD Color1,DWORD Color2,float Val)
{
	short int a=GetAValue(Color1)*Val+GetAValue(Color2)*(1-Val);
	short int r=GetRValue(Color1)*Val+GetRValue(Color2)*(1-Val);
	short int g=GetGValue(Color1)*Val+GetGValue(Color2)*(1-Val);
	short int b=GetBValue(Color1)*Val+GetBValue(Color2)*(1-Val);
	return D3DCOLOR_ARGB(a,b,g,r);
}
/*HRESULT CreateText(LPDIRECT3DVERTEXBUFFER9* Buffer,char* Text,float x0,float y0,float W,float H,int* Size)
{
	LPDIRECT3DVERTEXBUFFER9 Temp;
	if (FAILED(d3dd->CreateVertexBuffer(6*Length(Text)*sizeof(TVertex2D),0,SCREENVERTEX,
		D3DPOOL_SYSTEMMEM,&Temp,NULL))){
		return E_FAIL;
	}
	void** Vrt;
	Temp->Lock(0,4*Length(Text)*sizeof(TVertex2D),(void**)&Vrt,0);
	int i=0;
	float y=0,x=0;
	while (Text[i]!=0){
		if (Text[i]==10){
			y+=LetterWidth;
			x=0;
		}
		else
		{
			float tu,tv,tu1,tv1;
			ComputeTextureCoord(Text[i],&tu,&tv,&tu1,&tv1);
			AddToRectBuffer(&Vrt,ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y+H,0.0f,1.0f),0xFFFFFFFF,
				tu,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y,0.0f,1.0f),0xFFFFFFFF,
				tu,tv),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y+H,0.0f,1.0f),0xFFFFFFFF,
				tu1,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y,0.0f,1.0f),0xFFFFFFFF,
				tu1,tv));
			x+=LetterWidth;
		}
		i++;
	}
	Temp->Unlock();
	*Buffer=Temp;
	*Size=2*Length(Text);
}
	d3dd->SetTexture(0,FONT.Image);
	d3dd->SetFVF(SCREENVERTEX);
	if (Color1==0) Color1=Black;
	if (Color2==0) Color2=Black;
	int i=0;
	float y=0,x=0;
	while (Text[i]!=0&&Text!=NULL){
		if (Text[i]==10){
			y+=(H+spy);
			x=0;
		}
		else
		{
			if (Text[i]==32)
				x+=(W+spx);
			else
			{
				float tu,tv,tu1,tv1;
				ComputeTextureCoord(Text[i],&tu,&tv,&tu1,&tv1);
				if (Grad)
					UpdateRectBuffer(d3dd,&Letter,ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y+H,0.0f,1.0f),Color1,
						tu,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y,0.0f,1.0f),Color1,
						tu,tv),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y+H,0.0f,1.0f),Color2,
						tu1,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y,0.0f,1.0f),Color2,
						tu1,tv));
				else
					UpdateRectBuffer(d3dd,&Letter,ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y+H,0.0f,1.0f),Blend(Color1,Color2,(float)i/Length(Text)),
						tu,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x,y0+y,0.0f,1.0f),Blend(Color1,Color2,(float)i/Length(Text)),
						tu,tv),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y+H,0.0f,1.0f),Blend(Color1,Color2,(float)i/Length(Text)),
						tu1,tv1),ConvertToVertex2D(D3DXVECTOR4( x0+x+W,y0+y,0.0f,1.0f),Blend(Color1,Color2,(float)i/Length(Text)),
						tu1,tv));
				d3dd->SetStreamSource(0,Letter,0,sizeof(TVertex2D));
				d3dd->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);   
				x+=(W+spx);
			}
		}
		i++;
	}
*/
void ComputeTextureCoord(char c,float *tu,float* tv, float* tu1, float* tv1){
	short int k=c;
	if (c<0) 
		k+=256;
	k-=33;
	float ttu=(int)k%15*LetterSpace;
	float ttv=(int)k/15*LetterSpace;
//	if (ttv>2) ttv-=2;
//	ttu=(double)ttu/270;
//	ttv=(double)ttv/270;
	*tu=ttu;
	*tv=ttv;
	*tu1=ttu+LetterSpace;
	*tv1=ttv+LetterSpace;
}
CFont::CFont()
{
	ZeroMemory(this,sizeof(CFont));
	txt=new CTexture;
	rect=new CPRect;
}
bool CFont::LoadFont(LPCSTR Fname)
{
	return txt->LoadFromFile(Fname);
}
void CFont::Release()
{
	txt->Release();
}
bool CFont::Reset()
{
	if (txt->Created)
		return txt->Reset();
	return 1;
}
void CFont::Destroy()
{
	Release();
	delete txt;
	delete rect;
}
void CFont::PDrawTextEx(DWORD lx,DWORD ly,DWORD rx,DWORD ry,DWORD Color1,DWORD Color2,GRADIENT type,LPCSTR Text)
{
	if (Sm)
	{
	    fd3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	    fd3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	    fd3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
	}
	else
	{
	    fd3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_NONE );
	    fd3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_NONE );
	    fd3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
	}
	fd3dd->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	txt->SetTexture(0);
	if (Color1==0) Color1=Black;
	if (Color2==0) Color2=Black;
	int i=0;
	float y=0,x=0;
	DWORD L=0;
	while (Text[L]!=0)
	{
		L++;
	}
	while (Text[i]!=0&&Text!=NULL&&i<L){
		if (Text[i]==10){
			y+=(Height+spy);
			x=0;
		}
		else
		{
			if (Text[i]==32)
				x+=(Width+spx);
			else
			{
				float tu,tv,tu1,tv1;
				ComputeTextureCoord(Text[i],&tu,&tv,&tu1,&tv1);
				switch (type)
				{
				case GR_NONE:
					rect->SetColor(0,Color1);
					rect->SetColor(1,Color1);
					rect->SetColor(2,Color1);
					rect->SetColor(3,Color1);
					break;
				case GR_LEFTRIGHT:
					rect->SetColor(0,Blend(Color2,Color1,(float)i/L));
					rect->SetColor(1,Blend(Color2,Color1,(float)i/L));
					rect->SetColor(2,Blend(Color2,Color1,(float)i/L));
					rect->SetColor(3,Blend(Color2,Color1,(float)i/L));
					break;
				case GR_TOPBOTTOM:
					rect->SetColor(0,Color1);
					rect->SetColor(1,Color1);
					rect->SetColor(2,Color2);
					rect->SetColor(3,Color2);
					break;
				case GR_RIGHTLEFT:
					rect->SetColor(0,Blend(Color1,Color2,(float)i/L));
					rect->SetColor(1,Blend(Color1,Color2,(float)i/L));
					rect->SetColor(2,Blend(Color1,Color2,(float)i/L));
					rect->SetColor(3,Blend(Color1,Color2,(float)i/L));
					break;
				case GR_BOTTOMTOP:
					rect->SetColor(0,Color2);
					rect->SetColor(1,Color2);
					rect->SetColor(2,Color1);
					rect->SetColor(3,Color1);
					break;
				case GR_SPECIAL:
					rect->SetColor(0,Color1);
					rect->SetColor(1,Color2);
					rect->SetColor(2,Color1);
					rect->SetColor(3,Color2);
					break;
				}
				FLOAT x1,y1,x2,y2;
				x1=lx+x;
				x2=lx+x+Width;
				y1=ly+y;
				y2=ly+y+Height;
				bool draw=1;
				if (x1>rx||y1>ry)
					draw=false;
				if (x2>rx){
					x2=rx;
				}
				if (y2>ry){
					y2=ry;
				}
				rect->SetPos(0,Vector3(x1,y1,0.0f));
				rect->SetPos(1,Vector3(x2,y1,0.0f));
				rect->SetPos(2,Vector3(x1,y2,0.0f));
				rect->SetPos(3,Vector3(x2,y2,0.0f));
				rect->SetTCoord(0,tu,tv);
				rect->SetTCoord(1,tu1,tv);
				rect->SetTCoord(2,tu,tv1);
				rect->SetTCoord(3,tu1,tv1);
				if (draw)
				{
					rect->Update();
					rect->Draw();	
				}
				x+=(Width+spx);
			}
		}
		i++;
	}
	txt->SetNullTexture();
}
void CFont::PDrawText(DWORD xpos,DWORD ypos,LPCSTR text)
{
    PDrawTextEx(xpos,ypos,_ScrWidth,_ScrHeight,Color,Color,GR_NONE,text);
}
bool CFont::Create(FLOAT _Width,FLOAT _Height,FLOAT _spx,FLOAT _spy,DWORD _Color,LPCSTR Fname,bool Smooth)
{
	Width=_Width;
	Height=_Height;
	Sm=Smooth;
	spx=_spx;
	spy=_spy;
	Color=_Color;
	return LoadFont(Fname);
}



