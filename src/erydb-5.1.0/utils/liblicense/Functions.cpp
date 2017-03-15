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
	//一毫秒等于多少天
	//
	const double TimeSpan::DaysPerTicks = 1.1574074074074074074074074074074e-11;
	//
	//一毫秒等于多少小时
	//
	const double TimeSpan::HoursPerTicks = 2.7777777777777777E-10;
	//
	//一毫秒等于多少分钟数
	//
	const double TimeSpan::MinutesPerTicks = 1.6666666666666667E-8;
	//
	//最大毫秒数
	//
	const double TimeSpan::SecondsPerTicks  = 0.000001;
	//
	//最大毫秒数
	//
	const long long TimeSpan::MaxMillis=922337203685477ll ;
	//
	//最大秒数						  15372286728
	//								  4294967296
	const long long TimeSpan::MaxSeconds = 922337203685ll;
	//
	//一天多少毫秒
	//
	const int TimeSpan::MillisPerDay = 0x5265c00;
	//
	//1小时多少毫秒
	//
    const int TimeSpan::MillisPerHour = 0x36ee80;
	//
	//1分钟多少毫秒
	//
    const int TimeSpan::MillisPerMinute = 0xea60;
	//
	//1秒多少毫秒
	//
    const int TimeSpan::MillisPerSecond = 0x3e8;

	const long long TimeSpan::TicksPerMillisecond = 0x3e8LL;
	const long long TimeSpan::TicksPerDay = 0x141DD76000LL;
	const long long TimeSpan::TicksPerHour = 0xD693A400LL;
	const long long TimeSpan::TicksPerMinute = 0x3938700LL;
	const long long TimeSpan::TicksPerSecond = 0xF4240LL;


	//
	//最小毫秒数
	//
	const long long TimeSpan::MinMilliSeconds = -922337203685477ll;
	//
	//最小秒数
	//
	const long long TimeSpan::MinSeconds = -922337203685ll;
    // 摘要:
    //     表示最大的 Common.TimeSpan 值。此字段为只读。
	const TimeSpan TimeSpan::MaxValue=TimeSpan(TimeSpan::MaxSeconds * TimeSpan::TicksPerSecond);
    //
    // 摘要:
    //     表示最小的 Common.TimeSpan 值。此字段为只读。
    const TimeSpan TimeSpan::MinValue=TimeSpan(TimeSpan::MinSeconds * TimeSpan::TicksPerSecond);
    //
    // 摘要:
    //     表示零 Common.TimeSpan 值。此字段为只读。
	const  TimeSpan TimeSpan::Zero=TimeSpan(0);
#endif

//DateTime const static var//
#ifdef __Common_DateTime_H__ 
	const int  DateTime::DaysToMonth365[]={ 0, 0x1f, 0x3b, 90, 120, 0x97, 0xb5, 0xd4, 0xf3, 0x111, 0x130, 0x14e, 0x16d };
	const int  DateTime::DaysToMonth366[]={ 0, 0x1f, 60, 0x5b, 0x79, 0x98, 0xb6, 0xd5, 0xf4, 0x112, 0x131, 0x14f, 0x16e };

	const string DateTime::WeekName[7][3]={{"星期日","Sunday","Sun"}
	,{"星期一","Monday","Mon"},{"星期二","Tuesday","Tue"}
	,{"星期三","Wednesday","Wed"},{"星期四","Thursday","Thu"}
	,{"星期五","Friday","Fri"},{"星期六","Saturday","Sat"}};
	const string DateTime::MonthNames[13][3]={{"","",""}
	,{"1月","January","Jan"},{"2月","February","Feb"},{"3月","March","Mar"}
	,{"4月","April","Apr"},{"5月","May","May"},{"6月","June","June"}
	,{"7月","July","July"},{"8月","Aguest","Agu"},{"9月","September","Sep"}
	,{"10月","October","Oct"},{"11月","November","Nov"},{"12月","December","Dec"}};

	//string DateTime::_result="";
	//
	//摘要：
	//		UTC 标准时间多少毫秒
	//	62135596800000
	//	62135596800000.0000
	const long long DateTime::MillesPerUTCSta=62135596800000ll;
	const long long DateTime::MillesPer2100Year=66238041600000ll;
	//
	//摘要：
	//		最大小时 毫秒数
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
	//摘要：
	//		100年多少天
	//	36524
	const int DateTime::DaysPer100Years = 0x8eac;
	//
	//摘要：
	//		400年多少天
	//	146097
    const int DateTime::DaysPer400Years = 0x23ab1;
	//
	//摘要：
	//		4年多少天
	//	1461
    const int DateTime::DaysPer4Years = 0x5b5;
	//
	//摘要：
	//		1年多少天
	//	365
    const int DateTime::DaysPerYear = 0x16d;
	//
	//摘要：
	//		一天多少毫秒
	//	86400000
	const int DateTime::MillisPerDay = 0x5265c00;
	//
	//摘要：
	//		1小时多少毫秒
	//	3600000
    const int DateTime::MillisPerHour = 0x36ee80;
	//
	//摘要：
	//		1分钟多少毫秒
	//	60000
    const int DateTime::MillisPerMinute = 0xea60;
	//
	//摘要：
	//		1秒多少毫秒
	//	1000
    const int DateTime::MillisPerSecond = 0x3e8;
//#if OSTYPE<=10
	const time_t DateTime::ts=time(NULL);
	const int DateTime::lHour=localtime(&ts)->tm_hour;		
	const TimeZone DateTime::localTimeZone =  TimeZone((lHour-gmtime(&ts)->tm_hour)>12?((lHour-gmtime(&ts)->tm_hour)-24):((lHour-gmtime(&ts)->tm_hour)<-12?((lHour-gmtime(&ts)->tm_hour)+24):(lHour-gmtime(&ts)->tm_hour)));
//#endif
	//
	//摘要：
	//		最大时间值
	//	9999-12-31 23:59:59   //	315537897599999 毫秒 
	const  DateTime  DateTime::MaxValue=DateTime(DateTime::MaxTicks);
	//
	//摘要：
	//		最小时间值
	//	0001-1-1 0:00:00  //	0 毫秒
	const  DateTime  DateTime::MinValue=DateTime(DateTime::MinTicks);
	//*****    DateTime    TimeSpan operator method          *                                    
	// 摘要:
	//     从一个指定日期和时间减去另一个指定的日期和时间以生成时间间隔。
	//
	// 参数:
	//   d2:
	//     Common.DateTime（减数）。
	//
	//   d1:
	//     Common.DateTime（被减数）。
	//
	// 返回结果:
	//     Common.TimeSpan，它是 d1 和 d2 之间的时间间隔，即 d1 减去 d2。
	TimeSpan operator -(DateTime d1, DateTime d2)
	{
		return TimeSpan((d1.GetTicks()-d2.GetTicks()));
	}
	//
	// 摘要:
	//     从指定的日期和时间减去指定的时间间隔，以生成新的日期和时间。
	//
	// 参数:
	//   d:
	//     Common.DateTime。
	//
	//   t:
	//     Common.TimeSpan。
	//
	// 返回结果:
	//     Common.DateTime，它的值为 d 的值减去 t 的值。
	DateTime operator -(DateTime d, TimeSpan t)
	{
		return  DateTime(d._Ticks-t.getTotalTicks());
	}
	//
	// 摘要:
	//     确定 Common.DateTime 的两个指定的实例是否不等。
	//
	// 参数:
	//   d2:
	//     Common.DateTime。
	//
	//   d1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 d1 和 d2 不表示同一日期和时间，则为 true；否则为 false。
	bool operator !=(DateTime d1, DateTime d2)
	{
		if(d1.GetTicks()==d2.GetTicks())return false;
		else return true;
	}
	//
	// 摘要:
	//     将指定的时间间隔加到指定的日期和时间以生成新的日期和时间。
	//
	// 参数:
	//   d:
	//     Common.DateTime。
	//
	//   t:
	//     Common.TimeSpan。
	//
	// 返回结果:
	//     Common.DateTime，它是 d 和 t 值的和。
	DateTime operator +(DateTime d, TimeSpan t)
	{
		return  DateTime(d._Ticks+t.getTotalTicks());
	}
	DateTime &operator +=(DateTime &d, TimeSpan t)
	{
		return d=DateTime(d._Ticks+t.getTotalTicks());
	}
	//
	// 摘要:
	//     确定指定的 Common.DateTime 是否小于另一个指定的 Common.DateTime。
	//
	// 参数:
	//   t2:
	//     Common.DateTime。
	//
	//   t1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 t1 小于 t2，则为 true；否则为 false。
	bool operator <(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()<t2.GetTicks()) ;
	}
	//
	// 摘要:
	//     确定指定的 Common.DateTime 是否小于或等于另一个指定的 Common.DateTime。
	//
	// 参数:
	//   t2:
	//     Common.DateTime。
	//
	//   t1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 t1 小于或等于 t2，则为 true；否则为 false。
	bool operator <=(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()<=t2.GetTicks());
	}
	//
	// 摘要:
	//     确定 Common.DateTime 的两个指定的实例是否相等。
	//
	// 参数:
	//   d2:
	//     Common.DateTime。
	//
	//   d1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 d1 和 d2 表示同一日期和时间，则为 true；否则为 false。
	bool operator ==(DateTime d1, DateTime d2)
	{
		return (d1.GetTicks()==d2.GetTicks());
	}
	//
	// 摘要:
	//     确定指定的 Common.DateTime 是否大于另一个指定的 Common.DateTime。
	//
	// 参数:
	//   t2:
	//     Common.DateTime。
	//
	//   t1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 t1 大于 t2，则为 true；否则为 false。
	bool operator >(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()>t2.GetTicks());
	}
	 
	//
	// 摘要:
	//     确定指定的 Common.DateTime 是否大于或等于另一个指定的 Common.DateTime。
	//
	// 参数:
	//   t2:
	//     Common.DateTime。
	//
	//   t1:
	//     Common.DateTime。
	//
	// 返回结果:
	//     如果 t1 大于或等于 t2，则为 true；否则为 false。
	bool operator >=(DateTime t1, DateTime t2)
	{
		return (t1.GetTicks()>=t2.GetTicks());
	}
#endif

//**************TimeSpan  ***********************************************                                    
#ifdef __Common_TimeSpan_H__
    // 摘要:
    //     返回其值为指定实例的相反值的 Common::TimeSpan。
    //
    // 参数:
    //   t:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     与此实例的数值相同，但符号相反的 Common::TimeSpan。
    TimeSpan &operator -(TimeSpan &t)
	{
		t._ticks=0-t._ticks;
		return t;
	}
    //
    // 摘要:
    //     从另一个指定的 Common::TimeSpan 中减去指定的 Common::TimeSpan。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     值为 t1 的值减去 t2 的值后所得结果的 TimeSpan。
    TimeSpan operator -(TimeSpan &t1, TimeSpan &t2)
	{
		return  TimeSpan(t1._ticks-t2._ticks);
	}
    TimeSpan &operator -=(TimeSpan &t1, TimeSpan &t2)
	{
		return t1=TimeSpan(t1._ticks-=t2._ticks);
	}
    //
    // 摘要:
    //     指示两个 Common::TimeSpan 实例是否不相等。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 和 t2 的值不相等，则为 true；否则为 false。
    bool operator !=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks!=t2._ticks);
	}
    //
    // 摘要:
    //     添加两个指定的 Common::TimeSpan 实例。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     值为 t1 和 t2 的值之和的 Common::TimeSpan。
    TimeSpan operator +(TimeSpan &t1, TimeSpan &t2)
	{
		return  TimeSpan(t1._ticks+t2._ticks);
	}
    TimeSpan &operator +=(TimeSpan &t1, TimeSpan &t2)
	{
		return  t1=  TimeSpan(t1._ticks+t2._ticks);
	}
    //
    // 摘要:
    //     指示指定的 Common::TimeSpan 是否小于另一个指定的 Common::TimeSpan。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 的值小于 t2 的值，则为 true；否则为 false。
    bool operator <(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks<t2._ticks);
	}
    //
    // 摘要:
    //     指示指定的 Common::TimeSpan 是否小于或等于另一个指定的 Common::TimeSpan。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 的值小于或等于 t2 的值，则为 true；否则为 false。
    bool operator <=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks<=t2._ticks);
	}
    //
    // 摘要:
    //     指示两个 Common::TimeSpan 实例是否相等。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 和 t2 的值相等，则为 true；否则为 false。
    bool operator ==(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks==t2._ticks);
	}
    //
    // 摘要:
    //     指示指定的 Common::TimeSpan 是否大于另一个指定的 Common::TimeSpan。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 的值大于 t2 的值，则为 true；否则为 false。
    bool operator >(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks>t2._ticks);
	}
    //
    // 摘要:
    //     指示指定的 Common::TimeSpan 是否大于或等于另一个指定的 Common::TimeSpan。
    //
    // 参数:
    //   t2:
    //     TimeSpan。
    //
    //   t1:
    //     Common::TimeSpan。
    //
    // 返回结果:
    //     如果 t1 的值大于或等于 t2 的值，则为 true；否则为 false。
    bool operator >=(TimeSpan &t1, TimeSpan &t2)
	{
		return (t1._ticks>=t2._ticks);
	}

#endif
    
 
}
