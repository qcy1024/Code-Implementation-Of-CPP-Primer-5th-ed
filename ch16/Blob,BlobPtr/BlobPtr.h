#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
template <typename T> class Blob;
template<typename T> class BlobPtr
{ 
	typedef typename std::vector<T>::size_type size_type;
public:
	/*构造函数与拷贝控制*/
	//创建迭代器但并不让它指向任何地方，weak_ptr可以不被初始化，此时迭代器的指向是未定义的
	BlobPtr<T>() : curr(0) { };
	BlobPtr<T>(const Blob<T>& tmpBlob, size_type idx) : curr(idx), wptr(tmpBlob.data) {};

	/*接口*/
	//解引用运算符
	T& operator * ();


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
		throw std::runtime_error("unbound Blob");
	if (idx >= p->size())
		throw std::out_of_range(msg);
	return p;
}

//解引用运算符
template <typename T> T& BlobPtr<T>::operator * ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return (*p)[curr];
}