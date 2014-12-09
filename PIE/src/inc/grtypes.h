#ifndef PIE_GRTYPES
#define PIE_GRTYPES
#include"main.h"
#define White 0xFFFFFFFF
#define Black 0xFF000000
#define GetAValue(argb)((BYTE)((argb)>>24))
typedef enum _GRADIENT
{
	GR_NONE=0x0,
	GR_LEFTRIGHT=0x1,
	GR_TOPBOTTOM=0x2,
	GR_RIGHTLEFT=0x3,
	GR_BOTTOMTOP=0x4,
	GR_SPECIAL=0xF,
}GRADIENT;
#endif PIE_GRTYPES