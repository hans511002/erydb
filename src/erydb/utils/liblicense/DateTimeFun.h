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
//				时间类操作运算符函数
// ==============================================================

#ifndef __Common_DateTimeFun_H__ 
#define __Common_DateTimeFun_H__
#include "LicCommon.h"
 
namespace Common
{
		/**************************************************************************
		*
		*					操作符重载
		*
		**************************************************************************/
 		///	<summary>
		///	从一个指定日期和时间减去另一个指定的日期和时间以生成时间间隔<see cref="TimeSpan"/>
		///	<code>原型：TimeSpan operator -(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/>（减数）</param>
		///	<param name="d2">时间片<see cref="DateTime"/>（被减数）</param>
		///	<returns>一个新的<see cref="TimeSpan"/>对象，它是 d1 和 d2 之间的时间间隔，即 d1 减去 d2。</returns>
		TimeSpan operator -(DateTime d1, DateTime d2);
 		///	<summary>
		///	从指定的日期和时间减去指定的时间间隔，以生成新的日期和时间。
		///	<code>原型：DateTime operator -(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">时间<see cref="DateTime"/></param>
		///	<param name="t">时间片<see cref="TimeSpan"/></param>
		///	<returns>一个新的<see cref="DateTime"/>对象，值为d表示的时间减去t表示的时间片</returns>
		DateTime operator -(DateTime d, TimeSpan t);
 		///	<summary>
		///	确定 <see cref="DateTime"/> 的两个指定的实例是否不等。
		///	<code>原型：bool operator !=(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1 和 d2 不表示同一日期和时间，则为 true；否则为 false。</returns>
		bool operator !=(DateTime d1, DateTime d2);
 		///	<summary>
		///	将指定的时间间隔加<see cref="TimeSpan"/>到指定的日期和时间以生成新的日期和时间<see cref="DateTime"/>。
		///	<code>原型：DateTime operator +(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">时间<see cref="DateTime"/>，左值</param>
		///	<param name="t">时间片<see cref="TimeSpan"/></param>
		///	<returns>一个新的<see cref="DateTime"/>对象，值为d表示的时间加上t表示的时间片</returns>
		DateTime operator +(DateTime d, TimeSpan t);
 		///	<summary>
		///	对指定的<see cref="DateTime"/>对象加上一个指定的时间片<see cref="TimeSpan"/>。
		///	<code>原型：DateTime &lt;operator +=(DateTime d, TimeSpan t);</code>
		///	</summary>
		///	<param name="d">时间<see cref="DateTime"/>，左值</param>
		///	<param name="t">时间片<see cref="TimeSpan"/></param>
		///	<returns>返回d本身,在d上加上t表示的时间片</returns>
		DateTime &operator +=(DateTime &d, TimeSpan t);
 		///	<summary>
		///	二个<see cref="DateTime"/>对象的比较。确定指定的 <see cref="DateTime"/>是否小于另一个指定的 <see cref="DateTime"/>。
		///	<code>原型：bool operator &lt;(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1表示的时间比 d2 表示的时间更早，则为 true；否则为 false。</returns>
		bool operator <(DateTime t1, DateTime t2);
 		///	<summary>
		///	二个<see cref="DateTime"/>对象的比较。确定指定的 <see cref="DateTime"/>是否小于或等于另一个指定的 <see cref="DateTime"/>。
		///	<code>原型：bool operator &lt;=(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1表示的时间比 d2 表示的时间更早或相同，则为 true；否则为 false。</returns>
		bool operator <=(DateTime d1, DateTime d2);
 		///	<summary>
		///	二个<see cref="DateTime"/>对象的比较。确定<see cref="DateTime"/>的两个指定的实例是否相等。
		///	<code>原型：bool operator ==(DateTime d1, DateTime d2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1 和 d2 表示同一日期和时间，则为 true；否则为 false。</returns>
		bool operator ==(DateTime d1, DateTime d2);
 		///	<summary>
		///	二个<see cref="DateTime"/>对象的比较。确定指定的<see cref="DateTime"/>是否大于另一个指定的<see cref="DateTime"/>。
		///	<code>原型：bool operator >(DateTime t1, DateTime t2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1表示的时间比d2表示的时间更晚，则为 true；否则为 false。</returns>
		bool operator >(DateTime d1, DateTime d2);
 		///	<summary>
		///	二个<see cref="DateTime"/>对象的比较。确定指定的<see cref="DateTime"/>是否大于或等于另一个指定的<see cref="DateTime"/>。
		///	<code>原型：bool operator >=(DateTime t1, DateTime t2);</code>
		///	</summary>
		///	<param name="d1">时间一<see cref="DateTime"/></param>
		///	<param name="d2">时间二<see cref="DateTime"/></param>
		///	<returns>如果 d1表示的时间比d2表示的时间更晚，或跟d2表示同一时间点，则为 true；否则为 false。</returns>
		bool operator >=(DateTime d1, DateTime d2);

/****************************************************************************
				TimeSpan
********************************************************************************/
 		///	<summary>
		///	返回其值为指定实例的相反值的<see cref="TimeSpan"/>。
		///	<code>原型：TimeSpan &amp;operator -(TimeSpan &amp;t1);</code>
		///	</summary>
		///	<param name="t1">时间片<see cref="TimeSpan"/>，要取反的左值</param>
		///	<returns>与此实例的数值相同，但符号相反的<see cref="TimeSpan"/>。</returns>
        TimeSpan &operator -(TimeSpan &t);
 		///	<summary>
		///	时间片相减<see cref="TimeSpan"/>。
		///	<code>原型：TimeSpan operator -(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>一个新的时间片对象，值为t1值减压去t2以后的值。</returns>
		TimeSpan operator -(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	时间片相减<see cref="TimeSpan"/>。
		///	<code>原型：TimeSpan &amp;operator -=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一,左值<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>返回减去t2的t1本身。</returns>
		TimeSpan &operator -=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	指示两个 <see cref="TimeSpan"/>实例是否不相等。
		///	<code>原型：bool operator !=(TimeSpan &amp;t1, TimeSpan &amp;t2);;</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 和 t2 的值不相等，则为 true；否则为 false。。</returns>
        bool operator !=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	二个时间片的相加<see cref="TimeSpan"/>
		///	<code>原型：TimeSpan operator +(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>一个新的时间片对象，值为t1+t2的和。</returns>
        TimeSpan operator +(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	二个时间片的相加<see cref="TimeSpan"/>
		///	<code>原型：TimeSpan &amp;operator +=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一，左值<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>返回加上t2的t1本身。</returns>
		TimeSpan &operator +=(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	时间片的大小比较。指示指定的<see cref="TimeSpan"/>是否小于另一个指定的<see cref="TimeSpan"/>
		///	<code>原型：bool operator &lt;TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 的值小于 t2 的值，则为 true；否则为 false。</returns>
        bool operator <(TimeSpan &t1, TimeSpan &t2);
 		///	<summary>
		///	时间片的大小比较。指示指定的<see cref="TimeSpan"/>是否小于或等于另一个指定的<see cref="TimeSpan"/>
		///	<code>原型：bool operator &lt;=TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 的值小于或等于 t2 的值，则为 true；否则为 false。</returns>
       bool operator <=(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	时间片的大小比较。指示两个 <see cref="TimeSpan"/> 实例是否相等
		///	<code>原型：bool operator ==(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 和 t2 的值相等，则为 true；否则为 false。</returns>
        bool operator ==(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	时间片的大小比较。指示指定的 <see cref="TimeSpan"/> 是否大于或等于另一个指定的 <see cref="TimeSpan"/>
		///	<code>原型：bool operator >(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 的值大于 t2 的值，则为 true；否则为 false。</returns>
        bool operator >(TimeSpan &t1, TimeSpan &t2);
		///	<summary>
		///	时间片的大小比较。指示指定的 <see cref="TimeSpan"/> 是否大于或等于另一个指定的 <see cref="TimeSpan"/>
		///	<code>原型：bool operator >=(TimeSpan &amp;t1, TimeSpan &amp;t2);</code>
		///	</summary>
		///	<param name="t1">时间片一<see cref="TimeSpan"/></param>
		///	<param name="t2">时间片二<see cref="TimeSpan"/></param>
		///	<returns>如果 t1 的值大于或等于 t2 的值，则为 true；否则为 false。</returns>
        bool operator >=(TimeSpan &t1, TimeSpan &t2);



}
#endif
//
