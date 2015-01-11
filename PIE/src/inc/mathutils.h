#ifndef DREAMCATCHER_MATH_H
#define DREAMCATCHER_MATH_H
/*
File    : MathUtils.h
Author  : Dreamcatcher
Started : 6.11.2007 2:03
________________________
Description:
 Vector class Implementa
 tion, basic math functi
 ons, Matrices etc. 
*/

#pragma warning( disable : 4305 ) 
#pragma warning( disable : 4244 ) 
#define PI   3.1415926535897932
#define OOPI 0.3183098861837906
#define sincostable_dim 8192 
typedef float scalar;
static const scalar deganglem = 1.0f / ( 360.0f / (scalar)sincostable_dim);
static const scalar radanglem = 1.0f / ( (scalar)PI*2 / (scalar)sincostable_dim);
static const scalar PI_d180 = PI / 180.0f;
static const scalar d180_PI = 180.0f / PI;

void GenSinTable();
scalar fSinr(scalar angle);
scalar fSind(scalar angle);
scalar fSini(int index);
scalar fCosr(scalar angle);
scalar fCosd(scalar angle);
scalar fCosi(int index);

__forceinline scalar Max(scalar a, scalar b){return a>=b?a:b;}
__forceinline scalar Min(scalar a, scalar b){return a<=b?a:b;}
__forceinline scalar Clamp(scalar x , scalar xmin, scalar xmax){return Min(Max(x, xmin), xmax);}
__forceinline scalar DegToRad(scalar degree){ return (scalar)(degree * PI_d180);}
__forceinline scalar RadToDeg(scalar radian){ return (scalar)(radian * d180_PI);}

class Vector2{
public:
	scalar x, y;
	static const Vector2& Blank() { static const Vector2 V(0, 0); return V;} 
public:
	inline Vector2(void){}
	inline Vector2( scalar Ix, scalar Iy) : x(Ix), y(Iy){}
	inline Vector2 operator + (const Vector2 &V)const
	{ return Vector2( x + V.x, y + V.y );}
	inline Vector2 operator - (const Vector2 &V)const
	{ return Vector2( x - V.x, y - V.y );}
	inline Vector2 operator * (const scalar a)const
	{ return Vector2( x * a, y * a);}
	inline Vector2 operator / (const scalar a)const
	{ return Vector2( x / a, y / a);}

	friend Vector2 operator * (scalar k, const Vector2& V) 
	{return Vector2(V.x*k, V.y*k);}

	inline Vector2 &operator +=(const Vector2 &V) 
	{ x += V.x;	y += V.y; return *this;}
	inline Vector2 &operator -=(const Vector2 &V)
	{ x -= V.x; y -= V.y; return *this;}
	inline Vector2 &operator *=(const scalar a)
	{ x *= a; y *= a; return *this;}
	inline Vector2 &operator /=(const scalar a)
	{ x /= a; y /= a; return *this;}

	inline Vector2 operator -(void) const
	{ return Vector2( -x, -y);}

	inline scalar operator * (const Vector2 &V) const // dot product
	{ return x * V.x + y * V.y;}
	inline scalar operator ^ (const Vector2 &V) const // cross product
	{ return x * V.y - y * V.x;}

	inline scalar Length(void) const
	{ return (scalar)sqrt((double)(x*x + y*y));}
};

class Vector3{
public:
	scalar x, y, z;
	
	static const Vector3& Blank() { static const Vector3 V(0, 0, 0); return V;} 
	inline Vector3() : x(0), y(0), z(0){}
	inline Vector3( scalar xv, scalar yv, scalar zv ) : x(xv), y(yv), z(zv){}
	inline scalar& operator[](int i) { return (&x)[i]; } 
	inline Vector3 operator + (const Vector3 &v)const
		{return Vector3( x + v.x, y + v.y, z + v.z );}
	inline Vector3 operator - (const Vector3 &v)const
		{return Vector3( x - v.x, y - v.y, z - v.z );}
	inline Vector3 operator * (const scalar s)const
		{return Vector3( x * s, y * s, z * s);}
	inline Vector3 operator / (const scalar s)const
		{scalar t = 1.0f / s; return Vector3( x * t, y * t, z * t);}
	friend Vector3 operator * (scalar s, const Vector3& v) 
		{return Vector3(v.x * s, v.y * s, v.z * s); }
	inline Vector3 &operator +=(const Vector3 &v) 
		{ x += v.x;	y += v.y; z += v.z; return *this;}
	inline Vector3 &operator -=(const Vector3 &v)
		{x -= v.x; y -= v.y; z -= v.z; return *this;}
	inline Vector3 &operator *=(const scalar s)
		{x *= s; y *= s; z *= s; return *this;}
	inline Vector3 &operator /=(const scalar s)
		{scalar t = 1.0f / s; x *= t; y *= t; z *= t; return *this;}
	inline Vector3 operator -(void) const
		{return Vector3( -x, -y, -z);}
	inline scalar operator*(const Vector3 &v)const
		{return x * v.x + y * v.y + z * v.z;}
	inline Vector3 operator^(const Vector3 &v)const
		{return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}
	inline scalar Length(void) const
		{return (scalar)sqrt((double)(x*x + y*y + z*z));}

	scalar Normalise(void) 
	{
		scalar l = Length();
		if ( l == 0.0f )
			return 0.0f;
		(*this) *= ( 1.0f / l );	
		return l; 
	}

	Vector3 Normalized(void) 
	{
		scalar l = Length();
		if ( l == 0.0f )
			return Vector3();
		Vector3 t = (*this) * ( 1.0f / l );	 
		return t;
	}

	scalar ComputeNormal(const Vector3& V0, const Vector3& V1, const Vector3& V2)
	{
		Vector3 E = V1 - V0;// E -= V0;
		Vector3 F = V2 - V1;// F -= V1;
		(*this)  = E ^ F;		
		return (*this).Normalise();
	}
	__forceinline void RotateX(scalar angle)
	{
		scalar s = sin(angle), c = cos(angle);
		scalar ty = y*c - z*s, tz = z*c + y*s;
		z = tz; y = ty;
	}
	__forceinline void RotateY(scalar angle)
	{
		scalar s = sin(angle), c = cos(angle);
		scalar tz = z*c - x*s, tx = x*c + z*s;
		z = tz; x = tx;
	}
	__forceinline void RotateZ(scalar angle)
	{
		scalar s = sin(angle), c = cos(angle);
		scalar tx = x*c - y*s, ty = y*c + x*s;
		x = tx; y = ty;
	}

	void Rotate(Vector3 angle)
	{
		Vector3	sina, cosa, temp;

		sina.x = sin(angle.x);
		cosa.x = cos(angle.x);
		sina.y = sin(angle.y);
		cosa.y = cos(angle.y);
		sina.z = sin(angle.z);
		cosa.z = cos(angle.z);

		temp.x = (x * cosa.z + y * sina.z);
		temp.y = (y * cosa.z - x * sina.z);

		x = temp.x;
		y = temp.y;

		temp.z = (z * cosa.x + y * sina.x);
		temp.y = (y * cosa.x - z * sina.x);

		z = temp.z;
		y = temp.y;

		temp.x = (x * cosa.y + z * sina.y);
		temp.z = (z * cosa.y - x * sina.y);
		/*		temp.x = (x * cosa.z + y * sina.z);
		temp.y = (y * cosa.z - x * sina.z);

		x = temp.x;
		y = temp.y;

		temp.z = (z * cosa.x + z * sina.x);
		temp.y = (y * cosa.x - x * sina.x);

		z = temp.z;
		y = temp.y;

		temp.x = (x * cosa.y + x * sina.y);
		temp.z = (z * cosa.y - z * sina.y);
*/

		x = temp.x;
		z = temp.z;
	}
};


class Matrix3x3
{
public:
	Vector3 m[3];
	
	Matrix3x3(void)
	{
		m[0] = Vector3::Blank();
		m[1] = Vector3::Blank();
		m[2] = Vector3::Blank();
	}

	Matrix3x3(scalar xx, scalar xy, scalar xz,
			  scalar yx, scalar yy, scalar yz,
			  scalar zx, scalar zy, scalar zz)
	{
		m[0] = Vector3(xx, xy, xz);
		m[1] = Vector3(yx, yy, yz);
		m[2] = Vector3(zx, zy, zz);
	}

	
	
	Matrix3x3(Vector3 c0, Vector3 c1, Vector3 c2) //fill the columns
	{
		m[0] = c0;
		m[1] = c1;
		m[2] = c2;
	}

	inline Vector3 & operator [](int i) 
	{ return m[i];	} 

	inline Matrix3x3 &operator += ( Matrix3x3 other)
	{
		m[0] += other.m[0];
		m[1] += other.m[1];
		m[2] += other.m[2];
		return (*this);
	}
	inline Matrix3x3 &operator -= ( Matrix3x3 other)
	{
		m[0] -= other.m[0];
		m[1] -= other.m[1];
		m[2] -= other.m[2];
		return (*this);
	}
	inline Matrix3x3 &operator *= ( scalar other)
	{
		m[0] *= other;
		m[1] *= other;
		m[2] *= other;
		return (*this);
	}
	inline Matrix3x3 &operator /= ( scalar other)
	{
		m[0] /= other;
		m[1] /= other;
		m[2] /= other;
		return (*this);
	}

	inline friend Matrix3x3 operator*(const Matrix3x3& m1, const Matrix3x3& m2)
	{
		return Matrix3x3(
			m2.m[0]*m1.m[0], m2.m[1]*m1.m[0], m2.m[2]*m1.m[0],
			m2.m[0]*m1.m[1], m2.m[1]*m1.m[1], m2.m[2]*m1.m[1],
			m2.m[0]*m1.m[2], m2.m[1]*m1.m[2], m2.m[2]*m1.m[2]);
	}
	inline Matrix3x3 operator+(Matrix3x3 m)
	{
		return (*this) += m;
	}

	inline friend Vector3 operator *(const Vector3& V, const Matrix3x3& M)
	{
		Vector3 t;
		t.x = M.m[0]*V;
		t.y = M.m[1]*V;
		t.z = M.m[2]*V;
		return t;
	}

	inline friend Vector3 operator *(const Matrix3x3& M, const Vector3& V)
	{
		Vector3 t;
		t.x = M.m[0]*V;
		t.y = M.m[1]*V;
		t.z = M.m[2]*V;
		return t;
	}

	inline Matrix3x3 operator-(Matrix3x3 m)
	{
		return (*this) -= m;
	}

	Matrix3x3 Transpose() const 
	{
		return Matrix3x3(m[0].x, m[1].x, m[2].x,
						 m[0].y, m[1].y, m[2].y,
						 m[0].z, m[1].z, m[2].z);
	}

	scalar cofac(int r1, int c1, int r2, int c2) 
		{			
			return (m[r1][c1] * m[r2][c2] - m[r1][c2] * m[r2][c1]);
		}

	inline Matrix3x3 inverse() 
	{
		Vector3 co = Vector3(cofac(1, 1, 2, 2), cofac(1, 2, 2, 0), cofac(1, 0, 2, 1));
		scalar det = m[0]*co;
		//btFullAssert(det != btScalar(0.0));
		scalar s = 1.0f / det;
		return Matrix3x3(co.x * s, cofac(0, 2, 2, 1) * s, cofac(0, 1, 1, 2) * s,
						 co.y * s, cofac(0, 0, 2, 2) * s, cofac(0, 2, 1, 0) * s,
						 co.z * s, cofac(0, 1, 2, 0) * s, cofac(0, 0, 1, 1) * s);

		return Matrix3x3(co.x * s, co.y * s, co.z * s,
						 cofac(0, 2, 2, 1) * s, cofac(0, 0, 2, 2) * s, cofac(0, 1, 2, 0) * s,
						 cofac(0, 1, 1, 2) * s, cofac(0, 2, 1, 0) * s, cofac(0, 0, 1, 1) * s);

	}




};

class Matrix4x4
{
public:
scalar	e11, e12, e13, e14,
		e21, e22, e23, e24,
		e31, e32, e33, e34,
		e41, e42, e43, e44;
};
class Matrix2x2
{};

class Quaternion
{
	public:
		scalar x, y, z, w;

		Quaternion(){x=y=z=0.0f;w=1.0f;}
		Quaternion(scalar xv, scalar yv, scalar zv, scalar wv){x=xv;y=yv;z=zv;w=wv;}
		Quaternion(Vector3 v){x=v.x;y=v.y;z=v.z;w=0;};
		void operator=(const Quaternion &q){x=q.x;y=q.y;z=q.z;w=q.w;}
		inline Quaternion operator+(Quaternion q){return Quaternion( x + q.x , y + q.y, z + q.z, w + q.w );}
		inline Quaternion operator-(Quaternion q){return Quaternion( x - q.x , y - q.y, z - q.z, w - q.w );}
		inline Quaternion operator*(scalar s){return Quaternion(x * s, y * s, z * s, w * s);}
		inline Quaternion operator/(scalar s){scalar is = 1/s; return (*this)*is;}
		inline Quaternion operator+=(Quaternion q){(*this) = (*this)+q; return *this;}
		scalar Norm()const{return x * x + y * y + z * z + w * w;}
		scalar Length( void ){return sqrt(x * x + y * y + z * z + w * w );}	
		Quaternion Conjugate(){ return Quaternion(-x,-y,-z,w);}
		Quaternion Identity(){return (*this).Conjugate()/(*this).Norm();};
		scalar InnerProduct(const Quaternion& q){return x*q.x+y*q.y+z*q.z+w*q.w;}

			inline Quaternion operator*(const Quaternion &q)
		{
			Quaternion result;

			result.x = w * q.x + x * q.w + y * q.z - z * q.y;
            result.y = w * q.y - x * q.z + y * q.w + z * q.x;
            result.z = w * q.z + x * q.y - y * q.x + z * q.w;
            result.w = w * q.w - x * q.x - y * q.y - z * q.z;

            return result;
		}
		
	  inline void AxisAngle(Vector3& axis, scalar& angle)const {
        scalar vl = (scalar)sqrt( x*x + y*y + z*z );
        if( vl > 0.0001 )
        {
            scalar ivl = 1.0f/vl;
            axis = Vector3( x*ivl, y*ivl, z*ivl );
            if( w < 0 )
                angle = 2.0f*(scalar)atan2(-vl, -w); //-PI,0 
            else
                angle = 2.0f*(scalar)atan2( vl,  w); //0,PI 
        }else{
            axis = Vector3(0,0,0);
            angle = 0;
        }
    }


		void Rotate(scalar amount, scalar xAxis, scalar yAxis, scalar zAxis)
		{
			if((xAxis != 0 && xAxis != 1) ||
               (yAxis != 0 && yAxis != 1) ||
               (zAxis != 0 && zAxis != 1))
				{
					scalar length = (scalar)sqrt(xAxis * xAxis + yAxis * yAxis + zAxis * zAxis);
					xAxis /= length; yAxis /= length; zAxis /= length;
				}
			scalar angle = DegToRad(amount);
			scalar sine = (scalar)sin(angle / 2.0f);

            
	         x = xAxis * sine;
	         y = yAxis * sine;
	         z = zAxis * sine;
            w = (scalar)cos(angle / 2.0f);

      
            scalar length = 1 / (scalar)sqrt(x * x + y * y + z * z + w * w);
            x *= length;
            y *= length;
            z *= length;
		}

	    inline void toMatrix3x3( Matrix3x3& m  )const
		{
			scalar wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
			scalar s  = 2.0f/(*this).Norm();  
			x2 = x * s;    y2 = y * s;    z2 = z * s;
			xx = x * x2;   xy = x * y2;   xz = x * z2;
			yy = y * y2;   yz = y * z2;   zz = z * z2;
			wx = w * x2;   wy = w * y2;   wz = w * z2;

			m.m[0].x = 1.0f - (yy + zz);
			m.m[1].x = xy - wz;
			m.m[2].x = xz + wy;
	
			m.m[0].y = xy + wz;
			m.m[1].y = 1.0f - (xx + zz);
			m.m[2].y = yz - wx;
	
			m.m[0].z = xz - wy;
			m.m[1].z = yz + wx;
			m.m[2].z = 1.0f - (xx + yy);
    }


};

typedef Quaternion Vector4;

bool SqareEq( scalar a, scalar b, scalar c, scalar &t0, scalar &t1);

__forceinline Vector3 CalcNorm(const Vector3 v1,const Vector3 v2,const Vector3 v3)
{
   Vector3 t = (v3-v2)^(v2-v1);
   t.Normalise();
   return t;
}

__forceinline void Clampv(Vector3& x, const Vector3 xmin, Vector3 xmax)
{
	x.x = Clamp(x.x, xmin.x, xmax.x);
	x.y = Clamp(x.y, xmin.y, xmax.y);
	x.z = Clamp(x.z, xmin.z, xmax.z);
}



void CalcCameraVertices(scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat,Vector3 cup, Vector3 *v);
int PointsPlaneSide(Vector3 a, Vector3 n,Vector3 offset,Matrix3x3 R, Vector3 *points, int pnum);
scalar FindMTD(Vector3 a, Vector3 n,Vector3 offset,Matrix3x3 R, Vector3 *points, int pnum);
bool CullBox(Vector3 _min, Vector3 _max,Vector3 pos, Vector3 scaling, Matrix3x3 R,
						scalar fovy, scalar aspect, scalar znear, scalar zfar,
						Vector3 cpos, Vector3 cat, Vector3 cup);

#define Key_Backspace  8
#define Key_Tab  9
#define Key_Enter  13
#define Key_Shift  16
#define Key_Control  17
#define Key_Alt  18
#define Key_Escape  27
#define Key_Space  32

#define Key_Left  37
#define Key_Up  38
#define Key_Right  39
#define Key_Down  40

#define Key_0  48
#define Key_1  49
#define Key_2  50
#define Key_3  51
#define Key_4  52
#define Key_5  53
#define Key_6  54
#define Key_7  55
#define Key_8  56
#define Key_9  57

 
#define Key_A  65
#define Key_B  66
#define Key_C  67
#define Key_D  68
#define Key_E  69
#define Key_F  70
#define Key_G  71
#define Key_H  72
#define Key_I  73
#define Key_J  74
#define Key_K  75
#define Key_L  76
#define Key_M  77
#define Key_N  78
#define Key_O  79
#define Key_P  80
#define Key_Q  81
#define Key_R  82
#define Key_S  83
#define Key_T  84
#define Key_U  85
#define Key_V  86
#define Key_W  87
#define Key_X  88
#define Key_Y  89
#define Key_Z  90

#define Key_F1   112
#define Key_F2   113
#define Key_F3   114
#define Key_F4   115
#define Key_F5   116
#define Key_F6   117
#define Key_F7   118
#define Key_F8   119
#define Key_F9   120
#define Key_F10  121
#define Key_F11  122
#define Key_F12  123


#endif DREAMCATCHER_MATH_H

