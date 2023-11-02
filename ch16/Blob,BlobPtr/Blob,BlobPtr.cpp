#include <iostream>
#include "Blob.h"
#include "BlobPtr.h"

using namespace std;

int main()
{
    Blob<string> strBlob({ "Hell0,", "World","OK" });
    Blob<string> strBlob2 = { "Hello" };
    Blob<string> strBlob3 = { "Hell0,", "World","OK" };
    for (unsigned int i = 0; i < strBlob.size(); i++)
        cout << strBlob[i] << endl;
    for (BlobPtr<string> it = strBlob.begin(); it != strBlob.end(); ++it )
        cout << *it << endl;
    cout << strBlob.front() << endl;
    cout << strBlob.back() << endl;
    cout << endl;
    cout << "---------------------------" << endl << endl;
    cout << (strBlob == strBlob3) << endl;
    cout << (strBlob != strBlob3) << endl;
    cout << (strBlob < strBlob3) << endl;
    cout << (strBlob > strBlob3) << endl;
    std::vector<string> v = strBlob;
    for (auto item : v)
        cout << item << endl;
    auto iter = strBlob.begin();
    cout << iter->size() << endl;
    return 0;
}
