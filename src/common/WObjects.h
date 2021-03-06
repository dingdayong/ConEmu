﻿
/*
Copyright (c) 2009-2015 Maximus5
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
3. The name of the authors may not be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#pragma once

#include <windows.h>
//#include <wchar.h>
#include "common.hpp"
//#include "MSecurity.h"
//#include "ConEmuCheck.h"
#include "CmdArg.h"


// GCC fixes
#ifndef KEY_WOW64_32KEY
#define KEY_WOW64_32KEY 0x0200
#endif
#ifndef KEY_WOW64_64KEY
#define KEY_WOW64_64KEY 0x0100
#endif

// WinAPI wrappers
void getWindowInfo(HWND ahWnd, wchar_t (&rsInfo)[1024], bool bProcessName = false, LPDWORD pnPID = NULL);

// Win console defines
typedef BOOL (WINAPI* AttachConsole_t)(DWORD dwProcessId);

// Some WinAPI related functions
bool FileExists(LPCWSTR asFilePath, DWORD* pnSize = NULL);
bool FileSearchInDir(LPCWSTR asFilePath, CmdArg& rsFound);
bool IsVsNetHostExe(LPCWSTR asFilePatName);
bool IsGDB(LPCWSTR asFilePatName);

typedef bool (*SearchAppPaths_t)(LPCWSTR asFilePath, CmdArg& rsFound, bool abSetPath, CmdArg* rpsPathRestore /*= NULL*/);
extern SearchAppPaths_t gfnSearchAppPaths /*= NULL*/;
bool FileExistsSearch(LPCWSTR asFilePath, CmdArg& rsFound, bool abSetPath = true, bool abRegSearch = true);

bool GetShortFileName(LPCWSTR asFullPath, int cchShortNameMax, wchar_t* rsShortName/*[MAX_PATH+1]-name only*/, BOOL abFavorLength=FALSE);
wchar_t* GetShortFileNameEx(LPCWSTR asLong, BOOL abFavorLength=TRUE);

bool IsDbcs();
bool IsHwFullScreenAvailable();
bool GetOsVersionInformational(OSVERSIONINFO* pOsVer);
bool IsWinVerOrHigher(WORD OsVer); // Ex: 0x0601, _WIN32_WINNT_WIN10, ...
bool IsWin2kEql();
bool IsWin5family();
bool IsWinXPSP1();
bool IsWin6();
bool IsWin7();
bool IsWin8();
bool IsWin10();
bool IsWindows64();
bool IsWine();
bool IsWinPE();
// Lower-cased to distinct from plugin's export
bool isTerminalMode();

typedef struct tagPROCESSENTRY32W PROCESSENTRY32W;
int  GetProcessBits(DWORD nPID, HANDLE hProcess = NULL);
bool GetProcessInfo(DWORD nPID, PROCESSENTRY32W* Info);

bool CheckCallbackPtr(HMODULE hModule, size_t ProcCount, FARPROC* CallBack, BOOL abCheckModuleInfo, BOOL abAllowNTDLL = FALSE, BOOL abTestVirtual = TRUE);
bool IsModuleValid(HMODULE module, BOOL abTestVirtual = TRUE);

wchar_t* ExpandMacroValues(LPCWSTR pszFormat, LPCWSTR* pszValues, size_t nValCount);
wchar_t* ExpandEnvStr(LPCWSTR pszCommand);

wchar_t* GetEnvVar(LPCWSTR VarName);
wchar_t* GetComspec(const ConEmuComspec* pOpt);
LPCWSTR GetComspecFromEnvVar(wchar_t* pszComspec, DWORD cchMax, ComSpecBits Bits = csb_SameOS);

bool IsExportEnvVarAllowed(LPCWSTR szName);
void ApplyExportEnvVar(LPCWSTR asEnvNameVal);

bool CoordInSmallRect(const COORD& cr, const SMALL_RECT& rc);

UINT GetCpFromString(LPCWSTR asString, LPCWSTR* ppszEnd = NULL);
