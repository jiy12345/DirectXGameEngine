#pragma once
#include <math.h>
#include <cstdlib>
#include <time.h>
#include <stdarg.h>

#define T_PI 3.141592f
#define DegreeToRadian(x)  (x *(T_PI / 180.0f))
#define RadianToDegree(x) (x *(180.0f / T_PI))
#define T_Epsilon 0.001f

template<size_t n>
class JVector
{
    friend class JVector;
private:
    float elements[n];

public:
    template<typename... type>
    JVector(type const &... elements) : elements{ static_cast<float const>(elements)... }
    {
        static_assert(not (n == 1), "A vector of size 1 cannot be created.");
    }

    // ��Į�� ����
    JVector<n> operator *(float const& c) const;
    JVector<n>& operator *=(float const& c);
    JVector<n> operator /(float const& c);
    JVector<n>& operator /=(float const& c);

    // ��ȣ
    JVector<n> operator +(void) const;
    JVector<n> operator -(void) const;

    // ���Ͱ� ����
    JVector<n> operator +(JVector<n> const& M) const;
    JVector<n>& operator +=(JVector<n> const& M);
    JVector<n> operator -(JVector<n> const& M) const;
    JVector<n>& operator -=(JVector<n> const& M);

    // ���� ��
    bool operator ==(JVector<n> const& M) const;

    // �ε���
    float& operator [](size_t const& i) const;

    // ũ��
    inline float length() const;
    
    // ����ȭ
    JVector<n>& normalize();

    static inline JVector<n> GetRandomVector(int iLowerBound, int iUpperBound);
};