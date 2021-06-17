#pragma once
#include "BBHList.h"
#include "Enums.h"

class System//课程设计选题系统类
{
private:
	bool isThisActive;//此系统是否激活
	static bool isSystemActive;//是否有系统激活
	const std::string databasePath;//数据库路径
	const std::string stuListFileName;//学生数据库文件名
	const std::string probListFileName;//题目数据库文件名
	const std::string correspondingAccount[2];//账号和密码
private:
	BBHList<class Student>* studentList;//存放学生的表单
	BBHList<class Problem>* problemList;//存放题目的表单
	BBHList<Student>& stuList;//studentList引用
	BBHList<Problem>& probList;//problemList引用
private:
	//数据被非法修改过,进行自我修复从而将所有学生的选题和题目的已选人数清零
	void ERROR_SELF_REPAIR();
	//删除所有的数据
	void CLEAR_DATAS();
public:
	//构造函数,当输入账号密码正确且无其他已激活系统时才能激活系统
	System(const std::string, const std::string);
	//析构函数,保存并释放所有元素
	~System();

	//通过--编号 标题 指导老师 要求 最大人数 已选人数--添加课设题目,当且仅当系统激活时可用,成功时返回真
	bool AddProblem(const std::string, const std::string, const std::string, const std::string, const unsigned int, const unsigned int = 0u);
	//通过--学号 姓名 性别(1男0女) 年龄 选择的题目编号--添加学生,当且仅当系统激活时可用,成功时返回真
	bool AddStudent(const std::string, const std::string, const bool, const unsigned int, const std::string = "");
	//通过--学号 姓名 性别(1男0女) 年龄 题目列表的序号--添加学生,当且仅当系统激活时可用,成功时返回真
	bool AddStudent(const std::string, const std::string, const bool, const unsigned int, const unsigned int);
	
	//修改指定问题的编号、标题、指导老师、要求,当且仅当系统激活时可用,若成功则返回真
	bool ChangeProblemInfo(const Problem*, const std::string, ProbStringInfo);
	//修改指定问题的最大选题人数,当且仅当系统激活时可用,若成功则返回真
	bool ChangeProblemInfo(const Problem*, const unsigned int);
	//删除选题,如果该题已经有学生选择则不能删除,当且仅当系统激活时可用,若成功则返回真
	bool DeleteProblem(const Problem*);//未完成
	//根据列表中的顺序删除选题,如果该题已经有学生选择则不能删除,当且仅当系统激活时可用,若成功则返回真
	bool DeleteProblem(const unsigned int);

	//修改指定学生的学号、姓名,当且仅当系统激活时可用,若成功则返回真
	bool ChangeStudentInfo(const Student*, const std::string, StuStringInfo);
	//修改指定学生的性别,当且仅当系统激活时可用,若成功则返回真
	bool ChangeStudentInfo(const Student*, const bool);
	//修改指定学生的年龄,当且仅当系统激活时可用,若成功则返回真
	bool ChangeStudentInfo(const Student*, const unsigned int);
	//修改指定学生的选题,当且仅当系统激活时可用,若成功则返回真
	bool ChangeStudentInfo(const Student*, const Problem*);
	//删除学生,当且仅当系统激活时可用,若成功则返回真
	bool DeleteStudent(const Student*);//未完成
	//根据列表中的顺序删除学生,当且仅当系统激活时可用,若成功则返回真
	bool DeleteStudent(const unsigned int);

	//输出学生列表
	std::string OutputStu(OutputMethod);
	//输出题目列表
	std::string OutputProb(OutputMethod);
	//获取这个系统是否激活
	bool IsThisSystemActive();
};