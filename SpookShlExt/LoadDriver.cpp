// LoadDriver.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "LoadDriver.h"

typedef struct _LSA_UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PVOID Buffer;
} UNICODE_STRING, *PUNICODE_STRING; 

// 声明ntdll中使用的函数
typedef DWORD (CALLBACK* RTLINITUNICODESTRING)(PVOID, PVOID);
RTLINITUNICODESTRING RtlInitUnicodeString;
typedef DWORD (CALLBACK* RTLFREEUNICODESTRING)(PVOID);
RTLFREEUNICODESTRING RtlFreeUnicodeString;
typedef DWORD (CALLBACK* ZWLOADDRIVER)(PVOID);
ZWLOADDRIVER ZwLoadDriver;

BOOL AdjustProcessTokenPrivilege();

BOOL LoadDriver(LPCWSTR lpDrvName, LPCWSTR lpImagePath)
{
	//添加加载驱动程序所必需的注册表信息
	TCHAR szSubKey[200];
	TCHAR szDrvFullPath[256];
	UNICODE_STRING uStr;
	HKEY hkResult = NULL;
	DWORD Data = 0x0001;
	DWORD dwRet = 0;
	BOOL bRet = FALSE;

	if (!AdjustProcessTokenPrivilege())
	{
		//MessageBox(NULL, TEXT("提权失败"), TEXT("提示"), MB_OK);
		return FALSE;
	}

	RtlInitUnicodeString = (RTLINITUNICODESTRING)
		GetProcAddress(GetModuleHandle(TEXT("NTDLL.DLL")), "RtlInitUnicodeString");
	RtlFreeUnicodeString = (RTLFREEUNICODESTRING)
		GetProcAddress(GetModuleHandle(TEXT("NTDLL.DLL")), "RtlFreeUnicodeString");
	ZwLoadDriver = (ZWLOADDRIVER)
		GetProcAddress(GetModuleHandle(TEXT("NTDLL.DLL")), "ZwLoadDriver");

	swprintf(szSubKey, 200, TEXT("System\\CurrentControlSet\\Services\\%s"), lpDrvName);

	dwRet = RegCreateKey(HKEY_LOCAL_MACHINE, szSubKey, &hkResult);
	if(dwRet != ERROR_SUCCESS)
		return false;

	dwRet = RegSetValueEx(hkResult, TEXT("Type"), 0, 
		REG_DWORD, (PBYTE)&Data, sizeof(DWORD));
	dwRet = RegSetValueEx(hkResult, TEXT("ErrorControl"), 0, 
		REG_DWORD, (PBYTE)&Data, sizeof(DWORD));
	dwRet = RegSetValueEx(hkResult, TEXT("Start"), 0, 
		REG_DWORD, (PBYTE)&Data, sizeof(DWORD));

	GetFullPathName(lpImagePath, 256, szDrvFullPath, NULL);   

	dwRet = swprintf(szSubKey, 256, TEXT("\\??\\%s"), szDrvFullPath);
	dwRet = RegSetValueEx(hkResult, TEXT("ImagePath"), 0, 
		REG_SZ, (PBYTE)szSubKey, (dwRet+1)*sizeof(WCHAR));
	RegCloseKey(hkResult); 

	swprintf(szSubKey, 200, TEXT("\\Registry\\Machine\\System\\CurrentControlSet\\Services\\%s"), lpDrvName);

	RtlInitUnicodeString(&uStr, szSubKey);
	//加载驱动程序
	dwRet = ZwLoadDriver(&uStr);
	if ((dwRet == 0x0L) || (dwRet == 0xc000010eL) || (dwRet == 0xC0000035L)) //STATUS_SUCCESS  STATUS_IMAGE_ALREADY_LOADED STATUS_OBJECT_NAME_COLLISION
	{
		//MessageBox(NULL, TEXT("加载驱动成功"), TEXT("提示"), MB_OK);
		bRet = TRUE;
	}
	else
	{
		//MessageBox(NULL, TEXT("加载驱动失败"), TEXT("提示"), MB_OK);
		bRet = FALSE;
	}

	//删除注册表项
	//swprintf(szSubKey, TEXT("%s%s\\Enum"), TEXT("System\\CurrentControlSet\\Services\\") ,lpDrvName);
	//RegDeleteKey(HKEY_LOCAL_MACHINE,szSubKey);

	//swprintf(szSubKey, TEXT("%s%s\\Security"), TEXT("System\\CurrentControlSet\\Services\\"), lpDrvName);
	//RegDeleteKey(HKEY_LOCAL_MACHINE,szSubKey);

	//swprintf(szSubKey, TEXT("%s%s"), TEXT("System\\CurrentControlSet\\Services\\") ,lpDrvName);
	//RegDeleteKey(HKEY_LOCAL_MACHINE,szSubKey);

	return bRet;
}

BOOL AdjustProcessTokenPrivilege()
{
	LUID Luid;
	TOKEN_PRIVILEGES tp;
	HANDLE hToken;
	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken))
	{
		return FALSE;
	}

	if (!LookupPrivilegeValue(NULL, SE_LOAD_DRIVER_NAME, &Luid) )
	{
		return FALSE;
	}

	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = Luid;
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	

	if (!AdjustTokenPrivileges(hToken, 0, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL))
	{
		return FALSE;
	}

	return TRUE;
}

//BOOL InitDeviceDriver(LPCTSTR lpImagePath, LPCTSTR lpServiceName)
//{
//	SC_HANDLE hSCM = NULL;
//	SC_HANDLE hService = NULL;
//	DWORD ec = 0;
//
//	if ((hSCM = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)) == NULL)
//	{
//		AtlTrace(TEXT("Failed at OpenSCManager\n"));
//		return FALSE;
//	}
//
//	hService = CreateService(hSCM,
//		lpServiceName,
//		lpServiceName,
//		GENERIC_EXECUTE,
//		SERVICE_KERNEL_DRIVER,
//		SERVICE_SYSTEM_START,
//		SERVICE_ERROR_IGNORE,
//		lpImagePath,
//		NULL,
//		NULL,
//		NULL,
//		NULL,
//		NULL);
//
//	if (hService == NULL)
//	{
//		ec = GetLastError();
//		switch(ec)
//		{
//		case ERROR_SERVICE_EXISTS:
//			AtlTrace(TEXT("Service already exsit!\n"));
//			hService = OpenService(hSCM, 
//				lpServiceName,
//				GENERIC_EXECUTE | GENERIC_ALL);
//			break;
//		default:
//			AtlTrace(TEXT("CreateService Failed!\n"));
//			CloseServiceHandle(hSCM);
//			return FALSE;
//		}
//	}
//	CloseServiceHandle(hSCM);
//
//	if (hService == NULL)
//	{
//		AtlTrace(TEXT("Service already exsit but failed to open it!\n"));
//		return FALSE;
//	}
//
//	::StartService(hService, 0, NULL);
//	ec = GetLastError();
//	if ((ec != ERROR_SUCCESS) && (ec != ERROR_SERVICE_ALREADY_RUNNING))
//	{
//		AtlTrace(TEXT("Service already exsit and opend but failed to start it!\n"));
//		return FALSE;
//	}
//
//	CloseServiceHandle(hService);
//	return TRUE;
//}
//
//BOOL UnLoadDeviceService(LPCTSTR lpServiceName)
//{
//	SC_HANDLE hSCM = NULL;
//	SC_HANDLE hService = NULL;
//	DWORD ec = 0;
//
//	if ((hSCM = OpenSCManager(NULL,NULL,SC_MANAGER_ALL_ACCESS)) == NULL)
//	{
//		AtlTrace(TEXT("Failed at OpenSCManager\n"));
//		return FALSE;
//	}
//
//	hService = OpenService(hSCM, 
//		lpServiceName,
//		GENERIC_EXECUTE | GENERIC_ALL);
//	CloseServiceHandle(hSCM);
//
//	if (hService == NULL)
//	{
//		AtlTrace(TEXT("Open service failed!\n"));
//		return FALSE;
//	}
//	
//	SERVICE_STATUS ss;
//	::ControlService(hService, SERVICE_CONTROL_STOP, &ss);
//	ec = GetLastError();
//	if (ec != ERROR_SUCCESS && ec != ERROR_SERVICE_NOT_ACTIVE)
//	{
//		AtlTrace(TEXT("Failed to stop the service!\n"));
//	}
//
//	BOOL bRet = ::DeleteService(hService);
//
//	CloseServiceHandle(hService);
//	return bRet;
//}