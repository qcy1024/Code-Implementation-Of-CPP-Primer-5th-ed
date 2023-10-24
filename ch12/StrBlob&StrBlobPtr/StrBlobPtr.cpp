#include "StrBlobPtr.h"
#include <stdexcept>
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

StrBlobPtr& StrBlobPtr::operator ++ ()
{
	check(curr, "out of range");
	this->curr += 1;
	return *this;
}

//迭代器要支持的!=运算符
bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto lsp = lhs.wptr.lock();
	auto rsp = rhs.wptr.lock();
	return !(lsp == rsp && lhs.curr == rhs.curr);
}
