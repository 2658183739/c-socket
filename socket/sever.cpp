#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPECATED_NO_MARNINGS

#include<Windows.h>
#include<WinSock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")
int main()
{
	//����Windows socket 2.x����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);
	//----------

	//--��socket API��������TCP�����
	//1.����һ��socket
	SOCKET _sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//bind �����ڽ��ܿͻ������ӵ�����˿�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);//host to net unsigned short
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//inet_addr("127.0.0.1");
	if (SOCKET_ERROR == bind(_sock, (sockaddr*)&_sin, sizeof(_sin)))
	{
		printf("error!");
	}
	else
	{
		printf("success!");
	}
	//3 listen ��������˿�
	if (listen(_sock, 5) == SOCKET_ERROR)
	{
		printf("error");
	}
	else
	{
		printf("success��");
	}
	//4.accept �ȴ����ܿͻ�������
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	char msgBuf[] = "HELLO,l`m server.";

	while (1)
	{
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (INVALID_SOCKET == _cSock)
		{
			printf("error");
		}
		printf("�¿ͻ��˼��룺ip=%s \n", inet_ntoa(clientAddr.sin_addr));
		//5 send��ͻ��˷�������
		send(_cSock, msgBuf, sizeof(msgBuf) + 1, 0);
	}
	
	
	//�ر��׽���
	closesocket(_sock);


}