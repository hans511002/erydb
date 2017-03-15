// ==============================================================
//progame      Common::DateTime 
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
//				ʱ����������������
// ==============================================================

#ifndef __Common_DateTimeFun_H__ 
#define __Common_DateTimeFun_H__
#include "LicCommon.h"
 
namespace Common
{
		/**************************************************************************
		*
		*					����������
		*
		**************************************************************************/
 		///	<summary>
		///	��һ��ָ�����ں�ʱ���ȥ��һ��ָ�������ں�ʱ��������ʱ����<see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�TimeSpan operator -(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/>��������</param>
		///	<param name="d2">ʱ��Ƭ<see cref="DateTime"/>����������</param>
		///	<returns>һ���µ�<see cref="TimeSpan"/>�������� d1 �� d2 ֮���ʱ�������� d1 ��ȥ d2��</returns>
		TimeSpan operator -(DateTime d1, DateTime d2);
 		///	<summary>
		///	��ָ�������ں�ʱ���ȥָ����ʱ�������������µ����ں�ʱ�䡣
		///	<code>ԭ�ͣ�DateTime operator -(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">ʱ��<see cref="DateTime"/></param>
		///	<param name="t">ʱ��Ƭ<see cref="TimeSpan"/></param>
		///	<returns>һ���µ�<see cref="DateTime"/>����ֵΪd��ʾ��ʱ���ȥt��ʾ��ʱ��Ƭ</returns>
		DateTime operator -(DateTime d, TimeSpan t);
 		///	<summary>
		///	ȷ�� <see cref="DateTime"/> ������ָ����ʵ���Ƿ񲻵ȡ�
		///	<code>ԭ�ͣ�bool operator !=(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1 �� d2 ����ʾͬһ���ں�ʱ�䣬��Ϊ true������Ϊ false��</returns>
		bool operator !=(DateTime d1, DateTime d2);
 		///	<summary>
		///	��ָ����ʱ������<see cref="TimeSpan"/>��ָ�������ں�ʱ���������µ����ں�ʱ��<see cref="DateTime"/>��
		///	<code>ԭ�ͣ�DateTime operator +(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">ʱ��<see cref="DateTime"/>����ֵ</param>
		///	<param name="t">ʱ��Ƭ<see cref="TimeSpan"/></param>
		///	<returns>һ���µ�<see cref="DateTime"/>����ֵΪd��ʾ��ʱ�����t��ʾ��ʱ��Ƭ</returns>
		DateTime operator +(DateTime d, TimeSpan t);
 		///	<summary>
		///	��ָ����<see cref="DateTime"/>�������һ��ָ����ʱ��Ƭ<see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�DateTime &lt;operator +=(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">ʱ��<see cref="DateTime"/>����ֵ</param>
		///	<param name="t">ʱ��Ƭ<see cref="TimeSpan"/></param>
		///	<returns>����d����,��d�ϼ���t��ʾ��ʱ��Ƭ</returns>
		DateTime &operator +=(DateTime &d, TimeSpan t);
 		///	<summary>
		///	����<see cref="DateTime"/>����ıȽϡ�ȷ��ָ���� <see cref="DateTime"/>�Ƿ�С����һ��ָ���� <see cref="DateTime"/>��
		///	<code>ԭ�ͣ�bool operator &lt;(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1��ʾ��ʱ��� d2 ��ʾ��ʱ����磬��Ϊ true������Ϊ false��</returns>
		bool operator <(DateTime t1, DateTime t2);
 		///	<summary>
		///	����<see cref="DateTime"/>����ıȽϡ�ȷ��ָ���� <see cref="DateTime"/>�Ƿ�С�ڻ������һ��ָ���� <see cref="DateTime"/>��
		///	<code>ԭ�ͣ�bool operator &lt;=(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1��ʾ��ʱ��� d2 ��ʾ��ʱ��������ͬ����Ϊ true������Ϊ false��</returns>
		bool operator <=(DateTime d1, DateTime d2);
 		///	<summary>
		///	����<see cref="DateTime"/>����ıȽϡ�ȷ��<see cref="DateTime"/>������ָ����ʵ���Ƿ���ȡ�
		///	<code>ԭ�ͣ�bool operator ==(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1 �� d2 ��ʾͬһ���ں�ʱ�䣬��Ϊ true������Ϊ false��</returns>
		bool operator ==(DateTime d1, DateTime d2);
 		///	<summary>
		///	����<see cref="DateTime"/>����ıȽϡ�ȷ��ָ����<see cref="DateTime"/>�Ƿ������һ��ָ����<see cref="DateTime"/>��
		///	<code>ԭ�ͣ�bool operator >(DateTime t1, DateTime t2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1��ʾ��ʱ���d2��ʾ��ʱ�������Ϊ true������Ϊ false��</returns>
		bool operator >(DateTime d1, DateTime d2);
 		///	<summary>
		///	����<see cref="DateTime"/>����ıȽϡ�ȷ��ָ����<see cref="DateTime"/>�Ƿ���ڻ������һ��ָ����<see cref="DateTime"/>��
		///	<code>ԭ�ͣ�bool operator >=(DateTime t1, DateTime t2);</code>
		///	</summary>
		///	<param name="d1">ʱ��һ<see cref="DateTime"/></param>
		///	<param name="d2">ʱ���<see cref="DateTime"/></param>
		///	<returns>��� d1��ʾ��ʱ���d2��ʾ��ʱ��������d2��ʾͬһʱ��㣬��Ϊ true������Ϊ false��</returns>
		bool operator >=(DateTime d1, DateTime d2);

/****************************************************************************
				TimeSpan
********************************************************************************/
 		///	<summary>
		///	������ֵΪָ��ʵ�����෴ֵ��<see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�TimeSpan &amp;operator -(TimeSpan &amp;t1);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭ<see cref="TimeSpan"/>��Ҫȡ������ֵ</param>
		///	<returns>���ʵ������ֵ��ͬ���������෴��<see cref="TimeSpan"/>��</returns>
        TimeSpan &operator -(TimeSpan &t);
 		///	<summary>
		///	ʱ��Ƭ���<see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�TimeSpan operator -(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>һ���µ�ʱ��Ƭ����ֵΪt1ֵ��ѹȥt2�Ժ��ֵ��</returns>
		TimeSpan operator -(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	ʱ��Ƭ���<see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�TimeSpan &amp;operator -=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ,��ֵ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>���ؼ�ȥt2��t1����</returns>
		TimeSpan &operator -=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	ָʾ���� <see cref="TimeSpan"/>ʵ���Ƿ���ȡ�
		///	<code>ԭ�ͣ�bool operator !=(TimeSpan &amp;t1, TimeSpan &amp;t2);;</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 �� t2 ��ֵ����ȣ���Ϊ true������Ϊ false����</returns>
        bool operator !=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	����ʱ��Ƭ�����<see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�TimeSpan operator +(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>һ���µ�ʱ��Ƭ����ֵΪt1+t2�ĺ͡�</returns>
        TimeSpan operator +(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	����ʱ��Ƭ�����<see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�TimeSpan &amp;operator +=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ����ֵ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>���ؼ���t2��t1����</returns>
		TimeSpan &operator +=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	ʱ��Ƭ�Ĵ�С�Ƚϡ�ָʾָ����<see cref="TimeSpan"/>�Ƿ�С����һ��ָ����<see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�bool operator &lt;TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 ��ֵС�� t2 ��ֵ����Ϊ true������Ϊ false��</returns>
        bool operator <(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	ʱ��Ƭ�Ĵ�С�Ƚϡ�ָʾָ����<see cref="TimeSpan"/>�Ƿ�С�ڻ������һ��ָ����<see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�bool operator &lt;=TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 ��ֵС�ڻ���� t2 ��ֵ����Ϊ true������Ϊ false��</returns>
       bool operator <=(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	ʱ��Ƭ�Ĵ�С�Ƚϡ�ָʾ���� <see cref="TimeSpan"/> ʵ���Ƿ����
		///	<code>ԭ�ͣ�bool operator ==(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 �� t2 ��ֵ��ȣ���Ϊ true������Ϊ false��</returns>
        bool operator ==(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	ʱ��Ƭ�Ĵ�С�Ƚϡ�ָʾָ���� <see cref="TimeSpan"/> �Ƿ���ڻ������һ��ָ���� <see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�bool operator >(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 ��ֵ���� t2 ��ֵ����Ϊ true������Ϊ false��</returns>
        bool operator >(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	ʱ��Ƭ�Ĵ�С�Ƚϡ�ָʾָ���� <see cref="TimeSpan"/> �Ƿ���ڻ������һ��ָ���� <see cref="TimeSpan"/>
		///	<code>ԭ�ͣ�bool operator >=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">ʱ��Ƭһ<see cref="TimeSpan"/></param>
		///	<param name="t2">ʱ��Ƭ��<see cref="TimeSpan"/></param>
		///	<returns>��� t1 ��ֵ���ڻ���� t2 ��ֵ����Ϊ true������Ϊ false��</returns>
        bool operator >=(TimeSpan &t1, TimeSpan &t2);



}
#endif
//
