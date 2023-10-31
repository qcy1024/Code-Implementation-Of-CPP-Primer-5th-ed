#pragma once
#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>
template<typename T> class Blob
{
public:
	typedef typename std::vector<T>::size_type size_type;

	//构造函数与拷贝控制
	Blob<T>() : data(std::make_shared<std::vector<T> >()) {};
	Blob<T>(std::initializer_list<T> li) : data(std::make_shared<std::vector<T> >(li)) {};
	
	//接口
	void push_back(const T& elem);
	T& operator [] (size_type i);
	size_type size() { return data->size(); };

private:
	std::shared_ptr<std::vector<T> > data;
	void check(size_type idx, const std::string msg);
};

//工具函数
template<typename T> void Blob<T>::check(size_type idx, const std::string msg)
{
	if (idx >= data->size())
		throw std::out_of_range(msg);
	return;
}

//push_back
template<typename T> void Blob<T>::push_back(const T& elem)
{
	data->push_back(elem);
	return;
}

//下标访问运算符
template<typename T> T& Blob<T>::operator [] (size_type i)
{
	check(i, "out of range");
	return (*data)[i];
}