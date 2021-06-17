#pragma once

enum class StuStringInfo//学号StuID 姓名Name
{
	StuID,
	Name
};

enum class OutputMethod//忽略编号/学号IgnoreID 简短Short 完整Complete 保存用Save
{
	IgnoreID,
	Short,
	Complete,
	Save
};

enum class ProbStringInfo//编号ID 标题Title 指导老师TeacherName 要求Requirement
{
	ID,
	Title,
	TeacherName,
	Requirement
};