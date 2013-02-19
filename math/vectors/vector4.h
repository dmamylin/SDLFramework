#ifndef VECTOR4_H
#define VECTOR4_H

class mat4;
class vec3;

class vec4
{
	public:
		float x, y, z, w;

		vec4() : x(0.0f), y(0.0f), z(0.0f), w(0.0f) { }
		vec4(float X, float Y, float Z, float W) : x(X), y(Y), z(Z), w(W) { }
		vec4(const vec4& v) : x(v.x), y(v.y), z(v.z), w(v.w) { }
        vec4(const vec2&, const float, const float);
		vec4(const vec3&, const float);
		
		friend bool operator == (const vec4&, const vec4&);
		friend bool operator != (const vec4&, const vec4&);
		friend const vec4 operator + (const vec4&); //Unary
		friend vec4 operator + (const vec4&, const  vec4&);
		friend vec4 operator + (const vec4&, const float);
		friend vec4 operator + (const float, const vec4&);
		friend const vec4 operator - (const vec4&); //Unary
		friend vec4 operator - (const vec4&, const vec4&);
		friend vec4 operator - (const vec4&, const float);
		friend vec4 operator - (const float, const vec4&);
		friend float operator * (const vec4&, const vec4&);		
		friend vec4 operator * (const vec4&, const float);
		friend vec4 operator * (const float, const vec4&);
		friend vec4 operator * (const mat4&, const vec4&);
		friend vec4 operator * (const vec4&, const mat4&);
		friend vec4 operator / (const float, const vec4&);
		friend vec4 operator / (const vec4&, const float);

        inline float& operator [] (int ind) { return *(&x + ind); }
        inline float operator [] (int ind) const { return *(&x + ind); }
		void operator = (const vec4&);
		void operator /= (const float);
		void operator *= (const float);
        void operator *= (const mat4&);
		void operator += (const float);
        void operator += (const vec4&);
		void operator -= (const float);		
		void operator -= (const vec4&);		
	
		inline float Length(void) { return sqrt(x*x + y*y + z*z + w*w); }
		void Normalize(void);
};

inline bool operator == (const vec4& a, const vec4& b)
{
	return ( a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w );
}

inline bool operator != (const vec4& a, const vec4& b)
{
	return !(a == b);
}

inline const vec4 operator + (const vec4& v)
{
	return v;
}

inline vec4 operator + (const vec4& a, const vec4& b)
{
	return vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

inline vec4 operator + (const vec4& v, const float k)
{
	return vec4(v.x + k, v.y + k, v.z + k, v.w + k);
}

inline vec4 operator + (const float k, const vec4& v)
{
	return v + k;
}

inline const vec4 operator - (const vec4& v)
{
    return vec4(-v.x, -v.y, -v.z, -v.w);
}

inline vec4 operator - (const vec4& a, const vec4& b)
{
	return vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}
inline vec4 operator - (const vec4& v, const float k)
{
	return vec4(v.x - k, v.y - k, v.z - k, v.w - k);
}

inline vec4 operator - (const float k, const vec4& v)
{
	return v - k;
}

inline float operator * (const vec4& a, const vec4& b)
{
	return (a.x * b.x + a.y + b.y + a.z * b.z + a.w * b.w);
}

inline vec4 operator * (const vec4& v, const float k)
{
	return vec4(v.x * k, v.y * k, v.z * k, v.w * k);
}

inline vec4 operator * (const float k, const vec4& v)
{
	return v * k;
}

inline vec4 operator / (const vec4& v, const float k)
{
	return vec4(v.x / k, v.y / k, v.z / k, v.w / k);
}

inline vec4 operator / (const float k, const vec4& v)
{
	return v / k;
}

inline void vec4::operator = (const vec4& vr)
{
	x = vr.x;
	y = vr.y;
	z = vr.z;
	w = vr.w;
}

inline void vec4::operator /= (const float k)
{
	x /= k;
	y /= k;
	z /= k;
	w /= k;
}

inline void vec4::operator *= (const float k)
{
	x *= k;
	y *= k;
	z *= k;
	w *= k;
}

inline void vec4::operator += (const float k)
{
	x += k;
	y += k;
	z += k;
	w += k;
}

inline void vec4::operator -= (const float k)
{
	x -= k;
	y -= k;
	z -= k;
	w -= k;
}

inline void vec4::operator += (const vec4& v)
{
	(*this) = (*this) + v;
}

inline void vec4::operator -= (const vec4& v)
{
	(*this) = (*this) - v;
}

inline void vec4::Normalize(void)
{
	(*this) /= Length();
}

#endif