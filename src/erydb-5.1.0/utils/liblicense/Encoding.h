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
	///	���ܺ�����
	///	</summary>
	///	<remarks>
	///	<code>�����ƶԳƼ��ܶ�Ӧ�ļ����㷨</code>
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class Encoding
	{
	public:
		///	<summary>
		///	�������,�ȴ��ң�����λ
		///	<code>ԭ�ͣ�static void matrixEncode(const char * src,char * dest,const char * password);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		///	<param name="password">��Կ</param>
		static void matrixEncode(const char * src,char * dest,const char * password);
		///	<summary>
		///	�������(����)
		///	<code>ԭ�ͣ�static void MSLEncode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		static void MSLEncode(const char * src,char * dest);
 		///	<summary>
		///	���ü���
		///	<code>ԭ�ͣ�static void anasEncode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		static void anasEncode(const char * src,char * dest);
  		///	<summary>
		///	��λ����
		///	<code>ԭ�ͣ�static void shiftEncode(const char * src,char * dest,int size);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		///	<param name="size">��λ��С������8ȡģΪ0ʱ��������</param>
		static void shiftEncode(const char * src,char * dest,int size);
  		///	<summary>
		///	����λ����
		///	<code>ԭ�ͣ�static void shiftEncode(const char * src,char * dest,int size,int len);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		///	<param name="size">intָ�룬��Ԫ�ر�ʾ��λ��С������8ȡģΪ0ʱ��������</param>
		///	<param name="len">ָʾsizeָ��ĳ���</param>
		static void shiftEncode(const char * src,char * dest,int * size,int len);
  		///	<summary>
		///	���Ҽ���
		///	<code>ԭ�ͣ�static void chaosEncode(const char * src,char * dest,int len);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param> 
		///	<param name="len">ָʾ���Ҿ���ĳ���</param>
		static void chaosEncode(const char * src,char * dest,int len);
  		///	<summary>
		///	�ַ���λ��ѭ����λ
		///	<code>ԭ�ͣ�inline static char cycShift(const char src,int size);</code>
		///	</summary>
		///	<param name="src">�����ַ�</param> 
		///	<param name="size">��λ��С</param>
		///	<returns>��λ����ַ�</returns>
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
