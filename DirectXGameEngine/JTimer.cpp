#include "JTimer.h"

bool JTimer::init()
{
    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10.0f;
    QueryPerformanceFrequency(&m_Frequency);
    QueryPerformanceCounter(&m_Before);
    return true;
}

bool JTimer::frame()
{
    QueryPerformanceCounter(&m_Current);
    m_fElapseTimer = (float)(m_Current.QuadPart - m_Before.QuadPart) /
        (float)m_Frequency.QuadPart;
    m_fGameTimer += m_fElapseTimer;

    {
        m_iFPSCounter++;
        m_fFPSTimer += m_fElapseTimer;
        if (m_fFPSTimer >= 1.0f) {
            m_iFPS = m_iFPSCounter;
            m_iFPSCounter = 0;
            m_fFPSTimer = m_fFPSTimer - 1.0f;
        }
    }

    m_Before = m_Current;
    return true;
}

bool JTimer::render()
{
    m_szTimer = std::to_wstring(m_fGameTimer);
    m_szTimer += L"   ";
    m_szTimer += std::to_wstring(m_iFPS);
    m_szTimer += L"\n";
    OutputDebugString(m_szTimer.c_str());
    return true;
}

bool JTimer::release()
{
    return true;
}
