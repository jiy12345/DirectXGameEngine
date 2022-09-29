#include "JTestObject.h"

bool JTestObject::frame()
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

void JTestObject::updateVertexBuffer()
{
    nCube<2> rtNDC = getNDC();
    m_VertexList[0].p = { rtNDC.m_vLeftTop[0], rtNDC.m_vLeftTop[1] + rtNDC.m_vSize[1], 0.0f };
    m_VertexList[0].t = { m_rtUV.m_vLeftTop[0], m_rtUV.m_vLeftTop[1] };

    m_VertexList[1].p = { rtNDC.m_vLeftTop[0] + rtNDC.m_vSize[0],  rtNDC.m_vLeftTop[1] + rtNDC.m_vSize[1],  0.0f };
    m_VertexList[1].t = { m_rtUV.m_vLeftTop[0] + m_rtUV.m_vSize[0], m_rtUV.m_vLeftTop[1] };

    m_VertexList[2].p = { rtNDC.m_vLeftTop[0],  rtNDC.m_vLeftTop[1], 0.0f };
    m_VertexList[2].t = { m_rtUV.m_vLeftTop[0], m_rtUV.m_vLeftTop[1] + m_rtUV.m_vSize[1] };

    m_VertexList[3].p = { rtNDC.m_vLeftTop[0] + rtNDC.m_vSize[0],  rtNDC.m_vLeftTop[1], 0.0f };
    m_VertexList[3].t = { m_rtUV.m_vLeftTop[0] + m_rtUV.m_vSize[0], m_rtUV.m_vLeftTop[1] + m_rtUV.m_vSize[1] };

    I_Device.m_pImmediateContext->UpdateSubresource(
        m_pVertexBuffer, NULL, NULL, &m_VertexList.at(0), 0, 0);
}

nCube<2> JTestObject::getNDC()
{
    nCube<2> rtNDC;

    rtNDC.m_vLeftTop[0] = m_rtArea.m_vLeftTop[0] / I_Window.m_rtClient.right * 2 - 1;
    rtNDC.m_vLeftTop[1] = -((m_rtArea.m_vLeftTop[1] + m_rtArea.m_vSize[1]) / I_Window.m_rtClient.bottom * 2 - 1);
    rtNDC.m_vSize[0] = m_rtArea.m_vSize[0] / I_Window.m_rtClient.right * 2;
    rtNDC.m_vSize[1] = m_rtArea.m_vSize[1] / I_Window.m_rtClient.bottom * 2;

	return rtNDC;
}
