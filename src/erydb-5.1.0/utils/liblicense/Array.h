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
	/// 模板数组类.继承std:vector&lt;T>
	///	<summary>
	///	<remarks>
	/// 摘要:
    ///     模板数组类.添加方便的访问操作方法
	///
	/// 作 者: 邹远贵
    /// 日 期: 2007-4-25
    /// 版 本: 1.0
	///	</remarks>
	/// <example><code>Array&lt;int> tarr;ss
	///	tarr[5]=5;//可直接访问未申请的区域
    /// </code></example>
	template <class T = int> class Array:public vector<T>
	{

	public:
		Array(int size = 0);
		//
		// 摘要:
		//     用于返回引用的数组对象构造。
		//
		// 参数:
		//   args:
		//      new 产生的数组指针。
		//	size:
		//		数组长度
		//
		Array(T * args,int size,bool del=false);
		inline T& operator[](int i);
		inline bool operator==(Array<T> &arr);
		inline bool operator!=(Array<T> &arr){return !(this->operator ==(arr));};
		inline int size();
		//Array & operator=(Array &arr);
		//operator T *();
		//Array &operator=(const Array &arr);

		
		 //摘要:
		 //    确定此实例是否与另一个指定的 Common.Array 对象具有相同的值。
		 //
		 //参数:
		 //  value:
		 //    Common.Array。
		 //
		 //返回结果:
		 //    如果 value 参数的值与此实例相同，则为 true；否则为 false。
		inline bool equals(Array &arr);
		//
		// 摘要:
		//     确定此实例是否存在类型为T的对象并移出最后一个，相应length减一。
		//
		// 返回结果:
		//     Aaary 对象中的最后一个 类型 T 对象。当length=0时返回 null 。
		inline T  pop();
		//
		// 摘要:
		//     将一个类型T的对象添加到Array对象的最后，相应length加一。
		//
		// 参数:
		//   value:
		//     Common.Array。
		//
		// 返回结果:
		//     Aaary 对象中的最后一个 类型 T 对象。
		inline T& push(T t);
		//
		// 摘要:
		//     确定此实例是否存在类型为T的对象并移出第一个，相应length减一。
		//
		// 返回结果:
		//     Aaary 对象中的第一个 类型 T 对象。当length=0时返回 null 。
		inline T shift();
		//
		// 摘要:
		//     将一个类型T的对象添加到Array对象的最前面，相应length加一。
		//
		// 参数:
		//   value:
		//     Common.Array。
		//
		// 返回结果:
		//     Aaary 对象中的第一个 类型 T 对象。
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
	// 摘要:
	//     确定此实例是否与另一个指定的 Common.Array 对象具有相同的值。
	//
	// 参数:
	//   value:
	//     Common.Array。
	//
	// 返回结果:
	//     如果 value 参数的值与此实例相同，则为 true；否则为 false。
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
	// 摘要:
	//     确定此实例是否存在类型为T的对象并移出最后一个，相应length减一。
	//
	// 返回结果:
	//     Aaary 对象中的最后一个 类型 T 对象。当length=0时返回 null 。
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
	// 摘要:
	//     将一个类型T的对象添加到Array对象的最后，相应length加一。
	//
	// 参数:
	//   value:
	//     Common.Array。
	//
	// 返回结果:
	//     Aaary 对象中的最后一个 类型 T 对象。
	template <class T> inline T & Array<T>::push(T t)
	{
		this->push_back(t);
		return this->at((int)this->size()-1);
	}
	//
	// 摘要:
	//     确定此实例是否存在类型为T的对象并移出第一个。
	//
	// 返回结果:
	//     Aaary 对象中的第一个 类型 T 对象。当length=0时返回 null 。
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
	// 摘要:
	//     将一个类型T的对象添加到Array对象的最前面。
	//
	// 参数:
	//   value:
	//     Common.Array。
	//
	// 返回结果:
	//     Aaary 对象中的第一个 类型 T 对象。
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
