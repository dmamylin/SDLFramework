#ifndef VECTOR2_H
#define VECTOR2_H

class vec3;
class vec4;

class vec2
{
	public:
		float x, y;

        vec2() : x(0.0f), y(0.0f) { }
        vec2(float X, float Y) : x(X), y(Y) { }
        vec2(const vec2& v) : x(v.x), y(v.y) { }
        vec2(const vec3&);
        vec2(const vec4&);

        friend bool operator == (const vec2&, const vec2&);
        friend bool operator != (const vec2&, const vec2&);
        friend const vec2 operator + (const vec2&); //Unary
		friend vec2 operator + (const vec2&, const vec2&);
		friend vec2 operator + (const vec2&, const float);
		friend vec2 operator + (const float, const vec2&);
		friend const vec2 operator - (const vec2&); //Unary
		friend vec2 operator - (const vec2&, const vec2&);
		friend vec2 operator - (const vec2&, const float);
		friend vec2 operator - (const float, const vec2&);
		friend vec2 operator * (const vec2&, const float);
		friend float operator * (const vec2&, const vec2&);
		friend vec2 operator * (const float, const vec2&);
		friend vec2 operator / (const vec2&, const float);
		friend vec2 operator / (const float, const vec2&);

        inline float& operator [] (int ind) { return *(&x + ind); }
        inline float operator [] (int ind) const { return *(&x + ind); }
        void operator = (const vec2&);
		void operator /= (const float);
		void operator *= (const float);
		void operator += (const float);
		void operator -= (const float);
		void operator += (const vec2&);
		void operator -= (const vec2&);

        inline float Length(void) const { return sqrt(x * x + y * y); }
        void Normalize(void);
};

inline bool operator == (const vec2& a, const vec2& b)
{
    return ( (a.x == b.x) && (a.y == b.y) );
}

inline bool operator != (const vec2& a, const vec2& b)
{
    return !(a == b);
}

inline const vec2 operator + (const vec2& v)
{
    return v;
}

inline vec2 operator + (const vec2& a, const vec2& b)
{
	return vec2(a.x + b.x, a.y + b.y);
}

inline vec2 operator + (const vec2& v, const float k)
{
	return vec2(v.x + k, v.y + k);
}

inline vec2 operator + (const float k, const vec2& v)
{
	return v + k;
}

inline const vec2 operator - (const vec2& v)
{
	return vec2(-v.x, -v.y);
}

inline vec2 operator - (const vec2& a, const vec2& b)
{
	return vec2(a.x - b.x, a.y - b.y);
}
inline vec2 operator - (const vec2& v, const float k)
{
	return vec2(v.x - k, v.y - k);
}

inline vec2 operator - (const float k, const vec2& v)
{
	return v - k;
}

inline vec2 operator * (const vec2& v, const float k)
{
	return vec2(v.x * k, v.y * k);
}

inline float operator * (const vec2& v0, const vec2& v1)
{
	return (v0.x * v1.x + v0.y * v1.y);
}

inline vec2 operator * (const float k, const vec2& v)
{
	return v * k;
}

inline vec2 operator / (const vec2& v, const float k)
{
	return vec2(v.x / k, v.y / k);
}

inline vec2 operator / (const float k, const vec2& v)
{
	return v / k;
}

inline void vec2::operator = (const vec2& v)
{
	x = v.x;
	y = v.y;
}

inline void vec2::operator /= (const float k)
{
	x /= k;
	y /= k;
}

inline void vec2::operator *= (const float k)
{
	x *= k;
	y *= k;
}

inline void vec2::operator += (const float k)
{
	x += k;
	y += k;
}

inline void vec2::operator -= (const float k)
{
	x -= k;
	y -= k;
}

inline void vec2::operator += (const vec2& v)
{
	(*this) = (*this) + v;
}

inline void vec2::operator -= (const vec2& v)
{
	(*this) = (*this) - v;
}

inline void vec2::Normalize(void)
{
    (*this) /= Length();
}

#endif
