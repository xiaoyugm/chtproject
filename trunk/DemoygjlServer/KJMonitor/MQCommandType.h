#pragma once

enum CommandType
{
	SENDSTARTTIME,             //����������ʱ��
	REALTIMEDATA,              //�ɼ�ʵʱ����
	VERIFYTIMER,               //Уʱ����
	MANUALCONTROL,             //�ֶ����Ʋ���
	SENDCONFIG,                //���ò���
	TESTCOMMUNICATION,         //ͨѶ����
	WINDGASATRESIA,            //�����˹����
	FAULTATRESIA,               //���ϱ���
	INFODEFINE,                 //���÷�վ
	SERIALERROR,                 //����ͨѶʧ��
	AUTOCONTROL                 //�Զ����Ʋ���
};