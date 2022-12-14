#include "JVector.h"

template<size_t n>
struct nCube
{
public:
    JVector<n> m_vCenter;
    JVector<n> m_vSize;
public:
    nCube() {}
    nCube(const JVector<n>& vPos, const JVector<n>& vSize)
    {
        Set(vPos, vSize);
    }
    void  Set(const JVector<n>& vPos, const JVector<n>& vSize)
    {
        m_vCenter = vPos;
        this->m_vSize = vSize;
    }
public:
    bool   operator == (nCube<n>& dest)
    {
        if (m_vCenter == dest.m_vCenter)
        {
            if (m_vSize == dest.m_vSize)
            {
                return true;
            }
        }
        return false;
    }
};

template<size_t n>
struct nSphere
{
public:
    JVector<n> m_vCenter;
    float m_fRadius;
public:
    nSphere() {
        for (int i = 0; i < n; i++)
            m_vCenter[i] = 0;
        m_fRadius = 1;
    };
    nSphere(const JVector<n>& vC, const float& r) {
        m_vCenter = vC;
        m_fRadius = r;
    };
    void  Set(const JVector<n>& vCenter, const float& radius)
    {
        m_vCenter = vCenter;
        m_fRadius = radius;
    }
    void Set(const nCube<n>& cube) {
        m_vCenter = cube.vCenter();
        m_fRadius = (cube.m_vSize * 0.5f).length();
    }
};
