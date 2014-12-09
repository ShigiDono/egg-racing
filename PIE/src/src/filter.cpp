#include"stdafx.h"
#include"filter.h"
Matrix5::Matrix5()
{
	ZeroMemory(this,sizeof(Matrix5));
}
void Matrix5::Clear()
{
	ZeroMemory(this,sizeof(Matrix5));
}
void Matrix5::Update()
{
	FLOAT res=0;
	for (BYTE i=0;i<5;i++)
	{
		for (BYTE j=0;j<5;j++)
		{
			res+=data[i][j];
		}
	}
	if (res>1)
	{
		for	(BYTE i=0;i<5;i++)
		{
			for (BYTE j=0;j<5;j++)
			{
				data[i][j]/=res;
			}
		}
	}
}
void Matrix5::Reset()
{
	for (BYTE i=0;i<5;i++)
	{
		for (BYTE j=0;j<5;j++)
		{
			data[i][j]=_data[i][j];
		}
	}
}
void Matrix5::pop()
{
	for (BYTE i=0;i<5;i++)
	{
		for (BYTE j=0;j<5;j++)
		{
			_data[i][j]=data[i][j];
		}
	}
}
void Matrix5::Sqrt()
{
	for (BYTE i=0;i<5;i++)
	{
		for (BYTE j=0;j<5;j++)
		{
			data[i][j]=sqrt(data[i][j]);
		}
	}
}
bool Matrix5::Load(LPCSTR Fname)
{
	PFile f=new CPFile;
	if (!FileExists(Fname))
		return 0;
	if (!f->Open(Fname,FILE_READ)) return 0;
	for (BYTE i=0;i<5;i++)
	{
		for (BYTE j=0;j<5;j++)
		{
			f->Read(&_data[i][j],4);
			data[i][j]=_data[i][j];
		}
	}
	return f->Close();
}
void Matrix5::ApplyEffect(BYTE *Src,BYTE *Dest,int Width,int Height)
{
	int x=0,y=0;
	FLOAT a,r,g,b;
    for (int i=0;i<Width;i++)
	{
		for (int j=0;j<Height;j++)
		{
			a=r=g=b=0;
			for (int l=0;l<5;l++)
			{
				for (int k=0;k<5;k++)
				{
					x=i+l-2;
					y=j+k-2;
					if (x<0)
					{
						x=0;
					}
					if (y<0)
					{
						y=0;
					}
					if (y>=Height)
					{
						y=Height-1;
					}
					if (x>=Width)
					{
						x=Width-1;
					}
//					sc=Src+(y*Width+x)*4;
					a+=(FLOAT)Src[(y*Width+x)*4+0]*data[l][k];
					r+=(FLOAT)Src[(y*Width+x)*4+1]*data[l][k];
					g+=(FLOAT)Src[(y*Width+x)*4+2]*data[l][k];
					b+=(FLOAT)Src[(y*Width+x)*4+3]*data[l][k];
				}
			}
//			sc=Dest+(i+j*Width)*4;
			Dest[(i+j*Width)*4]=(BYTE)a;
			Dest[(i+j*Width)*4+1]=(BYTE)r;
			Dest[(i+j*Width)*4+2]=(BYTE)g;
			Dest[(i+j*Width)*4+3]=(BYTE)b;
/*			*sc=(BYTE)a;
//			sc++;
			*sc=(BYTE)r;
//			sc++;
			*sc=(BYTE)g;
//			sc++;
			*sc=(BYTE)b;*/
		}
	}
}