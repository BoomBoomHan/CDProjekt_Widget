#pragma once
#include <string>
#include "System.h"
#include "Enums.h"

class Problem//������Ŀ��
{
private:
	mutable std::string id;//���
	mutable std::string title;//����
	mutable std::string teacherName;//ָ����ʦ
	mutable std::string requirement;//Ҫ��
	mutable unsigned int maxNum;//���ѡ������
	mutable unsigned int nowNum;//��ѡ����
private:
	friend class Student;//Student���Ǵ������Ԫ��
	friend class System;//System���Ǵ������Ԫ��
public:
	//��� ���� ָ����ʦ Ҫ�� ������� ��ѡ����
	Problem(const std::string, const std::string, const std::string, const std::string, const unsigned int);
	//����
	~Problem();
	//��ȡ���(const)
	std::string GetID() const;
	//��ȡ����
	std::string GetTitle() const;
	//��ȡ���ѡ������
	unsigned int GetMaxNumber() const;
	//��ȡ��ѡ����
	unsigned int GetNowNumber() const;
	//�Ƿ���ѡ��
	bool IsFull() const;
	//���ֲ�ͬ�������ʽ,IgnoreIDΪֻ�������,ShortΪ���ID�ͱ���,CompleteΪȫ�����,SaveΪֻ����ؼ���Ϣ
	std::string Output(OutputMethod) const;
	//�����߱����ͬ�򷵻���(const)
	bool operator ==(const Problem&) const;
	//����Ԫ������System��ĳ�Ա����
	friend bool System::ChangeProblemInfo(const Problem*, const std::string, ProbStringInfo);
	//����Ԫ������System��ĳ�Ա����
	friend bool System::ChangeProblemInfo(const Problem*, const unsigned int);
};

