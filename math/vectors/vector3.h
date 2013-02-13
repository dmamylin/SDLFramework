#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class mat3;
class vec2;
class vec4;

class vec3
{
	public:
		float x, y, z;
	
		vec3() : x(0.0f), y(0.0f), z(0.0f) { }
		vec3(float X, float Y, float Z) : x(X), y(Y), z(Z) { }
		vec3(const vec3& v) : x(v.x), y(v.y), z(v.z) { }
        vec3(const vec2&, const float);
		vec3(const vec4&);
	
        friend bool operator == (const vec3&, const vec3&);
        friend bool operator != (const vec3&, const vec3&);
		friend const vec3 operator + (const vec3&); //Unary
		friend vec3 operator + (const vec3&, const vec3&);
		friend vec3 operator + (const vec3&, const float);
		friend vec3 operator + (const float, const vec3&);
		friend const vec3 operator - (const vec3&); //Unary
		friend vec3 operator - (const vec3&, const vec3&);
		friend vec3 operator - (const vec3&, const float);
		friend vec3 operator - (const float, const vec3&);
		friend vec3 operator * (const vec3&, const float);
		friend float operator * (const vec3&, const vec3&);
		friend vec3 operator * (const float, const vec3&);
        friend vec3 operator * (const mat3&, const vec3&);
        friend vec3 operator * (const vec3&, const mat3&);
		friend vec3 operator / (const vec3&, const float);
		friend vec3 operator / (const float, const vec3&);
		
		void operator = (const vec3&);
		void operator /= (const float);
		void operator *= (const float);
		void operator += (const float);
		void operator -= (const float);
		void operator += (const vec3&);
		void operator -= (const vec3&);
	
		float Length(void) const;
		void Normalize(void);
	
		friend vec3 CrossProduct(const vec3&, const vec3&);
		friend float DotProduct(const vec3&, const vec3&);
};

inline bool operator == (const vec3& a, const vec3& b)
{
    return ( (a.x == b.x) && (a.y == b.y) && (a.z == b.z) );
}

inline bool operator != (const vec3& a, const vec3& b)
{
    return !(a == b);
}

inline const vec3 operator + (const vec3& v)
{
	return v;
}

inline vec3 operator + (const vec3& a, const vec3& b)
{
	return vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline vec3 operator + (const vec3& v, const float k)
{
	return vec3(v.x + k, v.y + k, v.z + k);
}

inline vec3 operator + (const float k, const vec3& v)
{
	return v + k;
}

inline const vec3 operator - (const vec3& v)
{
	return vec3(-v.x, -v.y, -v.z);
}

inline vec3 operator - (const vec3& a, const vec3& b)
{
	return vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}
inline vec3 operator - (const vec3& v, const float k)
{
	return vec3(v.x - k, v.y - k, v.z - k);
}

inline vec3 operator - (const float k, const vec3& v)
{
	return v - k;
}

inline vec3 operator * (const vec3& v, const float k)
{
	return vec3(v.x * k, v.y * k, v.z * k);
}

inline float operator * (const vec3& v0, const vec3& v1)
{
	return (v0.x * v1.x + v0.y * v1.y + v0.z * v1.z);
}

inline vec3 operator * (const float k, const vec3& v)
{
	return v * k;
}

inline vec3 operator / (const vec3& v, const float k)
{
	return vec3(v.x / k, v.y / k, v.z / k);
}

inline vec3 operator / (const float k, const vec3& v)
{
	return v / k;
}

inline void vec3::operator = (const vec3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

inline void vec3::operator /= (const float k)
{
	x /= k;
	y /= k;
	z /= k;
}

inline void vec3::operator *= (const float k)
{
	x *= k;
	y *= k;
	z *= k;
}

inline void vec3::operator += (const float k)
{
	x += k;
	y += k;
	z += k;
}

inline void vec3::operator -= (const float k)
{
	x -= k;
	y -= k;
	z -= k;
}

inline void vec3::operator += (const vec3& v)
{
	(*this) = (*this) + v;
}

inline void vec3::operator -= (const vec3& v)
{
	(*this) = (*this) - v;
}

inline float vec3::Length(void) const
{
	return sqrt(x*x + y*y + z*z);
}

inline void vec3::Normalize(void)
{
	(*this)  /= Length();
}

inline vec3 CrossProduct(const vec3& a, const vec3& b)
{
	return vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

inline float DotProduct(const vec3& a, const vec3& b)
{
	return ( (a * b) / (a.Length() * b.Length()) );
}

#endif
