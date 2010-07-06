#if !defined(_ENUM_H)
#define _ENUM_H

typedef struct tagLineChangeStruct			//边线变化数据结构
{
	COLORREF    	clrInLineColor;
	COLORREF    	clrOutLineColor;
	COLORREF     	clrCommErrorLineColor;
	UINT	       	nPoint;
	unsigned char   LineWarn_state;
}LineChangeStruct;

typedef struct tagFillChangeStruct			//填充变化数据结构
{
	COLORREF       	clrInFillColor;
	COLORREF     	clrOutFillColor;
	COLORREF       	clrCommErrorFillColor;
	UINT        	nPoint;
	unsigned char   FillWarn_state;
}FillChangeStruct;


typedef struct tagRayChangeStruct			//闪烁变化数据结构
{
	BOOL		bRayType;					//闪烁类型
	UINT		nRaySpeed;
	COLORREF	clrRayStartColor;
	COLORREF	clrRayEndColor;
	UINT		nPoint;
	UINT		nMin,nMax;
}RayChangeStruct;

typedef enum 				//参考点定义
{
	KILL,
	TOP,
	BOTTOM,
	LEFT,
	RIGHT,
	CENTER
}REFERENCEPOINT;

typedef struct tagPercentHStruct			//水平填充数据结构
{
	UINT		nPoint;
	UINT		pufdata;
	COLORREF	clrFillColor;
	REFERENCEPOINT	ReferencePoint;

}PercentHStruct;

typedef struct tagPercentVStruct			//垂直填充数据结构
{
	UINT		nPoint;
	UINT		pufdata;
	COLORREF	clrFillColor;
	REFERENCEPOINT	ReferencePoint;
}PercentVStruct;

typedef struct tagActionStruct				//动作数据结构
{
	BOOL				bIsLineColorChange;		//边线颜色变化
	LineChangeStruct	stcLineChange;

	BOOL				bIsFillColorChange;				//填充颜色变化
	FillChangeStruct	stcFillChange;

	BOOL				bIsRayChange;					//闪烁
	RayChangeStruct		stcRayChange;

	BOOL				bIsPencentFillH;				//水平百分比填充
	PercentHStruct		stcPHChange;
	
	BOOL				bIsPencentFillV;				//垂直百分比填充
	PercentVStruct		stcPVChange;

}ActionStruct;

typedef struct tagRotaryStruct			//转轮数据结构
{
	UINT		nPoint;	
	UINT		nSpeed;
	COLORREF    clrLineColor;			//边线颜色
	COLORREF    clrFillColor;			//填充颜色
	COLORREF    clrRotaryColor;			//转轮内部颜色
	UINT		nAngle;					//内部角度
	BOOL		bContrarotate;			//旋转方向
}RotaryStruct;

typedef struct tagCarStruct				//小车数据结构
{
	UINT		nPoint;					//对应点号
	UINT		nSpeed;					//移动速度
	COLORREF    clrLineColor;			//边线颜色
	COLORREF    clrFillColor;			//填充颜色
}CarStruct;

typedef struct tagConduitStruct			//管道数据结构
{
	UINT		nPoint;	
	COLORREF    clrBackColor;			//填充颜色
	COLORREF    clrForwordColor;		//前景颜色
	COLORREF    clrMoveColor;			//转轮内部颜色
	UINT		nLineWidth;				//宽度
}ConduitStruct;


#endif

