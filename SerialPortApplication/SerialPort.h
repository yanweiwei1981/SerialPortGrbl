#pragma once
#ifndef __SERIALPORT_H__
#define __SERIALPORT_H__

#define WM_COMM_BREAK_DETECTED		WM_USER + 1		//串口输入中断
#define WM_COMM_CTS_DETECTED		WM_USER + 2		//清空和发送状态改变
#define WM_COMM_DSR_DETECTED		WM_USER + 3		//数据发送准备状态改变
#define WM_COMM_ERR_DETECTED		WM_USER + 4		//错误
#define WM_COMM_RING_DETECTED		WM_USER + 5		//循环
#define WM_COMM_RLNG_DETECTED		WM_USER + 6		//接收到单个信号状态改变
#define WM_COMM_RXCHAR				WM_USER + 7		//接收字符并放到缓冲区
#define WM_COMM_RXFLAG_DETECTED		WM_USER + 8		//接收事件
#define WM_COMM_TXEMPTY_DETECTED	WM_USER + 9		//最后一个字符从缓冲区发送出去
#define WM_COMM_RXCHAR_COORDINATE	WM_USER + 10	//接收字符并放到缓冲区-坐标
#endif // !__SERIALPORT_H__

class CSerialPort
{
public:
	int m_nWriteSize;
	void ClosePort();

	CSerialPort();
	virtual ~CSerialPort();
	//端口初始化
	BOOL InitPort(CWnd* pPortOwner, UINT portnr = 1, UINT baud = 19200, char parity = 'N', UINT databits = 8, UINT stopbits = 1, DWORD dwCommEvents = EV_RXCHAR, UINT writebuffersize = 1024);
	HANDLE m_hComm;

	//起/停COM观察
	BOOL StartMonitoring();
	BOOL RestartMonitoring();
	BOOL StopMonitoring();

	DWORD GetWriteBufferSize();
	DWORD GetCommEvents();
	DCB GetDCB();

	void WriteToPort(char* string);
	void WriteToPort(char* string, int n);
	void WriteToPort(LPCTSTR string);
	void WriteToPort(LPCTSTR string, int n);

protected:
	void ProcessErrorMessage(char* ErrorText);
	static UINT CommThread(LPVOID pParam);
	static void ReceiveChar(CSerialPort* port, COMSTAT comstat);
	static void WriteChar(CSerialPort* port);

	//线程
	CWinThread* m_Thread;
	//同步线程对象
	CRITICAL_SECTION m_csCommunicationSync;
	BOOL m_bThreadAlive;

	//句柄
	HANDLE m_hWriteEvent;
	HANDLE m_hShutdownEvent;

	HANDLE m_hEventArray[3];

	//结构
	OVERLAPPED m_ov;
	COMMTIMEOUTS m_CommTimeouts;
	DCB m_dcb;

	//本窗口
	CWnd* m_pOwner;

	//
	UINT m_nPortNr;
	char* m_szWriteBuffer;
	DWORD m_dwCommEvents;
	DWORD m_nWriteBufferSize;
};

