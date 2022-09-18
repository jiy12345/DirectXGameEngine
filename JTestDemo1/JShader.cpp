#include "JShader.h"
void    JShader::setVertexData() {
    m_VertexList.resize(4);
    m_VertexList[0].p = { -0.5f, 0.5f, 0.0f };
    m_VertexList[1].p = { +0.5f, 0.5f,  0.0f };
    m_VertexList[2].p = { -0.5f, -0.5f, 0.0f };
    m_VertexList[3].p = { 0.5f, -0.5f, 0.0f };

    m_VertexList[0].c = { 1.0f, 0.0f, 1.0f, 1.0f };
    m_VertexList[1].c = { 0.0f, 1.0f, 1.0f, 1.0f };
    m_VertexList[2].c = { 1.0f, 1.0f, 0.0f, 1.0f };
    m_VertexList[3].c = { 1.0f, 0.0f, 0.0f, 1.0f };

    m_VertexList[0].t = { 0.0f, 0.0f };
    m_VertexList[1].t = { 1.0f, 0.0f };
    m_VertexList[2].t = { 0.0f, 1.0f };
    m_VertexList[3].t = { 1.0f, 1.0f };
}
void    JShader::setIndexData() {
    m_IndexList.resize(6);
    m_IndexList[0] = 0;
    m_IndexList[1] = 1;
    m_IndexList[2] = 2;
    m_IndexList[3] = 2;
    m_IndexList[4] = 1;
    m_IndexList[5] = 3;
}

HRESULT JShader::createVertexBuffer() {
    HRESULT hr;
    setVertexData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
    // GPU 메모리에 할당
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_VertexList.at(0);
    hr = I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pVertexBuffer);
    return hr;
}
HRESULT JShader::createIndexBuffer() {
    HRESULT hr;

    setIndexData();

    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_IndexList.at(0);
    hr = I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pIndexBuffer);
    return hr;
}

bool	JShader::init() {
    createVertexBuffer();
    createIndexBuffer();
    return true;
}
bool	JShader::frame() {
    return true;
}
bool	JShader::render() {
    I_Device.m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    I_Device.m_pImmediateContext->VSSetShader(m_pVS, NULL, 0);
    I_Device.m_pImmediateContext->PSSetShader(m_pPS, NULL, 0);
    UINT stride = sizeof(SimpleVertex);
    UINT offset = 0;
    I_Device.m_pImmediateContext->IASetVertexBuffers(0, 1,
        &m_pVertexBuffer, &stride, &offset);
    I_Device.m_pImmediateContext->IASetIndexBuffer(m_pIndexBuffer,
        DXGI_FORMAT_R32_UINT, 0);

    if (m_pIndexBuffer == nullptr)
        I_Device.m_pImmediateContext->Draw(m_VertexList.size(), 0);
    else
        I_Device.m_pImmediateContext->DrawIndexed(m_IndexList.size(), 0, 0);
    return true;
}
bool	JShader::release() {
    if (m_pVS) m_pVS->Release();
    if (m_pPS) m_pPS->Release();
    if (m_pVSCode) m_pVSCode->Release();
    if (m_pPSCode) m_pPSCode->Release();
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pIndexBuffer) m_pIndexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    return true;
}
HRESULT JShader::load(std::wstring filename) {
    HRESULT hr;
    ID3DBlob* pErrorCode = nullptr;
    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "VS",
        "vs_5_0",
        0,
        0,
        &m_pVSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    hr = I_Device.m_pd3dDevice->CreateVertexShader(
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        NULL,
        &m_pVS);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    hr = D3DCompileFromFile(
        filename.c_str(),
        NULL,
        NULL,
        "PS",
        "ps_5_0",
        0,
        0,
        &m_pPSCode,
        &pErrorCode);
    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    hr = I_Device.m_pd3dDevice->CreatePixelShader(
        m_pPSCode->GetBufferPointer(),
        m_pPSCode->GetBufferSize(),
        NULL,
        &m_pPS);

    if (FAILED(hr))
    {
        if (pErrorCode)
        {
            OutputDebugStringA((char*)pErrorCode->GetBufferPointer());
            pErrorCode->Release();
        }
        return hr;
    }

    D3D11_INPUT_ELEMENT_DESC ied[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
        { "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
    };
    UINT NumElements = sizeof(ied) / sizeof(ied[0]);
    hr = I_Device.m_pd3dDevice->CreateInputLayout(
        ied,
        NumElements,
        m_pVSCode->GetBufferPointer(),
        m_pVSCode->GetBufferSize(),
        &m_pVertexLayout);

    return hr;
}