#pragma once
#include "stdafx.h"

struct JSprite
{
	int						m_iNumFrame;
	float					m_totalTime;
	std::vector<nCube<2>>	m_spriteRtLists;
};

