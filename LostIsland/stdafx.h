// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
#define _CRTDBG_MAP_ALLOC               // debug memory leaks

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <crtdbg.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#ifdef _DEBUG
#define GCC_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new GCC_NEW
#endif

// TODO: reference additional headers your program requires here
#include <d3d11.h>
#include <D3DX11.h>
#include <xnamath.h>
#include <memory>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

extern BOOL g_bContinue;

// defines
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SAFE_RELEASE(_resource) { if((_resource) != NULL) { (_resource)->Release(); (_resource) = NULL; } }
#define SAFE_DELETE(_ptr) { if((_ptr) != NULL) { delete (_ptr); (_ptr) = NULL; } }
#define RETURN_IF_FAILED(_hr, _errorMsg) { if(FAILED(_hr)) return hr; } // TODO: output message
#define shared_ptr std::tr1::shared_ptr;
#define weak_ptr std::tr1::weak_ptr;