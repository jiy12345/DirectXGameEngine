#include "JGameEngine.h"

bool JGameEngine::engineInit()
{
    return false;
}

bool JGameEngine::engineFrame()
{
    return false;
}

bool JGameEngine::engineRender()
{
    return false;
}

bool JGameEngine::engineRelease()
{
    return false;
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
