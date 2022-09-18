#include "JVector.h"

template<size_t n>
JVector<n> JVector<n>::operator *(float const& c) const
{
    JVector<n> product = *this;

    for (size_t i = 0; i < n; ++i)
        product.elements[i] *= c;

    return product;
}

template<size_t n>
JVector<n>& JVector<n>::operator *=(float const& c)
{
    return *this = *this * c;
}

template<size_t n>
JVector<n> JVector<n>::operator/(float const& c)
{
    return *this * (1 / c);
}

template<size_t n>
JVector<n>& JVector<n>::operator /=(float const& c)
{
    return *this = *this / c;
}

template<size_t n>
JVector<n> JVector<n>::operator +(void) const
{
    return *this;
}

template<size_t n>
JVector<n> JVector<n>::operator -(void) const
{
    return *this * -1;
}

template<size_t n>
JVector<n> JVector<n>::operator +(JVector<n> const& M) const
{
    JVector<n> product = *this;

    for (size_t i = 0; i < n; ++i)
        product.elements[i] += M.elements[i];

    return product;
}

template<size_t n>
JVector<n>& JVector<n>::operator +=(JVector<n> const& M)
{
    return *this = *this + M;
}

template<size_t n>
JVector<n> JVector<n>::operator -(JVector<n> const& M) const
{
    return *this + (-M);
}

template<size_t n>
JVector<n>& JVector<n>::operator -=(JVector<n> const& M)
{
    return *this = *this - M;
}

template<size_t n>
bool JVector<n>::operator ==(JVector<n> const& M) const
{
    for (int i = 0; i < n; i++)
        if (fabs(elements[i] - M[i]) > T_Epsilon) return false;
    return true;
}

template<size_t n>
float& JVector<n>::operator[](size_t const& i) const
{
    return const_cast<float&>(elements[i]);
}

template<size_t n>
inline float JVector<n>::length() const
{
    return sqrt(dot(*this, *this));
}

template<size_t n>
JVector<n>& JVector<n>::normalize()
{
    return *this = *this / length();
}

template<size_t n>
inline JVector<n> JVector<n>::GetRandomVector(int iLowerBound, int iUpperBound)
{
    JVector<n> vector;
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % (iUpperBound + 1) + iLowerBound;
    }
    return vector;
}

template<size_t n>
JVector<n> normalized(JVector<n> & v)
{
    return v / v.length();
}

template<size_t n>
inline float dot(JVector<n> const& u, JVector<n> const& v)
{
    float dotProduct = 0;

    for (int i = 0; i < n; i++)
        dotProduct += u[i] * v[i];

    return dotProduct;
}