#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    I_Window.init();
    I_Device.init();
    I_Timer.init();
    return init();
}

bool JGameEngine::engineFrame()
{
    I_Timer.frame();
    return frame();
}

bool JGameEngine::engineRender()
{
    I_Device.render();
    render();
    I_Timer.render();
    I_Device.m_pSwapChain->Present(0, 0);
    return true;
}

bool JGameEngine::engineRelease()
{
    release();
    I_Timer.release();
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
