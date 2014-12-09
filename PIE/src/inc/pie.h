#ifndef PIE_ENGINE
#define PIE_ENGINE
//#include"main.h"
//#include"mesh.h"
//#include"t_and_s.h"
//#include"font.h"
//#include"matrix.h"
//#include"ParticleSystem.h"
#include"Resources.h"
#include"terrain.h"
//#include"CYKATECT.h"
///#include"particlesystem.h"
#define MAX_MESHES 1000
typedef bool (*PIECallback)();
    //Main stats
#define PRESSED 0x080
#define SAMPLE_BUFFER_SIZE  16     
#define KEY_UNPR 0
#define KEY_DOWN 1 
#define KEY_UP   2
#define KEY_PRESSED 3

#define COOP_FLAGS DISCL_EXCLUSIVE | DISCL_FOREGROUND
//alternate acssess modes DISCL_NONEXCLUSIVE | DISCL_BACKGROUND | DISCL_NOWINKEY

#define MOUSE_KEY_0 0
#define MOUSE_KEY_1 1
#define MOUSE_KEY_2 2
#define MOUSE_KEY_3 3
#define MOUSE_KEY_4 4
#define MOUSE_KEY_5 5
#define MOUSE_KEY_6 6
#define MOUSE_KEY_7 7
typedef enum _PIE_STATES
{
	PIE_INIT_FUNC		= 0x00,
	PIE_FRAME_FUNC		= 0x01,
	PIE_DRAW_FUNC		= 0x02,
	PIE_GFXR_FUNC		= 0x03,
	PIE_EXIT_FUNC		= 0x04,
	PIE_BWIDTH			= 0x05,
	PIE_BHEIGHT			= 0x06,
	PIE_BFORMAT			= 0x07,
	PIE_BWINDOWED		= 0x08,
	PIE_BRRATE			= 0x09,
	PIE_BMULTIS			= 0x0A,
	PIE_BGROUND			= 0x0B,
	PIE_FILLMODE		= 0x0C,
	PIE_LIGHTENABLE		= 0x0D,
	PIE_TFILTERING		= 0x0E,
	PIE_TENABLE			= 0x0F,
	PIE_FOGENABLE		= 0x10,
	PIE_FOGSTART		= 0x11,
	PIE_FOGEND			= 0x12,
	PIE_FOGCOLOR		= 0x13,
	PIE_FOGMODE			= 0x14,
	PIE_BLENDMODE		= 0x15,
}Pie_States;
class CPie
{
public:
	CPie();
	bool					Init(HINSTANCE hinst);
// Dinput
	// main funcs
	HRESULT					InitDirectInput();
	void					UpdateDirectInput();
	void					FreeDirectInput();

	int					isMouseButtonPressed(int buttonindex);
	void					GetMouseDelta(int * dx, int * dy);
	void					GetMousePos(int * x, int * y);
	void					SetMousePos(const int x, const int y);

	int					isKeyPressed(int index);
	// additional funcs
	HRESULT					InitMouse();
	HRESULT					InitKeyboard();
	void					FreeMouse();
	void					FreeKeyboard();
	HRESULT					UpdateKeyboardDataImmediate();
	HRESULT					UpdateMouseDataImmediate();

	bool					InitD3D();
	bool					ReInitD3D();
	bool					ResetD3D();
	int						Run(HINSTANCE hinstance);
	void					Render();
	bool					Step();
	bool					UserInit();
	void					PrintScreen(LPCSTR Fname);
	void					PrintScreen();
    bool					LoadFilter(LPCSTR FName,PFilter _f);
	void					ApplyFilter(PFilter f);
	void					SetState(Pie_States State,DWORD Value);
//	InI files
	void					Ini_SetInt(const char *section, const char *name, int value);
	int						Ini_GetInt(const char *section, const char *name, int def_val);
	void					Ini_SetFloat(const char *section, const char *name, float value);
	float					Ini_GetFloat(const char *section, const char *name, float def_val);
	void					Ini_SetString(const char *section, const char *name, const char *value);
	char*					Ini_GetString(const char *section, const char *name, const char *def_val);
//	Log files
	void					System_Log(const char *szFormat, ...);
	char					szIniFile[MAX_PATH];
	char					szLogFile[MAX_PATH];
	char					szIniString[256];
	void					SetUInitFunc(PIECallback Func);
	void					SetUDrawFunc(PIECallback Func);
	void					SetUFGainFunc(PIECallback Func);
	float					GetFPS();
	void					Release();
	void					AssignCamera(PCamera _Camera);
	void					ViewCamera(PCamera _Camera);
	void					SetBGColor(DWORD _color);
	DWORD					GetTime();
	WORD					GetScreenWidth(){return ScrWidth;}
	WORD					GetScreenHeight(){return ScrHeight;}
	void					AddPointLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Position,float Range,
									float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
	void					AddSpotLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Position,Vector3 Direction,float InnerCone,
									float OuterCone,float Falloff,float Range,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
	void					AddDirectionalLight(D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient
									,D3DCOLORVALUE Specular,Vector3 Direction,float Range,
									float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
	void					AddLight(D3DLIGHTTYPE Type,D3DCOLORVALUE Diffuse,D3DCOLORVALUE Ambient,D3DCOLORVALUE Specular,
									D3DVECTOR Direction,D3DVECTOR Position,float Falloff,float Phi,float Range,
									float Theta,float Attenuation0,float Attenuation1,float Attenuation2,bool Enabled);
	D3DLIGHT9				*GetLight(WORD index){return &Lights[index];}
	void					DeleteLight(WORD index);
	void					EnableLight(WORD index,bool Enabled);
	void					SetLightPos(WORD index,Vector3 pos);
	void					ClearLights();
	void					UpdateLight(WORD index);
	void					Exit();
	DWORD					GetDTime(){return DTime;}//delta time in milliseconds
	char					*GetAppPath(){return szAppPath;}
	void					WindowToggleFullScreen(bool isFullScreen);
	void					ToggleFullScreen(bool isFullScreen);
	bool					IsFullScreen(){return !d3dp.Windowed;}
	CSceneManager			SManager;
	bool					glowEnable(){return GlowEnable;}
	void					SetGlow(bool b){GlowEnable=b;}
	LPDIRECT3DDEVICE9		GetDevice(){return d3dd;}
	bool					PrepareScene();
	void					PresentScene();
	char					Map[MAX_PATH];
	DWORD					StepTime, DrawTime;
protected:
	DWORD					DTime;
	WORD					MeshCount;
	PMesh					Meshes[MAX_MESHES];
	char					szAppPath[MAX_PATH];
	char					ScPath[MAX_PATH];
	char					ScFormat[MAX_PATH];
	int						ScScount;
	PCamera					Camera;
	float					Fps;
	D3DLIGHT9				Lights[16];
	WORD					LightCount;
	WORD					ScrWidth;
	HINSTANCE				hInst;
	WORD					ScrHeight;
	DWORD					ScrRRate;
	D3DFORMAT				ScrFormat;
	bool					GlowEnable;
	HWND					hWnd;
	D3DCOLOR				BGround;
	bool					CWindow();
	HICON					hIcon;
	bool					DeviceLost;
	bool					(*procUserInit)();
	bool					(*procFrameFunc)();
	bool					(*procRenderFunc)();
	bool					(*procFocusLostFunc)();
	bool					(*procFocusGainFunc)();
	bool					(*procGfxRestoreFunc)();
	bool					(*procExitFunc)();

	// dinput
	BYTE					keys[256]; // сюда для клавы
	BYTE					okeys[256];
	BYTE 					*pkeys;
	BYTE 					*pokeys;
	DIMOUSESTATE2			dims2; // сюда он все читает для мыши
	DIMOUSESTATE2			odims2; 
	DIMOUSESTATE2			*pdims2; 
	DIMOUSESTATE2			*podims2; 


	int						_mx, _my; // мыши координаты
private:
	bool					_exit;
	PSurface				BackBuffer;
	LPDIRECT3D9				pd3d;
	LPDIRECT3DDEVICE9		d3dd;
	D3DPRESENT_PARAMETERS	d3dp;
	D3DDISPLAYMODE			dModeList[40];
	BYTE					ModeCount;

	// dinput
	LPDIRECTINPUT8 lpDI; 
	LPDIRECTINPUTDEVICE8	lpDIMouse;
	LPDIRECTINPUTDEVICE8	lpDIKeyboard;
	LPDIRECTINPUTDEVICE8	lpDIGamepad;

};
typedef CPie *PPie;
#endif PIE_ENGINE