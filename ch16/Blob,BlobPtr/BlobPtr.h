#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
template <typename T> class Blob;
template<typename T> class BlobPtr
{ 
	typedef typename std::vector<T>::size_type size_type;
public:
	/*���캯���뿽������*/
	//��������������������ָ���κεط���weak_ptr���Բ�����ʼ������ʱ��������ָ����δ�����
	BlobPtr<T>() : curr(0) { };
	BlobPtr<T>(const Blob<T>& tmpBlob, size_type idx) : curr(idx), wptr(tmpBlob.data) {};

	/*�ӿ�*/
	//�����������
	T& operator * ();


private:
	//weak_ptr������������
	std::weak_ptr<std::vector<T> > wptr;
	//���ߺ��������weak_ptrָ��������Ƿ���ڣ��Լ��±�λ���Ƿ�Ϸ�
	std::shared_ptr<std::vector<T> > check(size_type idx, const std::string msg);
	//��ǰλ��
	size_type curr;
};

//���ߺ��������weak_ptrָ��������Ƿ���ڣ��Լ��±�λ���Ƿ�Ϸ��������ͨ������ָ�����ݵ�shared_ptr
//��ͼ�õ����������Ѿ������ڵ����ݣ����߲��Ϸ����±�λ�ý������쳣��
template <typename T>
std::shared_ptr<std::vector<T> > BlobPtr<T>::check(size_type idx, const std::string msg)
{
	std::shared_ptr<std::vector<T> > p = wptr.lock();
	if (!p)
		throw std::runtime_error("unbound Blob");
	if (idx >= p->size())
		throw std::out_of_range(msg);
	return p;
}

//�����������
template <typename T> T& BlobPtr<T>::operator * ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return (*p)[curr];
}