
// SerialPortApplicationDlg.cpp : implementation file
//
//
#include "stdafx.h"
#include "SerialPortApplication.h"
#include "SerialPortApplicationDlg.h"
#include "afxdialogex.h"
#include "io.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

long TX_count = 0;


// CAboutDlg dialog used for App About//

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// CSerialPortApplicationDlg dialog
CSerialPortApplicationDlg::CSerialPortApplicationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALPORTAPPLICATION_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ReceiveData = _T("");
	m_strSendData = _T("");
	m_strCurPath = _T("");
	m_strSendFilePathName = _T("");
	m_bAutoSend = FALSE;
	m_bAutoSendCoordinateAccess = FALSE;
	m_bVisible = FALSE;
	m_bSendFile = FALSE;
	m_bStopDispRXData = FALSE;
	m_bOpenPort = FALSE;
	m_nCycleTime = 1000;
	m_strCurPath = _T("C:\\COMDATA");
	m_strSendFilePathName = _T("还没有选择文件");//"No File Selected!";
	m_nFileLength = 0;
}

void CSerialPortApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_BUTTON_HELP, m_ctrlHelp);								//01-x
	//DDX_Control(pDX, IDC_BUTTON_PUSHPIN, m_ctrlPushPin);							//02-x
	//DDX_Control(pDX, IDC_BUTTON_SENDFILE, m_ctrlSendFile);						//03
	DDX_Control(pDX, IDC_EDIT_SENDFILE, m_ctrlEditSendFile);						//04
	DDX_Control(pDX, IDC_STATIC_TXCOUNT, m_ctrlTXCount);							//05
	DDX_Control(pDX, IDC_STATIC_STATUS, m_ctrlPortStatus);							//06
	DDX_Control(pDX, IDC_STATIC_RXCOUNT, m_ctrlRXCOUNT);							//07
	DDX_Control(pDX, IDC_EDIT_SAVEPATH, m_ctrlSavePath);
	//DDX_Control(pDX, IDC_EDIT_SAVEPATH, m_ctrlSavePath);							//08
	DDX_Control(pDX, IDC_BUTTON_MANUALSEND, m_ctrlManualSend);						//09
	//DDX_Control(pDX, IDC_STATIC_GJW, m_ctrlHyperLink2);							//10-x
	DDX_Control(pDX, IDC_BUTTON_CLEARRECASENDA, m_ctrlClearTXData);					//11
	//DDX_Control(pDX, IDC_STATIC_XFS, m_ctrlStaticXFS);							//12-x
	//DDX_Control(pDX, IDC_BUTTON_CLOSE, m_ctrlClose);								//13-x
	DDX_Control(pDX, IDC_BUTTON_COUNTRESET, m_ctrlCounterReset);					//14
	DDX_Control(pDX, IDC_EDIT_SEND, m_ctrlEditSend);								//15
	DDX_Control(pDX, IDC_EDIT_RECIVE, m_ctrlReceiveData);							//16
	DDX_Control(pDX, IDC_EDIT_COORDINATE, m_ctrlReceiveDataCoordinateAccess);		//16
	DDX_Control(pDX, IDC_CHECK_AUTOCLEAR, m_ctrlAutoClear);							//17
	DDX_Control(pDX, IDC_COMBO_STOPBITS, m_StopBits);								//20
	DDX_Control(pDX, IDC_COMBO_DATABITS, m_DataBits);								//21
	DDX_Control(pDX, IDC_COMBO_PARITY, m_Parity);									//22
	DDX_Control(pDX, IDC_CHECK_AUTOSEND, m_ctrlAutoSend);							//23
	DDX_Control(pDX, IDC_CHECK_COORDINATE, m_ctrlAutoSendCoordinateAccess);
	DDX_Control(pDX, IDC_CHECK_HEXSEND, m_ctrlHexSend);								//24
	DDX_Control(pDX, IDC_BUTTON_STOPDISP, m_ctrlStopDisp);							//25
	DDX_Control(pDX, IDC_BUTTON_OPENPORT, m_ctrlOpenPort);							//26
	DDX_Control(pDX, IDC_CHECK_HEXRECIEVE, m_ctrlHexReceieve);						//27
	DDX_Control(pDX, IDC_COMBO_SPEED, m_Speed);										//28
	DDX_Control(pDX, IDC_COMBO_COMSELECT, m_Com);									//29
	DDX_Text(pDX, IDC_EDIT_RECIVE, m_ReceiveData);									//30
	DDX_Text(pDX, IDC_EDIT_COORDINATE, m_ReceiveDataCoordinateAccess);				//30
	DDX_Text(pDX, IDC_EDIT_SEND, m_strSendData);									//31
	DDX_Text(pDX, IDC_EDIT_SAVEPATH, m_strCurPath);									//32
	DDV_MaxChars(pDX, m_strCurPath, 200);											//33
	DDX_Text(pDX, IDC_EDIT_SENDFILE, m_strSendFilePathName);						//34
	DDV_MaxChars(pDX, m_strSendFilePathName, 200);									//35

	DDX_Control(pDX, IDC_COMBO_STEP, m_Step);
}

BEGIN_MESSAGE_MAP(CSerialPortApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()

	ON_MESSAGE(WM_COMM_RXCHAR_COORDINATE, &CSerialPortApplicationDlg::OnCoordinateAccess)
	ON_MESSAGE(WM_COMM_RXCHAR, &CSerialPortApplicationDlg::OnCommunication)								//01
	//ON_MESSAGE(WM_COMM_TXEMPTY_DETECTED, OnFileSendingEnded)											//02-x
	ON_BN_CLICKED(IDC_BUTTON_CLEAR_RECI_AREA, &CSerialPortApplicationDlg::OnButtonClearReciArea)		//03
	ON_BN_CLICKED(IDC_BUTTON_OPENPORT, &CSerialPortApplicationDlg::OnButtonOpenport)					//04
	ON_BN_CLICKED(IDC_BUTTON_STOPDISP, &CSerialPortApplicationDlg::OnButtonStopdisp)					//05-接收区域是否持续显示
	ON_BN_CLICKED(IDC_BUTTON_MANUALSEND, &CSerialPortApplicationDlg::OnButtonManualsend)				//06
	ON_BN_CLICKED(IDC_CHECK_AUTOSEND, &CSerialPortApplicationDlg::OnCheckAutosend)						//07-勾选是否定时自动发送
	ON_WM_TIMER()																						//08
	ON_EN_CHANGE(IDC_EDIT_CYCLETIME, &CSerialPortApplicationDlg::OnChangeEditCycletime)					//09
	ON_EN_CHANGE(IDC_EDIT_SEND, &CSerialPortApplicationDlg::OnChangeEditSend)							//10
	ON_BN_CLICKED(IDC_BUTTON_CLEARRECASENDA, &CSerialPortApplicationDlg::OnButtonClearrecasenda)		//11
	ON_CBN_SELENDOK(IDC_COMBO_COMSELECT, &CSerialPortApplicationDlg::OnSelendokComboComselect)			//12
	ON_CBN_SELENDOK(IDC_COMBO_SPEED, &CSerialPortApplicationDlg::OnSelendokComboSpeed)					//13
	ON_CBN_SELENDOK(IDC_COMBO_PARITY, &CSerialPortApplicationDlg::OnSelendokComboParity)				//14
	ON_CBN_SELENDOK(IDC_COMBO_DATABITS, &CSerialPortApplicationDlg::OnSelendokComboDatabits)			//15
	ON_CBN_SELENDOK(IDC_COMBO_STOPBITS, &CSerialPortApplicationDlg::OnSelendokComboStopbits)			//16

	//ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, OnButtonSavedata)												//17
	//ON_BN_CLICKED(IDC_BUTTON_DIRBROWSER, OnButtonDirbrowser)											//18
	//ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendfile)												//19
	//ON_BN_CLICKED(IDC_BUTTON_COUNTRESET, OnButtonCountreset)											//20
	//ON_BN_CLICKED(IDC_BUTTON_CLOSE, OnButtonClose)													//21-x
	//ON_BN_CLICKED(IDC_BUTTON_FILEBROWSER, OnButtonFilebrowser)										//22
	//ON_BN_CLICKED(IDC_BUTTON_PUSHPIN, OnButtonPushpin)												//23-x

	ON_BN_CLICKED(IDC_BUTTON_SAVEDATA, &CSerialPortApplicationDlg::OnButtonSavedata)					//17
	ON_BN_CLICKED(IDC_BUTTON_DIRBROWSER, &CSerialPortApplicationDlg::OnButtonDirbrowser)				//18
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, &CSerialPortApplicationDlg::OnButtonSendfile)					//19
	ON_BN_CLICKED(IDC_BUTTON_COUNTRESET, &CSerialPortApplicationDlg::OnButtonCountreset)				//20
	ON_BN_CLICKED(IDC_BUTTON_FILEBROWSER, &CSerialPortApplicationDlg::OnButtonFilebrowser)				//22
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CSerialPortApplicationDlg::OnButtonClose)
	ON_CBN_SELENDOK(IDC_COMBO_STEP, &CSerialPortApplicationDlg::OnCbnSelendokComboStep)
	ON_BN_CLICKED(IDC_BUTTON_X_INC, &CSerialPortApplicationDlg::OnBnClickedButtonXInc)
	ON_BN_CLICKED(IDC_BUTTON_X_DEC, &CSerialPortApplicationDlg::OnBnClickedButtonXDec)
	ON_BN_CLICKED(IDC_BUTTON_Y_INC, &CSerialPortApplicationDlg::OnBnClickedButtonYInc)
	ON_BN_CLICKED(IDC_BUTTON_Y_DEC, &CSerialPortApplicationDlg::OnBnClickedButtonYDec)
	ON_BN_CLICKED(IDC_BUTTON_Z_INC, &CSerialPortApplicationDlg::OnBnClickedButtonZInc)
	ON_BN_CLICKED(IDC_BUTTON_Z_DEC, &CSerialPortApplicationDlg::OnBnClickedButtonZDec)
	ON_BN_CLICKED(IDC_CHECK_COORDINATE, &CSerialPortApplicationDlg::OnBnClickedCheckCoordinate)
END_MESSAGE_MAP()

// CSerialPortApplicationDlg Function
UINT CSerialPortApplicationDlg::WriteToPortThread(LPVOID pParam)
{
	CSerialPortApplicationDlg* dlg = (CSerialPortApplicationDlg*)pParam;
	int nIndex;
	int nFind;
	int nStart = 0;
	int nLength;
	int nLoop1 = 0;
	//BOOL bSleep5000 = FALSE;
	//int nCount;
	CString strTemp1, strTemp2, strTemp3;
	strTemp3 = _T("\n");
	CString strTemp;

	//dlg->UpdateData(TRUE);

	nFind = dlg->m_strSendData.Find(_T("\n"));
	strTemp1 = dlg->m_strSendData;
	nIndex = strTemp1.Find(_T("\n"));
	strTemp1 = dlg->m_strSendData;
	if (nFind >= 0)
	{
		while (nIndex >= 0)
		{
			nIndex = strTemp1.Find(_T("\n"));
			nLength = strTemp1.GetLength();
			

			strTemp2 = strTemp1.Mid(nStart, (nIndex + 1));
			//nStart = nIndex;
			strTemp1 = strTemp1.Mid((nIndex + 1), (nLength - nIndex - 1));

			strTemp3 += strTemp2;

			dlg->m_Port.WriteToPort((LPCTSTR)strTemp2);	//发送数据
			TX_count += strTemp2.GetLength();
			//dlg->GetDlgItem(IDC_STATIC_TXCOUNT).SetWindowText();
			strTemp.Format("TX:%d", TX_count);
			dlg->m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
			nLoop1++;
			if ((nLoop1 % 10) == 0)
			{
				//dlg->m_Port.WriteToPort((LPCTSTR)strTemp3);	//发送数据
				//TX_count += strTemp3.GetLength();
				//strTemp.Format("TX:%d", TX_count);
				//dlg->m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
				strTemp3 = _T("\n");
				Sleep(5000);
			}
			else
			{
				Sleep(2000);
			}
		}
	}
	else
	{
		//dlg->m_Port.WriteToPort((LPCTSTR)dlg->m_strSendData);	//发送数据
	}
	return 0;
}

//这个版本的坐标解析是完整的-----OK
UINT CSerialPortApplicationDlg::CoordinateAccessThread(LPVOID pParam)
{
	CSerialPortApplicationDlg* dlg = (CSerialPortApplicationDlg*)pParam;
	CString strSendData = _T("?\n");
	CString strTemp;
	CString strReceiveData;
	CString X = _T("0.001");
	CString Y = _T("0.001");
	CString Z = _T("0.001");
	CString strMPosCoordinate;
	CString strComma = _T(",");
	CString strColon = _T(":");
	int iFind_MPos = 0;
	int iFind_Comma = 0;
	int iFind_Colon = 0;
	int i = 0;

	for (;;)
	{
		if (dlg->m_Port.m_hComm == NULL)
		{
			dlg->m_ctrlAutoSend.SetCheck(0);
			AfxMessageBox(_T("串口没有打开，请打开串口."));
			return -1;
		}
		else
		{
			//UpdateData(TRUE);
			if (!dlg->m_ctrlHexSend.GetCheck())
			{
				dlg->m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
				TX_count += strSendData.GetLength();
			}
			strTemp.Format(_T("TX:%d"), TX_count);
			dlg->m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
		}
		//dlg->m_CoordinateAccess = _T("<Idle,MPos:1.000,0.000,0.000,WPos:0.000,0.000,0.000>");
		//dlg->m_CoordinateAccess = dlg->m_ReceiveData;
		strReceiveData = dlg->m_ReceiveDataCoordinateAccess;
		iFind_MPos = strReceiveData.Find(_T("MPos"));
		if (iFind_MPos >= 0)
		{
			//iFind_Comma
			strMPosCoordinate = strReceiveData.Mid(iFind_MPos, (strReceiveData.GetLength() - 1));
			while ((iFind_Comma = strMPosCoordinate.Find(strComma)) && i < 3)
			{
				switch (i)
				{
				case 0:
					iFind_Colon = strMPosCoordinate.Find(strColon);
					X = strMPosCoordinate.Mid((iFind_Colon + 1), (iFind_Comma - (iFind_Colon + 1)));
					iFind_Comma = strMPosCoordinate.Find(strComma);
					strMPosCoordinate = strMPosCoordinate.Mid((iFind_Comma + 1), (strMPosCoordinate.GetLength() - 1));
					break;
				case 1:
					iFind_Comma = strMPosCoordinate.Find(strComma);
					Y = strMPosCoordinate.Mid(0, iFind_Comma);
					strMPosCoordinate = strMPosCoordinate.Mid((iFind_Comma + 1), (strMPosCoordinate.GetLength() - 1));
					break;
				case 2:
					iFind_Comma = strMPosCoordinate.Find(strComma);
					Z = strMPosCoordinate.Mid(0, iFind_Comma);
					strMPosCoordinate = strMPosCoordinate.Mid((iFind_Comma + 1), (strMPosCoordinate.GetLength() - 1));
					break;
				default:
					break;
				}
				i++;
			}
		}

		dlg->GetDlgItem(IDC_EDIT_X_COORDINATE)->SetWindowText(X);
		dlg->GetDlgItem(IDC_EDIT_Y_COORDINATE)->SetWindowText(Y);
		dlg->GetDlgItem(IDC_EDIT_Z_COORDINATE)->SetWindowText(Z);



		dlg->m_ReceiveDataCoordinateAccess.Empty();
		dlg->GetDlgItem(IDC_EDIT_COORDINATE)->SetWindowText(_T(""));
		i = 0;
		Sleep(2000);
	}
	return 0;
}


BOOL CSerialPortApplicationDlg::StartCoordinateAccessMonitoring()
{
	if (!(m_DlgThread = AfxBeginThread(CoordinateAccessThread, this)))
		return FALSE;
	TRACE("Coordinate Access Thread started\n");
	return TRUE;
}

BOOL CSerialPortApplicationDlg::RestartCoordinateAccessMonitoring()
{
	TRACE("Coordinate Access Thread resumed\n");
	m_DlgThread->ResumeThread();
	return TRUE;
}

BOOL CSerialPortApplicationDlg::StopCoordinateAccessMonitoring()
{
	TRACE("Coordinate Access Thread suspended\n");
	m_DlgThread->SuspendThread();
	return TRUE;
}


char CSerialPortApplicationDlg::HexChar(char c)
{
	if ((c >= '0') && (c <= '9'))
		return c - 0x30;
	else if ((c >= 'A') && (c <= 'F'))
		return c - 'A' + 10;
	else if ((c >= 'a') && (c <= 'f'))
		return c - 'a' + 10;
	else
		return 0x10;
}

//将一个字符串作为十六进制串转化为一个字节数组，字节间可用空格分隔，
//返回转换后的字节数组长度，同时字节数组长度自动设置。
int CSerialPortApplicationDlg::Str2Hex(CString str, char* data)
{
	int t, t1;
	int rlen = 0, len = str.GetLength();
	//data.SetSize(len/2);
	for (int i = 0; i<len;)
	{
		char l, h = str[i];
		if (h == ' ')
		{
			i++;
			continue;
		}
		i++;
		if (i >= len)
			break;
		l = str[i];
		t = HexChar(h);
		t1 = HexChar(l);
		if ((t == 16) || (t1 == 16))
			break;
		else
			t = t * 16 + t1;
		i++;
		data[rlen] = (char)t;
		rlen++;
	}
	return rlen;

}

// CSerialPortApplicationDlg message handlers
BOOL CSerialPortApplicationDlg::OnInitDialog()
{
	BOOL b = CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_nBaud = 9600;
	m_nCom = 3;
	m_cParity = _T('N');
	m_nDatabits = 8;
	m_nStopbits = 1;
	m_dwCommEvents = EV_RXFLAG | EV_RXCHAR;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		m_Port.StartMonitoring();
		strStatus.Format(_T("STATUS：COM%d OPENED，%d,%c,%d,%d"), m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);

		//"当前状态：串口打开，无奇偶校验，8数据位，1停止位");
	}
	else
	{
		AfxMessageBox(_T("没有发现此串口."));
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
	m_ctrlPortStatus.SetWindowText(strStatus);

	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CYCLETIME);
	CString strText;
	strText.Format(_T("%d"), m_nCycleTime);
	pEdit->SetWindowText(strText);   //Display cycle time

	m_strSendData = _T("?\n");
	char cr = 13, lf = 10;;
	//m_strSendData+=(char)cr+lf;
	//m_strSendData = cr+lf;

	m_ctrlAutoClear.SetCheck(1);
	m_ctrlEditSendFile.SetWindowText("No File Selected!");

	m_Com.SetCurSel(0);
	m_Speed.SetCurSel(5);
	m_Parity.SetCurSel(0);
	m_DataBits.SetCurSel(0);
	m_StopBits.SetCurSel(0);

	m_Step.SetCurSel(0);
	m_strStep = _T("1");
	//m_animIcon.SetImageList(IDB_ANIM_IMGLIST, 4, RGB(0, 0, 0));
	SetTimer(4, 200, NULL);

	StartCoordinateAccessMonitoring();
	StopCoordinateAccessMonitoring();

	UpdateData(FALSE);

	ShowWindow(SW_SHOW);

	return b;  // return TRUE  unless you set the focus to a control
}

void CSerialPortApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSerialPortApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSerialPortApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


afx_msg LRESULT CSerialPortApplicationDlg::OnCoordinateAccess(WPARAM ch, LPARAM port)
{
	if (port <= 0 || port > 4)
		return -1;
	CString str;
	if (m_ctrlHexReceieve.GetCheck())
		str.Format("%02X ", ch);
	else
		str.Format("%c", ch);
	int nLen = m_ctrlReceiveDataCoordinateAccess.GetWindowTextLength();
	m_ctrlReceiveDataCoordinateAccess.SetSel(nLen, nLen);
	m_ctrlReceiveDataCoordinateAccess.ReplaceSel(str);
	nLen += str.GetLength();

	m_ReceiveDataCoordinateAccess += str;
	//m_CoordinateAccess += str;
	return 0;
}

static long rxdatacount = 0;//该变量用于接收字符计数
afx_msg LRESULT CSerialPortApplicationDlg::OnCommunication(WPARAM ch, LPARAM port)
{
	if (port <= 0 || port > 4)
		return -1;
	rxdatacount++;//接收的字节计数
	CString strTemp;
	strTemp.Format("%ld", rxdatacount);
	strTemp = "RX : " + strTemp;
	m_ctrlRXCOUNT.SetWindowText(strTemp);

	if (m_bStopDispRXData)
		return -1;
	//若设置了“自动清空”，则达到50行后，自动清空接收编辑框中显示的数据
	if ((m_ctrlAutoClear.GetCheck()) && (m_ctrlReceiveData.GetLineCount() >= 50))
	{
		m_ReceiveData.Empty();
		UpdateData(FALSE);
	}
	//如果没有“自动清空”，数据行达到400后，也自动清空
	//因为数据过多，影响接收速度，显示是最费CPU时间的操作
	if (m_ctrlReceiveData.GetLineCount() > 400)
	{
		m_ReceiveData.Empty();
		m_ReceiveData = "***Too long, Emptied Automaticly...\r\n";
		UpdateData(FALSE);
	}
	//如果选择了"十六进制显示"，则显示十六进制值
	CString str;
	if (m_ctrlHexReceieve.GetCheck())
		str.Format("%02X ", ch);
	else
		str.Format("%c", ch);
	//以下是将接收的字符加在字符串的最后，这里费时很多
	//但考虑到数据需要保存成文件，所以没有用List Control
	int nLen = m_ctrlReceiveData.GetWindowTextLength();
	m_ctrlReceiveData.SetSel(nLen, nLen);
	m_ctrlReceiveData.ReplaceSel(str);
	nLen += str.GetLength();

	m_ReceiveData += str;

	return 0;
}


void CSerialPortApplicationDlg::OnButtonClearReciArea()
{
	// TODO: Add your control notification handler code here
	m_ReceiveData.Empty();
	UpdateData(FALSE);
}


void CSerialPortApplicationDlg::OnButtonOpenport()
{
	// TODO: Add your control notification handler code here
	m_bOpenPort = !m_bOpenPort;
	if (m_bOpenPort)
	{
		if (m_ctrlAutoSend.GetCheck())
		{
			m_bOpenPort = !m_bOpenPort;
			AfxMessageBox("请先关闭自动发送.");
			return;
		}
		if (m_ctrlAutoSendCoordinateAccess.GetCheck())
		{
			m_bOpenPort = !m_bOpenPort;
			AfxMessageBox("请先关闭自动坐标访问.");
			return;
		}

		m_ctrlOpenPort.SetWindowText("OPEN_PORT");
		m_Port.ClosePort();
		m_ctrlPortStatus.SetWindowText("STATUS : COM Port Closed");
	}
	else
	{
		m_ctrlOpenPort.SetWindowText("CLOSE_PORT");
		CString strStatus;
		if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
		{
			m_Port.StartMonitoring();
			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			AfxMessageBox("没有发现此串口或被占用.");
		}
		m_ctrlPortStatus.SetWindowText(strStatus);
	}
}


void CSerialPortApplicationDlg::OnButtonStopdisp()
{
	// TODO: Add your control notification handler code here
	m_bStopDispRXData = !m_bStopDispRXData;
	if (m_bStopDispRXData)
		m_ctrlStopDisp.SetWindowText("Continue...");
	else
		m_ctrlStopDisp.SetWindowText("Stop...");
}


void CSerialPortApplicationDlg::OnButtonManualsend()
{
	// TODO: Add your control notification handler code here
	int nLength;
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (m_ctrlHexSend.GetCheck())
		{
			char data[512];
			int len = Str2Hex(m_strSendData, data);
			m_Port.WriteToPort(data, len);
			TX_count += (long)((m_strSendData.GetLength() + 1) / 3);
		}
		else
		{
			nLength = m_strSendData.GetLength();
			//nLength = 150;
			if (nLength > 100)
			{
				if (!(m_DlgWritePortThread = AfxBeginThread(WriteToPortThread, this)))
					return;
				TRACE("Port Access Thread started\n");
			}
			else
			{
				m_strSendData += _T("\n");
				m_Port.WriteToPort((LPCTSTR)m_strSendData);	//发送数据
				TX_count += m_strSendData.GetLength();
			}
			//m_Port.WriteToPort((LPCTSTR)m_strSendData);	//发送数据
			//TX_count += m_strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnTimer(UINT_PTR nIDEvent)
{
	CString strStatus;
	switch (nIDEvent)
	{
	case 1://手动发送
		OnButtonManualsend();
		break;
	case 2:
		KillTimer(2);
		break;
	case 3:
		m_ctrlManualSend.EnableWindow(TRUE);
		m_ctrlAutoSend.EnableWindow(TRUE);
		m_ctrlAutoSendCoordinateAccess.EnableWindow(TRUE);
		m_ctrlSendFile.EnableWindow(TRUE);
		m_strSendFilePathName = m_strTempSendFilePathName;
		m_ctrlEditSendFile.SetWindowText(m_strSendFilePathName);//m_strSendFilePathName
		KillTimer(3);
		if (!(m_ctrlAutoSend.GetCheck()) && !(m_ctrlAutoSendCoordinateAccess.GetCheck()))
		{
			if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
			{
				m_Port.StartMonitoring();
				strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
				//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			}
			else
			{
				AfxMessageBox("Failed to reset send buffer size!");
				//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			}
			m_ctrlPortStatus.SetWindowText(strStatus);
		}
		break;
	case 4:
		break;
	default:
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CSerialPortApplicationDlg::OnChangeEditCycletime()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_CYCLETIME);
	CString strText;
	pEdit->GetWindowText(strText);
	m_nCycleTime = atoi(strText);
}


void CSerialPortApplicationDlg::OnButtonClearrecasenda()
{
	// TODO: Add your control notification handler code here
	m_strSendData.Empty();
	UpdateData(FALSE);
}


void CSerialPortApplicationDlg::OnCheckAutosend()
{
	// TODO: Add your control notification handler code here
	m_bAutoSend = !m_bAutoSend;
	if (m_bAutoSend)
	{
		if (m_Port.m_hComm == NULL)
		{
			m_bAutoSend = !m_bAutoSend;
			m_ctrlAutoSend.SetCheck(0);
			AfxMessageBox("串口没有打开，请打开串口.");
			return;
		}
		else
			SetTimer(1, m_nCycleTime, NULL);
	}
	else
	{
		KillTimer(1);
	}
}


void CSerialPortApplicationDlg::OnChangeEditSend()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	UpdateData(TRUE);
}


void CSerialPortApplicationDlg::OnSelendokComboComselect()
{
	// TODO: Add your control notification handler code here
	if (m_Port.m_hComm != NULL)
	{
		m_Port.ClosePort();
	}

	m_nCom = m_Com.GetCurSel() + 1;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		if (!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS：COM%d CLOSED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
		AfxMessageBox("没有发现此串口或被占用.");
	}
}


void CSerialPortApplicationDlg::OnSelendokComboSpeed()
{
	// TODO: Add your control notification handler code here
	CString temp;
	int i = m_Speed.GetCurSel();
	switch (i)
	{
	case 0:
		i = 300;
		break;
	case 1:
		i = 600;
		break;
	case 2:
		i = 1200;
		break;
	case 3:
		i = 2400;
		break;
	case 4:
		i = 4800;
		break;
	case 5:
		i = 9600;
		break;
	case 6:
		i = 19200;
		break;
	case 7:
		i = 38400;
		break;
	case 8:
		i = 43000;
		break;
	case 9:
		i = 56000;
		break;
	case 10:
		i = 57600;
		break;
	case 11:
		i = 115200;
		break;
	default:
		break;

	}
	m_nBaud = i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		if (!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);


			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS：COM%d CLOSED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("没有成功，请重试");
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}


void CSerialPortApplicationDlg::OnSelendokComboParity()
{
	// TODO: Add your control notification handler code here
	char temp;
	int i = m_Parity.GetCurSel();
	switch (i)
	{
	case 0:
		temp = 'N';
		break;
	case 1:
		temp = 'O';
		break;
	case 2:
		temp = 'E';
		break;
	}
	m_cParity = temp;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		if (!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS：COM%d CLOSED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("没有成功，请重试");
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}


void CSerialPortApplicationDlg::OnSelendokComboDatabits()
{
	// TODO: Add your control notification handler code here
	int i = m_DataBits.GetCurSel();
	switch (i)
	{
	case 0:
		i = 8;
		break;
	case 1:
		i = 7;
		break;
	case 2:
		i = 6;
		break;
	}
	m_nDatabits = i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		if (!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS：COM%d CLOSED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("没有成功，请重试");
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}


void CSerialPortApplicationDlg::OnSelendokComboStopbits()
{
	// TODO: Add your control notification handler code here
	int i = m_StopBits.GetCurSel();
	switch (i)
	{
	case 0:
		i = 1;
		break;
	case 1:
		i = 2;
		break;
	}
	m_nStopbits = i;
	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, 512))
	{
		if (!m_bOpenPort)
		{
			m_Port.StartMonitoring();
			//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
			strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		else
		{
			//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
			strStatus.Format("STATUS：COM%d CLOSED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		}
		m_ctrlPortStatus.SetWindowText(strStatus);

	}
	else
	{
		AfxMessageBox("没有成功，请重试");
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
}


void CSerialPortApplicationDlg::OnButtonSavedata()
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	int		nLength;
	nLength = m_strCurPath.GetLength();

	for (int nCount = 0; nCount < nLength; nCount++)
	{
		if (m_strCurPath.GetAt(nCount) == '\\')
			CreateDirectory(m_strCurPath.Left(nCount + 1), NULL);
	}
	CreateDirectory(m_strCurPath, NULL);

	CFile m_rFile;
	LPCSTR	lpszPath = m_strCurPath;// "c:\\comdata";
	SetCurrentDirectory(lpszPath);

	//文件名为Rec**.txt,以下代码自动检测文件名是否存在，若存在，则后面序号自动递增
	//如Rec00.txt Rec01.txt,程序自动为正要保存的文件命名为Rec02.txt.
	char buf[20];
	for (int j = 0; j<100; j++)
	{
		sprintf(buf, "Rec%02d.txt", j);
		if ((_access(buf, 0)) == -1)
			break;
	}

	if (!m_rFile.Open(buf, CFile::modeCreate | CFile::modeWrite))
	{
		AfxMessageBox("创建记录文件失败！");
		return;
	}
	if ((_access(buf, 0)) == -1)
	{
		AfxMessageBox("failed");
		return;
	}
	CTime t = CTime::GetCurrentTime();
	CString str = t.Format("%Y年%m月%d日%H时%M分%S秒\r\n");
	m_rFile.Write((LPCTSTR)str, str.GetLength());
	m_rFile.Write((LPCTSTR)m_ReceiveData, m_ReceiveData.GetLength());
	m_rFile.Flush();
	m_rFile.Close();

	str = "OK,";
	for (int i = 0; i<5; i++)
		str += buf[i];
	str += ".txt saved";
	m_ctrlSavePath.SetWindowText(str);
	SetTimer(2, 5000, NULL);   //在定时器中显示保存文件状态
}


void CSerialPortApplicationDlg::OnButtonDirbrowser()
{
	// TODO: Add your control notification handler code here
	static char displayname[MAX_PATH];
	static char path[MAX_PATH];
	LPITEMIDLIST pidlBrowse;    // PIDL selected by user 
	BROWSEINFO bi;
	bi.hwndOwner = this->m_hWnd;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = displayname;
	bi.lpszTitle = _T("请选择要保存接收数据的文件夹");
	bi.ulFlags = BIF_EDITBOX;
	bi.lpfn = NULL;
	pidlBrowse = SHBrowseForFolder(&bi);
	if (pidlBrowse != NULL)
	{
		SHGetPathFromIDList(pidlBrowse, path);
	}
	CString str = path;  //得到路径
	if (str.IsEmpty()) return;  //如果没有选择，就返回
	m_strCurPath = str;	//接收路径编辑框对应变量
	UpdateData(FALSE);
}


void CSerialPortApplicationDlg::OnButtonSendfile()
{
	// TODO: Add your control notification handler code here
	CFile fp;
	if (!(fp.Open((LPCTSTR)m_strSendFilePathName, CFile::modeRead)))
	{
		AfxMessageBox("Open file failed!");
		return;
	}
	fp.SeekToEnd();
	unsigned long fplength = fp.GetLength();
	m_nFileLength = fplength;
	char* fpBuff;
	fpBuff = new char[fplength];
	fp.SeekToBegin();
	if (fp.Read(fpBuff, fplength)<1)
	{
		fp.Close();
		return;
	}
	fp.Close();

	CString strStatus;
	if (m_Port.InitPort(this, m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits, m_dwCommEvents, fplength))
	{
		m_Port.StartMonitoring();
		strStatus.Format("STATUS：COM%d OPENED，%d,%c,%d,%d", m_nCom, m_nBaud, m_cParity, m_nDatabits, m_nStopbits);
		//m_ctrlIconOpenoff.SetIcon(m_hIconRed);
		m_bSendFile = TRUE;
		m_strTempSendFilePathName = m_strSendFilePathName;
		m_ctrlEditSendFile.SetWindowText("正在发送......");
		//发送文件时，以下功能不能使用
		m_ctrlManualSend.EnableWindow(FALSE);
		m_ctrlAutoSend.EnableWindow(FALSE);
		m_ctrlAutoSendCoordinateAccess.EnableWindow(FALSE);
		m_ctrlSendFile.EnableWindow(FALSE);
		m_Port.WriteToPort((LPCTSTR)fpBuff, fplength);
	}
	else
	{
		AfxMessageBox("Failed to send file!");
		//m_ctrlIconOpenoff.SetIcon(m_hIconOff);
	}
	delete fpBuff;
}


void CSerialPortApplicationDlg::OnButtonCountreset()
{
	// TODO: Add your control notification handler code here
	rxdatacount = 0;
	CString strTemp;
	strTemp.Format("%ld", rxdatacount);
	strTemp = "RX:" + strTemp;
	m_ctrlRXCOUNT.SetWindowText(strTemp);
	TX_count = 0;
	strTemp.Format("%ld", TX_count);
	strTemp = "TX:" + strTemp;
	m_ctrlTXCount.SetWindowText(strTemp);
}


void CSerialPortApplicationDlg::OnButtonFilebrowser()
{
	// TODO: Add your control notification handler code here
	LPCSTR	lpszPath = "c:\\comdata";
	SetCurrentDirectory(lpszPath);
	static char BASED_CODE szFilter[] = "文本文件(*.txt)|*.txt|所有文件(*.*)|*.*||";

	CFileDialog FileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		szFilter);
	FileDlg.m_ofn.lpstrInitialDir = lpszPath;

	if (FileDlg.DoModal() == IDOK)
	{
		CString strFileName = FileDlg.GetFileName();
		CString strFileExt = FileDlg.GetFileExt();
		CString lpstrName = FileDlg.GetPathName();
		m_strSendFilePathName = lpstrName;
		UpdateData(FALSE);
	}
}


void CSerialPortApplicationDlg::OnButtonClose()
{
	// TODO: Add your control notification handler code here
	CSerialPortApplicationDlg::OnOK();
}

void CSerialPortApplicationDlg::OnDestroy()
{
	CDialog::OnDestroy();
	m_ctrlAutoSend.SetCheck(0);  //强行关闭自动发送
	m_ctrlAutoSendCoordinateAccess.SetCheck(0);
	KillTimer(1);   //关闭定时器
	KillTimer(4);
	m_Port.ClosePort();  //关闭串口
	m_ReceiveData.Empty();  //清空接收数据字符串
}

void CSerialPortApplicationDlg::OnCbnSelendokComboStep()
{
	// TODO: Add your control notification handler code here
	CString temp;
	int i = m_Step.GetCurSel();
	m_strStep = "1";
	switch (i)
	{
	case 0:
		m_strStep = "1";
		break;
	case 1:
		m_strStep = "2";
		break;
	case 2:
		m_strStep = "3";
		break;
	case 3:
		m_strStep = "4";
		break;
	case 4:
		m_strStep = "5";
		break;
	case 5:
		m_strStep = "10";
		break;
	case 6:
		m_strStep = "20";
		break;
	default:
		m_strStep = "1";
		break;
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonXInc()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 X";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonXDec()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 X-";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonYInc()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 Y";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonYDec()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 Y-";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonZInc()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 Z";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedButtonZDec()
{
	// TODO: Add your control notification handler code here
	CString strSendData = "G91 G01 Z-";
	strSendData += m_strStep;
	strSendData += "\n";
	if (m_Port.m_hComm == NULL)
	{
		m_ctrlAutoSend.SetCheck(0);
		AfxMessageBox("串口没有打开，请打开串口.");
		return;
	}
	else
	{
		UpdateData(TRUE);
		if (!m_ctrlHexSend.GetCheck())
		{
			m_Port.WriteToPort((LPCTSTR)strSendData);	//发送数据
			TX_count += strSendData.GetLength();
		}
		CString strTemp;
		strTemp.Format("TX:%d", TX_count);
		m_ctrlTXCount.SetWindowText(strTemp);//将发送的数量在TX发送文本框中显示
	}
}


void CSerialPortApplicationDlg::OnBnClickedCheckCoordinate()
{
	// TODO: Add your control notification handler code here
	m_bAutoSendCoordinateAccess = !m_bAutoSendCoordinateAccess;
	if (m_bAutoSendCoordinateAccess)
	{
		if (m_Port.m_hComm == NULL)
		{
			m_bAutoSendCoordinateAccess = !m_bAutoSendCoordinateAccess;
			m_ctrlAutoSend.SetCheck(0);
			AfxMessageBox("串口没有打开，请打开串口.");
			return;
		}
		else
			RestartCoordinateAccessMonitoring();
	}
	else
	{
		StopCoordinateAccessMonitoring();
	}
}
