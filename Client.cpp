#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib") // 載入 ws2_32.dll

int main() {
	// 初始化DLL
	WSADATA wasData;
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// 創建套嵌字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 向服務器發起請求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr)); // 每個字節都用0來填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	// 接收服務器傳回的數據
	char szBuffer[MAXBYTE] = { 0 };
	recv(sock, szBuffer, MAXBYTE, NULL);

	// 輸出接收到的數據
	printf("Message from server: %s\n", szBuffer);

	// 關閉套嵌字
	closesocket(sock);

	// 中止使用DLL
	WSACleanup();

	system("pause");
	return 0;
}