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
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include <memory>
#include <vector>
#include <list>
#include <hash_map>
#include <string>
using std::tr1::shared_ptr;
using std::tr1::weak_ptr;
using std::wstring;
using std::string;
using std::vector;
using std::hash_map;
using std::list;

#include "DebugConsole.h"
using DebugConsole::PrintInfo;
using DebugConsole::PrintWarning;
using DebugConsole::PrintError;
#include "FastDelegate.h"
#include "FastDelegateBind.h"

typedef unsigned long EventType;

extern BOOL g_continue; // TODO (nico3000): into GameLogic

// defines
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SAFE_RELEASE(_resource){ if((_resource) != NULL) { (_resource)->Release(); (_resource) = NULL; } }
#define SAFE_DELETE(_ptr) { if((_ptr) != NULL) { delete (_ptr); (_ptr) = NULL; } }
#define RETURN_IF_FAILED(_hr, _errorMsg) { if(FAILED(_hr)) { ERROR(_errorMsg); return hr; } } // TODO (nico3000): output message
#define ERROR(_msg) { PrintError(_msg, __FILE__, __LINE__); }
