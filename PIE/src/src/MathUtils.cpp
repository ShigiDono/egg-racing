#include "stdafx.h"
#include "MathUtils.h"



void CalcCameraVertices(scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup, Vector3 *v)
{
	scalar y1 = znear * tan(fovy*0.5f);
	scalar x1 = y1 * aspect;

	scalar y2 = zfar * tan(fovy*0.5f);
	scalar x2 = y2 * aspect;

	/*v[0] = Vector3(-x1,-y1,znear);
	v[1] = Vector3( x1,-y1,znear);
	v[2] = Vector3( x1, y1,znear);
	v[3] = Vector3(-x1, y1,znear);

	v[4] = Vector3(-x2,-y2,zfar);
	v[5] = Vector3( x2,-y2,zfar);
	v[6] = Vector3( x2, y2,zfar);
	v[7] = Vector3(-x2, y2,zfar);*/

	Vector3 nz = cat - cpos, ny = cup, nx;
	nz.Normalise();
	ny.Normalise();
	nx =  nz ^ ny;
	nx.Normalise();

	Vector3 Z,X,Y,nc, fc , Dir;
	Z = cpos - cat;
	Z.Normalise();
	X = Z ^ cup;
	X.Normalise();
	Y = Z ^ X;

	nc = cpos - Z * znear;
	fc = cpos - Z * zfar;

	v[0] = nc - Y * y1 - X * x1;
	v[1] = nc - Y * y1 + X * x1;
	v[2] = nc + Y * y1 + X * x1;
	v[3] = nc + Y * y1 - X * x1;
	
	

	// compute the 4 corners of the frustum on the far plane
	v[4] = fc - Y * y2 - X * x2;
	v[5] = fc - Y * y2 + X * x2;
	v[6] = fc + Y * y2 + X * x2;
	v[7] = fc + Y * y2 - X * x2;
	
	
//	for(int i=0;i<8;i++)
//		v[i] = v[i] - cpos;



}

// Эта (PointsPlaneSide) фунция проверяет лежат ли все точки
// по одну сторону от плоскост или нет если нет то возвращает 0
// если да - то знак полуплоскости

int PointsPlaneSide(Vector3 a, Vector3 n,Vector3 offset,Matrix3x3 R, Vector3 *points, int pnum)
{
	scalar sign = n * (offset + points[0]*R - a);
	for(int i=1; i < pnum; i++)
	{
		scalar t = n * (offset + points[i]*R - a);
		if ((t >= 0 && sign <= 0) || (t <= 0 && sign >= 0)) return 0;
		sign = t;
	}
	return (sign > 0)?1:-1;
}

scalar FindMTD(Vector3 a, Vector3 n,Vector3 offset,Matrix3x3 R, Vector3 *points, int pnum)
{
	scalar sign = n * (offset + points[0]*R - a);
	for(int i=1; i < pnum; i++)
	{
		scalar t = n * (offset + points[i]*R - a);
		if (t < sign)
		sign = t;
	}
	return sign;
}

 bool CullBox(Vector3 _min, Vector3 _max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
                        scalar fovy, scalar aspect, scalar znear, scalar zfar,
                        Vector3 cpos, Vector3 cat, Vector3 cup)
{
//    Vector3 v[8];
    Vector3 p[8];
	_min.x*=scaling.x;
	_min.y*=scaling.y;
	_min.z*=scaling.z;
	_max.x*=scaling.x;
	_max.y*=scaling.y;
	_max.z*=scaling.z;
    p[0] = _min + pos;
	p[1] = Vector3(_max.x, _min.y, _min.z) + pos;
	p[2] = Vector3(_max.x, _max.y, _min.z) + pos;
	p[3] = Vector3(_min.x, _max.y, _min.z) + pos;
	p[4] = Vector3(_min.x, _min.y, _max.z) + pos;
	p[5] = Vector3(_max.x, _min.y, _max.z) + pos;
	p[6] = Vector3(_max.x, _max.y, _max.z) + pos;
	p[7] = Vector3(_min.x, _max.y, _max.z) + pos;
	int res = 0;
	for (int i = 0; i < 8; i++)
	{
		Vector3 v = p[i] - cpos, lo = cat - cpos;
		float l = v.Length();
		float s = acosf((float)(v*lo)/(v.Length()*lo.Length()));
		res += ((s <= (float)(fovy/2)*1.5) && (l <= zfar) && (l >= znear));
	}
    return res!=0;
/*    CalcCameraVertices(fovy, aspect, znear, zfar, cpos, cat, cup, v);
    scalar sign[6];
    sign[0] = PointsPlaneSide(v[0], CalcNorm(v[0], v[1], v[2]), pos, //Vector3(0,0,0)
                                R ,p, 8);
    sign[1] = PointsPlaneSide(v[1], CalcNorm(v[1], v[5], v[6]), pos, 
                                R ,p, 8);
    sign[2] = PointsPlaneSide(v[0], CalcNorm(v[0], v[3], v[7]), pos, 
                                R ,p, 8);
    sign[3] = PointsPlaneSide(v[0], CalcNorm(v[0], v[4], v[5]), pos, 
                                R ,p, 8);
    sign[4] = PointsPlaneSide(v[3], CalcNorm(v[3], v[7], v[6]), pos, 
                                R ,p, 8);
    sign[5] = PointsPlaneSide(v[6], CalcNorm(v[6], v[7], v[4]), pos, 
                                R ,p, 8);
	if ((sign[0]<0)) return 0;
	if ((sign[1]<0)) return 0;
	if ((sign[2]<0)) return 0;
	if ((sign[3]<0)) return 0;
	if ((sign[4]>0)) return 0;
	if ((sign[5]>0)) return 0;
	return 1;
}


bool SqareEq( float a, float b, float c, float &t0, float &t1)
{
	float d = b * b - 4.0f * a * c;
	if ( d < 0)	return false;
	d = (float)sqrt( d);
	float oo2a = 1 / ( 2.0f * a);
	t0 = (- b + d) * oo2a;
	t1 = (- b - d) * oo2a;
	if ( t1 > t0)
	{
		float t = t0;
		t0 = t1;
		t1 = t;
	}*/
	return true;	
}

static float sintable[sincostable_dim], costable[sincostable_dim];

 void GenSinTable()
{
	float a = 0, add = (float)PI*2 / (float)sincostable_dim;
	for (int i=0; i<sincostable_dim; ++i){
		sintable[i] = (float)sin(a);
		costable[i] = (float)cos(a);
		a += add;
	}
}

float fSinr(float angle){return sintable[(int)(angle*radanglem)%sincostable_dim];}
float fSind(float angle){return sintable[(int)(angle*deganglem)%sincostable_dim];}
float fSini(int index){return sintable[index%sincostable_dim];}
float fCosr(float angle){return costable[(int)(angle*radanglem)%sincostable_dim];}
float fCosd(float angle){return costable[(int)(angle*deganglem)%sincostable_dim];}
float fCosi(int index){return costable[index%sincostable_dim];}
