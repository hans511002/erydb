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
	///	���ܺ�����
	///	</summary>
	///	<remarks>
	///	<code>�����ƶԳƼ��ܶ�Ӧ�Ľ����㷨</code>
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class Decoding
	{
	public:
		///	<summary>
		///	�������
		///	<code>ԭ�ͣ�static void matrixDecode(const char * src,char * dest,const char * password);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>
		///	<param name="password">��Կ</param>
		static void matrixDecode(const char * src,char * dest,const char * password);
		///	<summary>
		///	�������
		///	<code>ԭ�ͣ�static void MSLDecode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param> 
		static void MSLDecode(const char * src,char * dest);
		///	<summary>
		///	���ý���
		///	<code>ԭ�ͣ�static void anasDecode(const char * src,char * dest);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param> 
		static void anasDecode(const char * src,char * dest);
		///	<summary>
		///	��λ����(���ֽ�ѭ��������λ)
		///	<code>ԭ�ͣ�static void shiftDecode(const char * src,char * dest,int size);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param> 
		///	<param name="size">��С,��8ȡģΪ0�������޸ı�</param> 
		static void shiftDecode(const char * src,char * dest,int size);
		///	<summary>
		///	����λ����(���ֽ�ѭ��������λ)
		///	<code>ԭ�ͣ�static void shiftDecode(const char * src,char * dest,int size,int len);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param> 
		///	<param name="size">��λ��Сָ��,����Ԫ�ض�8ȡģΪ0�������޸ı�</param> 
		///	<param name="len">ָʾsize�ĳ���</param> 
		static void shiftDecode(const char * src,char * dest,int * size,int len);
		///	<summary>
		///	������ҽ���
		///	<code>ԭ�ͣ�static void chaosDecode(const char * src,char * dest,int len);</code>
		///	</summary>
		///	<param name="src">�����ַ���ָ��</param>
		///	<param name="dest">�洢���ܺ�������ַ���ָ��</param>  
		///	<param name="len">��lenָ���ĳ��Ⱦ���ԭ</param> 
		static void chaosDecode(const char * src,char * dest,int len);
		static int base64_decode(const char * base64, unsigned char * bindata);
		static void base64_decode(FILE * fp_in, FILE * fp_out);

	};
}
#endif
