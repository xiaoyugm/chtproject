// qqhappyfarmstructure.h: 
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_)
#define AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef MAX_PACK
#define MAX_PACK	10240*10240
#endif

//////////////////////////////////////////////////////////////////////////

//#define QQ_HOST _T("http://happyfarm.qzone.qq.com")		//��������ַ

#define MAX_POINT_NUMBER     15001       //������  1-15000
#define COLOR_MASK	RGB(0x00,0x80,0x80)
#define MAX_FDS      61                  //����վ  60 +1
#define MAX_CHAN     25                  //ÿ��վ���ͨ��  24 +1   16AD 8C
// Define use when allocating the buffer to send a file part
#define BUFFER_SIZE 1024

#define MAX_ROW     400  //������� 50

struct CPointInfo
{
        unsigned char  lWarn_state;
        unsigned short lufdata;
		double         ldfValue;
		double         fMin;
		double         fMax;
		double         unWarnMin;
		double         unWarnMax;
		double         pnValue;
		CString        usUnit;
		CString        strExplaintemp;
		CString        strWarnCausetemp;
		CString        strWarnTime;
///		CString strWarn;
		CString        strWarnDate;
};

struct CWarnPoint
{
        unsigned short  warnPoint;
        unsigned short  OldwarnPoint;
       	unsigned char OldWarn_state;
};

struct CStrWarn{
	int m_SlaveStation;                     // ��վ��
	int m_NumChannel;                     	//ͨ����
	CString locationname;                       //��װ�ص�/����
	CString strValue;                       //���ֵ
	CString warnTime;                       //����ʱ��
	CString breakTime;                        //�ϵ�ʱ��
	CString restoreTime;                        //����ʱ��
	CString feedStatus;                        //����״̬
	CString feedTime;                        //����ʱ��
	CString safetyprecautions;                        //��ȫ��ʩ
};




//////////////////////////////////////////////////////////////////////////
//��ṹ
struct DTypeTField	 {
	CString     DID;                      //ģ��������������id
	CString Name;                    //ģ����������������������   
	CString ptype;	                  	//������
	CString name0;	                	//������
	CString name1;	               //�߱���ֵ
	CString name2;	              //�ͱ���ֵ
	CString     palms;	                 //���������Ͷϵ�ֵ
	CString falm;                    //
	CString fdel;		        // (����)��λ
	CString recdate;		        // (����)��λ
	CString deldate;		        // (����)��λ
	CString Useridadd;		        // (����)��λ
	CString Useriddel;		        // (����)��λ

	CString ltop;	                  	//������
	CString lbom;	                	//������
	CString palmu;	               //�߱���ֵ
	CString palmd;	              //�ͱ���ֵ
	CString pbrk;	                 //ģ�������Ͷϵ�ֵ
	CString prtn;	                 //ģ�������͸���ֵ
	CString punit;		        // (����)��λ
	CString pico;                    //
//���������
	CString     pointnum;                       //���
	CString     utype;	                	//���������ͣ�0�ǵ����ͣ�1��Ƶ���ͣ�
	CString     typeID;	                        //����ID
	CString     positionid;	                    //λ��ID
	CString     fds;	                    //������ڷ�վ
	CString     chan;                       //�������ͨ��
	CString     subOpr;                     //������־
};
struct DTypeTFD	 {
//����������
//��װ�ص��
	CString     DID;                      //ģ��������������id
	CString Name;                    //ģ����������������������   
	CString ptype;	                  	//����������  ������ͣ�0��ģ������1�ǿ�������
	CString name0;	                	//0̬����
	CString name1;	                    //1̬����
	CString name2;	                    //2̬����
	CString     palms;	                 //���������ͱ���״̬
	CString falm;                    //��������
	CString fdel;		           // ɾ����־
	CString recdate;		        // ��¼ʱ��
	CString deldate;		        // ɾ��ʱ��
	CString Useridadd;		        // ��Ӳ����û�
	CString Useriddel;		        // ɾ�������û�

//ģ��������
	CString ltop;	                  	//������
	CString lbom;	                	//������
	CString palmu;	                    //�߱���ֵ
	CString palmd;	                    //�ͱ���ֵ
	CString pbrk;	                    //ģ�������Ͷϵ�ֵ
	CString prtn;	                    //ģ�������͸���ֵ
	CString punit;		                // (����)��λ
	CString pico;                       //ͼ����

//���������
	CString     pointnum;                       //���
	CString     utype;	                	//���������ͣ�0�ǵ����ͣ�1��Ƶ���ͣ�
	CString     typeID;	                        //����ID
	CString     potioinid;	                    //λ��ID
	CString     fds;	                    //������ڷ�վ
	CString     chan;                       //�������ͨ��
	CString     subOpr;                     //������־
};


struct ADTypeTable	 {
	CString TableName;                     //����   
	CString NameD;                         //����������   
	DTypeTField        m_DTypeTField;      //ģ�������������ͽṹ
	DTypeTFD        m_DTypeTFD;            //ģ������������������
};

//���Ʊ�
//��������
//��У�����
//�û���


//������ʾ������  
struct ADMainDis	 {
	int     m_ATotalnum;	                 //ģ����0-24����ֵ����           ����/�ϵ����
	float   ATotalV;	        	         //ģ����0-24����ֵ
	int     duant;                           //�Ƿ�ĳ��ʱ��
	float   AavV;	        	             //ģ����ƽ��ֵ
	float   AMinValue;	                     //ģ������Сֵ     
	float   AMaxValue;	                     //ģ�������ֵ                   ��n�����ֵ
	COleDateTime  AMaxTime;                  //ģ�������ֵʱ��               ��n�����ֵʱ��
	COleDateTime  ATime;                     //��󱨾����ֵʱ��             �ۼƱ���ʱ��/�����쳣ʱ��
	COleDateTime  NTime;                     //����������ֵʱ��   ��ʩʱ��  ��ʼ
	COleDateTime  BTime;                     //���ϵ���ֵʱ��             ��ֹ
	COleDateTime  RTime;                     //��󸴵���ֵʱ��   ����ʱ��  ��ʩʱ��
	CString     strsafetext;                                                //��ʩ         
	CString     strlocal;                                                   //�ϵ�����|����״̬|ʱ��  
	int     havev; 
	COleDateTimeSpan tmid;
};

//�ձ�/�౨��ͷ�ַ���
struct CommonStr	 {
	CString strc[150];                               
};

//������5���ӱ仯
struct DCHm5	 {
	DCHm5(const CString& str1, const CString& str2,const CString& str3, const CString& str4 )
		:str1(str1)
		,str2(str2)
		,str3(str3)
		,str4(str4)
	{}
	CString str1;
	CString str2;
	CString str3;
	CString str4;
};


struct ListV {
	CString   strl;          // list dian hao
};
struct DIDVer {
	int   n_iddf;          // list dian hao
};

struct SListstatus {
	unsigned char   oldstate;          // list zhuangtai
};

//////////////////////////////////////////////////////////////////////////
//ADC�ϵ�    ����
struct ADCbreakE	 {
	int     bFSd;	                        //��վ  
	int     bchanel;                        //������ͨ��     ����ͨ��
	CString adpoint;                        //AD     ���������         
	CString cpoint;                         //C      ���������
	CString CName;                          //��������㰲װ�ص�����   
};

//�������ӷ�վ   ��ɫ����    ���������硢�ϵ��list0--n��Ӧ��
struct SerialF	 {
	int     SFSd;	                        //��վ  ��ɫֵ
	int     cfds;	                        //��վ 
	int     cchan;	                        //����ͨ��
	int     ffds;	                        //��վ 
	int     fchan;	                        //����ͨ��
};
struct RT60DATA	 {
	unsigned char   rtdata[44]; 
};
//ͨ����
//struct NumChannel {
//	int EFeed;                  	//����״̬
//	int EquipmentState;             //�豸״̬
//};
//��վ
struct SlaveStation {
	int     m_PID;	                        //���  
	int     ptype;                   //����������
	COleDateTime  ValueTime;              //�ɼ����ֵʱ��   
	CString falma;                  //��������
	CString WatchName;              //��㰲װ�ص�����   
	CString strPN;                  //����� 01A01  
	CString         utype;           //������/ģ������������
    unsigned char   Channel_state;        //ͨ��״̬   0000 ���� 0001:����      

	float AValue;	                 //ģ������ǰֵ
	float m_RangeH;	        	     //������
	float m_RangeL;	        	     //������
	float AlarmValueH;	             //�߱���ֵ
	float AlarmValueL;	             //�ͱ���ֵ
	float Apbrk;	                 //ģ�������Ͷϵ�ֵ
	float Aprtn;	                 //ģ�������͸���ֵ
	CString m_Unit;		             // (����)��λ
    unsigned char       pnValue;        //ģ�����ٷֱ�ֵ

	int    CValue;	                    //������/Ƶ��/���֣�ģ�⣩ ��ǰֵ  0ͨ����ֱ��
	int AlarmState;	            //����״̬              0ͨ�����ϱ���
	CString ZeroState;          //0̬   ������
	CString OneState;           //1̬   ������
	CString TwoState;           //2̬   ������

	CString FeedState;           //����״̬
	CString strSafe;             //��ȫ��ʩ
	CString strBS;		             // �ϵ緶Χ

	unsigned char  RangeH8;                    //0ͨ������������λ
	unsigned char  RangeL8;                    //0ͨ������������λ
	unsigned char  AValueH8;
	unsigned char  AValueL8;
	unsigned char  ApbrkH8;
	unsigned char  ApbrkL8;
	unsigned char  AprtnH8;
	unsigned char  AprtnL8;
    unsigned char  Control_state;        //������״̬
	unsigned char  Channel8;             //����������+ģ��/����(ͨ������

    unsigned char   Adjust_state;        //��У״̬
    int   m_second;            //�ڶ��β�����
    unsigned char   m_ffds;              //�����վ
    unsigned char   m_fchan;             //����ͨ��

    CTime   m5_T;                //��������ݴ洢ʱ��
	float m5_AMaxValue;	                 //ģ�������ֵ
	float m5_AMinValue;	                 //ģ������Сֵ
	float m5_ATotalValue;	                 //ģ������������ݴ洢ֵ
    int   m5_Atotal;                      //��������ݴ洢����

    CTime   m24_T;                //24Сʱ���ݴ洢ʱ��
	float m24_AMaxValue;	                 //24Сʱģ�������ֵ
	float m24_AMinValue;	                 //24Сʱģ������Сֵ
	float m24_ATotalValue;	                 //ģ����24Сʱ���ݴ洢ֵ
    int   m24_Atotal;                      //24Сʱ���ݴ洢����
};

//IP
struct OthersSetting {
	int           Port;                     //�˿ں�
//	int       numFormView;                  //FormView����
	CString   IP;	                        //IP��ַ   
	CString   DBname;	                        //���ݿ�����   
};

//DrawView
struct DrawView {
	CString   DrawViewName;          // FormView����
};

//View����
struct ViewWindows {
	int       numDrawView;                  //DrawView����
	int       numFormView;                  //FormView����
	CString   VWName;	                    //������������   
};

//ListCtrl ���ͽṹ
struct ListCtrl	 {
	CString   ListCtrlName;            // ListCtrl����
	bool      Visible;                 //ListCtrl�ɼ�
    bool      SubclassHeader;	        //�б�ͷ����  
	int       MoveWindowx;             //ListCtrl���
	int       SetWindowPosX;           //ListCtrl��
	int       SetWindowPosY;           //ListCtrl��
	CString   ColumnHeading1;          //ListCtrlͷ����
	CString   ColumnHeading2;          //ListCtrlͷ����
	CString   ColumnHeading3;          //ListCtrlͷ����
	int       ColumnWidth1;            //ListCtrlͷ��   
	int       ColumnWidth2;            //ListCtrlͷ��   
	int       ColumnWidth3;            //ListCtrlͷ��   
	int       ColumniItem;             //ListCtrl����   
	COLORREF  BackColor;                //ListCtrl������ɫ
	COLORREF  TextColor;               //ListCtrl������ɫ          
	COLORREF  AlarmTextColor;           //ListCtrl����������ɫ
	COLORREF  AlarmBackColor;           //ListCtrl����������ɫ
	COLORREF  TextColor1;
	COLORREF  TextColor2;
};

//FormView
struct FormView {
	int       numForm;
	CString   FormViewName;          // FormView����
	ListCtrl  m_ListCtrl[3];         //FormView��ListCtrl���ݽṹ
};

//DisplayPoint �б���ʾ
struct DisplayPoint {
//	CString     CPName;                    //ģ����������������������   
	CString     CPpointnum;                       //���
	int         fds;             //��վ
	int         chan;            // ͨ��
	unsigned char      D_Chan_state;           //ģ��������������
};

//��̬ͼ��ʾ
struct DisplayDraw {
	int         fds;             //��վ
	int         chan;            // ͨ��
//	int         ptype;           //ģ��������������
};

#endif // !defined(AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_)
