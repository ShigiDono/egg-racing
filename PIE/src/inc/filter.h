
#ifndef PIE_FILTER
#define PIE_FILTER

#include"main.h"
#include"files.h"

class Matrix5
{
public:
	Matrix5();
	float data[5][5];
    void Clear();
	bool Load(LPCSTR Fname);
	void Update();
	void Reset();
	void Sqrt();
	void pop();
	Matrix5 &operator *=(const Matrix5 a)
	{
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				data[i][j]*=a.data[i][j];
			}
		}
		Update();
		return *this;
	}
	Matrix5 operator *(const Matrix5 a)
	{
		Matrix5 res;
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				res.data[i][j]=data[i][j]*a.data[i][j];
			}
		}
		res.pop();
		res.Update();
		return res;
	}
	Matrix5 &operator +=(const FLOAT a)
	{
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				data[i][j]+=a;
			}
		}
		return *this;
	}
	Matrix5 &operator +=(const Matrix5 a)
	{
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				data[i][j]+=a.data[i][j];
			}
		}
		Update();
		return *this;
	}
	Matrix5 operator +(const Matrix5 a)
	{
		Matrix5 res;
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				res.data[i][j]=data[i][j]+a.data[i][j];
			}
		}
		res.pop();
		res.Update();
		return res;
	}	Matrix5 &operator -=(const FLOAT a)
	{
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				data[i][j]-=a;
			}
		}
		return *this;
	}
	Matrix5 &operator -=(const Matrix5 a)
	{
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				data[i][j]-=a.data[i][j];
			}
		}
		Update();
		return *this;
	}
	Matrix5 operator -(const Matrix5 a)
	{
		Matrix5 res;
		for (int i=0;i<5;i++)
		{
			for (int j=0;j<5;j++)
			{
				res.data[i][j]=data[i][j]-a.data[i][j];
			}
		}
		res.pop();
		res.Update();
		return res;
	}
	void ApplyEffect(BYTE* Src,BYTE* Dest,int Width,int Height);//я тут подумал и решил:
	//(((((в топку 16 битный цвет)))))))))))))))))))))
	//(((((нада наслаждатьс€ 32 битным=))))))))))))):3
	//(((((а у  кого не пойдет пусть сменит комп=)))))
	//(((((так что теперь есть только 4 байта=))))))))
	//(((((<!-Ѕ≈«  ќћћ≈Ќ“ј–»≈¬-->;3=))))))))))))))))))
private:
	float _data[5][5];
};
typedef Matrix5 CFilter;
typedef CFilter *PFilter;

#endif PIE_FILTER