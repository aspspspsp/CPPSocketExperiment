#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib") // 載入 ws2_32.dll

int main() {
	// 初始化 dll
	WSADATA wasData;
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// 創建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 綁定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET; // 使用Ipv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //具體的IP地址
	sockAddr.sin_port = htons(1234); // 端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	// 進入監聽狀態
	listen(servSock, 20);

	// 接收客戶端請求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	// 向客戶端發送數據
	const char *str = "HELLO WORLD!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	// 關閉套接字
	closesocket(clntSock);
	closesocket(servSock);

	// 中止DLL的使用
	WSACleanup();

	return 0;
}
