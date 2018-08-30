#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <comdef.h>
#include <Wbemidl.h>
#include <vector>
#include "Wininet.h"
#include <tlhelp32.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib,"Wininet.lib")

#include "strenc.h"

using namespace std;

std::string base64_encode(const std::string &in);
std::string base64_decode(const std::string &in);
std::string encryptDecrypt(std::string toEncrypt);
string StringToHex(const string input);

DWORD FindProcessId(const std::string& processName);
string GetUrlData(string url);

enum ConsoleColor {
	Black = 0,
	Blue = 1,
	Green = 2,
	Cyan = 3,
	Red = 4,
	Magenta = 5,
	Brown = 6,
	LightGray = 7,
	DarkGray = 8,
	LightBlue = 9,
	LightGreen = 10,
	LightCyan = 11,
	LightRed = 12,
	LightMagenta = 13,
	Yellow = 14,
	White = 15
};

#define DLL_METASPLOIT_ATTACH	4
#define DLL_METASPLOIT_DETACH	5
#define DLL_QUERY_HMODULE		6

#define DEREF( name )*(UINT_PTR *)(name)
#define DEREF_64( name )*(DWORD64 *)(name)
#define DEREF_32( name )*(DWORD *)(name)
#define DEREF_16( name )*(WORD *)(name)
#define DEREF_8( name )*(BYTE *)(name)

typedef ULONG_PTR(WINAPI * REFLECTIVELOADER)(VOID);
typedef BOOL(WINAPI * DLLMAIN)(HINSTANCE, DWORD, LPVOID);

#define DLLEXPORT __declspec( dllexport ) 

DWORD GetReflectiveLoaderOffset(VOID * lpReflectiveDllBuffer);

HMODULE WINAPI LoadLibraryR(LPVOID lpBuffer, DWORD dwLength);

HANDLE WINAPI LoadRemoteLibraryR(HANDLE hProcess, LPVOID lpBuffer, DWORD dwLength, LPVOID lpParameter);
