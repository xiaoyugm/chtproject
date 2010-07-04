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

#define QQ_HOST _T("http://happyfarm.qzone.qq.com")		//��������ַ

#define MAX_POINT_NUMBER     15001  //������  1-15000
#define COLOR_MASK	RGB(0x00,0x80,0x80)

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
	CString strPoint;                       //����ʱ��
	CString strDate;                        //�ϵ�ʱ��
	CString strTime;                        //����ʱ��
	CString strText;                        //����ʱ��
	CString strWarn;                        //��ȫ��ʩ
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



//////////////////////////////////////////////////////////////////////////
//ģ���� ���ͽṹ
struct AType	 {
	CString falma;                  //��������
	CString WatchName;              //��㰲װ�ص�����   
	float AValue;	                //ģ������ǰֵ
	float m_RangeH;	        	//������
	float m_RangeL;	        	//������
	float AlarmValueH;	        //�߱���ֵ
	float AlarmValueL;	        //�ͱ���ֵ
	float Apbrk;	                 //ģ�������Ͷϵ�ֵ
	float Aprtn;	                 //ģ�������͸���ֵ
	CString m_Unit;		        // (����)��λ
	CString         utype;           //ģ������������
};
//������ ���ͽṹ
struct DType	 {
	CString falmd;                  //��������
	CString WatchName;              //��㰲װ�ص�����   
	bool    DValue;	                    //��������ǰֵ  
	int AlarmState;	            //����״̬  
	CString ZeroState;          //0̬   ������
	CString OneState;           //1̬   ������
	CString TwoState;           //2̬   ������
	CString       utype;           //��������������
};

//ͨ����
//struct NumChannel {
//	int EFeed;                  	//����״̬
//	int EquipmentState;             //�豸״̬
//};
//��վ
struct SlaveStation {
	int FStyle;	                        //��վ����  
	int IsScan;	                        //�Ƿ�Ѳ��   
	AType        m_Atype;               //ģ���� ���ͽṹ
	DType        m_Dtype[3];            //������ ���ͽṹ
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

//DisplayPoint
struct DisplayPoint {
	CString     CPName;                    //ģ����������������������   
	CString     CPpointnum;                       //���
	int         fds;             //��վ
	int         chan;            // ͨ��
	int         ptype;           //ģ��������������
};

#endif // !defined(AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_)
