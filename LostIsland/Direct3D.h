#pragma once

#define SWAP_CHAIN Direct3D::g_pSwapChain
#define DEVICE Direct3D::g_pDevice
#define CONTEXT Direct3D::g_pContext
#define DEFAULT_RTV Direct3D::g_pDefaultRTV

namespace Direct3D {

    extern IDXGISwapChain *g_pSwapChain;
    extern ID3D11Device *g_pDevice;
    extern ID3D11DeviceContext *g_pContext;
    extern ID3D11RenderTargetView *g_pDefaultRTV;

    HRESULT Create(HWND hWnd);
    VOID Destroy(VOID);
    VOID ActivateDefaultRTV(VOID);

}
