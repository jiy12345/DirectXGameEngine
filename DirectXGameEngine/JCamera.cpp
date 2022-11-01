#include "JCamera.h"

bool JCamera::frame()
{
	m_Aspect = (float)I_Window.m_rtClient.right / (float)I_Window.m_rtClient.bottom;
	return true;
}
