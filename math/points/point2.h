#ifndef POINT2_H
#define POINT2_H

class vec2;
class vec3;
class vec4;

template <class T>
class point2
{
	public:
		T x, y;
		
		point2() : x(0), y(0) { }
		point2(const T X, const T Y) : x(X), y(Y) { }		
		point2(const vec2&);
		point2(const vec3&);
		point2(const vec4&);

        template <class F>
		point2(const point2<F>& p) : x( T(p.x) ), y( T(p.y) ) { }
		
		template <class F>
		void operator = (const point2<F>& p) 
		{ 
			x = T(p.x); 
			y = T(p.y); 
		}
		
		template <class F>
		inline bool operator == (const point2<F>& p)
		{
			return ( x == T(p.x) && y == T(p.y) );
		}
		
		template <class F>
		inline bool operator != (const point2<F>& p)
		{
			return !( (*this) == p );
		}

        friend inline point2<T> operator + (const point2<T>& p1, const point2<T>& p2)
        {
            return point2<T>(p1.x + p2.x, p1.y + p2.y);
        }
		
		template <class F>
		inline float DistanceTo(const point2<F>& p)
		{ 
			return sqrt( float((p.x - x) * (p.x - x) + (p.y - y) * (p.y - y)) ); 
		}
};

#endif