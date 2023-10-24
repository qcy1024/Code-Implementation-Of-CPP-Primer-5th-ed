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
	StrBlobPtr() :curr(0) {};
	StrBlobPtr(StrBlob& str,std::size_t curr = 0) : wptr(str.data),curr(curr) {};
	std::string& deref();
	StrBlobPtr& incr();

	StrBlobPtr& operator ++ ();

private:
	std::weak_ptr<std::vector<std::string> > wptr;
	std::size_t curr;
	std::shared_ptr<std::vector<std::string> > check(std::size_t i, const std::string& msg) const;
};

bool operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs);

#endif // !__STRBLOBPTR__H