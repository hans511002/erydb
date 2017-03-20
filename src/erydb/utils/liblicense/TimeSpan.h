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
	///	��ʾһ��ʱ������
	///	</summary>
	///	<remarks>
	///	��ȷ�ı�ʾһ��ʱ��������ȷ��΢�롣
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class TimeSpan
	{
	public:
		///	<summary>
		///	ʱ��Ƭ�Ŀ̶�����΢������
		///	</summary>
		long long _ticks;
		///	<summary>
		///	һ΢����ڶ����졣���ֶ�Ϊ������
		///	</summary>
		static const double DaysPerTicks;
		///	<summary>
		///	һ΢����ڶ���Сʱ�����ֶ�Ϊ������
		///	</summary>
		static const double HoursPerTicks;
		///	<summary>
		///	һ΢����ڶ��ٷ����������ֶ�Ϊ������
		///	</summary>
		static const double MinutesPerTicks;
		///	<summary>
		///	һ΢����ڶ����롣���ֶ�Ϊ������
		///	</summary>
		static const double SecondsPerTicks;
		///	<summary>
		///	�������������ֶ�Ϊ������
		///	</summary>
		static const long long MaxMillis ;
		///	<summary>
		///	������������ֶ�Ϊ������
		///	</summary>
		static const long long MaxSeconds ;
		///	<summary>
		///	��ʾһ���еĿ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const int MillisPerDay ;
		///	<summary>
		///	��ʾ 1 Сʱ�Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const int MillisPerHour ;
		///	<summary>
		///	��ʾ 1 ���ӵĿ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const int MillisPerMinute ;
		///	<summary>
		///	��ʾ 1 ��Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const int MillisPerSecond ;

		///	<summary>
		///	��ʾ 1 ����Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const long long  TicksPerMillisecond ;
		///	<summary>
		///	��ʾ 1 ��Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const long long  TicksPerSecond ;
		///	<summary>
		///	��ʾ 1 ���ӵĿ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const long long  TicksPerMinute ;
		///	<summary>
		///	��ʾ 1 Сʱ�Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const long long  TicksPerHour ;
		///	<summary>
		///	��ʾ 1 ��Ŀ̶���(΢��)�����ֶ�Ϊ������
		///	</summary>
		static const long long  TicksPerDay ;
		///	<summary>
		///	��С�����������ֶ�Ϊ������
		///	</summary>
		static const long long MinMilliSeconds ;
		///	<summary>
		///	��С���������ֶ�Ϊ������
		///	</summary>
		static const long long MinSeconds ;
		///	<summary>
		///	��ʾ����<see cref="TimeSpan"/>�����ֶ�Ϊ������
		///	</summary>
        static  const TimeSpan MaxValue;
		///	<summary>
		///	��ʾ��С��<see cref="TimeSpan"/>�����ֶ�Ϊ������
		///	</summary>
        static  const TimeSpan MinValue;
		///	<summary>
		///	��ʾ��<see cref="TimeSpan"/> ֵ�����ֶ�Ϊ������
		///	</summary>
        static const  TimeSpan Zero;


	public:
		///	<summary>
		///	��ʱ�䲿��ת��Ϊʱ��̶�����΢�룩
		///	<code>ԭ�ͣ�inline static unsigned long long TimeToTicks(int hour, int minute, int second);</code>
		///	</summary>
		///	<param name="hour">Сʱ</param>
		///	<param name="minute">����</param>
		///	<param name="second">��</param>
		///	<returns>���ض�Ӧ�Ŀ̶�����΢������</returns>
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
		///	���µ� <see cref="TimeSpan"/> ��ʼ��Ϊָ���Ŀ̶�����΢�룩��
		///	<code>ԭ�ͣ�TimeSpan(long long ticks=0);</code>
		///	</summary>
		///	<param name="ticks">�̶�����΢���������� 1 ΢��Ϊ��λ��ʾ��ʱ��Ρ�</param>
		TimeSpan(long long ticks=0)
		{
			this->_ticks=ticks;
		}
		///	<summary>
		///	���µ� <see cref="TimeSpan"/> ��ʼ��Ϊָ���Ŀ̶�����΢�룩��
		///	<code>ԭ�ͣ�TimeSpan(int millis);</code>
		///	</summary>
		///	<param name="millis">�̶�����΢���������� 1 ΢��Ϊ��λ��ʾ��ʱ��Ρ�</param>
		TimeSpan(int millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	���µ� <see cref="TimeSpan"/> ��ʼ��Ϊָ���Ŀ̶�����΢�룩��
		///	<code>ԭ�ͣ�TimeSpan(long millis);</code>
		///	</summary>
		///	<param name="millis">�̶�����΢���������� 1 ΢��Ϊ��λ��ʾ��ʱ��Ρ�</param>
		TimeSpan(long millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	���µ� <see cref="TimeSpan"/> ��ʼ��Ϊָ���Ŀ̶�����΢�룩��
		///	<code>ԭ�ͣ�TimeSpan(unsigned long long millis);</code>
		///	</summary>
		///	<param name="millis">�̶�����΢���������� 1 ΢��Ϊ��λ��ʾ��ʱ��Ρ�</param>
		TimeSpan(unsigned long long millis)
		{
			this->_ticks=millis;
		}
		///	<summary>
		///	��ָ����ʱ�������΢���ʼ��<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�TimeSpan(int hours, int minutes, int seconds, int milliseconds,int ticks);</code>
		///	</summary>
		///	<param name="hours">Сʱ��</param>
		///	<param name="minutes">���ӡ�</param>
		///	<param name="seconds">�롣</param>
		///	<param name="milliseconds">���롣</param>
		///	<param name="ticks">΢�롣</param> 
		TimeSpan(int hours, int minutes, int seconds, int milliseconds,int ticks)
		{
			this->_ticks=hours * TicksPerHour + minutes * TicksPerMinute + seconds * TicksPerSecond+milliseconds* this->TicksPerMillisecond + ticks;
		}
		///	<summary>
		///	��ָ����ʱ�������΢���ʼ��<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�TimeSpan(int days,int hours, int minutes, int seconds, int milliseconds,int ticks);</code>
		///	</summary>
		///	<param name="days">�졣</param>
		///	<param name="hours">Сʱ��</param>
		///	<param name="minutes">���ӡ�</param>
		///	<param name="seconds">�롣</param>
		///	<param name="milliseconds">���롣</param>
		///	<param name="ticks">΢�롣</param> 
		TimeSpan(int days, int hours, int minutes, int seconds, int milliseconds,int ticks)
		{
			this->_ticks=days * TicksPerDay +hours * TicksPerHour + minutes * TicksPerMinute + seconds * TicksPerSecond+milliseconds* this->TicksPerMillisecond + ticks;
		}

        // ���ƿռ����������Ԫ����
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
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ����������
		///	<code>ԭ�ͣ�inline int getDays();</code>
		///	</summary>
		///	<returns>��ʵ�����������֡�����ֵ����������Ҳ�����Ǹ�����</returns>
		inline int getDays()
		{
			if(this->_ticks==0)return 0;
			return (this->_ticks/this->TicksPerDay);
		}
		///	<summary>
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ����Сʱ����
		///	<code>ԭ�ͣ�inline int getHours();</code>
		///	</summary>
		///	<returns>��ǰ<see cref="TimeSpan"/>�ṹ��Сʱ����������ֵ�ķ�ΧΪ -23 �� 23��</returns>
		inline int getHours()
		{
			if(this->_ticks==0)return 0;
			return	int((this->_ticks%this->TicksPerDay)/this->TicksPerHour);
		} 
		///	<summary>
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ������������
		///	<code>ԭ�ͣ�inline int getMinutes();</code>
		///	</summary>
		///	<returns>��ǰ<see cref="TimeSpan"/>�ṹ�ķ��ӷ���������ֵ�ķ�ΧΪ -59 �� 59��</returns>
		inline int getMinutes()
		{
			if(this->_ticks==0)return 0;
			return int((this->_ticks % this->TicksPerHour)/this->TicksPerMinute);
		} 
		///	<summary>
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ����������
		///	<code>ԭ�ͣ�inline int getSeconds();</code>
		///	</summary>
		///	<returns>��ǰ<see cref="TimeSpan"/>�ṹ�������������ֵ�ķ�ΧΪ -59 �� 59��</returns>
		inline int getSeconds()
		{
			if(this->_ticks==0)return 0;
			return int(this->_ticks/this->TicksPerSecond) % 60;
		}
		///	<summary>
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ����������
		///	<code>ԭ�ͣ�inline int getSeconds();</code>
		///	</summary>
		///	<returns>��ǰ<see cref="TimeSpan"/>�ṹ�ĺ������������ֵ�ķ�ΧΪ -999 �� 999��</returns>
		inline int getMilliseconds()
		{
			if(this->_ticks==0)return 0;
			return int((this->_ticks % this->TicksPerSecond)/this->TicksPerMillisecond);
		}
		///	<summary>
		///	��ȡ�ɵ�ǰ <see cref="TimeSpan"/> �ṹ��ʾ��΢������
		///	<code>ԭ�ͣ�inline int getUsec();</code>
		///	</summary>
		///	<returns>��ǰ<see cref="TimeSpan"/>�ṹ��ʾ��΢����������ֵ�ķ�ΧΪ -999 �� 999��</returns>
		inline int getUsec()
		{
			if(this->_ticks==0)return 0;
			return int(this->_ticks % this->TicksPerMillisecond);
		}
		///	<summary>
		///	��ȡ�������������С�����ֱ�ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalDays();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ��������</returns>
		inline double getTotalDays()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerDay;;
		}
		///	<summary>
		///	��ȡ����Сʱ����Сʱ��С�����ֱ�ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalHours();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ����Сʱ��</returns>
		inline double getTotalHours()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerHour;
		}
 		///	<summary>
		///	��ȡ�����������ͷ��ӵ�С�����ֱ�ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalMinutes();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ���ܷ�����</returns>
		inline double getTotalMinutes()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerMinute;;
		}
  		///	<summary>
		///	��ȡ�������������С�����ֱ�ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalSeconds();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ��������</returns>
		inline double getTotalSeconds()
		{
			if(this->_ticks==0)return 0;
			return (double)this->_ticks/(double)this->TicksPerSecond;
		}
  		///	<summary>
		///	��ȡ�����������ͺ����С�����ֱ�ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalMilliseconds();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ���ܺ�����</returns>
		inline double getTotalMilliseconds()
		{
			return (double)this->_ticks/(double)this->TicksPerMillisecond;
		}
  		///	<summary>
		///	��ȡ����΢������ʾ�ĵ�ǰ <see cref="TimeSpan"/> �ṹ��ֵ��
		///	<code>ԭ�ͣ�inline double getTotalTicks();</code>
		///	</summary>
		///	<returns>��ʵ����ʾ����΢����</returns>
		inline long long getTotalTicks()
		{
			return this->_ticks;
		}
  		///	<summary>
		///	��ָ���� <see cref="TimeSpan"/> ��ӵ���ʵ���С�
		///	<code>ԭ�ͣ�inline TimeSpan &amp;Add(TimeSpan ts);</code>
		///	</summary>
		///	<param name="ts">Ҫ��ӵ�<see cref="TimeSpan"/>����</param>
		///	<returns>��ǰʵ������ֵΪ��ʵ����ֵ�� ts ��ֵ֮��</returns>
		inline TimeSpan &Add(TimeSpan ts)
		{
			this->_ticks+=ts.getTotalTicks();
			return *this;
		}
  		///	<summary>
		///	�Ƚ����� <see cref="TimeSpan"/> ֵ������һ��ָʾ����֮���ϵ��������
		///	<code>ԭ�ͣ�inline static int Compare(TimeSpan t1, TimeSpan t2);</code>
		///	</summary>
		///	<param name="t1">ʱ����һ<see cref="TimeSpan"/>����</param>
		///	<param name="t2">ʱ������<see cref="TimeSpan"/>����</param>
		///	<returns>ֵ����: -1 t1 С�� t2, 0 t1 ���� t2,1 t1 ���� t2</returns>
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
		///	����ʵ����ָ�� <see cref="TimeSpan"/> ������бȽϲ����ض������ֵ��ָʾ��
		///	<code>ԭ�ͣ�inline int Compare(TimeSpan value);</code>
		///	</summary>
		///	<param name="value">ʱ����һ<see cref="TimeSpan"/>����</param> 
		///	<returns>�з������֣�ָʾ��ʵ���� value �����ֵ��ֵ˵��: ������ ��ʵ��С�� value�� �� ��ʵ������ value�� ������ ��ʵ������ value��</returns>
		inline int CompareTo(TimeSpan value){return TimeSpan::Compare(*this, value);};
   		///	<summary>
		///	�����µ� <see cref="TimeSpan"/> ������ֵ�ǵ�ǰ <see cref="TimeSpan"/> ����ľ���ֵ����
		///	<code>ԭ�ͣ�inline TimeSpan Duration();</code>
		///	</summary>
 		///	<returns>�µ� <see cref="TimeSpan"/>����ֵ�ǵ�ǰ <see cref="TimeSpan"/> ����ľ���ֵ</returns>
        inline TimeSpan Duration()
		{
			if(this->_ticks>0)
				return TimeSpan(this->_ticks);
			else
				return TimeSpan(0-this->_ticks);
		};
//**********************************************                                    
   		///	<summary>
		///	����һ��ֵ����ֵָʾ��ʵ���Ƿ���ָ���� <see cref="TimeSpan"/> ������ȡ�
		///	<code>ԭ�ͣ�inline bool Equals(TimeSpan obj);</code>
		///	</summary>
 		///	<param name="obj">ʱ����<see cref="TimeSpan"/>����</param>
		///	<returns>��� obj ��ʾ��ʱ�������ʵ����ͬ����Ϊ true������Ϊ false��</returns>
		inline bool Equals(TimeSpan obj){return this->_ticks==obj.getTotalTicks();};
   		///	<summary>
		///	����һ��ֵ����ֵָʾ <see cref="TimeSpan"/> ������ָ��ʵ���Ƿ���ȡ�
		///	<code>ԭ�ͣ�inline static bool Equals(TimeSpan t1, TimeSpan t2);</code>
		///	</summary>
 		///	<param name="t1">ʱ����һ<see cref="TimeSpan"/>����</param>
 		///	<param name="t2">ʱ������<see cref="TimeSpan"/>����</param>
		///	<returns>��� t1 �� t2 ��ֵ��ȣ���Ϊ true������Ϊ false��</returns>
		inline static bool Equals(TimeSpan t1, TimeSpan t2){return t1.getTotalTicks()==t2.getTotalTicks();};
   		///	<summary>
		///	���ر�ʾָ�������� <see cref="TimeSpan"/> ���ж�������ָ����ȷ����ӽ���΢�롣
		///	<code>ԭ�ͣ�inline static TimeSpan FromDays(double value);</code>
		///	</summary>
 		///	<param name="value">��������ȷ����ӽ���΢�롣</param> 
		///	<returns>��ʾ value �� <see cref="TimeSpan"/></returns>
        inline static TimeSpan FromDays(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerDay);
			return TimeSpan(l);
		};
   		///	<summary>
		///	���ر�ʾָ��Сʱ���� <see cref="TimeSpan"/> ���ж�Сʱ����ָ����ȷ����ӽ���΢�롣
		///	<code>ԭ�ͣ�inline static TimeSpan FromHours(double value);</code>
		///	</summary>
 		///	<param name="value">Сʱ������ȷ����ӽ���΢�롣</param> 
		///	<returns>��ʾ value �� <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromHours(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerHour);
			return TimeSpan(l);
		}
   		///	<summary>
		///	���ر�ʾָ��΢������ <see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�inline static TimeSpan FromMilliseconds(long long value);</code>
		///	</summary>
 		///	<param name="value">΢������</param> 
		///	<returns>��ʾ value �� <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromMilliseconds(long long value)
		{
			return TimeSpan(value);
		}
   		///	<summary>
		///	���ر�ʾָ���������� <see cref="TimeSpan"/>,���жԷ�������ָ����ȷ����ӽ���΢�롣
		///	<code>ԭ�ͣ�inline static TimeSpan FromMinutes(double value);</code>
		///	</summary>
 		///	<param name="value">����������ȷ����ӽ���΢�롣</param> 
		///	<returns>��ʾ value �� <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromMinutes(double value)
		{
			long long  l=(long long)ceil(value*TimeSpan::TicksPerMinute);
			return TimeSpan(l);
		}
   		///	<summary>
		///	���ر�ʾָ�������� <see cref="TimeSpan"/>,���жԷ�������ָ����ȷ����ӽ���΢�롣
		///	<code>ԭ�ͣ�inline static TimeSpan FromSeconds(double value);</code>
		///	</summary>
 		///	<param name="value">��������ȷ����ӽ���΢�롣</param> 
		///	<returns>��ʾ value �� <see cref="TimeSpan"/></returns>
		inline static TimeSpan FromSeconds(double value)
		{
			long long l=(long long)ceil(value*TimeSpan::TicksPerSecond);
			return TimeSpan(l);
		}
   		///	<summary>
		///	������ֵΪ��ʵ�����෴ֵ�� <see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�inline TimeSpan Negate();</code>
		///	</summary>
		///	<returns>���ʵ������ֵ��ͬ�������෴</returns>
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
		///	�Ӵ�ʵ���м�ȥָ���� <see cref="TimeSpan"/>��
		///	<code>ԭ�ͣ�inline TimeSpan &amp;Subtract(TimeSpan ts);</code>
		///	</summary>
 		///	<param name="ts">Ҫ��ȥ�� <see cref="TimeSpan"/>��</param> 
		///	<returns>ֵΪ��ʵ����ֵ��ȥ ts ��ֵ�����ý���� <see cref="TimeSpan"/></returns>
        inline TimeSpan &Subtract(TimeSpan ts)
		{
			this->_ticks-=ts.getTotalTicks();
			return *this;
		};
   		///	<summary>
		///	��ȡʱ�����ĸ�ʱ���ʾ���֡�
		///	<code>ԭ�ͣ�inline void getTimsSpanParts(int *day,int *hour,int *minute,int*second,
		///	                                         int * millis=NULL,int * usec=NULL);</code>
		///	</summary>
 		///	<param name="day">��ķ���ֵ��</param> 
 		///	<param name="hour">Сʱ�ķ���ֵ��</param> 
 		///	<param name="minute">���ӵķ���ֵ��</param> 
 		///	<param name="second">��ķ���ֵ��</param> 
 		///	<param name="millis">����ķ���ֵ��</param> 
 		///	<param name="usec">��ķ���ֵ��</param> 
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
		///	���ش�ʵ����ֵ���ַ�����ʾ��ʽ��
		///	<code>ԭ�ͣ�inline string ToString();</code>
		///	</summary>
		///	<returns>��ʵ�����ַ�����ʾ��ʽ,ֻ�����벿��
		///     ��ʾ��ʵ����ֵ���ַ���������ֵ��ʽ���£� [-][d.]hh:mm:ss[.ff] �����ţ���[���͡�]�����е����ǿ�ѡ�ģ�ð�ź;�ţ���:���͡�.������ԭ���ַ������������¡���
		///     ˵�� "-" ��ѡ�ĸ��ţ�ָʾ��ʱ�� ��d�� ��ѡ������ ��hh�� Сʱ����Χ�� 0 �� 23 ��mm�� ���ӣ���Χ�� 0 �� 59 ��ss�� �룬��Χ��
		///     0 �� 59 ��ff�� ��ѡ�����С�����֣��� 3 ��С��λ����ȷ�����롣
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
		///	���ַ�����ָ����ʱ���������µ�<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�inline static TimeSpan Parse(const string&amp; s);</code>
		///	</summary>
		///	<remarks>��λ����</remarks>
 		///	<param name="s">ָ��ʱ�������ַ�����</param> 
		///	<returns>��sֵ��Ӧ�� <see cref="TimeSpan"/></returns>
 		/// <exception cref="Exception">��ʽ����ȷ����������ʱ�׳�</exception>
		inline static TimeSpan Parse(const string& s)
		{
			StringParser parser2 = StringParser();
			return TimeSpan(parser2.Parse(s));
		}
   		///	<summary>
		///	���ַ�����ָ����ʱ���������µ�<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�inline static TimeSpan Parse2(const string&amp; s);</code>
		///	</summary>
		/// <exception cref="Exception">��ʽ����ȷ����������ʱ�׳�</exception>
		///	<remarks>ʹ�ø�ʽ���Ŀ��ٵ�sscanf�������ֵ</remarks>
 		///	<param name="s">ָ��ʱ�������ַ�����</param> 
		///	<returns>��sֵ��Ӧ�� <see cref="TimeSpan"/></returns>
		inline static TimeSpan Parse2(string& s)
		{
			TimeSpan tp;
			celerityParse::Parse(tp,s);
			return tp;
		}
   		///	<summary>
		///	���ַ�����ָ����ʱ���������µ�<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�inline static void Parse2(TimeSpan &amp;result,string&amp; s);</code>
		///	</summary>
		///	<remarks>ʹ�ø�ʽ���Ŀ��ٵ�sscanf�������ֵ</remarks>
		///	<param name="result">������sֵ��Ӧ�� <see cref="TimeSpan"/>��</param> 
 		///	<param name="s">ָ��ʱ�������ַ�����</param> 
 		/// <exception cref="Exception">��ʽ����ȷ����������ʱ�׳�</exception>
		inline static void Parse2(TimeSpan &result,string& s)
		{
			celerityParse::Parse(result,s);
		}
   		///	<summary>
		///	���ַ�����ָ����ʱ���������µ�<see cref="TimeSpan"/>����
		///	<code>ԭ�ͣ�inline static void Parse(TimeSpan &amp;result,string&amp; s);</code>
		///	</summary>
		///	<remarks>ʹ�ø�ʽ���Ŀ��ٵ�sscanf�������ֵ</remarks>
 		///	<param name="result">�˷�������ʱ��������ʾ�� s ָ����ʱ�����Ķ��󣻻������ת��ʧ�ܣ������ Common.TimeSpan.Zero���ò���δ����ʼ���������ݡ���</param> 
 		///	<param name="s">ָ��ʱ�������ַ���</param> 
		///	<returns>��� s ת���ɹ�����Ϊ true������Ϊ false����� s ����Ϊnull����ʽ��Ч�� ��ʾ��ʱ����С�� Common.TimeSpan.MinValue
        ///     ����� Common.TimeSpan.MaxValue�������졢Сʱ�����ӻ����������������һ����������Ч��Χ��������㷵�� false�� </returns>
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
		//ժҪ��
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
						if(len<4)EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"dd.hh:mi:ss.ms\"�ַ���");
					}
					else if(c==':')
					{
						len=sscanf(tp, "%d:%d:%d.%d", &hour,&minute,&second,&millis);
						if(len<3)EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"dd.hh:mi:ss.ms\"�ַ���");
					}
					else
					{
						EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"dd.hh:mi:ss.ms\"�ַ���");
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

