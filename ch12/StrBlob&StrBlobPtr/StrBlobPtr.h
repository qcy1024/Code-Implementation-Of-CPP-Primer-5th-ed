#ifndef __STRBLOBPTR__H
#define __STRBLOBPTR__H

#include <vector>
#include <string>
#include <memory>
#include "StrBlob.h"
class StrBlobPtr
{
	friend bool operator !=(const StrBlobPtr& lhs, const StrBlobPtr& rhs);
public:
	/*拷贝控制*/
	StrBlobPtr() :curr(0) {};
	StrBlobPtr(const StrBlob& str,std::size_t curr = 0) : wptr(str.data),curr(curr) {};
	
	/*接口*/
	std::string& deref();
	StrBlobPtr& incr();
	StrBlobPtr& operator ++ ();
	StrBlobPtr& operator -- ();
	StrBlobPtr operator ++ (int);
	StrBlobPtr operator -- (int);
	std::string& operator * () const;
	std::string* operator -> () const;
private:
	std::weak_ptr<std::vector<std::string> > wptr;
	std::size_t curr;
	/*工具函数：检查数据还存不存在以及下标是否合法*/
	std::shared_ptr<std::vector<std::string> > check(std::size_t i, const std::string& msg) const;
};

//迭代器的!=运算符，非成员函数
bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs);

#endif // !__STRBLOBPTR__H