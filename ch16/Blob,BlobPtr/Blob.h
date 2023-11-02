#pragma once
#include <vector>
#include <memory>
#include <initializer_list>
#include <stdexcept>
#include "BlobPtr.h"

template <typename T> bool operator == (const Blob<T>&, const Blob<T>&);
template <typename T> bool operator != (const Blob<T>&, const Blob<T>&);
template <typename T> bool operator <  (const Blob<T>&, const Blob<T>&);
template <typename T> bool operator >  (const Blob<T>&, const Blob<T>&);

template<typename T> class Blob
{
	friend class BlobPtr<T>;
	friend bool operator == <T> (const Blob<T>&, const Blob<T>&);
	friend bool operator != <T> (const Blob<T>&, const Blob<T>&);
	friend bool operator <  <T> (const Blob<T>&, const Blob<T>&);
	friend bool operator >  <T> (const Blob<T>&, const Blob<T>&);
public:
	typedef typename std::vector<T>::size_type size_type;

	/*构造函数与拷贝控制*/
	Blob<T>() : data(std::make_shared<std::vector<T> >()) {};
	Blob<T>(std::initializer_list<T> li) : data(std::make_shared<std::vector<T> >(li)) {};
	
	/*接口*/
	void push_back(const T& elem);
	void pop_back();
	T& operator [] (size_type i);
	size_type size() const { return data->size(); };
	bool empty() const { return data->empty(); };
	T front() const { return data->front(); };
	T back() const { return data->back(); };
	//类型转换运算符：将Blob<T>转换成对应的std::vector<T>类型
	operator std::vector<T>() { return *data; };
	//返回首尾迭代器
	BlobPtr<T> begin() const;
	BlobPtr<T> end() const;

private:
	std::shared_ptr<std::vector<T> > data;
	void check(size_type idx, const std::string msg) const;
};

//工具函数
template<typename T> void Blob<T>::check(size_type idx, const std::string msg) const 
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

//pop_back
template <typename T> void Blob<T>::pop_back()
{
	data->pop_back();
	return;
}

//下标访问运算符
template<typename T> T& Blob<T>::operator [] (size_type i) 
{
	check(i, "out of range");
	return (*data)[i];
}

//begin()和end()返回首尾迭代器
template <typename T> BlobPtr<T> Blob<T>::begin() const
{
	BlobPtr<T> ret(*this, 0);
	return ret;
}

template <typename T> BlobPtr<T> Blob<T>::end() const
{
	BlobPtr<T> ret(*this, 0 + this->size());
	return ret;
}

//重载的各种比较运算符
template <typename T> 
bool operator == (const Blob<T>& Blob1, const Blob<T>& Blob2)
{
	return *Blob1.data == *Blob2.data;
}

template <typename T>
bool operator != (const Blob<T>& Blob1, const Blob<T>& Blob2)
{
	return *Blob1.data != *Blob2.data;
}

template <typename T> 
bool operator < (const Blob<T>& Blob1, const Blob<T>& Blob2)
{
	return *Blob1.data < *Blob2.data;
}

template <typename T> 
bool operator > (const Blob<T>& Blob1, const Blob<T>& Blob2)
{
	return *Blob1.data > *Blob2.data;
}
