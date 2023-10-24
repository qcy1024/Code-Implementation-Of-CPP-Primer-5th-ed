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
	//拷贝控制
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);

	//接口
	void push_back(const std::string& elem) { data->push_back(elem); };
	void pop_back();
	bool empty() const { return data->empty(); };
	std::string& front();
	std::string& back();
	//通过this指针的底层const重载front()和back(),使得常量StrBlob也能调用front()和back
	const std::string& front() const;
	const std::string& back() const;

	//返回begin()和end()迭代器
	StrBlobPtr begin();
	StrBlobPtr end();


	//
	std::string& operator [] (size_type t);

private:
	std::shared_ptr<std::vector<std::string> > data;
	//工具函数，若位置i不合法，抛出一个msg表示的异常
	void check(size_type i, const std::string& msg) const;
};

#endif