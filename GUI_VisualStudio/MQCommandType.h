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
	AUTOCONTROL,                 //自动控制操作
	SAVEDBREALTIMEDATA,           //存实时数据
	SAVEADJUSTDATA,               //存调校数据
	SAVE5MRTDATA,                  //存5M实时数据
	MASTERSLAVER,                  //主机备机
	DISDRAWMENU,                 //更新主机draw菜单
	SERVER_FILES,
	REQUEST_FILE,
	START_TRANSFERT,
	REQUEST_NEXT_FILE_PART,
	NEXT_FILE_PART,
	TRANSFERT_COMPLETED,
	SERVER_READY,
};