#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JBox.h"
#include "JFbxLoader.h"

class Test : public JGameEngine
{
	JFbxLoader m_FBXLoader;
	JBox* m_pJBox;
	JSoundChannel* m_pBGM;
	std::vector<JSoundChannel*> m_pGunShots;

public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


