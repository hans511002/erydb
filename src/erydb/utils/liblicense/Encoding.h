// ==============================================================
//progame      Common::Encoding 
//company      hans
//copyright    Copyright (c) hans  2007-4     2008-06
//version      1.0
//Author       hans
//date         2007-4     2008-06
//description  Common namespace
//				This library is free software. Permission to use, copy,
//				modify and redistribute it for any purpose is hereby granted
//				without fee, provided that the above copyright notice appear
//				in all copies.
// ==============================================================

#ifndef __License_Encoding__
#define __License_Encoding__
#include "LicCommon.h"

namespace License
{
	extern    char   *  base64char  ;
	///	<summary>
	///	加密函数类
	///	</summary>
	///	<remarks>
	///	<code>二进制对称加密对应的加密算法</code>
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class Encoding
	{
	public:
		///	<summary>
		///	矩阵加密,先打乱，再移位
		///	<code>原型：static void matrixEncode(const char * src,char * dest,const char * password);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param>
		///	<param name="password">密钥</param>
		static void matrixEncode(const char * src,char * dest,const char * password);
		///	<summary>
		///	镜像加密(补反)
		///	<code>原型：static void MSLEncode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param>
		static void MSLEncode(const char * src,char * dest);
 		///	<summary>
		///	倒置加密
		///	<code>原型：static void anasEncode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param>
		static void anasEncode(const char * src,char * dest);
  		///	<summary>
		///	移位加密
		///	<code>原型：static void shiftEncode(const char * src,char * dest,int size);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param>
		///	<param name="size">移位大小，当对8取模为0时不起作用</param>
		static void shiftEncode(const char * src,char * dest,int size);
  		///	<summary>
		///	多移位加密
		///	<code>原型：static void shiftEncode(const char * src,char * dest,int size,int len);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param>
		///	<param name="size">int指针，基元素表示移位大小，当对8取模为0时不起作用</param>
		///	<param name="len">指示size指针的长度</param>
		static void shiftEncode(const char * src,char * dest,int * size,int len);
  		///	<summary>
		///	打乱加密
		///	<code>原型：static void chaosEncode(const char * src,char * dest,int len);</code>
		///	</summary>
		///	<param name="src">明文字符串指针</param>
		///	<param name="dest">存储加密后的密文字符串指针</param> 
		///	<param name="len">指示打乱矩阵的长度</param>
		static void chaosEncode(const char * src,char * dest,int len);
  		///	<summary>
		///	字符移位，循环移位
		///	<code>原型：inline static char cycShift(const char src,int size);</code>
		///	</summary>
		///	<param name="src">明文字符</param> 
		///	<param name="size">移位大小</param>
		///	<returns>移位后的字符</returns>
		inline static char cycShift(const char src,int size)
		{
			unsigned char c=src;
			unsigned char tc;
			tc=c>>size;
			return (c<<(8-size)) | tc;
		}
		template <class T>  inline static T cycShift(const T src,int size)
		{
			T tc=src>>size;
			return (src<<((sizeof(T))-size)) | tc;
		}


		static char * base64_encode(const unsigned char * bindata, char * base64, int binlength);

		static void base64_encode(FILE * fp_in, FILE * fp_out);

		
	};
}
#endif
