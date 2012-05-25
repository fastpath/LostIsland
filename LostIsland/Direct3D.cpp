#include "StdAfx.h"
#include "Direct3D.h"

IDXGISwapChain *Direct3D::g_pSwapChain = NULL;
ID3D11Device *Direct3D::g_pDevice = NULL;
ID3D11DeviceContext *Direct3D::g_pContext = NULL;
ID3D11RenderTargetView *Direct3D::g_pDefaultRTV = NULL;

HRESULT Direct3D::create(HWND hWnd) {
    DXGI_SWAP_CHAIN_DESC scDesc;
    ZeroMemory(&scDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    scDesc.BufferDesc.Width = SCREEN_WIDTH;
    scDesc.BufferDesc.Height = SCREEN_HEIGHT;
    scDesc.BufferDesc.RefreshRate.Numerator = 1;
    scDesc.BufferDesc.RefreshRate.Denominator = 1;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.OutputWindow = hWnd;
    scDesc.SampleDesc.Count = 1;
    scDesc.SampleDesc.Quality = 0;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.Windowed = TRUE;

    UINT flags = 0;
#ifdef _DEBUG
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    D3D_FEATURE_LEVEL pLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    D3D_FEATURE_LEVEL level;
    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL,
                                               D3D_DRIVER_TYPE_HARDWARE,
                                               NULL,                                  
                                               flags,
                                               pLevels,
                                               ARRAYSIZE(pLevels),
                                               D3D11_SDK_VERSION,
                                               &scDesc,
                                               &g_pSwapChain,
                                               &g_pDevice,
                                               &level,
                                               &g_pContext);
    RETURN_IF_FAILED(hr, "D3D11CreateDeviceAndSwapChain() failed");

    ID3D11Texture2D *pBufferTexture;
    g_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (VOID**)&pBufferTexture);
    hr = g_pDevice->CreateRenderTargetView(pBufferTexture, NULL, &g_pDefaultRTV);
    SAFE_RELEASE(pBufferTexture);
    RETURN_IF_FAILED(hr, "CreateRenderTargetView() failed");
    
    return hr;
}


VOID Direct3D::destroy(VOID) {
    SAFE_RELEASE(g_pDefaultRTV);
    SAFE_RELEASE(g_pContext);
    SAFE_RELEASE(g_pDevice);
    SAFE_RELEASE(g_pSwapChain);
}


VOID Direct3D::activateDefaultRTV(VOID) {
    g_pContext->OMSetRenderTargets(1, &g_pDefaultRTV, NULL);
}
