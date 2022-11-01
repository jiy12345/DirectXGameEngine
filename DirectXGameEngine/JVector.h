#pragma once
#include <math.h>
#include <cstdlib>
#include <stdarg.h>
#include "JMatrix.h"

#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f

template<size_t n>
using JVector = JMatrix<1, n>;

template<size_t n>
inline float length(const JVector<n>& v)
{
    return sqrt(dot(v, v));
}

template<size_t n>
inline JVector<n> GetRandomVector(int iLowerBound, int iUpperBound)
{
    JVector<n> vector;
    for (int i = 0; i < n; i++) {
        vector[i] = rand() % (iUpperBound + 1) + iLowerBound;
    }
    return vector;
}

template<size_t n>
JVector<n> normalized(const JVector<n>& v)
{
    return v / length(v);
}

template<size_t n>
inline float dot(JVector<n> const& u, JVector<n> const& v)
{
    float dotProduct = 0;

    for (int i = 0; i < n; i++)
        dotProduct += u[i] * v[i];

    return dotProduct;
}

inline JVector<3> const cross(JVector<3> const& u, JVector<3> const& v)
{
    JVector<3> product = JVector<3>();

    for (size_t i = 0; i < 3; ++i)
    {
        size_t const j = (i + 1) % 3;
        size_t const k = (j + 1) % 3;

        product[i] = u[j] * v[k] - u[k] * v[j];
    }

    return product;
}