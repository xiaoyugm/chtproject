
////////ģ�����ṹ����///////////////
typedef struct _StructSimulate
{
	unsigned short	PointNo;			///���
	double  MaxValue;			///���ֵ
	double  MinValue;			///��Сֵ
	__int32 BitNumber;			///������λ��
	unsigned char WarnMode;			///����ģʽ
	double WarningMaxValue;	///�������ֵ
	double WarningMinValue;	///������Сֵ
	char    StrUnit[50];		///���̵�λ
}StructSimulate;

////////�������ṹ����///////////////
typedef struct _StructSwitch
{
	unsigned short	PointNo;			//���
	unsigned char WarnMode;			//unAC
}StructSwitch;

////////��ṹ����///////////////
typedef struct _StructPoint
{
	char	Type;				///����
	__int32 SpendTime;			///����ʱ��
	short	unConnectorID;		
    unsigned short   Standard;             //����������
	StructSimulate m_StruSimulate;  
	StructSwitch m_StruSwitch;
}StructPoint;










