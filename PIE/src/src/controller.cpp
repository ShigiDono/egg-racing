#include "stdafx.h"
#include"controller.h"
/*CController<class _Class>::CController()
{
	this->ct=0;
	this->kt=1;
	this->len=100;
	this->Loop=1;
	this->Playing=0;
	this->Record=0;
	this->rlen=0;
	this->ValueAdress=NULL;
	this->Stream=NULL;
	cnt=0;
	ZeroMemory(&val,sizeof(_Class));
}
void CController<class _Class>::SetUpLength(int _len)
{
	if (_len<=0) return;
    len=_len;
	rlen=0;
	DELETE(Stream);
	Stream=new _Class[_len];
}
void CController<class _Class>::Update(float dt)
{
	if (Playing||Record)
	{
		ct+=dt;
		if (Playing){
			if (ct>kt*rlen)
			{
				if (Loop)
					ct-=kt*rlen;
				else
					ct=kt*rlen;
			}
		}
		if (Record){
			val+=*ValueAdress;
			cnt++;
		}
		if (val>=kt)
		{
			if (Record){
				Stream[rlen]=(float)val/cnt;
				rlen++;
				if (rlen>=len)
				{
					EndRecord();
					return;
				}
			}	
			if (Playing){
				*ValueAdress=Stream[rlen];
			}
			val=0;
		}
	}
}*/