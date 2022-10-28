#pragma once
#include<cstring>

template<size_t m, size_t n>
class JMatrix
{
    friend class JMatrix;

private:
    float elements[m][n];

public:
    template<typename... type>
    JMatrix(type const &... elements) : elements{ static_cast<float const>(elements)... }
    {
        static_assert(not (m == 1 and n == 1), "matrix<1, 1> cannot be created.");
    }

    JMatrix() {
        if (n == m) {
            for (int i = 0; i < m; i++)
                for (int j = 0; j < n; j++) {
                    if (i == j) elements[i][j] = 1;
                    else        elements[i][j] = 0;
                }
        }
        else {
            memset(elements, 0, sizeof(elements));
        }
    }

    void const zeroMatrix() {
        memset(elements, 0, sizeof(elements));
    }

    auto const operator *(float const& c) const
    {
        JMatrix<m, n> product = *this;

        for (size_t i = 0; i < m; ++i)
            for (size_t j = 0; j < n; ++j)
                product.elements[i][j] *= c;

        return product;
    }

    auto& operator *=(float const& c)
    {
        return *this = *this * c;
    }

    auto const operator /(float const& c) const
    {
        return *this * (1 / c);
    }

    auto& operator /=(float const& c)
    {
        return *this = *this / c;
    }

    auto const operator +(void) const
    {
        return *this;
    }

    auto const operator +(JMatrix<m, n> const& M) const
    {
        JMatrix<m, n> product = *this;

        for (size_t i = 0; i < m; ++i)
            for (size_t j = 0; j < n; ++j)
                product.elements[i][j] += M.elements[i][j];

        return product;
    }

    auto& operator +=(JMatrix<m, n> const& M)
    {
        return *this = *this + M;
    }

    auto const operator -(void) const
    {
        return *this * -1;
    }

    auto const operator -(JMatrix<m, n> const& M) const
    {
        return *this + (-M);
    }

    auto& operator -=(JMatrix<m, n> const& M)
    {
        return *this = *this - M;
    }

    template<size_t l>
    auto const operator *(JMatrix<n, l> const& M) const
    {
        if constexpr (m == 1 and l == 1)
        {
            float product = float();

            for (size_t i = 0; i < n; ++i)
                product += (*this).elements[0][i] * M.elements[i][0];

            return product;
        }
        else
        {
            JMatrix<m, l> product = JMatrix<m, l>();
            product.zeroMatrix();

            for (size_t i = 0; i < m; ++i)
                for (size_t j = 0; j < l; ++j)
                    for (size_t k = 0; k < n; ++k)
                        product.elements[i][j] += (*this).elements[i][k] * M.elements[k][j];

            return product;
        }
    }

    auto& operator *=(JMatrix<n, n> const& M)
    {
        return *this = *this * M;
    }

    auto& operator [](size_t const& i)
    {
        if constexpr (m == 1 and n != 1) return elements[0][i];
        else if constexpr (m != 1 and n == 1) return elements[i][0];
        else                                  return elements[i];
    }

    auto const& operator [](size_t const& i) const
    {
        return const_cast<JMatrix<m, n> &>(*this)[i];
    }
};

template<size_t m, size_t n>
inline JMatrix<n, m> const transpose(JMatrix<m, n> const& M)
{
    if constexpr (m == 1 or n == 1)
    {
        return reinterpret_cast<JMatrix<n, m> const&>(M);
    }
    else
    {
        JMatrix<n, m> product = JMatrix<n, m>();

        for (size_t i = 0; i < n; ++i)
            for (size_t j = 0; j < m; ++j)
                product[i][j] = M[j][i];

        return product;
    }
}