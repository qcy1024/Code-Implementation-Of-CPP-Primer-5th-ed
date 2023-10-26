#include <iostream>
#include <vector>
#include "StrBlob.h"
#include "StrBlobPtr.h"
#include <memory>
using namespace std;

int main()
{
    //测试构造函数
    StrBlob s1({ "Hello,","World","!" });
    //测试拷贝赋值运算符
    StrBlob s2 = s1;
    //测试重载的==运算符
    cout << (s1 == s2) << endl;
    //测试size()、重载的[]运算符
    for (StrBlob::size_type i = 0; i < s1.size(); i++)
        s1[i] = "asdfasdf";
    //测试push_back
    s1.push_back("dasfa");
    //测试StrBlobPtr的迭代器访问、begin()、end()函数
    for (StrBlobPtr iter = s1.begin(); iter != s1.end(); ++iter)
    {
        //测试解引用运算符*
        cout << *iter << endl;
    }
    //测试重载的输出运算符<<
    cout << s1 << endl;
    cout << (s1 == s2) << endl;
    StrBlob s3({ "azd","asdfasdf","asdfasdf" });
    //测试重载的<运算符
    cout << (s3 < s1) << endl;
    for (StrBlobPtr iter = s1.begin(); iter != s1.end(); ++iter)
    {
        //测试StrBlobPtr的成员访问运算符->
        cout << iter->size() << endl;
    }
    //测试类型转换运算符
    vector<string> v(s1);
    for (auto item : v)
        cout << item << endl;
    return 0;
}

