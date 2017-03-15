// ==============================================================
//progame      Common::String base string
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

#ifndef __Common_String_H__
#define __Common_String_H__
#include "LicCommon.h" 
#include "Array.h" 
#include "Convert.h" 
#include "Enums.h"
#include "hashMath.h"

namespace Common   
{
#define USE_CHAR_ARRAY_MAP

#ifdef USE_CHAR_ARRAY_MAP
	const unsigned char charUpperToLower[] = {
			  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
			 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 
			 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 
			 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 
			 64, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
			112,113,114,115,116,117,118,119,120,121,122, 91, 92, 93, 94, 95, 
			 96, 97, 98, 99,100,101,102,103,104,105,106,107,108,109,110,111,
			112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,
			128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,
			144,145,146,147,148,149,150,151,152,153,154,155,156,157,158,159,
			160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,
			176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,
			192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,
			208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223,
			224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,
			240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255
		};
	const unsigned char charCtypeMap[256] = {
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 00..07    ........ */
	  0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00,  /* 08..0f    ........ */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 10..17    ........ */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 18..1f    ........ */
	  0x01, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00,  /* 20..27     !"#$%&' */
	  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 28..2f    ()*+,-./ */
	  0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,  /* 30..37    01234567 */
	  0x0c, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 38..3f    89:;<=>? */

	  0x00, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x0a, 0x02,  /* 40..47    @ABCDEFG */
	  0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,  /* 48..4f    HIJKLMNO */
	  0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,  /* 50..57    PQRSTUVW */
	  0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x40,  /* 58..5f    XYZ[\]^_ */
	  0x00, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x2a, 0x22,  /* 60..67    `abcdefg */
	  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,  /* 68..6f    hijklmno */
	  0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,  /* 70..77    pqrstuvw */
	  0x22, 0x22, 0x22, 0x00, 0x00, 0x00, 0x00, 0x00,  /* 78..7f    xyz{|}~. */

	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* 80..87    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* 88..8f    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* 90..97    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* 98..9f    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* a0..a7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* a8..af    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* b0..b7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* b8..bf    ........ */

	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* c0..c7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* c8..cf    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* d0..d7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* d8..df    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* e0..e7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* e8..ef    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,  /* f0..f7    ........ */
	  0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40   /* f8..ff    ........ */
	};
# define charToUpper(x)  ((x)&~(charCtypeMap[(unsigned char)(x)]&0x20))
# define charIsSpace(x)   (charCtypeMap[(unsigned char)(x)]&0x01)
# define charIsAlnum(x)   (charCtypeMap[(unsigned char)(x)]&0x06)
# define charIsAlpha(x)   (charCtypeMap[(unsigned char)(x)]&0x02)
# define charIsDigit(x)   (charCtypeMap[(unsigned char)(x)]&0x04)
# define charIsXdigit(x)  (charCtypeMap[(unsigned char)(x)]&0x08)
# define charToLower(x)   (charUpperToLower[(unsigned char)(x)])
#endif
	///	<summary>
	///	字符串类
	///	</summary>
	///	<remarks>
	///	<code>继承STL标准类，扩展方法，ASCII字符。采用系统默认编码
    /// 作 者: 邹远贵
    /// 日 期: 2007-4-25
	/// 版 本: 1.0
	///	//未添加详细注释的重载运算方法
	///	inline ostream&amp; operator&lt;&lt;(ostream&amp; target, const String&amp; s);
	///	inline String operator+(const String &amp;a,const char * b);
	///	inline String operator+(const char * b,const String &amp;a);
	///	inline String operator+(const int b,const String&amp; a);
	///	inline String operator+(const String&amp; a,const int b);
	///	inline String operator+(const unsigned int b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const unsigned int b);
	///	inline String operator+(const long b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const long b);
	///	inline String operator+(const unsigned long b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const unsigned long b);
	///	inline String operator+(const unsigned long long b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const unsigned long long b);
	///	inline String operator+(const long long b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const long long b);
	///	inline String operator+(const double b,const String &amp;a);
	///	inline String operator+(const String &amp;a,const double b);
	///	inline String operator+(const char b,const String &amp;a);
	///	inline String operator+(const String &amp;b,const char a);
	///	//  string + String 
	///	inline String operator+(const String &amp;a,const String &amp;b);
	///	inline String operator+(const string &amp;a,const String &amp;b);
	///	inline String operator+(const String &amp;a,const string &amp;b);
	///	inline String &amp; operator+=(String &amp;b,const int a);
	///	inline String &amp; operator+=(String &amp;b,const long a);
	///	inline String &amp; operator+=(String &amp;b,const long long a);
	///	inline String &amp; operator+=(String &amp;b,const unsigned int a);
	///	inline String &amp; operator+=(String &amp;b,const unsigned long a);
	///	inline String &amp; operator+=(String &amp;b,const unsigned long long a);
	///	inline string &amp; operator+=(string &amp;b,const double a);
	///	inline String &amp; operator+=(String &amp;b,const char a);
	///	inline String &amp; operator+=(String &amp;b,const char * a);
	///	inline String &amp; operator+=(String &amp;b,const String &amp;a);
	///	inline string &amp; operator+=(string &amp;b,const String &amp;a);
	///	inline String &amp; operator+=(String &amp;b,const string &amp;a);
	///    bool inline operator>(const  String &amp;a,const  String &amp;b);
	///    bool inline operator>(const  String &amp;a,const  string &amp;b);
	///    bool inline operator>(const  string &amp;a,const  String &amp;b);
	///    bool inline operator>=(const  String &amp;a,const  String &amp;b);
	///    bool inline operator>=(const  String &amp;a,const  string &amp;b);
	///    bool inline operator>=(const  string &amp;a,const  String &amp;b);
	///    bool inline operator&lt;=(const  String &amp;a,const  String &amp;b);
	///    bool inline operator&lt;=(const  String &amp;a,const  string &amp;b);
	///    bool inline operator&lt;=(const  string &amp;a,const  String &amp;b);
	///    bool inline operator&lt;(const  String &amp;a,const  String &amp;b);
	///    bool inline operator&lt;(const  String &amp;a,const  string &amp;b);
	///    bool inline operator&lt;(const  string &amp;a,const  String &amp;b);
	///    bool inline operator> (const  String &amp;a,const  char * b);
	///    bool inline operator>=(const  String &amp;a,const  char * b);
	///    bool inline operator&lt;=(const  String &amp;a,const  char * b);
	///    bool inline operator&lt; (const  String &amp;a,const  char * b);
	///	bool inline operator!=(const String &amp;a,const String &amp;b);
	///	bool inline operator!=(const String &amp;a,const string &amp;b);
	///	bool inline operator!=(const string &amp;a,const String &amp;b);
	///	bool inline operator!=(const String &amp;a,const char * b);
	///	bool inline operator==(const  String &amp;a,const  String &amp;b);
	///	bool inline operator==(const  string &amp;a,const  String &amp;b);
	///	bool inline operator==(const  String &amp;a,const  string &amp;b);
	///	bool inline operator==(const  String &amp;a,const char *b);
	///	inline int operator%(const String &amp;s,const int b);
	///</code>
	///	</remarks>
    /// <example><code>
	///	应用命令行参数解析：
	///	String a;
	///	a="sdgdsgh";
	///	String a="sdgd";
    /// </code></example>
	class String :public string
	{ 
		typedef enum StringSplitOptions StringSplitOptions;
	public: 
		//static const unsigned char charUpperToLower[] ;
		///	<summary>
		///	常量空白字符数组
		///	</summary>
		///	<remarks>值列表：<code>    '\t','\n','\v','\f','\r',' ','\b','\a'</code></remarks>
		static const char WhitespaceChars[];
		///	<summary>
		///	字符串拷贝
		///	<code>原型：inline static char * strcpy(char * dest,const char * source);</code>
		///	</summary>
		///	<param name="dest">目标存储指针，要求dest所指向的存储空间要比源大，否则造成非法地址访问</param>
		///	<param name="source">源数据指针</param>
		///	<returns>返回dest指针</returns>
		inline static char * strcpy(char * dest,const char * source)
		{
			::strcpy(dest,source);
			return dest;
		}
		///	<summary>
		///	字符串拷贝，指定源开始位置
		///	<code>原型：inline static char *  strcpy(char * dest,const char * source,int startIndex);</code>
		///	</summary>
		///	<param name="dest">目标存储指针，要求dest所指向的存储空间要比源大，否则造成非法地址访问</param>
		///	<param name="source">源数据指针</param>
		///	<param name="startIndex">开始索引位置</param>
		///	<returns>返回dest指针</returns>
		inline static char *  strcpy(char * dest,const char * source,int startIndex)
		{
			source+=startIndex;
			STDSPACE::strcpy(dest,source);
			return dest;
		}
		///	<summary>
		///	字符串拷贝，指定源开始位置和长度
		///	<code>原型：inline static char *  strcpy(char * dest,const char * source,int startIndex,int length);</code>
		///	</summary>
		///	<param name="dest">目标存储指针，要求dest所指向的存储空间要比源大，否则造成非法地址访问</param>
		///	<param name="source">源数据指针</param>
		///	<param name="startIndex">开始索引位置</param>
		///	<param name="length">需要拷贝的长度</param>
		///	<returns>拷贝的字节数</returns>
		inline static int strcpy(char * dest,const char * source,int startIndex,int length)
		{
			int i=0;
			if(length<1)return 0;
			source+=startIndex;
			while(source[i])
			{
				if(i>=length)break;
				dest[i]=source[i];
				i++;
			}
			dest[i]=0;
			return i;
		}
		
		///	<summary>
		///	字节拷贝,强制拷贝
		///	<code>原型：inline static void strcpy(unsigned char * dest,const unsigned char * source,int length);</code>
		///	</summary>
		///	<param name="dest">目标存储指针，要求dest所指向的存储空间不能比length小，否则造成非法地址访问</param>
		///	<param name="source">源数据指针</param>
		///	<param name="length">需要拷贝的长度</param>
		inline static void strcpy(unsigned char * dest,const unsigned char * source,int length)
		{
			if(length<1)return;
			int i=0;
			while(i<length)
			{
				dest[i]=source[i];
				i++;
			}
		}
		///	<summary>
		///	字符串拷贝，指定源开始位置和长度
		///	<code>原型：inline static int strcpy(char * dest,int startIndex,const char * source,int sourceIndex,int length);</code>
		///	</summary>
		///	<param name="dest">目标存储指针</param>
		///	<param name="startIndex">目标开始索引位置</param>
		///	<param name="source">源数据指针</param>
		///	<param name="sourceIndex">源开始索引位置</param>
		///	<param name="length">需要拷贝的长度</param>
		///	<returns>拷贝的字节数</returns>
		inline static int strcpy(char * dest,int startIndex,const char * source,int sourceIndex,int length)
		{
			int i=0;
			if(length<1)return 0;
			char * temp=dest+startIndex;		
			source+=sourceIndex;
			while(source[i])
			{
				if(i>=length)break;
				temp[i]=source[i];
				i++;
			}
			dest[i]=0;
			return i;
		}
		///	<summary>
		///	获取字符指针指向字符的长度
		///	<code>原型：inline static int strlen(const char *source);</code>
		///	</summary> 
		///	<param name="source">字符指针</param>
		///	<returns>字符长度</returns>
		inline static int strlen(const char *source)
		{
			return STDSPACE::strlen(source);
		};
		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,const char * _Str2);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,const char * _Str2)
		{
			return STDSPACE::strcmp(_Str1,_Str2);
		}
		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,const char * _Str2,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,const char * _Str2,bool ignoreCase)
		{
			if(ignoreCase)
			{
				char a,b;int i=0;
				while(_Str1[i] && _Str2[i])
				{
					a=_Str1[i];
					b=_Str2[i];
					if(a>='a' && a<='z')a=a-32;
					if(b>='a' && b<='z')b=b-32;
					if(a>b)return 1;
					if(a<b)return -1;
					i++;
				}
				if(_Str1[i]=='\0' && _Str2[i]=='\0') return 0;
				if(_Str1[i]=='\0')return -1;
				else return 1;//if(_Str2[i]=='\0')return 1;
			}
			else
			{
				return strcmp(_Str1, _Str2);
			}
		} 
		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<param name="index">字符比较的开始位置</param>
		///	<param name="length">要比较的长度</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length)
		{
			int i=0;
			while(_Str1[i] && _Str2[i])
			{
				if(i<index)
				{
					i++;
					continue;
				}
				if(_Str1[i]>_Str2[i])return 1;
				if(_Str1[i]<_Str2[i])return -1;
				i++;
				if(i>=index+length)return 0;
			}
			if((_Str1[i]=='\0' && _Str2[i]=='\0')|| i==index+length) return 0;
			if(_Str1[i]=='\0')return -1;
			else return 1;//if(_Str2[i]=='\0')return 1;
		}
		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<param name="index">字符比较的开始位置</param>
		///	<param name="length">要比较的长度</param>
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length,bool ignoreCase)
		{
			if(ignoreCase)
			{
				char a,b;int i=0;
				while(_Str1[i] && _Str2[i])
				{
					if(i<index)
					{
						i++;
						continue;
					}
					i++;
					a=_Str1[i];
					b=_Str2[i];
					if(a>='a' && a<='z')a=a-32;
					if(b>='a' && b<='z')b=b-32;
					if(a>b)return 1;
					if(a<b)return -1;
					if(i>=index+length)return 0;
				}
				if(_Str1[i]=='\0' && _Str2[i]=='\0') return 0;
				if(_Str1[i]=='\0')return -1;
				else return 1;//if(_Str2[i]=='\0')return 1;
			}
			else
			{
				return strcmp(_Str1, _Str2,index,length);
			}
		}

		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="indexA">字符_Str1比较的开始位置</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<param name="indexB">字符_Str2比较的开始位置</param>
		///	<param name="length">要比较的长度</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length)
		{
			return strcmp(_Str1+indexA,_Str2+indexB,0,length);		
		}
		///	<summary>
		///	比较两个字符串值的相对指示
		///	<code>原型：inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,
		///                                      int indexB,int length,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">指向字符串指针</param>
		///	<param name="indexA">字符_Str1比较的开始位置</param>
		///	<param name="_Str2">指向字符串指针</param>
		///	<param name="indexB">字符_Str2比较的开始位置</param>
		///	<param name="length">要比较的长度</param>
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns> 相对比较值  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length,bool ignoreCase)
		{
			return strcmp(_Str1+indexA,_Str2+indexB,0,length,ignoreCase);	
		}

		///	<summary>
		///	字符串连接,将source拷贝到dest末尾的字符串指针
		///	<code>原型：inline static char * strcat(char * dest,const char * source);</code>
		///	</summary> 
		///	<param name="dest">指向字符串指针</param> 
		///	<param name="source">指向字符串指针</param> 
		///	<returns> 连接后的dest</returns>
		inline static char * strcat(char * dest,const char * source)
		{
			return STDSPACE::strcat(dest,source);
			//int i=0;
			//while(*(dest+i)!='\0')	i++;
			//while(*source!='\0')*(dest+i++)=*source++;
			//*(dest+i++)='\0';
			//return dest;
		} 
		///	<summary>
		///	格式化字符内存空间
		///	<code>原型：inline static char * memset(char * _Dst,  int _Val,  int _Size);</code>
		///	</summary> 
		///	<param name="_Dst">目标字符串指针</param> 
		///	<param name="_Val">要填充的字符值</param>
		///	<param name="_Size">标识_Dst的大小,要填充的字符个数</param> 
		///	<returns>填充_Val后的_Dst指针</returns>
		inline static char * memset(char * _Dst,  int _Val,  int _Size)
		{
			STDSPACE::memset(_Dst,_Val,_Size);
			return _Dst;
		}
		///	<summary>
		///	格式化内存空间
		///	<code>原型：inline static char * memset(char * _Dst,  int _Val,  int _Size);</code>
		///	</summary> 
		///	<param name="_Dst">内存指针</param> 
		///	<param name="_Val">要填充的字符值</param>
		///	<param name="_Size">标识_Dst的大小,要填充的字符个数</param> 
		inline static void * memset(void * _Dst,  int _Val,  int _Size)
		{
			STDSPACE::memset(_Dst,_Val,_Size);
			return _Dst;
		}
 
		///	<summary>
		///	大写转换
		///	<code>原型：inline static char * ToUpper(char * dest);</code>
		///	</summary> 
		///	<param name="dest">要转换的字符串指针</param> 
		///	<returns>转换后的dest指针</returns>
		inline static char * ToUpper(char * dest)
		{
			int i=-1;
			while(dest[++i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				dest[i]=charToUpper(dest[i]);
#else
				if(dest[i]>='a' && dest[i]<='z')
					dest[i]=dest[i]-32;
#endif
			}
			return dest;
		}; 
		///	<summary>
		///	小写转换
		///	<code>原型：inline static char * ToLower(char * dest);</code>
		///	</summary> 
		///	<param name="dest">要转换的字符串指针</param> 
		///	<returns>转换后的dest指针</returns>
		inline static char * ToLower(char * dest)
		{
			int i=-1;
			while(dest[++i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				dest[i]=charToLower(dest[i]);
#else
				if(dest[i]>='A' && dest[i]<='Z')
					dest[i]=dest[i]+32;
#endif
			}
			return dest;
		};

		String():string(){};
		///	<summary>
		///	以基类<see cref="string"/>初始化对象
		///	<code>原型：String(string s);</code>
		///	</summary> 
		///	<param name="value"><see cref="string"/>对象</param> 
		String(string s):string(s){};
		//String(const String &s){this->assign(s.c_str());};

		///	<summary>
		///	以字符指针初始化
		///	<code>原型：String(const char * value);</code>
		///	</summary> 
		///	<param name="value">字符串指针</param> 
		String(const char * value):string(value){};
		///	<summary>
		///	以整数初始化
		///	<code>原型：String(int i);</code>
		///	</summary> 
		///	<param name="i">整数</param> 
		String(int i){char p[40];sprintf(p,"%d",i);assign(p);};
		///	<summary>
		///	以长整数初始化
		///	<code>原型：String(long i);</code>
		///	</summary> 
		///	<param name="l">整数</param> 
		String(long l){char p[40];sprintf(p,"%ld",l);assign(p);};
		///	<summary>
		///	以64位长整数初始化
		///	<code>原型：String(long long i);</code>
		///	</summary> 
		///	<param name="l">64位长整数</param> 
		String(long long l){char p[40];sprintf(p,"%lld",l);assign(p);};
		///	<summary>
		///	以无符号整数初始化
		///	<code>原型：String(unsigned int i);</code>
		///	</summary> 
		///	<param name="l">无符号整数</param> 
		String(unsigned int i){char p[40];sprintf(p,"%u",i);assign(p);};
		///	<summary>
		///	以无符号长整数初始化
		///	<code>原型：String(unsigned long i);</code>
		///	</summary> 
		///	<param name="l">无符号长整数</param> 
		String(unsigned long l){char p[40];sprintf(p,"%lu",l);assign(p);};
		///	<summary>
		///	以无符号64位整数初始化
		///	<code>原型：String(unsigned long long  i);</code>
		///	</summary> 
		///	<param name="l">无符号64位整数</param> 
		String(unsigned long long l){char p[40];sprintf(p,"%llu",l);assign(p);};
		///	<summary>
		///	以double初始化
		///	<code>原型：String(double i);</code>
		///	</summary> 
		///	<param name="d">double类型数字</param> 
		String(double d):string(Convert::ToString(d)){}//{ *this=Convert::ToString(d);};
		///	<summary>
		///	以字符初始化
		///	<code>原型：String(char i);</code>
		///	</summary> 
		///	<param name="c">字符</param> 
		String(char c){char p[2];p[0]=c;p[1]=0;assign(p);};
		///	<summary>
		///	以相同字符初始化
		///	<code>原型：String(char i);</code>
		///	</summary> 
		///	<param name="c">字符</param> 
		///	<param name="count">长度个数</param> 
		String(char c, int count):string(count,c){}
		///	<summary>
		///	以<see cref="String"/>对象初始化
		///	<code>原型：String(String &amp;value, int startIndex);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>对象实例</param> 
		///	<param name="startIndex">起始位置</param> 
		String(String &value, int startIndex):string(value.c_str()+startIndex){}
 		///	<summary>
		///	以<see cref="String"/>对象初始化
		///	<code>原型：String(String &amp;value, int startIndex, int length);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>对象实例</param> 
		///	<param name="startIndex">value 内的起始位置。</param> 
		///	<param name="length">要使用字符数长度。</param> 
		String(String &value, int startIndex, int length):string(value.c_str()+startIndex,length){}
 		///	<summary>
		///	以字符串指针初始化
		///	<code>原型：String(const char * value,int startIndex);</code>
		///	</summary> 
		///	<param name="value">字符串指针</param> 
		///	<param name="startIndex">value 内的起始位置。</param>  
		String(const char * value,int startIndex):string(value+startIndex){}
 		///	<summary>
		///	以字符串指针初始化
		///	<code>原型：String(const char * value,int startIndex, int length);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>对象实例</param> 
		///	<param name="startIndex">value 内的起始位置。</param> 
		///	<param name="length">要使用字符数长度。</param> 
		String(const char * value,int startIndex, int length):string(value+startIndex,length){}
 		///	<summary>
		///	下标运算符
		///	<code>原型：inline char &amp;operator[](int index);</code>
		///	</summary> 
		///	<param name="index">字符串内位置</param> 
		///	<returns>对应位置字符引用</returns>
		inline char &operator[](int index){return at(index);};
 
 		///	<summary>
		///	比较两个指定的 <see cref="String"/> 对象。
		///	<code>原型：inline static int Compare(String &amp;strA, String &amp;strB);</code>
		///	</summary> 
		///	<param name="strA">第一个<see cref="String"/>对象</param> 
		///	<param name="strB">第二个<see cref="String"/>对象</param>
		///	<returns>一个 32 位有符号整数，指示两个比较数之间的词法关系。值 条件 小于零 strA 小于 strB。 零 strA 等于 strB。 大于零 strA 大于 strB。</returns>
		inline static int Compare(String &strA, String &strB){return String::strcmp(strA.c_str(),strB.c_str());};
 		///	<summary>
		///	比较两个指定的 <see cref="String"/> 对象,忽略或考虑它们的大小写。
		///	<code>原型：inline static int Compare(String &amp;strA, String &amp;strB, bool ignoreCase);</code>
		///	</summary> 
		///	<param name="strA">第一个<see cref="String"/>对象</param> 
		///	<param name="strB">第二个<see cref="String"/>对象</param>
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns>一个 32 位有符号整数，指示两个比较数之间的词法关系。值 条件 小于零 strA 小于 strB。 零 strA 等于 strB。 大于零 strA 大于 strB。</returns>
        inline static int Compare(String &strA, String &strB, bool ignoreCase){return String::strcmp(strA.c_str(),strB.c_str(),ignoreCase);};
    	///	<summary>
		///	比较两个指定的 <see cref="String"/> 对象,忽略或考虑它们的大小写。
		///	<code>原型：inline static int Compare(String &amp;strA, int indexA, String &amp;strB,int indexB, int length);</code>
		///	</summary> 
		///	<param name="strA">第一个<see cref="String"/>对象</param> 
		///	<param name="indexA"> strA 内子字符串的位置。</param> 
		///	<param name="strB">第二个<see cref="String"/>对象</param>
		///	<param name="indexB"> strB 内子字符串的位置。</param> 
		///	<param name="length">要比较的字符长度。</param> 
		///	<returns>一个 32 位有符号整数，指示两个比较数之间的词法关系。值条件 小于零 strA 中的子字符串小于 strB 中的子字符串。 零 子字符串相等，或者
        ///     length 为零。 大于零 strA 中的子字符串大于 strB 中的子字符串。</returns>
        inline static int Compare(String &strA, int indexA, String &strB, int indexB, int length){return String::strcmp(strA.c_str(),indexA,strB.c_str(),indexB,length);};
  		///	<summary>
		///	比较两个指定的 <see cref="String"/> 对象,忽略或考虑它们的大小写。
		///	<code>原型：inline static int Compare(String &amp;strA, int indexA, String &amp;strB,
		///                                       int indexB,  int length, bool ignoreCase);</code>
		///	</summary> 
		///	<param name="strA">第一个<see cref="String"/>对象</param> 
		///	<param name="indexA"> strA 内子字符串的位置。</param> 
		///	<param name="strB">第二个<see cref="String"/>对象</param>
		///	<param name="indexB"> strB 内子字符串的位置。</param> 
		///	<param name="length">要比较的字符长度。</param> 
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns>一个 32 位有符号整数，指示两个比较数之间的词法关系。值条件 小于零 strA 中的子字符串小于 strB 中的子字符串。 零 子字符串相等，或者
        ///     length 为零。 大于零 strA 中的子字符串大于 strB 中的子字符串。</returns>
       inline static int Compare(String &strA, int indexA, String &strB, int indexB, int length, bool ignoreCase){return String::strcmp(strA.c_str(),indexA,strB.c_str(),indexB,length,ignoreCase);};
   		///	<summary>
		///	将此实例与指定的  <see cref="String"/> 对象进行比较。 
		///	<code>原型：inline int Compare(String &amp;strB );</code>
		///	</summary>  
		///	<param name="strB">第二个<see cref="String"/>对象</param> 
		///	<returns> 一个 32 位有符号整数，指示两个比较数之间的词法关系。值 条件 小于零 此实例小于 strB。 零 此实例等于 strB。 大于零 此实例大于
        ///     strB。- 或 - strB 为null。</returns>
        inline int CompareTo(String &strB){return String::strcmp(c_str(),strB.c_str());};
    	///	<summary>
		///	返回一个值，该值指示指定的 <see cref="String"/>对象是否出现在此字符串中。
		///	<code>原型：inline int Contains(String &amp;value );</code>
		///	</summary>  
		///	<param name="value">要查找的 <see cref="String"/>对象。</param> 
		///	<returns> 如果 value 参数出现在此字符串中，或者 value 为空字符串 ("")，则为 true；否则为 false。</returns>
       inline bool Contains(String &value)
		{
			if(value.empty())return true;
			char * p=(char *)c_str();
			char * tp=(char *)value.c_str();
			int len=value.size();
			while(*p++)
			{
				if(*p==*tp)
				{
					int i=0;
					for(i=0;i<len;i++)
					{
						if(*(p+i)=='\0')return false;
						if(*(p+i)!=*(tp+i))break;
					}
					if(i==len)return true;
				}
				else
				{
					continue;
				}
			}
			return false;
		}
    	///	<summary>
		///	拷贝字符到字符串指针中.
		///	<code>原型：inline void CopyTo(int sourceIndex, char * destination, int destinationIndex, int count);</code>
		///	</summary>  
		///	<param name="sourceIndex">当前实例对象中字符开始位置。</param> 
		///	<param name="destination">目标字符指针。</param> 
		///	<param name="destinationIndex">destination 中的开始位置。</param> 
		///	<param name="count">此实例中要复制到 destination 的字符数。</param> 
		inline void CopyTo(int sourceIndex, char * destination, int destinationIndex, int count)
		{
			String::strcpy(destination,destinationIndex,c_str(),sourceIndex,count);
		}
    	///	<summary>
		///	确定此实例是否与另一个指定的 <see cref="String"/> 对象具有相同的值.
		///	<code>原型：inline bool Equals(String &amp;value);</code>
		///	</summary>  
		///	<param name="value">要比对的<see cref="String"/>对象。</param>  
		///	<returns>如果 value 参数的值与此实例相同，则为 true；否则为 false。</returns>
		inline bool Equals(String &value)
		{
			 int result=String::strcmp(c_str(),value.c_str());
			 if(result==0)
				 return true;
			 else 
				 return false;
		} 
     	///	<summary>
		///	确定两个指定的<see cref="String"/>对象是否具有同一值。参数指定区域性、大小写以及比较所用的排序规则。
		///	<code>原型：inline static bool Equals(String &amp;a, String &amp;b, bool ignoreCase=false)</code>
		///	</summary>  
		///	<param name="a">要比对的<see cref="String"/>对象。</param>  
		///	<param name="b">要比对的<see cref="String"/>对象。</param>  
		///	<param name="ignoreCase">是否忽略大小写</param>
		///	<returns>如果 value 参数的值与此实例相同，则为 true；否则为 false。</returns>
        inline static bool Equals(String &a, String &b, bool ignoreCase=false){return String::strcmp(a.c_str(),b.c_str(),ignoreCase)==0;};
		inline static bool Equals(string &a, string b, bool ignoreCase=false){return String::strcmp(a.c_str(),b.c_str(),ignoreCase)==0;};
     	///	<summary>
		///	将指定的<see cref="String"/>中的格式项替换为指定的<see cref="String"/>实例的值的文本等效项。
		///	<code>原型：inline static String Format(String format, String arg0);</code>
		///	</summary>  
		///	<param name="format">格式化的format<see cref="String"/>对象，包含“{0}”这个占位符。</param>  
		///	<param name="arg0">要格式化的<see cref="String"/>对象。</param>   
		///	<returns>format 的一个副本，其中的第一个格式项{0}已替换为 arg0 的<see cref="String"/>等效项。</returns>
		inline static String Format(String format, String arg0)
		{
			String s="{0}",result;
			int index=format.IndexOf(s);
			if(index>=0)
			{
				result=format.Replace(s,arg0);
			}
			else
			{
				result=format;
			}
			return result.c_str();
		} 
     	///	<summary>
		///	将指定的<see cref="String"/>中的格式项替换为指定的<see cref="String"/>实例的值的文本等效项。
		///	<code>原型：inline static String Format(String format, Array&lt;String> &amp;args);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>，包含零个或多个格式项。</param>  
		///	<param name="args">包含零个或多个要格式化的对象的<see cref="String"/>数组。</param>   
		///	<returns>format 的一个副本，其中格式项已替换为 args 中相应 <see cref="String"/> 实例的 <see cref="String"/> 等效项。</returns>
		inline static String Format(String format, Array<String> &args)
		{
			String result=format;
			for(int i=0;i<args.size();i++)
			{
				String temp="{";
				temp+=String(i) +"}";
				int index=format.IndexOf(temp);
				if(index>=0)
				{
					result=format.Replace(temp,args[i]);
				}
			}
			return result.c_str();
		}
     	///	<summary>
		///	将指定的<see cref="String"/>中的格式项替换为指定的<see cref="String"/>实例的值的文本等效项。
		///	<code>原型：inline static String Format(String format, String arg0, String arg1);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>，包含零个或多个格式项。</param>  
		///	<param name="arg0">第一个要格式化的<see cref="String"/>。</param>   
		///	<param name="arg1">第二个要格式化的<see cref="String"/>。</param>   
		///	<returns>format 的一个副本，其中格式项已替换为 arg0 ,arg1中相应 <see cref="String"/> 实例的 <see cref="String"/> 等效项。</returns>
		inline static String Format(String format, String arg0, String arg1)
		{
			int i=0,count=0;
			while(count<2)
			{
				String temp="{";
				temp+=String(i) +"}";
				int index=format.IndexOf(temp);
				if(index>=0)
				{
					count++;
					String t;
					if(count==1)
					{
						format=format.Replace(temp,arg0);
					}
					else
					{
						format=format.Replace(temp,arg1);
					}
				}
				if(i>5)break;
			}
			return format.c_str();
		}
      	///	<summary>
		///	将指定的 <see cref="String"/> 中的格式项替换为三个指定的 <see cref="String"/> 。
		///	<code>原型：inline static String Format(String format, String arg0, String arg1, String arg2);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>，包含零个或多个格式项。</param>  
		///	<param name="arg0">第一个要格式化的<see cref="String"/>。</param>   
		///	<param name="arg1">第二个要格式化的<see cref="String"/>。</param>   
		///	<param name="arg1">第三个要格式化的<see cref="String"/>。</param>   
		///	<returns>format 的一个副本，其中格式项已替换为 arg0 ,arg1 ,arg2中相应 <see cref="String"/> 实例的 <see cref="String"/> 等效项。</returns>
		inline static String Format(String format, String arg0, String arg1, String arg2)
		{
			int i=0,count=0;
			while(count<3)
			{
				String temp="{";
				temp+=String(i) +"}";
				int index=format.IndexOf(temp);
				if(index>=0)
				{
					count++;
					if(count==1)
					{
						format=format.Replace(temp,arg0);
					}
					else if(count==2)
					{
						format=format.Replace(temp,arg1);
					}
					else if(count==3)
					{
						format=format.Replace(temp,arg2);
					}
				}
				if(i>5)break;
			}
			return format.c_str();
		}
       	///	<summary>
		///	报告指定字符在此字符串中的第一个匹配项的索引。
		///	<code>原型：inline int IndexOf(char value, int startIndex,bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">要查找的字符 。</param>   
		///	<param name="startIndex">搜索起始位置。</param>   
		///	<param name="ignoreCase">是否忽略大小写。</param>   
		///	<param name="count">查找长度，查找多少字符后停止查找。</param>   
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
        inline int IndexOf(char value, int startIndex,bool ignoreCase, int count=0)
		{
			int i=startIndex;
			String temp1=c_str();
			if(ignoreCase)
			{
				temp1.ToUpper();			
				if(value>='a' && value<='z')value=value-32;
			}
			while(i<size() && c_str()[i])
			{
				if(count>0 && i-startIndex>=count)return -1;
				if(c_str()[i]==value)return i;
				i++;
			}
			return -1;
		}
       	///	<summary>
		///	报告指定字符在此字符串中的第一个匹配项的索引。该搜索从指定字符位置开始
		///	<code>原型：inline int IndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">要查找的字符 。</param>     
		///	<param name="ignoreCase">是否忽略大小写。</param>    
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
		inline int IndexOf(char value, bool ignoreCase=0)
		{
			return IndexOf(value,0,ignoreCase);
		}
       	///	<summary>
		///	报告指定的 <see cref="String"/> 在此实例中的第一个匹配项的索引。
		///	<code>原型：inline int IndexOf(String value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">要查找的字符串<see cref="String"/>  。</param>     
		///	<param name="startIndex">搜索起始位置。</param>   
		///	<param name="ignoreCase">是否忽略大小写。</param>   
		///	<param name="count">查找长度，查找多少字符后停止查找。</param>   
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
		inline int IndexOf(String value, int startIndex, bool ignoreCase, int count=0)
		{
			if(value.empty())return startIndex;
			int index=startIndex;
			if(size()<value.size())return -1;
			char * _Str1=(char *)c_str()+startIndex;
			char * _Str2=(char *)value.c_str();
			String temp1=_Str1;
			if(ignoreCase)
			{
				temp1.ToUpper();
				value.ToUpper();
				_Str1=(char *)temp1.c_str();
			}
			_Str2=(char *)value.c_str();
			while(*_Str1)
			{
				if(count>0 && index-startIndex==count)break;
				int i=0;
				for(i=0;i<value.size() && _Str1[i];i++)
				{
					if(_Str1[i]!=_Str2[i])break;
				}
				if(i==value.size())return index;
				_Str1++;index++;
				if(size()-index<value.size())return -1;
			}
			return -1;
		}

      	///	<summary>
		///	报告指定的 <see cref="String"/> 在此实例中的第一个匹配项的索引。该搜索从指定字符位置开始
		///	<code>原型：inline int IndexOf(String value,  bool ignoreCase );</code>
		///	</summary>  
		///	<param name="value">要查找的字符串<see cref="String"/>  。</param>   
		///	<param name="ignoreCase">是否忽略大小写。</param>    
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
		inline int IndexOf(String value, bool ignoreCase=false)
		{
			return IndexOf(value,0,ignoreCase);
		}
       	///	<summary>
		///	报告指定字符数组中的任意字符在此实例中第一个匹配项的索引。搜索从指定字符位置开始，并检查指定数量的字符位置。
		///	<code>原型：inline int IndexOfAny(String anyOf, int startIndex=0, int count=0);</code>
		///	</summary>  
		///	<param name="anyOf">要查找的字符数组，包含一个或多个要查找的字符。<see cref="String"/>  。</param>   
		///	<param name="startIndex">是否忽略大小写。</param>    
		///	<param name="count">要检查的字符位置数。</param>    
		///	<returns>此实例中第一个匹配项的索引位置，在此处找到 anyOf 中的任意字符；否则，如果未找到 anyOf 中的字符，则为 -1。</returns>
 		inline int IndexOfAny(String anyOf, int startIndex=0, int count=0)
		{
			if(count==0)return -1;
			int i=0;
			while(c_str()[i+startIndex])
			{
				if(count>0 && i>=count)break;
				int j=0;
				while(anyOf[j])
				{
					if(c_str()[i+startIndex]==anyOf[j]) return i;
					j++;
				}
				i++;
			}
			return -1;
		}
       	///	<summary>
		///	在指定 <see cref="String"/>  数组的每个元素之间串联指定的分隔符 <see cref="String"/> ，
		///     从而产生单个串联的字符串。参数指定要使用的第一个数组元素和元素数。
		///	<code>原型：inline static String Join(Array&lt;String> &amp;value,String separator=",",
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="String"/> 数组。</param>   
		///	<param name="separator">分隔符字符串 <see cref="String"/>  。</param>   
		///	<param name="startIndex">要使用的 value 中的第一个数组元素。</param>    
		///	<param name="count">要使用的 value 的元素数。</param>    
		///	<returns><see cref="String"/> 对象，由通过 separator 联接的 value 中的字符串组成。如果 count 为零、value 没有元素或者
		///     separator 和 value 的全部元素为 Common.String.Empty，则为 Common.String.Empty。</returns>
		inline static String Join(Array<String> &value,String separator=",", int startIndex=0, int count=0x7fffffff)
		{
			String result;
			for(int i=startIndex;i<value.size();i++)
			{
				if(i==startIndex)result=value[i];
				else result+=separator+value[i];
				if(i-startIndex+1==count)break;
			}
			return result;
		}
       	///	<summary>
		///	在指定 <see cref="string"/>  数组的每个元素之间串联指定的分隔符 <see cref="string"/> ，
		///     从而产生单个串联的字符串。参数指定要使用的第一个数组元素和元素数。
		///	<code>原型：inline static string Join(Array&lt;string> &amp;value,string separator=",", 
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="string"/> 数组。 </param>   
		///	<param name="separator">分隔符字符串 <see cref="string"/>  。</param>   
		///	<param name="startIndex">要使用的 value 中的第一个数组元素。</param>    
		///	<param name="count">要使用的 value 的元素数。</param>    
		///	<returns><see cref="string"/> 对象，由通过 separator 联接的 value 中的字符串组成。如果 count 为零、value 没有元素或者
		///     separator 和 value 的全部元素为 Common.String.Empty，则为 Common.String.Empty。</returns>
		inline static string Join(Array<string> &value, string separator=",", int startIndex=0, int count=0x7fffffff)
		{
			string result;
			for(int i=startIndex;i<value.size();i++)
			{
				if(i==startIndex)result=value[i];
				else result+=separator+value[i];
				if(i-startIndex+1==count)break;
			}
			return result;
		} 
       	///	<summary>
		///	在指定 <see cref="char"/>  数组的每个元素之间串联指定的分隔符 <see cref="String"/> ，
		///     从而产生单个串联的字符串。参数指定要使用的第一个数组元素和元素数。
		///	<code>原型：inline static String Join(Array&lt;char> &amp;value,String separator=",",
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="char"/> 数组。 </param>   
		///	<param name="separator">分隔符字符串 <see cref="String"/>  。</param>   
		///	<param name="startIndex">要使用的 value 中的第一个数组元素。</param>    
		///	<param name="count">要使用的 value 的元素数。</param>    
		///	<returns><see cref="String"/> 对象，由通过 separator 联接的 value 中的字符串组成。如果 count 为零、value 没有元素或者
		///     separator 和 value 的全部元素为 Common.String.Empty，则为 Common.String.Empty。</returns>
		inline static String Join(Array<char> &value,String separator=",", int startIndex=0, int count=0x7fffffff)
		{
			String result;
			for(int i=startIndex;i<value.size();i++)
			{
				if(i==startIndex)result=value[i];
				else result+=separator+value[i];
				if(i-startIndex+1==count)break;
			}
			return result;
		}
       	///	<summary>
		///	报告指定字符在此实例中的最后一个匹配项的索引位置。
		///	<code>原型：inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="char"/> 。 </param>       
		///	<param name="ignoreCase">是否忽略大小写。</param>    
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
        inline int LastIndexOf(char value, bool ignoreCase=0)
		{
			if(ignoreCase)
			{
				String temp1=c_str();
				temp1.ToUpper();
				if(value>='a' && value<='z')value=value-32;
				return temp1.LastIndexOf(value,0,0,0);
			}
			else
			{
				return LastIndexOf(value,0,0,0);
			}
		}
       	///	<summary>
		///	报告指定字符在此实例中的最后一个匹配项的索引位置。
		///	<code>原型：inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="char"/> 。 </param>       
		///	<param name="startIndex">开始位置，反向查找时的截止位置。</param>    
		///	<param name="ignoreCase">是否忽略大小写。</param>    
		///	<param name="count">查找字符数。</param>    
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
        inline int LastIndexOf(char value, int startIndex, bool ignoreCase, int count=0)
		{
			int i=size()-1;
			char * temp=(char *)c_str();
			String temp1;
			if(ignoreCase)
			{
				if(value>='a' && value<='z')value=value-32;
				temp1=c_str();temp1.ToUpper();
				temp=(char *)temp1.c_str();
			}
			while(c_str()[i] && i>=0)
			{
				if(i<startIndex)return -1;
				if(count>0 && (int)size()-i-1>=count)return -1;
				if(c_str()[i]==value)return i;
				i--;
			}
			return -1;
		}
    	///	<summary>
		///	报告指定<see cref="String"/>在此实例中的最后一个匹配项的索引位置。
		///	<code>原型：inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="char"/> 。 </param>        
		///	<param name="ignoreCase">是否忽略大小写。</param>     
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
        inline int LastIndexOf(String value, bool ignoreCase=0)
		{
			return LastIndexOf(value,0,ignoreCase);
		}
     	///	<summary>
		///	报告指定<see cref="String"/>在此实例中的最后一个匹配项的索引位置。
		///	参数指定当前字符串中的起始搜索位置、要搜索的当前字符串中的字符数量，以及是否忽略大小写。
		///	<code>原型：inline int LastIndexOf(String value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">一个 <see cref="char"/> 。 </param>        
		///	<param name="startIndex">搜索起始位置，反向查找时的截止位置。</param>    
		///	<param name="ignoreCase">是否忽略大小写。</param>    
		///	<param name="count">要检查的字符位置数。</param>    
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>
        inline int LastIndexOf(String value, int startIndex, bool ignoreCase, int count=0)
		{
			if(value.empty())return startIndex;
			int index=(int)size()-1;
			if(size()<value.size()+startIndex)return -1;
			String temp1;
			const char * _Str1=c_str()+index;
			if(ignoreCase)
			{
				temp1=ToUpper();
				value.ToUpper();
				_Str1=temp1.c_str()+index;
			}
			const char * _Str2=value.c_str();
			while(*_Str1)
			{
				if(index<startIndex)break;
				if(count>0 && (int)size()-index-1>=count)return -1;
				if(String::strcmp(_Str1,_Str2,0,value.size())==0)return index;
				_Str1--;index--;
			}
			return -1;
		}

     	///	<summary>
		///	报告在字符数组中指定的一个或多个字符在此实例中的最后一个匹配项的索引位置。搜索从指定字符位置开始，并检查指定数量的字符位置。
		///	<code>原型：inline int LastIndexOfAny(String anyOf, int startIndex=0, int count=0);</code>
		///	</summary>  
		///	<param name="anyOf">一个<see cref="String"/>表示的<see cref="char"/>数组。 </param>        
		///	<param name="startIndex">搜索起始位置，反向查找时的截止位置。</param>    
		///	<param name="count">要检查的字符位置数。</param>    
		///	<returns>此实例中最后一个匹配项的索引位置，在此位置找到 anyOf 中的任意字符；否则，如果未找到 anyOf 中的字符，则为 -1。</returns>
		inline int LastIndexOfAny(String anyOf, int startIndex=0, int count=0)
		{
			int i=startIndex+count-1;
			if(i>=size())i=size()-1;
			while(c_str()[i] && i>=0)
			{
				int j=0;
				while(anyOf[j])
				{
					if(c_str()[i]==anyOf[j]) return i;
					j++;
				}
				i--;
				if(i<startIndex)return -1;
			}
			return -1;
		}
       	///	<summary>
		///	右对齐此实例中的字符，在左边用指定的字符填充以达到指定的总长度。
		///	<code>原型：inline String &amp;PadLeft(int totalWidth, char paddingChar=' ');</code>
		///	</summary>  
		///	<param name="totalWidth">结果字符串中的字符数，等于原始字符数加上任何其他填充字符。 </param>        
		///	<param name="paddingChar">填充字符。</param>       
		///	<returns>此实例本身，但它是右对齐的，并在左边用达到 totalWidth 长度所需数目的 paddingChar 字符进行填充。如果
        ///     totalWidth 小于此实例的长度，则不修改。</returns>
        inline String &PadLeft(int totalWidth, char paddingChar=' ')
		{
			if(size()>=totalWidth)return *this;
			int len=size();
			int startIndex=totalWidth-len;
			char * temp=new char[startIndex+1];
			temp[startIndex]='\0';
			for(int i=0;i<startIndex;i++)
			{
				 temp[i]=paddingChar;
			}
			insert(0,temp);
			delete[] temp;
			return *this;
		}
       	///	<summary>
		///	左对齐此字符串中的字符，在右边用指定的字符填充以达到指定的总长度。
		///	<code>原型：inline String &amp;PadRight(int totalWidth, char paddingChar=' ');</code>
		///	</summary>  
		///	<param name="totalWidth">结果字符串中的字符数，等于原始字符数加上任何其他填充字符。 </param>        
		///	<param name="paddingChar">填充字符。</param>       
		///	<returns>此实例本身，但它是左对齐的，并在右边用达到 totalWidth 长度所需数目的 paddingChar 字符进行填充。如果
        ///     totalWidth 小于此实例的长度，则不修改。</returns>
        inline String &PadRight(int totalWidth, char paddingChar=' ')
		{
			if(size()>=totalWidth)return *this;
			int len=size();
			int startIndex=totalWidth-len;
			char * temp=new char[startIndex+1];
			temp[startIndex]='\0';
			for(int i=0;i<startIndex;i++)
			{
				 temp[i]=paddingChar;
			}
			append(temp);
			delete[] temp;
			return *this;
		}
        ///	<summary>
		///	删除此字符串中从指定位置到最后位置的所有字符
		///	<code>原型：inline String &amp;Remove(int startIndex);</code>
		///	</summary>  
		///	<param name="startIndex">开始删除字符的位置。 </param>        
		///	<param name="paddingChar">填充字符。</param>       
		///	<returns>此实例本身，它等于此字符串剔除已删除字符后的字符串。</returns>
        inline String &Remove(int startIndex)
		{
			//if((c_str()=(char *)realloc(c_str(),startIndex+1))==NULL)
			//{
			//	c_str()[startIndex]='\0';
			//	size()=startIndex;
			//	Size=startIndex+1;
			//	return *this;
			//}
			//else
			//	return String::Empty;

			return Remove(startIndex,(int)size()-startIndex);
		}
        ///	<summary>
		///	从此实例中的指定位置开始删除指定数目的字符
		///	<code>原型：inline String &amp;Remove(int startIndex, int count);</code>
		///	</summary>  
		///	<param name="startIndex">开始删除字符的位置。 </param>        
		///	<param name="paddingChar">填充字符。</param>       
		///	<returns>此实例本身，它等于此字符串剔除已删除指定数目的字符后的字符串。</returns>
        inline String &Remove(int startIndex, int count)
		{
			erase(startIndex,count);
			return *this;
		};
        ///	<summary>
		///	将此实例中的指定字符的所有匹配项替换为其他指定的字符。
		///	<code>原型：inline String ReplaceAll(char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary>  
		///	<param name="oldChar">要替换的字符。</param>       
		///	<param name="newChar">要替换 oldChar 的所有匹配项的新字符。 </param>        
		///	<param name="ignoreCase">是否忽略大小写。 </param>        
		///	<returns>但将 oldChar 的所有实例都替换为 newChar 后的新的 <see cref="String"/>。</returns>
        inline String ReplaceAll(char oldChar, char newChar,bool ignoreCase=false)
		{
			String result;
			if(oldChar==newChar)
			{
				result=c_str();
				return result.c_str();
			}
			result=String('\0',size());
			if(newChar!=0)
			{
				int i=0;
				char upchar=oldChar;
				if(ignoreCase)
				{
					if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar+32;
					else if(oldChar>='a' && oldChar<='z')
						upchar=oldChar-32;
				}
				const char * tp=c_str();
				char * dtp=(char *)result.c_str();
				while(tp[i])
				{
					if(tp[i]==oldChar || tp[i]==upchar)
					{
						dtp[i]=newChar;
					}
					else
					{
						dtp[i]=tp[i];
					}
					i++;
				}
			}
			else
			{
				int i=0,count=0;
				const char * tp=c_str();
				char * dtp=(char *)result.c_str();
				while(tp[i])
				{
					if(tp[i]!=oldChar)
					{
						dtp[count]=tp[i];
						count++;
					}
					i++;
				}
			}
			return result;
		};
        ///	<summary>
		///	将此实例中的指定字符的第一个匹配项替换为其他指定的字符。
		///	<code>原型：inline String Replace(char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary>  
		///	<param name="oldChar">要替换的字符。</param>       
		///	<param name="newChar">要替换 oldChar 的所有匹配项的新字符。 </param>        
		///	<param name="ignoreCase">是否忽略大小写。 </param>        
		///	<returns>将 oldChar 的第一个实例替换为 newChar 后的新的 <see cref="String"/>。</returns>
		inline String Replace(char oldChar, char newChar,bool ignoreCase=false)
		{
			String result;
			if(oldChar==newChar)
			{
				return *this;
			}
			result=*this;
			if(newChar!=0)
			{
				int i=0;
				char upchar=oldChar;
				if(ignoreCase)
				{
					if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar+32;
					else if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar-32;
				}
				const char * tp=c_str();
				while(result[i])
				{
					if(tp[i]==oldChar || tp[i]==upchar)
					{
						result[i]=newChar;
						break;
					}
					i++;
				}
			}
			else
			{
				int i=0;
				const char * tp=c_str();
				while(tp[i])
				{
					if(tp[i]==oldChar)
					{
						break;
					}
					result[i]=tp[i];
					i++;
				}
				for(;i<size();i++)
				{
					result[i]=tp[i+1];
				}
			}
			return result;
		}

        ///	<summary>
		///	将此实例中的指定 <see cref="String"/> 的所有匹配项替换为其他指定的 <see cref="String"/>。
		///	<code>原型：inline String ReplaceAll(const String&amp; oldValue, const String&amp; newValue,bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="oldValue">要替换的<see cref="String"/>。</param>       
		///	<param name="newValue">要替换 oldValue 的所有匹配项的<see cref="String"/>。 </param>        
		///	<param name="ignoreCase">是否忽略大小写。 </param>        
		///	<returns>等效于此实例，但将 oldValue 的所有实例都替换为 newValue 的 <see cref="String"/>。</returns>
		inline String ReplaceAll(const String& oldValue, const String& newValue,bool ignoreCase=false)
		{
			String result;
			if(oldValue==newValue)
			{
				result=c_str();
				return result.c_str();
			}
			int index=0;
			result=c_str();
			while((index=result.IndexOf(oldValue,index,ignoreCase))>-1)
			{
				result=result.SubString(0,index)+newValue+result.SubString(index+oldValue.size());
				index+=newValue.size();
			}
			return result.c_str();
		}
		//String ReplaceAll(String oldValue, char * newValue);
		//String ReplaceAll(char * oldValue, String newValue);
		//String ReplaceAll(char * oldValue, char * newValue);

        ///	<summary>
		///	将此实例中的指定 <see cref="String"/> 的第一个匹配项替换为其他指定的 <see cref="String"/>。
		///	<code>原型：inline String Replace(const String&amp; oldValue, const String&amp; newValue,bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="oldValue">要替换的<see cref="String"/>。</param>       
		///	<param name="newValue">要替换 oldValue 的所有匹配项的<see cref="String"/>。 </param>        
		///	<param name="ignoreCase">是否忽略大小写。 </param>        
		///	<returns>等效于此实例，但将 oldValue 的第一个实例替换为 newValue 的新的 <see cref="String"/>。</returns>
		inline String Replace(const String& oldValue, const String& newValue,bool ignoreCase=false)
		{
			String result=c_str();
			if(oldValue==newValue)
			{
				return result.c_str();
			}
			int index=IndexOf(oldValue,ignoreCase);
			if(index==-1)
			{
				return result.c_str();
			}
			if(newValue.size()==0)
				result=SubString(0,index)+SubString(index+oldValue.size());
			else
				result=SubString(0,index)+newValue+SubString(index+oldValue.size());
			return result.c_str();
		}
        ///	<summary>
		///	确定此字符串的开头是否与指定的字符串匹配。
		///	<code>原型：inline bool StartsWith(String value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">要比较的<see cref="String"/>对象。</param>           
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。 </param>        
		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>
		inline bool StartsWith(String value, bool ignoreCase=false)
		{
			//return IndexOf(value,0,ignoreCase)==0;
			if(value.empty())return true;
			if(size()<value.size())return false;
			char * _Str1=(char *)c_str();
			char * _Str2;
			String temp1;
			if(ignoreCase)
			{
				temp1=_Str1;
				temp1.ToUpper();
				value.ToUpper();
				_Str1=(char *)temp1.c_str();
			}
			_Str2=(char *)value.c_str();
			for(int i=0;i<value.size() && _Str1[i];i++)
			{
				if(_Str1[i]!=_Str2[i])return false;
			}
			return true;
		};
        ///	<summary>
		///	确定此字符串的开头是否与指定的字符匹配。
		///	<code>原型：inline bool StartsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">要比较的<see cref="char"/>。</param>           
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。 </param>        
		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>
		inline bool StartsWith(char value, bool ignoreCase=false)
		{
			//return IndexOf(value,0,ignoreCase)==0;
			if(value==0)return true;
			if(size()==0)return false;
			char c=at(0);
			if(ignoreCase)
			{
				if(value>='a' && value<='z')
					value=value-32;
				if(c>='a' && c<='z')
					c=c-32;
			}
			return c==value;
		};
        ///	<summary>
		///	确定此字符串的末尾是否与指定的字符串匹配。
		///	<code>原型：inline bool EndsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">要比较的<see cref="String"/>。</param>           
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。 </param>        
		///	<returns> 如果此字符串的末尾与 value 参数匹配，则为 true；否则为 false。</returns>
		inline bool EndsWith(String value, bool ignoreCase=false)
		{
			//return LastIndexOf(value,0,ignoreCase)==(int)size()-(int)value.size();
			if(value.empty())return true;
			if(size()<value.size())return false;
			char * _Str1=(char *)c_str()+size()-value.size();
			char * _Str2;
			String temp1;
			if(ignoreCase)
			{
				temp1=_Str1;
				temp1.ToUpper();
				value.ToUpper();
				_Str1=(char *)temp1.c_str();
			}
			_Str2=(char *)value.c_str();
			return strcmp(_Str1,_Str2)==0;
		};
        ///	<summary>
		///	确定此字符串的末尾是否与指定的字符匹配。
		///	<code>原型：inline bool EndsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">要比较的<see cref="char"/>。</param>           
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。 </param>        
		///	<returns> 如果此字符串的末尾与 value 参数匹配，则为 true；否则为 false。</returns>
		inline bool EndsWith(char value, bool ignoreCase=false)
		{
			//return LastIndexOf(value,0,ignoreCase)==(int)size()-1;
			if(value==0)return true;
			if(size()==0)return false;
			char c=at(size()-1);
			if(ignoreCase)
			{
				if(value>='a' && value<='z')
					value=value-32;
				if(c>='a' && c<='z')
					c=c-32;
			}
			return c==value;
		};
		///	<summary>
		///	从此实例检索子字符串。子字符串从指定的字符位置开始。
		///	<code>原型：inline String SubString(int startIndex);</code>
		///	</summary>
		///	<param name="startIndex">此实例中子字符串的起始字符位置<see cref="int"/></param>
		///	<returns>截取的子字符串一个 <see cref="String"/>对象，它等于此实例中从 startIndex 开始的子字符串，如果 startIndex 等于此实例的长度，则为
        ///     Common.String.Empty。</returns>
        inline String SubString(int startIndex)
		{
			if(startIndex>=size())return "";
			return String(*this,startIndex);
		}
		///	<summary>
		///	从此实例检索子字符串。子字符串从指定的字符位置开始且具有指定的长度。
		///	<code>原型：inline String SubString(int startIndex, int length);</code>
		///	</summary>
		///	<param name="startIndex">子字符串的起始位置的索引<see cref="int"/></param>
		///	<param name="length">子字符串中的字符数<see cref="int"/></param>
		///	<returns>一个 <see cref="String"/>，它等于此实例中从 startIndex 开始的长度为 length 的子字符串，如果 startIndex 等于此实例的长度且
        ///     length 为零，则为 Common.String.Empty。 </returns>
        inline String SubString(int startIndex, int length)
		{
			if(startIndex>=size() || length<0)return "";
			return String(*this,startIndex,length);
		}
		///	<summary>
		///	返回此 <see cref="String"/> 的转换为小写形式的副本
		///	<code>原型：inline String &amp;ToLower();</code>
		///	</summary>
		///	<returns>此实例本身。 </returns>
        inline String &ToLower()
		{
			int i=0;
			char * tp=(char *)c_str();
			while(tp[i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				tp[i]=charToLower(tp[i]);
#else
				if(tp[i]>='A' && tp [i]<='Z')
					tp[i]+=32;
#endif
				i++;
			}
			return *this;
		}
		///	<summary>
		///	返回此 <see cref="String"/> 的转换为大写形式的副本
		///	<code>原型：inline String &amp;ToUpper();</code>
		///	</summary>
		///	<returns>此实例本身。 </returns>
        inline String &ToUpper()
		{
			int i=0;
			char * tp=(char *)c_str();
			while(tp[i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				tp[i]=charToUpper(tp[i]);
#else
				if(tp[i]>='a' && tp[i]<='z')
					tp[i]-=32;
#endif
				i++;
			}
			return *this;
		};
		///	<summary>
		///	从此实例的开始位置和末尾移除空白字符(包括制表符)的所有匹配项
		///	<code>原型：inline String &amp;Trim();</code>
		///	</summary>
		///	<returns>此实例本身。 </returns>
		inline String &Trim(){return Trim(' ');};
		///	<summary>
		///	从此实例的开始位置和末尾移除指定字符的所有匹配项,这里空格与制表符等效
		///	<code>原型：inline String &amp;Trim(char c);</code>
		///	</summary>
		///	<param name="c">要先移除的字符 </param> 
		///	<returns>此实例本身。 </returns>
		inline String &Trim(char c)
		{
			int i=size()-1,startIndex=0,endCount=0;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(c_str()[i]==c || c_str()[i]==temp)
			{
				at(i)=0;
				endCount++;
				i--;
			}
			while(c_str()[startIndex]==c || c_str()[startIndex]==temp)
			{
				startIndex++;
			}
			assign(c_str()+startIndex);
			return *this;
		}
		///	<summary>
		///	从此实例的末尾移除指定字符的所有匹配项,这里空格与制表符等效
		///	<code>原型：inline String &amp;TrimEnd(char c);</code>
		///	</summary>
		///	<param name="c">要先移除的字符 </param> 
		///	<returns>此实例本身。 </returns>
		inline String &TrimEnd(char c)
		{
			int i=size()-1,count=0;;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(c_str()[i]==c || c_str()[i]==temp)
			{
				at(i)=0;
				count++;
				i--;
			}
			assign(c_str());
			return *this;
		}
		///	<summary>
		///	从此实例的开始位置移除指定字符的所有匹配项,这里空格与制表符等效
		///	<code>原型：inline String &amp;TrimStart(char c);</code>
		///	</summary>
		///	<param name="c">要先移除的字符 </param> 
		///	<returns>此实例本身。 </returns>
		inline String &TrimStart(char c)
		{
			int count=0;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(c_str()[count]==c || c_str()[count]==temp)
			{
				count++;
			}
			assign(c_str()+count);
			return *this;
		}
		///	<summary>
		///	从此实例的开始和末尾移除数组中指定的一组字符的所有匹配项
		///	<code>原型：inline String &amp;Trim(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">要移除的字符数组 </param> 
		///	<returns>此实例本身,从此实例的开始和结尾移除 trimChars 中字符的所有匹配项后剩余的 Common.String。如果 trimChars 为null，则改为移除空白字符。 </returns>
        inline String &Trim(const char * trimChars)
		{
			if(trimChars==NULL)return Trim();
			String temp=trimChars;
			int i=size()-1,startIndex=0,endCount=0;
			while(temp.IndexOf(c_str()[i])>-1)
			{
				at(i)=0;
				endCount++;
				i--;
			}
			while(temp.IndexOf(c_str()[startIndex])>-1)
			{
				startIndex++;
			}
			assign(c_str()+startIndex);
			return *this;
		}
 		///	<summary>
		///	从此实例的结尾移除数组中指定的一组字符的所有匹配项
		///	<code>原型：inline String &amp;TrimEnd(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">要移除的字符数组 </param> 
		///	<returns>此实例本身,从此实例的结尾移除 trimChars 中字符的所有匹配项后剩余的 Common.String。如果 trimChars 为null，则改为移除空白字符。 </returns>
        inline String &TrimEnd(char * trimChars)
		{
			if(trimChars==NULL)return TrimEnd(' ');
			String temp=trimChars;
			int i=size()-1,count=0;;
			while(temp.IndexOf(c_str()[i])>-1)
			{
				at(i)=0;
				count++;
				i--;
			}
			assign(c_str());
			return *this;
		}

 		///	<summary>
		///	从此实例的开始位置移除数组中指定的一组字符的所有匹配项
		///	<code>原型：inline String &amp;TrimStart(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">要移除的字符数组 </param> 
		///	<returns>此实例本身,从此实例的开始位置移除 trimChars 中字符的所有匹配项后剩余的 Common.String。如果 trimChars 为null，则改为移除空白字符。 </returns>
        inline String &TrimStart(char * trimChars)
		{
			if(trimChars==NULL)return TrimStart(' ');
			String temp=trimChars;
			int count=0;
			while(temp.IndexOf(c_str()[count])>-1)
			{
				count++;
			}
			assign(c_str()+count);
			return *this;
		}

 		///	<summary>
		///	获取此字符串对象的简单hash值
		///	<code>原型：inline unsigned int hashCode();</code>
		///	</summary> 
		///	<returns>一个无符号整数。 </returns>
		inline unsigned int hashCode(){return hashMath::hashsp(c_str(),size());};
 		///	<summary>
		///	获取此字符串对象的简单hash值
		///	<code>原型：inline static unsigned int getHashCode(const string &amp; s);</code>
		///	</summary> 
		///	<param name="s">要计算hash值的字符串 </param> 
		///	<returns>一个无符号整数。 </returns>
		inline static unsigned int getHashCode(const string & s){return hashMath::hashsp(s);};
 		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='String'/> 数组。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,char separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 中的一个或多个字符分隔</param> 
		///	<param name="separator">拆分字符</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		void Split(Array<String>  &result,char separator,StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='String'/> 数组。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,Array&lt;char> separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separators 中的一个或多个字符分隔</param> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
        void Split(Array<String>  &result,Array<char> & separators, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的字符串的元素或字符串分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,String separator,bool isString,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator指定的字符串或多个字符分隔</param> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="isString">指示separator是字符串还是字符数组，为真时以字符串拆分，为假时以字符串中的任一字符拆分</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
        void Split(Array<String>  &result,String separator,bool isString, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='String'/>分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,String separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 分隔</param> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		void Split(Array<String>  &result,String separator,StringSplitOptions options=None, int count=0)
		{
			Split(result,separator,true, options,count);
		};
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='String'/>数组分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,Array&lt;String>  &amp; separators,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separators 中的一个或多个字符串分隔</param> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
	    void Split(Array<String>  &result,Array<String> &separators, StringSplitOptions options=None, int count=0);
 		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='String'/> 数组。
		///	<code>原型：inline Array&lt;String> Split(char separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">拆分字符</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		///	<returns><see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 中的一个或多个字符串分隔</returns>
		inline Array<String> Split(char separator,StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,options, count);
			return result;
		};
   		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='String'/> 数组。
		///	<code>原型：inline Array&lt;String> Split(Array&lt;char> separator,
		///                                            StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		///	<returns><see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 中的一个或多个字符串分隔</returns>
		inline Array<String> Split(Array<char> & separators, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separators,options, count);
			return result;
		};
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的字符串的元素或字符串分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：inline Array&lt;String>  Split(String separator,bool isString,
		///                                            StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="isString">指示separator是字符串还是字符数组，为真时以字符串拆分，为假时以字符串中的任一字符拆分</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		///	<returns><see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 指定的字符串或多个字符分隔</returns>
		inline Array<String> Split(String separator,bool isString, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,isString,options, count);
			return result;
		};
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='String'/>分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：inline Array&lt;String> Split(String separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		///	<returns><see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 分隔</returns>
		inline Array<String> Split(String separator,StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,true,options, count);
			return result;
		};
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='String'/>数组分隔）的<see cref='String'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：void Split(Array&lt;String>  &amp;result,Array&lt;String>  &amp; separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		///	<returns><see cref='String'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separators 中的一个或多个字符串分隔</returns>
		inline Array<String> Split(Array<String> &separators, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separators,options, count);
			return result;
		};


//for base class string//
 		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='string'/> 数组。
		///	<code>原型：static void Split(Array&lt;string>  &amp;result,string str,char separator,
		///                                StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='string'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 中的一个或多个字符分隔</param> 
		///	<param name="str">要进行拆分的源字符串,<see cref='String'/>的父类<see cref='string'/></param> 
		///	<param name="separator">拆分字符</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		static void Split(Array<string>  &result,string str,char separator,StringSplitOptions options=None,int count=0);
   		///	<summary>
		///	字符拆分,返回包含此实例中的子字符串的 <see cref='string'/> 数组。
		///	<code>原型：static void Split(Array&lt;string>  &amp;result,string str,Array&lt;char> separator,
		///                               StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='string'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separators 中的一个或多个字符分隔</param> 
		///	<param name="str">要进行拆分的源字符串,<see cref='String'/>的父类<see cref='string'/></param> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		static void Split(Array<string>  &result,string str,Array<char> & separator, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的字符串的元素或字符串分隔）的<see cref='string'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：static void Split(Array&lt;string>  &amp;result,string separator,
		///                               bool isString,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='string'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator指定的字符串或多个字符分隔</param> 
		///	<param name="str">要进行拆分的源字符串,<see cref='String'/>的父类<see cref='string'/></param> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="isString">指示separator是字符串还是字符数组，为真时以字符串拆分，为假时以字符串中的任一字符拆分</param> 
		///	<param name="options">指定<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		static void Split(Array<string>  &result,string str,string separator,bool isString, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='string'/>分隔）的<see cref='string'/>数组。
		///	<code>原型：inline static void Split(Array&lt;string>  &amp;result,string str,string separator);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='string'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separator 分隔</param> 
		///	<param name="str">要进行拆分的源字符串,<see cref='String'/>的父类<see cref='string'/></param> 
		///	<param name="separator">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		inline static void Split(Array<string>  &result,string str,string separator){Split(result,str,separator,true);};
   		///	<summary>
		///	字符串拆分,返回包含此字符串中的子字符串（由指定的 <see cref='string'/>数组分隔）的<see cref='string'/>数组。参数指定是否返回空数组元素。
		///	<code>原型：static void Split(Array&lt;string>  &amp;result,string str,Array&lt;string>  &amp; separators,
		///                               StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">要保存结果值的<see cref='string'/> 数组,其元素包含此实例中的子字符串,这些子字符串由 separators 中的一个或多个字符串分隔</param> 
		///	<param name="str">要进行拆分的源字符串,<see cref='String'/>的父类<see cref='string'/></param> 
		///	<param name="separators">分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null</param> 
		///	<param name="options">指定<see cref='StringSplitOptions'/>.<see cref='RemoveEmptyEntries'/> 以省略返回的数组中的空数组元素，或指定<see cref='None'/> 以包含返回的数组中的空数组元素 </param> 
		///	<param name="count">要返回的子字符串的最大数量 </param>  
		static void Split(Array<string>  &result,string str,Array<string> &separators, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	字符串拆分,返回拆分大小
		///	<code>原型：inline static int SplitCpy(char * dest[],const char * src,char c);</code>
		///	</summary> 
		/// <remarks>快速拆分字符串,一般性能为: 90W/s</remarks>
		///	<param name="dest">要保存结果值的字符指针数组，二维字符数组，因进行了值的拷贝，所以每个维度的大小要有保证</param> 
		///	<param name="str">拆分源字符串</param> 
		///	<param name="c">拆分字符</param> 
		///	<returns>拆分的数组大小</returns>  
		inline static int SplitCpy(char * dest[],const char * src,char c,bool remove=false)
		{
			int count=0,len=0;
			if(c==0){strcpy(dest[0],src);return 1;}
			while(*src)
			{
				if(*src==c){dest[count++][len]=0; len=0;src++;if(remove )while(*src==c)src++;continue;}
				dest[count][len++]=*src++;
			}
			return count+1;
		}
   		///	<summary>
		///	字符串拆分,返回拆分大小
		///	<code>原型：inline static int Split(char * dest[],const char * src,char c);</code>
		///	</summary> 
		/// <remarks>快速拆分字符串,一般性能为: 200W/s
		///	         注意：源字符串中拆分字符值已经修改为空。</remarks>
		///	<param name="dest">要保存结果值的字符指针数组</param> 
		///	<param name="str">拆分源字符串</param> 
		///	<param name="c">拆分字符</param> 
		///	<returns>拆分的数组大小，指示dest指针数组中有效指针个数</returns>  
		inline static int Split(char * dest[],const char * src,char c,bool remove=false)
		{
			char * tp=(char *)src;
			dest[0]=tp;
			int count=1;
			if(c==0){return count;}
			while(tp=strchr(tp,c))
			{
				*tp=0;
				dest[count++]=++tp;
				if(remove && *tp==c)
					count--;
			}
			return count;
		}
   		///	<summary>
		///	字符串拆分,使用字符串来拆分字符串,返回拆分大小
		///	<code>原型：inline static int Split(char * dest[],const char * src,const char *spc);</code>
		///	</summary> 
		/// <remarks>快速拆分字符串,一般性能为: 100W/s
		///	         注意：源字符串中拆分字符开始位置值已经修改为空。</remarks>
		///	<param name="dest">要保存结果值的字符指针数组</param> 
		///	<param name="str">拆分源字符串</param> 
		///	<param name="spc">拆分字符串</param> 
		///	<returns>拆分的数组大小，指示dest指针数组中有效指针个数</returns>  
		inline static int Split(char * dest[],const char * src,const char *spc)
		{
			char * tp=(char *)src;
			int spLen=strlen(spc);
			dest[0]=tp;
			int count=1;
			if(spc[0]==0){return count;}
			while(tp=strchr(tp,spc[0]))
			{
				//判断tp是否以spc开始
				bool htrue=true;
				for(int i=1;i<spLen;i++)
				{
					if(tp[i]!=spc[i]){tp++;htrue=false;break;}
				}
				if(htrue)
				{
					*tp=0;
					tp+=spLen;
					dest[count++]=tp;
				}
			}
			return count;
		}

		///	<summary>
		///	对父类字符串对象大写转换
		///	<code>原型：inline static string&amp; ToUpper(string &amp;dest);</code>
		///	</summary> 
		///	<param name="dest">要转换的字符串对象</param> 
		///	<returns>dest所表示的字符串对象</returns>  
		inline static string& ToUpper(string &dest)
		{
			int i=-1;
			char * tp=(char *)dest.c_str();
			while(tp[++i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				tp[i]=charToUpper(tp[i]);
#else
				if(tp[i]>='a' && tp[i]<='z')
					tp[i]-=32;
#endif
			}
			return dest;
		};
		///	<summary>
		///	对父类字符串对象小写转换
		///	<code>原型：inline static string&amp; ToLower(string &amp;dest);</code>
		///	</summary> 
		///	<param name="dest">要转换的字符串对象</param> 
		///	<returns>dest所表示的字符串对象</returns>  
		inline static string& ToLower(string &dest)
		{
			int i=-1;
			char * tp=(char *)dest.c_str();
			while(dest[++i])
			{
#ifdef USE_CHAR_ARRAY_MAP 
				tp[i]=charToLower(tp[i]);
#else
				if(tp[i]>='A' && tp[i]<='Z')
					tp[i]+=32;
#endif
			}
			return dest;
		};
		///	<summary>
		///	报告指定字符在指定字符串中的第一个匹配项的索引。该搜索从指定字符位置开始。
		///	<code>原型：inline static int IndexOf(string str,char value, int startIndex,bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符</param> 
		///	<param name="startIndex">开始查找位置</param> 
		///	<param name="ignoreCase">是否忽略大小写</param> 
		///	<param name="count">指定要查找的字符个数,为0不指定</param> 
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
        inline static int IndexOf(string str,char value, int startIndex,bool ignoreCase, int count=0)
		{
			int i=startIndex,size=str.size();
			if(ignoreCase)
			{
				String::ToUpper(str);		
				if(value>='a' && value<='z')value=value-32;
			}
			const char * tmp=str.c_str();
			while(i<size && str[i])
			{
				if(count>0 && i-startIndex>=count)return -1;
				if(tmp[i]==value)return i;
				i++;
			}
			return -1;
		}
		///	<summary>
		///	报告指定字符在指定字符串中的第一个匹配项的索引。
		///	<code>原型：inline static int IndexOf(string str,char value, bool ignoreCase=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符</param>  
		///	<param name="ignoreCase">是否忽略大小写</param>  
		///	<returns>如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
		inline static int IndexOf(string str,char value, bool ignoreCase=0)
		{
			return IndexOf(str,value,0,ignoreCase);
		} 
		///	<summary>
		///	报告指定字符在指定字符串中的第一个匹配项的索引。该搜索从指定字符位置开始。
		///	<code>原型：inline static int IndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符串<see cref="string"/></param>  
		///	<param name="startIndex">开始查找位置</param> 
		///	<param name="ignoreCase">是否忽略大小写</param>  
		///	<param name="count">指定要查找的字符个数,为0不指定</param> 
		///	<returns> 如果找到该字符，则为 value 的索引位置；如果未找到该字符，则为 -1。如果 value 为 Common.String.Empty，则返回值为startIndex。</returns>  
		inline static int IndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0)
		{
			if(value.empty())return startIndex;
			int index=startIndex;
			char * _Str1=(char *)str.c_str()+startIndex;
			char * _Str2=(char *)value.c_str();
			if(str.size()<value.size())return -1;
			if(ignoreCase)
			{
				String::ToUpper(str);
				String::ToUpper(value);
			}
			_Str2=(char *)value.c_str();
			int len=str.size()-value.size();
			while(*_Str1)
			{
				if(count>0 && index-startIndex==count)break;
				int i=0;
				for(i=0;i<value.size() && _Str1[i];i++)
				{
					if(_Str1[i]!=_Str2[i])break;
				}
				if(i==value.size())return index;
				_Str1++;index++;
				if(len<index)return -1;
			}
			return -1;
		}

		///	<summary>
		///	报告指定字符在指定字符串中的第一个匹配项的索引。
		///	<code>原型：inline static int IndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符串</param>   
		///	<param name="ignoreCase">是否忽略大小写</param>   
		///	<returns> 如果找到该字符，则为 value 的索引位置；如果未找到该字符，则为 -1。如果 value 为 Common.String.Empty，则返回值为startIndex。</returns>  
		inline static int IndexOf(string str,string value, bool ignoreCase=false){return IndexOf(str,value,0,ignoreCase);}
		///	<summary>
		///	报告指定字符数组中的任意字符在指定字符串实例中第一个匹配项的索引，搜索从指定字符位置开始,并检查指定数量的字符位置。
		///	<code>原型：inline static int IndexOfAny(string str,string value, int startIndex, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="anyOf">要查找的字符元素组</param>   
		///	<param name="startIndex">开始查找位置</param> 
		///	<param name="count">指定要查找的字符个数,为0不指定</param>  
		///	<returns> 此实例中第一个匹配项的索引位置，在此处找到 anyOf 中的任意字符；否则，如果未找到 anyOf 中的字符，则为 -1。</returns>  
 		inline static int IndexOfAny(string str,string anyOf, int startIndex=0, int count=0)
		{
			if(count==0)return -1;
			int i=0;
			while(str[i+startIndex])
			{
				if(count>0 && i>=count)break;
				int j=0;
				while(anyOf[j])
				{
					if(str[i+startIndex]==anyOf[j]) return i;
					j++;
				}
				i++;
			}
			return -1;
		}

 		///	<summary>
		///	报告指定字符在指定字符串实例中最后一个匹配项的索引，搜索从指定字符位置开始。
		///	<code>原型：inline static int LastIndexOf(string str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符元素</param>  
		///	<param name="ignoreCase">要在对此实例与 value 进行比较时忽略大小写，则为 true；否则为 false。</param>  
		///	<returns> 如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
        inline static int LastIndexOf(string str,char value, bool ignoreCase=false)
		{
			if(ignoreCase)
			{
				String::ToUpper(str);
				if(value>='a' && value<='z')value=value-32;
				return String::LastIndexOf(str,value,0,0,0);
			}
			else
			{
				return String::LastIndexOf(str,value,0,0,0);
			}
		} 
 		///	<summary>
		///	报告指定字符在指定字符串实例中最后一个匹配项的索引，搜索从指定字符位置开始，并检查指定数量的字符位置。
		///	<code>原型：inline static int LastIndexOf(string str,char value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符元素</param>  
		///	<param name="startIndex">此实例内子字符串的起始位置</param>  
		///	<param name="ignoreCase">要在对此实例与 value 进行比较时忽略大小写，则为 true；否则为 false。</param>  
		///	<param name="count">指定要查找的字符个数,为0不指定</param>  
		///	<returns> 如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
        inline static int LastIndexOf(string str,char value, int startIndex, bool ignoreCase, int count=0)
		{
			int i=str.size()-1;
			char * temp=(char *)str.c_str();
			if(ignoreCase)
			{
				if(value>='a' && value<='z')value=value-32;
				String::ToUpper(str);
			}
			while(str[i] && i>=0)
			{
				if(i<startIndex)return -1;
				if(count>0 && (int)str.size()-i-1>=count)return -1;
				if(str[i]==value)return i;
				i--;
			}
			return -1;
		} 
  		///	<summary>
		///	报告指定字符串在指定字符串实例中最后一个匹配项的索引。
		///	<code>原型：inline static int LastIndexOf(string str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符串</param> 
		///	<param name="ignoreCase">要在对此实例与 value 进行比较时忽略大小写，则为 true；否则为 false。</param>  
		///	<returns> 如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
        inline static int LastIndexOf(string str,string value, bool ignoreCase=false)
		{
			return LastIndexOf(str,value,0,ignoreCase);
		}
  		///	<summary>
		///	报告指定字符串在指定字符串实例中最后一个匹配项的索引。
		///	<code>原型：inline static int LastIndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="value">要查找的字符串</param> 
		///	<param name="startIndex">此实例内子字符串的起始位置</param>  
		///	<param name="ignoreCase">要在对此实例与 value 进行比较时忽略大小写，则为 true；否则为 false。</param>  
		///	<param name="count">指定要查找的字符个数,为0不指定</param>  
 		///	<returns> 如果找到该字符，则为 value 的索引位置；否则如果未找到，则为 -1。</returns>  
        inline static int LastIndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0)
		{
			if(value.empty())return startIndex;
			int index=(int)str.size()-1;
			if(str.size()<value.size()+startIndex)return -1;
			const char * _Str1=str.c_str()+index;
			if(ignoreCase)
			{
				ToUpper(str);
				ToUpper(value);
			}
			const char * _Str2=value.c_str();
			while(*_Str1)
			{
				if(index<startIndex)break;
				if(count>0 && (int)str.size()-index-1>=count)return -1;
				if(String::strcmp(_Str1,_Str2,0,value.size())==0)return index;
				_Str1--;index--;
			}
			return -1;
		}
    
  		///	<summary>
		///	报告指定字符数组中的任意字符在指定字符串实例中最后一个匹配项的索引。
		///	<code>原型：inline static int LastIndexOfAny(string str,string anyOf, int startIndex=0, int count=0);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param> 
		///	<param name="anyOf">要查找的字符串</param> 
		///	<param name="startIndex">此实例内子字符串的起始位置</param>
		///	<param name="count">指定要查找的字符个数,为0不指定</param>  
 		///	<returns> 此实例中最后一个匹配项的索引位置，在此位置找到 anyOf 中的任意字符；否则，如果未找到 anyOf 中的字符，则为 -1。</returns>  
		inline static int LastIndexOfAny(string str,string anyOf, int startIndex=0, int count=0)
		{
			int i=startIndex+count-1;
			if(i>=str.size())i=str.size()-1;
			while(str[i] && i>=0)
			{
				int j=0;
				while(anyOf[j])
				{
					if(str[i]==anyOf[j]) return i;
					j++;
				}
				i--;
				if(i<startIndex)return -1;
			}
			return -1;
		}

  		///	<summary>
		///	从指定实例的开始位置和末尾移除空白字符的所有匹配项。
		///	<code>原型：inline static string &amp;Trim(string &amp;str);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param>  
 		///	<returns> str实例。</returns>  
		inline static string &Trim(string &str){return String::Trim(str,' ');};
  		///	<summary>
		///	从指定实例的开始位置和末尾移除指定字符的所有匹配项。
		///	<code>原型：inline static string &amp;Trim(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">源字符串对象</param>  
		///	<param name="c">移除字符</param>  
 		///	<returns> str实例。</returns>  
		inline static string &Trim(string &str,char c)
		{
			int i=str.size()-1,startIndex=0,endCount=0;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(str[i]==c || str[i]==temp)
			{
				str.at(i)=0;
				endCount++;
				i--;
			}
			while(str[startIndex]==c || str[startIndex]==temp)
			{
				startIndex++;
			}
			str.assign(str.c_str()+startIndex);
			return str;
		}
  		///	<summary>
		///	从指定字符指针的开始位置和末尾移除指定字符的所有匹配项。
		///	<code>原型：inline static char * Trim(char *str,char c);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param>  
		///	<param name="c">移除字符</param>  
 		///	<returns> 新字符开始位置指针。</returns>  
		inline static char * Trim(char *str,char c)
		{
			if(str==NULL)return str;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(*str==c || *str==temp )
			{
				str++;
			}
			char * tp=str+strlen(str)-1;
			while(*tp==c || *tp==temp)
			{
				*tp=0;
				tp--;
			}
			return str;
		}
  		///	<summary>
		///	从指定字符指针的开始位置和末尾移除空白字符的所有匹配项。
		///	<code>原型：inline static char * Trim(const char * str);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
 		///	<returns> 新字符开始位置指针。</returns>  
		inline static char * Trim(char * str){return String::Trim((char *)str,' ');};
  		///	<summary>
		///	从指定字符对象的末尾移除指定字符的所有匹配项。
		///	<code>原型：inline static string &amp;TrimEnd(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="c">移除字符</param>  
 		///	<returns> str实例。</returns>  
		inline static string &TrimEnd(string &str,char c)
		{
			int i=str.size()-1,count=0;;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(str[i]==c || str[i]==temp)
			{
				str.at(i)=0;
				count++;
				i--;
			}
			str.assign(str.c_str());
			return str;
		}
  		///	<summary>
		///	从指定字符对象的开始位置移除指定字符的所有匹配项。
		///	<code>原型：inline static string &amp;TrimStart(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="c">移除字符</param>  
 		///	<returns> str实例。</returns>  
		inline static string &TrimStart(string &str,char c)
		{
			int count=0;
			char temp=(c==32)?'\t':(c=='\t')?32:c;
			while(str[count]==c || str[count]==temp)
			{
				count++;
			}
			str.assign(str.c_str()+count);
			return str;
		}
   		///	<summary>
		///	从指定字符对象的开始位置移除一组字符的所有匹配项。
		///	<code>原型：inline static string &amp;Trim(string &amp;str,char *trimChars);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="trimChars">要移除的char字符指针,如果 trimChars 为null，则改为移除空白字符。</param>  
 		///	<returns> str实例。</returns>  
        inline static string &Trim(string &str,char * trimChars)
		{
			if(trimChars==NULL)return Trim(str);
			string temp=trimChars;
			int i=str.size()-1,startIndex=0,endCount=0;
			while(String::IndexOf(temp,str[i])>-1)
			{
				str.at(i)=0;
				endCount++;
				i--;
			}
			while(String::IndexOf(temp,str[startIndex])>-1)
			{
				startIndex++;
			}
			str.assign(str.c_str()+startIndex);
			return str;
		}
   		///	<summary>
		///	从指定字符对象的结尾移除一组字符的所有匹配项。
		///	<code>原型：inline static string &amp;TrimEnd(string &amp;str,char * trimChars);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="trimChars">要移除的char字符指针,如果 trimChars 为null，则改为移除空白字符。</param>  
 		///	<returns> str实例。</returns>  
        inline static string &TrimEnd(string &str,char * trimChars)
		{
			if(trimChars==NULL)return TrimEnd(str,' ');
			string temp=trimChars;
			int i=str.size()-1,count=0;;
			while(String::IndexOf(temp,str[i])>-1)
			{
				str.at(i)=0;
				count++;
				i--;
			}
			str.assign(str.c_str());
			return str;
		}
   		///	<summary>
		///	从指定字符对象的开始位置移除一组字符的所有匹配项。
		///	<code>原型：inline static string &amp;TrimStart(string &amp;str,char * trimChars);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="trimChars">要移除的char字符指针,如果 trimChars 为null，则改为移除空白字符。</param>  
 		///	<returns> str实例。</returns>  
        inline static string &TrimStart(string &str,char * trimChars)
		{
			if(trimChars==NULL)return TrimStart(str,' ');
			string temp=trimChars;
			int count=0;
			while(String::IndexOf(temp,str[count])>-1)
			{
				count++;
			}
			str.assign(str.c_str()+count);
			return str;
		} 
		///	<summary>
		///	确定此字符串的开头是否与指定的字符串匹配。
		///	<code>原型：inline static bool StartsWith(const string &amp;str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="value">要比较的<see cref='string'/>。</param>  
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。</param> 
 		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>  
		inline static bool StartsWith(const string &str,string value, bool ignoreCase=false)
		{
			//return IndexOf(str,value,0,ignoreCase)==0;
			if(value.empty())return true;
			if(str.size()<value.size())return false;
			char * _Str1=(char *)str.c_str();
			char * _Str2;
			String temp1;
			if(ignoreCase)
			{
				temp1=_Str1;
				temp1.ToUpper();
				String::ToUpper(value);
				_Str1=(char *)temp1.c_str();
			}
			_Str2=(char *)value.c_str();
			for(int i=0;i<value.size() && _Str1[i];i++)
			{
				if(_Str1[i]!=_Str2[i])return false;
			}
			return true;
		};
		///	<summary>
		///	确定此字符串的开头是否与指定的字符匹配。
		///	<code>原型：inline static bool StartsWith(const string &amp;str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="value">要比较的字符。</param>  
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。</param> 
 		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>  
 		inline static bool StartsWith(const string &str,char value, bool ignoreCase=false)
		{
			//return IndexOf(str,value,0,ignoreCase)==0;
			if(value==0)return true;
			if(str.size()==0)return false;
			char c=str.at(0);
			if(ignoreCase)
			{
				if(value>='a' && value<='z')
					value=value-32;
				if(c>='a' && c<='z')
					c=c-32;
			}
			return c==value;
		};
		///	<summary>
		///	确定此字符串的结尾是否与指定的字符串匹配。
		///	<code>原型：inline static bool EndsWith(const string &amp;str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="value">要比较的字符串。</param>  
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。</param> 
 		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>  
		inline static bool EndsWith(const string &str,string value, bool ignoreCase=false)
		{
			//return LastIndexOf(str,value,0,ignoreCase)==(int)str.size()-(int)value.size();
			if(value.empty())return true;
			if(str.size()<value.size())return false;
			char * _Str1=(char *)str.c_str()+str.size()-value.size();
			char * _Str2;
			String temp1;
			if(ignoreCase)
			{
				temp1=_Str1;
				temp1.ToUpper();
				String::ToUpper(value);
				_Str1=(char *)temp1.c_str();
			}
			_Str2=(char *)value.c_str();
			return strcmp(_Str1,_Str2)==0;
		};
		///	<summary>
		///	确定此字符串的结尾是否与指定的字符匹配。
		///	<code>原型：inline static bool EndsWith(const string &amp;str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="value">要比较的字符。</param>  
		///	<param name="ignoreCase">若要在对此字符串与 value 进行比较时忽略大小写，则为 true；否则为 false。</param> 
 		///	<returns> 如果 value 参数与此字符串的开头匹配，则为 true；否则为 false。</returns>  
		inline static bool EndsWith(const string &str,char value, bool ignoreCase=false)
		{
			if(value==0)return true;
			if(str.size()==0)return false;
			char c=str.at(str.size()-1);
			if(ignoreCase)
			{
				if(value>='a' && value<='z')
					value=value-32;
				if(c>='a' && c<='z')
					c=c-32;
			}
			return c==value;
		};
 		///	<summary>
		///	右对齐此实例中的字符，在左边用指定的字符填充以达到指定的总长度。
		///	<code>原型：inline static string &amp;PadLeft(string &amp;str,int totalWidth, char paddingChar=' ');</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="totalWidth">结果字符串中的字符数，等于原始字符数加上任何其他填充字符。 </param>
		///	<param name="paddingChar">填充字符</param> 
 		///	<returns> str对象本身，但它是右对齐的，并在左边用达到 totalWidth 长度所需数目的 paddingChar 字符进行填充。如果
        ///     totalWidth 小于此实例的长度，则不修改。</returns>  
        inline static string &PadLeft(string &str,int totalWidth, char paddingChar=' ')
		{
			int len=str.size();
			if(len>=totalWidth)return str;
			int startIndex=totalWidth-len;
			char * temp=new char[startIndex+1];
			temp[startIndex]='\0';
			for(int i=0;i<startIndex;i++)
			{
				 temp[i]=paddingChar;
			}
			str.insert(0,temp);
			delete[] temp;
			return str;
		}
  		///	<summary>
		///	左对齐此实例中的字符，在右边用指定的字符填充以达到指定的总长度。
		///	<code>原型：inline static string &amp;PadRight(string &amp;str,int totalWidth, char paddingChar=' ');</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="totalWidth">结果字符串中的字符数，等于原始字符数加上任何其他填充字符。 </param>
		///	<param name="paddingChar">填充字符</param> 
 		///	<returns> str对象本身，但它是左对齐的，并在右边用达到 totalWidth 长度所需数目的 paddingChar 字符进行填充。如果
        ///     totalWidth 小于此实例的长度，则不修改。</returns>  
        inline static string &PadRight(string &str,int totalWidth, char paddingChar=' ')
		{
			int len=str.size();
			if(len>=totalWidth)return str;
			int startIndex=totalWidth-len;
			char * temp=new char[startIndex+1];
			temp[startIndex]='\0';
			for(int i=0;i<startIndex;i++)
			{
				 temp[i]=paddingChar;
			}
			str.append(temp);
			delete[] temp;
			return str;
		}

  		///	<summary>
		///	删除此字符串中从指定位置到最后位置的所有字符。
		///	<code>原型：inline static string &amp;Remove(string &amp;str,int startIndex);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="startIndex">开始删除字符的位置。 </param> 
 		///	<returns> str对象本身，它等于此字符串剔除已删除字符后的字符串。</returns>  
        inline static string &Remove(string &str,int startIndex)
		{
			return Remove(str,startIndex,(int)str.size()-startIndex);
		}
   		///	<summary>
		///	从此实例中的指定位置开始删除指定数目的字符。
		///	<code>原型：inline static string &amp;Remove(string &amp;str,int startIndex, int count);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="startIndex">开始删除字符的位置。 </param> 
		///	<param name="count">要删除的字符数。 </param> 
 		///	<returns> str对象本身，它等于此字符串剔除已删除字符后的字符串。</returns>  
        inline static string &Remove(string &str,int startIndex, int count)
		{
			str.erase(startIndex,count);
			return str;
		}; 
   		///	<summary>
		///	将此实例中的指定字符的所有匹配项替换为其他指定的字符。。
		///	<code>原型：inline static string ReplaceAll(string &amp;str,char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="oldChar"> 要替换的字符。 </param> 
		///	<param name="newChar">要替换 oldChar 的所有匹配项的字符。。 </param> 
		///	<param name="ignoreCase">是否忽略大小写。 </param> 
		///	<returns> 等效于此实例，但将 oldChar 的所有实例都替换为 newChar 的<see cref="String"/>。</returns>  
        inline static string ReplaceAll(string &str,char oldChar, char newChar,bool ignoreCase=false)
		{
			string result;
			if(oldChar==newChar)
			{
				result=str.c_str();
				return result.c_str();
			}
			//result=string('\0',(int)str.size());
			result.resize(str.size());
			if(newChar!=0)
			{
				int i=0;
				char upchar=oldChar;
				if(ignoreCase)
				{
					if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar+32;
					else if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar-32;
				}
				while(str[i])
				{
					if(str[i]==oldChar || str[i]==upchar)
					{
						result.at(i)=newChar;
					}
					else
					{
						result.at(i)=str[i];
					}
					i++;
				}
			}
			else
			{
				int i=0,count=0;
				while(str[i])
				{
					if(str[i]!=oldChar)
					{
						result.at(count)=str[i];
						count++;
					}
					i++;
				}
			}
			return result;
		}
   		///	<summary>
		///	将此实例中的指定字符的第一个匹配项替换为其他指定的字符。
		///	<code>原型：inline static string Replace(string &amp;str,char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串指针</param> 
		///	<param name="oldChar"> 要替换的字符。 </param> 
		///	<param name="newChar">要替换 oldChar 的所有匹配项的字符。 </param> 
		///	<param name="ignoreCase">是否忽略大小写。 </param> 
 		///	<returns> 等效于此实例，但将 oldChar 的第一个实例替换为 newChar 的<see cref="string"/>。</returns>  
		inline static string Replace(string &str,char oldChar, char newChar,bool ignoreCase=false)
		{
			if(oldChar==newChar)
			{
				return str;
			}
			string result=str;
			if(newChar!=0)
			{
				int i=0;
				char upchar=oldChar;
				if(ignoreCase)
				{
					if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar+32;
					else if(oldChar>='A' && oldChar<='Z')
						upchar=oldChar-32;
				}
				while(result[i])
				{
					if(result[i]==oldChar || str[i]==upchar)
					{
						result.at(i)=newChar;
						break;
					}
					i++;
				}
			}
			else
			{
				int i=0;
				while(result[i])
				{
					if(result[i]==oldChar)
					{
						break;
					}
					result.at(i)=str[i];
					i++;
				}
				for(;i<str.size();i++)
				{
					result.at(i)=str[i+1];
				}
			}
			return result;
		}
   		///	<summary>
		///	将此实例中的指定 <see cref="string"/> 的所有匹配项替换为其他指定的 <see cref="string"/>。
		///	<code>原型：inline static string ReplaceAll(string &amp;str,const string&amp; oldValue, 
		///                                             const string&amp; newValue,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串</param> 
		///	<param name="oldChar"> 要替换的<see cref="string"/>。 </param> 
		///	<param name="newChar">要替换 oldChar 的所有匹配项的<see cref="string"/>。 </param> 
		///	<param name="ignoreCase">是否忽略大小写。 </param> 
 		///	<returns> 等效于此实例，但将 oldChar 的第一个实例替换为 newChar 的<see cref="string"/>。</returns>  
		inline static string ReplaceAll(string &str,const string& oldValue, const string& newValue,bool ignoreCase=false)
		{
			string& result=str;
			if(oldValue==newValue)
			{
				return result;
			}
			int index=0;
			while((index=IndexOf(result,oldValue,index,ignoreCase))>-1)
			{
				result=result.substr(0,index)+newValue+result.substr(index+oldValue.size());
				index+=newValue.size();
			}
			return result;
		}
   		///	<summary>
		///	将此实例中的指定 <see cref="string"/> 的第一个匹配项替换为其他指定的 <see cref="string"/>。
		///	<code>原型：inline static string Replace(string &amp;str,const string&amp; oldValue, 
		///                                             const string&amp; newValue,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">源字符串</param> 
		///	<param name="oldChar"> 要替换的<see cref="string"/>。 </param> 
		///	<param name="newChar">要替换 oldChar 的所有匹配项的<see cref="string"/>。 </param> 
		///	<param name="ignoreCase">是否忽略大小写。 </param> 
 		///	<returns> 等效于此实例，但将 oldChar 的第一个实例替换为 newChar 的<see cref="string"/>。</returns>  
		inline static string Replace(string &str,const string& oldValue, const string& newValue,bool ignoreCase=false)
		{
			string result=str;
			if(oldValue==newValue)
			{
				return result;
			}
			int index=IndexOf(str,oldValue,ignoreCase);
			if(index==-1)
			{
				return result;
			}
			if(newValue.size()==0)
				result=str.substr(0,index)+str.substr(index+oldValue.size());
			else
				result=str.substr(0,index)+newValue+str.substr(index+oldValue.size());
			return result;
		}

#if defined(__OTL_H__)
   		///	<summary>
		///	从otl_datetime对象输入字符
		///	<code>原型：String&amp; operator&lt;&lt;(otl_datetime&amp; t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime 时间对象</param> 
 		///	<returns><see cref="String"/>实例本身。</returns>  
		String& operator<<(otl_datetime& t)
		{
			if(t.year==0){(*this)=""; return *this;}
			char p[20];
			sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",t.year,t.month,t.day,t.hour,t.minute,t.second);
			(*this)=p;
			return *this;
		};
   		///	<summary>
		///	以otl_datetime对象实例化<see cref="String"/>对象
		///	<code>原型：String(otl_datetime t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime 时间对象</param>  
		String(otl_datetime t)
		{
			if(t.year==0){(*this)=""; }
			char p[20];
			sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",t.year,t.month,t.day,t.hour,t.minute,t.second);
			(*this)=p;
		};
   		///	<summary>
		///	以otl_datetime对<see cref="String"/>对象赋值
		///	<code>原型：String &amp;operator=(otl_datetime &amp;t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime 时间对象</param>  
		String &operator=(otl_datetime &t)
		{
			if(t.year==0){(*this)=""; }
			char p[20];
			sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",t.year,t.month,t.day,t.hour,t.minute,t.second);
			return (*this)=p;
		};
#endif
	};

	inline ostream& operator<<(ostream& target, const String& s)
	{
		target << s.c_str();
		return target;
	}

	inline String operator+(const String &a,const char * b)
	{
		String result=b;
		result.insert(0,a);
		return result;
	}
	inline String operator+(const char * b,const String &a)
	{
		String result=b;
		result.append(a);
		return result;
	}
	inline String operator+(const int b,const String& a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String& a,const int b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const unsigned int b,const String &a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String &a,const unsigned int b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const long b,const String &a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String &a,const long b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const unsigned long b,const String &a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String &a,const unsigned long b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const unsigned long long b,const String &a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String &a,const unsigned long long b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const long long b,const String &a)
	{
		String temp=b;
		return temp.append(a);
	}
	inline String operator+(const String &a,const long long b)
	{
		String temp=b;
		return temp.insert(0,a);
	}
	inline String operator+(const double b,const String &a)
	{
		String temp=Convert::ToString(b);
		temp+=a;
		return temp;
	}
	inline String operator+(const String &a,const double b)
	{
		String temp=a;
		temp+=Convert::ToString(b);
		return temp;
	}
	inline String operator+(const char b,const String &a)
	{
        String result=b;
		return result.insert(result.size(),a);
	}
	inline String operator+(const String &b,const char a)
	{
        String result=a;
		return result.insert(0,b);
	}

#ifndef _MSC_VER
	//  string + String 
	inline String operator+(const String &a, String b)
	{
		String temp=a;
		return temp.append(b);
	}
	inline String operator+(const string &a,const String &b)
	{
		String temp=a;
		return temp.append(b);
	}
	inline String operator+(const String &a,const string &b)
	{
		String temp=a;
		return temp.append(b);
	}
#endif
	inline String & operator+=(String &b,const int a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline String & operator+=(String &b,const long a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline String & operator+=(String &b,const long long a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline String & operator+=(String &b,const unsigned int a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline String & operator+=(String &b,const unsigned long a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline String & operator+=(String &b,const unsigned long long a)
	{
		String t=a;
		b.append(t);
		return b;
	}
	inline string & operator+=(string &b,const double a)
	{
		b.append(Convert::ToString(a));
		return b;
	}
	inline String & operator+=(String &b,const char a)
	{
		b.append(String(a));
		return b;
	}
	inline String & operator+=(String &b,const char * a)
	{
		b.append(a);
		return b;
	}
	inline String & operator+=(String &b,const String &a)
	{
		b.append(a);
		return b;
	}

	inline string & operator+=(string &b,const String &a)
	{
		b.append(a);
		return b;
	}

	inline String & operator+=(String &b,const string &a)
	{
		b.append(a);
		return b;
	}

	
	// 摘要:
    //     一般性字符串操作符比较。
    //
    // 返回结果:
    //     如果 a 的值与 b 的值不同，则为 true；否则为 false。
    //
    bool inline operator>(const  String &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>0;
    };
    bool inline operator>(const  String &a,const  string &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>0;
    };
    bool inline operator>(const  string &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>0;
    };
    bool inline operator>=(const  String &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>=0;
    };
    bool inline operator>=(const  String &a,const  string &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>=0;
    };
    bool inline operator>=(const  string &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())>=0;
    };
    bool inline operator<=(const  String &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<=0;
    };
    bool inline operator<=(const  String &a,const  string &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<=0;
    };
    bool inline operator<=(const  string &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<=0;
    };
    bool inline operator<(const  String &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<0;
    };

    bool inline operator<(const  String &a,const  string &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<0;
    };

    bool inline operator<(const  string &a,const  String &b)
    {
        return String::strcmp(a.c_str(),b.c_str())<0;
    };

    bool inline operator> (const  String &a,const  char * b)
    {
        return String::strcmp(a.c_str(),b)>0;
    };
    bool inline operator>=(const  String &a,const  char * b)
    {
        return String::strcmp(a.c_str(),b)>=0;
    };
    bool inline operator<=(const  String &a,const  char * b)
    {
        return String::strcmp(a.c_str(),b)<=0;
    };
    bool inline operator< (const  String &a,const  char * b)
    {
        return String::strcmp(a.c_str(),b)<0;
    };

	// 摘要:
    //     确定两个指定的 Common.String 对象是否具有不同的值。
    //
    // 参数:
    //   a:
    //     String 或null。
    //
    // 返回结果:
    //     如果 a 的值与 b 的值不同，则为 true；否则为 false。
	bool inline operator!=(const String &a,const String &b)
	{
        return String::strcmp(a.c_str(),b.c_str())!=0;
	};
	bool inline operator!=(const String &a,const string &b)
	{
        return String::strcmp(a.c_str(),b.c_str())!=0;
	};
	bool inline operator!=(const string &a,const String &b)
	{
        return String::strcmp(a.c_str(),b.c_str())!=0;
	};
	bool inline operator!=(const String &a,const char * b)
	{
        return String::strcmp(a.c_str(),b)!=0;
	};
    //
    // 摘要:
    //     确定两个指定的 Common.String 对象是否具有同一值。
    //
    // 参数:
    //   a:
    //     Common.String 或null。
    //
    // 返回结果:
    //     如果 a 的值与 b 的值相同，则为 true；否则为 false。
	bool inline operator==(const  String &a,const  String &b)
	{
        return String::strcmp(a.c_str(),b.c_str())==0;
	 };
	bool inline operator==(const  string &a,const  String &b)
	{
        return String::strcmp(a.c_str(),b.c_str())==0;
	 };
	bool inline operator==(const  String &a,const  string &b)
	{
        return String::strcmp(a.c_str(),b.c_str())==0;
	 };
	bool inline operator==(const  String &a,const char *b)
	{
		return String::strcmp(a.c_str(),b)==0;
	};
	//
	inline int operator%(const String &s,const int b)
	{
		return String::getHashCode(s) % b;
	}
}
#endif
