#include <iostream>
#include <stdarg.h>
#include <windows.h>

#include "LoggerWin32.hpp"
#include "common/Util.hpp"

void LoggerWin32::print(eLogLevel ll, const char* const str)
{
    Logger::print(ll, str);

    HANDLE handle;
    handle = GetStdHandle(STD_OUTPUT_HANDLE);

    // message colors
    switch (ll)
    {
    default:
    case LOG_INFO:
        SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    case LOG_WARN:
        SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN);
    case LOG_ERR:
        SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);
    }

    // wellp, this sucks, but it's fine
    OutputDebugStringA(GetTag(ll));
    OutputDebugStringA(str);
    OutputDebugStringA("\n");

    // reset to normal after printing
    SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void LoggerWin32::print(eLogLevel ll, std::string str)
{
    print(ll, str.c_str());
}

void LoggerWin32::vprintf(eLogLevel ll, const char* const fmt, va_list argPtr)
{
    print(ll, Util::vformat(fmt, argPtr));
}

void LoggerWin32::printf(eLogLevel ll, const char* const fmt, ...)
{
    va_list argList;
    va_start(argList, fmt);

    vprintf(ll, fmt, argList);

    va_end(argList);
}