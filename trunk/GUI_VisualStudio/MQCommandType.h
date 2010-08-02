#pragma once

enum CommandType
{
	SENDSTARTTIME,             //服务器启动时间
	REALTIMEDATA,              //采集实时数据
	VERIFYTIMER,               //校时操作
	MANUALCONTROL,             //手动控制操作
	SENDCONFIG,                //配置分站测点
	TESTCOMMUNICATION,         //通讯测试
	WINDGASATRESIA,            //风电瓦斯闭锁
	FAULTATRESIA,               //故障闭锁
	INFODEFINE,                 //配置分站
	SERIALERROR,                 //串口通讯失败
	AUTOCONTROL                 //自动控制操作
};