#include "JFbxObject.h"

void JFbxObject::setVertexData()
{
}

void JFbxObject::setIndexData()
{
}

HRESULT JFbxObject::createVertexBuffer()
{
	HRESULT hr = S_OK;
	if (vbDataList.size() > 0)
	{
		for (int ivb = 0; ivb < vbDataList.size(); ivb++)
		{
			m_VertexList = vbDataList[ivb];
			hr = JBaseObject::createVertexBuffer();
			if (FAILED(hr)) return hr;

			m_pSubVB.push_back(m_pVertexBuffer);
		}
	}
	else
	{
		hr = JBaseObject::createVertexBuffer();
	}
	return hr;
}

HRESULT JFbxObject::createIndexBuffer()
{
    return S_OK;
}

bool JFbxObject::postRender()
{
	if (m_pIndexBuffer == nullptr)
	{
		if (vbDataList.size() > 0)
		{
			for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++)
			{
				UINT stride = sizeof(SimpleVertex);
				UINT offset = 0;
				I_Device.m_pImmediateContext->IASetVertexBuffers(0, 1,
					&m_pSubVB[iSubObj], &stride, &offset);

				ID3D11ShaderResourceView* pSRV = nullptr;
				I_Tex.loadSRV(pSRV, vbTexList[iSubObj]);
				I_Device.m_pImmediateContext->PSSetShaderResources(0, 1, &pSRV);
				I_Device.m_pImmediateContext->Draw(vbDataList[iSubObj].size(), 0);
			}
		}
		else
		{
			I_Device.m_pImmediateContext->Draw(m_VertexList.size(), 0);
		}
	}
	else
	{
		I_Device.m_pImmediateContext->DrawIndexed(m_dwFace * 3, 0, 0);
	}
	return true;
}

bool	JFbxObject::release()
{
	J3DObject::release();

	for (int iSubObj = 0; iSubObj < m_pSubVB.size(); iSubObj++) {
		if (m_pSubVB[iSubObj]) {
			m_pSubVB[iSubObj]->Release();
		}
	}
	return true;
}
