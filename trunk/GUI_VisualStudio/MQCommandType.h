#pragma once

enum CommandType
{
	SENDSTARTTIME,             //����������ʱ��
	REALTIMEDATA,              //�ɼ�ʵʱ����
	VERIFYTIMER,               //Уʱ����
	MANUALCONTROL,             //�ֶ����Ʋ���
	SENDCONFIG,                //���÷�վ���
	TESTCOMMUNICATION,         //ͨѶ����
	WINDGASATRESIA,            //�����˹����
	FAULTATRESIA,               //���ϱ���
	INFODEFINE,                 //���÷�վ
	SERIALERROR,                 //����ͨѶʧ��
	AUTOCONTROL                 //�Զ����Ʋ���
};