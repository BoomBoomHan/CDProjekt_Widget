#pragma once
#include <string>
#include "System.h"

class Student//学生类
{
private:
	mutable std::string stuID;//学号
	mutable std::string name;//姓名
	mutable bool sex;//1为男，0为女
	mutable unsigned int age;//年龄
	mutable class Problem* selectedProblem;//选择的题目
	mutable bool isDeleted;
	static std::string nullProblemFlag;
private:
	//设置题目
	bool setProblem(const Problem*) const;
	//将自己所选的题目已选人数减1
	void selfDelete() const;

	friend class System;//System类是此类的友元类
public:
	//学号 姓名 性别(1男0女) 年龄 选择的题目 序号
	Student(const std::string, const std::string, const bool, const unsigned int, const Problem*);
	//析构
	~Student();
	//获取学号
	std::string GetID() const;
	//获取题目
	Problem* GetProblem() const;
	//四种不同的输出方式,IgnoreID为只输出标题,Short为输出ID和标题,Complete为全部输出,Save为只输出关键信息
	std::string Output(OutputMethod) const;
	//若两个学生学号相同则返回真(const)
	bool operator ==(const Student&) const;
	//此友元函数是System类的成员函数
	friend bool System::ChangeStudentInfo(const Student*, const std::string, StuStringInfo);
	//此友元函数是System类的成员函数
	friend bool System::ChangeStudentInfo(const Student*, const bool);
	//此友元函数是System类的成员函数
	friend bool System::ChangeStudentInfo(const Student*, const unsigned int);
	//此友元函数是System类的成员函数
	friend bool System::ChangeStudentInfo(const Student*, const Problem* b);
};