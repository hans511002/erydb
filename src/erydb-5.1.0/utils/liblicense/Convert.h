// ==============================================================
//progame      Common::Convert var type convert 
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

#ifndef __Common_Convert_H__
#define __Common_Convert_H__
#include "LicCommon.h"  


namespace Common
{
	///	<summary>
	///	基本数据类型转换类
	///	</summary>
	///	<remarks>
	///	基本使用的STD标准函数，集中整理，因全是内联函数，帮不会降低性能，方便编程时调用。
	///	方法如下：<code>
	/// static int ParseInt(string s);//
	/// static double ParseDouble(string s);//
	/// inline static int ToInt(string s);//等效于atoi(s.c_str());
	/// inline static int ToInt(bool b);//等效于b==true?1:0;
	/// inline static long ToLong(string s);//等效于atol(s.c_str());
	/// inline static long long ToLLong(string s);//等效于atoll(s.c_str()); 
	///               HP有时不存在atoll函数，可在Common.h 364行添加 #define atoll(c){long long l=0;ato_t(l,c);return l;}
	/// inline static float  ToFloat(string s);//等效于atof(s.c_str()); 
	/// inline static double ToDouble(string s);//等效于atof(s.c_str()); 
	/// inline static double Ceil(double d);//等效于ceil(d); 向上舍入
	/// inline static float  Ceil(float d);//等效于ceil(d);
	/// inline static double Floor(double d);//等效于floor(d); 向下舍入
	/// inline static float  Floor(float d);//等效于floor(d);
	///	inline static string ToString(int i) ;
	///	inline static string ToString(long l) ;
	///	inline static string ToString(long long l) ;
	///	inline static string ToString(double d,int p=0,int r=0) ;
	///	inline static string ToString(bool b) ;
	///	inline static bool ToBool(const string &amp;s) ;
	/// inline static void convertBits(unsigned char * src,unsigned char * dest,int len);//网络序列反转
	/// inline static void convertBits(unsigned char * src,int len);//网络序列反转</code>
	///	</remarks>
    /// <example><code>
	///	String a=Convert::ToString(54.464,4,2);
    /// </code></example>
	class Convert
	{
	public:
		//
		//摘要：
		//		模仿DateTime::StringParser::ParseInt
		inline static int ParseInt(string s)
		{
			return ParseInt(s.c_str());
		};
		static int ParseInt(const char * s)
		{
			int pos=0,i=0;
			while (((s[pos] == ' ') || (s[pos] == '\t')))
			{
				pos++;
			}
			bool flag=false;
			if (s[pos] == '-')
			{
				flag=true;
				pos++;
			}
			while (((s[pos] >= '0') && (s[pos] <= '9')))
			{
				i = (((i * 10) + s[pos]) - 0x30);
				if (i < 0)
				{
					return 0;
				}
				pos++;
			}
			if(flag)i=-i;
			return i;
		}
		//
		//摘要：
		//		模仿DateTime::StringParser::ParseInt
		static double ParseDouble(string s)
		{
			return ParseDouble(s.c_str());
		};
		static double ParseDouble(const char * s)
		{
			int pos=0;
			double d=0;
			while (((s[pos] == ' ') || (s[pos] == '\t')))
			{
				pos++;
			}
			bool flag=false;
			if (s[pos] == '-')
			{
				flag=true;
				pos++;
			}
			while (((s[pos] >= '0') && (s[pos] <= '9')))
			{
				d = (((d * 10) + s[pos]) - 0x30);
				if (d < 0)
				{
					return 0.0;
				}
				pos++;
			}
			if (s[0] == '.')
			{
				pos++;
				double temp=10;
				while ((s[pos] >= '0') && (s[pos] <= '9'))
				{
					d += ((s[pos] - '0') / temp);
					temp *= 10;
					pos++;
				}
			}
			if(flag)d=0-d;
			return d;
		}

		inline static int ToInt(string s)
		{
			return atoi(s.c_str());
		}inline static int ToInt(const char * s)
		{
			return atoi(s );
		}
		inline static int ToInt(bool b)
		{
			if(b)return 1;else return 0;
		}
		inline static long ToLong(string s)
		{
			return atol(s.c_str());
		}
		inline static long long ToLLong(string s)
		{
			return atoll(s.c_str());
		}
		inline static float  ToFloat(string s)
		{
			return (float)atof(s.c_str());
		}	
		inline static double ToDouble(string s)
		{
			return ParseDouble(s.c_str());
		}
		inline static double ToDouble(char * s)
		{
			return ParseDouble(s);
		}
		inline static double Ceil(double d)
		{
			return ceil(d);
		}
		inline static float  Ceil(float d)
		{
			return ceil(d);
		}

		inline static double Floor(double d)
		{
			return floor(d);
		}
		inline static float  Floor(float d)
		{
			return floor(d);
		}
		inline static string ToString(int i)
		{
			char p[40];
			p[39]=0;
			// 系统函数
			int len=sprintf(p,"%d",i);
			//return String('F',50000000);
			return p;//value= String(p,0,len);

			// 自己运算
			//int a=0,b=0,l=38;
			//while(i>0)
			//{
			//	a = i % 10 ;
			//	i = i / 10 ;
			//	p[l--] = a + 48;
			//}
			//return p;
		}
		inline static string ToString(long l)
		{
			char p[40];
			int len=sprintf(p,"%ld",l);
			return p;//value=  String(p,0,len);
		}
		inline static string ToString(long long l)
		{
			char p[40];
			int len=sprintf(p,"%lld",l);
			return p;//value=  String(p,0,len);
		}
		inline static string ToString(double d,int p=0,int r=0)
		{
			char buffer[40];
			char *f;
			char bf[20];
			f=bf;
			if(p==0 && r==0)
			{
				f[0]='%';
				f[1]='f';
				f[2]='\0';
			}
			else if(p==0 && r!=0)
			{
				sprintf(f,"%%.%df",r);
			}
			else if(p!=0 && r==0)
			{
				sprintf(f,"%%%d.f",p);
			}
			else if(p!=0 && r!=0)
			{
				sprintf(f,"%%%d.%df",p,r);
			}
			int len=sprintf(buffer,f,d);
			buffer[len]='\0';
			return string(buffer);
		}
		inline static string ToString(bool b)
		{
			if(b)return string("true");
			else return string("false");
		}

		inline static bool ToBool(const string &s)
		{
			return (strcmp(s.c_str(),"true")==0 || strcmp(s.c_str(),"TRUE"));
		};
		inline static void convertBits(unsigned char * src,unsigned char * dest,int len)
		{
			for(int i=0;i<len;i++)
			{
				dest[i]=src[len-i-1];
			}
		};
		inline static void convertBits(unsigned char * src,int len)
		{
			for(int i=0;i<len/2;i++)
			{
				char c=src[i];
				src[i]=src[len-1-i];
				src[len-1-i]=c;
			}
		};
		inline static string ToString0X(long v)
		{
			return ToString0X((long long )v);

			char data[20];
			char pa[10];
			memset(pa,0,10);
			memset(data,'0',20);
			long long ll=v;
			unsigned int h=ll>>32;
			unsigned int l=ll;
			int len=sprintf(pa,"%0x",l);
			if(h==0)
			{
				if(len<8)
				{
					strcpy(data+2,pa);
					return data;
				}
				else
					return pa;
			}
			else
			{
				len=sprintf(pa,"%0x",h);
				strcpy(data+8-len,pa);
				data[8]='f';
				len=sprintf(pa,"%0x",l);
				strcpy(data+16-len,pa);
				return data;
			}
		}
		inline static string ToString0X(int v)
		{
			char data[20];
			char pa[10];
			memset(pa,0,10);
			memset(data,'0',20);
			int len=sprintf(pa,"0x%0x",v);
			if(len<8)
			{
				strcpy(data+2,pa);
				return data;
			}
			else
				return pa;
		}
		inline static string ToString0X(long long v)
		{

			char data[20];
			sprintf(data,"0x%llx",v);
			return data;

			char pa[10];
			memset(pa,0,10);
			memset(data,'0',20);
			unsigned int h=v>>32;
			unsigned int l=v;
			int len=sprintf(pa,"%0x",h);
			strcpy(data+8-len,pa);
			memset(data+8,'f',12);
			data[8]='f';
			len=sprintf(pa,"%0x",l);
			strcpy(data+16-len,pa);
			return data;
		}
		//打印地址
		inline static string ToString0X(void * v)
		{
			if(sizeof(v)==8)
			{
				return ToString0X((long long)v);
			}
			else
			{
				long l=(long long)v;
				return ToString0X(l);
			}
		}
		inline static int toInt(unsigned char bt[4])
		{
			int res=(((int)bt[3]) << 24) + (((int)bt[2]) << 16 )+ (((int)bt[1]) << 8) + (int)bt[0];
			return res;
		}
		inline static long long toLong(unsigned char bt[8])
		{
			return   (((long long)bt[7]) << 56) + (((long long)bt[6]) << 48) + (((long long)bt[5]) << 40) + ((long long)bt[4] << 32)
				+ ((long long)bt[3] << 24) + ((long long)bt[2] << 16) + ((long long)bt[1] << 8 )+ ((long long)bt[0]);
		}
	};
}

#endif
