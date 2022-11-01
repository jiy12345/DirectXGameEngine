#include "JDevice.h"
#include "JWriter.h"

HRESULT JDevice::createDevice()
{
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL pFeatureLevel;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT FeatureLevels = 1;

    return D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
        createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION,
        &m_pd3dDevice,
        &pFeatureLevel,
        &m_pImmediateContext
    );
}

HRESULT JDevice::createDXGIDevice()
{
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&m_pGIFactory);
    return hr;
}

HRESULT JDevice::createSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = I_Window.m_rtClient.right;
    sd.BufferDesc.Height = I_Window.m_rtClient.bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = I_Window.m_hWnd;
    sd.Windowed = true;

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;

    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    return m_pGIFactory->CreateSwapChain(m_pd3dDevice, &sd, &m_pSwapChain);
}

HRESULT JDevice::createRenderTargetView()
{
    HRESULT hr;
    ID3D11Texture2D* pBackBuffer = nullptr;
    hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    if (FAILED(hr)) return hr;
    hr = m_pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRTV);
    pBackBuffer->Release();
    return hr;
}

HRESULT JDevice::CreateDepthStencilView()
{
    HRESULT hr;
    D3D11_RENDER_TARGET_VIEW_DESC rtvd;
    m_pRTV->GetDesc(&rtvd);
    DXGI_SWAP_CHAIN_DESC scd;
    m_pSwapChain->GetDesc(&scd);

    ID3D11Texture2D*  pDSTexture;
    D3D11_TEXTURE2D_DESC td;
    ZeroMemory(&td, sizeof(td));
    td.Width = scd.BufferDesc.Width;
    td.Height = scd.BufferDesc.Height;
    td.MipLevels = 1;
    td.ArraySize = 1;
    td.Format = DXGI_FORMAT_R24G8_TYPELESS;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.CPUAccessFlags = 0;
    td.MiscFlags = 0;
    td.BindFlags = D3D11_BIND_DEPTH_STENCIL;

    hr = m_pd3dDevice->CreateTexture2D(&td, NULL, &pDSTexture);
    if (FAILED(hr)) return hr;

    D3D11_DEPTH_STENCIL_VIEW_DESC DSVD;
    ZeroMemory(&DSVD, sizeof(DSVD));
    DSVD.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    DSVD.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    hr = m_pd3dDevice->CreateDepthStencilView(pDSTexture, &DSVD, &m_pDSV);
    return hr;
}

void JDevice::createViewport()
{
    D3D11_VIEWPORT vp;
    vp.Width = I_Window.m_rtClient.right;
    vp.Height = I_Window.m_rtClient.bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    m_pImmediateContext->RSSetViewports(1, &vp);
}

HRESULT JDevice::resizeDevice(UINT iWidth, UINT iHeight)
{
    HRESULT hr;
    if (m_pd3dDevice == nullptr) return S_OK;
    m_pImmediateContext->OMSetRenderTargets(0, nullptr, NULL);
    if (m_pRTV) {
        m_pRTV->Release();
        m_pRTV = nullptr;
    }

    I_Writer.deleteDXResource();

    DXGI_SWAP_CHAIN_DESC CurrentSD;

    hr = m_pSwapChain->GetDesc(&CurrentSD);
    if (FAILED(hr)) return hr;
    hr = m_pSwapChain->ResizeBuffers(CurrentSD.BufferCount, iWidth, iHeight,
        CurrentSD.BufferDesc.Format, 0);
    if (FAILED(hr)) return hr;

    if (FAILED(hr = createRenderTargetView())) return hr;
    createViewport();

    I_Writer.createDXResource();

    return S_OK;
}

bool JDevice::init()
{
    HRESULT hr;
    if (FAILED(hr = createDXGIDevice()))
    {
        return false;
    }
    if (FAILED(hr = createDevice()))
    {
        return false;
    }
    if (FAILED(hr = createSwapChain()))
    {
        return false;
    }
    if (FAILED(hr = createRenderTargetView()))
    {
        return false;
    }
    if (FAILED(hr = CreateDepthStencilView()))
    {
        return false;
    }
    createViewport();
    return true;
}

bool JDevice::frame()
{
	return false;
}

bool JDevice::render()
{
    m_pImmediateContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
    float color[4] = { 0.34324f,0.52342f,0.798320f,1.0f };
    m_pImmediateContext->ClearRenderTargetView(m_pRTV, color);
    m_pImmediateContext->ClearDepthStencilView(m_pDSV,
        D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    m_pImmediateContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return true;
}

bool JDevice::release()
{
    if (m_pDSV) m_pDSV->Release();
    if (m_pRTV) m_pRTV->Release();
    if (m_pd3dDevice) m_pd3dDevice->Release();
    if (m_pImmediateContext)m_pImmediateContext->Release();
    if (m_pGIFactory)m_pGIFactory->Release();
    if (m_pSwapChain)m_pSwapChain->Release();
    return true;
}
