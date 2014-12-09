#include"stdafx.h"
#include"pie.h"
DWORD lt=0,_llt=0;
WORD  fr=0;
BYTE dest[1600*1200];
CPie::CPie()
{
	_Start();
	GUI kk=this->SManager.UI;
	ZeroMemory(this,sizeof(CPie));
	SManager.UI=kk;
	GetCurrentDirectoryA(1024,szAppPath);
	szAppPath[strlen(szAppPath)]='\\';
	strcpy(szIniFile,szAppPath);
	strcpy(szLogFile,szAppPath);
	strcat(szIniFile,INI_FILE);
	strcat(szLogFile,LOG_FILE);
	DeleteFileA(szLogFile);
/*	PFile f=new CPFile;
	f->Open(szLogFile,FILE_WRITE);
	f->Close();*/
	DWORD ct=timeGetTime();
	ClearErrorQueue();
//	char dta[128];
//	ZeroMemory(dta,128);
//	sprintf(dta,"%s%d","Time: ",&ct);
	//System_Log("|-----|PIE Engine|-----|\n%c-->Version 1.011\n	-->Current time : %d",9,ct);
	WriteMsg("|-----|PIE Engine|-----|");
	WriteMsg("Version 1.011");
	WriteTime(NULL);
	WriteDate(NULL);
	WriteMsg("Preparing...");
	WriteMsg("App path:'%s'",szAppPath);
	//System_Log("%c-->App path:'%s'",9,szAppPath);
	AddTab();
//	delete f;
}
LRESULT CALLBACK MainWinProc(
							 HWND	hwnd,
							 UINT	msg,
							 WPARAM	wparam,
							 LPARAM lparam)
{
	switch (msg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
			break;
		}
/*	case WM_KEYDOWN:
		{
			if (wparam==VK_ESCAPE){
				PostQuitMessage(0);
				return 0;
				break;
			}
		}
/*	case WM_ACTIVATEAPP:
		{
			if (Render) Render=0; else Render=1;
			break;
		}*/
	}
	return(DefWindowProc(hwnd,msg,wparam,lparam));
}
void CPie::SetState(Pie_States State,DWORD Value)
{
	switch (State){
		case PIE_INIT_FUNC:
			procUserInit=(PIECallback)Value;
			break;
		case PIE_FRAME_FUNC:
			procFrameFunc=(PIECallback)Value;
			break;
		case PIE_DRAW_FUNC:
			procRenderFunc=(PIECallback)Value;
			break;
		case PIE_GFXR_FUNC:
			procGfxRestoreFunc=(PIECallback)Value;
			break;
		case PIE_EXIT_FUNC:
			procExitFunc=(PIECallback)Value;
			break;
		case PIE_BWIDTH:
			ScrWidth=Value;
			d3dp.BackBufferWidth=Value;
			break;
		case PIE_BHEIGHT:
			ScrHeight=Value;
			d3dp.BackBufferHeight=Value;
			break;
		case PIE_BFORMAT:
			ScrFormat=(D3DFORMAT)Value;
			d3dp.BackBufferFormat=(D3DFORMAT)Value;
			break;
		case PIE_BWINDOWED:
			d3dp.Windowed=Value;
			break;
		case PIE_BRRATE:
			d3dp.FullScreen_RefreshRateInHz=Value;
			break;
		case PIE_BMULTIS:
			if (Value) d3dp.MultiSampleType=(D3DMULTISAMPLE_TYPE)1;
			else d3dp.MultiSampleType=D3DMULTISAMPLE_NONE;
			break;
		case PIE_BGROUND:
			BGround=Value;
			break;
		case PIE_FILLMODE:
			if (Value) d3dd->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
			else d3dd->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
			break;
		case PIE_LIGHTENABLE:
			if (Value) d3dd->SetRenderState(D3DRS_LIGHTING,true);
			else d3dd->SetRenderState(D3DRS_LIGHTING,false);
			break;
		case PIE_TFILTERING:
			if (Value)
			{
				d3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
				d3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
				d3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
			}
			else
			{
				d3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_NONE );
				d3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_NONE );
				d3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_NONE );
			}
			break;
		case PIE_BLENDMODE:
			if (Value)
			{
				d3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_ONE );
				d3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_ONE );
			}
			else
			{
				d3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
				d3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
			}
			break;
		case PIE_TENABLE:
			break;
		case PIE_FOGENABLE:
				d3dd->SetRenderState( D3DRS_FOGENABLE,         Value );
			break;
		case PIE_FOGSTART:
				d3dd->SetRenderState( D3DRS_FOGSTART,         Value );
			break;
		case PIE_FOGEND:
				d3dd->SetRenderState( D3DRS_FOGEND,         Value );
			break;
		case PIE_FOGCOLOR:
				d3dd->SetRenderState( D3DRS_FOGCOLOR,         Value );
			break;
		case PIE_FOGMODE:
				d3dd->SetRenderState( D3DRS_FOGVERTEXMODE,         Value );
			break;
	}

}
/*bool CPie::LoadMesh(LPCSTR FName,LPCSTR MName,LPCSTR tfname,FLOAT athres,FLOAT vthres,FLOAT txtrthres,bool InvertNormals)
{
	Meshes[MeshCount]=new CMesh;
	if (!Meshes[MeshCount]->LoadMesh(FName,tfname,athres,vthres,txtrthres,InvertNormals)){
		delete Meshes[MeshCount];
		return 0;
	}
	strcpy(Meshes[MeshCount]->name,MName);
	MeshCount++;
	return 1;
}
PMesh CPie::FindMesh(LPCSTR _mname)
{
	for (WORD i=0;i<MeshCount;i++)
	{
		if (strcmp(_mname,Meshes[i]->name)==0)
			return Meshes[i];
	}
	return 0;
}*/
void CPie::UpdateLight(WORD index)
{
	d3dd->SetLight(index,&Lights[index]);
}
void CPie::SetLightPos(WORD index,Vector3 pos)
{
	Lights[index].Position.x=pos.x;
	Lights[index].Position.y=pos.y;
	Lights[index].Position.z=pos.z;
}
/*void CPie::CreateModel(LPCSTR mname,WORD index,PModel mdl)
{
	mdl->AssignMesh(FindMesh(mname),index);
}*/
bool CPie::Step()
{
/*	HRESULT hr=d3dd->TestCooperativeLevel();
	if (FAILED(hr))
		return 0;
	if (hr==D3DERR_DEVICENOTRESET)
	{
		d3dd->Release();
		WriteMsg("-->Reseting device and resources.");
		if (!ResetD3D())
		{
			WriteMsg("-->Failed to reinit d3d.");
			return 0;
		}
		if (procFocusGainFunc)
		{
			if (!(procFocusGainFunc)())
			{
				WriteMsg("-->User gain focus proc failed.");
				return 0;
			}
		}
		DeviceLost=0;
	}
	if (hr==D3DERR_DEVICELOST)
	{
		DeviceLost=1;
	}*/
	UpdateDirectInput();
	SManager.Update((FLOAT)GetDTime()/1000);
/*	if (procFrameFunc)
	{
/*		if (!(procFrameFunc)())
		{
			System_Log("User frame func failed.");
			return 0;
		}
	}*/
	return 1;
}

bool CPie::LoadFilter(LPCSTR FName,PFilter _f)
{
	char temp[MAX_PATH];
	ZeroMemory(temp,sizeof(temp));
	strcpy(temp,szAppPath);
	strcat(temp,FName);
	return _f->Load(temp);
}
void CPie::ApplyFilter(PFilter f)
{
	LPDIRECT3DSURFACE9 _BackBuffer=NULL;
//	d3dd->CreateOffscreenPlainSurface(ScrWidth,ScrHeight,ScrFormat,D3DPOOL_DEFAULT,&_BackBuffer,NULL);
	D3DLOCKED_RECT r;
	RECT rr;
	rr.left=0;
	rr.top=0;
	rr.bottom=ScrHeight-1;
	rr.right=ScrWidth-1;
	HRESULT hr;
	hr=D3DERR_INVALIDCALL;
	hr=d3dd->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_BackBuffer);
	hr=_BackBuffer->LockRect(&r,&rr,D3DLOCK_READONLY);
	f->ApplyEffect((BYTE*)r.pBits,dest,ScrWidth,ScrHeight);
	_BackBuffer->UnlockRect();
	hr=_BackBuffer->LockRect(&r,NULL,D3DLOCK_DISCARD);
	memcpy(r.pBits,dest,ScrWidth*ScrHeight);
	_BackBuffer->UnlockRect();
//	DELETE(dest);
}
bool CPie::CWindow()
{
	WNDCLASSEX wc;/* = {sizeof(WNDCLASSEX),CS_DBLCLKS, MainWinProc, 0L, 0L,
		hInst, hIcon, NULL, NULL, NULL,
		TEXT("PIEWndClass"), NULL
	};*/
	wc.cbClsExtra=0L;
	wc.cbSize=sizeof(WNDCLASSEX);
	wc.cbWndExtra=0L;
	wc.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.hCursor=NULL;
	wc.hIcon=hIcon;
	wc.hIconSm=NULL;
	wc.hInstance=hInst;
	wc.lpfnWndProc=(WNDPROC)&MainWinProc;
	wc.lpszClassName=L"PIEWndClass";
	wc.lpszMenuName=NULL;
	wc.style=CS_OWNDC|CS_HREDRAW|CS_VREDRAW;
	if (!(RegisterClassEx(&wc))){
		return 0;
	}
	hWnd=PIECreateWindow(hInst,WS_EX_TOPMOST,DIR3D_WND,"PIEWndClass","]PIE Engine[",0,0,200,200,1);
	ShowWindow(hWnd,SW_SHOWDEFAULT);
	UpdateWindow(hWnd);
	return 1;
}
void CPie::System_Log(const char *szFormat, ...)
{
	FILE *hf = NULL;
	va_list ap;
	
	if(!szLogFile[0]) return;

	hf = fopen(szLogFile, "a");
	if(!hf) return;

	va_start(ap, szFormat);
	vfprintf(hf, szFormat, ap);
	va_end(ap);

	fprintf(hf, "\n");

	fclose(hf);
}
void    CPie::UpdateDirectInput()
{
	UpdateMouseDataImmediate();
	UpdateKeyboardDataImmediate();
}
bool					CPie::PrepareScene(){
	if (FAILED(d3dd->BeginScene())) return 0;
	d3dd->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,BGround,1.0f,0);//0L
	return 1;

}
void					CPie::PresentScene(){
		d3dd->EndScene();
		d3dd->Present(NULL,NULL,NULL,NULL);
}
bool CPie::Init(HINSTANCE hinst)
{
	hInst=hinst;//SManager.Presets.rm=GetPSTexture;
	if (!CWindow())
	{
		WriteMsg("-->Window init failed.");
		return 0;
	}
	if (!InitD3D())
	{
		WriteMsg("-->D3D init failed.");
		return 0;
	}
	if (FAILED(InitDirectInput()))
	{
		WriteMsg("-->DInput init failed.");
		return 0;
	}
	//Reading some stuff from ini
	{
		char _fname[50];
		ZeroMemory(_fname,sizeof(_fname));
		char _dir[50];
		ZeroMemory(_dir,sizeof(_dir));
		ZeroMemory(Map,sizeof(Map));
		strcpy(_dir,this->Ini_GetString("SCREENSHOT","Directory",_dir));
		strcpy(_fname,this->Ini_GetString("SCREENSHOT","FileName",_fname));
		strcpy(Map,this->Ini_GetString("MAP","FileName","nothing"));
		if (strcmp(Map,"nothing")==0){
			WriteMsg("-->No map to load.");
			return 0;
		}
		ZeroMemory(ScPath,sizeof(ScPath));
		strcpy(ScPath,this->szAppPath);
		strcat(ScPath,_dir);
		if (ScPath[strlen(ScPath)-1]!='\\'&&strlen(ScPath)!=0)
		{
			ScPath[strlen(ScPath)]='\\';
		}
		CreateDirectoryA(ScPath,NULL);
		ZeroMemory(ScFormat,sizeof(ScFormat));
		strcpy(ScFormat,ScPath);
		strcat(ScFormat,_fname);
		strcat(ScFormat,"%s.jpg");
		ScScount=this->Ini_GetInt("SCREENSHOT","Count",0);
		this->Ini_SetInt("SCREENSHOT","Count",0);
	}
	if (procUserInit){
		if (!(procUserInit)())
		{
			WriteMsg("-->User init failed.");
			return 0;
		}
	}
	WriteMsg("-->User init success.");
	lt=_llt=timeGetTime();
	return 1;
}
void CPie::WindowToggleFullScreen(bool isFullScreen)
{
	DWORD Style;
	int x,y,w,h;
	if (isFullScreen)
	{
		Style=DIR3D_WND;
		x=0;
		y=0;
		w=ScrWidth;
		h=ScrHeight;
	}
	else
	{
		Style=DEFAULT_WND;
		w=ScrWidth+GetSystemMetrics(SM_CXFIXEDFRAME)*2;
		h=ScrHeight + GetSystemMetrics(SM_CYFIXEDFRAME)*2 + GetSystemMetrics(SM_CYCAPTION);
		x=(GetSystemMetrics(SM_CXSCREEN)-w)/2;
		y=(GetSystemMetrics(SM_CYSCREEN)-h)/2;
	}
	SetWindowLong(hWnd,GWL_STYLE,Style);
	SetWindowPos(hWnd,HWND_TOPMOST,x,y,w,h,SWP_SHOWWINDOW);
	UpdateWindow(hWnd);
	/*
	styleW := WS_POPUP or WS_VISIBLE or WS_CAPTION or WS_SYSMENU or WS_MINIMIZEBOX;
	styleFS := WS_POPUP or WS_VISIBLE ;
	width  := ScrWidth + GetSystemMetrics(SM_CXFIXEDFRAME)*2;
	height := ScrHeight + GetSystemMetrics(SM_CYFIXEDFRAME)*2 + GetSystemMetrics(SM_CYCAPTION);	rectW.left := (GetSystemMetrics(SM_CXSCREEN)-width) div 2;
	rectW.top := (GetSystemMetrics(SM_CYSCREEN)-height) div 2;
	rectW.right := rectW.left + width;
	rectW.bottom := rectW.top + height;

	rectFS.left := 0;
	rectFS.top := 0;
	rectFS.right := ScrWidth;
	rectFS.bottom := ScrHeight;

	if windowed then
	Wnd := CreateWindowEx( 0, WINDOWCLASSNAME, pchar(WNDTITLE), styleW, rectW.left,
		  rectW.top, rectW.right-rectW.left, rectW.bottom-rectW.top, 0, 0, Instance, nil)
	else
	Wnd := CreateWindowEx( 0, WINDOWCLASSNAME, pchar(WNDTITLE), styleFS, 0, 0, 0, 0, 0, 0, Instance, nil);*/
}
void CPie::ToggleFullScreen(bool isFullScreen)
{
	bool ww=d3dp.Windowed;
	SManager.Release();
	MRelease();
	RELEASE(d3dd);
	WindowToggleFullScreen(isFullScreen);//!
	if (ww!=isFullScreen)
		return;
	d3dp.Windowed=!isFullScreen;//!
	WORD w=ScrWidth;
	WORD h=ScrHeight;
	if (!ReInitD3D())
	{
		ScrWidth=d3dp.BackBufferWidth;
		ScrHeight=d3dp.BackBufferHeight;
		WindowToggleFullScreen(isFullScreen);
		d3dp.BackBufferWidth=dModeList[0].Width;
		d3dp.BackBufferHeight=dModeList[0].Height;
		d3dp.FullScreen_RefreshRateInHz=dModeList[0].RefreshRate;
		if (!ReInitD3D())
		{
			WindowToggleFullScreen(ww);
			d3dp.BackBufferWidth=w;
			d3dp.BackBufferHeight=h;
			d3dp.Windowed=ww;
			ScrWidth=w;
			ScrHeight=h;
			ReInitD3D();
		}
		else
		{
			ScrWidth=d3dp.BackBufferWidth;
			ScrHeight=d3dp.BackBufferHeight;
		}
	}
}
void CPie::Exit()
{
	_exit=1;
}
int CPie::Run(HINSTANCE hinstance)
{
	MSG msg;
	DWORD _lt,_llt, _lstep, _ldraw;
	DWORD cnt1 = 0, cnt2 = 0;
	_lt=_llt=timeGetTime();
		ZeroMemory(&msg,sizeof(msg));
	if (Init(hinstance))
	{
		System_Log("	Running...");
		_ldraw = timeGetTime();
		while(msg.message!=WM_QUIT&&!bError())
		{
			if (PeekMessage(&msg,NULL,0,0,PM_REMOVE)){
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else{
				DWORD ct=timeGetTime();
				if (DeviceLost&&(ct-lt<3000))
				{
					//do nothing
				}
				else
				{
					_lt=timeGetTime();
					if (_lt-_llt>=20)
					{
						//WriteMsg("-->Step");
						_lstep = timeGetTime();
						if (!Step())
							return 0;
						StepTime = timeGetTime() - _lstep;
						//WriteMsg("-->Render");
						_ldraw = timeGetTime();
						Render();
						DrawTime = timeGetTime() - _ldraw;
						if (_exit)
							break;
						_llt=_lt;
					}
				}
			}
		}
	}
	Release();
	RemTab();
	WriteMsg("-->Releasing engine");
	WriteMsg("-->Total running time");
	WriteMsg("Errors:%d;",GetErrorCount());
	WriteErrors(szLogFile);

	return msg.wParam;
}
bool CPie::InitD3D()
{
	//Checking existance...
	pd3d=NULL;
	pd3d=PIECreate3D();
	if (pd3d==NULL)
	{
		WriteMsg("-->Unable to create main 3D object.");
		return 0;
	}
	ModeCount=pd3d->GetAdapterModeCount(D3DADAPTER_DEFAULT,D3DFMT_X8R8G8B8);
	for (int i=0;i<ModeCount;i++)
	{
		if (FAILED(pd3d->EnumAdapterModes(D3DADAPTER_DEFAULT,D3DFMT_X8R8G8B8,i,&dModeList[i])))//GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&dModeList[i])))
		{
			WriteMsg("-->Unable to get display mode info.");
			return 0;
		}
		if (dModeList[i].Width<640)
		{
			i--;
			ModeCount--;
		}
	}
	bool Ex=1;
	GlowEnable=0;
	if (FileExists(szIniFile))
	{
		ScrWidth	= Ini_GetInt("VIDEO","Width",-1);
		ScrHeight	= Ini_GetInt("VIDEO","Height",-1);
		ScrFormat	= (D3DFORMAT)Ini_GetInt("VIDEO","Format",-1);
		ScrRRate	= Ini_GetInt("VIDEO","Refresh_Rate",-1);
		GlowEnable	= Ini_GetInt("VIDEO","GlowEnable",0);
		Ini_SetInt("VIDEO","GlowEnable",GlowEnable);
		if (ScrWidth==-1||ScrHeight==-1||ScrRRate==-1||ScrFormat==-1)
		{
			Ex=0; 
			WriteMsg("-->Screen data doesn't exist. Creating...");
		}
	}
	else
	{
		Ex=0;
		WriteMsg("-->Ini file doesn't exist. Creating...");
	}
	if (!Ex)
	{
		int i=0;
		for (int i=0;i<ModeCount;i++)
		{
		}
		ScrWidth	= dModeList[0].Width;
		ScrHeight	= dModeList[0].Height;
		ScrRRate	= dModeList[0].RefreshRate;
		ScrFormat	= dModeList[0].Format;
		Ini_SetInt("VIDEO","Width",ScrWidth);
		Ini_SetInt("VIDEO","Height",ScrHeight);
		Ini_SetInt("VIDEO","Format",(int)ScrFormat);
		Ini_SetInt("VIDEO","Refresh_Rate",ScrRRate);
		Ini_SetInt("VIDEO","GlowEnable",GlowEnable);
	}
	d3dp.BackBufferCount			= 1;
	d3dp.BackBufferFormat			= ScrFormat;
	d3dp.BackBufferWidth			= ScrWidth;
	d3dp.BackBufferHeight			= ScrHeight;
	d3dp.FullScreen_RefreshRateInHz = ScrRRate;
	int an=Ini_GetInt("VIDEO","Antialias",-1);
	if (an==-1)
	{
		an=0;
		Ini_SetInt("VIDEO","Antialias",0);
	}
	int wm=Ini_GetInt("VIDEO","Windowed",-1);
	if (wm==-1)
	{
		wm=0;
		Ini_SetInt("VIDEO","Windowed",0);
	}
	if (wm)
		d3dp.FullScreen_RefreshRateInHz	= 0;
	d3dp.hDeviceWindow=hWnd;
	d3dp.Windowed						= wm;
	d3dp.MultiSampleType				= (D3DMULTISAMPLE_TYPE)an;
	d3dp.MultiSampleQuality				= 0;
	d3dp.EnableAutoDepthStencil			= TRUE;
	d3dp.SwapEffect						= D3DSWAPEFFECT_DISCARD;//D3DSWAPEFFECT_COPY;;
	d3dp.PresentationInterval			= D3DPRESENT_INTERVAL_IMMEDIATE;//0x80000000;//
	d3dp.Flags							= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dp.AutoDepthStencilFormat			= D3DFMT_D16;
	WindowToggleFullScreen(!wm);
	if (!ReInitD3D())
	{
		d3dp.AutoDepthStencilFormat			= D3DFMT_D32;
		return ReInitD3D();
	}
	return 1;
}
void CPie::AssignCamera(PCamera _Camera)
{
	Camera=_Camera;
}
DWORD CPie::GetTime()
{
	return timeGetTime();
}
void CPie::ViewCamera(PCamera _Camera)
{
	_Camera->Assign(d3dd);
}
void CPie::Render()
{
	DWORD ct=timeGetTime();
	DTime=ct-_llt;
	_llt=ct;

	if (ct-lt>=1000)
	{
		Fps=(float)((fr)*1000)/(ct-lt);
		lt=ct;
		fr=0;
	}
//	System_Log("Clearing");
//	System_Log("Begining scene");
//	WriteMsg("-->Beginning scene");
		d3dd->SetRenderState(D3DRS_ZENABLE,1);
		d3dd->SetRenderState(D3DRS_ZWRITEENABLE,1);
	HRESULT xx=d3dd->BeginScene();
//	WriteMsg("-->Result %ld",xx);
//	DisableMessages();
	if (!FAILED(xx))
	{
//		WriteMsg("-->Success");
		d3dd->Clear(0,NULL,D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,BGround,1.0f,0);//0L
		if (Camera)
			Camera->Assign(d3dd);
//		if (procRenderFunc)
//			(procRenderFunc)();
		SManager.Draw();
		fr++;
//		System_Log("Ending scene");
/*		if (isKeyPressed(DIK_P)){
			if (cct-llt>=100){
				PrintScreen("ScrnShot.jpg");
				llt=pd->GetTime();
			}
		}*/
//		WriteMsg("-->Ending Scene");
		d3dd->EndScene();
//		WriteMsg("-->Success");
//		WriteMsg("-->Presenting Scene");
		d3dd->Present(NULL,NULL,NULL,NULL);
	//	WriteMsg("-->Success");
	EnableMessages();
	}
	else
	{
	//	WriteMsg("-->Failed");
	}
//	System_Log("Presenting scene");
//	System_Log("Success");
}
void CPie::SetBGColor(DWORD _color)
{
	BGround=_color;
}
float CPie::GetFPS()
{
	return Fps;
}
void CPie::AddPointLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Position,float Range,
									float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled)
{
	D3DVECTOR x,y;
	x.x=Position.x;
	x.y=Position.y;
	x.z=Position.z;
	y.x=1.0f;
	y.y=0.0f;
	y.z=0.0f;
/*	y.x=Direction.x;
	y.y=Direction.y;
	y.z=Direction.z;*/
	AddLight(D3DLIGHT_POINT,Diffuse,Ambient,Specular,y,x,0.0f,
		0.0f,Range,0.0f,Attenuation0,Attenuation1,Attenuation2,Enabled);
}
void CPie::AddSpotLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Position,Vector3 Direction,float InnerCone,
									float OuterCone,float Falloff,float Range,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled)
{
	D3DVECTOR x,y;
	x.x=Position.x;
	x.y=Position.y;
	x.z=Position.z;
	y.x=Direction.x;
	y.y=Direction.y;
	y.z=Direction.z;
	AddLight(D3DLIGHT_SPOT,Diffuse,Ambient,Specular,y,x,Falloff,
		OuterCone,Range,InnerCone,Attenuation0,Attenuation1,Attenuation2,Enabled);
}
void CPie::DeleteLight(WORD index)
{
	if (LightCount==0)
		return;
	index%=LightCount;
	d3dd->LightEnable(index,0);
	LightCount--;
	if (index!=LightCount)
		swap(Lights[index],Lights[LightCount]);
	ZeroMemory(&Lights[LightCount],sizeof(D3DLIGHT9));
}
void CPie::EnableLight(WORD index,bool Enabled)
{
	if (LightCount==0)
		return;
	index%=LightCount;
	d3dd->SetLight(index,&Lights[index]);
	d3dd->LightEnable(index,Enabled);
}
void CPie::ClearLights()
{
	if (LightCount==0)
		return;
	for (int i=LightCount-1;i>=0;i--)
	{
        DeleteLight(i);
	}
}
void CPie::AddDirectionalLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Direction,float Range,
									float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled)
{
	D3DVECTOR x,y;
	x.x=0.0f;
	x.y=0.0f;
	x.z=0.0f;
	y.x=Direction.x;
	y.y=Direction.y;
	y.z=Direction.z;
	AddLight(D3DLIGHT_DIRECTIONAL,Diffuse,Ambient,Specular,y,x,0.0f,
		0.0f,Range,0.0f,Attenuation0,Attenuation1,Attenuation2,Enabled);
}
void CPie::AddLight(D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
									D3DVECTOR Direction,D3DVECTOR Position,float Falloff,float Phi,float Range,
									float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled)
{
	if (LightCount>=16)
	{
		WriteMsg("-->Limit of lights was exceeded!");
	}
	memcpy(&Lights[LightCount].Ambient,&Ambient,16);
	memcpy(&Lights[LightCount].Diffuse,&Diffuse,16);
	memcpy(&Lights[LightCount].Specular,&Specular,16);
	memcpy(&Lights[LightCount].Position,&Position,12);
	memcpy(&Lights[LightCount].Direction,&Direction,12);
	memcpy(&Lights[LightCount].Type,&Type,4);
	Lights[LightCount].Attenuation0=Attenuation0;
	Lights[LightCount].Attenuation1=Attenuation1;
	Lights[LightCount].Attenuation2=Attenuation2;
	Lights[LightCount].Range=Range;
	Lights[LightCount].Falloff=Falloff;
	Lights[LightCount].Phi=Phi;
	Lights[LightCount].Theta=Theta;
	d3dd->SetLight(LightCount,&Lights[LightCount]);
	d3dd->LightEnable(LightCount,Enabled);
	LightCount++;
}
bool CPie::ReInitD3D()
{
	SetCursor(NULL);
	RELEASE(d3dd);
	WriteMsg("-->New video mode");
	WriteMsg("-->Width:%d; Heght:%d; Windowed:%d;",ScrWidth,ScrHeight,d3dp.Windowed);
//	ToggleFullScreen(3dp.Windowed);
	if (!PIEInitDirect3D(hWnd,pd3d,&d3dd,d3dp,D3DCREATE_SOFTWARE_VERTEXPROCESSING,DEFAULT_DEVICE))
	{
		WriteMsg("-->Unable to init direct3d device with software vertexprocessing.");
		if (!PIEInitDirect3D(hWnd,pd3d,&d3dd,d3dp,D3DCREATE_HARDWARE_VERTEXPROCESSING,DEFAULT_DEVICE))
		{
			WriteMsg("-->Unable to init direct3d device with hardware vertexprocessing.");
			WriteMsg("-->Unable to init direct3d device.");
			return 0;
		}
		else
		{
			WriteMsg("-->Initialisation direct3d device with hardware vertexprocessing - success.");
		}
	}
	else
	{
		WriteMsg("-->Initialisation direct3d device with software vertexprocessing - success.");
	}
/*	THAssignDevice(d3dd,szAppPath);
	MHAssignDevice(d3dd,szAppPath);
	FAssign(d3dd,d3dp.BackBufferWidth,d3dp.BackBufferHeight);*/
	AssignDevice(d3dd,ScrWidth,ScrHeight,szAppPath);
	if (!SManager.Reset())
		return 0;
//	ResetMeshes();
	float f=1.0f;
//	d3dd->SetRenderState(D3DRS_DEPTHBIAS,		  (DWORD)&f); 
//	d3dd->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS ,		  (DWORD)&f); 
    d3dd->SetRenderState( D3DRS_DITHERENABLE, TRUE );
	d3dd->SetRenderState(D3DRS_CULLMODE,		  D3DCULL_CW); 
//	d3dd->SetRenderState(D3DRS_NORMALIZENORMALS , TRUE);
//    d3dd->SetRenderState( D3DRS_COLORWRITEENABLE,
//            D3DCOLORWRITEENABLE_RED  | D3DCOLORWRITEENABLE_GREEN |
//            D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );
    d3dd->SetRenderState( D3DRS_CLIPPING,         TRUE );
//    d3dd->SetRenderState( D3DRS_DITHERENABLE,     TRUE );
	d3dd->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_SOLID  );
	d3dd->SetRenderState( D3DRS_LIGHTING,         FALSE );
	d3dd->SetRenderState( D3DRS_ZENABLE,          TRUE );
//	d3dd->SetRenderState( D3DRS_ZFUNC,			  D3DCMP_LESSEQUAL);
	d3dd->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
	d3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	d3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
	d3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
	d3dd->SetRenderState( D3DRS_FOGENABLE,        FALSE );
//	d3dd->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
//	d3dd->SetRenderState( D3DRS_ALPHAREF,         0x00 );
	d3dd->SetRenderState( D3DRS_ALPHAFUNC,		  D3DCMP_GREATEREQUAL );
	d3dd->SetRenderState( D3DRS_SPECULARENABLE,	  true);
//	d3dd->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,true);
	d3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	d3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	d3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
//	d3dd->SetRenderState( D3DRS_SCISSORTESTENABLE,1);
//	dest=new BYTE[ScrWidth*ScrHeight];
	return 1;
}
bool CPie::ResetD3D()
{
	SetCursor(NULL);
	WriteMsg("-->New video mode");
	WriteMsg("-->Width:%d; Heght:%d; Windowed:%d;",ScrWidth,ScrHeight,d3dp.Windowed);
//	ToggleFullScreen(3dp.Windowed);
	if (d3dd)
		RELEASE(d3dd);
	if (FAILED(d3dd->Reset(&d3dp)))
		return 0;
/*	THAssignDevice(d3dd,szAppPath);
	MHAssignDevice(d3dd,szAppPath);
	FAssign(d3dd,d3dp.BackBufferWidth,d3dp.BackBufferHeight);*/
	AssignDevice(d3dd,ScrWidth,ScrHeight,szAppPath);
	if (!SManager.Reset())
		return 0;
//	ResetMeshes();
	float f=1.0f;
//	d3dd->SetRenderState(D3DRS_DEPTHBIAS,		  (DWORD)&f); 
//	d3dd->SetRenderState(D3DRS_SLOPESCALEDEPTHBIAS ,		  (DWORD)&f); 
    d3dd->SetRenderState( D3DRS_DITHERENABLE, TRUE );
	d3dd->SetRenderState(D3DRS_CULLMODE,		  D3DCULL_CW); 
//	d3dd->SetRenderState(D3DRS_NORMALIZENORMALS , TRUE);
//    d3dd->SetRenderState( D3DRS_COLORWRITEENABLE,
//            D3DCOLORWRITEENABLE_RED  | D3DCOLORWRITEENABLE_GREEN |
//            D3DCOLORWRITEENABLE_BLUE | D3DCOLORWRITEENABLE_ALPHA );
    d3dd->SetRenderState( D3DRS_CLIPPING,         TRUE );
//    d3dd->SetRenderState( D3DRS_DITHERENABLE,     FALSE );
	d3dd->SetRenderState( D3DRS_FILLMODE,		  D3DFILL_SOLID  );
	d3dd->SetRenderState( D3DRS_LIGHTING,         FALSE );
	d3dd->SetRenderState( D3DRS_ZENABLE,          TRUE );
//	d3dd->SetRenderState( D3DRS_ZFUNC,			  D3DCMP_LESSEQUAL);
	d3dd->SetRenderState( D3DRS_ZWRITEENABLE,     TRUE );
	d3dd->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	d3dd->SetRenderState( D3DRS_SRCBLEND,         D3DBLEND_SRCALPHA );
	d3dd->SetRenderState( D3DRS_DESTBLEND,        D3DBLEND_INVSRCALPHA );
	d3dd->SetRenderState( D3DRS_FOGENABLE,        FALSE );
//	d3dd->SetRenderState( D3DRS_ALPHATESTENABLE,  TRUE );
//	d3dd->SetRenderState( D3DRS_ALPHAREF,         0x00 );
	d3dd->SetRenderState( D3DRS_ALPHAFUNC,		  D3DCMP_GREATEREQUAL );
	d3dd->SetRenderState( D3DRS_SPECULARENABLE,	  true);
//	d3dd->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE,true);
	d3dd->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	d3dd->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	d3dd->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );
//	d3dd->SetRenderState( D3DRS_SCISSORTESTENABLE,1);
//	dest=new BYTE[ScrWidth*ScrHeight];
	return 1;
}
void CPie::PrintScreen(LPCSTR Fname)
{
	LPDIRECT3DSURFACE9 _fb=NULL;
	d3dd->CreateOffscreenPlainSurface(ScrWidth,ScrHeight,(D3DFORMAT)ScrFormat,D3DPOOL_SYSTEMMEM,&_fb,NULL);
	d3dd->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_fb);
//	d3dd->GetFrontBufferData(0,_fb);
	char temp[MAX_PATH];
	ZeroMemory(temp,MAX_PATH);
	strcpy(temp,szAppPath);
	strcat(temp,Fname);
	D3DXSaveSurfaceToFileA(temp,D3DXIFF_JPG,_fb,NULL,NULL);
	_fb->Release();	
}
void CPie::PrintScreen()
{
	LPDIRECT3DSURFACE9 _fb=NULL;
	d3dd->CreateOffscreenPlainSurface(ScrWidth,ScrHeight,(D3DFORMAT)ScrFormat,D3DPOOL_SYSTEMMEM,&_fb,NULL);
	d3dd->GetBackBuffer(0,0,D3DBACKBUFFER_TYPE_MONO,&_fb);
//	d3dd->GetFrontBufferData(0,_fb);
	char temp[MAX_PATH];
	ZeroMemory(temp,MAX_PATH);
	char _ScScount[10];ZeroMemory(_ScScount,sizeof(_ScScount));
	sprintf(_ScScount,"%10d",ScScount);
	for (int i=0;i<10;i++)
	{
		if (_ScScount[i]==32)
			_ScScount[i]='0';
	}
	sprintf(temp,this->ScFormat,_ScScount);
	ScScount++;
	WriteMsg("-->Screen shot %s.",temp);
	this->Ini_SetInt("SCREENSHOT","Count",ScScount);
	D3DXSaveSurfaceToFileA(temp,D3DXIFF_JPG,_fb,NULL,NULL);
	_fb->Release();	
}
void CPie::Release()
{
	if (procExitFunc)
		(procExitFunc)();
	SManager.Destroy();
	MRelease();
	RRelease();
	RELEASE(d3dd);
	RELEASE(pd3d);
	FreeDirectInput();
}
void CPie::SetUInitFunc(PIECallback Func)
{
	procUserInit=Func;
}
void CPie::SetUDrawFunc(PIECallback Func)
{
	procRenderFunc=Func;
}
void CPie::SetUFGainFunc(PIECallback Func)
{
	procFocusGainFunc=Func;
}
HRESULT CPie::InitDirectInput()
{
	HRESULT hr;
	if ( FAILED( hr = DirectInput8Create( GetModuleHandle(NULL), DIRECTINPUT_VERSION, 
										  IID_IDirectInput8, (void**)&lpDI, NULL )))
	{
		WriteMsg("-->Error initializing Direct Input");
		return hr;
	}
	WriteMsg("-->Direct input initialization - success");

	InitMouse();
	InitKeyboard();
	return S_OK;
}

HRESULT CPie::InitMouse()
{
	HRESULT hr;
	_mx=0;
	_my=0;
	
	if ( FAILED( hr = lpDI->CreateDevice( GUID_SysMouse, &lpDIMouse, NULL)))
	{
		return hr;
		WriteMsg("-->Eror initializing mouse");
	}
	if ( FAILED( hr = lpDIMouse->SetDataFormat( &c_dfDIMouse2 )))
	{
		return hr;
		WriteMsg("-->Eror initializing mouse");
	}
	if ( FAILED( hr = lpDIMouse->SetCooperativeLevel( hWnd, COOP_FLAGS )))
	{
		return hr;
		WriteMsg("-->Eror initializing mouse");
	}
// stuff for buffered mode
/*	DIPROPDWORD dipropdw;
	dipropdw.diph.dwSize		= sizeof( DIPROPDWORD );
	dipropdw.diph.dwHeaderSize  = sizeof( DIPROPHEADER );
	dipropdw.diph.dwObj			= 0;
	dipropdw.diph.dwHow			= DIPH_DEVICE;
	dipropdw.dwData				= SAMPLE_BUFFER_SIZE;

	if ( FAILED( hr = lpDIMouse->SetProperty( DIPROP_BUFFERSIZE, &dipropdw.diph )))
		return hr; */
// eee
	lpDIMouse->Acquire();

	pdims2 = &odims2;
	podims2 = &dims2;
	ZeroMemory( pdims2, sizeof(DIMOUSESTATE2) );
	ZeroMemory( podims2, sizeof(DIMOUSESTATE2) );
	
	WriteMsg("-->Mouse initializing - success");
	return S_OK;
}

HRESULT CPie::InitKeyboard()
{
	HRESULT hr;
	if( FAILED( hr = lpDI->CreateDevice( GUID_SysKeyboard, &lpDIKeyboard, NULL ) ) )
	{
		WriteMsg("-->Error initializing keyboard");
		return hr;
	}
	if( FAILED( hr = lpDIKeyboard->SetDataFormat( &c_dfDIKeyboard ) ) )
	{
		WriteMsg("-->Error initializing keyboard");
		return hr;
	}
	if( FAILED( hr = lpDIKeyboard->SetCooperativeLevel( hWnd, COOP_FLAGS )))
	{
		WriteMsg("-->Error initializing keyboard");
		return hr;
	}

	lpDIKeyboard->Acquire();

	pkeys = okeys;
	pokeys = keys;
	ZeroMemory( pkeys, sizeof(keys) );
	ZeroMemory( pokeys, sizeof(keys) );

	WriteMsg("-->Keyboard initializing - success");
	return S_OK;


}

HRESULT CPie::UpdateKeyboardDataImmediate()
{
	HRESULT hr;

	if( lpDIKeyboard == NULL ) 
		return S_OK;

	BYTE *t = pkeys;
	pkeys = pokeys;
	pokeys = t;

	ZeroMemory( pkeys, sizeof(keys) );
	hr = lpDIKeyboard->GetDeviceState( sizeof(keys), pkeys );
	if( FAILED(hr) ) 
    {
		hr = lpDIKeyboard->Acquire();
		while( hr == DIERR_INPUTLOST ) 
			hr = lpDIKeyboard->Acquire();

        if( FAILED(hr) ) 
			return hr;
			return S_OK; 
	}
	return S_OK;
	

}

int CPie::isKeyPressed(int index)
{
	if (index >= 0 && index < 256)
		if (pkeys[index] & PRESSED) 
		{
			if (pokeys[index] & PRESSED) return KEY_PRESSED;
			else	return KEY_DOWN;
		}
		else
		{
			if (pokeys[index] & PRESSED) return KEY_UP;
			else	return KEY_UNPR;
		}
	else
		return KEY_UNPR;
}

HRESULT CPie::UpdateMouseDataImmediate()
{
    HRESULT hr;
	if( lpDIMouse == NULL )
		return S_OK;
	DIMOUSESTATE2 * t = podims2;
	podims2 = pdims2;
	pdims2 = t;

	ZeroMemory( &pdims2, sizeof(DIMOUSESTATE2) );
    hr = lpDIMouse->GetDeviceState( sizeof(DIMOUSESTATE2), &dims2 );
    if( FAILED(hr) ) 
    {
		hr = lpDIMouse->Acquire();
		while( hr == DIERR_INPUTLOST )
			hr = lpDIMouse->Acquire();
		if( hr == DIERR_OTHERAPPHASPRIO || hr == DIERR_NOTACQUIRED )
			return hr;
		return S_OK; 
	}

	_mx += dims2.lX;
	_my += dims2.lY;
	if (_mx < 0) _mx = 0;
	if (_mx >= ScrWidth) _mx = ScrWidth - 1;
	if (_my < 0) _my = 0;
	if (_my >= ScrHeight) _my = ScrHeight - 1;

	return S_OK;
}

int CPie::isMouseButtonPressed(int buttonindex)
{
	if (pdims2->rgbButtons[buttonindex] & PRESSED) 
	{
		if (podims2->rgbButtons[buttonindex] & PRESSED) return KEY_PRESSED;
		else return KEY_DOWN;
	}
		else
		{
			if (podims2->rgbButtons[buttonindex] & PRESSED) return KEY_UP;
			else	return KEY_UNPR;
		}
}

void CPie::GetMouseDelta(int * dx, int * dy)
{
	*dx = dims2.lX;
	*dy = dims2.lY;
}

void CPie::GetMousePos(int * x, int * y)
{
	*x = _mx;
	*y = _my;
}

void CPie::SetMousePos(const int x, const int y)
{
	_mx = x;
	_my = y;
}


void CPie::FreeDirectInput()
{
	FreeMouse();
	FreeKeyboard();
    RELEASE( lpDI );
}

void CPie::FreeMouse()
{
	if( lpDIMouse )
		lpDIMouse->Unacquire();
	RELEASE( lpDIMouse );

}
void CPie::FreeKeyboard()
{
	if( lpDIKeyboard )
		lpDIKeyboard->Unacquire();
	RELEASE( lpDIKeyboard );
}