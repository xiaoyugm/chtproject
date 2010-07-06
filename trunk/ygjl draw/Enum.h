#if !defined(_ENUM_H)
#define _ENUM_H

typedef struct tagLineChangeStruct			//���߱仯���ݽṹ
{
	COLORREF    	clrInLineColor;
	COLORREF    	clrOutLineColor;
	COLORREF     	clrCommErrorLineColor;
	UINT	       	nPoint;
	unsigned char   LineWarn_state;
}LineChangeStruct;

typedef struct tagFillChangeStruct			//���仯���ݽṹ
{
	COLORREF       	clrInFillColor;
	COLORREF     	clrOutFillColor;
	COLORREF       	clrCommErrorFillColor;
	UINT        	nPoint;
	unsigned char   FillWarn_state;
}FillChangeStruct;


typedef struct tagRayChangeStruct			//��˸�仯���ݽṹ
{
	BOOL		bRayType;					//��˸����
	UINT		nRaySpeed;
	COLORREF	clrRayStartColor;
	COLORREF	clrRayEndColor;
	UINT		nPoint;
	UINT		nMin,nMax;
}RayChangeStruct;

typedef enum 				//�ο��㶨��
{
	KILL,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	CENTER
}REFERENCEPOINT;

typedef struct tagPercentHStruct			//ˮƽ������ݽṹ
{
	UINT		nPoint;
	UINT		pufdata;
	COLORREF	clrFillColor;
	REFERENCEPOINT	ReferencePoint;

}PercentHStruct;

typedef struct tagPercentVStruct			//��ֱ������ݽṹ
{
	UINT		nPoint;
	UINT		pufdata;
	COLORREF	clrFillColor;
	REFERENCEPOINT	ReferencePoint;
}PercentVStruct;

typedef struct tagActionStruct				//�������ݽṹ
{
	BOOL				bIsLineColorChange;		//������ɫ�仯
	LineChangeStruct	stcLineChange;

	BOOL				bIsFillColorChange;				//�����ɫ�仯
	FillChangeStruct	stcFillChange;

	BOOL				bIsRayChange;					//��˸
	RayChangeStruct		stcRayChange;

	BOOL				bIsPencentFillH;				//ˮƽ�ٷֱ����
	PercentHStruct		stcPHChange;
	
	BOOL				bIsPencentFillV;				//��ֱ�ٷֱ����
	PercentVStruct		stcPVChange;

}ActionStruct;

typedef struct tagRotaryStruct			//ת�����ݽṹ
{
	UINT		nPoint;	
	UINT		nSpeed;
	COLORREF    clrLineColor;			//������ɫ
	COLORREF    clrFillColor;			//�����ɫ
	COLORREF    clrRotaryColor;			//ת���ڲ���ɫ
	UINT		nAngle;					//�ڲ��Ƕ�
	BOOL		bContrarotate;			//��ת����
}RotaryStruct;

typedef struct tagCarStruct				//С�����ݽṹ
{
	UINT		nPoint;					//��Ӧ���
	UINT		nSpeed;					//�ƶ��ٶ�
	COLORREF    clrLineColor;			//������ɫ
	COLORREF    clrFillColor;			//�����ɫ
}CarStruct;

typedef struct tagConduitStruct			//�ܵ����ݽṹ
{
	UINT		nPoint;	
	COLORREF    clrBackColor;			//�����ɫ
	COLORREF    clrForwordColor;		//ǰ����ɫ
	COLORREF    clrMoveColor;			//ת���ڲ���ɫ
	UINT		nLineWidth;				//���
}ConduitStruct;


#endif

