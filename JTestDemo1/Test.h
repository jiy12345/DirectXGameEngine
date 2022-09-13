#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JWriter.h"

class Test : public JGameEngine
{
	JWriter m_Writer;
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


