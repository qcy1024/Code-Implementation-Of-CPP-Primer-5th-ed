#include "StrBlob.h"
#include <stdexcept>
#include <memory>
#include "StrBlobPtr.h"
//定义一个StrBlob对象时，申请一个vector<string>的空间，令data指向它
StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string> >()) 
{

}
//包含列表初始化的构造函数
StrBlob::StrBlob(std::initializer_list<std::string> il) :
	data(std::make_shared<std::vector<std::string> > (il))
{

}

void StrBlob::check(size_type i, const std::string& msg) const
{
	if (i >= data->size())
	{
		throw std::out_of_range(msg);
	}
}

void StrBlob::pop_back()
{
	check(0, "out of range");
	data->pop_back();
}

std::string& StrBlob::front()
{
	check(0, "out_of_range");
	return data->front();
}

std::string& StrBlob::back()
{
	check(0, "out_of_range");
	return data->back();
}

const std::string& StrBlob::front() const
{
	check(0, "out_of_range");
	return data->front();
}

const std::string& StrBlob::back() const
{
	check(0, "out_of_range");
	return data->back();
}

//重载下标运算符实现StrBlob的下标访问
std::string& StrBlob::operator [] (size_type t)
{
	check(t, "out_of_range");
	return (*data)[t];
}

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}
