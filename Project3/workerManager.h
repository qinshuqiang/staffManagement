#pragma once  //防止头文件重复包含
#include <iostream>//包含输入输出流头文件
#include "Worker.h"
using namespace std;//使用标准的命名空间
#include "employee.h"
#include "manager.h"
#include "boss.h"

#include <fstream>
#define FILENAME "empFile.txt"
class WorkerManager {
public:

	//展示菜单
	void Show_Menu();

	//退出系统
	void ExitSystem();

	//记录职工人数
	int m_EmpNum;
	
	//职工数组指针
	Worker** m_EmpArray;

	//添加职工
	void Add_Emp();

	//保存文件
	void save();

	//判断文件是否为空 标志
	bool m_FileIsEmpty;

	//统计文件中人数
	int	get_EmpNum();

	//初始化职工
	void init_Emp();

	//显示职工
	void show_Emp();

	//析构函数
	~WorkerManager();

	//删除职工
	void del_emp();

	//判断职工是否存在  如果存在返回职工所在数组中的位置，不存在返回-1
	int IsExist(int id);

	//修改职工
	void Mob_Emp();

	//查找职工
	void Find_Emp();
	
	//排序职工
	void Sort_Emp();

	//清空职工
	void cleanFile();
	//构造函数
	WorkerManager();

};