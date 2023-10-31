#include <iostream>
#include "Blob.h"
using namespace std;

int main()
{
    Blob<string> strBlob({ "Hell0,", "World" });
    for (int i = 0; i < strBlob.size(); i++)
        cout << strBlob[i] << endl;
    return 0;
}
