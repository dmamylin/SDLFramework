#ifndef COLOR3_H
#define COLOR3_H

template <class T>
struct color3
{
	T r, g, b;
	
	color3() : r(0), g(0), b(0) { }
	color3(T R, T G, T B) : r(R), g(G), b(B) { }

    template <class F>
    color3(const color3<F>&);

    template <class F>
    void Set(const color3<F>& c) { *this = c; }

    template <class F>
    void Set(const F R, const F G, const F B) { r = R; g = G; b = B; }

    template <class F>
    void operator = (const color3<F>&);

    template <class F>
    friend bool operator == (const color3<T>&, const color3<F>&);

    template <class F>
    friend bool operator != (const color3<T>&, const color3<F>&);
	
	~color3() { }
};

template <class T>
template <class F>
color3<T>::color3(const color3<F>& c)
{
    r = T(c.r);
    g = T(c.g);
    b = T(c.b);
}

template <class T>
template <class F>
inline void color3<T>::operator = (const color3<F>& c)
{
    r = T(c.r);
    g = T(c.g);
    b = T(c.b);
}

template <class T, class F>
inline bool operator == (const color3<T>& c0, const color3<F>& c1)
{
    return ( (c0.r == T(c1.r)) && (c0.g == T(c1.g)) && (c0.b == T(c1.b)) );
}

template <class T, class F>
inline bool operator != (const color3<T>& c0, const color3<F>& c1)
{
    return !(c0 == c1);
}

#endif