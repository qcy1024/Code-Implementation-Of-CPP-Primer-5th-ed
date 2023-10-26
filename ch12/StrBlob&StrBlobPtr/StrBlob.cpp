#include "StrBlob.h"
#include <stdexcept>
#include <memory>
#include "StrBlobPtr.h"
/*��������*/
//����һ��StrBlob����ʱ������һ��vector<string>�Ŀռ䣬��dataָ����
StrBlob::StrBlob() :data(std::make_shared<std::vector<std::string> >()) 
{

}
//�����б��ʼ���Ĺ��캯��
StrBlob::StrBlob(std::initializer_list<std::string> il) :
	data(std::make_shared<std::vector<std::string> > (il))
{

}

/*���ߺ���*/
void StrBlob::check(size_type i, const std::string& msg) const
{
	if (i >= data->size())
	{
		throw std::out_of_range(msg);
	}
}

/*�ӿ�*/
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

/*��Ϊ��Ա���������������*/
//��ӡStrBlob�������ַ���
std::ostream& operator << (std::ostream& os, const StrBlob& str)
{
	for (StrBlobPtr iter = str.begin(); iter != str.end(); ++iter)
	{
		os << *iter << "  ";
	}
	return os;
}

//�����±������ʵ��StrBlob���±����
std::string& StrBlob::operator [] (size_type t)
{
	check(t, "out_of_range");
	return (*data)[t];
}

/*��Ϊ�ǳ�Ա���������������*/
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
	//�ñ�׼��vector��<�����ʵ�����ǵ�<�����
	return *lhs.data < *rhs.data;
}

bool operator > (const StrBlob& lhs, const StrBlob& rhs)
{
	//�ñ�׼��vector��>�����ʵ�����ǵ�>�����
	return *lhs.data > *rhs.data;
}

