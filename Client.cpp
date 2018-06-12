#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib") // �d�� ws2_32.dll

int main() {
	// ��ʼ��DLL
	WSADATA wasData;
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// ������Ƕ��
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// ��������l��Ո��
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr)); // ÿ���ֹ�����0�����
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	// ���շ��������صĔ���
	char szBuffer[MAXBYTE] = { 0 };
	recv(sock, szBuffer, MAXBYTE, NULL);

	// ݔ�����յ��Ĕ���
	printf("Message from server: %s\n", szBuffer);

	// �P�]��Ƕ��
	closesocket(sock);

	// ��ֹʹ��DLL
	WSACleanup();

	system("pause");
	return 0;
}