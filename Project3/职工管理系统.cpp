#include <iostream>
using namespace std;
#include "workerManager.h"
//#include "Worker.h"
//#include "employee.h"
//#include "manager.h"
//#include "boss.h"

int main() {
	//���Դ���
	/*Worker* worker = NULL;
	worker = new Employee(1, "����", 1);
	worker->showInfo();
	delete worker;
	worker = new Manager(2, "����", 2);
	worker->showInfo();
	delete worker;
	worker = new Boss(3, "����", 3);
	worker->showInfo();
	delete worker;*/
	//ʵ����һ�������߶���
	WorkerManager wm;
	int choice = 0;//�����洢�û���ѡ��
	while (true)
	{
		wm.Show_Menu();
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0://�˳�ϵͳ
			wm.ExitSystem();
			break;
		case 1://����ְ��
			wm.Add_Emp();
			break;
		case 2://��ʾְ��
			wm.show_Emp();
			break;
		case 3://ɾ��ְ��
			wm.del_emp();
			break;
		case 4://�޸�ְ��
			wm.Mob_Emp();
			break;
		case 5://����ְ��
			wm.Find_Emp();
			break;
		case 6://����ְ��
			wm.Sort_Emp();
			break;
		case 7://����ĵ�
			wm.cleanFile();
			break;
		default://��ս���
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}