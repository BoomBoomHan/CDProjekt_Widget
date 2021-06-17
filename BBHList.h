#pragma once
#include "FunctionLibrary.h"
#include <vector>

//����ģ����Ƚ�����,�����Ķ���ֻ��.h����.cpp�ļ��������������붨�嶼д��.h��
//���ڴ洢ѧ����������Ŀ�ı�
template<typename T>
struct BBHList
{
private:
	std::vector<T> list;//��
	unsigned int size;
public:
	//���캯��
	BBHList()
		:size(0)
	{
		
	}

	//���沢�ͷ�����Ԫ��
	~BBHList()
	{
		list.clear();
	}

	//��ȡ��Ԫ�صĸ���
	unsigned int GetSize() const
	{
		return size;
	}

	//��β�����Ԫ��,�ڶ�������Ϊ�˱��Ƿ���ӵ���ظ�Ԫ��,���ɹ��򷵻���
	bool AddElement(const T& element, const bool arrayIsUnique = true)
	{
		if (arrayIsUnique)
		{
			const bool isUnique = CheckUnique(element);
			if (!isUnique)
			{
				return false;
			}
		}
		list.push_back(element);
		size++;
		return true;
	}

	//ɾ��ָ��Ԫ��,���ɹ��򷵻���
	bool DeleteElement(unsigned int index)
	{
		if (!FunctionLibrary::IsInRange(index, 0u, size, true))
		{
			return false;
		}
		list.erase(list.begin() + index);
		size--;
		return true;
	}

	//��ȡ��i��Ԫ��
	T& operator [](const unsigned int index)
	{
		if (FunctionLibrary::IsInRange(index, 0u, size, true))
		{
			return list[index];
		}
		return list[size - 1];
	}

	//����Ƿ�����ͬԪ��,�����򷵻���
	bool CheckUnique(const T& element) const
	{
		for (unsigned int i = 0; i < size; i++)
		{
			if (element == list[i])
			{
				return false;
			}
		}
		return true;
	}

	void ClearDatas()
	{
		list.clear();
		size = 0;
	}
};