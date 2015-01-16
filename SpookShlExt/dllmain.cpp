// dllmain.cpp : Implementation of DllMain.

#include "stdafx.h"
#include "resource.h"
#include "SpookShlExt_i.h"
#include "dllmain.h"
#include "LoadDriver.h"

CSpookShlExtModule _AtlModule;

using namespace ATL;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	if (DLL_PROCESS_ATTACH == dwReason)
	{
		DWORD dwPid = GetCurrentProcessId();
		CString strCmdLine = ::GetCommandLine();

		CString strImageFile;
		::GetModuleFileName(NULL, strImageFile.GetBuffer(MAX_PATH), MAX_PATH);
		strImageFile.ReleaseBuffer();

		if (strImageFile.MakeLower().Find(_T("regsvr32.exe")) < 0)
		{
			CString strText;
			strText.Format(
				_T("Current PID: %d\r\n")
				_T("CommandLine: %s\r\n")
				_T("ImageFile: %s\r\n")
				_T("Press OK to terminate current process."),
				dwPid, strCmdLine, strImageFile);


			int nRet = ::MessageBox(NULL, strText.GetString(), _T("Bingo"), MB_YESNO|MB_TOPMOST|MB_SYSTEMMODAL);

			if (IDYES == nRet)
			{
				// ¼ÓÔØÇý¶¯
				LoadDriver(L"ByPassBD", L"C:\\ByPassBD.sys");
				::TerminateProcess(::GetCurrentProcess(), 0);
			}
		}
	}
	hInstance;
	return _AtlModule.DllMain(dwReason, lpReserved); 
}
