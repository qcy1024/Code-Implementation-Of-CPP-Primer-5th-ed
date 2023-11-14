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
	/*���캯���뿽������*/
	StrVec();
	/*��������(��ֵ)���ã����õľ��ǿ����汾�ģ�����������ֵ���ã����õľ����ƶ��汾��*/
	/*�ƶ��汾�Ĺ��캯���븳ֵ�������ŵҪ�ƶ�������ʱ����������Ҫ���ٸ�ֵ�����١�*/
	//���������뿽����ֵ�����
	StrVec(const StrVec& vec);
	StrVec& operator = (const StrVec& vec);
	//�ƶ��������ƶ���ֵ�����
	StrVec(StrVec&& vec) noexcept;
	StrVec& operator = (StrVec&& vec) noexcept;
	~StrVec();

	/*�ӿ�*/
	void push_back(const std::string& str);
	std::string& operator [] (int i) const { return elements[i]; };
	
	std::string* begin() { return elements; };
	std::string* end() { return firstFree; };

	size_t size() const { return firstFree - elements; };
	size_t capacity() const { return cap - elements; };

private:
	//Ϊʲô��alloc����ɾ�̬��Ա���������ʱ����
	std::allocator<std::string> alloc;
	//ʹ������ָ��ʵ�ֵײ����ݱ�ʾ��elementsָ��������һ��Ԫ�أ�firstFreeָ��������
	//��Ԫ�ص����һ��λ�õ���һ��λ�ã�capָ���ѷ����ڴ�����һ��λ�õ���һ��λ��
	std::string* elements;
	std::string* firstFree;
	std::string* cap;

	/*���ߺ���*/
	void Free();
	void reallocate();
	//��鵱ǰStrVec�Ƿ����ٻ��пռ�����һ����Ԫ�أ���û�пռ䣬�����reallocate��������ڴ档
	void chk_n_alloc();
};

#endif // !__STRVEC__H