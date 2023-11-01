#### Blob: 一个共享底层数据的vector。 BlobPtr:  Blob的迭代器类型。

Blob使用标准库智能指针shared_ptr保存容器底层数据，保留默认拷贝构造函数以及拷贝赋值运算符使得多个Blob对象共享底层数据。Blob已实现操作：

1. push_back(const T& elem)

2. pop_back();

3. empty();

4. size();

5. begin();

6. end();

7. operator [] (size_type t);

   

BlobPtr使用标准库智能指针weak_ptr指向对应的Blob的数据。Blob已实现操作：

1. operator * () const;

   