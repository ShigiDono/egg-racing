#ifndef PIE_CONTROLLER
#define PIE_CONTROLLER
#include"main.h"
//#include<list>
template<class _Class> class CController
{
public:
    CController();
	void		SetUpLength(int _len);
	void		SetUpKeyFrames(float dt){if (dt==0) return;kt=dt;}
	bool		BeginRecord(){if (Playing) return 0;if (Record) return 0;Record=1;return 1;}
	void		EndRecord(){Record=0;ct=0;}
	bool		BeginPlay(){if (Record) return 0;if (Playing) return 0;Playing=1;return 1;}
	void		Update(float dt);
	void		EndPlay(){Playing=0;ct=0;}
	void		Reset(){ct=0;rlen=0;}
	void		SetTime(float dt){if (((float)dt/kt)>rlen) return; if (dt<=0) return; ct=dt;Update(dt-ct);}
	void		SetValueAdress(_Class *_ValueAdress){ValueAdress=_ValueAdress;}
private:
	_Class		*ValueAdress;
	bool		Record;
	bool		Playing;
	bool		Loop;
	int			len;
	int			rlen;
	float		ct;
	float		kt;
	_Class		*Stream;
	int			cnt;
	_Class		val;
};
#endif PIE_CONTROLLER