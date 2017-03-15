// ==============================================================
//progame      Common functions
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

#include "LicCommon.h"
#include "Array.h"
#include "Enums.h"
#include "Convert.h"  

#include "Functions.h"
#include "DateTimeFun.h"
#include "TimeSpan.h"
#include "DateTime.h"

namespace Common
{
#ifdef __Common_fileData_H__
	int fileData::groupSize=7777777;
	char fileData::staticDcp[4096];
#endif
//DataTable static var //
#ifdef __Common_DataTable_H__
	String DataTable::dbStr;
	bool DataTable::stringObject=false;
#endif
//TimeSpan static const var //
#ifdef __Common_TimeSpan_H__
	//
	//һ������ڶ�����
	//
	const double TimeSpan::DaysPerTicks = 1.1574074074074074074074074074074e-11;
	//
	//һ������ڶ���Сʱ
	//
	const double TimeSpan::HoursPerTicks = 2.7777777777777777E-10;
	//
	//һ������ڶ��ٷ�����
	//
	const double TimeSpan::MinutesPerTicks = 1.6666666666666667E-8;
	//
	//��������
	//
	const double TimeSpan::SecondsPerTicks  = 0.000001;
	//
	//��������
	//
	const long long TimeSpan::MaxMillis=922337203685477ll ;
	//
	//�������						  15372286728
	//								  4294967296
	const long long TimeSpan::MaxSeconds = 922337203685ll;
	//
	//һ����ٺ���
	//
	const int TimeSpan::MillisPerDay = 0x5265c00;
	//
	//1Сʱ���ٺ���
	//
    const int TimeSpan::MillisPerHour = 0x36ee80;
	//
	//1���Ӷ��ٺ���
	//
    const int TimeSpan::MillisPerMinute = 0xea60;
	//
	//1����ٺ���
	//
    const int TimeSpan::MillisPerSecond = 0x3e8;

	const long long TimeSpan::TicksPerMillisecond = 0x3e8LL;
	const long long TimeSpan::TicksPerDay = 0x141DD76000LL;
	const long long TimeSpan::TicksPerHour = 0xD693A400LL;
	const long long TimeSpan::TicksPerMinute = 0x3938700LL;
	const long long TimeSpan::TicksPerSecond = 0xF4240LL;


	//
	//��С������
	//
	const long long TimeSpan::MinMilliSeconds = -922337203685477ll;
	//
	//��С����
	//
	const long long TimeSpan::MinSeconds = -922337203685ll;
    // ժҪ:
    //     ��ʾ���� Common.TimeSpan ֵ�����ֶ�Ϊֻ����
	const TimeSpan TimeSpan::MaxValue=TimeSpan(TimeSpan::MaxSeconds * TimeSpan::TicksPerSecond);
    //
    // ժҪ:
    //     ��ʾ��С�� Common.TimeSpan ֵ�����ֶ�Ϊֻ����
    const TimeSpan TimeSpan::MinValue=TimeSpan(TimeSpan::MinSeconds * TimeSpan::TicksPerSecond);
    //
    // ժҪ:
    //     ��ʾ�� Common.TimeSpan ֵ�����ֶ�Ϊֻ����
	const  TimeSpan TimeSpan::Zero=TimeSpan(0);
#endif

//DateTime const static var//
#ifdef __Common_DateTime_H__ 
	const int  DateTime::DaysToMonth365[]={ 0, 0x1f, 0x3b, 90, 120, 0x97, 0xb5, 0xd4, 0xf3, 0x111, 0x130, 0x14e, 0x16d };
	const int  DateTime::DaysToMonth366[]={ 0, 0x1f, 60, 0x5b, 0x79, 0x98, 0xb6, 0xd5, 0xf4, 0x112, 0x131, 0x14f, 0x16e };

	const string DateTime::WeekName[7][3]={{"������","Sunday","Sun"}
	,{"����һ","Monday","Mon"},{"���ڶ�","Tuesday","Tue"}
	,{"������","Wednesday","Wed"},{"������","Thursday","Thu"}
	,{"������","Friday","Fri"},{"������","Saturday","Sat"}};
	const string DateTime::MonthNames[13][3]={{"","",""}
	,{"1��","January","Jan"},{"2��","February","Feb"},{"3��","March","Mar"}
	,{"4��","April","Apr"},{"5��","May","May"},{"6��","June","June"}
	,{"7��","July","July"},{"8��","Aguest","Agu"},{"9��","September","Sep"}
	,{"10��","October","Oct"},{"11��","November","Nov"},{"12��","December","Dec"}};

	//string DateTime::_result="";
	//
	//ժҪ��
	//		UTC ��׼ʱ����ٺ���
	//	62135596800000
	//	62135596800000.0000
	const long long DateTime::MillesPerUTCSta=62135596800000ll;
	const long long DateTime::MillesPer2100Year=66238041600000ll;
	//
	//ժҪ��
	//		���Сʱ ������
	//	315537897599999	 
	const long long DateTime::MaxMillesSecond=315537897599999ll;
	const long long DateTime::MinMillesSecond=0;
	const long long DateTime::MaxTicks = 0x461040BCB9F1FFFLL;
	const long long DateTime::MinTicks = 0L;
	const long long DateTime::TicksCeiling = 0xF800000000000000LL;
	const long long DateTime::TicksMask = 0x7FFFFFFFFFFFFFFLL;
	const long long DateTime::TicksPerDay = 0x141DD76000LL;
	const long long DateTime::TicksPerHour = 0xD693A400LL;
	const long long DateTime::TicksPerMillisecond = 0x3e8LL;
	const long long DateTime::TicksPerMinute = 0x3938700LL;
	const long long DateTime::TicksPerSecond = 0xF4240LL;
	const long long DateTime::TicksPerUTCSta=0xDCBFFEFF2BC000LL;
	const long long DateTime::SecondPerUTCSta=0xE7791F700ll;

	//
	//ժҪ��
	//		100�������
	//	36524
	const int DateTime::DaysPer100Years = 0x8eac;
	//
	//ժҪ��
	//		400�������
	//	146097
    const int DateTime::DaysPer400Years = 0x23ab1;
	//
	//ժҪ��
	//		4�������
	//	1461
    const int DateTime::DaysPer4Years = 0x5b5;
	//
	//ժҪ��
	//		1�������
	//	365
    const int DateTime::DaysPerYear = 0x16d;
	//
	//ժҪ��
	//		һ����ٺ���
	//	86400000
	const int DateTime::MillisPerDay = 0x5265c00;
	//
	//ժҪ��
	//		1Сʱ���ٺ���
	//	3600000
    const int DateTime::MillisPerHour = 0x36ee80;
	//
	//ժҪ��
	//		1���Ӷ��ٺ���
	//	60000
    const int DateTime::MillisPerMinute = 0xea60;
	//
	//ժҪ��
	//		1����ٺ���
	//	1000
    const int DateTime::MillisPerSecond = 0x3e8;
//#if OSTYPE<=10
	const time_t DateTime::ts=time(NULL);
	const int DateTime::lHour=localtime(&ts)->tm_hour;		
	const TimeZone DateTime::localTimeZone =  TimeZone((lHour-gmtime(&ts)->tm_hour)>12?((lHour-gmtime(&ts)->tm_hour)-24):((lHour-gmtime(&ts)->tm_hour)<-12?((lHour-gmtime(&ts)->tm_hour)+24):(lHour-gmtime(&ts)->tm_hour)));
//#endif
	//
	//ժҪ��
	//		���ʱ��ֵ
	//	9999-12-31 23:59:59   //	315537897599999 ���� 
	const  DateTime  DateTime::MaxValue=DateTime(DateTime::MaxTicks);
	//
	//ժҪ��
	//		��Сʱ��ֵ
	//	0001-1-1 0:00:00  //	0 ����
	const  DateTime  DateTime::MinValue=DateTime(DateTime::MinTicks);
	//*****    DateTime    TimeSpan operator method          *                                    
	// ժҪ:
	//     ��һ��ָ�����ں�ʱ���ȥ��һ��ָ�������ں�ʱ��������ʱ������
	//
	// ����:
	//   d2:
	//     Common.DateTime����������
	//
	//   d1:
	//     Common.DateTime������������
	//
	// ���ؽ��:
	//     Common.TimeSpan������ d1 �� d2 ֮���ʱ�������� d1 ��ȥ d2��
	TimeSpan operator -(DateTime d1, DateTime d2)
	{
		return TimeSpan((d1.GetTicks()-d2.GetTicks()));
	}
	//
	// ժҪ:
	//     ��ָ�������ں�ʱ���ȥָ����ʱ�������������µ����ں�ʱ�䡣
	//
	// ����:
	//   d:
	//     Common.DateTime��
	//
	//   t:
	//     Common.TimeSpan��
	//
	// ���ؽ��:
	//     Common.DateTime������ֵΪ d ��ֵ��ȥ t ��ֵ��
	DateTime operator -(DateTime d, TimeSpan t)
	{
		return  DateTime(d._Ticks-t.getTotalTicks());
	}
	//
	// ժҪ:
	//     ȷ�� Common.DateTime ������ָ����ʵ���Ƿ񲻵ȡ�
	//
	// ����:
	//   d2:
	//     Common.DateTime��
	//
	//   d1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� d1 �� d2 ����ʾͬһ���ں�ʱ�䣬��Ϊ true������Ϊ false��
	bool operator !=(DateTime d1, DateTime d2)
	{
		if(d1.GetTicks()==d2.GetTicks())return false;
		else return true;
	}
	//
	// ժҪ:
	//     ��ָ����ʱ�����ӵ�ָ�������ں�ʱ���������µ����ں�ʱ�䡣
	//
	// ����:
	//   d:
	//     Common.DateTime��
	//
	//   t:
	//     Common.TimeSpan��
	//
	// ���ؽ��:
	//     Common.DateTime������ d �� t ֵ�ĺ͡�
	DateTime operator +(DateTime d, TimeSpan t)
	{
		return  DateTime(d._Ticks+t.getTotalTicks());
	}
	DateTime &operator +=(DateTime &d, TimeSpan t)
	{
		return d=DateTime(d._Ticks+t.getTotalTicks());
	}
	//
	// ժҪ:
	//     ȷ��ָ���� Common.DateTime �Ƿ�С����һ��ָ���� Common.DateTime��
	//
	// ����:
	//   t2:
	//     Common.DateTime��
	//
	//   t1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� t1 С�� t2����Ϊ true������Ϊ false��
	bool operator <(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()<t2.GetTicks()) ;
	}
	//
	// ժҪ:
	//     ȷ��ָ���� Common.DateTime �Ƿ�С�ڻ������һ��ָ���� Common.DateTime��
	//
	// ����:
	//   t2:
	//     Common.DateTime��
	//
	//   t1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� t1 С�ڻ���� t2����Ϊ true������Ϊ false��
	bool operator <=(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()<=t2.GetTicks());
	}
	//
	// ժҪ:
	//     ȷ�� Common.DateTime ������ָ����ʵ���Ƿ���ȡ�
	//
	// ����:
	//   d2:
	//     Common.DateTime��
	//
	//   d1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� d1 �� d2 ��ʾͬһ���ں�ʱ�䣬��Ϊ true������Ϊ false��
	bool operator ==(DateTime d1, DateTime d2)
	{
		return (d1.GetTicks()==d2.GetTicks());
	}
	//
	// ժҪ:
	//     ȷ��ָ���� Common.DateTime �Ƿ������һ��ָ���� Common.DateTime��
	//
	// ����:
	//   t2:
	//     Common.DateTime��
	//
	//   t1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� t1 ���� t2����Ϊ true������Ϊ false��
	bool operator >(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()>t2.GetTicks());
	}
	 
	//
	// ժҪ:
	//     ȷ��ָ���� Common.DateTime �Ƿ���ڻ������һ��ָ���� Common.DateTime��
	//
	// ����:
	//   t2:
	//     Common.DateTime��
	//
	//   t1:
	//     Common.DateTime��
	//
	// ���ؽ��:
	//     ��� t1 ���ڻ���� t2����Ϊ true������Ϊ false��
	bool operator >=(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()>=t2.GetTicks());
	}
#endif

//**************TimeSpan  ***********************************************                                    
#ifdef __Common_TimeSpan_H__
    // ժҪ:
    //     ������ֵΪָ��ʵ�����෴ֵ�� Common::TimeSpan��
    //
    // ����:
    //   t:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ���ʵ������ֵ��ͬ���������෴�� Common::TimeSpan��
    TimeSpan &operator -(TimeSpan &t)
	{
		t._ticks=0-t._ticks;
		return t;
	}
    //
    // ժҪ:
    //     ����һ��ָ���� Common::TimeSpan �м�ȥָ���� Common::TimeSpan��
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ֵΪ t1 ��ֵ��ȥ t2 ��ֵ�����ý���� TimeSpan��
    TimeSpan operator -(TimeSpan &t1, TimeSpan &t2)
	{
		return  TimeSpan(t1._ticks-t2._ticks);
	}
    TimeSpan &operator -=(TimeSpan &t1, TimeSpan &t2)
	{
		return t1=TimeSpan(t1._ticks-=t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾ���� Common::TimeSpan ʵ���Ƿ���ȡ�
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 �� t2 ��ֵ����ȣ���Ϊ true������Ϊ false��
    bool operator !=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks!=t2._ticks);
	}
    //
    // ժҪ:
    //     �������ָ���� Common::TimeSpan ʵ����
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ֵΪ t1 �� t2 ��ֵ֮�͵� Common::TimeSpan��
    TimeSpan operator +(TimeSpan &t1, TimeSpan &t2)
	{
		return  TimeSpan(t1._ticks+t2._ticks);
	}
    TimeSpan &operator +=(TimeSpan &t1, TimeSpan &t2)
	{
		return  t1=  TimeSpan(t1._ticks+t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾָ���� Common::TimeSpan �Ƿ�С����һ��ָ���� Common::TimeSpan��
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 ��ֵС�� t2 ��ֵ����Ϊ true������Ϊ false��
    bool operator <(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks<t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾָ���� Common::TimeSpan �Ƿ�С�ڻ������һ��ָ���� Common::TimeSpan��
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 ��ֵС�ڻ���� t2 ��ֵ����Ϊ true������Ϊ false��
    bool operator <=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks<=t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾ���� Common::TimeSpan ʵ���Ƿ���ȡ�
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 �� t2 ��ֵ��ȣ���Ϊ true������Ϊ false��
    bool operator ==(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks==t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾָ���� Common::TimeSpan �Ƿ������һ��ָ���� Common::TimeSpan��
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 ��ֵ���� t2 ��ֵ����Ϊ true������Ϊ false��
    bool operator >(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks>t2._ticks);
	}
    //
    // ժҪ:
    //     ָʾָ���� Common::TimeSpan �Ƿ���ڻ������һ��ָ���� Common::TimeSpan��
    //
    // ����:
    //   t2:
    //     TimeSpan��
    //
    //   t1:
    //     Common::TimeSpan��
    //
    // ���ؽ��:
    //     ��� t1 ��ֵ���ڻ���� t2 ��ֵ����Ϊ true������Ϊ false��
    bool operator >=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks>=t2._ticks);
	}

#endif
    
 
}
