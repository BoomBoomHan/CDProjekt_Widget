#pragma once
#include "FunctionLibrary.h"
#include <vector>

//由于模板类比较特殊,这个类的定义只有.h而无.cpp文件，函数的声明与定义都写在.h内
//用于存储学生及课设题目的表单
template<typename T>
struct BBHList
{
private:
	std::vector<T> list;//表单
	unsigned int size;
public:
	//构造函数
	BBHList()
		:size(0)
	{
		
	}

	//保存并释放所有元素
	~BBHList()
	{
		list.clear();
	}

	//获取表单元素的个数
	unsigned int GetSize() const
	{
		return size;
	}

	//在尾部添加元素,第二个参数为此表单是否不能拥有重复元素,若成功则返回真
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

	//删除指定元素,若成功则返回真
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

	//获取第i个元素
	T& operator [](const unsigned int index)
	{
		if (FunctionLibrary::IsInRange(index, 0u, size, true))
		{
			return list[index];
		}
		return list[size - 1];
	}

	//检查是否有相同元素,若无则返回真
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