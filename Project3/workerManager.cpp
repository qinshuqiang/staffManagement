#include "workerManager.h"
WorkerManager::WorkerManager() {

	//1���ļ�������
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//�ļ�������
		cout << "�ļ�������" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2���ļ�����,����Ϊ��
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "�ļ�Ϊ��" << endl;
		//�ļ�������
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3�����ļ����ڲ���������
	int num = this->get_EmpNum();
	cout<< "ְ��������Ϊ��" << num << endl;
	this->m_EmpNum = num;

	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//��ʼ��ʼ�����ݣ��浽������
	this->init_Emp();
}
void WorkerManager::Show_Menu() {
	cout << "*****************************************************" << endl;
	cout << "**************��ӭʹ��ְ������ϵͳ*******************" << endl;
	cout << "***************** 0.�˳�����ϵͳ*********************" << endl;
	cout << "***************** 1.����Ա����Ϣ*********************" << endl;
	cout << "***************** 2.��ʾԱ����Ϣ*********************" << endl;
	cout << "***************** 3.ɾ����ְְ��*********************" << endl;
	cout << "***************** 4.�޸�ְ����Ϣ*********************" << endl;
	cout << "***************** 5.����ְ����Ϣ*********************" << endl;
	cout << "***************** 6.���ձ������*********************" << endl;
	cout << "***************** 7.��������ĵ�*********************" << endl;
	cout << "*****************************************************" << endl;

}
//�˳�
void WorkerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);//�˳�����
}
//��ֹ�û���������
int ckeckDSelect() {
	int num;
	cout << "��������ְλ" << endl;
	cout << "1����ְͨ��" << endl;
	cout << "2������" << endl;
	cout << "3���ϰ�" << endl;
	cin >> num;
	if (num != 1&& num != 2 && num != 3) {
		cout << "��������" << endl;
		return ckeckDSelect();
	}
	else
	{
		return num;
	}
}
void WorkerManager::Add_Emp() {
	cout << "���������ְ������" << endl;
	int addNum = 0;//�û����������
	cin >> addNum;
	if (addNum > 0) {//��ʼ���
		//������ӿռ��С
		int newSize = this->m_EmpNum + addNum;//�¿ռ��С = ԭ����¼����+��������

		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];

		//��ԭ���ռ��µ����ݣ��������¿ռ���
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//��ʼ�������
		for (int i = 0; i < addNum; i++)
		{
			int id;//ְ�����
			string name;//ְ������
			int dSelect;//����ѡ��
			cout << "�������" << i + 1 << "��ְ����ţ�" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "��ְ��������" << endl;
			cin >> name;
			Worker* worker = NULL;
			cout << "��ѡ���" << i + 1 << "��ְ����λ��" << endl;
			dSelect = ckeckDSelect();
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "mmmmm����ְλ�ˣ��ó���Ա��Ӹ��ж�" << endl;
				break;
			}
			//������ְ��ָ�룬���浽������
			newSpace[this->m_EmpNum + i] = worker;
		}


		//�ͷ�Դ�еĿռ�
		delete[] this->m_EmpArray;

		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;

		//������ְ������
		this->m_EmpNum = newSize;

		//����ְ���ļ���Ϊ��
		this->m_FileIsEmpty = false;

		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ�������ڹ���" << newSize << "��ְ��" << endl;
		//���浽�ļ���
		this->save();
	}
	else {//��������

	}
	//��������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");

}
void WorkerManager::save() {
	ofstream ofs(FILENAME, ios::out);//������ķ�ʽ���ļ�---д�ļ�

	//��ÿ��������д���ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "   "
			<< this->m_EmpArray[i]->m_Name << "   "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//�ر��ļ�
	ofs.close();
}
int	WorkerManager::get_EmpNum() {
	ifstream ifs(FILENAME, ios::in);//���ļ������ļ�
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs>>id&&ifs>>name&&ifs>>dId)
	{
		num++;
	}
	return num;
}
void WorkerManager::init_Emp() {
	ifstream ifs(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs>>id&&ifs>>name&&ifs>>dId)
	{
		Worker* worker = NULL;
		if (dId == 1)//��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}else if (dId == 2)//��ְͨ��
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)//��ְͨ��
		{
			worker = new Boss(id, name, dId);
		}
		else {
			cout << "��ȡ�ļ��������޸�������" << endl;
			system("pause");
			exit(0);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkerManager::show_Emp() {
	//�ж��ļ��Ƿ�Ϊ��||����
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ��߼�¼Ϊ��" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//�������������
	system("pause");
	system("cls");
}
//ɾ��ְ��
void WorkerManager::del_emp() {
	if (this->m_FileIsEmpty) {
		cout << "Ա���б�Ϊ�գ�����¼��ְ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��������Ҫɾ����ְ�����" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1) {
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;//������������
		this->save();
		cout << "ɾ���ɹ�" << endl;
	}
	else
	{
		cout << "û���ҵ����Ա��" << endl;
	}
	system("pause");
	system("cls");
}
//�ж�ְ���Ƿ����  ������ڷ���ְ�����������е�λ�ã������ڷ���-1
int WorkerManager::IsExist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}
//�޸�ְ��
void WorkerManager::Mob_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "Ա���б�Ϊ�գ�����¼��ְ��" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "��������Ҫ�޸ĵ�ְ�����" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1) {
		delete this->m_EmpArray[index];
		int newId = 0;
		string newName;
		int dSelect = 0;

		cout << "���ҵ�"<<id<<"��Ա��" << endl;
		cout << "������������" << endl;
		cin >> newName;
		cout << "�������±��" << endl;
		cin >> newId;
		dSelect = ckeckDSelect();
		Worker* worker = NULL;
		switch (dSelect)
		{
		case 1:
			worker = new Employee(newId, newName, 1);
			break;
		case 2:
			worker = new Manager(newId, newName, 2);
			break;
		case 3:
			worker = new Boss(newId, newName, 3);
			break;
		default:
			cout << "mmmmm����ְλ�ˣ��ó���Ա��Ӹ��ж�" << endl;
			break;
		}
		//������ְ��ָ�룬���浽������
		this->m_EmpArray[index] = worker;
		this->save();
		cout << "�޸ĳɹ�" << endl;
	}
	else
	{
		cout << "û���ҵ����Ա��" << endl;
	}
	system("pause");
	system("cls");
}
//����ְ��
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "Ա���б�Ϊ�գ�����¼��ְ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "1������ְ���ı�Ų��ң�" << endl;
		cout << "2������ְ�����������ң�" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			cout << "��������Ҫ���ҵ�ְ�����" << endl;
			int id;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1) {
				cout << "���ҳɹ�����Ϣ���£�" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
					cout << "���޴˱��" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "��������Ҫ���ҵ�ְ������" << endl;
			cin >> name;
			bool bl=false;//�Ƿ�鵽���ְ��
			cout << "���ҽ��ͼ�£�" << endl;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name) {
					bl = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!bl) {
				cout << "���޴���" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
		system("pause");
		system("cls");

	}
}

//����ְ��
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "Ա���б�Ϊ�գ�����¼��ְ��" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "��ѡ������ʽ" << endl;
	cout << "1������ְ�������������" << endl;
	cout << "2������ְ����Ž�������" << endl;
	int select = 0;
	cin >> select;
	for (int i = 0; i < m_EmpNum; i++)
	{
		int minOrMax = i;
		for (int j = i+1; j < m_EmpNum; j++)
		{
			if (select == 1) {//����
				if (this->m_EmpArray[minOrMax]->m_Id > this->m_EmpArray[j]->m_Id) {
					minOrMax = j;
				}
			}
			else
			{
				if (this->m_EmpArray[minOrMax]->m_Id < this->m_EmpArray[j]->m_Id) {
					minOrMax = j;
				}
			}
		}
		//�ж�һ��ʼ�϶�����Сֵ�������ֵ�ǲ��Ǽ������Сֵ�������ֵ��������ǣ���������
		if (minOrMax != i) {
			Worker* temp = this->m_EmpArray[i];
			m_EmpArray[i] = this->m_EmpArray[minOrMax];
			this->m_EmpArray[minOrMax] = temp;
		}
	}
	cout << "����ɹ��������Ľ��Ϊ��" << endl;
	this->save();
	this->show_Emp();

};
//���ְ��
void WorkerManager::cleanFile() {
	cout << "ȷ������" << endl;
	cout << "1��ȷ��" << endl;
	cout << "2��ȡ��" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL) {
			//ɾ��������ÿ��ְ������
			for (int i = 0; i < m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//ɾ����������ָ��
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			cout << "�����ɹ�" << endl;
		}
	}
	else if (select == 2) {
		return;
	}
	else
	{
		cout << "��������" << endl;
	}
	system("pause");
	system("cls");

}
WorkerManager::~WorkerManager() {
	if (this -> m_EmpArray != NULL) {
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}