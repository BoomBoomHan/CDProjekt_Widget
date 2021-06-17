#include "System.h"
#include "Student.h"
#include "Problem.h"
#include <iostream>
#include <fstream>

bool System::isSystemActive = false;

System::System(const std::string userName, const std::string password)
	:isThisActive(false),
	studentList(new BBHList<Student>),
	problemList(new BBHList<Problem>),
	stuList(*studentList),
	probList(*problemList),
	databasePath("Library"),
	stuListFileName("Students.dat"),
	probListFileName("Problems.dat"),
	correspondingAccount{ "BoomBoomHan","123456" }
{
	if ((!isSystemActive) && (userName == correspondingAccount[0]) && (password == correspondingAccount[1]))
	{
		isSystemActive = true;
		isThisActive = true;
	}
	if (isThisActive)
	{
		std::ifstream inputFile;
		//读取题目
		BBHList<unsigned int> nowNums;
		std::string _id;//编号
		std::string _title;//标题
		std::string _teacherName;//指导老师
		std::string _requirement;//要求
		unsigned int _maxNum = 0;//最大选课人数
		unsigned int _nowNum = 0;//已选人数
		if (FunctionLibrary::OpenFile(inputFile, databasePath + "/" + probListFileName))
		{
			while (!inputFile.eof())
			{
				std::getline(inputFile, _id);
				if (_id == "")
				{
					break;
				}
				std::getline(inputFile, _title);
				std::getline(inputFile, _teacherName);
				std::getline(inputFile, _requirement);
				inputFile >> _maxNum >> _nowNum;
				inputFile.get();
				AddProblem(_id, _title, _teacherName, _requirement, _maxNum, 0u);
				nowNums.AddElement(_nowNum, false);
			}
		}
		//读取学生
		std::string _stuID;//学号
		std::string _name;//姓名
		bool _sex;//1为男，0为女
		unsigned int _age;//年龄
		std::string _selectedProblemTitle;//选择的题目编号
		if (FunctionLibrary::OpenFile(inputFile, databasePath + "/" + stuListFileName))
		{
			while (!inputFile.eof())
			{
				std::getline(inputFile, _stuID);
				if (_stuID == "")
				{
					break;
				}
				std::getline(inputFile, _name);
				inputFile >> _sex >> _age;
				inputFile.get();
				std::getline(inputFile, _selectedProblemTitle);
				AddStudent(_stuID, _name, _sex, _age, _selectedProblemTitle);
			}
		}
		FunctionLibrary::CloseFile(inputFile);
		//数据检查
		for (unsigned int i = 0; i < probList.GetSize(); i++)
		{
			//std::cout << probList[i].GetNowNumber() << "," << nowNums[i] << std::endl;
			if (probList[i].GetNowNumber() != nowNums[i])
			{
				ERROR_SELF_REPAIR();
				break;
			}
		}
	}
}

System::~System()
{
	std::ofstream outputFile;
	std::string result;
	//保存题目
	if (FunctionLibrary::OpenFile(outputFile, FunctionLibrary::CreateFolder(databasePath) + "/" + probListFileName) && probList.GetSize())
	{
		for (unsigned int i = 0; i < probList.GetSize(); i++)
		{
			result += probList[i].Output(OutputMethod::Save);
		}
		result.erase(result.end() - 1);
		outputFile << result;
		result.clear();
	}
	//保存学生
	if (FunctionLibrary::OpenFile(outputFile, FunctionLibrary::CreateFolder(databasePath) + "/" + stuListFileName) && stuList.GetSize())
	{
		for (unsigned int i = 0; i < stuList.GetSize(); i++)
		{
			result += stuList[i].Output(OutputMethod::Save);
		}
		result.erase(result.end() - 1);
		outputFile << result;
		result.clear();
	}
	FunctionLibrary::CloseFile(outputFile);
	//关闭系统
	isSystemActive = false;
	delete studentList;
	delete problemList;
}

void System::ERROR_SELF_REPAIR()
{
	std::cout << "ERROR!!!" << std::endl;
	for (unsigned int i = 0; i < stuList.GetSize(); i++)
	{
		stuList[i].selectedProblem = nullptr;
	}
	for (unsigned int i = 0; i < probList.GetSize(); i++)
	{
		probList[i].nowNum = 0;
	}
}

void System::CLEAR_DATAS()
{
	remove((databasePath + "/" + stuListFileName).c_str());
	remove((databasePath + "/" + probListFileName).c_str());
}

bool System::AddProblem(const std::string _id, const std::string _title, const std::string _teacherName, const std::string _requirement, const unsigned int _maxNum, const unsigned int _nowNum)
{
	if (!isThisActive)
	{
		return false;
	}
	Problem prob(_id, _title, _teacherName, _requirement, _maxNum);
	prob.nowNum = _nowNum;
	return problemList->AddElement(prob);
}

bool System::AddStudent(const std::string _stuID, const std::string _name, const bool _sex, const unsigned int _age, const std::string probID)
{
	if ((!isThisActive) || (!stuList.CheckUnique(Student(_stuID, _name, _sex, _age, nullptr))))
	{
		return false;
	}
	if (probID == "" || probID == Student::nullProblemFlag)
	{
		return studentList->AddElement(Student(_stuID, _name, _sex, _age, nullptr));
	}
	Problem* target = nullptr;
	for (unsigned int i = 0; i < probList.GetSize(); i++)
	{
		if (probID == probList[i].GetID())
		{
			target = (!probList[i].IsFull()) ? &probList[i] : nullptr;
			break;
		}
	}
	return studentList->AddElement(Student(_stuID, _name, _sex, _age, target));
}

bool System::AddStudent(const std::string _stuID, const std::string _name, const bool _sex, const unsigned int _age, const unsigned int index)
{
	if ((!isThisActive) || (!FunctionLibrary::IsInRange(index, 0u, probList.GetSize(), true)) || (!stuList.CheckUnique(Student(_stuID, _name, _sex, _age, nullptr))))
	{
		return false;
	}
	const Problem* target = (!probList[index].IsFull()) ? &probList[index] : nullptr;
	return studentList->AddElement(Student(_stuID, _name, _sex, _age, target));
}

bool System::ChangeProblemInfo(const Problem* targetProb, const std::string str, ProbStringInfo targetInfo)
{
	if ((!isThisActive) || (!targetProb))
	{
		return false;
	}
	switch (targetInfo)
	{
	case ProbStringInfo::ID:
		targetProb->id = str;
		return true;
	case ProbStringInfo::Title:
		targetProb->title = str;
		return true;
	case ProbStringInfo::TeacherName:
		targetProb->teacherName = str;
		return true;
	case ProbStringInfo::Requirement:
		targetProb->requirement = str;
		return true;
	default:
		return false;
	}
}

bool System::ChangeProblemInfo(const Problem* targetProb, const unsigned int max)
{
	if ((!isThisActive) || (!targetProb))
	{
		return false;
	}
	if (max < targetProb->nowNum)
	{
		return false;
	}
	targetProb->maxNum = max;
	return true;
}

bool System::DeleteProblem(const Problem* targetProb)
{
	if ((!isThisActive) || (!targetProb) || (!probList.GetSize()))
	{
		return false;
	}
	if (targetProb->GetNowNumber())
	{
		return false;
	}
	unsigned int index = -1;
	for (unsigned int i = 0; i < probList.GetSize(); i++)
	{
		if (targetProb == &probList[i])
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return false;
	}
	const unsigned int deleteTarget = index;
	for (index += 1; index < probList.GetSize(); index++)
	{
		Problem* prob = &probList[index];
		for (unsigned int i = 0; i < stuList.GetSize(); i++)
		{
			Student* stu = &stuList[i];
			if (prob == stu->GetProblem())
			{
				stu->selectedProblem = &probList[index - 1];
			}
		}
	}
	return probList.DeleteElement(deleteTarget);
}

bool System::DeleteProblem(const unsigned int index)
{
	return DeleteProblem(&probList[index]);
}

bool System::ChangeStudentInfo(const Student* targetStu, const std::string str, StuStringInfo targetInfo)
{
	if (!isThisActive || !(targetStu))
	{
		return false;
	}
	switch (targetInfo)
	{
	case StuStringInfo::StuID:
		targetStu->stuID = str;
		return true;
	case StuStringInfo::Name:
		targetStu->name = str;
		return true;
	default:
		return false;
	}
}

bool System::ChangeStudentInfo(const Student* targetStu, const bool sex)
{
	if (!isThisActive || !(targetStu))
	{
		return false;
	}
	targetStu->sex = sex;
	return true;
}

bool System::ChangeStudentInfo(const Student* targetStu, const unsigned int age)
{
	if (!isThisActive || !(targetStu))
	{
		return false;
	}
	if (age <= 0)
	{
		return false;
	}
	targetStu->age = age;
	return true;
}

bool System::ChangeStudentInfo(const Student* targetStu, const Problem* prob)
{
	if ((!isThisActive) || !(targetStu) || (!prob))
	{
		return false;
	}
	return targetStu->setProblem(prob);
}

bool System::DeleteStudent(const Student* targetStu)
{
	if ((!isThisActive) || (!targetStu) || (!stuList.GetSize()))
	{
		return false;
	}
	unsigned int index = -1;
	for (unsigned int i = 0; i < stuList.GetSize(); i++)
	{
		if (targetStu == &stuList[i])
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		return false;
	}
	targetStu->selfDelete();
	return stuList.DeleteElement(index);
}

bool System::DeleteStudent(const unsigned int index)
{
	return DeleteStudent(&stuList[index]);
}

std::string System::OutputStu(OutputMethod method)
{
	if (stuList.GetSize() == 0)
	{
		return "空!";
	}
	std::string result;
	for (unsigned int i = 0; i < studentList->GetSize(); i++)
	{
		result += stuList[i].Output(method) + "\n\n";
	}
	return result;
}

std::string System::OutputProb(OutputMethod method)
{
	if (probList.GetSize() == 0)
	{
		return "空!";
	}
	std::string result;
	const std::string anotherEnter = (method == OutputMethod::Complete) ? "\n" : "";
	for (unsigned int i = 0; i < problemList->GetSize(); i++)
	{
		result += probList[i].Output(method) + "\n" + anotherEnter;
	}
	return result;
}

bool System::IsThisSystemActive()
{
	return isThisActive;
}