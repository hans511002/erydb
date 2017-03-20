// ==============================================================
//progame      Common::Array  base vector<T>
//company      hans
//copyright    Copyright (c) hans  2007-4     2008-03
//version      1.0
//Author       hans
//date         2007-4     2008-03
//description  Common namespace
//				This library is free software. Permission to use, copy,
//				modify and redistribute it for any purpose is hereby granted
//				without fee, provided that the above copyright notice appear
//				in all copies.
// ==============================================================

#ifndef __Common_Array_H__
#define __Common_Array_H__
#include <vector>
using namespace std;
//#include "Common.h"
namespace Common
{
	///	<summary>
	/// ģ��������.�̳�std:vector&lt;T>
	///	<summary>
	///	<remarks>
	/// ժҪ:
    ///     ģ��������.��ӷ���ķ��ʲ�������
	///
	/// �� ��: ��Զ��
    /// �� ��: 2007-4-25
    /// �� ��: 1.0
	///	</remarks>
	/// <example><code>Array&lt;int> tarr;ss
	///	tarr[5]=5;//��ֱ�ӷ���δ���������
    /// </code></example>
	template <class T = int> class Array:public vector<T>
	{

	public:
		Array(int size = 0);
		//
		// ժҪ:
		//     ���ڷ������õ���������졣
		//
		// ����:
		//   args:
		//      new ����������ָ�롣
		//	size:
		//		���鳤��
		//
		Array(T * args,int size,bool del=false);
		inline T& operator[](int i);
		inline bool operator==(Array<T> &arr);
		inline bool operator!=(Array<T> &arr){return !(this->operator ==(arr));};
		inline int size();
		//Array & operator=(Array &arr);
		//operator T *();
		//Array &operator=(const Array &arr);

		
		 //ժҪ:
		 //    ȷ����ʵ���Ƿ�����һ��ָ���� Common.Array ���������ͬ��ֵ��
		 //
		 //����:
		 //  value:
		 //    Common.Array��
		 //
		 //���ؽ��:
		 //    ��� value ������ֵ���ʵ����ͬ����Ϊ true������Ϊ false��
		inline bool equals(Array &arr);
		//
		// ժҪ:
		//     ȷ����ʵ���Ƿ��������ΪT�Ķ����Ƴ����һ������Ӧlength��һ��
		//
		// ���ؽ��:
		//     Aaary �����е����һ�� ���� T ���󡣵�length=0ʱ���� null ��
		inline T  pop();
		//
		// ժҪ:
		//     ��һ������T�Ķ�����ӵ�Array����������Ӧlength��һ��
		//
		// ����:
		//   value:
		//     Common.Array��
		//
		// ���ؽ��:
		//     Aaary �����е����һ�� ���� T ����
		inline T& push(T t);
		//
		// ժҪ:
		//     ȷ����ʵ���Ƿ��������ΪT�Ķ����Ƴ���һ������Ӧlength��һ��
		//
		// ���ؽ��:
		//     Aaary �����еĵ�һ�� ���� T ���󡣵�length=0ʱ���� null ��
		inline T shift();
		//
		// ժҪ:
		//     ��һ������T�Ķ�����ӵ�Array�������ǰ�棬��Ӧlength��һ��
		//
		// ����:
		//   value:
		//     Common.Array��
		//
		// ���ؽ��:
		//     Aaary �����еĵ�һ�� ���� T ����
		inline T& unshift(T t);
		inline T remove(int i)
		{
			T t=this->at(i);
			this->erase(this->begin()+i);
			return t;
		};
	};

	template <class T> Array<T> ::Array(int size): vector<T>(size){}
 
	template <class T> Array<T> ::Array(T * args,int size,bool del): vector<T>(size)
	{
		if(size>0)
		{
			for(int i=0;i<size;i++)
			{
				this->at(i)=args[i];
			}
			if(del)delete[] args;
		}
	}
	template <class T> inline T& Array<T>::operator[](int i)
	{
		while(i<0)
			i=this->size()+i;
		if(i<=(int)(this->size()-1))
		{
			return this->at(i);
		}
		else
		{
			//this->push_back(T()); 
			this->resize(i+1);
			return this->at(i);
		}
	}
	template <class T> inline bool Array<T>::operator==(Array<T> &arr)
	{
		if(this->size()!=arr.size())return false;
		int len=this->size();
		for(int i=0;i<len;i++)
		{
			if(this->at(i)!=arr.at(i))	return false;
		}
		return true;
	}

	//
	// ժҪ:
	//     ȷ����ʵ���Ƿ�����һ��ָ���� Common.Array ���������ͬ��ֵ��
	//
	// ����:
	//   value:
	//     Common.Array��
	//
	// ���ؽ��:
	//     ��� value ������ֵ���ʵ����ͬ����Ϊ true������Ϊ false��
	template <class T> inline bool Array<T>::equals(Array &arr)
	{
		if(arr.size()==this->size())
		{
			for(int i=0;i<(int)this->size();i++)
			{
				if(arr[i]!=this->at(i)) return false;
			}
			return true;
		}
		else
			return false;
	}
	//
	// ժҪ:
	//     ȷ����ʵ���Ƿ��������ΪT�Ķ����Ƴ����һ������Ӧlength��һ��
	//
	// ���ؽ��:
	//     Aaary �����е����һ�� ���� T ���󡣵�length=0ʱ���� null ��
	template <class T> inline T Array<T>::pop()
	{
		if(this->size()>0)
		{
			T t=this->at((int)this->size()-1);
			this->pop_back();
			return t;
		}
		else
			return T();
	}
	//
	// ժҪ:
	//     ��һ������T�Ķ�����ӵ�Array����������Ӧlength��һ��
	//
	// ����:
	//   value:
	//     Common.Array��
	//
	// ���ؽ��:
	//     Aaary �����е����һ�� ���� T ����
	template <class T> inline T & Array<T>::push(T t)
	{
		this->push_back(t);
		return this->at((int)this->size()-1);
	}
	//
	// ժҪ:
	//     ȷ����ʵ���Ƿ��������ΪT�Ķ����Ƴ���һ����
	//
	// ���ؽ��:
	//     Aaary �����еĵ�һ�� ���� T ���󡣵�length=0ʱ���� null ��
	template <class T> inline T Array<T>::shift()
	{
		T t=T();
		if(this->size()>0)
		{
			t=this->at(0);
			this->erase(this->begin());
		}
		return t;
	}
	//
	// ժҪ:
	//     ��һ������T�Ķ�����ӵ�Array�������ǰ�档
	//
	// ����:
	//   value:
	//     Common.Array��
	//
	// ���ؽ��:
	//     Aaary �����еĵ�һ�� ���� T ����
	template <class T> inline T & Array<T>::unshift(T t)
	{
		this->insert(this->begin(),t);
		return this->at(0);
	}
	template <class T> inline int  Array<T>::size()
	{
		return (int)vector<T>::size();
	}

}

#endif
