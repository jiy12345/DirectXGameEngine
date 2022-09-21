#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JShader.h"

class Test : public JGameEngine
{
	JShader* m_pShader1;
	JShader* m_pShader2;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


