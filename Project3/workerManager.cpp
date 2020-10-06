#include "workerManager.h"
WorkerManager::WorkerManager() {

	//1、文件不存在
	ifstream ifs(FILENAME, ios::in);
	if (!ifs.is_open()) {
		//文件不存在
		cout << "文件不存在" << endl;
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//2、文件存在,数据为空
	char ch;
	ifs >> ch;
	if (ifs.eof()) {
		cout << "文件为空" << endl;
		//文件不存在
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//3、当文件存在并且有数据
	int num = this->get_EmpNum();
	cout<< "职工的人数为：" << num << endl;
	this->m_EmpNum = num;

	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//开始初始化数据，存到数组中
	this->init_Emp();
}
void WorkerManager::Show_Menu() {
	cout << "*****************************************************" << endl;
	cout << "**************欢迎使用职工管理系统*******************" << endl;
	cout << "***************** 0.退出管理系统*********************" << endl;
	cout << "***************** 1.增加员工信息*********************" << endl;
	cout << "***************** 2.显示员工信息*********************" << endl;
	cout << "***************** 3.删除离职职工*********************" << endl;
	cout << "***************** 4.修改职工信息*********************" << endl;
	cout << "***************** 5.查找职工信息*********************" << endl;
	cout << "***************** 6.按照编号排序*********************" << endl;
	cout << "***************** 7.情况所有文档*********************" << endl;
	cout << "*****************************************************" << endl;

}
//退出
void WorkerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);//退出程序
}
//防止用户输入别的数
int ckeckDSelect() {
	int num;
	cout << "请输入新职位" << endl;
	cout << "1、普通职工" << endl;
	cout << "2、经理" << endl;
	cout << "3、老板" << endl;
	cin >> num;
	if (num != 1&& num != 2 && num != 3) {
		cout << "输入有误" << endl;
		return ckeckDSelect();
	}
	else
	{
		return num;
	}
}
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量" << endl;
	int addNum = 0;//用户输入的数量
	cin >> addNum;
	if (addNum > 0) {//开始添加
		//计算添加空间大小
		int newSize = this->m_EmpNum + addNum;//新空间大小 = 原来记录人数+新增人数

		//开辟新空间
		Worker** newSpace = new Worker * [newSize];

		//将原来空间下的数据，拷贝到新空间下
		if (this->m_EmpArray != NULL) {
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//开始添加数据
		for (int i = 0; i < addNum; i++)
		{
			int id;//职工编号
			string name;//职工姓名
			int dSelect;//部门选择
			cout << "请输入第" << i + 1 << "个职工编号：" << endl;
			cin >> id;
			cout << "请输入第" << i + 1 << "个职工姓名：" << endl;
			cin >> name;
			Worker* worker = NULL;
			cout << "请选择第" << i + 1 << "个职工岗位：" << endl;
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
				cout << "mmmmm加了职位了，让程序员多加个判断" << endl;
				break;
			}
			//将创建职工指针，保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}


		//释放源有的空间
		delete[] this->m_EmpArray;

		//更改新空间的指向
		this->m_EmpArray = newSpace;

		//更新新职工人数
		this->m_EmpNum = newSize;

		//更新职工文件不为空
		this->m_FileIsEmpty = false;

		//提示添加成功
		cout << "成功添加" << addNum << "名新职工，现在共有" << newSize << "名职工" << endl;
		//保存到文件中
		this->save();
	}
	else {//输入有误

	}
	//按任意键后清屏回到上级目录
	system("pause");
	system("cls");

}
void WorkerManager::save() {
	ofstream ofs(FILENAME, ios::out);//用输出的方式打开文件---写文件

	//将每个人数据写入文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << "   "
			<< this->m_EmpArray[i]->m_Name << "   "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}
int	WorkerManager::get_EmpNum() {
	ifstream ifs(FILENAME, ios::in);//打开文件，读文件
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
		if (dId == 1)//普通职工
		{
			worker = new Employee(id, name, dId);
		}else if (dId == 2)//普通职工
		{
			worker = new Manager(id, name, dId);
		}
		else if (dId == 3)//普通职工
		{
			worker = new Boss(id, name, dId);
		}
		else {
			cout << "读取文件出错，请修复后再试" << endl;
			system("pause");
			exit(0);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	ifs.close();
}
void WorkerManager::show_Emp() {
	//判断文件是否为空||存在
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者记录为空" << endl;
	}
	else {
		for (int i = 0; i < m_EmpNum; i++)
		{
			this->m_EmpArray[i]->showInfo();
		}
	}
	//按任意键后清屏
	system("pause");
	system("cls");
}
//删除职工
void WorkerManager::del_emp() {
	if (this->m_FileIsEmpty) {
		cout << "员工列表为空，请先录入职工" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请输入您要删除的职工编号" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1) {
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;//更新数组总数
		this->save();
		cout << "删除成功" << endl;
	}
	else
	{
		cout << "没有找到这个员工" << endl;
	}
	system("pause");
	system("cls");
}
//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
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
//修改职工
void WorkerManager::Mob_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "员工列表为空，请先录入职工" << endl;
		system("pause");
		system("cls");
		return;
	}

	cout << "请输入您要修改的职工编号" << endl;
	int id;
	cin >> id;
	int index = this->IsExist(id);
	if (index != -1) {
		delete this->m_EmpArray[index];
		int newId = 0;
		string newName;
		int dSelect = 0;

		cout << "查找到"<<id<<"号员工" << endl;
		cout << "请输入新姓名" << endl;
		cin >> newName;
		cout << "请输入新编号" << endl;
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
			cout << "mmmmm加了职位了，让程序员多加个判断" << endl;
			break;
		}
		//将创建职工指针，保存到数组中
		this->m_EmpArray[index] = worker;
		this->save();
		cout << "修改成功" << endl;
	}
	else
	{
		cout << "没有找到这个员工" << endl;
	}
	system("pause");
	system("cls");
}
//查找职工
void WorkerManager::Find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "员工列表为空，请先录入职工" << endl;
		system("pause");
		system("cls");
		return;
	}
	else
	{
		cout << "1、按照职工的编号查找：" << endl;
		cout << "2、按照职工的姓名查找：" << endl;
		int select = 0;
		cin >> select;
		if (select == 1) {
			cout << "请输入您要查找的职工编号" << endl;
			int id;
			cin >> id;
			int index = this->IsExist(id);
			if (index != -1) {
				cout << "查找成功，信息如下：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
			else {
					cout << "查无此编号" << endl;
			}
		}
		else if (select == 2) {
			string name;
			cout << "请输入您要查找的职工姓名" << endl;
			cin >> name;
			bool bl=false;//是否查到这个职工
			cout << "查找结果图下：" << endl;
			for (int i = 0; i < m_EmpNum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name) {
					bl = true;
					this->m_EmpArray[i]->showInfo();
				}
			}
			if (!bl) {
				cout << "查无此人" << endl;
			}
		}
		else
		{
			cout << "输入选项有误" << endl;
		}
		system("pause");
		system("cls");

	}
}

//排序职工
void WorkerManager::Sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "员工列表为空，请先录入职工" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "请选择排序方式" << endl;
	cout << "1、根据职工编号升序排列" << endl;
	cout << "2、根据职工编号降序排列" << endl;
	int select = 0;
	cin >> select;
	for (int i = 0; i < m_EmpNum; i++)
	{
		int minOrMax = i;
		for (int j = i+1; j < m_EmpNum; j++)
		{
			if (select == 1) {//升序
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
		//判断一开始认定的最小值或者最大值是不是计算的最小值或者最大值，如果不是，交换数据
		if (minOrMax != i) {
			Worker* temp = this->m_EmpArray[i];
			m_EmpArray[i] = this->m_EmpArray[minOrMax];
			this->m_EmpArray[minOrMax] = temp;
		}
	}
	cout << "排序成功，排序后的结果为：" << endl;
	this->save();
	this->show_Emp();

};
//清空职工
void WorkerManager::cleanFile() {
	cout << "确定清除嘛？" << endl;
	cout << "1、确定" << endl;
	cout << "2、取消" << endl;
	int select = 0;
	cin >> select;
	if (select == 1) {
		ofstream ofs(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != NULL) {
			//删除堆区的每个职工对象
			for (int i = 0; i < m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			//删除堆区数组指针
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
			cout << "操作成功" << endl;
		}
	}
	else if (select == 2) {
		return;
	}
	else
	{
		cout << "输入有误" << endl;
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