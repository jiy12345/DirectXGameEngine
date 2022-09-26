#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    I_Window.init();
    I_Device.init();
    I_Timer.init();
    I_Input.init();
    I_Sound.init();

    m_Writer.init();
    IDXGISurface1* m_pBackBuffer;
    I_Device.m_pSwapChain->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&m_pBackBuffer);
    m_Writer.set(m_pBackBuffer);

    return init();
}

bool JGameEngine::engineFrame()
{
    I_Timer.frame();
    I_Input.frame();
    m_Writer.frame();
    return frame();
}

bool JGameEngine::engineRender()
{
    I_Device.render();
    render();
    I_Timer.render();
    I_Input.render();
    m_Writer.render();
    I_Device.m_pSwapChain->Present(0, 0);
    return true;
}

bool JGameEngine::engineRelease()
{
    release();
    m_Writer.release();
    I_Sound.release();
    I_Input.release();
    I_Timer.release();
    I_Device.release();
    I_Window.release();
    return true;
}

bool JGameEngine::run()
{
    engineInit();
    I_Window.centerWindow();
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
