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
	AUTOCONTROL,                 //�Զ����Ʋ���
	SAVEDBREALTIMEDATA,           //��ʵʱ����
	SAVEADJUSTDATA,               //���У����
	SAVE5MRTDATA,                  //��5Mʵʱ����
	MASTERSLAVER,                  //��������
	DISDRAWMENU,                 //��������draw�˵�
	SERVER_FILES,
	REQUEST_FILE,
	START_TRANSFERT,
	REQUEST_NEXT_FILE_PART,
	NEXT_FILE_PART,
	TRANSFERT_COMPLETED,
	SERVER_READY,
};