#ifndef MATRIX3_H
#define MATRIX3_H

#include <string.h>

class mat4;

class mat3
{
	private:
		float m[9];
	
	public:
		mat3() { Identity(); }
		mat3(float* M) { memcpy(m, M, sizeof(float) * 9); }
		mat3(const mat3& M) { memcpy(m, M.m, sizeof(float) * 9); }
		mat3(const mat4&);
	
		void operator = (const mat3& r) { memcpy(m, r.m, sizeof(float) * 9); }
		float& operator [] (int ind) { return m[ind]; }
		float operator [] (int ind) const { return m[ind]; }
		void operator /= (const float);
		void operator *= (const mat3&);
		void operator *= (const float);
		void operator += (const mat3&);
		void operator += (const float);
		void operator -= (const mat3&);
		void operator -= (const float);
		
		friend bool operator == (const mat3&, const mat3&);
		friend bool operator != (const mat3&, const mat3&);
		friend mat3 operator + (const mat3&, const mat3&);
		friend mat3 operator + (const mat3&, const float);
		friend mat3 operator + (const float, const mat3&);
		friend mat3 operator - (const mat3&, const mat3&);
		friend mat3 operator - (const mat3&, const float);
		friend mat3 operator - (const float, const mat3&);
		friend mat3 operator * (const mat3&, const mat3&);
		friend mat3 operator * (const mat3&, const float);
		friend mat3 operator * (const float, const mat3&);	
		friend mat3 operator / (const mat3&, const float);
		friend mat3 operator / (const float, const mat3&);
	
		inline void Null(void) { memset(m, 0, sizeof(float) * 9); }
		void Identity(void);
		void Transpose(void);
		
		inline float Determinant(void) { return m[4] * (m[0] * m[8] - m[6] * m[2]) + m[3] * (m[7] * m[2] - m[1] * m[8]) + m[5] * (m[6] * m[1] - m[0] * m[7]); }
		mat3 Inverse(void);
};

inline void mat3::operator /= (const float k)
{
	(*this) = (*this) / k;
}

inline void mat3::operator *= (const mat3& m)
{
	(*this) = (*this) * m;
}

inline void mat3::operator *= (const float k)
{
	(*this) = (*this) * k;
}

inline void mat3::operator += (const mat3& m)
{
	(*this) = (*this) + m;
}

inline void mat3::operator += (const float k)
{
	(*this) = (*this) + k;
}

inline void mat3::operator -= (const mat3& m)
{
	(*this) = (*this) - m;
}

inline void mat3::operator -= (const float k)
{
	(*this) = (*this) - k;
}

inline mat3 operator + (const float k, const mat3& m)
{
	return (m + k);
}

inline mat3 operator - (const float k, const mat3& m)
{
	return (m - k);
}

inline mat3 operator * (const float k, const mat3& m)
{
	return (m * k);
}

inline mat3 operator / (const float k, const mat3& m)
{
	return (m / k);
}

#endif