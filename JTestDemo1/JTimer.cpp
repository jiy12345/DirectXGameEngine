#include "JTimer.h"

bool JTimer::Init()
{
    m_fGameTimer = 0.0f;
    m_fElapseTimer = 10.0f;
    m_dwBeforeTime = timeGetTime();
    return true;
}

bool JTimer::Frame()
{
    DWORD dwCurrentTime = timeGetTime();
    DWORD dwElapseTime = dwCurrentTime - m_dwBeforeTime;
    m_fElapseTimer = dwElapseTime / 1000.0f;
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

    m_dwBeforeTime = dwCurrentTime;
    return true;

}

bool JTimer::Render()
{
    m_szTimer = std::to_wstring(m_fGameTimer);
    m_szTimer += L"   ";
    m_szTimer += std::to_wstring(m_iFPS);
    m_szTimer += L"\n";
    OutputDebugString(m_szTimer.c_str());
    return true;
}

bool JTimer::Release()
{
    return true;
}
