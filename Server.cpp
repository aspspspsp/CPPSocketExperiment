#include <stdio.h>
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib") // �d�� ws2_32.dll

int main() {
	// ��ʼ�� dll
	WSADATA wasData;
	WSAStartup(MAKEWORD(2, 2), &wasData);

	// �����׽���
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	// �����׽���
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));
	sockAddr.sin_family = PF_INET; // ʹ��Ipv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //���w��IP��ַ
	sockAddr.sin_port = htons(1234); // �˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

	// �M��O ��B
	listen(servSock, 20);

	// ���տ͑���Ո��
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);

	// ��͑��˰l�͔���
	const char *str = "HELLO WORLD!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);

	// �P�]�׽���
	closesocket(clntSock);
	closesocket(servSock);

	// ��ֹDLL��ʹ��
	WSACleanup();

	return 0;
}
