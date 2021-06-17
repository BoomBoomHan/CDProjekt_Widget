#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <qstring.h>

class FunctionLibrary//����������
{
public:
	//������,С����ת��Ϊ�ַ���
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

	//��std::stringת��ΪQString
	static QString ToQString(const std::string);
	//��QStringת��Ϊstd::string
	static std::string ToStdString(const QString);

	//�ж�Ŀ�����Ƿ���min��max��,����,�������Ϊ�Ƿ��Ǳ�����
	template<typename T>
	static bool IsInRange(const T target, const T min, const T max, const bool isLeftClosed = false, const bool isRightClosed = false)
	{
		const bool result1 = isLeftClosed ? (target >= min) : (target > min);
		const bool result2 = isRightClosed ? (target <= max) : (target < max);
		return result1 * result2;
	}

	//��ָ��λ�ô����ļ���,����ֵΪ·����
	static std::string CreateFolder(const std::string);
	//��ָ������ļ�,����������Ϊ�Ƿ�Ϊios::app,���ɹ��򷵻���
	static bool OpenFile(std::ofstream&, const std::string, const bool = false);
	//��ָ�������ļ�,���ɹ��򷵻���
	static bool OpenFile(std::ifstream&, const std::string);
	//�ر��ļ�
	static void CloseFile(std::ifstream&);
	//�ر��ļ�
	static void CloseFile(std::ofstream&);
};

