#include "StdAfx.h"
#include "DebugConsole.h"

namespace DebugConsole
{
    static streambuf* g_pCinBuf  = NULL;
    static streambuf* g_pCoutBuf = NULL;
    static streambuf* g_pCerrBuf = NULL;
    static ifstream   g_consoleCin;
    static ofstream   g_consoleCout;
    static ofstream   g_consoleCerr;

    void Open()
    {
        AllocConsole();
        AttachConsole(GetCurrentProcessId());
        g_pCinBuf = std::cin.rdbuf();
        g_consoleCin.open("CONIN$");
        std::cin.rdbuf(g_consoleCin.rdbuf());
        g_pCoutBuf = std::cout.rdbuf();
        g_consoleCout.open("CONOUT$");
        std::cout.rdbuf(g_consoleCout.rdbuf());
        g_pCerrBuf = std::cerr.rdbuf();
        g_consoleCerr.open("CONOUT$");
        std::cerr.rdbuf(g_consoleCerr.rdbuf());

        //for(INT bg=0; bg < 16; ++bg)
        //{
        //    for(INT fg=0; fg < 16; ++fg)
        //    {
        //        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bg << 4) | fg);
        //        std::cout << fg << " " << bg << std::endl;
        //    }
        //}
    }

    void Close()
    {
        std::cout << "Press ENTER..." << std::endl;
        std::cin.get();
        g_consoleCout.close();
        std::cout.rdbuf(g_pCoutBuf);
        g_consoleCin.close();
        std::cin.rdbuf(g_pCinBuf);
        g_consoleCerr.close();
        std::cerr.rdbuf(g_pCerrBuf);
        FreeConsole();
    }

    void Print(UINT color, LPCSTR str)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
        std::cout << str << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_DEFAULT);
    }


    VOID PrintError(LPCSTR str, LPCSTR file, INT line) 
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_RED);
        std::cout << file << "(" << line << ") : " << str << std::endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_DEFAULT);

    }


    VOID Print(UINT color, string str)
    {
        Print(color, str.c_str());
    }


    VOID PrintInfo(LPCSTR str)
    {
        Print(COLOR_DEFAULT, str);
    }


    VOID PrintInfo(string str)
    {
        Print(COLOR_DEFAULT, str);
    }


    VOID PrintWarning(LPCSTR str)
    {
        Print(COLOR_YELLOW, str);
    }  


    VOID PrintWarning(string str)
    {
        Print(COLOR_YELLOW, str);
    }


    VOID PrintError(string str, LPCSTR file, INT line)
    {
        PrintError(str.c_str(), file, line);
    }
}