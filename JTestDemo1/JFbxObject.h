#pragma once
#include "stdafx.h"
#include "J3DObject.h"

class JFbxObject : public J3DObject
{
public:
	std::vector<JFbxObject*> m_pDrawChild;
	std::vector<std::vector<SimpleVertex>>   vbDataList;
	std::vector<W_STR>   vbTexList;
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

