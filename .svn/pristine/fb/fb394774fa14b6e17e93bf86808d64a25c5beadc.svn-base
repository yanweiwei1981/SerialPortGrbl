#include "stdafx.h"
#include "SerialPort.h"

#include <assert.h>
#include <iostream>


CSerialPort::CSerialPort()
{
	m_hComm = NULL;
	//初始化overlapped
	m_ov.Offset = 0;
	m_ov.OffsetHigh = 0;

	m_ov.hEvent = NULL;

	m_hWriteEvent = NULL;
	m_hShutdownEvent = NULL;

	m_szWriteBuffer = NULL;
	m_nWriteSize = 1;

	m_bThreadAlive = FALSE;
}


CSerialPort::~CSerialPort()
{
	do
	{
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);

	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	if (m_hShutdownEvent != NULL) 
		CloseHandle(m_hShutdownEvent);

	if (m_ov.hEvent != NULL)
		CloseHandle(m_ov.hEvent);

	if (m_hWriteEvent != NULL)
		CloseHandle(m_hWriteEvent);

	TRACE("Thread ended\n");

	delete[] m_szWriteBuffer;
}

BOOL CSerialPort::InitPort(CWnd * pPortOwner, UINT portnr, UINT baud, char parity, UINT databits, UINT stopbits, DWORD dwCommEvents, UINT writebuffersize)
{
	assert(portnr > 0 && portnr < 5);
	assert(pPortOwner != NULL);

	if (m_bThreadAlive)
	{
		do
		{
			SetEvent(m_hShutdownEvent);

		} while (m_bThreadAlive);
		TRACE("Thread ended\n");
	}

	//创建事件
	if (m_ov.hEvent != NULL)
		ResetEvent(m_ov.hEvent);
	else
		m_ov.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hWriteEvent != NULL)
		ResetEvent(m_hWriteEvent);
	else
		m_hWriteEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	if (m_hShutdownEvent != NULL)
		ResetEvent(m_hShutdownEvent);
	else
		m_hShutdownEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

	//初始化事件对象
	m_hEventArray[0] = m_hShutdownEvent;
	m_hEventArray[1] = m_ov.hEvent;
	m_hEventArray[2] = m_hWriteEvent;

	InitializeCriticalSection(&m_csCommunicationSync);

	m_pOwner = pPortOwner;

	if (m_szWriteBuffer != NULL)
		delete[] m_szWriteBuffer;

	m_szWriteBuffer = new char[writebuffersize];

	m_nPortNr = portnr;

	m_nWriteBufferSize = writebuffersize;
	m_dwCommEvents = dwCommEvents;

	BOOL bResult = FALSE;
	//LPCWSTR szPort = _T("COM1");// new char[50];
	char* szPort = new char[50];
	char* szBaud = new char[50];

	/*CString str = CString(szPort);
	USES_CONVERSION;
	LPCWSTR wszPort = A2CW(W2A(str));
	str = CString(szBaud);
	LPCWSTR wszBaud = A2CW(W2A(str));
	str.ReleaseBuffer();*/

	EnterCriticalSection(&m_csCommunicationSync);

	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}

	sprintf(szPort, "COM%d", portnr);
	sprintf(szBaud, "baud=%d parity=%c data=%d stop=%d", baud, parity, databits, stopbits);

	m_hComm = CreateFile(szPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, 0);
	
	if (m_hComm == INVALID_HANDLE_VALUE)
	{
		//没有找到串口
		delete[] szPort;
		delete[] szBaud;

		return FALSE;
	}

	//设置超时
	m_CommTimeouts.ReadIntervalTimeout = 1000;
	m_CommTimeouts.ReadTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.ReadTotalTimeoutConstant = 1000;
	m_CommTimeouts.WriteTotalTimeoutMultiplier = 1000;
	m_CommTimeouts.WriteTotalTimeoutConstant = 1000;

	//配置
	if (SetCommTimeouts(m_hComm, &m_CommTimeouts))
	{
		if (SetCommMask(m_hComm, dwCommEvents))
		{
			if (GetCommState(m_hComm, &m_dcb))
			{
				m_dcb.EvtChar = 'q';
				m_dcb.fRtsControl = RTS_CONTROL_ENABLE;
				if (BuildCommDCB(szBaud, &m_dcb))
					if (SetCommState(m_hComm, &m_dcb))
						;
					else
						ProcessErrorMessage("SetCommState()");
				else
					ProcessErrorMessage("BuildCommDCB()");
			}
			else
				ProcessErrorMessage("GetCommState()");
		}
		else
			ProcessErrorMessage("SetCommMask()");
	}
	else
		ProcessErrorMessage("SetCommTimeouts()");

	delete[] szPort;
	delete[] szBaud;

	//刷新串口
	PurgeComm(m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	LeaveCriticalSection(&m_csCommunicationSync);

	TRACE("Initialisation for communicationport %d completed.\nUse Startmonitor to communicate.\n", portnr);

	return TRUE;
}

UINT CSerialPort::CommThread(LPVOID pParam)
{
	CSerialPort* port = (CSerialPort*)pParam;
	port->m_bThreadAlive = TRUE;

	DWORD BytesTransfered = 0;
	DWORD Event = 0;
	DWORD CommEvent = 0;
	DWORD dwError = 0;
	static COMSTAT comstat;
	BOOL  bResult = TRUE;

	//清理串口并启动
	if (port->m_hComm)//确认串口打开
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	for (;;)
	{
		bResult = WaitCommEvent(port->m_hComm, &Event, &port->m_ov);
		if (!bResult)
		{
			switch (dwError = GetLastError())
			{
			case ERROR_IO_PENDING:
			{
				break;
			}
				
			case 87:
			{
				break;
			}
			default:
			{
				port->ProcessErrorMessage("WaitCommEvent()");
				break;
			}
			}
		}
		else
		{
			bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

			if (comstat.cbInQue == 0)
				continue;
		}//if-else

		Event = WaitForMultipleObjects(3, port->m_hEventArray, FALSE, INFINITE);

		switch (Event)
		{
		case 0:
		{
			//关闭
			CloseHandle(port->m_hComm);
			port->m_hComm = NULL;
			port->m_bThreadAlive = FALSE;

			//关闭线程
			AfxEndThread(100);

			break;
		}
		case 1://事件
		{
			GetCommMask(port->m_hComm, &CommEvent);
			if (CommEvent & EV_RXCHAR)
				//读串口数据
				ReceiveChar(port, comstat);
			if (CommEvent & EV_CTS)
				::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_CTS_DETECTED, (WPARAM)0, (LPARAM)port->m_nPortNr);
			if (CommEvent & EV_BREAK)
				::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_BREAK_DETECTED, (WPARAM)0, (LPARAM)port->m_nPortNr);
			if (CommEvent & EV_ERR)
				::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_ERR_DETECTED, (WPARAM)0, (LPARAM)port->m_nPortNr);
			if (CommEvent & EV_RING)
				::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RING_DETECTED, (WPARAM)0, (LPARAM)port->m_nPortNr);

			if (CommEvent & EV_RXFLAG)
				::SendMessage(port->m_pOwner->m_hWnd, WM_COMM_RXFLAG_DETECTED, (WPARAM)0, (LPARAM)port->m_nPortNr);

			break;
		}
		case 2://写串口
		{
			//
			WriteChar(port);
			break;
		}

		} //结束switch

	}//循环 forever loop
	return 0;
}

BOOL CSerialPort::StartMonitoring()
{
	if (!(m_Thread = AfxBeginThread(CommThread, this)))
		return FALSE;
	TRACE("Thread started\n");
	return TRUE;
}

BOOL CSerialPort::RestartMonitoring()
{
	TRACE("Thread resumed\n");
	m_Thread->ResumeThread();
	return TRUE;
}

BOOL CSerialPort::StopMonitoring()
{
	TRACE("Thread suspended\n");
	m_Thread->SuspendThread();
	return TRUE;
}

void CSerialPort::ProcessErrorMessage(char* ErrorText)
{
	char* Temp = new char[200];

	LPVOID lpMsgBuf;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR)&lpMsgBuf,
		0,
		NULL
	);

	sprintf(Temp, "WARNING:  %s Failed with the following error: \n%s\nPort: %d\n", (char*)ErrorText, lpMsgBuf, m_nPortNr);
	MessageBoxA(NULL, Temp, "Application Error", MB_ICONSTOP);

	LocalFree(lpMsgBuf);
	delete[] Temp;
}

//写数据
void CSerialPort::WriteChar(CSerialPort* port)
{
	BOOL bWrite = TRUE;
	BOOL bResult = TRUE;

	DWORD BytesSent = 0;

	ResetEvent(port->m_hWriteEvent);

	//
	EnterCriticalSection(&port->m_csCommunicationSync);

	if (bWrite)
	{
		//
		port->m_ov.Offset = 0;
		port->m_ov.OffsetHigh = 0;

		//清理串口
		PurgeComm(port->m_hComm, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

		bResult = WriteFile(port->m_hComm,			//串口
			port->m_szWriteBuffer,					//
													//strlen((char*)port->m_szWriteBuffer),	// Length of message to send
			port->m_nWriteSize,						//信息长度
			&BytesSent,								//
			&port->m_ov);							//

		//异常处理
		if (!bResult)
		{
			DWORD dwError = GetLastError();
			switch (dwError)
			{
			case ERROR_IO_PENDING:
			{
				// continue to GetOverlappedResults()
				BytesSent = 0;
				bWrite = FALSE;
				break;
			}
			default:
			{
				//错误
				port->ProcessErrorMessage("WriteFile()");
			}
			}
		}
		else
		{
			LeaveCriticalSection(&port->m_csCommunicationSync);
		}
	} // end if(bWrite)

	if (!bWrite)
	{
		bWrite = TRUE;

		bResult = GetOverlappedResult(port->m_hComm,	//
			&port->m_ov,								//结构体
			&BytesSent,									//发送
			TRUE); 										//等待标志

		LeaveCriticalSection(&port->m_csCommunicationSync);

		//其他异常处理
		//if (!bResult)  
		{
			//port->ProcessErrorMessage("GetOverlappedResults() in WriteFile()");
		}
	} // end if (!bWrite)

	 //发送
	if (BytesSent != port->m_nWriteSize)	//
	{
		TRACE("WARNING: WriteFile() error.. Bytes Sent: %d; Message Length: %d\n", BytesSent, strlen((char*)port->m_szWriteBuffer));
	}
	//	::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_TXEMPTY_DETECTED, (WPARAM) RXBuff, (LPARAM) port->m_nPortNr);
	//	::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_TXEMPTY_DETECTED,0,(LPARAM) port->m_nPortNr);
}

//收数据
void CSerialPort::ReceiveChar(CSerialPort* port, COMSTAT comstat)
{
	BOOL  bRead = TRUE;
	BOOL  bResult = TRUE;
	DWORD dwError = 0;
	DWORD BytesRead = 0;
	unsigned char RXBuff;

	for (;;)
	{
		EnterCriticalSection(&port->m_csCommunicationSync);

		bResult = ClearCommError(port->m_hComm, &dwError, &comstat);

		LeaveCriticalSection(&port->m_csCommunicationSync);


		if (comstat.cbInQue == 0)
		{
			//
			break;
		}

		EnterCriticalSection(&port->m_csCommunicationSync);

		if (bRead)
		{
			bResult = ReadFile(port->m_hComm,		
				&RXBuff,				
				1,					
				&BytesRead,			
				&port->m_ov);		

			if (!bResult)
			{
				switch (dwError = GetLastError())
				{
				case ERROR_IO_PENDING:
				{
					// Proceed on to GetOverlappedResults();
					bRead = FALSE;
					break;
				}
				default:
				{
					//
					port->ProcessErrorMessage("ReadFile()");
					break;
				}
				}
			}
			else
			{
				//
				bRead = TRUE;
			}
		} //close if (bRead)

		if (!bRead)
		{
			bRead = TRUE;
			bResult = GetOverlappedResult(port->m_hComm,	
				&port->m_ov,		
				&BytesRead,		
				TRUE); 			

			if (!bResult)
			{
				port->ProcessErrorMessage("GetOverlappedResults() in ReadFile()");
			}
		} //close if (!bRead)

		LeaveCriticalSection(&port->m_csCommunicationSync);

		//
		::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXCHAR, (WPARAM)RXBuff, (LPARAM)port->m_nPortNr);
		::SendMessage((port->m_pOwner)->m_hWnd, WM_COMM_RXCHAR_COORDINATE, (WPARAM)RXBuff, (LPARAM)port->m_nPortNr);
	} // end forever loop

}


//写端口
void CSerialPort::WriteToPort(char* string)
{
	assert(m_hComm != 0);

	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	strcpy(m_szWriteBuffer, string);
	m_nWriteSize = strlen(string);

	//设置成写串口
	SetEvent(m_hWriteEvent);
}


void CSerialPort::WriteToPort(char* string, int n)
{
	assert(m_hComm != 0);

	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	//memset(m_szWriteBuffer, 0, n);
	//strncpy(m_szWriteBuffer, string, n);
	memcpy(m_szWriteBuffer, string, n);
	m_nWriteSize = n;

	//设置成写串口
	SetEvent(m_hWriteEvent);
}

void CSerialPort::WriteToPort(LPCTSTR string)
{
	assert(m_hComm != 0);

	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	strcpy(m_szWriteBuffer, string);
	m_nWriteSize = strlen(string);

	//设置成写串口
	SetEvent(m_hWriteEvent);
}

void CSerialPort::WriteToPort(LPCTSTR string, int n)
{
	assert(m_hComm != 0);

	memset(m_szWriteBuffer, 0, sizeof(m_szWriteBuffer));
	//strncpy(m_szWriteBuffer, string, n);
	memcpy(m_szWriteBuffer, string, n);
	m_nWriteSize = n;
	//设置成写串口
	SetEvent(m_hWriteEvent);
}

//返回设备控制权
DCB CSerialPort::GetDCB()
{
	return m_dcb;
}

//返回连接事件
DWORD CSerialPort::GetCommEvents()
{
	return m_dwCommEvents;
}

//返回输出缓冲大小
DWORD CSerialPort::GetWriteBufferSize()
{
	return m_nWriteBufferSize;
}


void CSerialPort::ClosePort()
{
	SetEvent(m_hShutdownEvent);
}

/*
void CSerialPort::ClosePort()
{
	do
	{
		SetEvent(m_hShutdownEvent);
	} while (m_bThreadAlive);


	// if the port is still opened: close it
	if (m_hComm != NULL)
	{
		CloseHandle(m_hComm);
		m_hComm = NULL;
	}
	// Close Handles
	if(m_hShutdownEvent!=NULL)
	CloseHandle( m_hShutdownEvent);
	if(m_ov.hEvent!=NULL)
		CloseHandle( m_ov.hEvent );
	if(m_hWriteEvent!=NULL)
		CloseHandle( m_hWriteEvent );

	TRACE("Thread ended\n");
	delete [] m_szWriteBuffer;
}

*/