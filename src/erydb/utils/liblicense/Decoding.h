// ==============================================================
//progame      Common::Decoding 
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

#ifndef __License_Decoding__
#define __License_Decoding__

namespace License
{
 
	///	<summary>
	///	解密函数类
	///	</summary>
	///	<remarks>
	///	<code>二进制对称加密对应的解密算法</code>
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class Decoding
	{
	public:
		///	<summary>
		///	矩阵解密
		///	<code>原型：static void matrixDecode(const char * src,char * dest,const char * password);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param>
		///	<param name="password">密钥</param>
		static void matrixDecode(const char * src,char * dest,const char * password);
		///	<summary>
		///	镜像解密
		///	<code>原型：static void MSLDecode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param> 
		static void MSLDecode(const char * src,char * dest);
		///	<summary>
		///	倒置解密
		///	<code>原型：static void anasDecode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param> 
		static void anasDecode(const char * src,char * dest);
		///	<summary>
		///	移位解密(按字节循环反向移位)
		///	<code>原型：static void shiftDecode(const char * src,char * dest,int size);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param> 
		///	<param name="size">大小,对8取模为0是数据无改变</param> 
		static void shiftDecode(const char * src,char * dest,int size);
		///	<summary>
		///	多移位解密(按字节循环反向移位)
		///	<code>原型：static void shiftDecode(const char * src,char * dest,int size,int len);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param> 
		///	<param name="size">移位大小指针,其中元素对8取模为0是数据无改变</param> 
		///	<param name="len">指示size的长度</param> 
		static void shiftDecode(const char * src,char * dest,int * size,int len);
		///	<summary>
		///	矩阵打乱解密
		///	<code>原型：static void chaosDecode(const char * src,char * dest,int len);</code>
		///	</summary>
		///	<param name="src">密文字符串指针</param>
		///	<param name="dest">存储解密后的明文字符串指针</param>  
		///	<param name="len">按len指定的长度矩阵还原</param> 
		static void chaosDecode(const char * src,char * dest,int len);
		static int base64_decode(const char * base64, unsigned char * bindata);
		static void base64_decode(FILE * fp_in, FILE * fp_out);

	};
}
#endif
