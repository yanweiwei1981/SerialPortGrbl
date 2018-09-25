
// SerialPortApplicationDlg.h : header file
//

#pragma once
#include "SerialPort.h"


// CSerialPortApplicationDlg dialog
class CSerialPortApplicationDlg : public CDialogEx
{
public:
	BOOL m_bVisible;		//�����Ƿ��������� ����ͼ����ť����
	BOOL m_bStopDispRXData; //�Ƿ���ʾ�����ַ�
	CString m_strTempSendFilePathName; //�����ļ�·����
	long m_nFileLength;		//�ļ�����
	BOOL m_bSendFile;		//�Ƿ����ļ�
	HICON m_hIconRed;		//���ڴ�ʱ�ĺ��ͼ����
	HICON m_hIconOff;		//���ڹر�ʱ��ָʾͼ����
	HICON m_hIconGreen;

	int m_nBaud;			//������
	int m_nCom;				//���ں�
	char m_cParity;			//У��
	int m_nDatabits;		//����λ
	int m_nStopbits;		//ֹͣλ
	CSerialPort m_Port;		//CSerialPort�����

// Construction
public:
	CSerialPortApplicationDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALPORTAPPLICATION_DIALOG };
#endif

public:
	CButton	m_ctrlHelp;
	//CPushPinButton	m_ctrlPushPin;
	CButton	m_ctrlSendFile;
	CEdit	m_ctrlEditSendFile;
	CStatic	m_ctrlTXCount;
	CStatic	m_ctrlPortStatus;
	CStatic	m_ctrlRXCOUNT;
	CEdit	m_ctrlSavePath;
	CButton	m_ctrlManualSend;
	//CHyperLink	m_ctrlHyperLink2;
	CButton	m_ctrlClearTXData;
	CStatic	m_ctrlStaticXFS;
	CButton	m_ctrlClose;
	CButton	m_ctrlCounterReset;
	CEdit	m_ctrlEditSend;
	CEdit	m_ctrlReceiveData;
	CEdit	m_ctrlReceiveDataCoordinateAccess;//���������Զ�����-����
	CButton	m_ctrlAutoClear;
	//CStatic	m_ctrlIconOpenoff;
	//CHyperLink	m_ctrlHyperLinkWWW;
	CComboBox	m_StopBits;
	CComboBox	m_DataBits;
	CComboBox	m_Parity;
	CButton	m_ctrlAutoSend;
	CButton m_ctrlAutoSendCoordinateAccess;//���������Զ�����
	CButton	m_ctrlHexSend;
	CButton	m_ctrlStopDisp;
	CButton	m_ctrlOpenPort;
	CButton	m_ctrlHexReceieve;
	CComboBox	m_Speed;
	CComboBox	m_Com;
	CString	m_ReceiveData;
	CString	m_ReceiveDataCoordinateAccess;//���������Զ�����-����
	CString	m_strSendData;
	CString	m_strCurPath;
	CString	m_strSendFilePathName;

	CComboBox m_Step;
	CString m_strStep;
	BOOL StartCoordinateAccessMonitoring();
	BOOL RestartCoordinateAccessMonitoring();
	BOOL StopCoordinateAccessMonitoring();
	CString m_CoordinateAccess;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	int m_nCycleTime;
	BOOL m_bAutoSend;
	BOOL m_bAutoSendCoordinateAccess;
	int Str2Hex(CString str, char *data);
	char HexChar(char c);
	DWORD m_dwCommEvents;
	BOOL m_bOpenPort;

	CWinThread* m_DlgThread;
	CWinThread* m_DlgWritePortThread;
	static UINT CoordinateAccessThread(LPVOID pParam);
	static UINT WriteToPortThread(LPVOID pParam);
	// Generated message map functions
	virtual BOOL OnInitDialog();

	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg LRESULT OnCoordinateAccess(WPARAM ch, LPARAM port);
	afx_msg LRESULT OnCommunication(WPARAM ch, LPARAM port);
	afx_msg void OnButtonClearReciArea();
	afx_msg void OnButtonOpenport();
	afx_msg void OnButtonStopdisp();
	afx_msg void OnButtonManualsend();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnChangeEditCycletime();
	afx_msg void OnButtonClearrecasenda();
	afx_msg void OnCheckAutosend();
	afx_msg void OnChangeEditSend();
	afx_msg void OnSelendokComboComselect();
	afx_msg void OnSelendokComboSpeed();
	afx_msg void OnSelendokComboParity();
	afx_msg void OnSelendokComboDatabits();
	afx_msg void OnSelendokComboStopbits();
	afx_msg void OnButtonSavedata();
	afx_msg void OnButtonDirbrowser();
	afx_msg void OnButtonSendfile();
	afx_msg void OnButtonCountreset();
	afx_msg void OnButtonFilebrowser();
	afx_msg void OnButtonClose();
	afx_msg void OnDestroy();
	afx_msg void OnCbnSelendokComboStep();
	afx_msg void OnBnClickedButtonXInc();
	afx_msg void OnBnClickedButtonXDec();
	afx_msg void OnBnClickedButtonYInc();
	afx_msg void OnBnClickedButtonYDec();
	afx_msg void OnBnClickedButtonZInc();
	afx_msg void OnBnClickedButtonZDec();
	afx_msg void OnBnClickedCheckCoordinate();
};
