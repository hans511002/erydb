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
	///	�ַ�����
	///	</summary>
	///	<remarks>
	///	<code>�̳�STL��׼�࣬��չ������ASCII�ַ�������ϵͳĬ�ϱ���
    /// �� ��: ��Զ��
    /// �� ��: 2007-4-25
	/// �� ��: 1.0
	///	//δ�����ϸע�͵��������㷽��
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
	///	Ӧ�������в���������
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
		///	�����հ��ַ�����
		///	</summary>
		///	<remarks>ֵ�б�<code>    '\t','\n','\v','\f','\r',' ','\b','\a'</code></remarks>
		static const char WhitespaceChars[];
		///	<summary>
		///	�ַ�������
		///	<code>ԭ�ͣ�inline static char * strcpy(char * dest,const char * source);</code>
		///	</summary>
		///	<param name="dest">Ŀ��洢ָ�룬Ҫ��dest��ָ��Ĵ洢�ռ�Ҫ��Դ�󣬷�����ɷǷ���ַ����</param>
		///	<param name="source">Դ����ָ��</param>
		///	<returns>����destָ��</returns>
		inline static char * strcpy(char * dest,const char * source)
		{
			::strcpy(dest,source);
			return dest;
		}
		///	<summary>
		///	�ַ���������ָ��Դ��ʼλ��
		///	<code>ԭ�ͣ�inline static char *  strcpy(char * dest,const char * source,int startIndex);</code>
		///	</summary>
		///	<param name="dest">Ŀ��洢ָ�룬Ҫ��dest��ָ��Ĵ洢�ռ�Ҫ��Դ�󣬷�����ɷǷ���ַ����</param>
		///	<param name="source">Դ����ָ��</param>
		///	<param name="startIndex">��ʼ����λ��</param>
		///	<returns>����destָ��</returns>
		inline static char *  strcpy(char * dest,const char * source,int startIndex)
		{
			source+=startIndex;
			STDSPACE::strcpy(dest,source);
			return dest;
		}
		///	<summary>
		///	�ַ���������ָ��Դ��ʼλ�úͳ���
		///	<code>ԭ�ͣ�inline static char *  strcpy(char * dest,const char * source,int startIndex,int length);</code>
		///	</summary>
		///	<param name="dest">Ŀ��洢ָ�룬Ҫ��dest��ָ��Ĵ洢�ռ�Ҫ��Դ�󣬷�����ɷǷ���ַ����</param>
		///	<param name="source">Դ����ָ��</param>
		///	<param name="startIndex">��ʼ����λ��</param>
		///	<param name="length">��Ҫ�����ĳ���</param>
		///	<returns>�������ֽ���</returns>
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
		///	�ֽڿ���,ǿ�ƿ���
		///	<code>ԭ�ͣ�inline static void strcpy(unsigned char * dest,const unsigned char * source,int length);</code>
		///	</summary>
		///	<param name="dest">Ŀ��洢ָ�룬Ҫ��dest��ָ��Ĵ洢�ռ䲻�ܱ�lengthС��������ɷǷ���ַ����</param>
		///	<param name="source">Դ����ָ��</param>
		///	<param name="length">��Ҫ�����ĳ���</param>
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
		///	�ַ���������ָ��Դ��ʼλ�úͳ���
		///	<code>ԭ�ͣ�inline static int strcpy(char * dest,int startIndex,const char * source,int sourceIndex,int length);</code>
		///	</summary>
		///	<param name="dest">Ŀ��洢ָ��</param>
		///	<param name="startIndex">Ŀ�꿪ʼ����λ��</param>
		///	<param name="source">Դ����ָ��</param>
		///	<param name="sourceIndex">Դ��ʼ����λ��</param>
		///	<param name="length">��Ҫ�����ĳ���</param>
		///	<returns>�������ֽ���</returns>
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
		///	��ȡ�ַ�ָ��ָ���ַ��ĳ���
		///	<code>ԭ�ͣ�inline static int strlen(const char *source);</code>
		///	</summary> 
		///	<param name="source">�ַ�ָ��</param>
		///	<returns>�ַ�����</returns>
		inline static int strlen(const char *source)
		{
			return STDSPACE::strlen(source);
		};
		///	<summary>
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,const char * _Str2);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,const char * _Str2)
		{
			return STDSPACE::strcmp(_Str1,_Str2);
		}
		///	<summary>
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,const char * _Str2,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
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
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<param name="index">�ַ��ȽϵĿ�ʼλ��</param>
		///	<param name="length">Ҫ�Ƚϵĳ���</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
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
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,const char * _Str2,int index,int length,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<param name="index">�ַ��ȽϵĿ�ʼλ��</param>
		///	<param name="length">Ҫ�Ƚϵĳ���</param>
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
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
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="indexA">�ַ�_Str1�ȽϵĿ�ʼλ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<param name="indexB">�ַ�_Str2�ȽϵĿ�ʼλ��</param>
		///	<param name="length">Ҫ�Ƚϵĳ���</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length)
		{
			return strcmp(_Str1+indexA,_Str2+indexB,0,length);		
		}
		///	<summary>
		///	�Ƚ������ַ���ֵ�����ָʾ
		///	<code>ԭ�ͣ�inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,
		///                                      int indexB,int length,bool ignoreCase);</code>
		///	</summary> 
		///	<param name="_Str1">ָ���ַ���ָ��</param>
		///	<param name="indexA">�ַ�_Str1�ȽϵĿ�ʼλ��</param>
		///	<param name="_Str2">ָ���ַ���ָ��</param>
		///	<param name="indexB">�ַ�_Str2�ȽϵĿ�ʼλ��</param>
		///	<param name="length">Ҫ�Ƚϵĳ���</param>
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns> ��ԱȽ�ֵ  1:_Str1>_Str2 , 0:_Str1=_Str2 , -1:_Str1&lt;_Str2</returns>
		inline static int strcmp(const char * _Str1,int indexA,const char * _Str2,int indexB,int length,bool ignoreCase)
		{
			return strcmp(_Str1+indexA,_Str2+indexB,0,length,ignoreCase);	
		}

		///	<summary>
		///	�ַ�������,��source������destĩβ���ַ���ָ��
		///	<code>ԭ�ͣ�inline static char * strcat(char * dest,const char * source);</code>
		///	</summary> 
		///	<param name="dest">ָ���ַ���ָ��</param> 
		///	<param name="source">ָ���ַ���ָ��</param> 
		///	<returns> ���Ӻ��dest</returns>
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
		///	��ʽ���ַ��ڴ�ռ�
		///	<code>ԭ�ͣ�inline static char * memset(char * _Dst,  int _Val,  int _Size);</code>
		///	</summary> 
		///	<param name="_Dst">Ŀ���ַ���ָ��</param> 
		///	<param name="_Val">Ҫ�����ַ�ֵ</param>
		///	<param name="_Size">��ʶ_Dst�Ĵ�С,Ҫ�����ַ�����</param> 
		///	<returns>���_Val���_Dstָ��</returns>
		inline static char * memset(char * _Dst,  int _Val,  int _Size)
		{
			STDSPACE::memset(_Dst,_Val,_Size);
			return _Dst;
		}
		///	<summary>
		///	��ʽ���ڴ�ռ�
		///	<code>ԭ�ͣ�inline static char * memset(char * _Dst,  int _Val,  int _Size);</code>
		///	</summary> 
		///	<param name="_Dst">�ڴ�ָ��</param> 
		///	<param name="_Val">Ҫ�����ַ�ֵ</param>
		///	<param name="_Size">��ʶ_Dst�Ĵ�С,Ҫ�����ַ�����</param> 
		inline static void * memset(void * _Dst,  int _Val,  int _Size)
		{
			STDSPACE::memset(_Dst,_Val,_Size);
			return _Dst;
		}
 
		///	<summary>
		///	��дת��
		///	<code>ԭ�ͣ�inline static char * ToUpper(char * dest);</code>
		///	</summary> 
		///	<param name="dest">Ҫת�����ַ���ָ��</param> 
		///	<returns>ת�����destָ��</returns>
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
		///	Сдת��
		///	<code>ԭ�ͣ�inline static char * ToLower(char * dest);</code>
		///	</summary> 
		///	<param name="dest">Ҫת�����ַ���ָ��</param> 
		///	<returns>ת�����destָ��</returns>
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
		///	�Ի���<see cref="string"/>��ʼ������
		///	<code>ԭ�ͣ�String(string s);</code>
		///	</summary> 
		///	<param name="value"><see cref="string"/>����</param> 
		String(string s):string(s){};
		//String(const String &s){this->assign(s.c_str());};

		///	<summary>
		///	���ַ�ָ���ʼ��
		///	<code>ԭ�ͣ�String(const char * value);</code>
		///	</summary> 
		///	<param name="value">�ַ���ָ��</param> 
		String(const char * value):string(value){};
		///	<summary>
		///	��������ʼ��
		///	<code>ԭ�ͣ�String(int i);</code>
		///	</summary> 
		///	<param name="i">����</param> 
		String(int i){char p[40];sprintf(p,"%d",i);assign(p);};
		///	<summary>
		///	�Գ�������ʼ��
		///	<code>ԭ�ͣ�String(long i);</code>
		///	</summary> 
		///	<param name="l">����</param> 
		String(long l){char p[40];sprintf(p,"%ld",l);assign(p);};
		///	<summary>
		///	��64λ��������ʼ��
		///	<code>ԭ�ͣ�String(long long i);</code>
		///	</summary> 
		///	<param name="l">64λ������</param> 
		String(long long l){char p[40];sprintf(p,"%lld",l);assign(p);};
		///	<summary>
		///	���޷���������ʼ��
		///	<code>ԭ�ͣ�String(unsigned int i);</code>
		///	</summary> 
		///	<param name="l">�޷�������</param> 
		String(unsigned int i){char p[40];sprintf(p,"%u",i);assign(p);};
		///	<summary>
		///	���޷��ų�������ʼ��
		///	<code>ԭ�ͣ�String(unsigned long i);</code>
		///	</summary> 
		///	<param name="l">�޷��ų�����</param> 
		String(unsigned long l){char p[40];sprintf(p,"%lu",l);assign(p);};
		///	<summary>
		///	���޷���64λ������ʼ��
		///	<code>ԭ�ͣ�String(unsigned long long  i);</code>
		///	</summary> 
		///	<param name="l">�޷���64λ����</param> 
		String(unsigned long long l){char p[40];sprintf(p,"%llu",l);assign(p);};
		///	<summary>
		///	��double��ʼ��
		///	<code>ԭ�ͣ�String(double i);</code>
		///	</summary> 
		///	<param name="d">double��������</param> 
		String(double d):string(Convert::ToString(d)){}//{ *this=Convert::ToString(d);};
		///	<summary>
		///	���ַ���ʼ��
		///	<code>ԭ�ͣ�String(char i);</code>
		///	</summary> 
		///	<param name="c">�ַ�</param> 
		String(char c){char p[2];p[0]=c;p[1]=0;assign(p);};
		///	<summary>
		///	����ͬ�ַ���ʼ��
		///	<code>ԭ�ͣ�String(char i);</code>
		///	</summary> 
		///	<param name="c">�ַ�</param> 
		///	<param name="count">���ȸ���</param> 
		String(char c, int count):string(count,c){}
		///	<summary>
		///	��<see cref="String"/>�����ʼ��
		///	<code>ԭ�ͣ�String(String &amp;value, int startIndex);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>����ʵ��</param> 
		///	<param name="startIndex">��ʼλ��</param> 
		String(String &value, int startIndex):string(value.c_str()+startIndex){}
 		///	<summary>
		///	��<see cref="String"/>�����ʼ��
		///	<code>ԭ�ͣ�String(String &amp;value, int startIndex, int length);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>����ʵ��</param> 
		///	<param name="startIndex">value �ڵ���ʼλ�á�</param> 
		///	<param name="length">Ҫʹ���ַ������ȡ�</param> 
		String(String &value, int startIndex, int length):string(value.c_str()+startIndex,length){}
 		///	<summary>
		///	���ַ���ָ���ʼ��
		///	<code>ԭ�ͣ�String(const char * value,int startIndex);</code>
		///	</summary> 
		///	<param name="value">�ַ���ָ��</param> 
		///	<param name="startIndex">value �ڵ���ʼλ�á�</param>  
		String(const char * value,int startIndex):string(value+startIndex){}
 		///	<summary>
		///	���ַ���ָ���ʼ��
		///	<code>ԭ�ͣ�String(const char * value,int startIndex, int length);</code>
		///	</summary> 
		///	<param name="value"><see cref="String"/>����ʵ��</param> 
		///	<param name="startIndex">value �ڵ���ʼλ�á�</param> 
		///	<param name="length">Ҫʹ���ַ������ȡ�</param> 
		String(const char * value,int startIndex, int length):string(value+startIndex,length){}
 		///	<summary>
		///	�±������
		///	<code>ԭ�ͣ�inline char &amp;operator[](int index);</code>
		///	</summary> 
		///	<param name="index">�ַ�����λ��</param> 
		///	<returns>��Ӧλ���ַ�����</returns>
		inline char &operator[](int index){return at(index);};
 
 		///	<summary>
		///	�Ƚ�����ָ���� <see cref="String"/> ����
		///	<code>ԭ�ͣ�inline static int Compare(String &amp;strA, String &amp;strB);</code>
		///	</summary> 
		///	<param name="strA">��һ��<see cref="String"/>����</param> 
		///	<param name="strB">�ڶ���<see cref="String"/>����</param>
		///	<returns>һ�� 32 λ�з���������ָʾ�����Ƚ���֮��Ĵʷ���ϵ��ֵ ���� С���� strA С�� strB�� �� strA ���� strB�� ������ strA ���� strB��</returns>
		inline static int Compare(String &strA, String &strB){return String::strcmp(strA.c_str(),strB.c_str());};
 		///	<summary>
		///	�Ƚ�����ָ���� <see cref="String"/> ����,���Ի������ǵĴ�Сд��
		///	<code>ԭ�ͣ�inline static int Compare(String &amp;strA, String &amp;strB, bool ignoreCase);</code>
		///	</summary> 
		///	<param name="strA">��һ��<see cref="String"/>����</param> 
		///	<param name="strB">�ڶ���<see cref="String"/>����</param>
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns>һ�� 32 λ�з���������ָʾ�����Ƚ���֮��Ĵʷ���ϵ��ֵ ���� С���� strA С�� strB�� �� strA ���� strB�� ������ strA ���� strB��</returns>
        inline static int Compare(String &strA, String &strB, bool ignoreCase){return String::strcmp(strA.c_str(),strB.c_str(),ignoreCase);};
    	///	<summary>
		///	�Ƚ�����ָ���� <see cref="String"/> ����,���Ի������ǵĴ�Сд��
		///	<code>ԭ�ͣ�inline static int Compare(String &amp;strA, int indexA, String &amp;strB,int indexB, int length);</code>
		///	</summary> 
		///	<param name="strA">��һ��<see cref="String"/>����</param> 
		///	<param name="indexA"> strA �����ַ�����λ�á�</param> 
		///	<param name="strB">�ڶ���<see cref="String"/>����</param>
		///	<param name="indexB"> strB �����ַ�����λ�á�</param> 
		///	<param name="length">Ҫ�Ƚϵ��ַ����ȡ�</param> 
		///	<returns>һ�� 32 λ�з���������ָʾ�����Ƚ���֮��Ĵʷ���ϵ��ֵ���� С���� strA �е����ַ���С�� strB �е����ַ����� �� ���ַ�����ȣ�����
        ///     length Ϊ�㡣 ������ strA �е����ַ������� strB �е����ַ�����</returns>
        inline static int Compare(String &strA, int indexA, String &strB, int indexB, int length){return String::strcmp(strA.c_str(),indexA,strB.c_str(),indexB,length);};
  		///	<summary>
		///	�Ƚ�����ָ���� <see cref="String"/> ����,���Ի������ǵĴ�Сд��
		///	<code>ԭ�ͣ�inline static int Compare(String &amp;strA, int indexA, String &amp;strB,
		///                                       int indexB,  int length, bool ignoreCase);</code>
		///	</summary> 
		///	<param name="strA">��һ��<see cref="String"/>����</param> 
		///	<param name="indexA"> strA �����ַ�����λ�á�</param> 
		///	<param name="strB">�ڶ���<see cref="String"/>����</param>
		///	<param name="indexB"> strB �����ַ�����λ�á�</param> 
		///	<param name="length">Ҫ�Ƚϵ��ַ����ȡ�</param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns>һ�� 32 λ�з���������ָʾ�����Ƚ���֮��Ĵʷ���ϵ��ֵ���� С���� strA �е����ַ���С�� strB �е����ַ����� �� ���ַ�����ȣ�����
        ///     length Ϊ�㡣 ������ strA �е����ַ������� strB �е����ַ�����</returns>
       inline static int Compare(String &strA, int indexA, String &strB, int indexB, int length, bool ignoreCase){return String::strcmp(strA.c_str(),indexA,strB.c_str(),indexB,length,ignoreCase);};
   		///	<summary>
		///	����ʵ����ָ����  <see cref="String"/> ������бȽϡ� 
		///	<code>ԭ�ͣ�inline int Compare(String &amp;strB );</code>
		///	</summary>  
		///	<param name="strB">�ڶ���<see cref="String"/>����</param> 
		///	<returns> һ�� 32 λ�з���������ָʾ�����Ƚ���֮��Ĵʷ���ϵ��ֵ ���� С���� ��ʵ��С�� strB�� �� ��ʵ������ strB�� ������ ��ʵ������
        ///     strB��- �� - strB Ϊnull��</returns>
        inline int CompareTo(String &strB){return String::strcmp(c_str(),strB.c_str());};
    	///	<summary>
		///	����һ��ֵ����ֵָʾָ���� <see cref="String"/>�����Ƿ�����ڴ��ַ����С�
		///	<code>ԭ�ͣ�inline int Contains(String &amp;value );</code>
		///	</summary>  
		///	<param name="value">Ҫ���ҵ� <see cref="String"/>����</param> 
		///	<returns> ��� value ���������ڴ��ַ����У����� value Ϊ���ַ��� ("")����Ϊ true������Ϊ false��</returns>
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
		///	�����ַ����ַ���ָ����.
		///	<code>ԭ�ͣ�inline void CopyTo(int sourceIndex, char * destination, int destinationIndex, int count);</code>
		///	</summary>  
		///	<param name="sourceIndex">��ǰʵ���������ַ���ʼλ�á�</param> 
		///	<param name="destination">Ŀ���ַ�ָ�롣</param> 
		///	<param name="destinationIndex">destination �еĿ�ʼλ�á�</param> 
		///	<param name="count">��ʵ����Ҫ���Ƶ� destination ���ַ�����</param> 
		inline void CopyTo(int sourceIndex, char * destination, int destinationIndex, int count)
		{
			String::strcpy(destination,destinationIndex,c_str(),sourceIndex,count);
		}
    	///	<summary>
		///	ȷ����ʵ���Ƿ�����һ��ָ���� <see cref="String"/> ���������ͬ��ֵ.
		///	<code>ԭ�ͣ�inline bool Equals(String &amp;value);</code>
		///	</summary>  
		///	<param name="value">Ҫ�ȶԵ�<see cref="String"/>����</param>  
		///	<returns>��� value ������ֵ���ʵ����ͬ����Ϊ true������Ϊ false��</returns>
		inline bool Equals(String &value)
		{
			 int result=String::strcmp(c_str(),value.c_str());
			 if(result==0)
				 return true;
			 else 
				 return false;
		} 
     	///	<summary>
		///	ȷ������ָ����<see cref="String"/>�����Ƿ����ͬһֵ������ָ�������ԡ���Сд�Լ��Ƚ����õ��������
		///	<code>ԭ�ͣ�inline static bool Equals(String &amp;a, String &amp;b, bool ignoreCase=false)</code>
		///	</summary>  
		///	<param name="a">Ҫ�ȶԵ�<see cref="String"/>����</param>  
		///	<param name="b">Ҫ�ȶԵ�<see cref="String"/>����</param>  
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>
		///	<returns>��� value ������ֵ���ʵ����ͬ����Ϊ true������Ϊ false��</returns>
        inline static bool Equals(String &a, String &b, bool ignoreCase=false){return String::strcmp(a.c_str(),b.c_str(),ignoreCase)==0;};
		inline static bool Equals(string &a, string b, bool ignoreCase=false){return String::strcmp(a.c_str(),b.c_str(),ignoreCase)==0;};
     	///	<summary>
		///	��ָ����<see cref="String"/>�еĸ�ʽ���滻Ϊָ����<see cref="String"/>ʵ����ֵ���ı���Ч�
		///	<code>ԭ�ͣ�inline static String Format(String format, String arg0);</code>
		///	</summary>  
		///	<param name="format">��ʽ����format<see cref="String"/>���󣬰�����{0}�����ռλ����</param>  
		///	<param name="arg0">Ҫ��ʽ����<see cref="String"/>����</param>   
		///	<returns>format ��һ�����������еĵ�һ����ʽ��{0}���滻Ϊ arg0 ��<see cref="String"/>��Ч�</returns>
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
		///	��ָ����<see cref="String"/>�еĸ�ʽ���滻Ϊָ����<see cref="String"/>ʵ����ֵ���ı���Ч�
		///	<code>ԭ�ͣ�inline static String Format(String format, Array&lt;String> &amp;args);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>���������������ʽ�</param>  
		///	<param name="args">�����������Ҫ��ʽ���Ķ����<see cref="String"/>���顣</param>   
		///	<returns>format ��һ�����������и�ʽ�����滻Ϊ args ����Ӧ <see cref="String"/> ʵ���� <see cref="String"/> ��Ч�</returns>
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
		///	��ָ����<see cref="String"/>�еĸ�ʽ���滻Ϊָ����<see cref="String"/>ʵ����ֵ���ı���Ч�
		///	<code>ԭ�ͣ�inline static String Format(String format, String arg0, String arg1);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>���������������ʽ�</param>  
		///	<param name="arg0">��һ��Ҫ��ʽ����<see cref="String"/>��</param>   
		///	<param name="arg1">�ڶ���Ҫ��ʽ����<see cref="String"/>��</param>   
		///	<returns>format ��һ�����������и�ʽ�����滻Ϊ arg0 ,arg1����Ӧ <see cref="String"/> ʵ���� <see cref="String"/> ��Ч�</returns>
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
		///	��ָ���� <see cref="String"/> �еĸ�ʽ���滻Ϊ����ָ���� <see cref="String"/> ��
		///	<code>ԭ�ͣ�inline static String Format(String format, String arg0, String arg1, String arg2);</code>
		///	</summary>  
		///	<param name="format"><see cref="String"/>���������������ʽ�</param>  
		///	<param name="arg0">��һ��Ҫ��ʽ����<see cref="String"/>��</param>   
		///	<param name="arg1">�ڶ���Ҫ��ʽ����<see cref="String"/>��</param>   
		///	<param name="arg1">������Ҫ��ʽ����<see cref="String"/>��</param>   
		///	<returns>format ��һ�����������и�ʽ�����滻Ϊ arg0 ,arg1 ,arg2����Ӧ <see cref="String"/> ʵ���� <see cref="String"/> ��Ч�</returns>
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
		///	����ָ���ַ��ڴ��ַ����еĵ�һ��ƥ�����������
		///	<code>ԭ�ͣ�inline int IndexOf(char value, int startIndex,bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">Ҫ���ҵ��ַ� ��</param>   
		///	<param name="startIndex">������ʼλ�á�</param>   
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>   
		///	<param name="count">���ҳ��ȣ����Ҷ����ַ���ֹͣ���ҡ�</param>   
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
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
		///	����ָ���ַ��ڴ��ַ����еĵ�һ��ƥ�������������������ָ���ַ�λ�ÿ�ʼ
		///	<code>ԭ�ͣ�inline int IndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">Ҫ���ҵ��ַ� ��</param>     
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>    
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
		inline int IndexOf(char value, bool ignoreCase=0)
		{
			return IndexOf(value,0,ignoreCase);
		}
       	///	<summary>
		///	����ָ���� <see cref="String"/> �ڴ�ʵ���еĵ�һ��ƥ�����������
		///	<code>ԭ�ͣ�inline int IndexOf(String value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">Ҫ���ҵ��ַ���<see cref="String"/>  ��</param>     
		///	<param name="startIndex">������ʼλ�á�</param>   
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>   
		///	<param name="count">���ҳ��ȣ����Ҷ����ַ���ֹͣ���ҡ�</param>   
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
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
		///	����ָ���� <see cref="String"/> �ڴ�ʵ���еĵ�һ��ƥ�������������������ָ���ַ�λ�ÿ�ʼ
		///	<code>ԭ�ͣ�inline int IndexOf(String value,  bool ignoreCase );</code>
		///	</summary>  
		///	<param name="value">Ҫ���ҵ��ַ���<see cref="String"/>  ��</param>   
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>    
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
		inline int IndexOf(String value, bool ignoreCase=false)
		{
			return IndexOf(value,0,ignoreCase);
		}
       	///	<summary>
		///	����ָ���ַ������е������ַ��ڴ�ʵ���е�һ��ƥ�����������������ָ���ַ�λ�ÿ�ʼ�������ָ���������ַ�λ�á�
		///	<code>ԭ�ͣ�inline int IndexOfAny(String anyOf, int startIndex=0, int count=0);</code>
		///	</summary>  
		///	<param name="anyOf">Ҫ���ҵ��ַ����飬����һ������Ҫ���ҵ��ַ���<see cref="String"/>  ��</param>   
		///	<param name="startIndex">�Ƿ���Դ�Сд��</param>    
		///	<param name="count">Ҫ�����ַ�λ������</param>    
		///	<returns>��ʵ���е�һ��ƥ���������λ�ã��ڴ˴��ҵ� anyOf �е������ַ����������δ�ҵ� anyOf �е��ַ�����Ϊ -1��</returns>
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
		///	��ָ�� <see cref="String"/>  �����ÿ��Ԫ��֮�䴮��ָ���ķָ��� <see cref="String"/> ��
		///     �Ӷ����������������ַ���������ָ��Ҫʹ�õĵ�һ������Ԫ�غ�Ԫ������
		///	<code>ԭ�ͣ�inline static String Join(Array&lt;String> &amp;value,String separator=",",
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="String"/> ���顣</param>   
		///	<param name="separator">�ָ����ַ��� <see cref="String"/>  ��</param>   
		///	<param name="startIndex">Ҫʹ�õ� value �еĵ�һ������Ԫ�ء�</param>    
		///	<param name="count">Ҫʹ�õ� value ��Ԫ������</param>    
		///	<returns><see cref="String"/> ������ͨ�� separator ���ӵ� value �е��ַ�����ɡ���� count Ϊ�㡢value û��Ԫ�ػ���
		///     separator �� value ��ȫ��Ԫ��Ϊ Common.String.Empty����Ϊ Common.String.Empty��</returns>
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
		///	��ָ�� <see cref="string"/>  �����ÿ��Ԫ��֮�䴮��ָ���ķָ��� <see cref="string"/> ��
		///     �Ӷ����������������ַ���������ָ��Ҫʹ�õĵ�һ������Ԫ�غ�Ԫ������
		///	<code>ԭ�ͣ�inline static string Join(Array&lt;string> &amp;value,string separator=",", 
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="string"/> ���顣 </param>   
		///	<param name="separator">�ָ����ַ��� <see cref="string"/>  ��</param>   
		///	<param name="startIndex">Ҫʹ�õ� value �еĵ�һ������Ԫ�ء�</param>    
		///	<param name="count">Ҫʹ�õ� value ��Ԫ������</param>    
		///	<returns><see cref="string"/> ������ͨ�� separator ���ӵ� value �е��ַ�����ɡ���� count Ϊ�㡢value û��Ԫ�ػ���
		///     separator �� value ��ȫ��Ԫ��Ϊ Common.String.Empty����Ϊ Common.String.Empty��</returns>
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
		///	��ָ�� <see cref="char"/>  �����ÿ��Ԫ��֮�䴮��ָ���ķָ��� <see cref="String"/> ��
		///     �Ӷ����������������ַ���������ָ��Ҫʹ�õĵ�һ������Ԫ�غ�Ԫ������
		///	<code>ԭ�ͣ�inline static String Join(Array&lt;char> &amp;value,String separator=",",
		///                                       int startIndex=0, int count=0x7fffffff);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="char"/> ���顣 </param>   
		///	<param name="separator">�ָ����ַ��� <see cref="String"/>  ��</param>   
		///	<param name="startIndex">Ҫʹ�õ� value �еĵ�һ������Ԫ�ء�</param>    
		///	<param name="count">Ҫʹ�õ� value ��Ԫ������</param>    
		///	<returns><see cref="String"/> ������ͨ�� separator ���ӵ� value �е��ַ�����ɡ���� count Ϊ�㡢value û��Ԫ�ػ���
		///     separator �� value ��ȫ��Ԫ��Ϊ Common.String.Empty����Ϊ Common.String.Empty��</returns>
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
		///	����ָ���ַ��ڴ�ʵ���е����һ��ƥ���������λ�á�
		///	<code>ԭ�ͣ�inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="char"/> �� </param>       
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>    
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
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
		///	����ָ���ַ��ڴ�ʵ���е����һ��ƥ���������λ�á�
		///	<code>ԭ�ͣ�inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="char"/> �� </param>       
		///	<param name="startIndex">��ʼλ�ã��������ʱ�Ľ�ֹλ�á�</param>    
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>    
		///	<param name="count">�����ַ�����</param>    
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
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
		///	����ָ��<see cref="String"/>�ڴ�ʵ���е����һ��ƥ���������λ�á�
		///	<code>ԭ�ͣ�inline int LastIndexOf(char value, bool ignoreCase=0);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="char"/> �� </param>        
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>     
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
        inline int LastIndexOf(String value, bool ignoreCase=0)
		{
			return LastIndexOf(value,0,ignoreCase);
		}
     	///	<summary>
		///	����ָ��<see cref="String"/>�ڴ�ʵ���е����һ��ƥ���������λ�á�
		///	����ָ����ǰ�ַ����е���ʼ����λ�á�Ҫ�����ĵ�ǰ�ַ����е��ַ��������Լ��Ƿ���Դ�Сд��
		///	<code>ԭ�ͣ�inline int LastIndexOf(String value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary>  
		///	<param name="value">һ�� <see cref="char"/> �� </param>        
		///	<param name="startIndex">������ʼλ�ã��������ʱ�Ľ�ֹλ�á�</param>    
		///	<param name="ignoreCase">�Ƿ���Դ�Сд��</param>    
		///	<param name="count">Ҫ�����ַ�λ������</param>    
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>
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
		///	�������ַ�������ָ����һ�������ַ��ڴ�ʵ���е����һ��ƥ���������λ�á�������ָ���ַ�λ�ÿ�ʼ�������ָ���������ַ�λ�á�
		///	<code>ԭ�ͣ�inline int LastIndexOfAny(String anyOf, int startIndex=0, int count=0);</code>
		///	</summary>  
		///	<param name="anyOf">һ��<see cref="String"/>��ʾ��<see cref="char"/>���顣 </param>        
		///	<param name="startIndex">������ʼλ�ã��������ʱ�Ľ�ֹλ�á�</param>    
		///	<param name="count">Ҫ�����ַ�λ������</param>    
		///	<returns>��ʵ�������һ��ƥ���������λ�ã��ڴ�λ���ҵ� anyOf �е������ַ����������δ�ҵ� anyOf �е��ַ�����Ϊ -1��</returns>
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
		///	�Ҷ����ʵ���е��ַ����������ָ�����ַ�����Դﵽָ�����ܳ��ȡ�
		///	<code>ԭ�ͣ�inline String &amp;PadLeft(int totalWidth, char paddingChar=' ');</code>
		///	</summary>  
		///	<param name="totalWidth">����ַ����е��ַ���������ԭʼ�ַ��������κ���������ַ��� </param>        
		///	<param name="paddingChar">����ַ���</param>       
		///	<returns>��ʵ�������������Ҷ���ģ���������ôﵽ totalWidth ����������Ŀ�� paddingChar �ַ�������䡣���
        ///     totalWidth С�ڴ�ʵ���ĳ��ȣ����޸ġ�</returns>
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
		///	�������ַ����е��ַ������ұ���ָ�����ַ�����Դﵽָ�����ܳ��ȡ�
		///	<code>ԭ�ͣ�inline String &amp;PadRight(int totalWidth, char paddingChar=' ');</code>
		///	</summary>  
		///	<param name="totalWidth">����ַ����е��ַ���������ԭʼ�ַ��������κ���������ַ��� </param>        
		///	<param name="paddingChar">����ַ���</param>       
		///	<returns>��ʵ�����������������ģ������ұ��ôﵽ totalWidth ����������Ŀ�� paddingChar �ַ�������䡣���
        ///     totalWidth С�ڴ�ʵ���ĳ��ȣ����޸ġ�</returns>
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
		///	ɾ�����ַ����д�ָ��λ�õ����λ�õ������ַ�
		///	<code>ԭ�ͣ�inline String &amp;Remove(int startIndex);</code>
		///	</summary>  
		///	<param name="startIndex">��ʼɾ���ַ���λ�á� </param>        
		///	<param name="paddingChar">����ַ���</param>       
		///	<returns>��ʵ�����������ڴ��ַ����޳���ɾ���ַ�����ַ�����</returns>
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
		///	�Ӵ�ʵ���е�ָ��λ�ÿ�ʼɾ��ָ����Ŀ���ַ�
		///	<code>ԭ�ͣ�inline String &amp;Remove(int startIndex, int count);</code>
		///	</summary>  
		///	<param name="startIndex">��ʼɾ���ַ���λ�á� </param>        
		///	<param name="paddingChar">����ַ���</param>       
		///	<returns>��ʵ�����������ڴ��ַ����޳���ɾ��ָ����Ŀ���ַ�����ַ�����</returns>
        inline String &Remove(int startIndex, int count)
		{
			erase(startIndex,count);
			return *this;
		};
        ///	<summary>
		///	����ʵ���е�ָ���ַ�������ƥ�����滻Ϊ����ָ�����ַ���
		///	<code>ԭ�ͣ�inline String ReplaceAll(char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary>  
		///	<param name="oldChar">Ҫ�滻���ַ���</param>       
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ��������ַ��� </param>        
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param>        
		///	<returns>���� oldChar ������ʵ�����滻Ϊ newChar ����µ� <see cref="String"/>��</returns>
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
		///	����ʵ���е�ָ���ַ��ĵ�һ��ƥ�����滻Ϊ����ָ�����ַ���
		///	<code>ԭ�ͣ�inline String Replace(char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary>  
		///	<param name="oldChar">Ҫ�滻���ַ���</param>       
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ��������ַ��� </param>        
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param>        
		///	<returns>�� oldChar �ĵ�һ��ʵ���滻Ϊ newChar ����µ� <see cref="String"/>��</returns>
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
		///	����ʵ���е�ָ�� <see cref="String"/> ������ƥ�����滻Ϊ����ָ���� <see cref="String"/>��
		///	<code>ԭ�ͣ�inline String ReplaceAll(const String&amp; oldValue, const String&amp; newValue,bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="oldValue">Ҫ�滻��<see cref="String"/>��</param>       
		///	<param name="newValue">Ҫ�滻 oldValue ������ƥ�����<see cref="String"/>�� </param>        
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param>        
		///	<returns>��Ч�ڴ�ʵ�������� oldValue ������ʵ�����滻Ϊ newValue �� <see cref="String"/>��</returns>
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
		///	����ʵ���е�ָ�� <see cref="String"/> �ĵ�һ��ƥ�����滻Ϊ����ָ���� <see cref="String"/>��
		///	<code>ԭ�ͣ�inline String Replace(const String&amp; oldValue, const String&amp; newValue,bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="oldValue">Ҫ�滻��<see cref="String"/>��</param>       
		///	<param name="newValue">Ҫ�滻 oldValue ������ƥ�����<see cref="String"/>�� </param>        
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param>        
		///	<returns>��Ч�ڴ�ʵ�������� oldValue �ĵ�һ��ʵ���滻Ϊ newValue ���µ� <see cref="String"/>��</returns>
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
		///	ȷ�����ַ����Ŀ�ͷ�Ƿ���ָ�����ַ���ƥ�䡣
		///	<code>ԭ�ͣ�inline bool StartsWith(String value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">Ҫ�Ƚϵ�<see cref="String"/>����</param>           
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false�� </param>        
		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>
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
		///	ȷ�����ַ����Ŀ�ͷ�Ƿ���ָ�����ַ�ƥ�䡣
		///	<code>ԭ�ͣ�inline bool StartsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">Ҫ�Ƚϵ�<see cref="char"/>��</param>           
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false�� </param>        
		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>
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
		///	ȷ�����ַ�����ĩβ�Ƿ���ָ�����ַ���ƥ�䡣
		///	<code>ԭ�ͣ�inline bool EndsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">Ҫ�Ƚϵ�<see cref="String"/>��</param>           
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false�� </param>        
		///	<returns> ������ַ�����ĩβ�� value ����ƥ�䣬��Ϊ true������Ϊ false��</returns>
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
		///	ȷ�����ַ�����ĩβ�Ƿ���ָ�����ַ�ƥ�䡣
		///	<code>ԭ�ͣ�inline bool EndsWith(char value, bool ignoreCase=false);</code>
		///	</summary>
		///	<param name="value">Ҫ�Ƚϵ�<see cref="char"/>��</param>           
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false�� </param>        
		///	<returns> ������ַ�����ĩβ�� value ����ƥ�䣬��Ϊ true������Ϊ false��</returns>
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
		///	�Ӵ�ʵ���������ַ��������ַ�����ָ�����ַ�λ�ÿ�ʼ��
		///	<code>ԭ�ͣ�inline String SubString(int startIndex);</code>
		///	</summary>
		///	<param name="startIndex">��ʵ�������ַ�������ʼ�ַ�λ��<see cref="int"/></param>
		///	<returns>��ȡ�����ַ���һ�� <see cref="String"/>���������ڴ�ʵ���д� startIndex ��ʼ�����ַ�������� startIndex ���ڴ�ʵ���ĳ��ȣ���Ϊ
        ///     Common.String.Empty��</returns>
        inline String SubString(int startIndex)
		{
			if(startIndex>=size())return "";
			return String(*this,startIndex);
		}
		///	<summary>
		///	�Ӵ�ʵ���������ַ��������ַ�����ָ�����ַ�λ�ÿ�ʼ�Ҿ���ָ���ĳ��ȡ�
		///	<code>ԭ�ͣ�inline String SubString(int startIndex, int length);</code>
		///	</summary>
		///	<param name="startIndex">���ַ�������ʼλ�õ�����<see cref="int"/></param>
		///	<param name="length">���ַ����е��ַ���<see cref="int"/></param>
		///	<returns>һ�� <see cref="String"/>�������ڴ�ʵ���д� startIndex ��ʼ�ĳ���Ϊ length �����ַ�������� startIndex ���ڴ�ʵ���ĳ�����
        ///     length Ϊ�㣬��Ϊ Common.String.Empty�� </returns>
        inline String SubString(int startIndex, int length)
		{
			if(startIndex>=size() || length<0)return "";
			return String(*this,startIndex,length);
		}
		///	<summary>
		///	���ش� <see cref="String"/> ��ת��ΪСд��ʽ�ĸ���
		///	<code>ԭ�ͣ�inline String &amp;ToLower();</code>
		///	</summary>
		///	<returns>��ʵ������ </returns>
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
		///	���ش� <see cref="String"/> ��ת��Ϊ��д��ʽ�ĸ���
		///	<code>ԭ�ͣ�inline String &amp;ToUpper();</code>
		///	</summary>
		///	<returns>��ʵ������ </returns>
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
		///	�Ӵ�ʵ���Ŀ�ʼλ�ú�ĩβ�Ƴ��հ��ַ�(�����Ʊ��)������ƥ����
		///	<code>ԭ�ͣ�inline String &amp;Trim();</code>
		///	</summary>
		///	<returns>��ʵ������ </returns>
		inline String &Trim(){return Trim(' ');};
		///	<summary>
		///	�Ӵ�ʵ���Ŀ�ʼλ�ú�ĩβ�Ƴ�ָ���ַ�������ƥ����,����ո����Ʊ����Ч
		///	<code>ԭ�ͣ�inline String &amp;Trim(char c);</code>
		///	</summary>
		///	<param name="c">Ҫ���Ƴ����ַ� </param> 
		///	<returns>��ʵ������ </returns>
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
		///	�Ӵ�ʵ����ĩβ�Ƴ�ָ���ַ�������ƥ����,����ո����Ʊ����Ч
		///	<code>ԭ�ͣ�inline String &amp;TrimEnd(char c);</code>
		///	</summary>
		///	<param name="c">Ҫ���Ƴ����ַ� </param> 
		///	<returns>��ʵ������ </returns>
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
		///	�Ӵ�ʵ���Ŀ�ʼλ���Ƴ�ָ���ַ�������ƥ����,����ո����Ʊ����Ч
		///	<code>ԭ�ͣ�inline String &amp;TrimStart(char c);</code>
		///	</summary>
		///	<param name="c">Ҫ���Ƴ����ַ� </param> 
		///	<returns>��ʵ������ </returns>
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
		///	�Ӵ�ʵ���Ŀ�ʼ��ĩβ�Ƴ�������ָ����һ���ַ�������ƥ����
		///	<code>ԭ�ͣ�inline String &amp;Trim(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">Ҫ�Ƴ����ַ����� </param> 
		///	<returns>��ʵ������,�Ӵ�ʵ���Ŀ�ʼ�ͽ�β�Ƴ� trimChars ���ַ�������ƥ�����ʣ��� Common.String����� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ��� </returns>
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
		///	�Ӵ�ʵ���Ľ�β�Ƴ�������ָ����һ���ַ�������ƥ����
		///	<code>ԭ�ͣ�inline String &amp;TrimEnd(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">Ҫ�Ƴ����ַ����� </param> 
		///	<returns>��ʵ������,�Ӵ�ʵ���Ľ�β�Ƴ� trimChars ���ַ�������ƥ�����ʣ��� Common.String����� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ��� </returns>
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
		///	�Ӵ�ʵ���Ŀ�ʼλ���Ƴ�������ָ����һ���ַ�������ƥ����
		///	<code>ԭ�ͣ�inline String &amp;TrimStart(char *trimChars);</code>
		///	</summary>
		///	<param name="trimChars">Ҫ�Ƴ����ַ����� </param> 
		///	<returns>��ʵ������,�Ӵ�ʵ���Ŀ�ʼλ���Ƴ� trimChars ���ַ�������ƥ�����ʣ��� Common.String����� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ��� </returns>
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
		///	��ȡ���ַ�������ļ�hashֵ
		///	<code>ԭ�ͣ�inline unsigned int hashCode();</code>
		///	</summary> 
		///	<returns>һ���޷��������� </returns>
		inline unsigned int hashCode(){return hashMath::hashsp(c_str(),size());};
 		///	<summary>
		///	��ȡ���ַ�������ļ�hashֵ
		///	<code>ԭ�ͣ�inline static unsigned int getHashCode(const string &amp; s);</code>
		///	</summary> 
		///	<param name="s">Ҫ����hashֵ���ַ��� </param> 
		///	<returns>һ���޷��������� </returns>
		inline static unsigned int getHashCode(const string & s){return hashMath::hashsp(s);};
 		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='String'/> ���顣
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,char separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �е�һ�������ַ��ָ�</param> 
		///	<param name="separator">����ַ�</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		void Split(Array<String>  &result,char separator,StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='String'/> ���顣
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,Array&lt;char> separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separators �е�һ�������ַ��ָ�</param> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
        void Split(Array<String>  &result,Array<char> & separators, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ�����ַ�����Ԫ�ػ��ַ����ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,String separator,bool isString,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separatorָ�����ַ��������ַ��ָ�</param> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="isString">ָʾseparator���ַ��������ַ����飬Ϊ��ʱ���ַ�����֣�Ϊ��ʱ���ַ����е���һ�ַ����</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
        void Split(Array<String>  &result,String separator,bool isString, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='String'/>�ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,String separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �ָ�</param> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		void Split(Array<String>  &result,String separator,StringSplitOptions options=None, int count=0)
		{
			Split(result,separator,true, options,count);
		};
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='String'/>����ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,Array&lt;String>  &amp; separators,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separators �е�һ�������ַ����ָ�</param> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
	    void Split(Array<String>  &result,Array<String> &separators, StringSplitOptions options=None, int count=0);
 		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='String'/> ���顣
		///	<code>ԭ�ͣ�inline Array&lt;String> Split(char separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">����ַ�</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		///	<returns><see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �е�һ�������ַ����ָ�</returns>
		inline Array<String> Split(char separator,StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,options, count);
			return result;
		};
   		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='String'/> ���顣
		///	<code>ԭ�ͣ�inline Array&lt;String> Split(Array&lt;char> separator,
		///                                            StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		///	<returns><see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �е�һ�������ַ����ָ�</returns>
		inline Array<String> Split(Array<char> & separators, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separators,options, count);
			return result;
		};
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ�����ַ�����Ԫ�ػ��ַ����ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�inline Array&lt;String>  Split(String separator,bool isString,
		///                                            StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="isString">ָʾseparator���ַ��������ַ����飬Ϊ��ʱ���ַ�����֣�Ϊ��ʱ���ַ����е���һ�ַ����</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		///	<returns><see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator ָ�����ַ��������ַ��ָ�</returns>
		inline Array<String> Split(String separator,bool isString, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,isString,options, count);
			return result;
		};
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='String'/>�ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�inline Array&lt;String> Split(String separator,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		///	<returns><see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �ָ�</returns>
		inline Array<String> Split(String separator,StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separator,true,options, count);
			return result;
		};
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='String'/>����ָ�����<see cref='String'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�void Split(Array&lt;String>  &amp;result,Array&lt;String>  &amp; separator,
		///                        StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		///	<returns><see cref='String'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separators �е�һ�������ַ����ָ�</returns>
		inline Array<String> Split(Array<String> &separators, StringSplitOptions options=None, int count=0)
		{
			Array<String>  result;
			Split(result,separators,options, count);
			return result;
		};


//for base class string//
 		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='string'/> ���顣
		///	<code>ԭ�ͣ�static void Split(Array&lt;string>  &amp;result,string str,char separator,
		///                                StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='string'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �е�һ�������ַ��ָ�</param> 
		///	<param name="str">Ҫ���в�ֵ�Դ�ַ���,<see cref='String'/>�ĸ���<see cref='string'/></param> 
		///	<param name="separator">����ַ�</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		static void Split(Array<string>  &result,string str,char separator,StringSplitOptions options=None,int count=0);
   		///	<summary>
		///	�ַ����,���ذ�����ʵ���е����ַ����� <see cref='string'/> ���顣
		///	<code>ԭ�ͣ�static void Split(Array&lt;string>  &amp;result,string str,Array&lt;char> separator,
		///                               StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='string'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separators �е�һ�������ַ��ָ�</param> 
		///	<param name="str">Ҫ���в�ֵ�Դ�ַ���,<see cref='String'/>�ĸ���<see cref='string'/></param> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		static void Split(Array<string>  &result,string str,Array<char> & separator, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ�����ַ�����Ԫ�ػ��ַ����ָ�����<see cref='string'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�static void Split(Array&lt;string>  &amp;result,string separator,
		///                               bool isString,StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='string'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separatorָ�����ַ��������ַ��ָ�</param> 
		///	<param name="str">Ҫ���в�ֵ�Դ�ַ���,<see cref='String'/>�ĸ���<see cref='string'/></param> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="isString">ָʾseparator���ַ��������ַ����飬Ϊ��ʱ���ַ�����֣�Ϊ��ʱ���ַ����е���һ�ַ����</param> 
		///	<param name="options">ָ��<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		static void Split(Array<string>  &result,string str,string separator,bool isString, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='string'/>�ָ�����<see cref='string'/>���顣
		///	<code>ԭ�ͣ�inline static void Split(Array&lt;string>  &amp;result,string str,string separator);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='string'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separator �ָ�</param> 
		///	<param name="str">Ҫ���в�ֵ�Դ�ַ���,<see cref='String'/>�ĸ���<see cref='string'/></param> 
		///	<param name="separator">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		inline static void Split(Array<string>  &result,string str,string separator){Split(result,str,separator,true);};
   		///	<summary>
		///	�ַ������,���ذ������ַ����е����ַ�������ָ���� <see cref='string'/>����ָ�����<see cref='string'/>���顣����ָ���Ƿ񷵻ؿ�����Ԫ�ء�
		///	<code>ԭ�ͣ�static void Split(Array&lt;string>  &amp;result,string str,Array&lt;string>  &amp; separators,
		///                               StringSplitOptions options=None, int count=0);</code>
		///	</summary> 
		///	<param name="result">Ҫ������ֵ��<see cref='string'/> ����,��Ԫ�ذ�����ʵ���е����ַ���,��Щ���ַ����� separators �е�һ�������ַ����ָ�</param> 
		///	<param name="str">Ҫ���в�ֵ�Դ�ַ���,<see cref='String'/>�ĸ���<see cref='string'/></param> 
		///	<param name="separators">�ָ����ַ��������ַ����� ASCII �ַ����顢�������ָ����Ŀ������null</param> 
		///	<param name="options">ָ��<see cref='StringSplitOptions'/>.<see cref='RemoveEmptyEntries'/> ��ʡ�Է��ص������еĿ�����Ԫ�أ���ָ��<see cref='None'/> �԰������ص������еĿ�����Ԫ�� </param> 
		///	<param name="count">Ҫ���ص����ַ������������ </param>  
		static void Split(Array<string>  &result,string str,Array<string> &separators, StringSplitOptions options=None, int count=0);
   		///	<summary>
		///	�ַ������,���ز�ִ�С
		///	<code>ԭ�ͣ�inline static int SplitCpy(char * dest[],const char * src,char c);</code>
		///	</summary> 
		/// <remarks>���ٲ���ַ���,һ������Ϊ: 90W/s</remarks>
		///	<param name="dest">Ҫ������ֵ���ַ�ָ�����飬��ά�ַ����飬�������ֵ�Ŀ���������ÿ��ά�ȵĴ�СҪ�б�֤</param> 
		///	<param name="str">���Դ�ַ���</param> 
		///	<param name="c">����ַ�</param> 
		///	<returns>��ֵ������С</returns>  
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
		///	�ַ������,���ز�ִ�С
		///	<code>ԭ�ͣ�inline static int Split(char * dest[],const char * src,char c);</code>
		///	</summary> 
		/// <remarks>���ٲ���ַ���,һ������Ϊ: 200W/s
		///	         ע�⣺Դ�ַ����в���ַ�ֵ�Ѿ��޸�Ϊ�ա�</remarks>
		///	<param name="dest">Ҫ������ֵ���ַ�ָ������</param> 
		///	<param name="str">���Դ�ַ���</param> 
		///	<param name="c">����ַ�</param> 
		///	<returns>��ֵ������С��ָʾdestָ����������Чָ�����</returns>  
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
		///	�ַ������,ʹ���ַ���������ַ���,���ز�ִ�С
		///	<code>ԭ�ͣ�inline static int Split(char * dest[],const char * src,const char *spc);</code>
		///	</summary> 
		/// <remarks>���ٲ���ַ���,һ������Ϊ: 100W/s
		///	         ע�⣺Դ�ַ����в���ַ���ʼλ��ֵ�Ѿ��޸�Ϊ�ա�</remarks>
		///	<param name="dest">Ҫ������ֵ���ַ�ָ������</param> 
		///	<param name="str">���Դ�ַ���</param> 
		///	<param name="spc">����ַ���</param> 
		///	<returns>��ֵ������С��ָʾdestָ����������Чָ�����</returns>  
		inline static int Split(char * dest[],const char * src,const char *spc)
		{
			char * tp=(char *)src;
			int spLen=strlen(spc);
			dest[0]=tp;
			int count=1;
			if(spc[0]==0){return count;}
			while(tp=strchr(tp,spc[0]))
			{
				//�ж�tp�Ƿ���spc��ʼ
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
		///	�Ը����ַ��������дת��
		///	<code>ԭ�ͣ�inline static string&amp; ToUpper(string &amp;dest);</code>
		///	</summary> 
		///	<param name="dest">Ҫת�����ַ�������</param> 
		///	<returns>dest����ʾ���ַ�������</returns>  
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
		///	�Ը����ַ�������Сдת��
		///	<code>ԭ�ͣ�inline static string&amp; ToLower(string &amp;dest);</code>
		///	</summary> 
		///	<param name="dest">Ҫת�����ַ�������</param> 
		///	<returns>dest����ʾ���ַ�������</returns>  
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
		///	����ָ���ַ���ָ���ַ����еĵ�һ��ƥ�������������������ָ���ַ�λ�ÿ�ʼ��
		///	<code>ԭ�ͣ�inline static int IndexOf(string str,char value, int startIndex,bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ�</param> 
		///	<param name="startIndex">��ʼ����λ��</param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param> 
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param> 
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
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
		///	����ָ���ַ���ָ���ַ����еĵ�һ��ƥ�����������
		///	<code>ԭ�ͣ�inline static int IndexOf(string str,char value, bool ignoreCase=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ�</param>  
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>  
		///	<returns>����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
		inline static int IndexOf(string str,char value, bool ignoreCase=0)
		{
			return IndexOf(str,value,0,ignoreCase);
		} 
		///	<summary>
		///	����ָ���ַ���ָ���ַ����еĵ�һ��ƥ�������������������ָ���ַ�λ�ÿ�ʼ��
		///	<code>ԭ�ͣ�inline static int IndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ���<see cref="string"/></param>  
		///	<param name="startIndex">��ʼ����λ��</param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>  
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param> 
		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã����δ�ҵ����ַ�����Ϊ -1����� value Ϊ Common.String.Empty���򷵻�ֵΪstartIndex��</returns>  
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
		///	����ָ���ַ���ָ���ַ����еĵ�һ��ƥ�����������
		///	<code>ԭ�ͣ�inline static int IndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ���</param>   
		///	<param name="ignoreCase">�Ƿ���Դ�Сд</param>   
		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã����δ�ҵ����ַ�����Ϊ -1����� value Ϊ Common.String.Empty���򷵻�ֵΪstartIndex��</returns>  
		inline static int IndexOf(string str,string value, bool ignoreCase=false){return IndexOf(str,value,0,ignoreCase);}
		///	<summary>
		///	����ָ���ַ������е������ַ���ָ���ַ���ʵ���е�һ��ƥ�����������������ָ���ַ�λ�ÿ�ʼ,�����ָ���������ַ�λ�á�
		///	<code>ԭ�ͣ�inline static int IndexOfAny(string str,string value, int startIndex, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="anyOf">Ҫ���ҵ��ַ�Ԫ����</param>   
		///	<param name="startIndex">��ʼ����λ��</param> 
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param>  
		///	<returns> ��ʵ���е�һ��ƥ���������λ�ã��ڴ˴��ҵ� anyOf �е������ַ����������δ�ҵ� anyOf �е��ַ�����Ϊ -1��</returns>  
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
		///	����ָ���ַ���ָ���ַ���ʵ�������һ��ƥ�����������������ָ���ַ�λ�ÿ�ʼ��
		///	<code>ԭ�ͣ�inline static int LastIndexOf(string str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ�Ԫ��</param>  
		///	<param name="ignoreCase">Ҫ�ڶԴ�ʵ���� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param>  
		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
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
		///	����ָ���ַ���ָ���ַ���ʵ�������һ��ƥ�����������������ָ���ַ�λ�ÿ�ʼ�������ָ���������ַ�λ�á�
		///	<code>ԭ�ͣ�inline static int LastIndexOf(string str,char value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ�Ԫ��</param>  
		///	<param name="startIndex">��ʵ�������ַ�������ʼλ��</param>  
		///	<param name="ignoreCase">Ҫ�ڶԴ�ʵ���� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param>  
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param>  
		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
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
		///	����ָ���ַ�����ָ���ַ���ʵ�������һ��ƥ�����������
		///	<code>ԭ�ͣ�inline static int LastIndexOf(string str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ���</param> 
		///	<param name="ignoreCase">Ҫ�ڶԴ�ʵ���� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param>  
		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
        inline static int LastIndexOf(string str,string value, bool ignoreCase=false)
		{
			return LastIndexOf(str,value,0,ignoreCase);
		}
  		///	<summary>
		///	����ָ���ַ�����ָ���ַ���ʵ�������һ��ƥ�����������
		///	<code>ԭ�ͣ�inline static int LastIndexOf(string str,string value, int startIndex, bool ignoreCase, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="value">Ҫ���ҵ��ַ���</param> 
		///	<param name="startIndex">��ʵ�������ַ�������ʼλ��</param>  
		///	<param name="ignoreCase">Ҫ�ڶԴ�ʵ���� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param>  
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param>  
 		///	<returns> ����ҵ����ַ�����Ϊ value ������λ�ã��������δ�ҵ�����Ϊ -1��</returns>  
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
		///	����ָ���ַ������е������ַ���ָ���ַ���ʵ�������һ��ƥ�����������
		///	<code>ԭ�ͣ�inline static int LastIndexOfAny(string str,string anyOf, int startIndex=0, int count=0);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param> 
		///	<param name="anyOf">Ҫ���ҵ��ַ���</param> 
		///	<param name="startIndex">��ʵ�������ַ�������ʼλ��</param>
		///	<param name="count">ָ��Ҫ���ҵ��ַ�����,Ϊ0��ָ��</param>  
 		///	<returns> ��ʵ�������һ��ƥ���������λ�ã��ڴ�λ���ҵ� anyOf �е������ַ����������δ�ҵ� anyOf �е��ַ�����Ϊ -1��</returns>  
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
		///	��ָ��ʵ���Ŀ�ʼλ�ú�ĩβ�Ƴ��հ��ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;Trim(string &amp;str);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param>  
 		///	<returns> strʵ����</returns>  
		inline static string &Trim(string &str){return String::Trim(str,' ');};
  		///	<summary>
		///	��ָ��ʵ���Ŀ�ʼλ�ú�ĩβ�Ƴ�ָ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;Trim(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ�������</param>  
		///	<param name="c">�Ƴ��ַ�</param>  
 		///	<returns> strʵ����</returns>  
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
		///	��ָ���ַ�ָ��Ŀ�ʼλ�ú�ĩβ�Ƴ�ָ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static char * Trim(char *str,char c);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param>  
		///	<param name="c">�Ƴ��ַ�</param>  
 		///	<returns> ���ַ���ʼλ��ָ�롣</returns>  
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
		///	��ָ���ַ�ָ��Ŀ�ʼλ�ú�ĩβ�Ƴ��հ��ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static char * Trim(const char * str);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
 		///	<returns> ���ַ���ʼλ��ָ�롣</returns>  
		inline static char * Trim(char * str){return String::Trim((char *)str,' ');};
  		///	<summary>
		///	��ָ���ַ������ĩβ�Ƴ�ָ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;TrimEnd(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="c">�Ƴ��ַ�</param>  
 		///	<returns> strʵ����</returns>  
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
		///	��ָ���ַ�����Ŀ�ʼλ���Ƴ�ָ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;TrimStart(string &amp;str,char c);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="c">�Ƴ��ַ�</param>  
 		///	<returns> strʵ����</returns>  
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
		///	��ָ���ַ�����Ŀ�ʼλ���Ƴ�һ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;Trim(string &amp;str,char *trimChars);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="trimChars">Ҫ�Ƴ���char�ַ�ָ��,��� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ���</param>  
 		///	<returns> strʵ����</returns>  
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
		///	��ָ���ַ�����Ľ�β�Ƴ�һ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;TrimEnd(string &amp;str,char * trimChars);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="trimChars">Ҫ�Ƴ���char�ַ�ָ��,��� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ���</param>  
 		///	<returns> strʵ����</returns>  
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
		///	��ָ���ַ�����Ŀ�ʼλ���Ƴ�һ���ַ�������ƥ���
		///	<code>ԭ�ͣ�inline static string &amp;TrimStart(string &amp;str,char * trimChars);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="trimChars">Ҫ�Ƴ���char�ַ�ָ��,��� trimChars Ϊnull�����Ϊ�Ƴ��հ��ַ���</param>  
 		///	<returns> strʵ����</returns>  
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
		///	ȷ�����ַ����Ŀ�ͷ�Ƿ���ָ�����ַ���ƥ�䡣
		///	<code>ԭ�ͣ�inline static bool StartsWith(const string &amp;str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="value">Ҫ�Ƚϵ�<see cref='string'/>��</param>  
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param> 
 		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>  
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
		///	ȷ�����ַ����Ŀ�ͷ�Ƿ���ָ�����ַ�ƥ�䡣
		///	<code>ԭ�ͣ�inline static bool StartsWith(const string &amp;str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="value">Ҫ�Ƚϵ��ַ���</param>  
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param> 
 		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>  
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
		///	ȷ�����ַ����Ľ�β�Ƿ���ָ�����ַ���ƥ�䡣
		///	<code>ԭ�ͣ�inline static bool EndsWith(const string &amp;str,string value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="value">Ҫ�Ƚϵ��ַ�����</param>  
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param> 
 		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>  
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
		///	ȷ�����ַ����Ľ�β�Ƿ���ָ�����ַ�ƥ�䡣
		///	<code>ԭ�ͣ�inline static bool EndsWith(const string &amp;str,char value, bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="value">Ҫ�Ƚϵ��ַ���</param>  
		///	<param name="ignoreCase">��Ҫ�ڶԴ��ַ����� value ���бȽ�ʱ���Դ�Сд����Ϊ true������Ϊ false��</param> 
 		///	<returns> ��� value ��������ַ����Ŀ�ͷƥ�䣬��Ϊ true������Ϊ false��</returns>  
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
		///	�Ҷ����ʵ���е��ַ����������ָ�����ַ�����Դﵽָ�����ܳ��ȡ�
		///	<code>ԭ�ͣ�inline static string &amp;PadLeft(string &amp;str,int totalWidth, char paddingChar=' ');</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="totalWidth">����ַ����е��ַ���������ԭʼ�ַ��������κ���������ַ��� </param>
		///	<param name="paddingChar">����ַ�</param> 
 		///	<returns> str�������������Ҷ���ģ���������ôﵽ totalWidth ����������Ŀ�� paddingChar �ַ�������䡣���
        ///     totalWidth С�ڴ�ʵ���ĳ��ȣ����޸ġ�</returns>  
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
		///	������ʵ���е��ַ������ұ���ָ�����ַ�����Դﵽָ�����ܳ��ȡ�
		///	<code>ԭ�ͣ�inline static string &amp;PadRight(string &amp;str,int totalWidth, char paddingChar=' ');</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="totalWidth">����ַ����е��ַ���������ԭʼ�ַ��������κ���������ַ��� </param>
		///	<param name="paddingChar">����ַ�</param> 
 		///	<returns> str�����������������ģ������ұ��ôﵽ totalWidth ����������Ŀ�� paddingChar �ַ�������䡣���
        ///     totalWidth С�ڴ�ʵ���ĳ��ȣ����޸ġ�</returns>  
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
		///	ɾ�����ַ����д�ָ��λ�õ����λ�õ������ַ���
		///	<code>ԭ�ͣ�inline static string &amp;Remove(string &amp;str,int startIndex);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="startIndex">��ʼɾ���ַ���λ�á� </param> 
 		///	<returns> str�����������ڴ��ַ����޳���ɾ���ַ�����ַ�����</returns>  
        inline static string &Remove(string &str,int startIndex)
		{
			return Remove(str,startIndex,(int)str.size()-startIndex);
		}
   		///	<summary>
		///	�Ӵ�ʵ���е�ָ��λ�ÿ�ʼɾ��ָ����Ŀ���ַ���
		///	<code>ԭ�ͣ�inline static string &amp;Remove(string &amp;str,int startIndex, int count);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="startIndex">��ʼɾ���ַ���λ�á� </param> 
		///	<param name="count">Ҫɾ�����ַ����� </param> 
 		///	<returns> str�����������ڴ��ַ����޳���ɾ���ַ�����ַ�����</returns>  
        inline static string &Remove(string &str,int startIndex, int count)
		{
			str.erase(startIndex,count);
			return str;
		}; 
   		///	<summary>
		///	����ʵ���е�ָ���ַ�������ƥ�����滻Ϊ����ָ�����ַ�����
		///	<code>ԭ�ͣ�inline static string ReplaceAll(string &amp;str,char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="oldChar"> Ҫ�滻���ַ��� </param> 
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ������ַ����� </param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param> 
		///	<returns> ��Ч�ڴ�ʵ�������� oldChar ������ʵ�����滻Ϊ newChar ��<see cref="String"/>��</returns>  
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
		///	����ʵ���е�ָ���ַ��ĵ�һ��ƥ�����滻Ϊ����ָ�����ַ���
		///	<code>ԭ�ͣ�inline static string Replace(string &amp;str,char oldChar, char newChar,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���ָ��</param> 
		///	<param name="oldChar"> Ҫ�滻���ַ��� </param> 
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ������ַ��� </param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param> 
 		///	<returns> ��Ч�ڴ�ʵ�������� oldChar �ĵ�һ��ʵ���滻Ϊ newChar ��<see cref="string"/>��</returns>  
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
		///	����ʵ���е�ָ�� <see cref="string"/> ������ƥ�����滻Ϊ����ָ���� <see cref="string"/>��
		///	<code>ԭ�ͣ�inline static string ReplaceAll(string &amp;str,const string&amp; oldValue, 
		///                                             const string&amp; newValue,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���</param> 
		///	<param name="oldChar"> Ҫ�滻��<see cref="string"/>�� </param> 
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ�����<see cref="string"/>�� </param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param> 
 		///	<returns> ��Ч�ڴ�ʵ�������� oldChar �ĵ�һ��ʵ���滻Ϊ newChar ��<see cref="string"/>��</returns>  
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
		///	����ʵ���е�ָ�� <see cref="string"/> �ĵ�һ��ƥ�����滻Ϊ����ָ���� <see cref="string"/>��
		///	<code>ԭ�ͣ�inline static string Replace(string &amp;str,const string&amp; oldValue, 
		///                                             const string&amp; newValue,bool ignoreCase=false);</code>
		///	</summary> 
		///	<param name="str">Դ�ַ���</param> 
		///	<param name="oldChar"> Ҫ�滻��<see cref="string"/>�� </param> 
		///	<param name="newChar">Ҫ�滻 oldChar ������ƥ�����<see cref="string"/>�� </param> 
		///	<param name="ignoreCase">�Ƿ���Դ�Сд�� </param> 
 		///	<returns> ��Ч�ڴ�ʵ�������� oldChar �ĵ�һ��ʵ���滻Ϊ newChar ��<see cref="string"/>��</returns>  
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
		///	��otl_datetime���������ַ�
		///	<code>ԭ�ͣ�String&amp; operator&lt;&lt;(otl_datetime&amp; t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime ʱ�����</param> 
 		///	<returns><see cref="String"/>ʵ������</returns>  
		String& operator<<(otl_datetime& t)
		{
			if(t.year==0){(*this)=""; return *this;}
			char p[20];
			sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",t.year,t.month,t.day,t.hour,t.minute,t.second);
			(*this)=p;
			return *this;
		};
   		///	<summary>
		///	��otl_datetime����ʵ����<see cref="String"/>����
		///	<code>ԭ�ͣ�String(otl_datetime t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime ʱ�����</param>  
		String(otl_datetime t)
		{
			if(t.year==0){(*this)=""; }
			char p[20];
			sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",t.year,t.month,t.day,t.hour,t.minute,t.second);
			(*this)=p;
		};
   		///	<summary>
		///	��otl_datetime��<see cref="String"/>����ֵ
		///	<code>ԭ�ͣ�String &amp;operator=(otl_datetime &amp;t)</code>
		///	</summary> 
		///	<param name="t">otl_datetime ʱ�����</param>  
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

	
	// ժҪ:
    //     һ�����ַ����������Ƚϡ�
    //
    // ���ؽ��:
    //     ��� a ��ֵ�� b ��ֵ��ͬ����Ϊ true������Ϊ false��
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

	// ժҪ:
    //     ȷ������ָ���� Common.String �����Ƿ���в�ͬ��ֵ��
    //
    // ����:
    //   a:
    //     String ��null��
    //
    // ���ؽ��:
    //     ��� a ��ֵ�� b ��ֵ��ͬ����Ϊ true������Ϊ false��
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
    // ժҪ:
    //     ȷ������ָ���� Common.String �����Ƿ����ͬһֵ��
    //
    // ����:
    //   a:
    //     Common.String ��null��
    //
    // ���ؽ��:
    //     ��� a ��ֵ�� b ��ֵ��ͬ����Ϊ true������Ϊ false��
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
