#include "StrBlob.h"
#include <stdexcept>
#include <memory>
#include "StrBlobPtr.h"
/*拷贝控制*/
//定义一个StrBlob对象时，申请一个vector<string>的空间，令data指向它
StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string> >()) 
{

}
//包含列表初始化的构造函数
StrBlob::StrBlob(std::initializer_list<std::string> il) :
	data(std::make_shared<std::vector<std::string> > (il))
{

}

/*工具函数*/
void StrBlob::check(size_type i, const std::string& msg) const
{
	if (i >= data->size())
	{
		throw std::out_of_range(msg);
	}
}

/*接口*/
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

StrBlobPtr StrBlob::begin()
{
	return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end()
{
	return StrBlobPtr(*this, data->size());
}

StrBlobPtr StrBlob::begin() const
{
	return StrBlobPtr(*this, 0);
}

StrBlobPtr StrBlob::end() const
{
	return StrBlobPtr(*this, data->size());
}

/*作为成员函数的运算符重载*/
//打印StrBlob中所有字符串
std::ostream& operator << (std::ostream& os, const StrBlob& str)
{
	for (StrBlobPtr iter = str.begin(); iter != str.end(); ++iter)
	{
		os << *iter << "  ";
	}
	return os;
}

//重载下标运算符实现StrBlob的下标访问
std::string& StrBlob::operator [] (size_type t)
{
	check(t, "out_of_range");
	return (*data)[t];
}

/*作为非成员函数的运算符重载*/
bool operator == (const StrBlob& lhs, const StrBlob& rhs)
{
	if (lhs.size() != rhs.size())
		return false;
	for (StrBlobPtr it1 = lhs.begin(), it2 = rhs.begin(); it1 != lhs.end() && it2 != rhs.end(); 
		++it1, ++it2)
	{
		if (*it1 != *it2)
			return false;
	}
	return true;
}

bool operator != (const StrBlob& lhs, const StrBlob& rhs)
{
	return !(lhs == rhs);
}

bool operator < (const StrBlob& lhs, const StrBlob& rhs)
{
	//用标准库vector的<运算符实现我们的<运算符
	return *lhs.data < *rhs.data;
}

bool operator > (const StrBlob& lhs, const StrBlob& rhs)
{
	//用标准库vector的>运算符实现我们的>运算符
	return *lhs.data > *rhs.data;
}

