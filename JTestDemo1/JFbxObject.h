#pragma once
#include "stdafx.h"
#include "J3DObject.h"

class JFbxObject : public J3DObject
{
public:
	void  CreateVertexData()
	{
	}
	HRESULT CreateIndexBuffer()
	{
		return S_OK;
	}

public:
	void	setVertexData() override {};
	void	setIndexData() override {};
	HRESULT createIndexBuffer() override {
		return S_OK;
	};
};

