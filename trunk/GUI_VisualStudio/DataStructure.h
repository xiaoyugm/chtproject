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

#define QQ_HOST _T("http://happyfarm.qzone.qq.com")		//服务器地址

#define MAX_POINT_NUMBER     15001  //最大点数  1-15000
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
	int m_SlaveStation;                     // 分站号
	int m_NumChannel;                     	//通道号
	CString strPoint;                       //报警时刻
	CString strDate;                        //断电时刻
	CString strTime;                        //复电时刻
	CString strText;                        //馈电时刻
	CString strWarn;                        //安全措施
};




//////////////////////////////////////////////////////////////////////////
//表结构
//模拟量类型
//开关量类型
//安装地点表
struct DTypeTField	 {
	CString     DID;                      //模拟量开关量类型id
	CString Name;                    //模拟量开关量类型名称描述   
	CString ptype;	                  	//高量程
	CString name0;	                	//低量程
	CString name1;	               //高报警值
	CString name2;	              //低报警值
	CString     palms;	                 //开关量类型断电值
	CString falm;                    //
	CString fdel;		        // (计量)单位
	CString recdate;		        // (计量)单位
	CString deldate;		        // (计量)单位
	CString Useridadd;		        // (计量)单位
	CString Useriddel;		        // (计量)单位

	CString ltop;	                  	//高量程
	CString lbom;	                	//低量程
	CString palmu;	               //高报警值
	CString palmd;	              //低报警值
	CString pbrk;	                 //模拟量类型断电值
	CString prtn;	                 //模拟量类型复电值
	CString punit;		        // (计量)单位
	CString pico;                    //
};
struct DTypeTFD	 {
	CString     DID;                      //模拟量开关量类型id
	CString Name;                    //模拟量开关量类型名称描述   
	CString ptype;	                  	//高量程
	CString name0;	                	//低量程
	CString name1;	               //高报警值
	CString name2;	              //低报警值
	CString     palms;	                 //开关量类型断电值
	CString falm;                    //
	CString fdel;		        // (计量)单位
	CString recdate;		        // (计量)单位
	CString deldate;		        // (计量)单位
	CString Useridadd;		        // (计量)单位
	CString Useriddel;		        // (计量)单位

	CString ltop;	                  	//高量程
	CString lbom;	                	//低量程
	CString palmu;	               //高报警值
	CString palmd;	              //低报警值
	CString pbrk;	                 //模拟量类型断电值
	CString prtn;	                 //模拟量类型复电值
	CString punit;		        // (计量)单位
	CString pico;                    //

};

//测点描述表
struct PDescriptionTable	 {
	int     PID;                      //开关量类型id
	CString ptype;	                  	//高量程
	CString utype;	                	//低量程
	CString typeID;	               //高报警值
	CString potioinid;	              //低报警值
	int     fds;	                 //开关量类型断电值
	CString chan;                    //
	CString subOpr;                    //
	CString fdel;		        // (计量)单位
	CString recdate;		        // (计量)单位
	CString deldate;		        // (计量)单位
	CString Useridadd;		        // (计量)单位
	CString Useriddel;		        // (计量)单位
};


struct ADTypeTable	 {
	CString TableName;                //表名   
	CString NameD;                    //表名称描述   
//	ATypeTField        m_ATypeTField;      //模拟量 类型结构
//	ATypeTFD        m_ATypeTFD;      //模拟量 类型结构
	DTypeTField        m_DTypeTField;      //开关量类型结构
	DTypeTFD        m_DTypeTFD;      //开关量类型结构
	PDescriptionTable     m_PDescriptionTable;
};


//控制表


//馈电管理表


//调校管理表


//用户表



//////////////////////////////////////////////////////////////////////////
//模拟量 类型结构
struct AType	 {
	float m_RangeH;	        	//高量程
	float m_RangeL;	        	//低量程
	float AlarmValueH;	        //高报警值
	float AlarmValueL;	        //低报警值
	CString m_Unit;		        // (计量)单位
	CString WatchName;          //测点名称   
};
//开关量 类型结构
struct DType	 {
	int AlarmState;	            //报警状态  
	CString ZeroState;          //0态   开关量
	CString OneState;           //1态   开关量
	CString TwoState;           //2态   开关量
	CString WatchName;          //测点名称   
};

//通道号
struct NumChannel {
	int SensorType;                 // 传感器型号 3种 开关量无
	int AStyle;                 	//模拟量 类型
	float AValue;	                //模拟量当前值
	AType        m_Atype[100];      //模拟量 类型结构

	CString WatchPosition;          //安装地点
	int EFeed;                  	//馈电状态
	int EquipmentState;             //设备状态

	int DValue;	                    //开关量当前值  
	int DStyle;	                    //开关量 类型  
	DType        m_Dtype[100];      //开关量 类型结构
};
//分站
struct SlaveStation {
	int FStyle;	                        //分站类型  
	int IsScan;	                        //是否巡检   
	NumChannel        m_NumChan[65];    //通道
//	ST_FIELD_INFO  field_info;       	//这个人的植物信息
	
};

//IP
struct OthersSetting {
	int           Port;                     //端口号
//	int       numFormView;                  //FormView数量
	CString   IP;	                        //IP地址   
	CString   DBname;	                        //数据库名称   
};

//DrawView
struct DrawView {
	CString   DrawViewName;          // FormView名字
};

//View窗口
struct ViewWindows {
	int       numDrawView;                  //DrawView数量
	int       numFormView;                  //FormView数量
	CString   VWName;	                    //窗口类型名字   
};

//ListCtrl 类型结构
struct ListCtrl	 {
	CString   ListCtrlName;            // ListCtrl名字
	bool      Visible;                 //ListCtrl可见
    bool      SubclassHeader;	        //列表头黑体  
	int       MoveWindowx;             //ListCtrl起点
	int       SetWindowPosX;           //ListCtrl宽
	int       SetWindowPosY;           //ListCtrl高
	CString   ColumnHeading1;          //ListCtrl头名字
	CString   ColumnHeading2;          //ListCtrl头名字
	CString   ColumnHeading3;          //ListCtrl头名字
	int       ColumnWidth1;            //ListCtrl头宽   
	int       ColumnWidth2;            //ListCtrl头宽   
	int       ColumnWidth3;            //ListCtrl头宽   
	int       ColumniItem;             //ListCtrl行数   
	COLORREF  BackColor;                //ListCtrl背景颜色
	COLORREF  TextColor;               //ListCtrl文字颜色          
	COLORREF  AlarmTextColor;           //ListCtrl报警文字颜色
	COLORREF  AlarmBackColor;           //ListCtrl报警背景颜色
	COLORREF  TextColor1;
	COLORREF  TextColor2;
};

//FormView
struct FormView {
	int       numForm;
	CString   FormViewName;          // FormView名字
	ListCtrl  m_ListCtrl[3];         //FormView的ListCtrl数据结构
};


#endif // !defined(AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_)
