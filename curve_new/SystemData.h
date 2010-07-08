
////////模拟量结构定义///////////////
typedef struct _StructSimulate
{
	unsigned short	PointNo;			///点号
	double  MaxValue;			///最大值
	double  MinValue;			///最小值
	__int32 BitNumber;			///二进制位数
	unsigned char WarnMode;			///报警模式
	double WarningMaxValue;	///报警最大值
	double WarningMinValue;	///报警最小值
	char    StrUnit[50];		///工程单位
}StructSimulate;

////////开关量结构定义///////////////
typedef struct _StructSwitch
{
	unsigned short	PointNo;			//点号
	unsigned char WarnMode;			//unAC
}StructSwitch;

////////点结构定义///////////////
typedef struct _StructPoint
{
	char	Type;				///类型
	__int32 SpendTime;			///消耗时间
	short	unConnectorID;		
    unsigned short   Standard;             //最大二进制数
	StructSimulate m_StruSimulate;  
	StructSwitch m_StruSwitch;
}StructPoint;










