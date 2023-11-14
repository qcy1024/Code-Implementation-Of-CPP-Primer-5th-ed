#ifndef __STRVEC__H
#define __STRVEC__H
#include <string>
#include <memory>

const int INITCAPACITY = 10;

class StrVec
{
public:
	typedef std::string* iterator;
	//StrVec() : elements(nullptr), firstFree(nullptr), cap(nullptr) {};
	/*构造函数与拷贝控制*/
	StrVec();
	/*若参数是(左值)引用，调用的就是拷贝版本的；若参数是右值引用，调用的就是移动版本的*/
	/*移动版本的构造函数与赋值运算符承诺要移动的是临时对象，它马上要面临赋值或销毁。*/
	//拷贝构造与拷贝赋值运算符
	StrVec(const StrVec& vec);
	StrVec& operator = (const StrVec& vec);
	//移动构造与移动赋值运算符
	StrVec(StrVec&& vec) noexcept;
	StrVec& operator = (StrVec&& vec) noexcept;
	~StrVec();

	/*接口*/
	void push_back(const std::string& str);
	std::string& operator [] (int i) const { return elements[i]; };
	
	std::string* begin() { return elements; };
	std::string* end() { return firstFree; };

	size_t size() const { return firstFree - elements; };
	size_t capacity() const { return cap - elements; };

private:
	//为什么把alloc定义成静态成员会出现链接时错误？
	std::allocator<std::string> alloc;
	//使用三个指针实现底层数据表示：elements指向容器第一个元素，firstFree指向容器已
	//有元素的最后一个位置的下一个位置，cap指向已分配内存的最后一个位置的下一个位置
	std::string* elements;
	std::string* firstFree;
	std::string* cap;

	/*工具函数*/
	void Free();
	void reallocate();
	//检查当前StrVec是否至少还有空间容纳一个新元素，若没有空间，则调用reallocate分配更多内存。
	void chk_n_alloc();
};

#endif // !__STRVEC__H