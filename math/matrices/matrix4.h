#ifndef MATRIX4_H
#define MATRIX4_H

#include <string.h>

class vec3;
class mat3;

class mat4
{
	private:
		float m[16];
	
	public:
		mat4() { Identity(); }
		mat4(float* M) { memcpy(m, M, sizeof(float) * 16); }
		mat4(const mat4& M) { memcpy(m, M.m, sizeof(float) * 16); }
		mat4(const mat3&);
	
		void operator = (const mat4& r) { memcpy(m,r.m,sizeof(float)*16); }
		float& operator [] (int ind) { return m[ind]; }
		float operator [] (int ind) const { return m[ind]; }
		void operator /= (const float);
		void operator *= (const mat4&);
		void operator *= (const float);
		void operator += (const mat4&);
		void operator += (const float);
		void operator -= (const mat4&);
		void operator -= (const float);
		
		friend bool operator == (const mat4&, const mat4&);
		friend bool operator != (const mat4&, const mat4&);
		friend mat4 operator + (const mat4&, const mat4&);
		friend mat4 operator + (const mat4&, const float);
		friend mat4 operator + (const float, const mat4&);
		friend mat4 operator - (const mat4&, const mat4&);
		friend mat4 operator - (const mat4&, const float);
		friend mat4 operator - (const float, const mat4&);
		friend mat4 operator * (const mat4&, const mat4&);
		friend mat4 operator * (const mat4&, const float);
		friend mat4 operator * (const float, const mat4&);		
		friend mat4 operator / (const mat4&, const float);
		friend mat4 operator / (const float, const mat4&);
	
		inline void Null(void) { memset(m, 0, sizeof(float) * 16); }
		void Identity(void);
		void LookAt(vec3, vec3, vec3);
		void Rotation(float  x, float y, float z);
		void Rotation(const vec3&);
		void Translation(float x, float y, float z);
		void Translation(const vec3&);
		void Scale(float x , float y , float z);
		void Scale(const vec3&);
		void Perspective(float fov, float aspect, float znear, float zfar);
        void Ortho(float left, float right, float bottom, float top);
		void Transpose(void);
		
		float Determinant(void);
		mat4 Inverse(void);
		
		friend mat4 RotationMatrix(float x, float y, float z);
		friend mat4 RotationMatrix(const vec3&);
		friend mat4 TranslationMatrix(float x, float y, float z);
		friend mat4 TranslationMatrix(const vec3&);
		friend mat4 ScaleMatrix(float x, float y, float z);
		friend mat4 ScaleMatrix(const vec3&);
};

inline void mat4::operator /= (const float k)
{
	(*this) = (*this) / k;
}

inline void mat4::operator *= (const mat4& m)
{
	(*this) = (*this) * m;
}

inline void mat4::operator *= (const float k)
{
	(*this) = (*this) * k;
}

inline void mat4::operator += (const mat4& m)
{
	(*this) = (*this) + m;
}

inline void mat4::operator += (const float k)
{
	(*this) = (*this) + k;
}

inline void mat4::operator -= (const mat4& m)
{
	(*this) = (*this) - m;
}

inline void mat4::operator -= (const float k)
{
	(*this) = (*this) - k;
}

inline mat4 operator + (const float k, const mat4& m)
{
	return (m + k);
}

inline mat4 operator - (const float k, const mat4& m)
{
	return (m - k);
}

inline mat4 operator * (const float k, const mat4& m)
{
	return (m * k);
}

inline mat4 operator / (const float k, const mat4& m)
{
	return (m / k);
}

inline mat4 RotationMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Rotation(x, y, z);
	return temp;
}

inline mat4 TranslationMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Translation(x, y, z);
	return temp;
}

inline mat4 ScaleMatrix(float x, float y, float z)
{
	mat4 temp;
	temp.Scale(x, y, z);
	return temp;
}

#endif