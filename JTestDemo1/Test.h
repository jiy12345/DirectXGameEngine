#pragma once
#include "stdafx.h"
#include "JGameEngine.h"
#include "JInput.h"

class Test : public JGameEngine
{
public:
	virtual bool init() override;
	virtual bool frame() override;
	virtual bool render() override;
	virtual bool release() override;
};


