#include "StrBlobPtr.h"
#include <stdexcept>
//检查该StrBlobPtr(迭代器)对象指向的数据还存不存在，以及当前迭代器指向的索引是否合法
std::shared_ptr<std::vector<std::string> > StrBlobPtr::check(std::size_t i, const std::string& msg) const
{
	std::shared_ptr<std::vector<std::string> > ret = wptr.lock();
	if (!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if (i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

std::string& StrBlobPtr::deref()
{
	std::shared_ptr<std::vector<std::string> > p = check(curr, "out of range");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "out of range");
	curr = curr + 1;
	return *this;
}

//迭代器要支持的递增/递减运算符
StrBlobPtr& StrBlobPtr::operator ++ ()
{
	check(curr, "out of range");
	this->curr += 1;
	return *this;
}

StrBlobPtr& StrBlobPtr::operator -- ()
{
	check(curr, "out of range");
	this->curr -= 1;
	return *this;
}

//后置版本
StrBlobPtr StrBlobPtr::operator ++ (int)
{
	StrBlobPtr ret = *this;
	check(curr, "out of range");
	curr += 1;
	return ret;
}

StrBlobPtr StrBlobPtr::operator -- (int)
{
	StrBlobPtr ret = *this;
	check(curr, "out of range");
	curr -= 1;
	return ret;
}

//迭代器要支持的!=运算符，非成员函数
bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto lsp = lhs.wptr.lock();
	auto rsp = rhs.wptr.lock();
	return !(lsp == rsp && lhs.curr == rhs.curr);
}

//迭代器解引用运算符
std::string& StrBlobPtr::operator * () const
{
	std::shared_ptr<std::vector<std::string> > p = check(curr, "out of range");
	return (*p)[curr];
}

std::string* StrBlobPtr::operator -> () const
{
	std::shared_ptr<std::vector<std::string> > p = wptr.lock();
	return &(*p)[curr];
}
