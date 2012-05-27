#pragma once
#include <iostream>
#include <streambuf>
#include <fstream>
#include <sstream>

namespace DebugConsole
{
    using std::ifstream;
    using std::ofstream;
    using std::streambuf;

#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_GRAY 7
#define COLOR_WHITE 15 
#define COLOR_GREEN 10
#define COLOR_RED 12
#define COLOR_YELLOW 14
#define COLOR_GRAY 7
#define COLOR_WHITE 15
#define COLOR_DEFAULT COLOR_GRAY

    VOID Open();
    VOID Close();
    VOID Print(UINT color, LPCSTR str);
    VOID Print(UINT color, string str);
    VOID PrintInfo(LPCSTR str);
    VOID PrintInfo(string str);
    VOID PrintWarning(LPCSTR str);
    VOID PrintWarning(string str);
    VOID PrintError(LPCSTR str, LPCSTR file, INT line);
    VOID PrintError(string str, LPCSTR file, INT line);
};
