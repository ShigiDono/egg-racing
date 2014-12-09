#ifndef PIE_TERRAIN 
#define PIE_TERRAIN
#include"main.h"
//#include"mesh.h"
#include"t_and_s.h"
#include"matrix.h"
#include"resources.h"
#include"perror.h"
#define TERRAIN_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)
#define TILE_SIZE 16
typedef void (*Tu)(float,char*);

#define ShadowColor		0xFF000000
#define HiLightColor	0xFFFFFFFF

struct TeVertex
{
	Vector3			p;
	DWORD			Color;
    FLOAT			tu, tv;
};
#define TERRAINVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
float Blend(float x,float y,float k);
struct Tdata
{
    WORD						coord[4];
	WORD						num[4];
	char						n;
};
class CHeightMap
{
public:
	CHeightMap();
	void						CreateHeightMap(WORD w,WORD h);
	void						LoadHeightMap(PFile f);
	void						GenerateNormals();
	void						LightIt(Vector3 LD);
	BYTE						*HMap;
	Vector3						*Normals;
	Vector3						*FaceNormals;
	DWORD						*ColorMap;
	WORD						*TempT;
	float						GetHeightValue(float x,float z);
	DWORD						Ambient;
	DWORD						Diffuse;
	WORD						Width,Height;
	float						HScale,VScale;
	DWORD						dr,undr;
	LPDIRECT3DTEXTURE9			Texture;
	Tu							prg;
	int							xxx,zzz,iii,TWidth,THeight,TCount,TS,TDef,TDef1;
	Vector3						LightVector;
	Vector3						GetFaceNormal(int x,int z,bool poly)
	{
		return FaceNormals[(z*Width+x)*2+poly];
	}
	void						Release(){
		DELETE(Normals);
		DELETE(FaceNormals);
		DELETE(HMap);
		DELETE(ColorMap);
		DELETE(TempT);
		RELEASE(Texture);
	}
};
typedef	CHeightMap *PHeightMap;
class	CPTile
{
public:
	CPTile();
    void						Draw();
	void						Create(TeVertex *v);
	Vector3						Mi,Ma;
	LPDIRECT3DVERTEXBUFFER9		buff;
	int							xt,yt;
	PHeightMap					HMap;
	void						Release(){RELEASE(buff);}
	void						Reset(){Create(NULL);}
	DWORD						Cl,ICl;
};
typedef CPTile *PTile;
class CTerrain
{
public:
	CTerrain();
	void						Load(PFile	f);
	Tu							prg;
	void						Release(){
		for (int i=0;i<TileCount;i++)
			Tiles[i].Release();
		HMap->Release();
		//SkyBox->Release();
//		RELEASE(SkyTexture);
//		RELEASE(SkyBox);
		//SkyTexture->Release();
	}
	void						Reset(){
		for (int i=0;i<TileCount;i++)
			Tiles[i].Reset();
	}
	void						Draw();
    PHeightMap					HMap;
	PTile						Tiles;
//	CRModel						*SkyBox;
	//PTexture					SkyTexture;
	int							TileCount;
//	char						SkyBoxTexture[MAX_PATH];
	DWORD						Cl;
private:
};
typedef CTerrain* PTerrain;

class CPMap
{
public:
	CPMap();
	CResourceManager			RM;
	Tu							prg;
	void						SetProgressFunction(Tu f ){ 
		prg=f;
		this->Terrain->prg=f;
		this->Terrain->HMap->prg=f;
	}
	void						Render();
	void						Update(scalar dt);
	bool						LoadFromFile(LPCSTR Fname);
	PTerrain					Terrain;
	char						name[32];
	int							Width,Height;
	char						_path[300][MAX_PATH];
	DWORD						BGcolor;
	float						fnear,ffar;
	void						Release()
	{
		Terrain->Release();
	}
	void						Reset()
	{
		Terrain->Reset();
	}
	DWORD TerrainTime, ModelsTime;
};



#endif PIE_TERRAIN