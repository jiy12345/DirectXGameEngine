#pragma once
#include"J3DObject.h"
class JBox: public J3DObject
{
public:
	virtual void		setVertexData() override;
	virtual void		setIndexData() override;
public:
	virtual bool		init() override;
	virtual bool		frame() override;
public:
	JBox() {};
	virtual ~JBox() {};
};

