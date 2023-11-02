#pragma once
#include <memory>
#include <vector>
#include <string>
#include <stdexcept>
template <typename T> class Blob;
template<typename T> class BlobPtr;
template <typename T> bool operator != (const BlobPtr<T>&, const BlobPtr<T>&);
template <typename T> bool operator == (const BlobPtr<T>&, const BlobPtr<T>&);
template<typename T> class BlobPtr
{ 
	typedef typename std::vector<T>::size_type size_type;
	friend bool operator !=<T> (const BlobPtr<T>&, const BlobPtr<T>&);
	friend bool operator ==<T> (const BlobPtr<T>&, const BlobPtr<T>&);
public:
	/*���캯���뿽������*/
	//��������������������ָ���κεط���weak_ptr���Բ�����ʼ������ʱ��������ָ����δ�����
	BlobPtr<T>() : curr(0) { };
	BlobPtr<T>(const Blob<T>& tmpBlob, size_type idx) : curr(idx), wptr(tmpBlob.data) {};

	/*�ӿ�*/
	//�����������
	T& operator * ();
	//������������ݼ������
	BlobPtr<T>& operator ++ ();
	BlobPtr<T>& operator -- ();
	//���ð汾
	BlobPtr<T> operator ++ (int);
	BlobPtr<T> operator -- (int);

	//��Ա���������->
	T* operator -> ();

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
		//����ʱ�쳣
		throw std::runtime_error("unbound Blob");
	if (idx >= p->size())
		//Խ���쳣
		throw std::out_of_range(msg);
	return p;
}

//�����������
template <typename T> T& BlobPtr<T>::operator * ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return (*p)[curr];
}

//������������ݼ������: ++ �� --
template <typename T> BlobPtr<T>& BlobPtr<T>::operator ++ ()
{
	check(this->curr, "out of range");
	this->curr += 1;
	return *this;
}

template <typename T> BlobPtr<T>& BlobPtr<T>::operator -- ()
{
	check(this->curr, "out of range");
	this->curr -= 1;
	return *this;
}
//���ð汾
template <typename T> BlobPtr<T> BlobPtr<T>::operator ++ (int)
{
	BlobPtr<T> ret(*this);
	this->curr += 1;
	return ret;
}

template <typename T> BlobPtr<T> BlobPtr<T>::operator -- (int)
{
	BlobPtr<T> ret(*this);
	this->curr -= 1;
	return ret;
}

//�ǳ�Ա��������������==�������!=�����
template <typename T> 
bool operator == (const BlobPtr<T>& it1, const BlobPtr<T>& it2)
{
	std::shared_ptr<std::vector<T> > p1 = it1.wptr.lock();
	std::shared_ptr<std::vector<T> > p2 = it2.wptr.lock();
	if (p1 != p2)
		return false;
	if (it1.curr != it2.curr)
		return false;
	return true;
}

template <typename T>
bool operator != (const BlobPtr<T>& it1, const BlobPtr<T>& it2)
{
	return !(it1 == it2);
}

//���س�Ա���������->
template <typename T> T* BlobPtr<T>::operator -> ()
{
	std::shared_ptr<std::vector<T> > p = check(curr, "out of range");
	return &(*p)[curr];
}

