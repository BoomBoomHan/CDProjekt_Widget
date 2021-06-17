#include "Student.h"
#include "Problem.h"

std::string Student::nullProblemFlag = "NO_PROBLEM";

Student::Student(const std::string _stuID, const std::string _name, const bool _sex, const unsigned int _age, const Problem* _prob)
	:stuID(_stuID),
	name(_name),
	sex(_sex),
	age(_age),
	isDeleted(false),
	selectedProblem(nullptr)
{
	if (_prob)
	{
		const bool setResult = setProblem(_prob);
	}
}

Student::~Student()
{
	stuID = '\0';
	name = '\0';
	sex = 0;
	age = 0;
	if (selectedProblem && isDeleted)
	{
		selectedProblem->nowNum--;
	}
}

void Student::selfDelete() const
{
	if (selectedProblem)
	{
		selectedProblem->nowNum--;
	}
}

std::string Student::GetID() const
{
	return stuID;
}

Problem* Student::GetProblem() const
{
	return selectedProblem;
}

bool Student::setProblem(const Problem* prob) const
{
	if (!prob)
	{
		return false;
	}
	if (prob->IsFull())
	{
		return false;
	}
	if (selectedProblem)
	{
		selectedProblem->nowNum--;
	}
	prob->nowNum++;
	selectedProblem = const_cast<Problem*>(prob);
	return true;
}

std::string Student::Output(OutputMethod method) const
{
	std::string result;
	switch (method)
	{
	case OutputMethod::Complete:
		result = "学号:" + stuID + "\n姓名:" + name + "\n性别:";
		result += sex ? "男" : "女";
		result += "\n年龄:" + FunctionLibrary::ToString(age) + "岁";
		result += "\n选择题目:";
		if (selectedProblem)
		{
			result += selectedProblem->Output(OutputMethod::IgnoreID);
		}
		else
		{
			result += "暂无";
		}
		break;
	case OutputMethod::Save:
		result = stuID + "\n" + name + "\n";
		result += sex ? "1" : "0";
		result += "\n" + FunctionLibrary::ToString(age) + "\n";
		if (selectedProblem)
		{
			result += selectedProblem->GetID();
		}
		else
		{
			result += nullProblemFlag;
		}
		result += "\n";
		break;
	case OutputMethod::Short:
		result = stuID + ",";
	case OutputMethod::IgnoreID:
	default:
		result += name;
		break;
	}
	return result;
}

bool Student::operator ==(const Student& stu) const
{
	return (stuID == stu.GetID()) ? true : false;
}