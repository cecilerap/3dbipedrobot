//////////////////////////////////////////////////////////////////////////
// ServerSocket.cpp
//////////////////////////////////////////////////////////////////////////

#include <winsock2.h>
#include <assert.h>
#include "ServerSocket.h"

CServerSocket::CServerSocket(void)
: m_sock(INVALID_SOCKET)
{
}

CServerSocket::~CServerSocket(void)
{
	if(m_sock != INVALID_SOCKET)
		Close();
}

BOOL CServerSocket::Create(unsigned short port)
{
	assert(m_sock == INVALID_SOCKET);

	if((m_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
		return FALSE;

	sockaddr_in addr = {0};
	addr.sin_family		 = AF_INET;
	addr.sin_port		 = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;

	int ret;
	if((ret = bind(m_sock, (sockaddr*)&addr, sizeof(addr))) == SOCKET_ERROR ||
	   (ret = listen(m_sock, SOMAXCONN))                    == SOCKET_ERROR )
	{
		Close();
		return FALSE;
	}

	return TRUE;
}

SOCKET CServerSocket::Accept(sockaddr_in* addr)
{
	int len = sizeof(sockaddr_in);
	return accept(m_sock, (sockaddr*)addr, &len);
}

void CServerSocket::Close()
{
	assert(m_sock != INVALID_SOCKET);
	closesocket(m_sock);
	m_sock = INVALID_SOCKET;
}

int CServerSocket::Send(const char* data, unsigned int len)
{
	assert(m_sock != INVALID_SOCKET);
	return ::send( m_sock, data, len, 0 );
}

int CServerSocket::Recv(char* data, unsigned int bufSize)
{
	assert(m_sock != INVALID_SOCKET);
	return ::recv(m_sock, data, bufSize, 0);
}