#ifndef __STRBLOB__H
#define __STRBLOB__H

#include <string>
#include <memory>
#include <vector>
class StrBlobPtr;
class StrBlob
{
	friend class StrBlobPtr;
public:
	typedef std::vector<std::string>::size_type size_type;
	//��������
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);

	//�ӿ�
	void push_back(const std::string& elem) { data->push_back(elem); };
	void pop_back();
	bool empty() const { return data->empty(); };
	std::string& front();
	std::string& back();
	//ͨ��thisָ��ĵײ�const����front()��back(),ʹ�ó���StrBlobҲ�ܵ���front()��back
	const std::string& front() const;
	const std::string& back() const;

	//����begin()��end()������
	StrBlobPtr begin();
	StrBlobPtr end();


	//
	std::string& operator [] (size_type t);

private:
	std::shared_ptr<std::vector<std::string> > data;
	//���ߺ�������λ��i���Ϸ����׳�һ��msg��ʾ���쳣
	void check(size_type i, const std::string& msg) const;
};

#endif