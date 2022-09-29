#include "JUser.h"

bool JUser::frame()
{
    JVector<2> vPos = m_rtArea.m_vLeftTop;
    if (I_Input.GetKey('W'))
    {
        vPos[1] += -1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('S'))
    {
        vPos[1] += +1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('A'))
    {
        vPos[0] += -1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    if (I_Input.GetKey('D'))
    {
        vPos[0] += +1.0f * I_Timer.m_fElapseTimer * m_fSpeed;
    }
    m_rtArea.m_vLeftTop = vPos;

    return true;
}
