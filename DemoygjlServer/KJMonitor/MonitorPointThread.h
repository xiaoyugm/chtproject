#if !defined(AFX_MONITORPOINTTHREAD_H__D4A8F7A4_2CFB_467C_A890_1ABD42D483B2__INCLUDED_)
#define AFX_MONITORPOINTTHREAD_H__D4A8F7A4_2CFB_467C_A890_1ABD42D483B2__INCLUDED_

#include "SQL\\SQLDirect.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MonitorPointThread.h : header file
//
#define MAXCOMMAND   2000
#define HIGHCOMMAND  1000
#define MEDIUMCOMMAND   500
#define  MINCOMMAND     100

#define	 SEQNUM	16
#define  MAXWAITLEN 20
#define   MAXSTEP   1
#define   MAXBLOCK 15 


/////////////////////////////////////////////////////////////////////////////
// CMonitorPointThread thread

#include "KJMonitor.h"
#include "FMMonitorPoint.h"
#include "monitorPointThread.h"
#include "OutputBar.h"
#include "Others\\soundbase.h"
#include "SQL\\String2DataType.h"	// Added by ClassView
#include "SQL\\sqldirect.h"

#include "Com\\SerialPort.h"
#include "SQL\\String2DataType.h"
#include "Controls\\XPStyleButtonST.h"
#include "Controls\\ThemeHelperST.h"


typedef struct trigSEQ {
  WORD   Point,Seq;
  int   Condition;
  BYTE PntStat;
 } TRIG;

  typedef struct tagDAYTIME {
  int    Hour;
  int    Minute;
  int    Month;
  int    Day;
  char    Daily;
  char    Active;
  UINT    Seqnum;
  } DAYTIME;

 typedef struct  tagCOMMAND1{
 
  int   command_type; 
  char  Para1[8];
  char  Para2[8];
  char  Para3[8];
  char  Para4[8];  
  } COMMAND1;

  typedef struct tagNSEQ {
  WORD    SPUnum;     //时序号
  BOOL    SPUhold;    //是否刮起
  BYTE    SPUprori;   //优先级
  unsigned int    num_of_command;

//   COMMAND1 command[2000];   //动态开辟 
  COMMAND1 *command;
  } NSEQ;

  typedef struct tagSTACK {
	WORD	seqnum;
	BYTE    seqevent;
//	BYTE	depth;
//    BYTE	id;
  } STACK;

  typedef struct tagSEQSTACK {
	STACK   seqstack[5];//4个可以执行的东西 
	BYTE	ptr;    
	BYTE    depth; //added by ljh
  } SEQSTACK;

class CMonitorPointThread : public CWinThread
{
	DECLARE_DYNCREATE(CMonitorPointThread)
protected:
	CMonitorPointThread();           // protected constructor used by dynamic creation
	COutputBar     m_wndOutputBar;

// Attributes
public:

// Operations
public:
	BOOL EndSequence();
	void AThreeCal(unsigned short m_usPointNoScanedNow, unsigned short ddata);
	void StatusD(unsigned short usPointNo );
	void StatusA(unsigned short m_usPoint ,unsigned char ucRXch);
	void CalA(unsigned short m_usPointNoScanedNow ,unsigned char ucRXch ,unsigned char ucRXAddr, unsigned char ucConvID );
	void SeqCtrl(BYTE trunck, BYTE addr, BYTE command);
//	void DoRefreshStatus(int iTrunk);
	CString GetAppPath();
	void CloseWarning();
	void DoPlayWarnSound(UINT uWarnNo);
	void WriteToWarnCauseRecord(unsigned char  CommStatus , unsigned short usPointNoNow);
	void WriteKeepTimeStr(unsigned short usPointNo, CString usKeepTime);
	void WriteCollectData(unsigned short pointno, unsigned short data);
	void ConnectDB();
	LPSTR GetDes(int mode,int command  );
	BOOL InitSequence();
	int chartoint(char *str);
	int CALL_SEQ(WORD Snum, BYTE event, BYTE id);
	void InsertSeq(int seqnum);
	void SeqSchedule();
	void Schedule();
	BOOL time_feg();
//	void DispWarning(unsigned short pointno);
	void DoRefreshPoint(unsigned short iTrunk,unsigned char ucSetDisp);
//	void Docomunication(int iTrunk);

//	CSQLDirect m_SQLDirect1;
	void SetKeepTime(unsigned short usPointNo);
	CString2DataType m_String2DataType;
	unsigned short m_usPointNoScanedNow;
	CSQLDirect m_SQLDirect;
	double ComputeValue(unsigned short ucRXch,double dfScopeMin,double dfScopeMax,UINT usPrecision);
//	unsigned char GetConvChannels(unsigned char ucConvID);
	void RefreshPoint(int iTrunk,unsigned char ucStatus);

	BOOL m_RepeatFlag;
    UINT uWarnNo1;
    unsigned short PointNow;
    UINT  PointNowCount;

	BOOL m_WChangeDate;
	BOOL m_ChangeStatus;
	BOOL m_ChangeDate;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMonitorPointThread)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CMonitorPointThread();

	// Generated message map functions
	//{{AFX_MSG(CMonitorPointThread)
//	afx_msg void OnBUTTONCloseSound();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONITORPOINTTHREAD_H__D4A8F7A4_2CFB_467C_A890_1ABD42D483B2__INCLUDED_)
