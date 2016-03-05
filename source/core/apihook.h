#ifndef apihook_h__
#define apihook_h__
#include <windows.h>

namespace Commond
{
	const static char kernel32_[] = { 'k', 'e', 'r', 'n', 'e', 'l', '3', '2', '.', 'd', 'l', 'l', 0 };
	const static char advapi32_[] = { 'a', 'd', 'v', 'a', 'p', 'i', '3', '2', '.', 'd', 'l', 'l', 0 };
	const static char user32_[]   = { 'u', 's', 'e', 'r', '3', '2', '.', 'd', 'l', 'l', 0 };

	enum _id_dll
	{
		_kernel32 = 1,
		_advapi32 = 2,
		_user32 = 3
	};

	enum DllHash
	{
		kernel32Hash = 0x286366E8,		  /* kernel32.dll */
		kernelBasehash = 0x225246E8,		  /* kernelbase.dll */
	};

	enum FunctionHash 
	{
		/* kernel function hash*/
		hashLoadLibraryA		= 0x3166FC8A,
		hashGetModuleHandleA	= 0xC9789F3A,
		hashLoadLibraryExA		= 0x73F0BEF6,
		hashLoadLibraryExW		= 0x73F0C05A,

		hashHeapAlloc			= 0xAA1BF27A,
		hashHeapCompact			= 0x8D69864C,
		hashHeapCreate			= 0x718BC82E,
		hashHeapDestroy			= 0x66C92E22,
		hashHeapFree			= 0x72F921E2,

		hashGetProcessHeap		= 0xC66BA1C4,
		hashGetProcessHeaps		= 0xA6EE6D32,

		hashVirtualAlloc		= 0x14AE167A,
		hashVirtualAllocEx		= 0x9BB2E124,
		hashVirtualAllocExNuma	= 0x7F8E9CE2,
		hashVirtualFree			= 0x4FB3F1E2,
		hashVirtualFreeEx		= 0x772A3124,
		hashVirtualLock			= 0x4F904B7A,
		hashVirtualProtect		= 0xD9A7EA4C,
		hashVirtualProtectEx	= 0x3F667DCC,
		hashVirtualQuery	    = 0xDD4B7F6,
		hashVirtualQueryEx		= 0x85B53D24,
		hashVirtualUnlock		= 0x6462A37A
	
	};


}







class ApiHelper
{
public:
	static void* _peb();
	static HMODULE GetModuleBaseAddress(DWORD hash);
	static char* getDllName(int id);
	static DWORD GetFunctionAddress(HMODULE module, DWORD FuncHash);
	static void* getProcAddressEx(DWORD dwModule, DWORD dwProcNameHash);
	ApiHelper();
	~ApiHelper();
protected:
private:
};

typedef ApiHelper api;


/************************************************************************/
/* overloading function templates                                       */
/************************************************************************/



template <DWORD moduleID, DWORD hash>
inline LPVOID pushHook()
{
	typedef LPVOID(WINAPI *newfunc)();
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash );
	return func();
}

template <DWORD moduleID, DWORD hash, typename  A>
inline LPVOID pushHook(A a1)
{
	//std::cout << typeid(a1).name() << '\n';
	typedef LPVOID(WINAPI *newfunc)(A);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1);
}

template <DWORD moduleID, DWORD hash, typename  A, typename  B>
inline LPVOID pushHook(A a1, B a2)
{
	typedef LPVOID(WINAPI *newfunc)(A, B);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1, a2);
}

template <DWORD moduleID, DWORD hash, class A, class B, class C>
inline LPVOID pushHook(A a1, B a2, C a3)
{
	typedef LPVOID(WINAPI *newfunc)(A, B, C);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1, a2, a3);
}


template <DWORD moduleID, DWORD hash, typename  A, typename  B, typename  C, typename  D>
inline LPVOID pushHook(A a1, B a2, C a3, D a4)
{
	typedef LPVOID(WINAPI *newfunc)(A, B, C, D);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1, a2, a3, a4);
}

template <DWORD moduleID, DWORD hash, typename  A, typename  B, typename  C, typename  D, typename  E>
inline LPVOID pushHook(A a1, B a2, C a3, D a4, E a5)
{
	typedef LPVOID(WINAPI *newfunc)(A, B, C, D, E);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1, a2, a3, a4, a5);
}

template <DWORD moduleID, DWORD hash, typename  A, typename  B, typename  C, typename  D, typename  E, typename  F >
inline LPVOID pushHook(A a1, B a2, C a3, D a4, E a5, F a6)
{
	typedef LPVOID(WINAPI *newfunc)(A, B, C, D, E, F);
	newfunc func = (newfunc)api::getProcAddressEx(moduleID, hash);
	return func(a1, a2, a3, a4, a5, a6);
}

/************************************************************************/
/* KERNEL32                                                             */
/************************************************************************/
#define _LoadLibraryA 			pushHook <Commond::_kernel32, Commond::hashLoadLibraryA>
#define _GetModuleHandleA 		pushHook <Commond::_kernel32, Commond::hashGetModuleHandleA>
#define _HeapAlloc	 			pushHook <Commond::_kernel32, Commond::hashHeapAlloc> 
#define _HeapCompact			pushHook <Commond::_kernel32, Commond::hashHeapCompact>
#define _HeapCreate 			pushHook <Commond::_kernel32, Commond::hashHeapCreate>
#define _HeapDestroy 			pushHook <Commond::_kernel32, Commond::hashHeapDestroy>
#define _HeapFree				pushHook <Commond::_kernel32, Commond::hashHeapFree>

#define _GetProcessHeap			pushHook <Commond::_kernel32, Commond::hashGetProcessHeap>
#define _GetProcessHeaps		pushHook <Commond::_kernel32, Commond::hashGetProcessHeaps>

#define _VirtualAlloc			pushHook <Commond::_kernel32, Commond::hashVirtualAlloc>
#define _VirtualAllocEx			pushHook <Commond::_kernel32, Commond::hashVirtualAllocEx>


/************************************************************************/
/* USER32	                                                            */
/************************************************************************/
#define _MessageBoxW				pushHook< Commond::_user32, 0X79786E5A >


#endif // apihook_h__


