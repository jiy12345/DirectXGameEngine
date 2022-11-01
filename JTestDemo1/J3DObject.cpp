#include "J3DObject.h"
#include "JConversionMatrix.h"

HRESULT J3DObject::CreateConstantBuffer()
{
    HRESULT hr;
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER) * 1;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &m_cbData;
    hr = I_Device.m_pd3dDevice->CreateBuffer(
        &bd,
        &sd,
        &m_pConstantBuffer);
    return hr;
}

void J3DObject::UpdateConstantBuffer()
{
    JMatrix<4, 4> mScale = JConversionMatrix<3>::Scale(m_cubeArea.m_vSize / 2);
    JMatrix<4, 4> mRotation = JConversionMatrix<3>::RotationX(DegreeToRadian(m_fXAngle)) *
                              JConversionMatrix<3>::RotationY(DegreeToRadian(m_fYAngle)) *
                              JConversionMatrix<3>::RotationZ(DegreeToRadian(m_fZAngle));
    JMatrix<4, 4> mTranslation = JConversionMatrix<3>::Translation(m_cubeArea.vCenter());
    m_matWorld = mScale * mRotation * mTranslation;
    m_matView = JConversionMatrix<3>::ViewLookAt();
    m_matProj = JConversionMatrix<3>::PerspectiveFovLH(1.0f, 1000.0f, T_PI * 0.25f,
        (float)I_Window.m_rtClient.right / (float)I_Window.m_rtClient.bottom);

    m_cbData.m_matWorld = transpose(m_matWorld);
    m_cbData.m_matView = transpose(m_matView);
    m_cbData.m_matProj = transpose(m_matProj);
    I_Device.m_pImmediateContext->UpdateSubresource(
        m_pConstantBuffer, 0, nullptr,
        &m_cbData, 0, 0);
}

bool J3DObject::init()
{
    JBaseObject::init();
    if (FAILED(CreateConstantBuffer()))
    {
        return false;
    }
    return true;
}

bool J3DObject::frame()
{
    JBaseObject::frame();

    return true;
}

bool J3DObject::render()
{
    UpdateConstantBuffer();
    I_Device.m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
    JBaseObject::preRender();

    JBaseObject::postRender();
    return true;
}

bool J3DObject::release()
{
    return false;
}

void J3DObject::setVertexData()
{

}
