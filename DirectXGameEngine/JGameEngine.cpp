#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    I_Window.init();
    I_Device.init();
    return true;
}

bool JGameEngine::engineFrame()
{
    return true;
}

bool JGameEngine::engineRender()
{
    I_Device.render();
    I_Device.m_pSwapChain->Present(0, 0);
    return false;
}

bool JGameEngine::engineRelease()
{
    I_Device.release();
    I_Window.release();
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
