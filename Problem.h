#pragma once
#include <string>
#include "System.h"
#include "Enums.h"

class Problem//课设题目类
{
private:
	mutable std::string id;//编号
	mutable std::string title;//标题
	mutable std::string teacherName;//指导老师
	mutable std::string requirement;//要求
	mutable unsigned int maxNum;//最大选课人数
	mutable unsigned int nowNum;//已选人数
private:
	friend class Student;//Student类是此类的友元类
	friend class System;//System类是此类的友元类
public:
	//编号 标题 指导老师 要求 最大人数 已选人数
	Problem(const std::string, const std::string, const std::string, const std::string, const unsigned int);
	//析构
	~Problem();
	//获取编号(const)
	std::string GetID() const;
	//获取标题
	std::string GetTitle() const;
	//获取最大选题人数
	unsigned int GetMaxNumber() const;
	//获取已选人数
	unsigned int GetNowNumber() const;
	//是否已选满
	bool IsFull() const;
	//四种不同的输出方式,IgnoreID为只输出标题,Short为输出ID和标题,Complete为全部输出,Save为只输出关键信息
	std::string Output(OutputMethod) const;
	//若两者编号相同则返回真(const)
	bool operator ==(const Problem&) const;
	//此友元函数是System类的成员函数
	friend bool System::ChangeProblemInfo(const Problem*, const std::string, ProbStringInfo);
	//此友元函数是System类的成员函数
	friend bool System::ChangeProblemInfo(const Problem*, const unsigned int);
};

