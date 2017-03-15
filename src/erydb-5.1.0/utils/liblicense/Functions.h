// ==============================================================
//progame      Common functions  declare
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

#ifndef __common_Functions_H__
#define __common_Functions_H__
#include "LicCommon.h"

typedef long long Long;

// 摘要:
//     公共函数头文件.
//
//注意：
//		为提高效率，所有类对象都建议采用引用参数传递。
//
//
// 作 者: 邹远贵
// 日 期: 2007-4-25
// 版 本: 1.0
//
namespace Common
{ 
	///	<summary>
	///	获取环境变量值
	///	<code>原型：inline string getEnv(const string &amp; name);</code>
	///	</summary>
	///	<param name="name">变量名</param>
	///	<returns>环境变量值</returns>
	inline string getEnv(const string & name)
	{
		char* val = getenv(name.c_str());
		if(val==NULL)return "";
		return val;
	} 
	inline string operator+(const int b,const string a)
	{
		//int ss=1;test
		char t[12];
		sprintf(t,"%d",b);
		return t+a;
	}
	inline string operator+(const string a,const int b)
	{
		char t[12];
		sprintf(t,"%d",b);
		return a+t;
	}
	inline string operator+(const long b,const string a)
	{
		char t[12];
		sprintf(t,"%ld",b);
		return t+a;
	}
	inline string operator+(const string a,const long b)
	{
		char t[12];
		sprintf(t,"%ld",b);
		return a+t;
	}
	inline string operator+(const double b,const string a)
	{
		char t[12];
		sprintf(t,"%f",b);
		return t+a;
	}
	inline string operator+(const string a,const double b)
	{
		char t[12];
		sprintf(t,"%f",b);
		return a+t;
	}

#define ELEM(i)   arr[i-1]
#define SWAP(i,j) temp = ELEM(i), ELEM(i) = ELEM(j), ELEM(j) = temp
	template <class className> void sort(vector<className> & arr,int (compare)(className & val1,className & val2))
	{
		int i, j, k, n = arr.size();
		className temp;
		if (n <= 1) 
		{ 
			return;
		}
		for (i = n/2, j = i; i >= 1; i--) 
		{ 
			k = i;
			className topId = ELEM(k);
			do
			{ 
				if (k*2 == n || (*compare)(ELEM(k*2), ELEM(k*2+1)) > 0) 
				{ 
					if ((*compare)(topId, ELEM(k*2)) >= 0) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if ((*compare)(topId, ELEM(k*2+1)) >= 0)
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} while (k <= j);
			ELEM(k) = topId; 
		}
		for (i = n; i >= 2; i--)
		{ 
			SWAP(1,i);
			className topId = ELEM(1);
			for (k = 1, j = (i-1)/2; k <= j;)
			{ 
				if (k*2 == i-1 || (*compare)(ELEM(k*2), ELEM(k*2+1)) > 0) 
				{
					if ((*compare)(topId, ELEM(k*2)) >= 0) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if ((*compare)(topId, ELEM(k*2+1)) >= 0)
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} 
			ELEM(k) = topId; 
		}

	}

	template <class className> void sort(vector<className> & arr)
	{
		int i, j, k, n = arr.size();
		className temp;
		if (n <= 1) 
		{ 
			return;
		}
		for (i = n/2, j = i; i >= 1; i--) 
		{ 
			k = i;
			className topId = ELEM(k);
			do
			{ 
				if (k*2 == n || ELEM(k*2) > ELEM(k*2+1))
				{ 
					if (topId>= ELEM(k*2)) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if (topId >= ELEM(k*2+1))
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} while (k <= j);
			ELEM(k) = topId; 
		}
		for (i = n; i >= 2; i--)
		{ 
			SWAP(1,i);
			className topId = ELEM(1);
			for (k = 1, j = (i-1)/2; k <= j;)
			{ 
				if (k*2 == i-1 || ELEM(k*2) > ELEM(k*2+1))
				{
					if(topId >= ELEM(k*2))
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if (topId >= ELEM(k*2+1))
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} 
			ELEM(k) = topId; 
		}
	}
	template <class className> void sort(className *arr,int (compare)(className & val1,className & val2),int size)
	{
		int i, j, k, n = size;
		className temp;
		if (n <= 1) 
		{ 
			return;
		}
		for (i = n/2, j = i; i >= 1; i--) 
		{ 
			k = i;
			className topId = ELEM(k);
			do
			{ 
				if (k*2 == n || (*compare)(ELEM(k*2), ELEM(k*2+1)) > 0) 
				{ 
					if ((*compare)(topId, ELEM(k*2)) >= 0) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if ((*compare)(topId, ELEM(k*2+1)) >= 0)
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} while (k <= j);
			ELEM(k) = topId; 
		}
		for (i = n; i >= 2; i--)
		{ 
			SWAP(1,i);
			className topId = ELEM(1);
			for (k = 1, j = (i-1)/2; k <= j;)
			{ 
				if (k*2 == i-1 || (*compare)(ELEM(k*2), ELEM(k*2+1)) > 0) 
				{
					if ((*compare)(topId, ELEM(k*2)) >= 0) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if ((*compare)(topId, ELEM(k*2+1)) >= 0)
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} 
			ELEM(k) = topId; 
		}

	}

	template <class className> void sort(className * arr,int size)
	{
		int i, j, k, n = size;
		className temp;
		if (n <= 1) 
		{ 
			return;
		}
		for (i = n/2, j = i; i >= 1; i--) 
		{ 
			k = i;
			className topId = ELEM(k);
			do
			{ 
				if (k*2 == n || ELEM(k*2) > ELEM(k*2+1))
				{ 
					if (topId>= ELEM(k*2)) 
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if (topId >= ELEM(k*2+1))
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} while (k <= j);
			ELEM(k) = topId; 
		}
		for (i = n; i >= 2; i--)
		{ 
			SWAP(1,i);
			className topId = ELEM(1);
			for (k = 1, j = (i-1)/2; k <= j;)
			{ 
				if (k*2 == i-1 || ELEM(k*2) > ELEM(k*2+1))
				{
					if(topId >= ELEM(k*2))
					{
						break;
					}
					ELEM(k) = ELEM(k*2);
					k = k*2;
				}
				else
				{ 
					if (topId >= ELEM(k*2+1))
					{
						break;
					}
					ELEM(k)= ELEM(k*2+1);
					k = k*2+1;
				}
			} 
			ELEM(k) = topId; 
		}
	}
#undef ELEM
#undef SWAP
	 

}
#endif
//
