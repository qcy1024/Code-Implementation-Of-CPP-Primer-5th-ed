#include "StrBlobPtr.h"
#include <stdexcept>
//����StrBlobPtr(������)����ָ������ݻ��治���ڣ��Լ���ǰ������ָ��������Ƿ�Ϸ�
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

//������Ҫ֧�ֵĵ���/�ݼ������
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

//���ð汾
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

//������Ҫ֧�ֵ�!=��������ǳ�Ա����
bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs)
{
	auto lsp = lhs.wptr.lock();
	auto rsp = rhs.wptr.lock();
	return !(lsp == rsp && lhs.curr == rhs.curr);
}

//�����������������
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
