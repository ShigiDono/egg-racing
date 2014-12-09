#ifndef PIE_PARTICLESYSTEM
#define PIE_PARTICLESYSTEM
#pragma warning( disable : 4244 ) 

#include"main.h"
#include"mesh.h"
#include"t_and_s.h"
#include"matrix.h"
//#include"resource.h"
//#include"Rigidbody.h"

#define MAX_PARTICLES		2000
#define MAXPSCOUNT			4000
#define MAXFORCECOUNT		1000
#define MAXPRESETCOUNT		1000

#define P_USE_TEXTURE		-1
#define	P_RANDOM			-2


//RigidBody b(10);



//int g_seed 152406923

void Random_Seed(int seed);

int Random_Int(int _min, int _max);
typedef Vector3 (*VC)(WORD index);
typedef WORD (*IC)(WORD index);
typedef PTexture (*Txt)(LPCSTR name);
scalar Random_scalar(scalar _min, scalar _max);
struct CForce
{
	Vector3 p;
	FLOAT	fallof,a;
	bool	plane;
};

typedef CForce *PForce;
class CForceManager
{
public:
	CForceManager();
	void				NewForce();
	PForce				GetForce(DWORD index);
	void				DeleteForce(DWORD index);
	void				Clear();
	void				Apply(Vector3 &v);
private:
	PForce				forces[MAXFORCECOUNT];
	DWORD				ForceCount;
};

struct particle
{
	Vector3 p, v, dv;
	scalar  size, dsize;
	scalar  r, g, b, a;
	scalar  dr, dg, db, da;
	scalar	life, age;
};

struct psysteminfo
{
	char				name[32];
	char				tname[368];
	int					emission, nedocreated; 
	scalar				sr,sg,sb,sa;
	scalar				er,eg,eb,ea;
	scalar				vr,vg,vb,va;
	scalar				startsize, endsize, sizevar;
	scalar				sspeed,vspeed,espeed;
	scalar				plife, plifevar;
	scalar				life;
	char				fcount,startf;
	bool				animated;
	BYTE				BlendKind;
	Vector3				Dir;
	bool				UseNormal;
	PTexture			txt;
};
typedef psysteminfo *ppsysteminfo;
bool LoadPresetFromFile(PFile f,ppsysteminfo preset);
class CPSysInfoManager
{
public:
	CPSysInfoManager();
	bool				LoadPresets(LPCSTR fname);
	void				NewPreset(LPCSTR name);
	void				NewPreset(ppsysteminfo prst);
	ppsysteminfo		GetPreset(WORD index);
	ppsysteminfo		GetPreset(LPCSTR name);
	void				DeletePreset(WORD index);
	void				DeletePreset(LPCSTR name);
	void				Clear();
	ppsysteminfo		LastCreatedPreset;
	DWORD				GetCount(){ return PresetCount;}
	ppsysteminfo		Presets[MAXPRESETCOUNT];
	DWORD				PresetCount;
	Txt					_load;
};
struct emitterinfo
{
	VC					getvertex;
	IC					getindex;
	int					vnum, fnum;
};


class CParticleSystem
{
public:
	CParticleSystem();
	int					ParticlesActive;
	ppsysteminfo		info;
	emitterinfo			emitter;
	particle			particles[MAX_PARTICLES];
	Vector3				Mi,Ma;
	scalar				age;
	bool Created;
	float				dt;
	scalar np;

	void SetEmitter(WORD vnum,WORD fnum,VC vfunc,IC ifunc);
	void SetParams(int emissionv, scalar sspeed,scalar vspeed,scalar lifev, scalar plife, scalar plifevar);
	void Update(scalar dt);
	
	// set : start color, endcolor, color variabylity
	void setsc(scalar r,scalar g,scalar b,scalar a);
	void setec(scalar r,scalar g,scalar b,scalar a);
	void setvc(scalar r,scalar g,scalar b,scalar a);

	void WriteToFile(char *name);
	void ReadFromFile(char *name);
private:

	void _swap(int i, int j);
};

class CDParticleSystem:public CParticleSystem
{
public:
//	CPS();
	CDParticleSystem();
	char name[32];
	void Render();
};
typedef CDParticleSystem *PDParticleSystem;
class CParticleSystemManager
{
public:
	CParticleSystemManager();
	void						NewParticleSystem(LPCSTR	name,LPCSTR	pname);
	void						NewParticleSystem(LPCSTR	name,ppsysteminfo preset);
	void						NewParticleSystem(PDParticleSystem PS);
	PDParticleSystem			GetParticleSystem(WORD index);
	PDParticleSystem			GetParticleSystem(LPCSTR name);
	void						DeletePS(WORD index);
	void						DeletePS(LPCSTR name);
	void						DrawPS(WORD ind,PCamera c);
	void						DrawPS(LPCSTR name,PCamera c);
	void						Update(WORD ind,PCamera c,FLOAT dt);
	void						Update(LPCSTR name,PCamera c,FLOAT dt);
	CForceManager				ForceManager;
	CPSysInfoManager			*Presets;
	void						Clear();
    PDParticleSystem			LastCreatedPS;	
	PDParticleSystem			ParticleSystems[MAXPSCOUNT];
	DWORD						PSCount;
};





#endif PIE_PARTICLESYSTEM