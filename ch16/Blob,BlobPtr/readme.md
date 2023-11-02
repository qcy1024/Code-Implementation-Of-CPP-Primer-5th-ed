#### Blob: 一个模板类，实现了共享底层数据的vector<T>。 BlobPtr:  模板类，Blob的迭代器类型。

Blob与BlobPtr是用模板重写的StrBlob以及StrBlobPtr(它们是模板参数T为std::string时的实例)。Blob使用标准库智能指针shared_ptr保存容器底层数据，保留默认拷贝构造函数以及拷贝赋值运算符使得多个Blob对象共享底层数据。Blob已实现StrBlob的所有操作：

1. push_back(const T& elem)

2. pop_back();

3. empty();

4. size();

5. begin();

6. end();

7. operator [] (size_type t);

   

BlobPtr使用标准库智能指针weak_ptr指向对应的Blob的数据。BlobPtr已实现StrBlobPtr操作：

1. operator * () const;

   
