#include"stdafx.h"
#include"pie.h"
#include"resource.h"

PRect rr=NULL,fr=NULL,ld1=NULL,ld2=NULL;
PPie pd=NULL;
WORD gen=1;
DWORD _T=0,sT=0,ST=0;
PCamera c=NULL,d=NULL;
Vector3 cpos,tline,c1,c2;
float efade=0.0f;
CPMap _map;
bool WireFrame=0;
DWORD tl=0,tc=0,iii=0,pos=0;float rot=0;double _iii=0;
bool la=0;
float fade=1.0f;
#define MouseSen 1.0f

D3DCOLORVALUE d3dcolorvalue(BYTE a,BYTE r,BYTE g,BYTE b)
{
	D3DCOLORVALUE res;
	res.a=(float)a/255;
	res.r=(float)r/255;
	res.g=(float)g/255;
	res.b=(float)b/255;
	return res;
}
const D3DCOLORVALUE clBlack=d3dcolorvalue(255,0,0,0),clWhite=d3dcolorvalue(255,255,255,255);
FLOAT dtt;

void Scene1Step(DWORD Scene,FLOAT dt)
{
	if (dt==0) return;
//	WriteMsg("-->BeginStep");
	PScene cs=(PScene)Scene;
	int kk=40;
	//do something
	c1=cpos;
	if (pd->isKeyPressed(DIK_W)==KEY_PRESSED)
	{	
		Vector3 cn = (c2 -c1);
		cn.Normalise();
		cn *= 2;
		c2 += cn;
		c1 += cn;
	}
	if (pd->isKeyPressed(DIK_S)==KEY_PRESSED)
	{
	    Vector3 cn = (c2 -c1);
	    cn.Normalise();
	    cn *= 2;
	    c2 -= cn;
	    c1 -= cn;
	}
	if (pd->isKeyPressed(DIK_A)==KEY_PRESSED)
	{
	    Vector3 cn = (c2 -c1);
	    cn = cn^Vector3(0,1,0);
		cn.Normalise();
		cn *= 2;
	    c2 += cn;
	    c1 += cn;
	}
	if (pd->isKeyPressed(DIK_D)==KEY_PRESSED)
	{
	    Vector3 cn = (c2 -c1);
	    cn = cn^Vector3(0,1,0);
	    cn.Normalise();
	    cn *= 2;
	    c2 -= cn;
	    c1 -= cn;
	}
	float RotX, RotY;
	LPPOINT  Point ;
	///GetCursorPos(Point);
	int ddx=0,ddy=0;
	pd->GetMouseDelta(&ddx,&ddy);
	if (ddx!=0 || ddy!=0) {
//		SetCursorPos((int)Xs, (int)Ys);
		Vector3 cn = c2 - c1;
		RotX = (ddx) / 500.0f;
		c2.z = c1.z + sin(-RotX) * cn.x + cos(-RotX) * cn.z;
		c2.x = c1.x + cos(-RotX) * cn.x - sin(-RotX) * cn.z;
		RotY = (ddy) / 10.0f;
		c2.y = c2.y - RotY * 15;
	}
	cpos=c1;
/*	if (pd->isKeyPressed(DIK_W)==KEY_PRESSED)
		cpos.x-=kk*dt;
	if (pd->isKeyPressed(DIK_S)==KEY_PRESSED)
		cpos.x+=kk*dt;
	if (pd->isKeyPressed(DIK_D)==KEY_PRESSED)
		cpos.z+=kk*dt;
	if (pd->isKeyPressed(DIK_A)==KEY_PRESSED)
		cpos.z-=kk*dt;*/
	if (pd->isKeyPressed(DIK_Q)==KEY_PRESSED)
		cpos.y-=kk*dt;
	if (pd->isKeyPressed(DIK_E)==KEY_PRESSED)
		cpos.y+=kk*dt;
	if (pd->isKeyPressed(DIK_Y)==KEY_PRESSED)
		tline.x-=kk*dt;
	if (pd->isKeyPressed(DIK_H)==KEY_PRESSED)
		tline.x+=kk*dt;
	if (pd->isKeyPressed(DIK_J)==KEY_PRESSED)
		tline.z+=kk*dt;
	if (pd->isKeyPressed(DIK_G)==KEY_PRESSED)
		tline.z-=kk*dt;
	if (pd->isKeyPressed(DIK_T)==KEY_PRESSED)
		tline.y-=kk*dt;
	if (pd->isKeyPressed(DIK_U)==KEY_PRESSED)
		tline.y+=kk*dt;
	if (pd->isKeyPressed(DIK_ESCAPE)==KEY_DOWN){
		sT=timeGetTime();
		efade=1.3f;
	}
	if (pd->isKeyPressed(DIK_UP)==KEY_DOWN)
		pos++;
	if (pd->isKeyPressed(DIK_DOWN)==KEY_DOWN)
		pos--;
	if (pd->isKeyPressed(DIK_RIGHT)==KEY_PRESSED)
		rot-=kk*dt;
	if (pd->isKeyPressed(DIK_LEFT)==KEY_PRESSED)
		rot+=kk*dt;
	if (pd->isKeyPressed(DIK_SYSRQ)==KEY_DOWN)
		pd->PrintScreen();
	_iii+=dt;
	_map.Update(dt);
	gen=gen%2;
	dtt=dt;
	cs->Camera->Pos=cpos;
	WriteMsg("-->EndStep");
}
void DrawCamera(PCamera c)
{
	DrawLine(c->Pos,c->Pos+c->Up,0xff00ff00,0xff00ff00);
	DrawLine(c->Pos,c->At,0xff00ff00,0xff00ff00);
	Vector3 v[8];
	CalcCameraVertices(c->FOV, c->Aspect, c->ZNear, c->ZFar,
		c->Pos, c->At, c->Up, v);
	DrawLine(v[0],v[3],0xff0000ff,0xff0000ff);
	DrawLine(v[2],v[3],0xff0000ff,0xff0000ff);
	DrawLine(v[2],v[1],0xff0000ff,0xff0000ff);
	DrawLine(v[0],v[1],0xff0000ff,0xff0000ff);

	DrawLine(v[7],v[6],0xff0000ff,0xff0000ff);
	DrawLine(v[6],v[5],0xff0000ff,0xff0000ff);
	DrawLine(v[5],v[4],0xff0000ff,0xff0000ff);
	DrawLine(v[4],v[7],0xff0000ff,0xff0000ff);

	DrawLine(v[3],v[7],0xffffff00,0xffffff00);
	DrawLine(v[2],v[6],0xffffff00,0xffffff00);
	DrawLine(v[1],v[5],0xffff0000,0xffff0000);
	DrawLine(v[0],v[4],0xffff0000,0xffff0000);

}
void	DrawFade(float progress)

{
///	if (!pd->PrepareScene()) return;
	__GetDevice()->SetTexture(0,NULL);
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,0);
//	pd->PresentScene();
	fr->SetColor(0,D3DCOLOR_ARGB((BYTE)(progress*255),0,0,0));
	fr->SetColor(1,D3DCOLOR_ARGB((BYTE)(progress*255),0,0,0));
	fr->SetColor(2,D3DCOLOR_ARGB((BYTE)(progress*255),0,0,0));
	fr->SetColor(3,D3DCOLOR_ARGB((BYTE)(progress*255),0,0,0));
	fr->Update();
	fr->Draw();
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,1);
}
void	DrawLoading(float progress,char *text)

{
	if (!pd->PrepareScene()) return;
//background
	pd->SetState(PIE_TFILTERING,1);
	PFont ff=pd->SManager.UI->Font;
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,0);
	pd->SManager.GetScene(0)->ResourceManager.Textures[0]->Set(0);
	rr->Update();

	rr->Draw();
	__GetDevice()->SetTexture(0,NULL);
	ld1->Update();
	ld1->Draw();
	ld2->v[2].p.x=ld2->v[0].p.x+313*min(1.0f,progress);
	ld2->v[3].p.x=ld2->v[0].p.x+313*min(1.0f,progress);
	ld2->Update();
	ld2->Draw();
	ff->Color=0xff06a445;
	ff->PDrawText(0,pd->GetScreenHeight()-30,text);
	__GetDevice()->SetRenderState(D3DRS_FOGENABLE,1);
	float _fade=progress-1.0f;
	if (_fade<0) 
		_fade=0;
	else 
		DrawFade(_fade);
	pd->PresentScene();
}
void Scene1Draw(DWORD Scene)
{
//	DrawLoading(0,"wdwd");
//	WriteMsg("-->Begin Drawing");
	PScene cs=(PScene)Scene;
//	ft[0] = timeGetTime();
//	WriteMsg("-->Getting terrain value");
	float _t=_map.Terrain->HMap->GetHeightValue(c->Pos.x,c->Pos.z);
	if (cpos.y-_t<=cs->Camera->ZNear+0.01f)
	{
		cpos.y=_t+cs->Camera->ZNear+0.05f;
	}
//	lt[0] = timeGetTime() - ft[0];
//	ft[1] = timeGetTime();
	cs->Camera->Pos=cpos;
	cs->Camera->At=c2;
//	WriteMsg("-->Assigning camera");
	cs->Camera->Assign(pd->GetDevice());/**/

//	lt[1] = timeGetTime() - ft[1];
//	ft[2] = timeGetTime();
	PFont ff=pd->SManager.UI->Font;
	char res[512];
	ZeroMemory(res,512);
	int xx1=-1,yy1=-1,x1,y1;
//	WriteMsg("-->Setting up state");
	pd->SetState(PIE_TFILTERING,1);
//	lt[2] = timeGetTime() - ft[2];
//	ft[3] = timeGetTime();
//	WriteMsg("-->Drawing terrain");
	_map.Render();//.Terrain->Draw();//>Tiles[0].Draw();
//	WriteMsg("-->Getting mouse pos");
	pd->GetMouseDelta(&xx1,&yy1);
	x1=_map.Terrain->HMap->dr;
	y1=_map.Terrain->HMap->undr;
//	WriteMsg("-->Creating text");
	DrawLine(Vector3(0,0,0),Vector3(0,100,0),0xffff0000,0xffff0000);

//	WriteMsg("-->Setting up state");
	pd->SetState(PIE_TFILTERING,1);
//	WriteMsg("-->Setting up state");
	pd->SetState(PIE_FOGENABLE,0);
//	WriteMsg("-->Drawing text");
//	lt[3] = timeGetTime() - ft[3];
//	lt = timeGetTime() - ft;
	sprintf(res,"FPS:%f %d;\nMX:%d;MY:%d;\nIII:%d;gen:%d\nPart. count:%d\n%d\\%d\nx:%f y:%f z:%f\n%d %d\n %d %d",pd->GetFPS(),(DWORD)(_iii*24),xx1,yy1,iii,gen,0/*_sc->ResourceManager.Models[0]->Ps->ParticlesActive*/,x1,y1,tline.x,tline.y,tline.z,pd->StepTime, pd->DrawTime, _map.ModelsTime, _map.TerrainTime);
	ff->PDrawTextEx(0,0,640,480,0xffff0000,0xffff0000,GR_NONE,res);
//	WriteMsg("-->Setting up state");
	pd->SetState(PIE_FOGENABLE,1);
//	WriteMsg("-->EndDrawing");
	DWORD ct=timeGetTime();
	if (fade>1){
		DrawFade(1.0f-(float)min(2000,(ct-ST))/2000.0f);
		fade=2.0f-(float)(ct-ST)/2000.0f;
	}
	if (efade>=1.0f){
		DrawFade((float)min(2000,(ct-sT))/2000.0f);
		efade=1.0f+(float)(ct-sT)/2000.0f;
	}
	if (efade>=2.0f) 		pd->Exit();
	//*/
	_T=ct;
}
bool MyRelease()
{
//	rr->Release();//,fr=NULL,ld1=NULL,ld2=NULL;
	_map.Release();
	return 1;
}
bool MyInit()
{
	DWORD tt=timeGetTime();
	while (timeGetTime()-tt<100);
	rr=new CPRect;
	rr->SetColor(0,0xffffffff);
	rr->SetColor(1,0xffffffff);
	rr->SetColor(2,0xffffffff);
	rr->SetColor(3,0xffffffff);
	rr->SetPos(0,Vector3((pd->GetScreenWidth()-640)/2.0f,0,0));
	rr->SetPos(2,Vector3((pd->GetScreenWidth()-640)/2.0f+640,0,0));
	rr->SetPos(3,Vector3((pd->GetScreenWidth()-640)/2.0f+640,480,0));
	rr->SetPos(1,Vector3((pd->GetScreenWidth()-640)/2.0f,480,0));
	rr->SetTCoord(0,0,0);
	rr->SetTCoord(2,1,0);
	rr->SetTCoord(3,1,1);
	rr->SetTCoord(1,0,1);
	//fade rect;
	fr=new CPRect;
	fr->SetColor(0,0xff000000);
	fr->SetColor(1,0xff000000);
	fr->SetColor(2,0xff000000);
	fr->SetColor(3,0xff000000);
	fr->SetPos(0,Vector3(0,0,0));
	fr->SetPos(2,Vector3(pd->GetScreenWidth(),0,0));
	fr->SetPos(3,Vector3(pd->GetScreenWidth(),pd->GetScreenHeight(),0));
	fr->SetPos(1,Vector3(0,pd->GetScreenHeight(),0));
	fr->SetTCoord(0,0,0);
	fr->SetTCoord(2,1,0);
	fr->SetTCoord(3,1,1);
	fr->SetTCoord(1,0,1);
	fr->Update();

	ld1=new CPRect;
	ld1->SetColor(0,0xff06a445);
	ld1->SetColor(1,0xff06a445);
	ld1->SetColor(2,0xff06a445);
	ld1->SetColor(3,0xff06a445);
	ld1->SetPos(0,Vector3((pd->GetScreenWidth()-320)/2.0f,pd->GetScreenHeight()-60,0));
	ld1->SetPos(2,Vector3((pd->GetScreenWidth()-320)/2.0f+320,pd->GetScreenHeight()-60,0));
	ld1->SetPos(3,Vector3((pd->GetScreenWidth()-320)/2.0f+320,pd->GetScreenHeight()-30,0));
	ld1->SetPos(1,Vector3((pd->GetScreenWidth()-320)/2.0f,pd->GetScreenHeight()-30,0));
	ld1->SetTCoord(0,0,0);
	ld1->SetTCoord(2,1,0);
	ld1->SetTCoord(3,1,1);
	ld1->SetTCoord(1,0,1);
	ld1->Update();

	ld2=new CPRect;
	ld2->SetColor(0,0xff1b5438);
	ld2->SetColor(1,0xff1b5438);
	ld2->SetColor(2,0xff1b5438);
	ld2->SetColor(3,0xff1b5438);
	ld2->SetPos(0,Vector3((pd->GetScreenWidth()-320)/2.0f+3,pd->GetScreenHeight()-60+3,0));
	ld2->SetPos(2,Vector3((pd->GetScreenWidth()-320)/2.0f+320-3,pd->GetScreenHeight()-60+3,0));
	ld2->SetPos(3,Vector3((pd->GetScreenWidth()-320)/2.0f+320-3,pd->GetScreenHeight()-30-3,0));
	ld2->SetPos(1,Vector3((pd->GetScreenWidth()-320)/2.0f+3,pd->GetScreenHeight()-30-3,0));
	ld2->SetTCoord(0,0,0);
	ld2->SetTCoord(2,1,0);
	ld2->SetTCoord(3,1,1);
	ld2->SetTCoord(1,0,1);
	ld2->Update();
	c=new CCamera;
	c->SetCPlanes(2.0f,200.0f);
	c->SetFA((FLOAT)D3DX_PI/4,(FLOAT)pd->GetScreenWidth()/pd->GetScreenHeight());
	c->SetPos(Vector3(512,80,512));
	tline=Vector3(255,80,255);
	c->SetTarget(Vector3(0,0,0));
	c->SetUp(Vector3(0,1,0));
	c->Set();
	pd->SetState(PIE_FOGENABLE,1);
	pd->SetState(PIE_FOGMODE,D3DFOG_LINEAR);
	pd->SManager.NewScene("Scene01");
	pd->SetBGColor(D3DCOLOR_XRGB(0,0,0));
	if (!pd->SManager.UI->Font->LoadFont("textures\\font.ptt"))
		return 0;
	PScene sc=pd->SManager.GetScene(0);
	sc->ResourceManager.AddResource(RESOURCE_TEXTURE,"Textures\\UI\\LScreen.ptt"," ");
	PFont ff=pd->SManager.UI->Font;
	_LoadPresets("Data\\ps.pps");
	_map.SetProgressFunction(DrawLoading);
	_map.LoadFromFile(pd->Map);//map.pm");
	float fs=c->ZNear+(float)(c->ZFar-c->ZNear)*_map.fnear,fe=c->ZNear+(float)(c->ZFar-c->ZNear)*_map.ffar;
	pd->SetState(PIE_FOGSTART,*((DWORD*)(&fs)));
	pd->SetState(PIE_FOGEND,*((DWORD*)(&fe)));
	sc->ResourceManager.psm.NewParticleSystem("TestBoom01",_Presets()->GetPreset("Boom01"));
	//loading back rect
	sc->AssignStepFunc(Scene1Step);
	sc->AssignDrawFunc(Scene1Draw);
	ff->Color=0xFFFFFFFF;
	ff->Height=18;
	ff->Width=18;
	ff->Sm=1;
	ff->spx=-2;
	ff->spy=-2;
	pd->AddDirectionalLight(clWhite,clBlack,clWhite,Vector3(-1,-1,-1),1000.0f,1.0f,1.0f,1.0f,1);
/*	d=new CCamera;
	d->SetCPlanes(2.0f,1000.0f);
	d->SetFA((FLOAT)D3DX_PI/4,(FLOAT)pd->GetScreenWidth()/pd->GetScreenHeight());
	d->SetPos(Vector3(128,255,128));
	d->SetTarget(Vector3(0,0,0));
	d->SetUp(Vector3(0,1,0));*/
	cpos=c->Pos;
	c2=Vector3(0,0,0);
	sc->Camera=c;
	fade=1.0f;
	DWORD __ttt=timeGetTime();
	while (timeGetTime()-__ttt<2000)
	{
		DrawLoading(1.0f+(float)(timeGetTime()-__ttt)/2000.0f," ");
	}
	_T=timeGetTime();
	ST=_T;
	sT=_T;
	fade=2.0f;
	pd->SetBGColor(_map.BGcolor);
	pd->SetState(PIE_FOGCOLOR,_map.BGcolor);
	return 1;
}
DWORD cct,llt;
	char res[256];
bool MyDraw()
{
	return 1;
}
bool MyStep()
{
	tc=pd->GetTime();
	return 1;
}
int WINAPI WinMain(HINSTANCE hinstance,
				   HINSTANCE hprevinstance,
				   LPSTR LpCmdLine,
				   int nCmdShow)
{
	bool b;
	pd=new CPie();
	pd->SetState(PIE_INIT_FUNC,(DWORD)MyInit);
	pd->SetState(PIE_DRAW_FUNC,(DWORD)MyDraw);
	pd->SetState(PIE_FRAME_FUNC,(DWORD)MyStep);
	pd->SetState(PIE_EXIT_FUNC,(DWORD)MyRelease);
/*	if (!pd->Init(hinstance))
		return 0;*/
	int res=pd->Run(hinstance);
	return res;
}
