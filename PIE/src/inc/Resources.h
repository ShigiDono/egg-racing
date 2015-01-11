#ifndef PIE_RESOURCEMANAGER
#define PIE_RESOURCEMANAGER
#include"main.h"
#include"mesh.h"
//#include"font.h"
#include"t_and_s.h"
#include"files.h"
#include"filter.h"
#include"ParticleSystem.h"
#include"UI.h"
#include"matrix.h"
//Resource definitions
#define MAX_MESH_COUNT				1000
#define MAX_TEXTURE_COUNT			1000
#define MAX_MODEL_COUNT				1000
#define MAX_PARTICLESYSTEM_COUNT	1000
//Scene definitions
#define MAX_SCENE_COUNT				100
//__forceinline Strcmp(LPCSTR str1,LPCSTR str2);
bool _LoadPresets(char* fname);

typedef enum _RESOURCE_TYPE
{
	RESOURCE_MESH				= 0x00,//3ds mesh
	RESOURCE_MODEL				= 0x01,//contains texture and mesh
	RESOURCE_TEXTURE			= 0x02,//any texture file
	RESOURCE_ANIMTEXTURE		= 0x03,//animated texture(may be AVI)
//	RESOURCE_PARTICLESYSTEM		= 0x04,//no comments :3
//	RESOURCE_TILE				= 0x05,//tiles
	RESOURCE_MUSIC				= 0x04,
	RESOURCE_SOUND				= 0x05,
}RESOURCE_TYPE;
//void AssignDevice(LPDIRECT3DDEVICE9 _d3dd,DWORD w,DWORD h,char* CDir);

class CResource
{
public:
//	CResource(){}
	virtual	bool			LoadFromFile(LPCSTR FName,LPCSTR rname)=0;
	virtual	void			Release()=0;
	virtual void			Destroy()=0;
	virtual	bool			Reset()=0;
	char					name[32];
	DWORD					rm;
};

class CRMesh : public CResource
{
public:
	CRMesh();
    PMesh					Mesh;
	bool 					LoadFromFile(LPCSTR FName,LPCSTR rname);
	void 					Release();
	void 					Destroy();
	void					Draw();
	bool 					Reset();
};

class CRTexture : public CResource
{
public:
	CRTexture();
    PTexture				Texture;
	bool 					LoadFromFile(LPCSTR FName,LPCSTR rname);
	void 					Release();
	void 					Destroy();
	bool 					Reset();
	void					Set(DWORD num);
	//void					SetState(D3DTEXTURESTAGESTATETYPE type,DWORD Value);
};

class CRModel : public CResource
{
public:
	CRModel();
	CRMesh					*Mesh,*PHmesh;
	CRTexture				*Texture;
	char					Fname[MAX_PATH];
	bool 					LoadFromFile(LPCSTR FName,LPCSTR rname);
	Vector3					GetVertex(WORD ind);
	inline WORD				GetIndex(WORD ind){return Mesh->Mesh->indices[ind];}
	void 					Release(){
		if (rm==NULL) RELEASE(Mesh);
		if (rm==NULL) RELEASE(PHmesh);
		if (rm==NULL) RELEASE(Texture);
		return;
	}
	void 					Destroy(){return;}
	bool 					Reset(){return 1;}
	void					Draw(DWORD tind);
	void					DrawEx(DWORD tind,Vector3 pos);
	void					DrawExx(DWORD tind,Vector3 pos,Vector3 rot);
	void					DrawBMesh(DWORD color);
	inline TVertex3D		*GetVertexData(){return Mesh->Mesh->vertices;}
	inline WORD				*GetIndexData(){return Mesh->Mesh->indices;}
	inline DWORD			GetVnum(){return Mesh->Mesh->vnum;}
	inline DWORD			GetFnum(){return Mesh->Mesh->fnum;}
	void					SetEmitter(PDParticleSystem ps);
	Vector3					Rotation,Scaling,Translation,Rot;
	void					DrawPS();
	void					UpdatePS(scalar dt);
	PDParticleSystem		Ps;
	DWORD					time1, time2;
};

/*class CRParticleSystem : public CResource
{
public:
	CRParticleSystem();
	CDParticleSystem		*ParticleSystem;
	CRTexture				*Texture;
	CRModel					*Emitter;
	bool 					LoadFromFile(LPCSTR FName,LPCSTR rname);
	void 					Release(){return;}
	void 					Destroy();
	bool 					Reset(){return 1;}
	void					Draw();
	void					Update(FLOAT dt);
	void					AssignEmitter(CRModel *emitter);
};*/
PTexture GetPSTexture(LPCSTR name);
class CResourceManager
{
public:
	CResourceManager();
	CRMesh*					Meshes[MAX_MESH_COUNT];
	CRTexture*				Textures[MAX_TEXTURE_COUNT];
	CRModel*				Models[MAX_MODEL_COUNT];
//	CRParticleSystem*		ParticleSystems[MAX_PARTICLESYSTEM_COUNT];
	WORD					MeshesCount,TexturesCount,ModelsCount;//,ParticleSystemsCount;
	CResource				*GetResource(RESOURCE_TYPE type,WORD index);
	CResource				*GetResource(RESOURCE_TYPE type,LPCSTR name);
	CResource				*LastCreatedResource;
	bool					AddResource(RESOURCE_TYPE type,LPCSTR fname,LPCSTR name);
	void					AddResource(RESOURCE_TYPE type,CResource *resource);
	void					AddResource(RESOURCE_TYPE type,LPCSTR name);
	void					RemoveResource(RESOURCE_TYPE type,WORD index);
	void					RemoveResource(RESOURCE_TYPE type,LPCSTR name);
	void					Release();
	void					Destroy();
	bool					Reset();
	CParticleSystemManager	psm;
	DWORD					Scene;
};


typedef void (*SceneRFunc)(DWORD);
typedef void (*SceneGFunc)(DWORD);
typedef void (*SceneSFunc)(DWORD,FLOAT);




class CScene
{
public:
	CScene();
	char name[32];
	CResourceManager		ResourceManager;
	void					ExecuteScript(LPCSTR str);
	bool					LoadFromFile(LPCSTR FName);
	SceneRFunc				Draw;
	SceneSFunc				Step;
	SceneGFunc				Gain;
	void					Render();
	void					Update(FLOAT dt);
	inline void				AssignDrawFunc(SceneRFunc DRAW){Draw=DRAW;}
	inline void				AssignStepFunc(SceneSFunc STEP){Step=STEP;}
	inline void				AssignGainFunc(SceneGFunc GAIN){Gain=GAIN;}
	void					Destroy();
	bool					Reset();
	void					Release();
	PCamera					Camera;
};
CPSysInfoManager* _Presets();
void RRelease();
typedef CScene *PScene;



class CSceneManager
{
public:
	CSceneManager();
	PScene					Scenes[MAX_SCENE_COUNT];
	bool					NewSceneFromFile(LPCSTR FName,LPCSTR name);
	void					NewScene(LPCSTR name);
	void					RemoveScene(WORD index);
	void					RemoveSceneEx(LPCSTR name);
	PScene					GetScene(WORD index);
	PScene					GetSceneEx(LPCSTR name);
	WORD					ScenesCount;
	WORD					CurrentScenePos,DCurrentScenePos;
	PScene					CurrentScene;
	void					Draw();
	void					Update(FLOAT dt);
	void					SetCurrentScene(WORD index);
	void					Clear();
	void					Release();
	bool					Reset();
	void					Destroy();
	bool					UseTransition;
	GUI						UI;
	CResourceManager		rm;
protected:
//	LPDIRECT3DTEXTURE9		GlowTexture;
//	LPDIRECT3DTEXTURE9		_GlowTexture;
//	LPDIRECT3DTEXTURE9		__GlowTexture;
//	LPDIRECT3DSURFACE9		GMap;
	PFilter					_f;
	float					TransitionPos;
	PRect					SRect;
};






#endif PIE_RESOURCEMANAGER