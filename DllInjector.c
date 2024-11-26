#include <windows.h>
#include <stdio.h>

int main(int argc, char** argv) {
	if (argc != 3) {
		printf("usage: dll-injector.exe <path-to-dll> <PID>\n");
		return 1;
	}
	PCSTR dll_path = argv[1];
	DWORD PID = atoi(argv[2]);
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
	if (hProcess == NULL) {
		printf("Failed to retrieve handle to remote process: %d\n", GetLastError());
		return 1;
	}
	LPVOID allocated_mem = VirtualAllocEx(hProcess, NULL, strlen(dll_path) + 1, (MEM_COMMIT | MEM_RESERVE), PAGE_READWRITE);
	if (allocated_mem == NULL) {
		printf("Failed to allocated memory in remote process: %d\n", GetLastError());
		return 1;
	}
	printf("memory allocated at: %p\n", allocated_mem);
	WriteProcessMemory(hProcess, allocated_mem, dll_path, strlen(dll_path) + 1, NULL);
	HMODULE kernel32Base = GetModuleHandleW(L"kernel32.dll");
	if (kernel32Base == NULL) {
		printf("Failed to retrieve handle to kernel32.dll: %d\n", GetLastError());
		return 1;
	}
	FARPROC load_library_address = GetProcAddress(kernel32Base, "LoadLibraryA");
	HANDLE hThread = CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)load_library_address, allocated_mem, 0, NULL);
	if (hThread == NULL) {
		printf("Failed to create thread in remote process: %d\n", GetLastError());
		return 1;
	}
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hProcess);

	return 0;
}