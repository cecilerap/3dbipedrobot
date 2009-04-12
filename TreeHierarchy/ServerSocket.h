//////////////////////////////////////////////////////////////////////////
// ServerSocket.h
//////////////////////////////////////////////////////////////////////////

#pragma once

class CServerSocket
{
public:
	CServerSocket(void);
	~CServerSocket(void);

	BOOL Create(unsigned short port);
	SOCKET Accept(sockaddr_in* addr = NULL);
	void Close();

	int Send(const char* data, unsigned int len);
	int Recv(char* data, unsigned int bufSize);

public:
	SOCKET m_sock;
};
