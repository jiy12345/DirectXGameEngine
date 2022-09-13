#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    I_Window.init();
    I_Device.init();
    return init();
}

bool JGameEngine::engineFrame()
{
    return frame();
}

bool JGameEngine::engineRender()
{
    I_Device.render();
    render();
    I_Device.m_pSwapChain->Present(0, 0);
    return true;
}

bool JGameEngine::engineRelease()
{
    release();
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
