
#include <windows.h>
#include <winternl.h>
#include <iostream>


#include "apihook.h"
//#include "api.h"
#include "str.h"


#define dll(name) return (PCHAR)Commond::name

ApiHelper::ApiHelper()
{

}

ApiHelper::~ApiHelper()
{

}


//************************************
// Method:    _peb
// FullName:  ApiHelper::_peb
// Access:    public static 
// Returns:   void*
// Qualifier:
//************************************
void* ApiHelper::_peb()
{
#ifdef _M_IX86 
	return (void*)__readfsdword(0x30);
#elif defined(_M_AMD64)
	return (void*)__readfsdword(0x60);
#endif
}


//************************************
// Method:    GetModuleBaseAddress
// FullName:  ApiHelper::GetModuleBaseAddress
// Access:    public static 
// Returns:   HMODULE
// Qualifier:
// Parameter: DWORD hash
//************************************
HMODULE ApiHelper::GetModuleBaseAddress(DWORD hash)
{
	PEB *peb = (PPEB)_peb();
	LDR_DATA_TABLE_ENTRY *LrdDataTableEntry = (PLDR_DATA_TABLE_ENTRY)peb->Ldr->InMemoryOrderModuleList.Flink;
	LIST_ENTRY *listEntry = peb->Ldr->InMemoryOrderModuleList.Flink;
	do
	{
		DWORD tempHash = toolsSrtW::makeHash(LrdDataTableEntry->FullDllName.Buffer, true);
		if (tempHash == hash)
		{
			return (HMODULE)LrdDataTableEntry->Reserved2[0];
		}

		listEntry = listEntry->Flink;
		LrdDataTableEntry = (PLDR_DATA_TABLE_ENTRY)(listEntry->Flink);


	} while (listEntry != peb->Ldr->InMemoryOrderModuleList.Flink);
	return 0;

}

char* ApiHelper::getDllName(int id)
{

	switch (id)
	{
	case Commond::_kernel32:		dll(kernel32_);
	case Commond::_advapi32:		dll(advapi32_);
	case Commond::_user32:			dll(user32_);
	}
	return NULL;
}

DWORD ApiHelper::GetFunctionAddress(HMODULE module, DWORD FuncHash)
{
	if (module == NULL) { return NULL; }

	DWORD ImageBase = (DWORD)module;
	PIMAGE_DOS_HEADER pDosHeader = (PIMAGE_DOS_HEADER)ImageBase;
	if (pDosHeader->e_magic != IMAGE_DOS_SIGNATURE) { return NULL; }

	PIMAGE_NT_HEADERS pNTHeader = (PIMAGE_NT_HEADERS)(ImageBase + pDosHeader->e_lfanew);
	DWORD RVAExports = pNTHeader->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;
	if (RVAExports == 0) { return NULL; }

	IMAGE_EXPORT_DIRECTORY *pExportDirectory = (IMAGE_EXPORT_DIRECTORY *)(ImageBase + RVAExports);
	DWORD *RVANames = (DWORD*)(ImageBase + pExportDirectory->AddressOfNames);
	WORD *RVANameOrdinals = (WORD*)(ImageBase + pExportDirectory->AddressOfNameOrdinals);
	DWORD *RVAFunctions = (DWORD*)(ImageBase + pExportDirectory->AddressOfFunctions);
	for (DWORD i = 0; i < pExportDirectory->NumberOfFunctions; ++i) {
		char *pName = (char*)(ImageBase + RVANames[i]);
		char tempName[MAX_PATH]; // fixme (temporal name of function since  got error  +Error reading string data+)
		stringA::copy(tempName, pName, sizeof(tempName)); //copy the name of  function to tempName (because *pName is pointer can't make lower case)
		DWORD currentHash = toolsSrtA::makeHash(tempName, true); // convert function name to hash
		if (currentHash == FuncHash)
		{
			std::cout << "Function name: " << tempName << " Hash: 0x" << std::hex << currentHash << " \n";
			DWORD functionAdress = ((DWORD)ImageBase + RVAFunctions[RVANameOrdinals[i]]);
			return functionAdress;
		}

	}

	return NULL;
}


void * ApiHelper::getProcAddressEx(DWORD dwModule, DWORD dwProcNameHash)
{
	HMODULE moduleHandle = NULL;
	PCHAR dllname = NULL;
	DWORD returFunciton;

	if (dwModule == Commond::_kernel32) moduleHandle = GetModuleBaseAddress(Commond::kernel32Hash);

	if (moduleHandle == NULL &&  dllname == NULL)
	{
		dllname = getDllName(dwModule);
		//std::cout << dllname;
	}

	if (moduleHandle == NULL &&  dllname != NULL)
	{
		moduleHandle = (HMODULE)_LoadLibraryA(dllname);

	}

	if (moduleHandle != NULL)
	{
		returFunciton = (DWORD)GetFunctionAddress(moduleHandle, dwProcNameHash);
	}


	return (LPVOID)returFunciton;
}
