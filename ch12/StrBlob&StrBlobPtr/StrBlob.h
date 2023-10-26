#ifndef __STRBLOB__H
#define __STRBLOB__H
/***************************************** *
* һ������ײ����ݵ�vector<string>         *
* ��C++Primer�������StrBlob�Լ�StrBlobPtr *
* ����������ʵ��                           *
****************************************** */
#include <string>
#include <memory>
#include <vector>
#include <iostream>
class StrBlobPtr;
class StrBlob
{
	friend class StrBlobPtr;		//StrBlobPtr�Ǹ������ĵ���������
	friend std::ostream& operator << (std::ostream& os, const StrBlob& str);
	friend bool operator == (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator != (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator < (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator > (const StrBlob& lhs, const StrBlob& rhs);
public:
	typedef std::vector<std::string>::size_type size_type;

	/*��������*/
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	//�������캯���Ϳ�����ֵ�����ʹ�ñ������ϳɵİ汾��
	StrBlob(const StrBlob&) = default;
	StrBlob& operator = (const StrBlob&) = default;

	/*�ӿ�*/
	void push_back(const std::string& elem) { data->push_back(elem); };
	void pop_back();
	bool empty() const { return data->empty(); };
	size_type size() const { return data->size(); };
	std::string& front();
	std::string& back();
	//ͨ��thisָ��ĵײ�const����front()��back(),ʹ�ó���StrBlobҲ�ܵ���front()��back
	const std::string& front() const;
	const std::string& back() const;
	//����begin()��end()������
	StrBlobPtr begin();
	StrBlobPtr end();
	//�����������thisָ�����const���صĻ���ʹ��const StrBlob���͵Ķ������begin()
	//��end����ִ���StrBlob*�޷�ָ��const StrBlob���͵Ķ���
	StrBlobPtr begin() const;
	StrBlobPtr end() const;
	//��Ϊ��Ա���������������
	std::string& operator [] (size_type t);

	//����ת����������ú���֧�ֽ�һ��StrBlob�����ת��Ϊһ��vector<string>����
	operator std::vector<std::string>() const { return *data; };

private:
	std::shared_ptr<std::vector<std::string> > data;
	//���ߺ�������λ��i���Ϸ����׳�һ��msg��ʾ���쳣
	void check(size_type i, const std::string& msg) const;
};

/*��Ϊ�ǳ�Ա���������������*/
//���StrBlob�е������ַ���
std::ostream& operator << (std::ostream& os, const StrBlob& str);

//����StrBlob���е������
bool operator == (const StrBlob& lhs, const StrBlob& rhs);
bool operator != (const StrBlob& lhs, const StrBlob& rhs);

bool operator < (const StrBlob& lhs, const StrBlob& rhs);
bool operator > (const StrBlob& lhs, const StrBlob& rhs);

#endif