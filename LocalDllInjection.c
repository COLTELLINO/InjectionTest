#include <windows.h>
#include <stdio.h>

DWORD WINAPI threadFunc(LPVOID lpParam) {
	// code to run by the thread
	printf("Thread is running...\n");
	return 0;
}


int main(int argc, char** argv) {
	// Load the DLL
	PCSTR path_to_dll = argv[1];
	HINSTANCE hDll = LoadLibraryA(argv[1]);
	if (hDll == NULL) {
		printf("Failed to load DLL.\n");
		return 1;
	}

	// Create a thread
	HANDLE hThread = CreateThread(NULL, 0, threadFunc, NULL, 0, NULL);
	if (hThread == NULL) {
		printf("Failed to create thread: %d\n", GetLastError());
		return 1;
	}

	// Wait for a short time
	WaitForSingleObject(hThread, INFINITE);

	// Close the thread handle
	CloseHandle(hThread);

	// Free the DLL
	FreeLibrary(hDll);

	return 0;
}