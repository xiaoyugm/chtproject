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

//#define QQ_HOST _T("http://happyfarm.qzone.qq.com")		//服务器地址

#define MAX_POINT_NUMBER     15001       //最大点数  1-15000
#define COLOR_MASK	RGB(0x00,0x80,0x80)
#define MAX_FDS      61                  //最大分站  60 +1
#define MAX_CHAN     25                  //每分站最大通道  24 +1   16AD 8C
// Define use when allocating the buffer to send a file part
#define BUFFER_SIZE 1024

#define MAX_ROW     400  //最大行数 50

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
	CString locationname;                       //安装地点/名称
	CString strValue;                       //监测值
	CString warnTime;                       //报警时刻
	CString breakTime;                        //断电时刻
	CString restoreTime;                        //复电时刻
	CString feedStatus;                        //馈电状态
	CString feedTime;                        //馈电时刻
	CString safetyprecautions;                        //安全措施
};




//////////////////////////////////////////////////////////////////////////
//表结构
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
//测点描述表
	CString     pointnum;                       //点号
	CString     utype;	                	//传感器类型（0是电流型，1是频率型）
	CString     typeID;	                        //类型ID
	CString     positionid;	                    //位置ID
	CString     fds;	                    //测点所在分站
	CString     chan;                       //测点所在通道
	CString     subOpr;                     //报警标志
};
struct DTypeTFD	 {
//开关量类型
//安装地点表
	CString     DID;                      //模拟量开关量类型id
	CString Name;                    //模拟量开关量类型名称描述   
	CString ptype;	                  	//开关量类型  测点类型（0是模拟量，1是开关量）
	CString name0;	                	//0态名称
	CString name1;	                    //1态名称
	CString name2;	                    //2态名称
	CString     palms;	                 //开关量类型报警状态
	CString falm;                    //报警音乐
	CString fdel;		           // 删除标志
	CString recdate;		        // 记录时间
	CString deldate;		        // 删除时间
	CString Useridadd;		        // 添加操作用户
	CString Useriddel;		        // 删除操作用户

//模拟量类型
	CString ltop;	                  	//高量程
	CString lbom;	                	//低量程
	CString palmu;	                    //高报警值
	CString palmd;	                    //低报警值
	CString pbrk;	                    //模拟量类型断电值
	CString prtn;	                    //模拟量类型复电值
	CString punit;		                // (计量)单位
	CString pico;                       //图标编号

//测点描述表
	CString     pointnum;                       //点号
	CString     utype;	                	//传感器类型（0是电流型，1是频率型）
	CString     typeID;	                        //类型ID
	CString     potioinid;	                    //位置ID
	CString     fds;	                    //测点所在分站
	CString     chan;                       //测点所在通道
	CString     subOpr;                     //报警标志
};


struct ADTypeTable	 {
	CString TableName;                     //表名   
	CString NameD;                         //表名称描述   
	DTypeTField        m_DTypeTField;      //模拟量开关量类型结构
	DTypeTFD        m_DTypeTFD;            //模拟量开关量类型描述
};

//控制表
//馈电管理表
//调校管理表
//用户表


//调用显示、报表  
struct ADMainDis	 {
	int     m_ATotalnum;	                 //模拟量0-24点总值数量           报警/断电次数
	float   ATotalV;	        	         //模拟量0-24点总值
	int     duant;                           //是否某段时间
	float   AavV;	        	             //模拟量平均值
	float   AMinValue;	                     //模拟量最小值     
	float   AMaxValue;	                     //模拟量最大值                   第n次最大值
	COleDateTime  AMaxTime;                  //模拟量最大值时间               第n次最大值时间
	COleDateTime  ATime;                     //最后报警测点值时间             累计报警时间/馈电异常时刻
	COleDateTime  NTime;                     //最后正常测点值时间   措施时刻  起始
	COleDateTime  BTime;                     //最后断电测点值时间             终止
	COleDateTime  RTime;                     //最后复电测点值时间   馈电时刻  措施时刻
	CString     strsafetext;                                                //措施         
	CString     strlocal;                                                   //断电区域|馈电状态|时刻  
	int     havev; 
	COleDateTimeSpan tmid;
};

//日报/班报表头字符串
struct CommonStr	 {
	CString strc[150];                               
};

//开关量5分钟变化
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
//ADC断电    馈电
struct ADCbreakE	 {
	int     bFSd;	                        //分站  
	int     bchanel;                        //控制量通道     馈电通道
	CString adpoint;                        //AD     开关量点号         
	CString cpoint;                         //C      控制量点号
	CString CName;                          //控制量测点安装地点名称   
};

//串口连接分站   颜色设置    报警、馈电、断电等list0--n对应点
struct SerialF	 {
	int     SFSd;	                        //分站  颜色值
	int     cfds;	                        //分站 
	int     cchan;	                        //控制通道
	int     ffds;	                        //分站 
	int     fchan;	                        //馈电通道
};
struct RT60DATA	 {
	unsigned char   rtdata[44]; 
};
//通道号
//struct NumChannel {
//	int EFeed;                  	//馈电状态
//	int EquipmentState;             //设备状态
//};
//分站
struct SlaveStation {
	int     m_PID;	                        //点号  
	int     ptype;                   //传感器类型
	COleDateTime  ValueTime;              //采集测点值时间   
	CString falma;                  //报警音乐
	CString WatchName;              //测点安装地点名称   
	CString strPN;                  //测点点号 01A01  
	CString         utype;           //开关量/模拟量类型名称
    unsigned char   Channel_state;        //通道状态   0000 正常 0001:报警      

	float AValue;	                 //模拟量当前值
	float m_RangeH;	        	     //高量程
	float m_RangeL;	        	     //低量程
	float AlarmValueH;	             //高报警值
	float AlarmValueL;	             //低报警值
	float Apbrk;	                 //模拟量类型断电值
	float Aprtn;	                 //模拟量类型复电值
	CString m_Unit;		             // (计量)单位
    unsigned char       pnValue;        //模拟量百分比值

	int    CValue;	                    //开关量/频率/数字（模拟） 当前值  0通道交直流
	int AlarmState;	            //报警状态              0通道故障闭锁
	CString ZeroState;          //0态   开关量
	CString OneState;           //1态   开关量
	CString TwoState;           //2态   开关量

	CString FeedState;           //馈电状态
	CString strSafe;             //安全措施
	CString strBS;		             // 断电范围

	unsigned char  RangeH8;                    //0通道控制量高四位
	unsigned char  RangeL8;                    //0通道控制量低四位
	unsigned char  AValueH8;
	unsigned char  AValueL8;
	unsigned char  ApbrkH8;
	unsigned char  ApbrkL8;
	unsigned char  AprtnH8;
	unsigned char  AprtnL8;
    unsigned char  Control_state;        //控制量状态
	unsigned char  Channel8;             //传感器类型+模拟/开关(通道类型

    unsigned char   Adjust_state;        //标校状态
    int   m_second;            //第二次查馈电
    unsigned char   m_ffds;              //馈电分站
    unsigned char   m_fchan;             //馈电通道

    CTime   m5_T;                //五分钟数据存储时间
	float m5_AMaxValue;	                 //模拟量最大值
	float m5_AMinValue;	                 //模拟量最小值
	float m5_ATotalValue;	                 //模拟量五分钟数据存储值
    int   m5_Atotal;                      //五分钟数据存储次数

    CTime   m24_T;                //24小时数据存储时间
	float m24_AMaxValue;	                 //24小时模拟量最大值
	float m24_AMinValue;	                 //24小时模拟量最小值
	float m24_ATotalValue;	                 //模拟量24小时数据存储值
    int   m24_Atotal;                      //24小时数据存储次数
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

//DisplayPoint 列表显示
struct DisplayPoint {
//	CString     CPName;                    //模拟量开关量类型名称描述   
	CString     CPpointnum;                       //点号
	int         fds;             //分站
	int         chan;            // 通道
	unsigned char      D_Chan_state;           //模拟量开关量类型
};

//动态图显示
struct DisplayDraw {
	int         fds;             //分站
	int         chan;            // 通道
//	int         ptype;           //模拟量开关量类型
};

#endif // !defined(AFX_JEINWEB_H__5D9516BA_00A4_4D7D_B08A_9EAA563AB7A7__INCLUDED_)
