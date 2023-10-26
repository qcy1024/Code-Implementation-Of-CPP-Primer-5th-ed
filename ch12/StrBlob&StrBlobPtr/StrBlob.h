#ifndef __STRBLOB__H
#define __STRBLOB__H
/***************************************** *
* 一个共享底层数据的vector<string>         *
* 对C++Primer第五版中StrBlob以及StrBlobPtr *
* 案例的完整实现                           *
****************************************** */
#include <string>
#include <memory>
#include <vector>
#include <iostream>
class StrBlobPtr;
class StrBlob
{
	friend class StrBlobPtr;		//StrBlobPtr是该容器的迭代器类型
	friend std::ostream& operator << (std::ostream& os, const StrBlob& str);
	friend bool operator == (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator != (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator < (const StrBlob& lhs, const StrBlob& rhs);
	friend bool operator > (const StrBlob& lhs, const StrBlob& rhs);
public:
	typedef std::vector<std::string>::size_type size_type;

	/*拷贝控制*/
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	//拷贝构造函数和拷贝赋值运算符使用编译器合成的版本。
	StrBlob(const StrBlob&) = default;
	StrBlob& operator = (const StrBlob&) = default;

	/*接口*/
	void push_back(const std::string& elem) { data->push_back(elem); };
	void pop_back();
	bool empty() const { return data->empty(); };
	size_type size() const { return data->size(); };
	std::string& front();
	std::string& back();
	//通过this指针的底层const重载front()和back(),使得常量StrBlob也能调用front()和back
	const std::string& front() const;
	const std::string& back() const;
	//返回begin()和end()迭代器
	StrBlobPtr begin();
	StrBlobPtr end();
	//这里如果不对this指针进行const重载的话，使用const StrBlob类型的对象调用begin()
	//和end会出现错误：StrBlob*无法指向const StrBlob类型的对象
	StrBlobPtr begin() const;
	StrBlobPtr end() const;
	//作为成员函数的重载运算符
	std::string& operator [] (size_type t);

	//类型转换运算符，该函数支持将一个StrBlob类对象转换为一个vector<string>对象。
	operator std::vector<std::string>() const { return *data; };

private:
	std::shared_ptr<std::vector<std::string> > data;
	//工具函数，若位置i不合法，抛出一个msg表示的异常
	void check(size_type i, const std::string& msg) const;
};

/*作为非成员函数的重载运算符*/
//输出StrBlob中的所有字符串
std::ostream& operator << (std::ostream& os, const StrBlob& str);

//用于StrBlob的判等运算符
bool operator == (const StrBlob& lhs, const StrBlob& rhs);
bool operator != (const StrBlob& lhs, const StrBlob& rhs);

bool operator < (const StrBlob& lhs, const StrBlob& rhs);
bool operator > (const StrBlob& lhs, const StrBlob& rhs);

#endif