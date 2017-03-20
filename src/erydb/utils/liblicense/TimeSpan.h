// ==============================================================
//progame      Common::TimeSpan 
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

#ifndef __Common_TimeSpan_H__
#define __Common_TimeSpan_H__
#include "LicCommon.h" 
#include "MYString.h" 

namespace Common
{
	///	<summary>
	///	表示一个时间间隔。
	///	</summary>
	///	<remarks>
	///	精确的表示一个时间间隔，精确到微秒。
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class TimeSpan
	{
	public:
		///	<summary>
		///	时间片的刻度数，微秒数。
		///	</summary>
		long long _ticks;
		///	<summary>
		///	一微秒等于多少天。此字段为常数。
		///	</summary>
		static const double DaysPerTicks;
		///	<summary>
		///	一微秒等于多少小时。此字段为常数。
		///	</summary>
		static const double HoursPerTicks;
		///	<summary>
		///	一微秒等于多少分钟数。此字段为常数。
		///	</summary>
		static const double MinutesPerTicks;
		///	<summary>
		///	一微秒等于多少秒。此字段为常数。
		///	</summary>
		static const double SecondsPerTicks;
		///	<summary>
		///	最大毫秒数。此字段为常数。
		///	</summary>
		static const long long MaxMillis ;
		///	<summary>
		///	最大秒数。此字段为常数。
		///	</summary>
		static const long long MaxSeconds ;
		///	<summary>
		///	表示一天中的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const int MillisPerDay ;
		///	<summary>
		///	表示 1 小时的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const int MillisPerHour ;
		///	<summary>
		///	表示 1 分钟的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const int MillisPerMinute ;
		///	<summary>
		///	表示 1 秒的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const int MillisPerSecond ;

		///	<summary>
		///	表示 1 毫秒的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const long long  TicksPerMillisecond ;
		///	<summary>
		///	表示 1 秒的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const long long  TicksPerSecond ;
		///	<summary>
		///	表示 1 分钟的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const long long  TicksPerMinute ;
		///	<summary>
		///	表示 1 小时的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const long long  TicksPerHour ;
		///	<summary>
		///	表示 1 天的刻度数(微秒)。此字段为常数。
		///	</summary>
		static const long long  TicksPerDay ;
		///	<summary>
		///	最小毫秒数。此字段为常数。
		///	</summary>
		static const long long MinMilliSeconds ;
		///	<summary>
		///	最小秒数。此字段为常数。
		///	</summary>
		static const long long MinSeconds ;
		///	<summary>
		///	表示最大的<see cref="TimeSpan"/>。此字段为常数。
		///	</summary>
        static  const TimeSpan MaxValue;
		///	<summary>
		///	表示最小的<see cref="TimeSpan"/>。此字段为常数。
		///	</summary>
        static  const TimeSpan MinValue;
		///	<summary>
		///	表示零<see cref="TimeSpan"/> 值。此字段为常数。
		///	</summary>
        static const  TimeSpan Zero;


	public:
		///	<summary>
		///	将时间部分转换为时间刻度数（微秒）
		///	<code>原型：inline static unsigned long long TimeToTicks(int hour, int minute, int second);</code>
		///	</summary>
		///	<param name="hour">小时</param>
		///	<param name="minute">分钟</param>
		///	<param name="second">秒</param>
		///	<returns>返回对应的刻度数（微秒数）</returns>
		inline static unsigned long long TimeToTicks(int hour, int minute, int second)
		{
			long long num = ((hour * 0xe10) + (minute * 60)) + second;
			if ((num > TimeSpan::MaxSeconds) || (num < TimeSpan::MinSeconds))
			{
				EXP("Overflow_TimeSpanTooLong");
			}
			return (num * TimeSpan::TicksPerSecond);
		}
		///	<summary>
		///	将新的 <see cref="TimeSpan"/> 初始化为指定的刻度数（微秒）。
		///	<code>原型：TimeSpan(long long ticks=0);</code>
		///	</summary>
		///	<param name="ticks">刻度数（微秒数），以 1 微秒为单位表示的时间段。</param>
		TimeSpan(long long ticks=0)
		{
			this->_ticks=ticks;
		}
		///	<summary>
		///	将新的 <see cref="TimeSpan"/> 初始化为指定的刻度数（微秒）。
		///	<code>原型：TimeSpan(int millis);</code>
		///	</summary>
		///	<param name="millis">刻度数（微秒数），以 1 微秒为单位表示的时间段。</param>
		TimeSpan(int millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	将新的 <see cref="TimeSpan"/> 初始化为指定的刻度数（微秒）。
		///	<code>原型：TimeSpan(long millis);</code>
		///	</summary>
		///	<param name="millis">刻度数（微秒数），以 1 微秒为单位表示的时间段。</param>
		TimeSpan(long millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	将新的 <see cref="TimeSpan"/> 初始化为指定的刻度数（微秒）。
		///	<code>原型：TimeSpan(unsigned long long millis);</code>
		///	</summary>
		///	<param name="millis">刻度数（微秒数），以 1 微秒为单位表示的时间段。</param>
		TimeSpan(unsigned long long millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	以指定的时分秒毫秒微秒初始化<see cref="TimeSpan"/>对象。
		///	<code>原型：TimeSpan(int hours, int minutes, int seconds, int milliseconds,int ticks);</code>
		///	</summary>
		///	<param name="hours">小时。</param>
		///	<param name="minutes">分钟。</param>
		///	<param name="seconds">秒。</param>
		///	<param name="milliseconds">毫秒。</param>
		///	<param name="ticks">微秒。</param> 
		TimeSpan(int hours, int minutes, int seconds, int milliseconds,int ticks)
		{
			this->_ticks=hours * TicksPerHour + minutes * TicksPerMinute + seconds * TicksPerSecond+milliseconds* this->TicksPerMillisecond + ticks;
		}
		///	<summary>
		///	以指定的时分秒毫秒微秒初始化<see cref="TimeSpan"/>对象。
		///	<code>原型：TimeSpan(int days,int hours, int minutes, int seconds, int milliseconds,int ticks);</code>
		///	</summary>
		///	<param name="days">天。</param>
		///	<param name="hours">小时。</param>
		///	<param name="minutes">分钟。</param>
		///	<param name="seconds">秒。</param>
		///	<param name="milliseconds">毫秒。</param>
		///	<param name="ticks">微秒。</param> 
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds,int ticks)
		{
			this->_ticks=days * TicksPerDay +hours * TicksPerHour + minutes * TicksPerMinute + seconds * TicksPerSecond+milliseconds* this->TicksPerMillisecond + ticks;
		}

        // 名称空间操作重载友元申明
        friend TimeSpan &Common::operator -(TimeSpan &t);
		friend TimeSpan Common::operator -(TimeSpan &t1, TimeSpan &t2);
		friend TimeSpan &Common::operator -=(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator !=(TimeSpan &t1, TimeSpan &t2);
        friend TimeSpan Common::operator +(TimeSpan &t1, TimeSpan &t2);
		friend TimeSpan &Common::operator +=(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator <(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator <=(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator ==(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator >(TimeSpan &t1, TimeSpan &t2);
        friend bool Common::operator >=(TimeSpan &t1, TimeSpan &t2);


		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的整天数。
		///	<code>原型：inline int getDays();</code>
		///	</summary>
		///	<returns>此实例的天数部分。返回值可以是正数也可以是负数。</returns>
		inline int getDays()
		{
			if(this->_ticks==0)return 0;
			return (this->_ticks/this->TicksPerDay);
		}
		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的整小时数。
		///	<code>原型：inline int getHours();</code>
		///	</summary>
		///	<returns>当前<see cref="TimeSpan"/>结构的小时分量。返回值的范围为 -23 到 23。</returns>
		inline int getHours()
		{
			if(this->_ticks==0)return 0;
			return	int((this->_ticks%this->TicksPerDay)/this->TicksPerHour);
		} 
		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的整分钟数。
		///	<code>原型：inline int getMinutes();</code>
		///	</summary>
		///	<returns>当前<see cref="TimeSpan"/>结构的分钟分量。返回值的范围为 -59 到 59。</returns>
		inline int getMinutes()
		{
			if(this->_ticks==0)return 0;
			return int((this->_ticks % this->TicksPerHour)/this->TicksPerMinute);
		} 
		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的整秒数。
		///	<code>原型：inline int getSeconds();</code>
		///	</summary>
		///	<returns>当前<see cref="TimeSpan"/>结构的秒分量。返回值的范围为 -59 到 59。</returns>
		inline int getSeconds()
		{
			if(this->_ticks==0)return 0;
			return int(this->_ticks/this->TicksPerSecond) % 60;
		}
		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的整秒数。
		///	<code>原型：inline int getSeconds();</code>
		///	</summary>
		///	<returns>当前<see cref="TimeSpan"/>结构的毫秒分量。返回值的范围为 -999 到 999。</returns>
		inline int getMilliseconds()
		{
			if(this->_ticks==0)return 0;
			return int((this->_ticks % this->TicksPerSecond)/this->TicksPerMillisecond);
		}
		///	<summary>
		///	获取由当前 <see cref="TimeSpan"/> 结构表示的微秒数。
		///	<code>原型：inline int getUsec();</code>
		///	</summary>
		///	<returns>当前<see cref="TimeSpan"/>结构表示的微秒数。返回值的范围为 -999 到 999。</returns>
		inline int getUsec()
		{
			if(this->_ticks==0)return 0;
			return int(this->_ticks % this->TicksPerMillisecond);
		}
		///	<summary>
		///	获取以整天数和天的小数部分表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalDays();</code>
		///	</summary>
		///	<returns>此实例表示的总天数</returns>
		inline double getTotalDays()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerDay;;
		}
		///	<summary>
		///	获取以整小时数和小时的小数部分表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalHours();</code>
		///	</summary>
		///	<returns>此实例表示的总小时数</returns>
		inline double getTotalHours()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerHour;
		}
 		///	<summary>
		///	获取以整分钟数和分钟的小数部分表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalMinutes();</code>
		///	</summary>
		///	<returns>此实例表示的总分钟数</returns>
		inline double getTotalMinutes()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerMinute;;
		}
  		///	<summary>
		///	获取以整秒数和秒的小数部分表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalSeconds();</code>
		///	</summary>
		///	<returns>此实例表示的总秒数</returns>
		inline double getTotalSeconds()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerSecond;
		}
  		///	<summary>
		///	获取以整毫秒数和毫秒的小数部分表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalMilliseconds();</code>
		///	</summary>
		///	<returns>此实例表示的总毫秒数</returns>
		inline double getTotalMilliseconds()
		{
			return (double)this->_ticks/(double)this->TicksPerMillisecond;
		}
  		///	<summary>
		///	获取以整微秒数表示的当前 <see cref="TimeSpan"/> 结构的值。
		///	<code>原型：inline double getTotalTicks();</code>
		///	</summary>
		///	<returns>此实例表示的总微秒数</returns>
		inline long long getTotalTicks()
		{
			return this->_ticks;
		}
  		///	<summary>
		///	将指定的 <see cref="TimeSpan"/> 添加到此实例中。
		///	<code>原型：inline TimeSpan &amp;Add(TimeSpan ts);</code>
		///	</summary>
		///	<param name="ts">要添加的<see cref="TimeSpan"/>对象</param>
		///	<returns>当前实例本身，值为此实例的值与 ts 的值之和</returns>
		inline TimeSpan &Add(TimeSpan ts)
		{
			this->_ticks+=ts.getTotalTicks();
			return *this;
		}
  		///	<summary>
		///	比较两个 <see cref="TimeSpan"/> 值并返回一个指示它们之间关系的整数。
		///	<code>原型：inline static int Compare(TimeSpan t1, TimeSpan t2);</code>
		///	</summary>
		///	<param name="t1">时间间隔一<see cref="TimeSpan"/>对象</param>
		///	<param name="t2">时间间隔二<see cref="TimeSpan"/>对象</param>
		///	<returns>值条件: -1 t1 小于 t2, 0 t1 等于 t2,1 t1 大于 t2</returns>
        inline static int Compare(TimeSpan t1, TimeSpan t2)
		{
			long long v=t1.getTotalTicks()-t2.getTotalTicks();
			if(v>0)
				return 1;
			else if(v==0)
				return 0;
			else return -1;
		};
  		///	<summary>
		///	将此实例与指定 <see cref="TimeSpan"/> 对象进行比较并返回对其相对值的指示。
		///	<code>原型：inline int Compare(TimeSpan value);</code>
		///	</summary>
		///	<param name="value">时间间隔一<see cref="TimeSpan"/>对象</param> 
		///	<returns>有符号数字，指示此实例和 value 的相对值。值说明: 负整数 此实例小于 value。 零 此实例等于 value。 正整数 此实例大于 value。</returns>
		inline int CompareTo(TimeSpan value){return TimeSpan::Compare(*this, value);};
   		///	<summary>
		///	返回新的 <see cref="TimeSpan"/> 对象，其值是当前 <see cref="TimeSpan"/> 对象的绝对值。。
		///	<code>原型：inline TimeSpan Duration();</code>
		///	</summary>
 		///	<returns>新的 <see cref="TimeSpan"/>，其值是当前 <see cref="TimeSpan"/> 对象的绝对值</returns>
        inline TimeSpan Duration()
		{
			if(this->_ticks>0)
				return TimeSpan(this->_ticks);
			else
				return TimeSpan(0-this->_ticks);
		};
//**********************************************                                    
   		///	<summary>
		///	返回一个值，该值指示此实例是否与指定的 <see cref="TimeSpan"/> 对象相等。
		///	<code>原型：inline bool Equals(TimeSpan obj);</code>
		///	</summary>
 		///	<param name="obj">时间间隔<see cref="TimeSpan"/>对象</param>
		///	<returns>如果 obj 表示的时间间隔与此实例相同，则为 true；否则为 false。</returns>
		inline bool Equals(TimeSpan obj){return this->_ticks==obj.getTotalTicks();};
   		///	<summary>
		///	返回一个值，该值指示 <see cref="TimeSpan"/> 的两个指定实例是否相等。
		///	<code>原型：inline static bool Equals(TimeSpan t1, TimeSpan t2);</code>
		///	</summary>
 		///	<param name="t1">时间间隔一<see cref="TimeSpan"/>对象</param>
 		///	<param name="t2">时间间隔下<see cref="TimeSpan"/>对象</param>
		///	<returns>如果 t1 和 t2 的值相等，则为 true；否则为 false。</returns>
		inline static bool Equals(TimeSpan t1, TimeSpan t2){return t1.getTotalTicks()==t2.getTotalTicks();};
   		///	<summary>
		///	返回表示指定天数的 <see cref="TimeSpan"/> 其中对天数的指定精确到最接近的微秒。
		///	<code>原型：inline static TimeSpan FromDays(double value);</code>
		///	</summary>
 		///	<param name="value">天数，精确到最接近的微秒。</param> 
		///	<returns>表示 value 的 <see cref="TimeSpan"/></returns>
        inline static TimeSpan FromDays(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerDay);
			return TimeSpan(l);
		};
   		///	<summary>
		///	返回表示指定小时数的 <see cref="TimeSpan"/> 其中对小时数的指定精确到最接近的微秒。
		///	<code>原型：inline static TimeSpan FromHours(double value);</code>
		///	</summary>
 		///	<param name="value">小时数，精确到最接近的微秒。</param> 
		///	<returns>表示 value 的 <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromHours(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerHour);
			return TimeSpan(l);
		}
   		///	<summary>
		///	返回表示指定微秒数的 <see cref="TimeSpan"/>。
		///	<code>原型：inline static TimeSpan FromMilliseconds(long long value);</code>
		///	</summary>
 		///	<param name="value">微秒数。</param> 
		///	<returns>表示 value 的 <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromMilliseconds(long long value)
		{
			return TimeSpan(value);
		}
   		///	<summary>
		///	返回表示指定分钟数的 <see cref="TimeSpan"/>,其中对分钟数的指定精确到最接近的微秒。
		///	<code>原型：inline static TimeSpan FromMinutes(double value);</code>
		///	</summary>
 		///	<param name="value">分钟数，精确到最接近的微秒。</param> 
		///	<returns>表示 value 的 <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromMinutes(double value)
		{
			long long  l=(long long)ceil(value*TimeSpan::TicksPerMinute);
			return TimeSpan(l);
		}
   		///	<summary>
		///	返回表示指定秒数的 <see cref="TimeSpan"/>,其中对分钟数的指定精确到最接近的微秒。
		///	<code>原型：inline static TimeSpan FromSeconds(double value);</code>
		///	</summary>
 		///	<param name="value">秒数，精确到最接近的微秒。</param> 
		///	<returns>表示 value 的 <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromSeconds(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerSecond);
			return TimeSpan(l);
		}
   		///	<summary>
		///	返回其值为此实例的相反值的 <see cref="TimeSpan"/>。
		///	<code>原型：inline TimeSpan Negate();</code>
		///	</summary>
		///	<returns>与此实例的数值相同但符号相反</returns>
        inline TimeSpan Negate()
		{
			if(this->_ticks!=0)
			{
				return  TimeSpan(0-_ticks);
			}
			else
			{
				return TimeSpan(0);
			}
		};
   		///	<summary>
		///	从此实例中减去指定的 <see cref="TimeSpan"/>。
		///	<code>原型：inline TimeSpan &amp;Subtract(TimeSpan ts);</code>
		///	</summary>
 		///	<param name="ts">要减去的 <see cref="TimeSpan"/>。</param> 
		///	<returns>值为此实例的值减去 ts 的值后所得结果的 <see cref="TimeSpan"/></returns>
        inline TimeSpan &Subtract(TimeSpan ts)
		{
			this->_ticks-=ts.getTotalTicks();
			return *this;
		};
   		///	<summary>
		///	获取时间间隔的各时间表示部分。
		///	<code>原型：inline void getTimsSpanParts(int *day,int *hour,int *minute,int*second,
		///	                                         int * millis=NULL,int * usec=NULL);</code>
		///	</summary>
 		///	<param name="day">天的返回值。</param> 
 		///	<param name="hour">小时的返回值。</param> 
 		///	<param name="minute">分钟的返回值。</param> 
 		///	<param name="second">秒的返回值。</param> 
 		///	<param name="millis">毫秒的返回值。</param> 
 		///	<param name="usec">秒的返回值。</param> 
		inline void getTimsSpanParts(int *day,int *hour,int *minute,int*second,int * millis=NULL,int * usec=NULL)
		{
			if(this->_ticks==0)
			{
				if(day)*day=0;if(hour)*hour=0;if(minute)*minute=0;if(second)*second=0;if(millis)*millis=0;return;
			};
			if(day)*day=(int)(this->_ticks/this->TicksPerDay);
			if(hour)*hour= int((this->_ticks%this->TicksPerDay)/this->TicksPerHour);
			if(minute)*minute= int((this->_ticks % this->TicksPerHour)/this->TicksPerMinute);
			if(second)*second= int((this->_ticks % TicksPerMinute)/this->TicksPerSecond);
			if(millis)*millis= int((this->_ticks % this->TicksPerSecond)/this->TicksPerMillisecond);
			if(usec)*usec= int(this->_ticks % this->TicksPerMillisecond);
		}
   		///	<summary>
		///	返回此实例的值的字符串表示形式。
		///	<code>原型：inline string ToString();</code>
		///	</summary>
		///	<returns>此实例的字符串表示形式,只到毫秒部分
		///     表示此实例的值的字符串。返回值形式如下： [-][d.]hh:mm:ss[.ff] 方括号（“[”和“]”）中的项是可选的，冒号和句号（“:”和“.”）是原义字符，其他项如下。项
		///     说明 "-" 可选的负号，指示负时间 “d” 可选的天数 “hh” 小时，范围从 0 到 23 “mm” 分钟，范围从 0 到 59 “ss” 秒，范围从
		///     0 到 59 “ff” 可选的秒的小数部分，有 3 个小数位，精确到毫秒。
		///</returns>
		inline string ToString()
		{
			string _result;
			char b[40];
			int l=0;
			int v[5];
			getTimsSpanParts(v,v+1,v+2,v+3,v+4);
			v[0]=v[0];
			v[1]=abs(v[1]);
			v[2]=abs(v[2]);
			v[3]=abs(v[3]);
			v[4]=abs(v[4]);
			if(this->_ticks!=0)
			{
				if(v[0]!=0 && v[4]!=0)
				{
					l=sprintf(b,"%d.%02d:%02d:%02d.%03d",v[0],v[1],v[2],v[3],v[4]);
				}
				else if(v[0]!=0 && v[4]==0)
				{
					l=sprintf(b,"%d.%02d:%02d:%02d",v[0],v[1],v[2],v[3]);
				}
				else if(v[0]==0 && v[4]!=0)
				{
					l=sprintf(b,"%02d:%02d:%02d.%03d",v[1],v[2],v[3],v[4]);
				}
				else if(v[0]==0 && v[4]==0)
				{
					l=sprintf(b,"%02d:%02d:%02d",v[1],v[2],v[3]);
				}
				_result=b;
			}
			else
			{
				_result= "00:00:00";
			}
			return _result;
		}
   		///	<summary>
		///	从字符串中指定的时间间隔构造新的<see cref="TimeSpan"/>对象。
		///	<code>原型：inline static TimeSpan Parse(const string&amp; s);</code>
		///	</summary>
		///	<remarks>按位解析</remarks>
 		///	<param name="s">指定时间间隔的字符串。</param> 
		///	<returns>与s值相应的 <see cref="TimeSpan"/></returns>
 		/// <exception cref="Exception">格式不正确，解析错误时抛出</exception>
		inline static TimeSpan Parse(const string& s)
		{
			StringParser parser2 = StringParser();
			return TimeSpan(parser2.Parse(s));
		}
   		///	<summary>
		///	从字符串中指定的时间间隔构造新的<see cref="TimeSpan"/>对象。
		///	<code>原型：inline static TimeSpan Parse2(const string&amp; s);</code>
		///	</summary>
		/// <exception cref="Exception">格式不正确，解析错误时抛出</exception>
		///	<remarks>使用格式化的快速的sscanf输入解析值</remarks>
 		///	<param name="s">指定时间间隔的字符串。</param> 
		///	<returns>与s值相应的 <see cref="TimeSpan"/></returns>
		inline static TimeSpan Parse2(string& s)
		{
			TimeSpan tp;
			celerityParse::Parse(tp,s);
			return tp;
		}
   		///	<summary>
		///	从字符串中指定的时间间隔构造新的<see cref="TimeSpan"/>对象。
		///	<code>原型：inline static void Parse2(TimeSpan &amp;result,string&amp; s);</code>
		///	</summary>
		///	<remarks>使用格式化的快速的sscanf输入解析值</remarks>
		///	<param name="result">返回与s值相应的 <see cref="TimeSpan"/>。</param> 
 		///	<param name="s">指定时间间隔的字符串。</param> 
 		/// <exception cref="Exception">格式不正确，解析错误时抛出</exception>
		inline static void Parse2(TimeSpan &result,string& s)
		{
			celerityParse::Parse(result,s);
		}
   		///	<summary>
		///	从字符串中指定的时间间隔构造新的<see cref="TimeSpan"/>对象。
		///	<code>原型：inline static void Parse(TimeSpan &amp;result,string&amp; s);</code>
		///	</summary>
		///	<remarks>使用格式化的快速的sscanf输入解析值</remarks>
 		///	<param name="result">此方法返回时，包含表示由 s 指定的时间间隔的对象；或者如果转换失败，则包含 Common.TimeSpan.Zero。该参数未经初始化即被传递。。</param> 
 		///	<param name="s">指定时间间隔的字符串</param> 
		///	<returns>如果 s 转换成功，则为 true；否则为 false。如果 s 参数为null，格式无效， 表示的时间间隔小于 Common.TimeSpan.MinValue
        ///     或大于 Common.TimeSpan.MaxValue，或者天、小时、分钟或者秒分量中至少有一个超出其有效范围，则此运算返回 false。 </returns>
        inline static bool Parse(TimeSpan &result,const string& s)
		{
			long long num;
			StringParser parser2 = StringParser();
			String temp=s;
			if (parser2.TryParse(temp, num))
			{
				result = TimeSpan(num);
				return true;
			}
			result = Zero;
			return false;
		};


		//
		//摘要：
		//		[-][d.]hh:mm:ss[.ff]
		protected:  
			class celerityParse
			{
				inline static char NextNonDigit(const char * p,int pos,int len)
				{
					for (int  i = pos; (i < len); i++)
					{
						if ((p[i] < '0') || (p[i] > '9'))return p[i];
					}
					return '\0';
				}
				public:
				inline static void Parse(TimeSpan & res,string& s)
				{
					int day=0,hour=0,minute=0,second=0,millis=0,len=0;
					String::Trim(s);
					bool  flag = false;
					if(s[0]=='-')flag = true;
					const char * tp=s.c_str();
					if(flag)tp++;
					char c=NextNonDigit(tp,0,s.size());
					if(c=='.')
					{
						len=sscanf(tp, "%d.%d:%d:%d.%d", &day,&hour,&minute,&second,&millis);
						if(len<4)EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"dd.hh:mi:ss.ms\"字符串");
					}
					else if(c==':')
					{
						len=sscanf(tp, "%d:%d:%d.%d", &hour,&minute,&second,&millis);
						if(len<3)EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"dd.hh:mi:ss.ms\"字符串");
					}
					else
					{
						EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"dd.hh:mi:ss.ms\"字符串");
					}
					res=TimeSpan(day, hour, minute, second, millis,0);
					if(flag)res=res.Duration();
				}
			};

			class StringParser
		{
		protected: enum ParseError
			{
				ArgumentNull = 4,
				Format = 1,
				Overflow = 2,
				OverflowHoursMinutesSeconds = 3
			};
		protected:
			string str;
			char ch;
			int pos;
			int len;
			ParseError error;
		public:
			inline void NextChar()
			{
				if (this->pos < this->len)
				{
					this->pos++;
				}
				this->ch = ((this->pos < this->len) ? this->str[this->pos] : '\0');
			}
			inline char NextNonDigit()
			{
				for (int  i = this->pos; (i < this->len); i++)
				{
					char  ch = this->str[i];
					if ((ch < '0') || (ch > '9'))
					{
						return ch;
					}
				}
				return '\0';
			}
			inline long long Parse(const string &s)
			{
				long long  num;
				if (this->TryParse(s, num))
				{
					return num;
				}
				switch (this->error)
				{
					case Format:
					{
						EXP("Format_InvalidString");
					}
					case Overflow:
					{
						EXP("Overflow_TimeSpanTooLong");
					}
					case OverflowHoursMinutesSeconds:
					{
 						EXP("Overflow_TimeSpanElementTooLarge");
					}
					case ArgumentNull:
					{
 						EXP("ArgumentNull");
					}
				}
				return 0;
			}
			inline bool ParseInt(int max,int &i)
			{
				i = 0;
				int  pos = this->pos;
				while (((this->ch >= '0') && (this->ch <= '9')))
				{
					if ((((long) i) & 0xf0000000) != 0)
					{
						this->error = Overflow;
						return false;
					}
					i = (((i * 10) + this->ch) - 0x30);
					if (i < 0)
					{
						this->error = Overflow;
						return false;
					}
					this->NextChar();
				}
				if (pos == this->pos)
				{
					this->error = Format;
					return false;
				}
				if (i > max)
				{
					this->error = Overflow;
					return false;
				}
				return true;
			}


			inline bool ParseTime(long long &time)
			{
				int  i;
				time = 0;
				if (!this->ParseInt(0x17, i))
				{
					if (this->error == Overflow)
					{
						this->error = OverflowHoursMinutesSeconds;
					}
					return false;
				}
				time = (i * TimeSpan::TicksPerHour);
				if (this->ch != ':')
				{
					this->error = Format;
					return false;
				}
				this->NextChar();
				if (!this->ParseInt(0x3b,  i))
				{
					if (this->error == Overflow)
					{
						this->error = OverflowHoursMinutesSeconds;
					}
					return false;
				}
				time += (i * TimeSpan::TicksPerMinute);
				if (this->ch == ':')
				{
					this->NextChar();
					if (this->ch != '.')
					{
						if (!this->ParseInt(0x3b,  i))
						{
							if (this->error == Overflow)
							{
								this->error = OverflowHoursMinutesSeconds;
							}
							return false;
						}
						time += (i * TimeSpan::TicksPerSecond);
					}
					if (this->ch == '.')
					{
						this->NextChar();
						int  num2 = TimeSpan::TicksPerSecond;
						while ((((num2 > 1) && (this->ch >= '0')) && (this->ch <= '9')))
						{
							num2 /= 10;
							time += ((this->ch - '0') * num2);
							this->NextChar();
						}
					}
				}
				return true;
			}

			inline void SkipBlanks()
			{
				while (((this->ch == ' ') || (this->ch == '\t')))
				{
					this->NextChar();
				}
			}
			inline bool TryParse(const string &s,long long &value)
			{
				long long  time;
				value = 0;
				if (s.empty())
				{
					this->error = ArgumentNull;
					return false;
				}
				this->str = s;
				this->len = s.size();
				this->pos = -1;
				this->NextChar();
				this->SkipBlanks();
				bool  flag = false;
				if (this->ch == '-')
				{
					flag = true;
					this->NextChar();
				}
				if (this->NextNonDigit() == ':')
				{
					if (!this->ParseTime(time))
					{
						return false;
					}
				}
				else
				{
					int  i;
					if (!this->ParseInt(0xa2e3ff,  i))
					{
						return false;
					}
					time = (i * TimeSpan::TicksPerDay);
					if (this->ch == '.')
					{
						long long  num3;
						this->NextChar();
						if (!this->ParseTime( num3))
						{
							return false;
						}
						time += num3;
					}
					else
					{
						return false;
					}
				}
				if (flag)
				{
					time = -time;
					if (time > 0)
					{
						this->error = Overflow;
						return false;
					}
				}
				else if (time < 0)
				{
					this->error = Overflow;
					return false;
				}
				this->SkipBlanks();
				if (this->pos < this->len)
				{
					this->error = Format;
					return false;
				}
				value = time;
				return true;
			}
		};
	};
	inline ostream& operator<<(ostream& target, TimeSpan dt)
	{
		target << dt.ToString();
		return target;
	}



}
#endif

