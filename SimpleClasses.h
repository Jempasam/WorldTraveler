#ifndef SIMPLECLASSES_H
#define SIMPLECLASSES_H

#include "SimpleFunction.h"

template<typename T>
class Pair
{
    public:
        T x,y;
        Pair() : x(0),y(0)
        {

        }
        Pair(T m_x,T m_y) : x(m_x),y(m_y)
        {

        }
};
template<typename T>
Pair<T> operator+(Pair<T> const& a, Pair<T> const& b)
{
    return Pair<T>(a.x+b.x,a.y+b.y);
}

template<typename T>
Pair<T> operator-(Pair<T> const& a, Pair<T> const& b)
{
    return Pair<T>(a.x-b.x,a.y-b.y);
}

template<typename T>
class Box
{
    public:
        Pair<T> a,b;
        Box() : a(0,0),b(0,0)
        {

        }
        Box(Pair<T> m_a,Pair<T> m_b) : a(m_a),b(m_b)
        {

        }
        Box(T x1,T y1,T x2,T y2) : a(x1,y1),b(x2,y2)
        {

        }
};

using Pair_int=Pair<int>;
using PairI=Pair<int>;
using PairF=Pair<float>;
using PairB=Pair<bool>;

using Position=Pair<float>;
using DispPos=Pair<int>;
using DispSize=Pair<unsigned int>;

#endif // SIMPLECLASSES_H
