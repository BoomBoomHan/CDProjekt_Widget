#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <qstring.h>

class FunctionLibrary//公共函数库
{
public:
	//将整数,小数等转换为字符串
	template<typename T>
	static std::string ToString(const T number)
	{
		std::stringstream stream;
		std::string result;
		stream << number;
		stream >> result;
		stream.clear();
		return result;
	}

	//将std::string转化为QString
	static QString ToQString(const std::string);
	//将QString转化为std::string
	static std::string ToStdString(const QString);

	//判断目标数是否在min和max间,第四,五个参数为是否是闭区间
	template<typename T>
	static bool IsInRange(const T target, const T min, const T max, const bool isLeftClosed = false, const bool isRightClosed = false)
	{
		const bool result1 = isLeftClosed ? (target >= min) : (target > min);
		const bool result2 = isRightClosed ? (target <= max) : (target < max);
		return result1 * result2;
	}

	//在指定位置创建文件夹,返回值为路径名
	static std::string CreateFolder(const std::string);
	//打开指定输出文件,第三个参数为是否为ios::app,若成功则返回真
	static bool OpenFile(std::ofstream&, const std::string, const bool = false);
	//打开指定输入文件,若成功则返回真
	static bool OpenFile(std::ifstream&, const std::string);
	//关闭文件
	static void CloseFile(std::ifstream&);
	//关闭文件
	static void CloseFile(std::ofstream&);
};

