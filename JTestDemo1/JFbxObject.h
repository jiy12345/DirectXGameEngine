#pragma once
#include "stdafx.h"
#include "J3DObject.h"

class JFbxObject : public J3DObject
{
public:
	DWORD									m_dwFace;
public:
	std::vector<ID3D11Buffer*>				m_pSubVB;
	std::vector<std::vector<SimpleVertex>>	vbDataList;
	std::vector<W_STR>						vbTexList;
public:
	void	setVertexData() override;
	void	setIndexData() override;
	HRESULT createVertexBuffer() override;
	HRESULT createIndexBuffer() override;
public:
	bool postRender() override;
	bool release();
};

