#include"stdafx.h"

template<size_t n>
struct nCube
{
    JVector<n> m_vMin;
    JVector<n> m_vSize;
    bool   operator == (nCube<n>& dest)
    {
        if (m_vMin == dest.m_vMin)
        {
            if (m_vSize == dest.m_vSize)
            {
                return true;
            }
        }
        return false;
    }
    nCube() {}
    nCube(const JVector<n> &vPos, const JVector<n>& vSize)
    {
        Set(vPos, vSize);
    }
    void  Set(const JVector<n>& vPos, const JVector<n>& vSize)
    {
        m_vMin = vPos;
        this->m_vSize = vSize;
    }
    JVector<n> vMax() const {
        return m_vMin + m_vSize;
    }
    JVector<n> vCenter() const {
        return (m_vMin + vMax()) / 2.0f;
    }
};

template<size_t n>
struct nSphere
{
    JVector<n> m_vCenter;
    float m_fRadius;
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
