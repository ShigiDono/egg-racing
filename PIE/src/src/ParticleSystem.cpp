#include"stdafx.h"
#include"ParticleSystem.h"
unsigned int g_seed=152406923;
void Random_Seed(int seed)
{
	if(!seed) g_seed=timeGetTime();
	else g_seed=seed;
}
CParticleSystem::CParticleSystem()
{
	ZeroMemory(this,sizeof(CParticleSystem));
	Created=0;
	np = 0.0f;
}
/*CPS::CPS()
{
	txtr=new CTexture;
}*/
int Random_Int(int _min, int _max)
{
	g_seed=214013*g_seed+2531011;
	return _min+(g_seed ^ g_seed>>15)%(_max-_min+1);
}
scalar Random_scalar(scalar _min, scalar _max)
{
	g_seed=214013*g_seed+2531011;
	//return min+g_seed*(1.0f/4294967295.0f)*(max-min);
	return _min+(g_seed>>16)*(1.0f/65535.0f)*(_max-_min);
}
void CParticleSystem::SetParams(int emissionv, scalar sspeed,scalar vspeed,scalar lifev, scalar plife, scalar plifevar)
{
/*	if (info.ParticlesActive!=0)
		this->info.ParticlesActive = 0;*/
	info->emission = emissionv;
	info->sizevar  = 1;
	info->plifevar = plifevar;
	info->plife = plife;
	info->life = lifev;
	info->sspeed=sspeed;
	info->vspeed=vspeed;

	info->va = 1.0f;
	info->vr = 1.0f;
	info->vg = 1.0f;
	info->vb = 1.0f;
}


void CParticleSystem::SetEmitter(WORD vnum,WORD fnum,VC vfunc,IC ifunc)
{
	emitter.vnum=vnum;
	emitter.fnum=fnum;
	emitter.getvertex=vfunc;
	emitter.getindex=ifunc;
}

void CParticleSystem::Update(scalar dt)
{
	Created=1;
	if (!(emitter.getvertex&&emitter.getindex))
		return;
	float x,y,z,d;
	if (age==-1) age=0;
	Mi=particles[0].p;
	Ma=Mi;
	for(int i=0; i < ParticlesActive; i++)
	{
		particles[i].age += dt;
		if ( particles[i].age >= particles[i].life)
		{
			_swap(i, ParticlesActive-1);
			ParticlesActive--;
			i--;
			continue;
		}
		if (i==0)
		{
			Mi=Ma=particles[i].p;
		}

		particles[i].p += particles[i].v * dt;
		particles[i].v += particles[i].dv * dt;
		Mi.x=min(Mi.x,particles[i].p.x);
		Mi.y=min(Mi.y,particles[i].p.y);
		Mi.z=min(Mi.z,particles[i].p.z);
		Ma.x=max(Ma.x,particles[i].p.x);
		Ma.y=max(Ma.y,particles[i].p.y);
		Ma.z=max(Ma.z,particles[i].p.z);
/*		if (force.a>0)
		{
			x=force.p.x-particles[i].p.x;
			y=force.p.y-particles[i].p.y;
			z=force.p.z-particles[i].p.z;
			if (force.fallof>0){
				d=1-(x*x+y*y+z*z)/force.fallof;
                if (d<0) d=0;				
			}
			else
				d=1;
			particles[i].v+=(force.p-particles[i].p)*dt*d*force.a;
		}*/

		particles[i].a += (particles[i].da*dt);
		particles[i].r += (particles[i].dr*dt);
		particles[i].g += (particles[i].dg*dt);
		particles[i].b += (particles[i].db*dt);

		particles[i].size += particles[i].dsize*dt;


	}

	np += info->emission * dt;// + nedocreated;

	if (info->life != -1)
	{
	age += dt;

	/*if (age >= info->life)
		return;*/
	}
	int t=ParticlesActive;
 for (int i = t; i < t + np; i++)
 {
//	 if (t==0)
	 if (ParticlesActive >= MAX_PARTICLES) break;
	 particles[i].life  = Random_scalar(info->plife ,info->plife + info->plifevar);
	 if (particles[i].life < 0 ) particles[i].life = info->plife;
	 particles[i].age = 0;


	 Vector3 v0(0,0,10.0f), v1(0,10.0f,0), v2(10.0f,0,0);

	 int f = rand()%emitter.fnum;
/*	 if (emitter.getvertex==NULL){
		 v0 = emitter.v[emitter.index[f*3]];//*b.R_T       + b.x;
		 v1 = emitter.v[emitter.index[f*3+1]];//*b.R_T  + b.x;
		 v2 = emitter.v[emitter.index[f*3+2]];//*b.R_T  + b.x;
	 }
	 else
	 {*/
		v0 = (emitter.getvertex)((emitter.getindex)(f*3));
		v1 = (emitter.getvertex)((emitter.getindex)(f*3+1));
		v2 = (emitter.getvertex)((emitter.getindex)(f*3+2));
/*		DrawLine(v0,v1,0xffffffff,0xffffffff);
		DrawLine(v1,v2,0xffffffff,0xffffffff);
		DrawLine(v0,v2,0xffffffff,0xffffffff);*/
//	 }

	scalar y1 = (rand()%100);
	scalar y2 = (rand()%100);
	
	

	Vector3 x1, x2;
	x1 = (v0*y1 + v1*y2)/(y1 + y2);

	 y1 = (rand()%100);
	 y2 = (rand()%100);
	

	x2 = (v2*y1 + x1*y2)/(y1 + y2);

	 particles[i].p = x2;
	 scalar sv=info->sspeed+(rand()%100 / 100.0f)*info->vspeed;
	 if (info->UseNormal){
		particles[i].v = CalcNorm(v0,v1,v2) * sv;
		particles[i].dv = CalcNorm(v0,v1,v2)*(scalar)(info->espeed-sv)/particles[i].life;
	 }
	 else
	 {
		 particles[i].v = info->Dir * sv;
		 particles[i].dv = info->Dir * (scalar)(info->espeed-sv)/particles[i].life;
	 }
	 /*+ ///*b.R_T 
		 Vector3( (rand()%100 - rand()%100) / 10000,
								(rand()%100 - rand()%100) / 100,
								(rand()%100 - rand()%100) / 100);*/


	 particles[i].size				= Random_scalar(info->startsize, info->startsize + info->sizevar);
	 particles[i].dsize				= (info->endsize - info->startsize) / particles[i].life;

	 
	 particles[i].a					= Random_scalar(info->sa ,info->sa + info->va);
	 particles[i].r					= Random_scalar(info->sr ,info->sr + info->vr);
	 particles[i].g					= Random_scalar(info->sg ,info->sg + info->vg);
	 particles[i].b					= Random_scalar(info->sb ,info->sb + info->vb);
	 if (particles[i].a<0)
		 particles[i].a=0;
	 if (particles[i].r<0)
		 particles[i].r=0;
	 if (particles[i].g<0)
		 particles[i].g=0;
	 if (particles[i].b<0)
		 particles[i].b=0;
//	 particles[i].size				= info.startsize;

	 particles[i].da				= (info->ea - particles[i].a)/particles[i].life;
	 particles[i].dr				= (info->er - particles[i].r)/particles[i].life;
	 particles[i].dg				= (info->eg - particles[i].g)/particles[i].life;
	 particles[i].db				= (info->eb - particles[i].b)/particles[i].life;
	 particles[i].dsize				= (info->endsize - particles[i].size)/particles[i].life;
		if (ParticlesActive==0)
			Mi=Ma=particles[i].p;
	Mi.x=min(Mi.x,particles[i].p.x);
	Mi.y=min(Mi.y,particles[i].p.y);
	Mi.z=min(Mi.z,particles[i].p.z);
	Ma.x=max(Ma.x,particles[i].p.x);
	Ma.y=max(Ma.y,particles[i].p.y);
	Ma.z=max(Ma.z,particles[i].p.z);
	 ParticlesActive++;
	}
 if (np > 1)
 {
	 np -= floor(np);
 }
}

/*void CParticleSystem::WriteToFile(char *name)
{
	DWORD dw = 0;
	HANDLE file = CreateFile(name,GENERIC_WRITE,FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);
	WriteFile(file, &info, sizeof(psysteminfo), &dw, NULL);
	WriteFile(file,&force,sizeof(CForce),&dw,NULL);
/*	WriteFile(file, &emitter.vnum , sizeof(int), &dw, NULL);
	WriteFile(file, &emitter.fnum , sizeof(int), &dw, NULL);
	WriteFile(file, &emitter.v    , sizeof(Vector3)*emitter.vnum, &dw, NULL);
	WriteFile(file, &emitter.index, sizeof(int)*emitter.fnum, &dw, NULL);
	CloseHandle(file);

}

void CParticleSystem::ReadFromFile(char *name)
{
	DWORD dw = 0;
	HANDLE file = CreateFile(name,GENERIC_READ,FILE_SHARE_READ,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,0);
	ReadFile(file, &info, sizeof(psysteminfo), &dw, NULL);
	ReadFile(file, &force,sizeof(CForce),&dw,NULL);
	info.getindex=NULL;
	info.getvertex=NULL;
//	ReadFile(file, &emitter.vnum , sizeof(int), &dw, NULL);
//	ReadFile(file, &emitter.fnum , sizeof(int), &dw, NULL);
//	ReadFile(file, &emitter.v    , sizeof(Vector3)*emitter.vnum, &dw, NULL);
//	ReadFile(file, &emitter.index, sizeof(int)*emitter.fnum, &dw, NULL);
	CloseHandle(file);

}*/

void CParticleSystem::setsc(scalar r,scalar g,scalar b,scalar a)
{
	 info->sa = a;
	 info->sr = r;
	 info->sg = g;
	 info->sb = b;
}

void CParticleSystem::setec(scalar r,scalar g,scalar b,scalar a)
{
	 info->ea = a;
	 info->er = r;
	 info->eg = g;
	 info->eb = b;
}

void CParticleSystem::setvc(scalar r,scalar g,scalar b,scalar a)
{
	 info->va = a;
	 info->vr = r;
	 info->vg = g;
	 info->vb = b;
}
void CParticleSystem::_swap(int i,int j)
{
	particle t   = particles[i];
	particles[i] = particles[j];
	particles[j] = t;
}
CDParticleSystem::CDParticleSystem()
{
	Created=0;
	age=-1;
}
CPSysInfoManager::CPSysInfoManager()
{
	ZeroMemory(this,sizeof(CPSysInfoManager));
}
void				CPSysInfoManager::NewPreset(LPCSTR name)
{
	this->Presets[this->PresetCount]=new psysteminfo;
	LastCreatedPreset=Presets[PresetCount];
	strcpy(LastCreatedPreset->name,name);
	this->PresetCount++;
}

void				CPSysInfoManager::NewPreset(ppsysteminfo prst)
{
	this->Presets[this->PresetCount]=prst;
	LastCreatedPreset=Presets[PresetCount];
	this->PresetCount++;
}

ppsysteminfo		CPSysInfoManager::GetPreset(WORD index){ 
	return Presets[index];
}
ppsysteminfo		CPSysInfoManager::GetPreset(LPCSTR name)
{
	for (int i=0;i<PresetCount;i++)
	{
		if (strcmp(name,Presets[i]->name)==0){
//			PresetCount--;
			return Presets[i];
		}
	}
	return NULL;
}
void				CPSysInfoManager::DeletePreset(WORD index){
	delete Presets[index];
    Presets[index]=Presets[PresetCount-1];
	Presets[PresetCount-1]=NULL;
	PresetCount--;
}
void				CPSysInfoManager::DeletePreset(LPCSTR name)
{
	for (int i=0;i<PresetCount;i++)
	{
		if (strcmp(name,Presets[i]->name)==0){
			DeletePreset(i);
			PresetCount--;
			return;
		}
	}
}
void				CPSysInfoManager::Clear(){
	while (PresetCount!=0) DeletePreset((WORD)0);
}
bool				CPSysInfoManager::LoadPresets(LPCSTR fname)
{
	WriteMsg("-->Loading particle systems preset file '%s'.",fname);
	AddTab();
	PFile f=new CPFile;
	if (!f->Open(fname,FILE_READ)){
		PutError("Failed to open preset!");
		RemTab();
		return 0;
	}

	char c=0;
	WORD c1;
	f->Read(&c,1);
	if (c!='P')
	{
		PutError("-->File %s%s has unknown format or damaged!",GetDir(),fname);
		f->Close();
		RemTab();
		delete f;
		return 0;
	}
	f->Read(&c,1);
	if (c!='P')
	{
		PutError("-->File %s%s has unknown format or damaged!",GetDir(),fname);
		f->Close();
		RemTab();
		delete f;
		return 0;
	}
	f->Read(&c,1);
	if (c!='S')
	{
		PutError("-->File %s%s has unknown format or damaged!",GetDir(),fname);
		f->Close();
		RemTab();
		delete f;
		return 0;
	}
	f->Read(&c1,2);
	for (int i=0;i<c1;i++)
	{
		this->NewPreset("No name");
		LoadPresetFromFile(f,LastCreatedPreset);
		LastCreatedPreset->txt=(_load)(LastCreatedPreset->tname);
	}

	if (!f->Close())
		return 0;
	RemTab();
	WriteMsg("-->Success");
	delete f;
	return 1;
}
bool				LoadPresetFromFile(PFile f,ppsysteminfo preset)
{
	byte b;
	ZeroMemory(preset->name,sizeof(preset->name));
	ZeroMemory(preset->tname,sizeof(preset->tname));
	f->ReadNullTerminatedString(preset->name);
	f->ReadNullTerminatedString(preset->tname);
	f->Read(&b,1);
	preset->animated=b;
	f->Read(&preset->startf,1);
	f->Read(&preset->fcount,1);
	f->Read(&b,1);
	preset->UseNormal=b;
	f->Read(&preset->BlendKind,1);
	f->Read(&preset->emission,4);
	f->Read(&preset->plife,4);
	f->Read(&preset->plifevar,4);
	f->Read(&preset->life,4);
	f->Read(&preset->sspeed,4);
	f->Read(&preset->espeed,4);
	f->Read(&preset->vspeed,4);
	f->Read(&preset->Dir.x,4);
	f->Read(&preset->Dir.y,4);
	f->Read(&preset->Dir.z,4);
	f->Read(&preset->sa,4);
	f->Read(&preset->sr,4);
	f->Read(&preset->sg,4);
	f->Read(&preset->sb,4);

	f->Read(&preset->ea,4);
	f->Read(&preset->er,4);
	f->Read(&preset->eg,4);
	f->Read(&preset->eb,4);

	f->Read(&preset->va,4);
	f->Read(&preset->vr,4);
	f->Read(&preset->vg,4);
	f->Read(&preset->vb,4);

	f->Read(&preset->startsize,4);
	f->Read(&preset->endsize,4);
	f->Read(&preset->sizevar,4);
	return 1;
}
CForceManager::CForceManager()
{
	return;
}
CParticleSystemManager::CParticleSystemManager()
{
	PSCount=0;
	LastCreatedPS=NULL;
	return;
}
void						CParticleSystemManager::NewParticleSystem(LPCSTR	name,LPCSTR	pname)
{
	ParticleSystems[PSCount]=new CDParticleSystem;
	strcpy(ParticleSystems[PSCount]->name,name);
	ParticleSystems[PSCount]->info=Presets->GetPreset(pname);
	LastCreatedPS=ParticleSystems[PSCount];
	PSCount++;
}
void						CParticleSystemManager::NewParticleSystem(LPCSTR	name,ppsysteminfo preset){
	ParticleSystems[PSCount]=new CDParticleSystem;
	strcpy(ParticleSystems[PSCount]->name,name);
	ParticleSystems[PSCount]->info=preset;LastCreatedPS=ParticleSystems[PSCount];
	PSCount++;
}
void						CParticleSystemManager::NewParticleSystem(PDParticleSystem PS)
{
	ParticleSystems[PSCount]=PS;LastCreatedPS=ParticleSystems[PSCount];
	PSCount++;
}
PDParticleSystem			CParticleSystemManager::GetParticleSystem(WORD index)
{
	return ParticleSystems[index];
}
PDParticleSystem			CParticleSystemManager::GetParticleSystem(LPCSTR name)
{
	for (int i=0;i<PSCount;i++)
	{
		if (strcmp(name,ParticleSystems[i]->name)==0)
			return ParticleSystems[i];
	}
	return NULL;
}
void						CParticleSystemManager::DeletePS(WORD index)
{
	delete ParticleSystems[index];
	ParticleSystems[index]=ParticleSystems[PSCount-1];
	PSCount--;
}
void						CParticleSystemManager::DeletePS(LPCSTR name){
	for (int i=0;i<PSCount;i++)
	{
		if (strcmp(name,ParticleSystems[i]->name)==0){
			DeletePS(i);
			return;
		}

	}
}
void						CParticleSystemManager::DrawPS(WORD ind,PCamera c){
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));
/*bool CullBox(Vector3 min, Vector3 max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);*/
	WriteMsg("-->Culling");

	if (CullBox(ParticleSystems[ind]->Mi,ParticleSystems[ind]->Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
	{
		ParticleSystems[ind]->Render();
	}
}
void						CParticleSystemManager::DrawPS(LPCSTR name,PCamera c)
{
	for (int i=0;i<PSCount;i++)
	{
		if (strcmp(name,ParticleSystems[i]->name)==0)
			DrawPS(i,c);
	}
}
void						CParticleSystemManager::Update(WORD ind,PCamera c,FLOAT dt){
	Matrix3x3 m0=Matrix3x3(Vector3(1.0f,0.0f,0.0f),Vector3(0.0f,1.0f,0.0f),Vector3(0.0f,0.0f,1.0f));
/*bool CullBox(Vector3 min, Vector3 max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);*/
	WriteMsg("-->Culling");
	if (!ParticleSystems[ind]->Created)
	{
		ParticleSystems[ind]->Update(dt);
	}
	else
	{
		if (CullBox(ParticleSystems[ind]->Mi,ParticleSystems[ind]->Ma,Vector3(0.0f,0.0f,0.0f),Vector3( 1.0f,1.0f,1.0f),m0,c->FOV,c->Aspect,c->ZNear,c->ZFar,c->Pos,c->At,c->Up))
		{
			ParticleSystems[ind]->Update(dt);
		}
	}

}
void						CParticleSystemManager::Update(LPCSTR name,PCamera c,FLOAT dt)
{
	for (int i=0;i<PSCount;i++)
	{
		if (strcmp(name,ParticleSystems[i]->name)==0)
			Update(i,c,dt);
	}
}
void						CParticleSystemManager::Clear()
{
	while(PSCount!=0)
		DeletePS((WORD)0);
}
