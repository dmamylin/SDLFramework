#ifndef RECT2_H
#define RECT2_H

template <class T>
struct rect2
{
    T width, height;

    rect2() : width(0), height(0) { }
    rect2(const T w, const T h) : width(w), height(h) { }

    template <class F>
    rect2(const rect2<F>&);

    inline T Area(void) { return width * height; }

    template <class F>
    void operator = (const rect2<F>&);

    template <class F>
    friend bool operator == (const rect2<T>&, const rect2<F>&);

    template <class F>
    friend bool operator != (const rect2<T>&, const rect2<F>&);
};

template <class T>
template <class F>
rect2<T>::rect2(const rect2<F>& r)
{
    width  = T(r.width);
    height = T(r.height);
}

template <class T>
template <class F>
inline void rect2<T>::operator = (const rect2<F>& r)
{
    width  = T(r.width);
    height = T(r.height);    
}

template <class T, class F>
inline bool operator == (const rect2<T>& r0, const rect2<F>& r1)
{
    return ( r0.width == T(r1.width) && r0.height == T(r1.height) );
}

template <class T, class F>
inline bool operator != (const rect2<T>& r0, const rect2<F>& r1)
{
    return !(r0 == r1);
}

#endif