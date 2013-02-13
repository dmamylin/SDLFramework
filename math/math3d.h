#ifndef MATH_3D_H
#define MATH_3D_H

#include "matrices/matrix3.h"
#include "matrices/matrix4.h"
#include "vectors/vector2.h"
#include "vectors/vector3.h"
#include "vectors/vector4.h"
#include "points/point2.h"
#include "points/point3.h"

#define PI		3.141592653589793f

//////////////////
//COMMON
/////////////////

inline float DegToRad(float angle)
{
	return angle * PI / 180.0f;
}

inline float RadToDeg(float angle)
{
	return 180.0f * angle / PI;
}

template <class T>
inline T Max(T a, T b)
{
	return (a > b) ? a : b;
}

template <class T>
inline T Min(T a, T b)
{
	return (a < b) ? a : b;
}

template <class T>
inline T Max(T a, T b, T c)
{
	return (a > b) ? ( (a > c) ? a : c ) : ( (b > c) ? b : c );
}

template <class T>
inline T Min(T a, T b, T c)
{
	return (a < b) ? ( (a < c) ? a : c ) : ( (b < c) ? b : c );
}

//////////////////
//VECTOR_2
/////////////////

vec2::vec2(const vec3& v)
{
	x = v.x;
	y = v.y;
}

vec2::vec2(const vec4& v)
{
	x = v.x;
	y = v.y;
}

//////////////////
//VECTOR_3
/////////////////

vec3::vec3(const vec2& v, const float Z)
{
	x = v.x;
	y = v.y;
	z = Z;
}

vec3::vec3(const vec4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

//////////////////
//VECTOR_4
/////////////////

vec4::vec4(const vec2& v, const float Z, const float W)
{
	x = v.x;
	y = v.y;
	z = Z;
	w = W;
}

vec4::vec4(const vec3& v, const float W)
{
	x = v.x;
	y =  v.y;
	z = v.z;
	w = W;
}

inline vec4 operator * (const vec4& v, const mat4& m)
{
	return vec4( 
		v.x * m[0] + v.y * m[1] + v.z * m[2] + v.w * m[3],
		v.x * m[4] + v.y * m[5] + v.z * m[6] + v.w * m[7],
		v.x * m[8] + v.y * m[9] + v.z * m[10] + v.w * m[11],
		v.x*m[12] + v.y* m[13] + v.z * m[14] + v.w * m[15] );
}

inline vec4 operator * (const mat4& m, const vec4& v)
{
	return v * m;
}

//////////////////
//MATRIX_3x3
/////////////////

mat3::mat3(const mat4& M)
{
	m[0] = M[0];
	m[1] = M[1];
	m[2] = M[2];
	m[3] = M[4];
	m[4] = M[5];
	m[5] = M[6];
	m[6] = M[8];
	m[7] = M[9];
	m[8] = M[10];
}

inline vec3 operator * (const vec3& v, const mat3& m)
{
	return vec3( v.x * m[0] + v.y * m[3] + v.z * m[6],
			   v.x * m[1] + v.y * m[4] + v.z * m[7],
			   v.x * m[2] + v.y * m[5] + v.z * m[8] );
}

inline vec3 operator * (const mat3& m, const vec3& v)
{
	return v * m;
}

//////////////////
//MATRIX_4x4
/////////////////

mat4::mat4(const mat3& M)
{	
	m[0] = M[0];
	m[1] = M[1];
	m[2] = M[2];
	m[3] = 0.0f;
	m[4] = M[3];
	m[5] = M[4];
	m[6] = M[5];
	m[7] = 0.0f;
	m[8] = M[6];
	m[9] = M[7];
	m[10] = M[8];
	m[11] = 0.0f;
	m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}

void mat4::LookAt(vec3 eye, vec3 center, vec3 up)
{
	vec3 forward, side, upvec;
	mat4 m, t;
	
	forward = center - eye;
	forward.Normalize();
	side = CrossProduct(forward, up);
	side.Normalize();
	upvec = CrossProduct(side, forward);
	
	m.Identity();
	
	m[0] = side.x;
	m[4] = side.y;
	m[8] = side.z;
	m[1] = upvec.x;
	m[5] = upvec.y;
	m[9] = upvec.z;
	m[2] = -forward.x;
	m[6] = -forward.y;
	m[10] = -forward.z;
	
	t.Translation(-eye.x, -eye.y, -eye.z);
	(*this) = m * t;
}

void mat4::Rotation(const vec3& v)
{
	Rotation(v.x, v.y, v.z);
}

void mat4::Translation(const vec3& v)
{
	Translation(v.x, v.y, v.z);
}

void mat4::Scale(const vec3& v)
{
	Scale(v.x, v.y, v.z);
}

mat4 RotationMatrix(const vec3& v)
{
	return RotationMatrix(v.x, v.y, v.z);
}

mat4 TranslationMatrix(const vec3& v)
{
	return TranslationMatrix(v.x, v.y, v.z);
}

mat4 ScaleMatrix(const vec3& v)
{
	return ScaleMatrix(v.x, v.y, v.z);
}

//////////////////
//POINT_2
/////////////////

template <class T>
point2<T>::point2(const vec2& v)
{
	x = T(v.x);
	y = T(v.y);
}

template <class T>
point2<T>::point2(const vec3& v)
{
	x = T(v.x);
	y = T(v.y);
}

template <class T>
point2<T>::point2(const vec4& v)
{
	x = T(v.x);
	y = T(v.y);
}

//////////////////
//POINT_3
/////////////////

template <class T>
point3<T>::point3(const vec2& v, const T Z)
{
	x = T(v.x);
	y = T(v.y);
    z = Z;
}

template <class T>
point3<T>::point3(const vec3& v)
{
	x = T(v.x);
	y = T(v.y);
    z = T(v.z);
}

template <class T>
point3<T>::point3(const vec4& v)
{
	x = T(v.x);
	y = T(v.y);
    z = T(v.z);
}

#endif