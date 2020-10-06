#pragma once  //��ֹͷ�ļ��ظ�����
#include <iostream>//�������������ͷ�ļ�
#include "Worker.h"
using namespace std;//ʹ�ñ�׼�������ռ�
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"
class WorkerManager {
public:

	//չʾ�˵�
	void Show_Menu();

	//�˳�ϵͳ
	void ExitSystem();

	//��¼ְ������
	int m_EmpNum;
	
	//ְ������ָ��
	Worker** m_EmpArray;

	//���ְ��
	void Add_Emp();

	//�����ļ�
	void save();

	//�ж��ļ��Ƿ�Ϊ�� ��־
	bool m_FileIsEmpty;

	//ͳ���ļ�������
	int	get_EmpNum();

	//��ʼ��ְ��
	void init_Emp();

	//��ʾְ��
	void show_Emp();

	//��������
	~WorkerManager();

	//ɾ��ְ��
	void del_emp();

	//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
	int IsExist(int id);

	//�޸�ְ��
	void Mob_Emp();

	//����ְ��
	void Find_Emp();
	
	//����ְ��
	void Sort_Emp();

	//���ְ��
	void cleanFile();
	//���캯��
	WorkerManager();

};