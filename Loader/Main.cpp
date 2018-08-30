#include "Main.h"

void SetColor(ConsoleColor text, ConsoleColor background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}

int main(int argc, char *argv[])
{
	SetConsoleTitle(charenc("NorAdrenaline Loader (hack.ovh) | Version: 3"));

	std::string protected_str = "/h4ck/NA/loader.php?hwid=";

	wstringstream HWID;

	HRESULT hres = CoInitializeEx(0, COINIT_MULTITHREADED);

	if (FAILED(hres))
	{
		cout << charenc("Failed to initialize COM library. Error code = 0x") << hex << hres << endl;
		return 1;                  // Program has failed.
	}

	hres = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);

	if (FAILED(hres))
	{
		cout << charenc("Failed to initialize security. Error code = 0x") << hex << hres << endl;
		CoUninitialize();
		return 1;                    // Program has failed.
	}

	IWbemLocator *pLoc = NULL;

	hres = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID *)&pLoc);

	if (FAILED(hres))
	{
		cout << charenc("Failed to create IWbemLocator object. Error code = 0x") << hex << hres << endl;
		CoUninitialize();
		return 1;                 // Program has failed.
	}

	IWbemServices *pSvc = NULL;

	hres = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), NULL, NULL, 0, NULL, 0, 0, &pSvc);

	if (FAILED(hres))
	{
		cout << charenc("Could not connect. Error code = 0x") << hex << hres << endl;
		pLoc->Release();
		CoUninitialize();
		return 1;                // Program has failed.
	}

	hres = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);

	if (FAILED(hres))
	{
		cout << charenc("Could not set proxy blanket. Error code = 0x") << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	IEnumWbemClassObject* pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t(charenc("WQL")), bstr_t(charenc("SELECT * FROM Win32_BaseBoard")), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	if (FAILED(hres))
	{
		cout << charenc("Query for baseboard failed. Error code = 0x") << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	IWbemClassObject *pclsObj = NULL;
	ULONG uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
			break;

		VARIANT vtProp;

		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		pclsObj->Release();
	}

	pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t(charenc("WQL")), bstr_t(charenc("SELECT * FROM Win32_BIOS")), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	if (FAILED(hres))
	{
		cout << charenc("Query for bios failed. Error code = 0x") << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	pclsObj = NULL;
	uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
			break;

		VARIANT vtProp;

		hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		pclsObj->Release();
	}

	pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t(charenc("WQL")), bstr_t(charenc("SELECT * FROM Win32_OperatingSystem")), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	if (FAILED(hres))
	{
		cout << charenc("Query for operating system failed. Error code = 0x") << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	pclsObj = NULL;
	uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
			break;

		VARIANT vtProp;

		hr = pclsObj->Get(L"InstallDate", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		pclsObj->Release();
	}

	pEnumerator = NULL;
	hres = pSvc->ExecQuery(bstr_t(charenc("WQL")), bstr_t(charenc("SELECT * FROM Win32_VideoController")), WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &pEnumerator);

	if (FAILED(hres))
	{
		cout << charenc("Query for video controller failed. Error code = 0x") << hex << hres << endl;
		pSvc->Release();
		pLoc->Release();
		CoUninitialize();
		return 1;               // Program has failed.
	}

	pclsObj = NULL;
	uReturn = 0;

	while (pEnumerator)
	{
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);

		if (0 == uReturn)
			break;

		VARIANT vtProp;

		hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
		HWID << vtProp.bstrVal << charenc(";");
		VariantClear(&vtProp);

		pclsObj->Release();
	}

	pSvc->Release();
	pLoc->Release();
	pEnumerator->Release();
	CoUninitialize();

	DWORD VolumeSerialNumber = 0;

	BOOL GetVolumeInformationFlag = GetVolumeInformationA(charenc("c:\\"), 0, 0, &VolumeSerialNumber, 0, 0, 0, 0);

	if (!GetVolumeInformationFlag)
	{
		cout << charenc("Query for volume failed. Error code = 0x") << endl;
		return 1;
	}

	HWID << VolumeSerialNumber << ";";

	std::wstring wide = HWID.str();
	std::string HashedHWID(wide.begin(), wide.end());

	HashedHWID = StringToHex(base64_encode(encryptDecrypt(HashedHWID)));

	std::cout << std::endl << charenc("Welcome! :3") << std::endl << std::endl;

	std::cout << charenc("HWID: ") << HashedHWID.c_str() << std::endl << std::endl;

	std::string url = protected_str + HashedHWID;

	std::cout << charenc("Join the server...") << std::endl;

	std::string respone = GetUrlData(url);

	if (strstr(respone.c_str(), charenc("true")))
	{
		size_t pos = respone.find(charenc("|"));
		if (!pos)
		{
			std::cout << charenc("It's impossible to get a date. (pos1)") << std::endl;
			return 1;
		}

		std::string date = respone.substr(pos + 1);

		size_t pos2 = date.find(charenc("|"));

		if (!pos2)
		{
			std::cout << charenc("It's impossible to get a date. (pos2)") << std::endl;
			return 1;
		}

		date = respone.substr(pos + 1, pos2);

		size_t pos3 = respone.find(charenc("|"));

		std::string key = respone.substr(pos3 + 1);

		pos3 = key.find(charenc("|"));

		key = key.substr(pos3 + 1);

		key = encryptDecrypt(base64_decode(key));

		std::cout << charenc("Checking key...") << std::endl;

		if (HashedHWID != key)
		{
			std::cout << charenc("Bad key.") << std::endl;
			return 1;
		}

		SetColor(Green, Black);

		std::cout << charenc("License before: ") << date << std::endl;

		SetColor(Cyan, Black);

		std::ifstream ifile(charenc("fixme"));

		if (!ifile.is_open())
		{
			std::cout << charenc("Using MD build.") << std::endl;

			url = protected_str + HashedHWID + "&dl=md";
		}
		else {
			std::cout << charenc("Using MT build.") << std::endl;

			url = protected_str + HashedHWID + "&dl=mt";

			ifile.close();
		}

		SetColor(White, Black);

		std::cout << charenc("Downloading latest update...") << std::endl;

		std::string contents = GetUrlData(url);

		contents = encryptDecrypt(base64_decode(contents));

		std::cout << charenc("Downloaded.") << std::endl;

		SetColor(LightMagenta, Black);

		if (argc == 1)
			std::cout << charenc("Looking for a process hl.exe...") << std::endl;
		else
			std::cout << charenc("Looking for a process ") << argv[1] << charenc("...") << std::endl;

		DWORD dwProcessId = 0;

		while (!dwProcessId)
		{
			if (argc == 1)
				dwProcessId = FindProcessId(charenc("hl.exe"));
			else
				dwProcessId = FindProcessId(argv[1]);

			Sleep(1000);
		}

		std::cout << charenc("Injecting to: ") << dwProcessId << charenc(".") << std::endl;

		HANDLE hModule = NULL;
		HANDLE hProcess = NULL;
		HANDLE hToken = NULL;
		LPVOID lpBuffer = NULL;
		DWORD dwLength = 0;
		DWORD dwBytesRead = 0;
		TOKEN_PRIVILEGES priv = { 0 };

		bool status = false;

		do
		{
			dwLength = contents.size();

			if (dwLength == INVALID_FILE_SIZE || dwLength == 0)
			{
				SetColor(Red, Black);
				std::cout << charenc("Failed to get the DLL file size.") << std::endl;
				break;
			}

			lpBuffer = (void*)contents.c_str();

			if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
			{
				priv.PrivilegeCount = 1;
				priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

				if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &priv.Privileges[0].Luid))
					AdjustTokenPrivileges(hToken, FALSE, &priv, 0, NULL, NULL);

				CloseHandle(hToken);
			}

			hProcess = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ, FALSE, dwProcessId);

			if (!hProcess)
			{
				SetColor(Red, Black);
				std::cout << charenc("Failed to open the target process.") << std::endl;
				break;
			}

			hModule = LoadRemoteLibraryR(hProcess, lpBuffer, dwLength, NULL);
			if (!hModule)
			{
				SetColor(Red, Black);
				std::cout << charenc("Failed to inject the DLL.") << std::endl;
				break;
			}

			status = true;

			WaitForSingleObject(hModule, -1);
		} while (0);

		if (hProcess)
			CloseHandle(hProcess);

		if (status)
		{
			std::cout << charenc("Successful injection.") << std::endl;
			return 0;   // Program successfully completed.
		}

		SetColor(White, Black);
	}
	else if (strstr(respone.c_str(), charenc("loader")))
	{
		SetColor(Yellow, Black);

		std::cout << charenc("Downloading new loader...") << std::endl;

		std::string loader = GetUrlData(strenc("/h4ck/NA/update_loader.suck"));

		std::cout << charenc("Downloaded...") << std::endl;

		std::ofstream out_file(charenc("LOADER_UPDATED_BRO.exe"));

		out_file << loader;

		out_file.close();

		SetColor(White, Black);
	}
	else {
		SetColor(Red, Black);
		std::cout << charenc("Server response: ") << respone << std::endl;
	}

	std::cout << std::endl << charenc("Press any button to continue...") << std::endl;
	std::cin.get();

	return 0;   // Program successfully completed.
}

std::string base64_encode(const std::string &in) 
{
	std::string out;

	int val = 0, valb = -6;
	for (unsigned char c : in) {
		val = (val << 8) + c;
		valb += 8;
		while (valb >= 0) {
			out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val >> valb) & 0x3F]);
			valb -= 6;
		}
	}
	if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val << 8) >> (valb + 8)) & 0x3F]);
	while (out.size() % 4) out.push_back('=');
	return out;
}

std::string base64_decode(const std::string &in) 
{
	std::string out;

	std::vector<int> T(256, -1);
	for (int i = 0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

	int val = 0, valb = -8;
	for (unsigned char c : in) {
		if (T[c] == -1) break;
		val = (val << 6) + T[c];
		valb += 6;
		if (valb >= 0) {
			out.push_back(char((val >> valb) & 0xFF));
			valb -= 8;
		}
	}
	return out;
}

string StringToHex(const string input)
{
	const char* lut = "0123456789ABCDEF";
	size_t len = input.length();
	string output = "";

	output.reserve(2 * len);

	for (size_t i = 0; i < len; i++)
	{
		const unsigned char c = input[i];
		output.push_back(lut[c >> 4]);
		output.push_back(lut[c & 15]);
	}

	return output;
}

std::string encryptDecrypt(std::string toEncrypt) 
{
	char key[] = { 'C','v','8','3','6','I','a','7','J','1','X','E','n','u','m','W','q','w','2','Z','V','h','t','5','k','b','w','W','6','7','S','5' }; //Any chars will work

	std::string output = toEncrypt;

	for (int i = 0; i < toEncrypt.size(); i++)
		output[i] = toEncrypt[i] ^ key[i % (sizeof(key) / sizeof(char))];

	return output;
}

string GetUrlData(string url)
{
	string request_data = "";

	HINTERNET hIntSession = InternetOpenA("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);

	if (!hIntSession)
		return request_data;

	HINTERNET hHttpSession = InternetConnectA(hIntSession, charenc("hack.ovh"), INTERNET_DEFAULT_HTTPS_PORT, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

	if (!hHttpSession)
		return request_data;

	HINTERNET hHttpRequest = HttpOpenRequestA(hHttpSession, "GET", url.c_str(), "HTTP/1.1", NULL, NULL, INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID, NULL);

	if (!hHttpSession)
		return request_data;

	char* szHeaders = "Content-Type: text/html\r\nUser-Agent: NorAdrenaline";
	char szRequest[1024] = { 0 };

	if (!HttpSendRequestA(hHttpRequest, szHeaders, strlen(szHeaders), szRequest, strlen(szRequest)))
		return request_data;

	CHAR szBuffer[1024] = { 0 };
	DWORD dwRead = 0;

	while (InternetReadFile(hHttpRequest, szBuffer, sizeof(szBuffer) - 1, &dwRead) && dwRead)
		request_data.append(szBuffer, dwRead);

	InternetCloseHandle(hHttpRequest);
	InternetCloseHandle(hHttpSession);
	InternetCloseHandle(hIntSession);

	return request_data;
}

DWORD FindProcessId(const std::string& processName)
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE)
		return 0;

	Process32First(processesSnapshot, &processInfo);
	if (!processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}


//===============================================================================================//
DWORD Rva2Offset(DWORD dwRva, UINT_PTR uiBaseAddress)
{
	WORD wIndex = 0;
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;
	PIMAGE_NT_HEADERS pNtHeaders = NULL;

	pNtHeaders = (PIMAGE_NT_HEADERS)(uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew);

	pSectionHeader = (PIMAGE_SECTION_HEADER)((UINT_PTR)(&pNtHeaders->OptionalHeader) + pNtHeaders->FileHeader.SizeOfOptionalHeader);

	if (dwRva < pSectionHeader[0].PointerToRawData)
		return dwRva;

	for (wIndex = 0; wIndex < pNtHeaders->FileHeader.NumberOfSections; wIndex++)
	{
		if (dwRva >= pSectionHeader[wIndex].VirtualAddress && dwRva < (pSectionHeader[wIndex].VirtualAddress + pSectionHeader[wIndex].SizeOfRawData))
			return (dwRva - pSectionHeader[wIndex].VirtualAddress + pSectionHeader[wIndex].PointerToRawData);
	}

	return 0;
}
//===============================================================================================//
DWORD GetReflectiveLoaderOffset(VOID * lpReflectiveDllBuffer)
{
	UINT_PTR uiBaseAddress = 0;
	UINT_PTR uiExportDir = 0;
	UINT_PTR uiNameArray = 0;
	UINT_PTR uiAddressArray = 0;
	UINT_PTR uiNameOrdinals = 0;
	DWORD dwCounter = 0;
#ifdef WIN_X64
	DWORD dwCompiledArch = 2;
#else
	// This will catch Win32 and WinRT.
	DWORD dwCompiledArch = 1;
#endif

	uiBaseAddress = (UINT_PTR)lpReflectiveDllBuffer;

	// get the File Offset of the modules NT Header
	uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

	// currenlty we can only process a PE file which is the same type as the one this fuction has  
	// been compiled as, due to various offset in the PE structures being defined at compile time.
	if (((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.Magic == 0x010B) // PE32
	{
		if (dwCompiledArch != 1)
			return 0;
	}
	else if (((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.Magic == 0x020B) // PE64
	{
		if (dwCompiledArch != 2)
			return 0;
	}
	else
	{
		return 0;
	}

	// uiNameArray = the address of the modules export directory entry
	uiNameArray = (UINT_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

	// get the File Offset of the export directory
	uiExportDir = uiBaseAddress + Rva2Offset(((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress, uiBaseAddress);

	// get the File Offset for the array of name pointers
	uiNameArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNames, uiBaseAddress);

	// get the File Offset for the array of addresses
	uiAddressArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions, uiBaseAddress);

	// get the File Offset for the array of name ordinals
	uiNameOrdinals = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNameOrdinals, uiBaseAddress);

	// get a counter for the number of exported functions...
	dwCounter = ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->NumberOfNames;

	// loop through all the exported functions to find the ReflectiveLoader
	while (dwCounter--)
	{
		char * cpExportedFunctionName = (char *)(uiBaseAddress + Rva2Offset(DEREF_32(uiNameArray), uiBaseAddress));

		if (strstr(cpExportedFunctionName, "ReflectiveLoader") != NULL)
		{
			// get the File Offset for the array of addresses
			uiAddressArray = uiBaseAddress + Rva2Offset(((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions, uiBaseAddress);

			// use the functions name ordinal as an index into the array of name pointers
			uiAddressArray += (DEREF_16(uiNameOrdinals) * sizeof(DWORD));

			// return the File Offset to the ReflectiveLoader() functions code...
			return Rva2Offset(DEREF_32(uiAddressArray), uiBaseAddress);
		}
		// get the next exported function name
		uiNameArray += sizeof(DWORD);

		// get the next exported function name ordinal
		uiNameOrdinals += sizeof(WORD);
	}

	return 0;
}
//===============================================================================================//
// Loads a DLL image from memory via its exported ReflectiveLoader function
HMODULE WINAPI LoadLibraryR(LPVOID lpBuffer, DWORD dwLength)
{
	HMODULE hResult = NULL;
	DWORD dwReflectiveLoaderOffset = 0;
	DWORD dwOldProtect1 = 0;
	DWORD dwOldProtect2 = 0;
	REFLECTIVELOADER pReflectiveLoader = NULL;
	DLLMAIN pDllMain = NULL;

	if (lpBuffer == NULL || dwLength == 0)
		return NULL;

	__try
	{
		// check if the library has a ReflectiveLoader...
		dwReflectiveLoaderOffset = GetReflectiveLoaderOffset(lpBuffer);
		if (dwReflectiveLoaderOffset != 0)
		{
			pReflectiveLoader = (REFLECTIVELOADER)((UINT_PTR)lpBuffer + dwReflectiveLoaderOffset);

			// we must VirtualProtect the buffer to RWX so we can execute the ReflectiveLoader...
			// this assumes lpBuffer is the base address of the region of pages and dwLength the size of the region
			if (VirtualProtect(lpBuffer, dwLength, PAGE_EXECUTE_READWRITE, &dwOldProtect1))
			{
				// call the librarys ReflectiveLoader...
				pDllMain = (DLLMAIN)pReflectiveLoader();
				if (pDllMain != NULL)
				{
					// call the loaded librarys DllMain to get its HMODULE
					if (!pDllMain(NULL, DLL_QUERY_HMODULE, &hResult))
						hResult = NULL;
				}
				// revert to the previous protection flags...
				VirtualProtect(lpBuffer, dwLength, dwOldProtect1, &dwOldProtect2);
			}
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		hResult = NULL;
	}

	return hResult;
}
//===============================================================================================//
// Loads a PE image from memory into the address space of a host process via the image's exported ReflectiveLoader function
// Note: You must compile whatever you are injecting with REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR 
//       defined in order to use the correct RDI prototypes.
// Note: The hProcess handle must have these access rights: PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | 
//       PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_VM_READ
// Note: If you are passing in an lpParameter value, if it is a pointer, remember it is for a different address space.
// Note: This function currently cant inject accross architectures, but only to architectures which are the 
//       same as the arch this function is compiled as, e.g. x86->x86 and x64->x64 but not x64->x86 or x86->x64.
HANDLE WINAPI LoadRemoteLibraryR(HANDLE hProcess, LPVOID lpBuffer, DWORD dwLength, LPVOID lpParameter)
{
	BOOL bSuccess = FALSE;
	LPVOID lpRemoteLibraryBuffer = NULL;
	LPTHREAD_START_ROUTINE lpReflectiveLoader = NULL;
	HANDLE hThread = NULL;
	DWORD dwReflectiveLoaderOffset = 0;
	DWORD dwThreadId = 0;

	__try
	{
		do
		{
			if (!hProcess || !lpBuffer || !dwLength)
				break;

			// check if the library has a ReflectiveLoader...
			dwReflectiveLoaderOffset = GetReflectiveLoaderOffset(lpBuffer);
			if (!dwReflectiveLoaderOffset)
				break;

			// alloc memory (RWX) in the host process for the image...
			lpRemoteLibraryBuffer = VirtualAllocEx(hProcess, NULL, dwLength, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (!lpRemoteLibraryBuffer)
				break;

			// write the image into the host process...
			if (!WriteProcessMemory(hProcess, lpRemoteLibraryBuffer, lpBuffer, dwLength, NULL))
				break;

			// add the offset to ReflectiveLoader() to the remote library address...
			lpReflectiveLoader = (LPTHREAD_START_ROUTINE)((ULONG_PTR)lpRemoteLibraryBuffer + dwReflectiveLoaderOffset);

			// create a remote thread in the host process to call the ReflectiveLoader!
			hThread = CreateRemoteThread(hProcess, NULL, 1024 * 1024, lpReflectiveLoader, lpParameter, (DWORD)NULL, &dwThreadId);

		} while (0);

	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		hThread = NULL;
	}

	return hThread;
}
//===============================================================================================//