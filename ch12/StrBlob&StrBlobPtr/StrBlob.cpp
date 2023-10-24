#include "StrBlob.h"
#include <stdexcept>
#include <memory>
#include "StrBlobPtr.h"
//����һ��StrBlob����ʱ������һ��vector<string>�Ŀռ䣬��dataָ����
StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string> >()) 
{

}
//�����б��ʼ���Ĺ��캯��
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

//�����±������ʵ��StrBlob���±����
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
