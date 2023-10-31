StrBlob: 一个共享底层数据的vector<string>。
StrBlobPtr: StrBlob的迭代器类型。

StrBlob使用标准库智能指针shared_ptr保存容器底层数据，保留默认拷贝构造函数以及拷贝赋值运算符使得多个StrBlob对象共享底层数据。StrBlob已实现操作：
1. push_back(const std::string& elem)
2. pop_back();
3. empty();
4. size();
5. front();
6. back();
7. begin();
8. end();
9. operator [] (size_type t);
10. operator std::vector<std::string>() const;  //类型转换运算符,将StrBlob对象转换成对应的vector<string>类型
11. operator << (std::ostream& os, const StrBlob& str);
12. operator == (const StrBlob& lhs, const StrBlob& rhs);
13. operator != (const StrBlob& lhs, const StrBlob& rhs);
14. operator < (const StrBlob& lhs, const StrBlob& rhs);
15. operator > (const StrBlob& lhs, const StrBlob& rhs);

StrBlobPtr使用标准库智能指针weak_ptr指向对应的StrBlob的数据。StrBlob已实现操作：
1. operator ++ ();
2. operator -- ();
3. operator ++ (int);
4. operator -- (int);
5. operator * () const;
6. operator -> () const;
7. operator != (const StrBlobPtr& lhs, const StrBlobPtr& rhs);
