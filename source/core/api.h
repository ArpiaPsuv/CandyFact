#ifndef api_h__
#define api_h__
#include "apihook.h"

#define _LoadLibraryA 	pushHook <Commond::_kernel32, Commond::hashLoadLibraryA>

#define _HeapAlloc	 	pushHook <Commond::_kernel32, Commond::hashHeapAlloc> 
#define _HeapCompact	pushHook <Commond::_kernel32, Commond::hashHeapCompact>
#define _HeapCreate 	pushHook <Commond::_kernel32, Commond::hashHeapCreate>
#define _HeapDestroy 	pushHook <Commond::_kernel32, Commond::hashHeapDestroy>
#define _HeapFree		pushHook <Commond::_kernel32, Commond::hashHeapFree>

#define _GetProcessHeap		pushHook <Commond::_kernel32, Commond::hashGetProcessHeap>
#define _GetProcessHeaps	pushHook <Commond::_kernel32, Commond::hashGetProcessHeaps>

#define _VirtualAlloc	pushHook <Commond::_kernel32, Commond::hashVirtualAlloc>
#define _VirtualAllocEx	pushHook <Commond::_kernel32, Commond::hashVirtualAllocEx>







#endif // api_h__
