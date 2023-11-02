#### Blob: 一个模板类，实现了共享底层数据的vector<T>。 BlobPtr:  模板类，Blob的迭代器类型。
模板参数列表：
template <typename T> class Blob;
template <typename T> class BlobPtr;

Blob与BlobPtr是用模板重写的StrBlob以及StrBlobPtr(它们是模板参数T为std::string时的实例)。Blob使用标准库智能指针shared_ptr保存容器底层数据，保留默认拷贝构造函数以及拷贝赋值运算符使得多个Blob对象共享底层数据。Blob已实现StrBlob的所有操作：

1. push_back(const T& elem)

2. pop_back();

3. empty();

4. size();

5. begin();

6. end();

7. operator [] (size_type t);push_back(const std::string& elem)

8. front();

9. back();

10. operator std::vector<std::T>() const; //类型转换运算符,将Blob对象转换成对应的vector类型
//用于Blob<T>类型的比较运算符，作为非成员函数
11. operator == (const Blob<T>&, const Blob<T>&);
    
12. operator != (const Blob<T>&, const Blob<T>&);
    
13. operator < (const Blob<T>&, const Blob<T>&);
    
14. operator > (const Blob<T>&, const Blob<T>& );


BlobPtr使用标准库智能指针weak_ptr指向对应的Blob的数据。BlobPtr已实现StrBlobPtr操作：

1. operator * () const;
2. operator ++ ();
3. operator -- ();
4. operator ++ (int);
5. operator -- (int);
6. operator -> ();
//用于迭代器比较的==和!=运算符，作为非成员函数
7. operator == (const BlobPtr<T>&, const BlobPtr<T>&)
8. operator != (const BlobPtr<T>&, const BlobPtr<T>&)
