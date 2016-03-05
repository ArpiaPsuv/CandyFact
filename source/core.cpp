
#include <iostream>
#include "core/apihook.h"
struct exampleStruct {

	short x;
	long y;
	double z;
	char a[20];
};

int main()
{
	/* 

 http://www.overclock.net/t/1464743/unhandled-exception-at-0x013b117d-in-acm-exe-0xc0000096-privileged-instruction-error-when-calling-a-certain-function
	*/

	HMODULE hkernel32 = api::GetModuleBaseAddress(Commond::kernel32Hash);
	api::GetFunctionAddress(hkernel32, Commond::hashHeapAlloc);
	_MessageBoxW(NULL, L"MessageBoxW work", L"hello World", MB_OK);

	system("pause");
}
