#ifndef PIE_MESH
#define PIE_MESH
#include"main.h"
//#include"t_and_s.h"
//void MHAssignDevice(LPDIRECT3DDEVICE9 _d3dd,char *CDir);
#define POINTVERTEX (D3DFVF_XYZ | D3DFVF_PSIZE | D3DFVF_DIFFUSE)
struct TPVertex
{
	Vector3			p;
	scalar			size;
	DWORD			Color;
};
//void DrawPS(CParticleSystem ps,WORD num);
void DrawLine(Vector3 v1,Vector3 v2,DWORD cl1,DWORD cl2);
void MRelease();
class CMesh
{
public:
	CMesh();
	TVertex3D				*vertices;
	WORD					*indices;
//	D3DMATERIAL9			mats;
	char					__fname[MAX_PATH];
	DWORD					fnum, vnum;
	void					AssignVertexData(TVertex3D *v,DWORD _vnum);
	void					AssignIndexData(WORD *i,DWORD _fnum);
//	LPDIRECT3DVERTEXBUFFER9 vb;
//	LPDIRECT3DINDEXBUFFER9	ib;
	void					Release(){RELEASE(vb);RELEASE(ib);}
	bool					Reset(){Release();return MakeBuffers();}
	bool					MakeBuffers();
	bool					LoadFromFile(LPCSTR FName,FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals);
	bool					LoadMesh(LPCSTR FName,FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals,bool _SelfIllumination);
	void					Draw();
	void					Draw1();
	bool					SelfIllumination;
	bool					DrawMesh;
	bool					CreateBuffers;
	void					DrawAsLines(DWORD Color);
	void					Destroy(){
		DELETE(vertices);
		DELETE(indices);
		Release();
	}
	bool					InvertN;
	Vector3					BMin,BMax;
};
typedef CMesh  *PMesh;
class CModel
{
public:
	CModel();
	void					AssignMesh(PMesh _mesh,WORD index);
	void					Draw(WORD index);
	Vector3					pos;
	Vector3					rot;
	Vector3					sc;
    PMesh					Mesh;
private:
	WORD					ind;
};
typedef CModel  *PModel;
class CPRect
{
public:
    CPRect();
	void					SetPos(int ind,Vector3 _p);
	void					SetTCoord(int ind,FLOAT _tu,FLOAT _tv);
	void					SetColor(int ind,DWORD _Color);
	void					Update();
	void					Draw();
	TVertex2D				v[4];
protected:
};
typedef CPRect *PRect;
#endif PIE_MESH