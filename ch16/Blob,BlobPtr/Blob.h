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

	/*���캯���뿽������*/
	Blob<T>() : data(std::make_shared<std::vector<T> >()) {};
	Blob<T>(std::initializer_list<T> li) : data(std::make_shared<std::vector<T> >(li)) {};
	
	/*�ӿ�*/
	void push_back(const T& elem);
	void pop_back();
	T& operator [] (size_type i);
	size_type size() const { return data->size(); };
	bool empty() const { return data->empty(); };
	T front() const { return data->front(); };
	T back() const { return data->back(); };
	//����ת�����������Blob<T>ת���ɶ�Ӧ��std::vector<T>����
	operator std::vector<T>() { return *data; };
	//������β������
	BlobPtr<T> begin() const;
	BlobPtr<T> end() const;

private:
	std::shared_ptr<std::vector<T> > data;
	void check(size_type idx, const std::string msg) const;
};

//���ߺ���
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

//�±���������
template<typename T> T& Blob<T>::operator [] (size_type i) 
{
	check(i, "out of range");
	return (*data)[i];
}

//begin()��end()������β������
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

//���صĸ��ֱȽ������
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
