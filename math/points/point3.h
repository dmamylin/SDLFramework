#ifndef POINT3_H
#define POINT3_H

#include <math.h>

class vec2;
class vec3;
class vec4;

template <class T>
class point3
{
	public:
		T x, y, z;
		
		point3() : x(0), y(0), z(0) { }
        point3(const T X, const T Y, const T Z) : x(X), y(Y), z(Z) { }        
		point3(const vec2&, const T);
		point3(const vec3&);
		point3(const vec4&);

        template <class F>
		point3(const point3<F>& p) : x( T(p.x) ), y( T(p.y) ), z( T(p.z) ) { }
		
		template <class F>
		void operator = (const point3<F>& p) 
		{ 
			x = T(p.x); 
			y = T(p.y);
            z = T(p.z);
		}
		
		template <class F>
		inline bool operator == (const point3<F>& p)
		{
			return ( (x == T(p.x)) && (y == T(p.y)) && (z == T(p.z)) );
		}
		
		template <class F>
		inline bool operator != (const point3<F>& p)
		{
			return !( (*this) == p );
		}
};

#endif