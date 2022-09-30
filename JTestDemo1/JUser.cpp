#include "JUser.h"

bool JUser::init()
{
    JBaseObject::init();
    I_Sprite.load(m_vSpriteInfo, L"../data/sprites/pilot.txt");
    m_fStep = m_vSpriteInfo[m_curSprite].m_fTotalTime / m_vSpriteInfo[m_curSprite].m_iNumFrame;
    return false;
}

bool JUser::frame()
{
    float curPosInViewY = -(I_Input.m_ptPos.y - I_Window.m_rtClient.bottom / 2);
    float curPosInViewX = I_Input.m_ptPos.x - I_Window.m_rtClient.right / 2;
    float angle = static_cast<float>(atan2(curPosInViewY, curPosInViewX) * 180 / PI);
    std::cout << angle << '\n';
    setCurDirection(angle);

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

void JUser::updateUVCoord()
{
    m_fEffectTimer += I_Timer.m_fElapseTimer;
    if (m_fStep <= m_fEffectTimer)
    {
        m_fEffectTimer -= m_fStep;
        m_iIndex++;
    }
    if (m_iIndex >= m_vSpriteInfo[m_curSprite].m_iNumFrame)
    {
        m_fEffectTimer = 0;
        //m_fEffectTimer -= m_vSpriteInfo[m_curSprite].m_fTotalTime;
        m_iIndex = 0;
    }
    m_rtUV = m_vSpriteInfo[m_curSprite].m_vSpriteRtLists[m_iIndex];

    m_rtUV.m_vLeftTop[0] /= m_vSpriteInfo[m_curSprite].m_vTotalTextureSize[0];
    m_rtUV.m_vLeftTop[1] /= m_vSpriteInfo[m_curSprite].m_vTotalTextureSize[1];
    m_rtUV.m_vSize[0] /= m_vSpriteInfo[m_curSprite].m_vTotalTextureSize[0];
    m_rtUV.m_vSize[1] /= m_vSpriteInfo[m_curSprite].m_vTotalTextureSize[1];
}

void JUser::setCurDirection(float angle) {
    if (angle >= 150 || angle <= -120) {
        m_curSprite = IDLE_LEFT;
    }
    else if (120 < angle && angle <= 150) {
        m_curSprite = IDLE_LEFT_UP;
    }
    else if (60 < angle && angle <= 120) {
        m_curSprite = IDLE_UP;
    }
    else if (30 < angle && angle <= 60) {
        m_curSprite = IDLE_RIGHT_UP;
    }
    else if (-60 < angle && angle <= 60) {
        m_curSprite = IDLE_RIGHT;
    }
    else if (-120 < angle && angle <= -60) {
        m_curSprite = IDLE_DOWN;
    }
}