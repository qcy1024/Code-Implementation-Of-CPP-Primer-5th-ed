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
	/*��������*/
	StrBlobPtr() :curr(0) {};
	StrBlobPtr(const StrBlob& str,std::size_t curr = 0) : wptr(str.data),curr(curr) {};
	
	/*�ӿ�*/
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
	/*���ߺ�����������ݻ��治�����Լ��±��Ƿ�Ϸ�*/
	std::shared_ptr<std::vector<std::string> > check(std::size_t i, const std::string& msg) const;
};

//��������!=��������ǳ�Ա����
bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs);

#endif // !__STRBLOBPTR__H