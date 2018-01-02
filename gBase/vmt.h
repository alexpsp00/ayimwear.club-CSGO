class CVMTManager
{
public:
	inline void* Hook(void* Instance, int Index, void* HookedFunc)
	{
		DWORD VirtualTable = *(DWORD*)Instance;
		DWORD VirtualFunction = VirtualTable + sizeof(DWORD)* Index;
		intptr_t OriginalFunction = *((DWORD*)VirtualFunction);
		DWORD OldProtect;
		VirtualProtect((LPVOID)VirtualFunction, sizeof(DWORD), PAGE_EXECUTE_READWRITE, &OldProtect);
		*((DWORD*)VirtualFunction) = (DWORD)HookedFunc;
		VirtualProtect((LPVOID)VirtualFunction, sizeof(DWORD), OldProtect, &OldProtect);
		return (void*)OriginalFunction;
	}
}; CVMTManager VMTManager;