#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
template <typename T> class Blob;
template<typename T> class BlobPtr;
template <typename T> bool operator != (const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator == (const BlobPtr<T>&, const BlobPtr<T>&);
template<typename T> class BlobPtr
{ 
	typedef typename std::vector<T>::size_type size_type;
	friend bool operator !=<T> (const BlobPtr<T>&, const BlobPtr<T>&);
	friend bool operator ==<T> (const BlobPtr<T>&, const BlobPtr<T>&);
public:
	/*构造函数与拷贝控制*/
	//创建迭代器但并不让它指向任何地方，weak_ptr可以不被初始化，此时迭代器的指向是未定义的
	BlobPtr<T>() : curr(0) { };
	BlobPtr<T>(const Blob<T>& tmpBlob, size_type idx) : curr(idx), wptr(tmpBlob.data) {};

	/*接口*/
	//解引用运算符
	T& operator * ();
	//迭代器递增与递减运算符
	BlobPtr<T>& operator ++ ();
	BlobPtr<T>& operator -- ();
	//后置版本
	BlobPtr<T> operator ++ (int);
	BlobPtr<T> operator -- (int);

	//成员访问运算符->
	T* operator -> ();

private:
	//weak_ptr，弱共享数据
	std::weak_ptr<std::vector<T> > wptr;
	//工具函数，检查weak_ptr指向的数据是否存在，以及下标位置是否合法
	std::shared_ptr<std::vector<T> > check(size_type idx, const std::string msg);
	//当前位置
	size_type curr;
};

//工具函数，检查weak_ptr指向的数据是否存在，以及下标位置是否合法，若检查通过返回指向数据的shared_ptr
//试图用迭代器访问已经不存在的数据，或者不合法的下标位置将引发异常。
template <typename T>
std::shared_ptr<std::vector<T> > BlobPtr<T>::check(size_type idx, const std::string msg)
{
	std::shared_ptr<std::vector<T> > p = wptr.lock();
	if (!p)
		//运行时异常
		throw std::runtime_error("unbound Blob");
	if (idx >= p->size())
		//越界异常
		throw std::out_of_range(msg);
	return p;
}

//解引用运算符
template <typename T> T& BlobPtr<T>::operator * ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return (*p)[curr];
}

//迭代器递增与递减运算符: ++ 与 --
template <typename T> BlobPtr<T>& BlobPtr<T>::operator ++ ()
{
	check(this->curr, "out of range");
	this->curr += 1;
	return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator -- ()
{
	check(this->curr, "out of range");
	this->curr -= 1;
	return *this;
}
//后置版本
template <typename T> BlobPtr<T> BlobPtr<T>::operator ++ (int)
{
	BlobPtr<T> ret(*this);
	this->curr += 1;
	return ret;
}

template <typename T> BlobPtr<T> BlobPtr<T>::operator -- (int)
{
	BlobPtr<T> ret(*this);
	this->curr -= 1;
	return ret;
}

//非成员函数：迭代器的==运算符与!=运算符
template <typename T> 
bool operator == (const BlobPtr<T>& it1, const BlobPtr<T>& it2)
{
	std::shared_ptr<std::vector<T> > p1 = it1.wptr.lock();
	std::shared_ptr<std::vector<T> > p2 = it2.wptr.lock();
	if (p1 != p2)
		return false;
	if (it1.curr != it2.curr)
		return false;
	return true;
}

template <typename T>
bool operator != (const BlobPtr<T>& it1, const BlobPtr<T>& it2)
{
	return !(it1 == it2);
}

//重载成员访问运算符->
template <typename T> T* BlobPtr<T>::operator -> ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return &(*p)[curr];
}

