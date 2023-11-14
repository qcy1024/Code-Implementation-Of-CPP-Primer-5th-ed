#include <iostream>
#include "StrVec.h"

//析构函数
StrVec::~StrVec()
{
    Free();
}

//无参构造函数
StrVec::StrVec()
{
    elements = alloc.allocate(INITCAPACITY);
    firstFree = elements;
    cap = elements + INITCAPACITY;
}

//拷贝时令新容器的capacity为原来容器的size
//StrVec::StrVec(const StrVec& vec)
//{
//    std::string* thisElements = alloc.allocate(vec.size());
//    std::string* thisFirstFree = std::uninitialized_copy(vec.elements, vec.firstFree, thisElements);
//    elements = thisElements;
//    firstFree = cap = thisFirstFree;
//}

//拷贝时令新容器的capacity为原来容器的capacity
StrVec::StrVec(const StrVec& vec)
{
    size_t thisCapacity = vec.capacity();
    std::string* thisElements = alloc.allocate(thisCapacity);
    std::string* thisFirstFree = std::uninitialized_copy(vec.elements, vec.firstFree, thisElements);
    elements = thisElements;
    firstFree = thisFirstFree;
    cap = elements + thisCapacity;
}

//注意拷贝赋值运算符必须正确地处理自赋值
StrVec& StrVec::operator = (const StrVec& vec)
{
    size_t thisCapacity = vec.capacity();
    std::string* newElements = alloc.allocate(thisCapacity);
    std::string* newFirstFree = std::uninitialized_copy(vec.elements, vec.firstFree, newElements);
    Free();
    elements = newElements;
    firstFree = newFirstFree;
    cap = newElements + thisCapacity;
    return *this;
}

//程序员如果能保证移动构造与移动赋值运算符不会抛出异常，就应该将它声明为noexcept。
StrVec::StrVec(StrVec&& vec) noexcept
{
    elements = vec.elements;
    firstFree = vec.firstFree;
    cap = vec.cap;
    vec.elements = vec.firstFree = vec.cap = nullptr;
}

StrVec& StrVec::operator = (StrVec&& vec) noexcept
{
    std::string* newElements = vec.elements;
    std::string* newFirstFree = vec.firstFree;
    std::string* newCap = vec.cap;
    if (elements != nullptr)
    {
        for (std::string* it = firstFree; it != elements; )
        {
            alloc.destroy(--it);
        }
        alloc.deallocate(elements, capacity());
    }
    elements = newElements;
    firstFree = newFirstFree;
    cap = newCap;
    vec.elements = vec.firstFree = vec.cap = nullptr;
    return *this;
}

//销毁当前容器中指针范围elements与firstFree的元素，并释放分配的capacity大小的空间
void StrVec::Free()
{
    if (elements == nullptr) return;
    //allocateor销毁对象和释放内存常用循环套路
    for (std::string* it = firstFree; it != elements; )
    {
        alloc.destroy(--it);
    }
    alloc.deallocate(elements, capacity());
}

//拷贝版本，容器内容不变，但底层内存重新分配(分配后容器 capacity 2倍于原来大小)
//void StrVec::reallocate()
//{
//    //两个同类型的指针，都是nullptr也是可以相减的，得到的结果是0
//    size_t newCapacity = size() ? size() * 2 : 1;
//    std::string* newElements = alloc.allocate(newCapacity);
//    std::string* newFirstFree = std::uninitialized_copy(elements, firstFree, newElements);
//    
//    Free();
//    elements = newElements;
//    firstFree = newFirstFree;
//    cap = newElements + newCapacity;
//}

//移动版本，用了std::string的移动构造
void StrVec::reallocate()
{
    size_t newCapacity = size() ? size() * 2 : 1;
    std::string* newElements = alloc.allocate(newCapacity);
    std::string* moveSrc = elements;
    std::string* moveDest = newElements;
    for (std::string* moveSrc = elements; moveSrc != firstFree; ++moveSrc)
    {
        alloc.construct(moveDest++, std::move(*moveSrc));
    }
    Free();
    elements = newElements;
    firstFree = moveDest;
    cap = elements + newCapacity;
}

void StrVec::chk_n_alloc()
{
    if (firstFree == cap)
        reallocate();
}

void StrVec::push_back(const std::string& str)
{
    chk_n_alloc();
    alloc.construct(firstFree++, str);
}


