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
    setVertexData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(SimpleVertex) * m_VertexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_VertexList.at(0);
    return I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pVertexBuffer);
}
HRESULT JShader::createIndexBuffer() {
    setIndexData();
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(DWORD) * m_IndexList.size();
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_IndexList.at(0);
    return I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pIndexBuffer);;
}

bool	JShader::init() {
    m_wstrVSName = L"DefaultShapeMask.hlsl";
    m_wstrPSName = L"DefaultShapeMask.hlsl";
    m_strVSFuncName = "VS";
    m_strPSFuncName = "PS";
    createVertexBuffer();
    createIndexBuffer();
    setInputLayout();

    return true;
}
bool	JShader::frame() {
    return true;
}
bool	JShader::render() {
    HRESULT hr;
    ID3D11VertexShader* pVS = nullptr;
    hr = I_Shader.loadVS(pVS, m_wstrVSName, m_strVSFuncName);
    if (FAILED(hr)) return false;

    ID3D11PixelShader* pPS = nullptr;
    hr = I_Shader.loadPS(pPS, m_wstrPSName, m_strPSFuncName);
    if (FAILED(hr)) return false;

    I_Device.m_pImmediateContext->IASetInputLayout(m_pVertexLayout);
    I_Device.m_pImmediateContext->VSSetShader(pVS, NULL, 0);
    I_Device.m_pImmediateContext->PSSetShader(pPS, NULL, 0);
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
    if (m_pVertexBuffer) m_pVertexBuffer->Release();
    if (m_pIndexBuffer) m_pIndexBuffer->Release();
    if (m_pVertexLayout) m_pVertexLayout->Release();
    return true;
}
HRESULT JShader::setInputLayout() {
    HRESULT hr;
    ID3DBlob* pVSCode = nullptr;
    hr = I_Shader.loadVSCode(pVSCode, m_wstrVSName, m_strVSFuncName);
    if (FAILED(hr)) return hr;

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
        pVSCode->GetBufferPointer(),
        pVSCode->GetBufferSize(),
        &m_pVertexLayout);

    return hr;
}