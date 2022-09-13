#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    I_Device.init();
    return true;
}

bool JGameEngine::engineFrame()
{
    return true;
}

bool JGameEngine::engineRender()
{
    I_Device.m_pImmediateContext->OMSetRenderTargets(1, &I_Device.m_pRTV, NULL);
    float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };
    I_Device.m_pImmediateContext->ClearRenderTargetView(I_Device.m_pRTV, color);
    I_Device.m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    return false;
}

bool JGameEngine::engineRelease()
{
    I_Device.release();
    return true;
}

bool JGameEngine::run()
{
    engineInit();
    while (m_bGameRun) {
        if (I_Window.run() == true) {
            engineFrame();
            engineRender();
        }
        else {
            m_bGameRun = false;
        }
    }
    engineRelease();
    return true;
}
