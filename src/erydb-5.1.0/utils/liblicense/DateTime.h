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
// ==============================================================

#ifndef __Common_DateTime_H__ 
#define __Common_DateTime_H__
#include "LicCommon.h"


namespace Common
{

	///	<summary>
	///	表示时间上的一刻，通常以日期和当天的时间表示。最小计数到微秒。
	///	</summary>
	///	<remarks>
	///	精确的表示一个时间间隔，精确到微秒。
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class DateTime
	{
		public:
		typedef enum Common::DateTimeKind DateTimeKind;
		typedef enum Common::DayOfWeek DayOfWeek;
		typedef enum Common::DateTimeStyles DateTimeStyles;
		typedef enum Common::TimeZone TimeZone;
		typedef enum Common::DatePart DatePart;

		// Fields
		protected:
			///	<summary>
			///	时间的刻度数，精确到微秒，并以时间编码。前五位存储时区信息，后59位存储时间值.
			///	</summary>
			unsigned long long _Ticks;        // 前5位表示时区
		public:
			///	<summary>
			///	将tm对象转换成指定格式的字符串对象
			///	<code>原型：inline static string ToString(tm &amp;_tm,DateTimeStyles style=StaDateTime);</code>
			///	</summary>
			///	<param name="_tm">tm对象，C标准的时间结构体</param>
			///	<param name="style">要转换成的格式<see cref="DateTimeStyles"/>,默认为标准格式 StaDateTime[yyyy-mm-dd hh:mi:ss] </param>
			///	<returns>返回tm对应的字符串表现形式</returns>
			EXPORT	inline static string ToString(tm &_tm, DateTimeStyles style = StaDateTime)
			{
				const string * weekName=DateTime::WeekName[_tm.tm_wday];
				int year=_tm.tm_year;
				int month=_tm.tm_mon;
				const string * monthName=MonthNames[month];
				int day=_tm.tm_mday;
				int hour=_tm.tm_hour;
				int minute=_tm.tm_min;
				int second=_tm.tm_sec;
				char p[40];
				memset(p,0,40);
				switch(style)
				{
				case StaUTC:				// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
					sprintf(p,"%s %s %d %02d:%02d:%02d %d",weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
					break;
				case StaDateTime:// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %0d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				case LongDate:				// yyyy年mm月dd日
					sprintf(p,"%04d年%d月%d日",year,month,day);
					break;
				case StaDate:		// yyyy-mm-dd
					sprintf(p,"%04d-%02d-%02d",year,month,day);
					break;
				case StaTime: 			// 	hh:mi:ss
					sprintf(p,"%d:%02d:%02d",hour,minute,second);
					break;
				case ShotDate: 			// 	yyyymmdd
					sprintf(p,"%04d%02d%02d",year,month,day);
					break;
				case ShotTime: 				// 	 hh:mi 
					sprintf(p,"%d:%02d",hour,minute);
					break;
				case ShotDateTime: 				// 	yyyymmddhhmiss
					sprintf(p,"%04d%02d%02d%02d%02d%02d",year,month,day,hour,minute,second);
					break;
				default:			// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %0d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				}
				return string(p);
			}



#if defined(_MSC_VER)        // windows 下的计数器函数
			///	<summary>
			///	直接获取CPU计数[跳次] 二次调用返回值差除以CPU频率即为秒   纳秒级
			///	<code>原型：inline static unsigned __int64 GetCycleCount();</code>
			///	</summary>
			///	<returns>64位无符号整数，CPU跳次计数值</returns>
			EXPORT	inline static unsigned __int64 GetCycleCount()
			{ 
			__asm _emit 0x0F 
			__asm _emit 0x31 
			};
			///	<summary>
			///	直接获取CPU计数[跳次] 二次调用返回值差除以CPU频率即为秒   纳秒级
			///	<code>原型：inline static unsigned __int64 GetCycleCount2();</code>
			///	</summary>
			///	<returns>64位无符号整数，CPU跳次计数值</returns>
			inline static unsigned __int64 GetCycleCount2() 
			{ 
			__asm RDTSC 
			};
#ifdef _TIMERAPI_H_
			///	<summary>
			///	毫秒级 需要加载多媒体函数库
			///	<code>原型：inline static unsigned long GetMMTime();</code>
			///	</summary>
			///	<returns>多媒体时间计算器时间</returns>
			EXPORT	inline static unsigned long GetMMTime()
			{
				return timeGetTime();
			};

			///	<summary>
			///	获取系统的计数器的频率 微秒级
			///	<code>原型：inline static unsigned long long GetPerformanceUnit();</code>
			///	</summary>
			///	<returns>返回系统计算器频率</returns>
			EXPORT inline static unsigned long long GetPerformanceUnit()
			{
				LARGE_INTEGER tc;
				QueryPerformanceFrequency(&tc); 
				return tc.QuadPart;
			};
			///	<summary>
			///	获取系统计数次数 二次返回值差除以计数器的频率即为秒  微秒级
			///	<code>原型：inline static unsigned long long GetPerformanceCounter();</code>
			///	</summary>
			///	<returns>返回系统计算器的值</returns>
			EXPORT	inline static unsigned long long GetPerformanceCounter()
			{
				LARGE_INTEGER tc;
				QueryPerformanceCounter(&tc);
				return tc.QuadPart;
			};
#endif
			///	<summary>
			///	系统计数次数
			///	</summary>
			static unsigned long long sysPerformanceUnit;
			///	<summary>
			///	CPU主频
			///	</summary>
			static unsigned long long sysCpuUnit;
#endif
			///	<summary>
			///	将时间对象转换成oracle存储格式
			///	<code>原型：inline static unsigned char * ToOracleDate(DateTime &amp;dt,unsigned char * tempStr);</code>
			///	</summary>
			///	<param name="dt">要转换的时间对象</param>
			///	<param name="tempStr">目标存储空间指针，用于存储转换后的值</param>
			///	<returns>返回tempStr指针</returns>
			EXPORT	inline static unsigned char * ToOracleDate(DateTime &dt, unsigned char * tempStr)
			{
				memset(tempStr,0,7);
				int year,month,day,hour,minute,second;
				dt.GetDateParts(&year,&month,&day,NULL,&hour,&minute,&second);
				int sj=year/100+100;
				year=year%100+100;
				tempStr[0]=sj;
				tempStr[1]=year;
				tempStr[2]=month;
				tempStr[3]=day;
				tempStr[4]=hour+1;
				tempStr[5]=minute+1;
				tempStr[6]=second+1;
				return tempStr;
			}
			///	<summary>
			///	从oracle存储格式转换时间对象
			///	<code>原型：inline static DateTime GetDateFromOracle(unsigned char * dtp,DateTime * nullDefault=NULL);</code>
			///	</summary>
			///	<param name="dtp">7字节的oracle存储格式数据</param>
			///	<param name="nullDefault">指定为空或异常时的默认时间值</param>
			///	<returns>转换所得的时间对象，如oracle所表示的时间异常，则返回最小时间值</returns>
			EXPORT	inline static DateTime GetDateFromOracle(unsigned char * dtp, DateTime * nullDefault = NULL)
			{
				if(dtp[0]==0 || (dtp[2]==6 && dtp[3]==31))
				{
					if(nullDefault)return *nullDefault;
					return DateTime::MinValue;
				}
				else
				{
					int sj=dtp[0]-100;
					int year=dtp[1]+(sj-1)*100;
					int month=dtp[2];
					int day=dtp[3];
					int hour=dtp[4]-1;
					int minute=dtp[5]-1;
					int second=dtp[6]-1;
					return DateTime(year,month,day,hour,minute,second);
				}
			}
			///	<summary>
			///	星期的名称 中文名,英文名,英文简写
			///	</summary>
			static const string WeekName[7][3];
			///	<summary>
			///	各种月份的名称  中文名,英文名,英文简写
			///	</summary>
			static const string MonthNames[13][3];
			
			///	<summary>
			///	13数组 标识每个月天数
			///	</summary>
			static  const int  DaysToMonth365[];
			///	<summary>
			///	13数组 标识每个月天数
			///	</summary>
			static  const int  DaysToMonth366[];
			///	<summary>
			///	UTC 标准时间有多少毫秒  62135596800000
			///	</summary>
			static const long long MillesPerUTCSta;
			///	<summary>
			///	100年有多少毫秒
			///	</summary>
			static const long long MillesPer2100Year;
			///	<summary> 
			///	最大毫秒数  315537897599999
			///	</summary>
			static const long long MaxMillesSecond;
			///	<summary> 
			///	最小时间  0
			///	</summary>
			static const long long MinMillesSecond;
			
			///	<summary> 
			///	100年多少天	36524
			///	</summary>
			static const int  DaysPer100Years; 
			///	<summary> 
			///	400年多少天	146097
			///	</summary>
			static const int  DaysPer400Years ;
			///	<summary> 
			///	4年多少天	1461
			///	</summary>
			static const int  DaysPer4Years ;
			///	<summary> 
			///	1年多少天	365
			///	</summary>
			static const int  DaysPerYear ;
			///	<summary> 
			///	一天多少毫秒	86400000
			///	</summary>
			static const int  MillisPerDay ;
			///	<summary> 
			///	1小时多少毫秒	3600000
			///	</summary>
			static const int  MillisPerHour ;
			///	<summary> 
			///	1分钟多少毫秒	60000
			///	</summary>
			static const int  MillisPerMinute ;
			///	<summary> 
			///	1秒多少毫秒	1000
			///	</summary>
			static const int  MillisPerSecond ;

			///	<summary> 
			///	最大时间刻度数 0x461040BCB9F1FFFLL
			///	</summary>
			static const long long MaxTicks ;//= 0x461040BCB9F1FFFLL;
			///	<summary> 
			///	最小时间刻度数 0
			///	</summary>
			static const long long MinTicks;// = 0L;

			///	<summary> 
			///	时区伪码，作与运算可直接获取时区部分 0xF800000000000000LL
			///	</summary>
			static const long long TicksCeiling ;
			///	<summary> 
			///	时间刻度伪码，作与运算可直接获取时间部分 0x7FFFFFFFFFFFFFFLL
			///	</summary>
			static const long long TicksMask;
			///	<summary> 
			///	一天有多少刻度数（微秒） 0x141DD76000LL
			///	</summary>
			static const long long TicksPerDay;
			///	<summary> 
			///	一小时有多少刻度数（微秒） 0xD693A400LL
			///	</summary>
			static const long long TicksPerHour;
			///	<summary> 
			///	一毫秒有多少刻度数（微秒） 0x3e8LL
			///	</summary>
			static const long long TicksPerMillisecond;
			///	<summary> 
			///	一分钟有多少刻度数（微秒） 0x3938700LL
			///	</summary>
			static const long long TicksPerMinute;
			///	<summary> 
			///	一秒有多少刻度数（微秒） 0xF4240LL
			///	</summary>
			static const long long TicksPerSecond;
			///	<summary> 
			///	UTC标准时间刻度数（微秒） 0xDCBFFEFF2BC000LL
			///	</summary>
			static const long long TicksPerUTCSta;
			///	<summary> 
			///	标准时间秒数 0xE7791F700ll
			///	</summary>
			static const long long SecondPerUTCSta;

//#if OSTYPE>10
//			static const TimeZone localTimeZone=GMT8 ;
//#else
		protected:
			static const time_t ts ;
			static const int lHour;//localtime(&ts)->tm_hour;
		public:
			///	<summary> 
			///	当前本地时区
			///	</summary>
			static const TimeZone localTimeZone;//=GMT8 ;//SetTimeZone
//#endif
		protected:
 			inline void _init(TimeZone tz=localTimeZone)
			{
				unsigned long long tl=0;
#ifndef _MSC_VER
				struct timeval tv;
				gettimeofday (&tv ,NULL);
				this->_Ticks=DateTime::TicksPerUTCSta+ tv.tv_sec* DateTime::TicksPerSecond+tv.tv_usec;	//微秒
				//printf("tv_sec; %d\n",tv.tv_sec) ;
				//printf("tv_usec; %d\n",tv.tv_usec);
				//printf("tz_minuteswest; %d\n",tz.tz_minuteswest);   // 时区信息   UTC与当前时区时间差值，  分钟数
				//printf("tz_dsttime,%d\n",tz.tz_dsttime);
#else
				
#ifdef _FILETIME_
				FILETIME ft;
				GetSystemTimeAsFileTime( &ft ); //返回100纳秒 级  性能比time还好
				_Ticks = ft.dwHighDateTime; _Ticks =(_Ticks<<32) | (long long)ft.dwLowDateTime;
				//_Ticks = (((long long)ft.dwHighDateTime)*4294967296LL) + (long long)ft.dwLowDateTime;
				_Ticks/=10;
				_Ticks+=50491123200000000LL;//50491094400000000LL; 加1600年 1601年tick为50491123200000000 				//*this=this->AddYears(1600);
#elif defined(_SYSTEMTIME_)
				SYSTEMTIME st;
				GetSystemTime(&st);	////精确到毫秒 
				//_init(st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,0,tz);
				unsigned long long ys=DateToTicks(st.wYear, st.wMonth, st.wDay);
				unsigned long long ds=TimeToTicks(st.wHour, st.wMinute, st.wSecond);
				unsigned long long num =  ys+ds;
				num += st.wMilliseconds*TicksPerMillisecond;
				num=(num>this->MaxTicks)?this->MaxTicks:num;
				num=(num<this->MinTicks)?this->MinTicks:num;
				this->_Ticks=num=num - tz * this->TicksPerHour;
#else
				//int l=(GetCycleCount() /2660) % 1000000;			//	精确到微秒
				int l = 0;
				//l = (GetTickCount() % this->MillisPerSecond)*this->TicksPerMillisecond;		//精确到毫秒

				//unsigned long long l=GetPerformanceCounter();
				//l = (((l * DateTime::TicksPerSecond ) / GetPerformanceUnit() )% DateTime::TicksPerSecond);	//	精确到微秒,性能较低
				time_t t = time(NULL);
				this->_Ticks = DateTime::TicksPerUTCSta + (unsigned long long)t * DateTime::TicksPerSecond + l;
#endif
				
#endif
				//组合计算时区
				tl=32+tz;
				tl=tl<<59;		//	留5位时区标识
				this->_Ticks=tl | _Ticks;
			}
			inline void _init(long long t,TimeZone tz=localTimeZone)
			{
				this->_Ticks=t>0?t:0;
				if(t>this->MaxTicks)this->_Ticks=this->MaxTicks;
				//组合计算时区
				unsigned long long tl=0;
				tl=32+tz;
				tl=tl<<59;		//	留5位时区标识
				this->_Ticks=(tl | (_Ticks & this->TicksMask));
			}
			inline void _init(int year, int month, int day, int hour, int minute, int second,int millisecond, int ticks,TimeZone tz)
			{
				if(year==0)
				{
					year=1;
					month=1;
					day=1;
					hour=0;
					minute=0;
					second=0;
					millisecond=0;
				}
				unsigned long long ys=DateToTicks(year, month, day);
				unsigned long long ds=TimeToTicks(hour, minute, second);
				unsigned long long num =  ys+ds +ticks;
				num += millisecond*TicksPerMillisecond;
				if ((millisecond < 0) || (millisecond >= this->TicksPerSecond))
				{
					EXP("millisecond ArgumentOutOfRange_Range[0-999]");
				}
				num=(num>this->MaxTicks)?this->MaxTicks:num;
				num=(num<this->MinTicks)?this->MinTicks:num;
				this->_Ticks=0;
				if(num> tz * this->TicksPerHour)
					this->_Ticks=num=num - tz * this->TicksPerHour;
				unsigned long long tl=0;
				tl=32+tz;
				tl=tl<<59;		//	留5位时区标识
				this->_Ticks=tl | _Ticks;
			}

		public:
			///	<summary> 
			///	获取从格林威治标准时间到指定时间的秒数
			///	<code>原型：inline static long getUtcSec(DateTime &amp; dt);</code>
			///	</summary>
			///	<param name="dt">时间对象<see cref="DateTime"/></param>
			///	<returns>返回格林威治标准时间到dt所表示的时间的秒数</returns>
			EXPORT	inline static long getUtcSec(DateTime & dt){ return (dt.GetTicks() - DateTime::TicksPerUTCSta) / DateTime::TicksPerSecond; };
			///	<summary> 
			///	获取从格林威治标准时间到此实例所表示的时间的秒数
			///	<code>原型：inline long getUtcSec();</code>
			///	</summary>
			///	<returns>返回些实例到UTC时间的秒数</returns>
			EXPORT	inline long getUtcSec(){ return ((_Ticks & this->TicksMask) - DateTime::TicksPerUTCSta) / DateTime::TicksPerSecond; };
			///	<summary> 
			///	从年月日的三个整数转换为时间刻度数（微秒）
			///	<code>原型：inline static unsigned long long DateToTicks(int year, int month, int day);</code>
			///	</summary>
			///	<param name="year">年</param>
			///	<param name="month">月</param>
			///	<param name="day">日</param>
			///	<returns>返回从公元一年一月一日零时零分零秒到指定年月日的刻度数</returns>
			EXPORT	inline static unsigned long long DateToTicks(int year, int month, int day)
			{
				if (((year >= 1) && (year <= 0x270f)) && ((month >= 1) && (month <= 12)))
				{
					const int * numArray = DateTime::IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
					if ((day >= 1) && (day <= (numArray[month] - numArray[month - 1])))
					{
						int num = year - 1;
						unsigned long long num2 = ((((((num * 0x16d) + (num / 4)) - (num / 100)) + (num / 400)) + numArray[month - 1]) + day) - 1;
						return (num2 * DateTime::TicksPerDay);
					}
				}
				EXP("ArgumentOutOfRange_BadYearMonthDay");
			}

			///	<summary>
			///	将时间部分转换为时间刻度数（微秒）
			///	<code>原型：inline static unsigned long long TimeToTicks(int hour, int minute, int second);</code>
			///	</summary>
			///	<param name="hour">小时</param>
			///	<param name="minute">分钟</param>
			///	<param name="second">秒</param>
			///	<returns>返回对应的刻度数（微秒数）</returns>
			EXPORT	inline static unsigned long long TimeToTicks(int hour, int minute, int second)
			{
				if ((((hour < 0) || (hour >= 0x18)) || ((minute < 0) || (minute >= 60))) || ((second < 0) || (second >= 60)))
				{
					EXP("ArgumentOutOfRange_BadHourMinuteSecond");
				}
				return TimeSpan::TimeToTicks(hour, minute, second);
			}

			///	<summary>
			///	最大时间值 9999-12-31 23:59:59 	315537897599999 毫秒 
			///	</summary>
			static  const DateTime  MaxValue;
			///	<summary>
			///	最小时间值 0001-1-1 0:00:00  	0 毫秒 
			///	</summary>
			static  const DateTime  MinValue;
			///	<summary>
			///	指定距UTC时间的秒数和时区信息初始化时间对象 
			///	<code>原型：DateTime(unsigned int  sec,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="sec">距UTC时间的秒数</param>
			///	<param name="tz">sec所要表示的时区时间<see cref="TimeZone"/></param>
			EXPORT	DateTime(unsigned int  sec, TimeZone tz = localTimeZone)
			{
				long long t=DateTime::TicksPerUTCSta+ (long long)sec * DateTime::TicksPerSecond;
				this->_Ticks=t>0?t:0;
				if(t>this->MaxTicks)this->_Ticks=this->MaxTicks;
				unsigned long long tl=0;
				tl=32+tz;
				tl=tl<<59;		//	留5位时区标识
				this->_Ticks=tl | _Ticks;
			};
			///	<summary>
			///	指定C的时间结构对象初始化时间对象 
			///	<code>原型：DateTime(tm &amp;_tm);</code>
			///	</summary>
			///	<param name="_tm">C时间结构对象</param> 
			EXPORT	DateTime(tm &_tm)
			{
				this->_init( _tm.tm_year+1900,_tm.tm_mon+1,_tm.tm_mday,_tm.tm_hour,_tm.tm_min,_tm.tm_sec,0,0,localTimeZone);
			}
			///	<summary>
			///	指定时区并以当前时间初始化对象 
			///	<code>原型：DateTime(TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="tz">时区信息</param> 
			EXPORT	DateTime(TimeZone tz = localTimeZone)
			{
				this->_init(tz);
			}
			///	<summary>
			///	以微秒为单位表示的日期和时间。其准时间：1年1月1日0时0分0秒 
			///	<code>原型：DateTime(long long t, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="t">以微秒为单位表示的日期和时间刻度数</param> 
			///	<param name="tz">时区信息</param> 
			EXPORT	DateTime(long long t, TimeZone tz = localTimeZone)
			{
				this->_init((long long)(t & this->TicksMask),tz);
			};
			///	<summary>
			///	以微秒为单位表示的日期和时间。其准时间：1年1月1日0时0分0秒 
			///	<code>原型：DateTime(unsigned long long t, TimeZone tz);</code>
			///	</summary>
			///	<param name="t">以微秒为单位表示的日期和时间刻度数</param> 
			///	<param name="tz">时区信息</param> 
			EXPORT	DateTime(unsigned long long t, TimeZone tz)
			{
				this->_init((long long)(t & this->TicksMask),tz);
			};
			///	<summary>
			///	以微秒为单位表示的日期和时间。其准时间：1年1月1日0时0分0秒 
			///	<code>原型：DateTime(unsigned long long t);</code>
			///	</summary>
			///	<param name="t">以微秒为单位表示的日期和时间刻度数</param> 
			EXPORT	DateTime(unsigned long long t)
			{
				if((t & this->TicksMask)>this->MaxTicks)
				{
					this->_Ticks=(t&this->TicksCeiling)+this->MaxTicks ;
				}
				else
				{
					this->_Ticks=t;
				}
			};
			///	<summary>
			///	将 <see cref='DateTime'/>结构的新实例初始化为指定年、月、日、小时、分钟、秒、毫秒、微秒和指定时区的时间。
			///	<code>原型：DateTime(int year, int month, int day, int hour=0, int minute=0, int second=0,
			///                       int millisecond=0,int ticks=0, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="year">年</param> 
			///	<param name="month">月</param> 
			///	<param name="day">日</param> 
			///	<param name="hour">小时</param> 
			///	<param name="minute">分</param> 
			///	<param name="second">秒</param> 
			///	<param name="millisecond">毫秒</param> 
			///	<param name="ticks">微秒</param> 
			///	<param name="tz">指定时间的对应时区</param>
			EXPORT	DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int ticks = 0, TimeZone tz = localTimeZone)
			{
				this->_init( year,month,day,hour,minute,second,millisecond,ticks,tz);
			}
			///	<summary>
			///	用8位整数表示的年月日初始化. 如:20071128将
			///	<code>原型：DateTime(int date,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="date">8位日期部分</param> 
			///	<param name="tz">对应时区</param> 
			EXPORT	DateTime(int date, TimeZone tz = localTimeZone)   //20071128 
			{
				int year,month,day;
				year  = date/10000;
				month = (date/100) % 100;
				day  = date % 100;
				this->_init(year,month,day,0,0,0,0,0,tz);
			}
			
			//*******************************操作符重载*****************************************                                    
			friend TimeSpan Common::operator -(DateTime d1, DateTime d2);
			friend DateTime Common::operator -(DateTime d, TimeSpan t);
			friend bool Common::operator !=(DateTime d1, DateTime d2);
			friend DateTime Common::operator +(DateTime d, TimeSpan t);
			friend DateTime &Common::operator +=(DateTime &d, TimeSpan t);
			friend bool Common::operator <(DateTime t1, DateTime t2);
			friend bool Common::operator <=(DateTime t1, DateTime t2);
			friend bool Common::operator ==(DateTime d1, DateTime d2);
			friend bool Common::operator >(DateTime t1, DateTime t2);
			friend bool Common::operator >=(DateTime t1, DateTime t2);

			///	<summary>
			///	获取此实例所表示日期的年份部分。
			///	<code>原型：inline int GetYear();</code>
			///	</summary>
			///	<returns>返回年部分</returns> 
			EXPORT	inline int GetYear()
			{
				return this->GetDatePart(0);		 
			}
			///	<summary>
			///	获取此实例所表示日期的月份部分。月组成部分，表示为 1 和 12 之间的一个值。
			///	<code>原型：inline int GetMonth();</code>
			///	</summary>
			///	<returns>返回月部分</returns> 
			EXPORT	inline int GetMonth()
			{
				return this->GetDatePart(2);		 
			}
			///	<summary>
			///	获取此实例所表示的日期为该月中的第几天。日组成部分，表示为 1 和 31 之间的一个值。
			///	<code>原型：inline int GetDay();</code>
			///	</summary>
			///	<returns>返回日部分</returns> 
			EXPORT	inline int GetDay()
			{
				return this->GetDatePart(3);
			}
			///	<summary>
			///	获取此实例所表示日期的小时部分。小时组成部分，表示为 0 和 23 之间的一个值。
			///	<code>原型：inline int GetHour();</code>
			///	</summary>
			///	<returns>返回小时部分</returns> 
			EXPORT	inline int GetHour()
			{
				unsigned long long totalTicks=(_Ticks & this->TicksMask);
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				totalTicks=totalTicks + tz * this->TicksPerHour ;
				if(totalTicks>MaxTicks)
					totalTicks=this->MaxTicks;
				long long hs=(long long)(totalTicks%this->TicksPerDay);
				return (int) (hs/this->TicksPerHour);
			}
			///	<summary>
			///	获取此实例所表示日期的分钟部分。分钟组成部分，表示为 0 和 59 之间的一个值。
			///	<code>原型：inline int GetMinute();</code>
			///	</summary>
			///	<returns>返回分钟部分</returns> 
			EXPORT	inline int GetMinute()
			{
				long long hs=(long long)((_Ticks & this->TicksMask)%this->TicksPerHour);
				return (int) (hs / this->TicksPerMinute);
			}
			///	<summary>
			///	获取此实例所表示日期的秒部分。秒数（介于 0 和 59 之间）。
			///	<code>原型：inline int GetSecond();</code>
			///	</summary>
			///	<returns>此实例所表示日期的秒部分</returns> 
			EXPORT	inline int GetSecond()
			{
				long long ds=(this->_Ticks & this->TicksMask) % this->TicksPerMinute;	
				return (int) (ds/this->TicksPerSecond);
			}
			///	<summary>
			///	获取此实例所表示日期的毫秒部分。毫秒数（介于 0 和 999 之间）。
			///	<code>原型：inline int GetMillessecond();</code>
			///	</summary>
			///	<returns>此实例所表示日期的毫秒部分</returns> 
			EXPORT	inline int GetMillessecond()
			{
				return (int)((this->_Ticks & this->TicksMask) % this->TicksPerSecond)/this->TicksPerMillisecond;
			}
			///	<summary>
			///	获取此实例所表示日期的微秒部分。微秒数（介于 0 和 999 之间）。
			///	<code>原型：inline int GetMicrosecond();</code>
			///	</summary>
			///	<returns>此实例所表示日期的微秒部分</returns> 
			EXPORT	inline int GetMicrosecond(){ return (this->_Ticks & this->TicksMask) % this->TicksPerMillisecond; };
			///	<summary>
			///	获取表示此实例的日期和时间的刻度数微秒数。
			///	<code>原型：inline unsigned long long GetTicks();</code>
			///	</summary>
			///	<returns>此实例所表示日期的微秒部分</returns> 
			EXPORT	inline unsigned long long GetTicks()
			{
				return (this->_Ticks & this->TicksMask);
			}
			///	<summary>
			///	获取此实例所表示的日期是该年中的第几天。该年中的第几天，表示为 1 和 366 之间的一个值。
			///	<code>原型：inline int GetDayOfYear();</code>
			///	</summary>
			///	<returns>此实例所表示的日期是该年中的第几天</returns> 
			EXPORT	inline int GetDayOfYear()
			{
				return this->GetDatePart(1);		 
			}
			///	<summary>
			///	获取此实例所转换时区所表示的日期是星期几。一个<see cref="Common.DayOfWeek"/>枚举常数，它指示星期几。该属性值的范围从零（表示星期日）到六（表示星期六）。
			///	<code>原型：inline DayOfWeek GetDayOfWeek(TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="tz">指定时区</param> 
			///	<returns>星期几</returns> 
			EXPORT	inline DayOfWeek GetDayOfWeek(TimeZone tz = localTimeZone)
			{
				return (DayOfWeek) ((int) ((((long)(((_Ticks & this->TicksMask)+tz*DateTime::TicksPerHour) / this->TicksPerDay)) + 1) % ((long) 7)));
			};
			///	<summary>
			///	返回当前时间所表示的星期名称。type=0 中文名称 1 英文全称 2 英文简写。
			///	<code>原型：inline const string &amp;GetWeekName(int type,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="type">指定返回表示形式</param> 
			///	<param name="tz">指定时区</param> 
			///	<returns>当前时间所表示的星期名称</returns> 
			EXPORT	inline const string &GetWeekName(int type, TimeZone tz = localTimeZone)
			{
				type=type%3;
				DayOfWeek index= this->GetDayOfWeek(tz);
				return DateTime::WeekName[index][type];
			}
			///	<summary>
			///	获取此实例的日期部分。新的 <see cref="DateTime"/>，其日期与此实例相同，时间值设置为午夜 12:00:00 (00:00:00)。
			///	<code>原型：inline DateTime GetDate();</code>
			///	</summary>
			///	<returns>此实例的日期部分所表示的新日期对象</returns> 
			EXPORT	inline DateTime GetDate()
			{
				unsigned long long l=(this->_Ticks & this->TicksMask);
				unsigned long long ll=(this->_Ticks & this->TicksCeiling);
				//l=(l/this->TicksPerDay) * this->TicksPerDay;
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				//l=l-(l%this->TicksPerDay) ;
				l=(l-(l+tz*this->TicksPerHour)%this->TicksPerDay) ;
				return DateTime(ll | l );
			}
			///	<summary>
			///	获取此实例的指定部分。
			///	<code>原型：inline int GetDatePart(DatePart dp);</code>
			///	</summary>
			///	<param name="dp">指定要返回的日期时间部分<see cref='DatePart'/></param> 
			///	<returns>获取此实例的指定部分</returns> 
			EXPORT	inline int GetDatePart(DatePart dp)
			{
				switch(dp)
				{
				case Year:
					return this->GetYear();
				case yearDay:
					return this->GetDatePart(1);
				case Month:
					return this->GetMonth();
				case Day:
					return this->GetDay();
				case Hour:
					return this->GetHour();
				case Minute:
					return this->GetMinute();
				case Second:
					return this->GetSecond();
				case MillesSecond:
					return this->GetMillessecond();
				case WeekDay:
					return this->GetDayOfWeek();
				case Usec:
					return this->GetMicrosecond();
				default:
					return this->GetDayOfYear();
				}
			}
			///	<summary>
			///	设置此实例表示时间的时区。
			///	<code>原型：inline void SetTimeZone(TimeZone tz);</code>
			///	</summary>
			///	<param name="tc">指定时区<see cref='TimeZone'/></param> 
			EXPORT	inline void SetTimeZone(TimeZone tz)
			{
				unsigned long long tl =32+tz;
				tl=tl<<59;		//	留5位时区标识
				this->_Ticks=(tl | (_Ticks & this->TicksMask ));
			}
			///	<summary>
			///	获取此实例表示时间的时区。
			///	<code>原型：inline TimeZone GetTimeZone();</code>
			///	</summary>
			///	<returns>获取此实例表示时间的时区</returns> 
			EXPORT	inline TimeZone GetTimeZone()
			{
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				return (TimeZone)tz;
			};
			///	<summary>
			///	获取一个<see cref='DateTime'/>对象，该对象设置为此计算机上的当前日期和时间，表示为本地时间。
			///	<code>原型：inline static DateTime Now();</code>
			///	</summary>
			///	<returns>返回当前计算机上的当前日期和时间，表示为本地时间</returns> 
			EXPORT	inline static DateTime Now()
			{
				return DateTime();
			}
			///	<summary>
			///	获取此实例的时间部分。
			///	<code>原型：inline TimeSpan GetTimeOfDay();</code>
			///	</summary>
			///	<returns>获取此实例的当天的时间，它表示当天自午夜以来已经过时间的部分</returns> 
			EXPORT	inline TimeSpan GetTimeOfDay()
			{
				long long d=((_Ticks & this->TicksMask) % this->TicksPerDay);
				return TimeSpan(d);
			}
			///	<summary>
			///	获取当前时间的日期部分。
			///	<code>原型：inline static DateTime GetToday();</code>
			///	</summary>
			///	<returns>获取当前时间的日期部分，其时间组成部分设置为 00:00:00</returns> 
			EXPORT	inline static DateTime GetToday()
			{
				return DateTime::Now().GetDate();
			}
			///	<summary>
			///	获取一个<see cref='DateTime'/>对象,该对象设置为此计算机上的当前日期和时间，并表示为协调通用时间 (UTC)。
			///	<code>原型：inline static DateTime GetUtcNow();</code>
			///	</summary>
			///	<returns>此计算机上的当前日期和时间，其时间组成部分设置为 00:00:00</returns> 
			EXPORT	inline static DateTime GetUtcNow()
			{
				return DateTime(GMT0);
			}

			///	<summary>
			///	获取此时间实例中的指定部分，批量返回。
			///	<code>原型：inline void GetDateParts(int * year,int * month,int * day,int * dayOfyear,int * hour=NULL,
			///                                   int* minute=NULL,int *second=NULL,int *millis=NULL,int * ticks=NULL);</code>
			///	</summary>
			///	<param name="year">返回年</param> 
			///	<param name="month">返回月</param> 
			///	<param name="day">返回日</param> 
			///	<param name="hour">返回小时</param> 
			///	<param name="minute">返回分</param> 
			///	<param name="second">返回秒</param> 
			///	<param name="millisecond">返回毫秒</param> 
			///	<param name="ticks">返回微秒</param> 
			EXPORT inline void GetDateParts(int * year, int * month, int * day, int * dayOfyear, int * hour = NULL, int* minute = NULL, int *second = NULL, int *millis = NULL, int * ticks = NULL)
			{
				unsigned long long totalTicks=(_Ticks & this->TicksMask);
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				totalTicks+=tz * this->TicksPerHour ;
				if(totalTicks>MaxTicks)
					totalTicks=this->MaxTicks;
				int num2 = (int) (totalTicks / this->TicksPerDay);
				int num3 = num2 /this->DaysPer400Years;// 0x23ab1;
				num2 -= num3 * this->DaysPer400Years;
				int num4 = num2 / this->DaysPer100Years;//0x8eac;
				if (num4 == 4)
				{
					num4 = 3;
				}
				num2 -= num4 * this->DaysPer100Years;
				int num5 = num2 / this->DaysPer4Years;//0x5b5;
				num2 -= num5 * this->DaysPer4Years;//;
				int num6 = num2 / this->DaysPerYear;//0x16d;
				if (num6 == 4)
				{
					num6 = 3;
				}
				if(year)*year= (((((num3 * 400) + (num4 * 100)) + (num5 * 4)) + num6) + 1);
				num2 -= num6 * this->DaysPerYear;
				if(dayOfyear)*dayOfyear=(num2 + 1);
				const int * numArray = ((num6 == 3) && ((num5 != 0x18) || (num4 == 3))) ? DaysToMonth366 : DaysToMonth365;
				int index = num2 >> 6;
				while (num2 >= numArray[index])
				{
					index++;
				}
				if (month)*month=index;
				if(day)*day= ((num2 - numArray[index - 1]) + 1);
				
				long long dayMillis=totalTicks % this->TicksPerDay;
				if(hour)*hour=(int)(dayMillis / this->TicksPerHour);
				if(minute)*minute=(int) (dayMillis % this->TicksPerHour / this->TicksPerMinute);
				if(second)*second=(int) (dayMillis % this->TicksPerMinute / this->TicksPerSecond);
				if(millis)*millis=(int) (dayMillis % this->TicksPerSecond /this->TicksPerMillisecond);
				if(ticks)*ticks=(int) (dayMillis % this->TicksPerMillisecond);
			}
			///	<summary>
			///	获取此时间实例中的指定某一部分。
			///	<code>原型：inline int GetDatePart(int part);</code>
			///	</summary>
			///	<returns>返回对应时间值部分</returns> 
			EXPORT inline int GetDatePart(int part)
			{
				unsigned long long totalTicks=(_Ticks & this->TicksMask);
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				totalTicks+=tz * this->TicksPerHour ;
				if(totalTicks>MaxTicks)
					totalTicks=this->MaxTicks;
				int num2 = (int) (totalTicks / this->TicksPerDay);
				int num3 = num2 /this->DaysPer400Years;// 0x23ab1;
				num2 -= num3 * this->DaysPer400Years;
				int num4 = num2 / this->DaysPer100Years;//0x8eac;
				if (num4 == 4)
				{
					num4 = 3;
				}
				num2 -= num4 * this->DaysPer100Years;
				int num5 = num2 / this->DaysPer4Years;//0x5b5;
				num2 -= num5 * this->DaysPer4Years;//;
				int num6 = num2 / this->DaysPerYear;//0x16d;
				if (num6 == 4)
				{
					num6 = 3;
				}
				if (part == 0)
				{
					return (((((num3 * 400) + (num4 * 100)) + (num5 * 4)) + num6) + 1);
				}
				num2 -= num6 * this->DaysPerYear;
				if (part == 1)
				{
					return (num2 + 1);
				}
				const int * numArray = ((num6 == 3) && ((num5 != 0x18) || (num4 == 3))) ? DaysToMonth366 : DaysToMonth365;
				int index = num2 >> 6;
				while (num2 >= numArray[index])
				{
					index++;
				}
				if (part == 2)
				{
					return index;
				}
				return ((num2 - numArray[index - 1]) + 1);
			}

			///	<summary>
			///	返回新<see cref='DateTime'/>对象，其值为在当前时间实例上加一指定时间部分的指定值。
			///	<code>原型：inline DateTime Add(long long value, long long scale);</code>
			///	</summary>
			///	<param name="value">指定值</param> 
			///	<param name="scale">指定单位</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值为在当前时间实例上加一指定时间部分的指定值。</returns> 
			EXPORT	inline DateTime Add(long long value, long long scale)
			{
				long long num = (time_t) ((value * scale) + ((value >= 0) ? 0.5 : -0.5));
				if ((num <= 0-MaxTicks) || (num >= this->MaxTicks))
				{
					EXP("ArgumentOutOfRange_AddValue");
				}
				return this->AddTicks(num);
			}
			///	<summary>
			///	将指定的<see cref='TimeSpan'/>的值加到此实例的值上。
			///	<code>原型：inline DateTime Add(TimeSpan value);</code>
			///	</summary>
			///	<param name="value">指定时间间隔</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的时间间隔之和。</returns> 
			EXPORT inline DateTime Add(TimeSpan value)
			{
				return this->Add(value._ticks,1);
			};
			///	<summary>
			///	将指定的微秒数加到此实例的值上。
			///	<code>原型：inline DateTime AddTicks(long long ticks);</code>
			///	</summary>
			///	<param name="value">时间刻度数，微秒数</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的微秒时间之和。</returns> 
			EXPORT inline DateTime AddTicks(long long ticks)
			{
				long long internalTicks = (_Ticks & this->TicksMask);
				if ((ticks > (this->MaxTicks - internalTicks)) || (ticks < -internalTicks))
				{
					EXP("ArgumentOutOfRange_DateArithmetic");
				}
				return DateTime(this->_Ticks+ticks);
			};
			///	<summary>
			///	将指定的毫秒数加到此实例的值上。
			///	<code>原型：inline DateTime AddMillesSecond(long long value);</code>
			///	</summary>
			///	<param name="value">毫秒数</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的毫秒时间之和。</returns> 
			EXPORT inline DateTime AddMillesSecond(long long value)
			{
				return this->Add(value,this->TicksPerMillisecond);
			}
			///	<summary>
			///	将指定的天数加到此实例的值上。
			///	<code>原型：inline DateTime AddDays(int value);</code>
			///	</summary>
			///	<param name="value">天数，可以是负数也可以是正数</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的天数之和。</returns> 
			EXPORT inline DateTime AddDays(int value)
			{
				return this->Add(value, this->TicksPerDay);
			}
			///	<summary>
			///	将指定的小时数加到此实例的值上。
			///	<code>原型：inline DateTime AddHours(int value);</code>
			///	</summary>
			///	<param name="value">小时数，可以是负数也可以是正数</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的小时数之和。</returns> 
			EXPORT inline DateTime AddHours(int value)
			{
				return this->Add(value, this->TicksPerHour);
			}
			///	<summary>
			///	将指定的分钟数加到此实例的值上。
			///	<code>原型：inline DateTime AddMinutes(int value);</code>
			///	</summary>
			///	<param name="value">分钟数，可以是负数也可以是正数</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的分钟数之和。</returns> 
			EXPORT inline DateTime AddMinutes(int value)
			{
				return this->Add(value, this->TicksPerMinute);
			}
			///	<summary>
			///	将指定的月份数加到此实例的值上。
			///	<code>原型：inline DateTime AddMonths(int months);</code>
			///	</summary>
			///	<param name="months">月份数。可以是负数也可以是正数。</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与months 所表示的月份数之和。</returns> 
			EXPORT inline DateTime AddMonths(int months)
			{
				if ((months < -120000) || (months > 120000)) //一万年
				{
					EXP("ArgumentOutOfRange_DateTimeBadMonths");
				}
				int year , month,day ;
				GetDateParts(&year,&month,&day,NULL);
				int num4 = (month - 1) + months;
				if (num4 >= 0)
				{
					month = (num4 % 12) + 1;
					year += num4 / 12;
				}
				else
				{
					month=12 - abs(num4 - 11) % 12;			//month = 12 + ((num4 + 1) % 12);   //负数取模是MS特有的算法
					year +=(num4 - 11) / 12;
				}
				if ((year < 1) || (year > 9999))
				{
					EXP("ArgumentOutOfRange_DateArithmetic");
				}
				int num5 = DaysInMonth(year, month);
				if (day > num5)
				{
					day = num5;
				}
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				long long tl=DateToTicks(year, month, day)-tz*TicksPerHour +(long long)(((_Ticks & this->TicksMask)+tz*TicksPerHour) % this->TicksPerDay);
				return DateTime(tl,(TimeZone)tz);
 			}
			///	<summary>
			///	将指定的秒数加到此实例的值上。
			///	<code>原型：inline DateTime AddMonths(int value);</code>
			///	</summary>
			///	<param name="value">秒数。可以是负数也可以是正数。</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的秒数之和。</returns> 
			EXPORT inline DateTime AddSeconds(int value)
			{
				return this->Add(value, this->TicksPerSecond);
			}
			///	<summary>
			///	将指定的年份数加到此实例的值上。
			///	<code>原型：inline DateTime AddYears(int value);</code>
			///	</summary>
			///	<param name="value">年份数。可以是负数也可以是正数。</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的年份数之和。</returns> 
			EXPORT inline DateTime AddYears(int value)
			{
				if ((value < -10000) || (value > 10000))
				{
					EXP("years: ArgumentOutOfRange_DateTimeBadYears");
				}
				return this->AddMonths(value * 12);
			}
			///	<summary>
			///	将指定的数值添加加到此实例的指定部分值上。
			///	<code>原型：inline DateTime AddDataPart(int number,DatePart dp);</code>
			///	</summary>
			///	<param name="number">可以是负数也可以是正数。</param> 
			///	<param name="dp">指定要添加到此实例的哪个部分上。</param> 
			///	<returns>一个新的<see cref='DateTime'/>对象，其值是此实例所表示的日期和时间与value 所表示的数之和。</returns> 
			EXPORT inline DateTime AddDataPart(int number, DatePart dp)
			{
				switch(dp)
				{
				case Year:
					return this->AddYears(number);
				case Month:
					return this->AddMonths(number);
				case Day:
					return this->AddDays(number);
				case Hour:
					return this->AddHours(number);
				case Minute:
					return this->AddMinutes(number);
				case Second:
					return this->AddSeconds(number);
				case MillesSecond:
					return this->AddMillesSecond(number);
				case Usec:
					return this->AddTicks(number);
				default:
					return this->AddDays(number);
				}
			}


			///	<summary>
			///	比较<see cref='DateTime'/>两个实例，并返回它们相对值的指示。
			///	<code>原型：inline static int Compare(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="t1">第一个<see cref='DateTime'/>。</param> 
			///	<param name="t2">第二个<see cref='DateTime'/>。</param> 
			///	<returns>有符号数字，指示 t1 和 t2 的相对值。值类型 条件 小于零 t1 小于 t2。 零 t1 等于 t2。 大于零 t1 大于 t2。</returns> 
			EXPORT inline static int Compare(DateTime t1, DateTime t2)
			{
				long long d=t1.GetTicks()-t2.GetTicks();
				if (d > 0)
				{
					return 1;
				}
				if (d < 0)
				{
					return -1;
				}
				return 0;
			}
			///	<summary>
			///	将此实例与指定<see cref='DateTime'/>对象进行比较并返回对其相对值的指示.
			///	<code>原型：inline int CompareTo(DateTime value);</code>
			///	</summary>
			///	<param name="value">要比较的<see cref='DateTime'/>对象。</param>
			///	<returns>有符号数字，指示此实例和 value 参数的相对值。值说明: 小于零 此实例小于 value。 零 此实例等于 value。 大于零 此实例大于value。。</returns> 
			EXPORT inline int CompareTo(DateTime value)
			{
				long long d=(_Ticks & this->TicksMask)-value.GetTicks();
				if (d > 0)
				{
					return 1;
				}
				if (d < 0)
				{
					return -1;
				}
				return 0;
			}
			///	<summary>
			///	返回指定年和月中的天数
			///	<code>原型：inline static int DaysInMonth(int year, int month);</code>
			///	</summary>
			///	<param name="year">年份</param>
			///	<param name="month">月份（介于 1 到 12 之间的一个数字）。</param>
			///	<returns> 指定 year 中 month 的天数。例如，如果 month 等于 2（表示二月），则返回值为 28 或 29，具体取决于 year 是否为闰年。</returns> 
			EXPORT inline static int DaysInMonth(int year, int month)
			{
				if ((month < 1) || (month > 12))
				{
					EXP("month: ArgumentOutOfRange_Month");
				}
				const int * numArray = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
				return (numArray[month] - numArray[month - 1]);
			}
			///	<summary>
			///	返回一个值，该值指示此实例是否与指定的<see cref='DateTime'/>实例相等
			///	<code>原型：inline bool Equals(DateTime value);</code>
			///	</summary>
			///	<param name="value">要与此实例进行比较的<see cref='DateTime'/>实例</param>
			///	<param name="month">月份（介于 1 到 12 之间的一个数字）。</param>
			///	<returns> 如果 value 参数等于此实例的值，则为 true；否则为 false。</returns> 
			EXPORT inline bool Equals(DateTime value)
			{
				return ((_Ticks & this->TicksMask)==value.GetTicks());
			}
			///	<summary>
			///	返回一个值，该值指示<see cref='DateTime'/>的两个实例是否相等
			///	<code>原型：inline static bool Equals(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="t1">要进行比较的<see cref='DateTime'/>实例1</param>
			///	<param name="t2">要进行比较的<see cref='DateTime'/>实例2。</param>
			///	<returns> 如果两个<see cref='DateTime'/> 值相等，则为 true；否则为 false。</returns> 
			EXPORT inline static bool Equals(DateTime t1, DateTime t2)
			{
				return (t1.GetTicks()==t2.GetTicks());
			}
			///	<summary>
			///	返回指定的年份是否为闰年的指示
			///	<code>原型：inline static bool Equals(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="year">四位数年份</param> 
			///	<returns> 如果 year 为闰年，则为 true；否则为 false。</returns> 
			EXPORT inline static bool IsLeapYear(int year)
			{
				if ((year < 1) || (year > 9999))
				{
					EXP("ArgumentOutOfRange_Year");
				}
				if ((year % 4) != 0)
				{
					return false;
				}
				if ((year % 100) == 0)
				{
					return ((year % 400) == 0);
				}
				return true;
			}
			///	<summary>
			///	将相对于格林威治时间所表示的秒数加上个指定秒数转换为标准字符串形式返回
			///	<code>原型：inline static string getDateAddDur(time_t NowTime,int dur=0);</code>
			///	</summary>
			///	<param name="NowTime">时间秒</param> 
			///	<param name="dur">要添加的秒数</param> 
			///	<returns> NowTime加上dur后所表示的时间对应的字符串形式。</returns> 
			EXPORT inline static string getDateAddDur(time_t NowTime, int dur = 0)
			{
				struct tm * _tm;
				NowTime +=dur;  
				_tm   =   localtime(&NowTime);
				char p[40];
				sprintf(p,"%04d-%02d-%02d %.2d:%02d:%02d",_tm->tm_year,_tm->tm_mon,_tm->tm_mday,_tm->tm_hour,_tm->tm_min,_tm->tm_sec);
				return p;
			}
			///	<summary>
			///	将字符串表示的时间加上指定的秒数再返回字符串时间
			///	<code>原型：inline static string getDateAddDur(string str,int dur=0);</code>
			///	</summary>
			///	<param name="str">字符串形式表示的时间</param> 
			///	<param name="dur">要添加的秒数</param> 
			///	<returns> str所表示时间加上dur后对应的字符串表示形式。</returns> 
			EXPORT inline static string getDateAddDur(string str, int dur = 0)
			{
				if(dur==0)return str;
				DateTime dt;
				celerityParse::Parse(dt,str.c_str());
				return dt.AddSeconds(dur).ToString();
				//StringParser parser2;
				//long long ticks= parser2.Parse(str);
				//ticks=ticks/DateTime::TicksPerSecond + dur;
				//time_t result=(time_t)(ticks-TicksPerUTCSta) ;   // GTM8
				//struct tm * _tm  =   localtime(&result);
				//char p[40];
				//sprintf(p,"%04d-%02d-%02d %.2d:%02d:%02d",_tm->tm_year+1900,_tm->tm_mon+1,_tm->tm_mday,_tm->tm_hour,_tm->tm_min,_tm->tm_sec);
				//return p;
			}
			///	<summary>
			///	将指定时间各部分加上指定秒后转换为本地时间字符串表示形式
			///	<code>原型：inline static string getDateAddDur(int year, int month, int day,
			///                                        int hour=0, int minute=0, int second=0,int dur=0);</code>
			///	</summary>
			///	<param name="year">年</param> 
			///	<param name="month">月</param> 
			///	<param name="day">日</param> 
			///	<param name="hour">时</param> 
			///	<param name="minute">分</param> 
			///	<param name="second">秒</param> 
			///	<param name="dur">要添加的秒数</param>  
			///	<returns>对应的字符串表示形式。</returns> 
			EXPORT 	inline static string getDateAddDur(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int dur = 0)
			{
				char p[40];
				if(dur==0)
				{
					sprintf(p,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
					return p;
				}
				else
				{
					DateTime dt(year,month,day,hour,minute,second);
					return dt.AddSeconds(dur).ToString();
				}
			}
			///	<summary>
			///	获取UTC相对秒数
			///	<code>原型：inline static time_t DateToUTCSecond(int year, int month, int day,
			///                                         int hour=0, int minute=0, int second=0);</code>
			///	</summary>
			///	<param name="year">年</param> 
			///	<param name="month">月</param> 
			///	<param name="day">日</param> 
			///	<param name="hour">时</param> 
			///	<param name="minute">分</param> 
			///	<param name="second">秒</param> 
			///	<returns>相对UTC秒数。</returns> 
			EXPORT 	inline static time_t DateToUTCSecond(int year, int month, int day, int hour = 0, int minute = 0, int second = 0)
			{
				time_t result;
				long long allsec;				
				if (((year >= 1) && (year <= 0x270f)) && ((month >= 1) && (month <= 12)))
				{
					const int * numArray = IsLeapYear(year) ? DaysToMonth366 : DaysToMonth365;
					if ((day >= 1) && (day <= (numArray[month] - numArray[month - 1])))
					{
						int num = year - 1;
						int num2 = ((((((num * 0x16d) + (num / 4)) - (num / 100)) + (num / 400)) + numArray[month - 1]) + day) - 1;
						allsec= ((long long)num2 * DateTime::TicksPerDay/DateTime::TicksPerSecond);
					}
				}
				allsec+= ((hour * 0xe10) + (minute * 60)) + second;	
				result=(time_t)(allsec-DateTime::localTimeZone * 3600 -TicksPerUTCSta/DateTime::TicksPerSecond) ;   // 减去当地时区时间
				return result;
			}
		public:

			///	<summary>
			///	从此实例中减去指定的日期和时间
			///	<code>原型：inline TimeSpan Subtract(DateTime value);</code>
			///	</summary>
			///	<param name="value"><see cref='DateTime'/>的一个实例</param> 
			///	<returns>相差时间间隔<see cref='TimeSpan'/>,它等于此实例所表示的日期和时间减去 value 所表示的日期和时间</returns> 
			EXPORT inline TimeSpan Subtract(DateTime value)
			{
				return TimeSpan(this->GetTicks()-value.GetTicks());
			};
			///	<summary>
			///	从此实例中减去指定时间间隔
			///	<code>原型：inline DateTime &amp;Subtract(TimeSpan value);</code>
			///	</summary>
			///	<param name="value"><see cref='TimeSpan'/>的一个实例</param> 
			///	<returns>此实例本身</returns> 
			EXPORT inline DateTime &Subtract(TimeSpan value)
			{
				this->_Ticks-=value.getTotalTicks();
				return *this;
			};
			///	<summary>
			///	将此实例的值转换为其等效的长日期字符串表示形式 yyyy年mm月dd日
			///	<code>原型：inline string ToLongDateString();</code>
			///	</summary>
			///	<returns>一个字符串,形如：yyyy年mm月dd日。</returns> 
			EXPORT inline string ToLongDateString()
			{
				int year,month,day;
				GetDateParts(&year,&month,&day,NULL);

				char p[20];
				char f[20];
				strcpy(f,"%d年%d月%d日");
				sprintf(p,f,year,month,day);
				//_result=p;
				return p;
			}
			///	<summary>
			///	将此实例的值转换为其等效的长时间字符串表示形式 hh:mi:ss
			///	<code>原型：inline string ToLongTimeString();</code>
			///	</summary>
			///	<returns>一个字符串，形如：hh:mi:ss。</returns> 
			EXPORT 	inline string ToLongTimeString()
			{
				return this->ToString(StaTime);
			} 
			///	<summary>
			///	将此实例的值转换为其等效的短日期字符串表示形式 yyyy-mm-dd
			///	<code>原型：inline string ToShortDateString();</code>
			///	</summary>
			///	<returns>一个字符串，形如：yyyy-mm-dd。</returns> 
			EXPORT inline string ToStaDateString()
			{
				return this->ToString(StaDate);
			}
			///	<summary>
			///	将此实例的值转换为其等效的短日期字符串表示形式 yyyymmdd
			///	<code>原型：inline string ToShortDateString();</code>
			///	</summary>
			///	<returns>一个字符串，形如：yyyymmdd。</returns> 
			EXPORT inline string ToShortDateString()
			{
				return this->ToString(ShotDate);
			}
			///	<summary>
			///	将此实例的值转换为其等效的短时间字符串表示形式 hh:mi
			///	<code>原型：inline string ToShortTimeString();</code>
			///	</summary>
			///	<returns>一个字符串，形如：hh:mi。</returns> 
			EXPORT inline string ToShortTimeString()
			{
				return this->ToString(ShotTime);
			}
			///	<summary>
			///	将此实例的值转换为其等效的短时间字符串表示形式 yyyymmddhhmiss
			///	<code>原型：inline string ToShotDateTimeString();</code>
			///	</summary>
			///	<returns>一个字符串，形如：yyyymmddhhmiss。</returns> 
			EXPORT inline string ToShotDateTimeString(){ return this->ToString(ShotDateTime); }
			///	<summary>
			///	将此实例的值转换为其等效的字符串表示
			///	<code>原型：inline string ToString(DateTimeStyles  format=StaDateTime);</code>
			///	</summary>
			///	<param name="format">指定返回字符串格式</param> 
			///	<returns>此实例的值的字符串表示形式，格式由format指定。</returns> 
			EXPORT inline string ToString(DateTimeStyles  format = StaDateTime)
			{
				const string * weekName=this->WeekName[this->GetDayOfWeek()];
				int year,month,day,hour,minute,second,millis;
				GetDateParts(&year,&month,&day,NULL,&hour,&minute,&second,&millis);
				const string * monthName=MonthNames[month];
				char p[30];
				//memset(p,0,40);
				//memset(f,0,40);
				switch(format)
				{
				case StaUTC:				// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
					sprintf(p,"%s %s %d %02d:%02d:%02d %d",weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
					break;
				case StaDateTime:// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				case LongDate:				// yyyy年mm月dd日
					sprintf(p,"%04d年%d月%d日",year,month,day);
					break;
				case StaDate:		// yyyy-mm-dd
					sprintf(p,"%04d-%02d-%02d",year,month,day);
					break;
				case StaTime: 			// 	hh:mi:ss
					sprintf(p,"%02d:%02d:%02d",hour,minute,second);
					break;
				case ShotDate: 			// 	yyyymmdd
					sprintf(p,"%04d%02d%02d",year,month,day);
					break;
				case ShotTime: 				// 	 hh:mi 
					sprintf(p,"%d:%02d",hour,minute);
					break;
				case ShotDateTime: 				// 	yyyymmddhhmiss
					sprintf(p,"%04d%02d%02d%02d%02d%02d",year,month,day,hour,minute,second);
					break;
				default:			// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				}
				//_result=p;
				return p;
			}
			///	<summary>
			///	使用指定的时区信息将此实例的值转换为它的等效字符串表示形式
			///	<code>原型：inline string ToString(TimeZone tz);</code>
			///	</summary>
			///	<param name="tz">指定时区</param> 
			///	<returns>此实例的值的字符串表示形式。</returns> 
			EXPORT inline string ToString(TimeZone tz)
			{
				DateTime temp=DateTime(this->_Ticks ,tz);
				return  temp.ToString();
			};
			///	<summary>
			///	使用指定格式将此实例的值转换成其等效的字符串表示
			///	<code>原型：inline string ToString(TimeZone tz);</code>
			///	</summary>
			///	<param name="format">格式字符串</param> 
			///	<returns>format 指定的此实例的值的字符串表示形式。。</returns> 
			EXPORT inline string ToString(string format)
			{
				string temp=format;
				format=String::ToLower(String::Trim(temp));
				if(format=="yyyy-mm-dd hh:mi:ss")
				{
					return ToString(StaDateTime);
				}
				else if(format=="yyyy年mm月dd日")
				{
					return ToString(LongDate);
				}
				else if(format=="yyyy-mm-dd")
				{
					return ToString(StaDate);
				}
				else if(format=="yyyymmdd")
				{
					return ToString(ShotDate);
				}
				else if(format=="hh:mi:ss")
				{
					return ToString(StaTime);
				}
				else if(format=="hh:mi")
				{
					return ToString(ShotTime);
				}
				else if(format=="yyyymmddhhmiss")
				{
					return ToString(ShotDateTime);
				}
				else if(format=="yyyymm")
				{
					return GetYearMonthStr();
				}
				else
				{
					return ToString(StaUTC);
				}
			}


			///	<summary>
			///	使用指定格式和时区将此实例的值转换为它的等效字符串表示形式
			///	<code>原型：inline string ToString(string format,TimeZone tz);</code>
			///	</summary>
			///	<param name="format">格式字符串</param> 
			///	<param name="tz">指定时区</param> 
			///	<returns>format 和tz 指定的此实例的值的字符串表示形式。。</returns> 
			EXPORT inline string ToString(string format, TimeZone tz)
			{
				DateTime temp=DateTime(this->_Ticks ,tz);
				return temp.ToString(format);
			}
			///	<summary>
			///	返回此实例的年月部分
			///	<code>原型：inline string GetYearMonthStr();</code>
			///	</summary>
			///	<returns>6位字符串形式表示年月。</returns> 
			EXPORT inline string GetYearMonthStr()
			{
				char p[20];
				memset(p,0,20);
				char f[]="%04d%02d";
				int year,month;
				GetDateParts(&year,&month,NULL,NULL);
				sprintf(p,f,year,month);
				return p;
			};
			///	<summary>
			///	返回8位整数表示的此实例的年月日部分
			///	<code>原型：inline string GetYearMonthDay();</code>
			///	</summary>
			///	<returns>8位整数表示的此实例的年月日。</returns> 
			EXPORT inline int GetYearMonthDay()
			{
				int year,month,day;
				GetDateParts(&year,&month,&day,NULL);
				return year*10000+month*100+day;
			};
			///	<summary>
			///	返回6位整数表示的此实例的年月部分
			///	<code>原型：inline int GetYearMonth();</code>
			///	</summary>
			///	<returns>6位整数表示的此实例的年月。</returns> 
			EXPORT inline int GetYearMonth()
			{
				int year,month;
				GetDateParts(&year,&month,NULL,NULL);
				return year*100+month;
			};
			///	<summary>
			///	返回14位整数表示的此实例的年月日时分秒部分
			///	<code>原型：inline long long GetFullDate();</code>
			///	</summary>
			///	<returns>14位整数表示的此实例的年月日时分秒部分。</returns> 
			EXPORT inline long long GetFullDate()
			{
				int year,month,day,hour,minute,second,millis;
				GetDateParts(&year,&month,&day,NULL,&hour,&minute,&second,&millis);
				long long res=year*10000000000L;
				return res+month*100000000L+day*1000000L+hour*10000L+minute*100L+second;
			}
			///	<summary>
			///	使用指定的时区信息和格式化样式,将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static DateTime Parse2(const char * s, DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">要解析的字符串</param> 
			///	<param name="styles">指定s表示时间的格式</param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			///	<returns><see cref='DateTime'/>,等效于由 tz 和 styles 所指定的 s 中包含的日期和时间。</returns> 
			EXPORT inline static DateTime Parse2(const char * s, DateTimeStyles styles = StaDateTime, TimeZone tz = localTimeZone)
			{
				DateTime res;
				celerityParse::Parse(res,s,styles,tz);
				return res;
			}
			///	<summary>
			///	使用指定的时区信息和格式化样式,将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static DateTime Parse2(string &amp; s, DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">要解析的字符串</param> 
			///	<param name="styles">指定s表示时间的格式</param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			///	<returns><see cref='DateTime'/>,等效于由 tz 和 styles 所指定的 s 中包含的日期和时间。</returns> 
			EXPORT inline static DateTime Parse2(string & s, DateTimeStyles styles = StaDateTime, TimeZone tz = localTimeZone)
			{
				DateTime res;
				celerityParse::Parse(res,s.c_str(),styles,tz);
				return res;
			}
			///	<summary>
			///	将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static DateTime Parse(string s, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">要解析的字符串,格式不定。但仅限于： yyyy-mm-dd hh:mm:ss "yyyy-mm-dd"
			///                "yyyy-mm-dd hh:mm:ss"  Mon May 14 02:03:55 2007(星期几 月份 日期 时:分:秒 年) </param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			///	<returns><see cref='DateTime'/>,等效于由 tz所指定的 s 中包含的日期和时间。</returns> 
			EXPORT inline static DateTime Parse(string s, TimeZone tz = localTimeZone)
			{
				StringParser parser2;
				long long ticks= parser2.Parse(s);
				ticks -= tz * TicksPerHour;
				return DateTime(ticks,tz);
			}
			///	<summary>
			///	将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static void Parse(DateTime &amp;result,string s, TimeZone tz=localTimeZone)</code>
			///	</summary>
			///	<param name="result"> 当此方法返回时，如果转换成功，则包含与 s 中包含的日期和时间等效的 Common.DateTime 值；如果转换失败，则为 Common.DateTime.MinValue。如果
			///     s 参数为空，或者不包含日期和时间的有效字符串表示形式，则转换失败。该参数未经初始化即被传递。</param> 
			///	<param name="s">要解析的字符串,格式不定。但仅限于： yyyy-mm-dd hh:mm:ss "yyyy-mm-dd"
			///                "yyyy-mm-dd hh:mm:ss"  Mon May 14 02:03:55 2007(星期几 月份 日期 时:分:秒 年) </param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			EXPORT inline static void Parse(DateTime &result, string s, TimeZone tz = localTimeZone)
			{
				result=DateTime::Parse(s,tz);
			}
			///	<summary>
			///	使用指定的时区信息和格式化样式,将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static void Parse2(DateTime &amp;result,const char *s,
			///                                 DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="result"><see cref='DateTime'/>,等效于由 tz 和 styles 所指定的 s 中包含的日期和时间。</param> 
			///	<param name="s">要解析的字符串</param> 
			///	<param name="styles">指定s表示时间的格式</param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			EXPORT inline static void Parse2(DateTime &result, const char *s, DateTimeStyles styles = StaDateTime
				, TimeZone tz=localTimeZone)
			{
				celerityParse::Parse(result,s,styles,tz);
			}
			///	<summary>
			///	使用指定的时区信息和格式化样式,将日期和时间的指定字符串表示形式转换为其等效的<see cref='DateTime'/>
			///	<code>原型：inline static void Parse2(DateTime &amp;result,string &amp; s,
			///                                 DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="result"><see cref='DateTime'/>,等效于由 tz 和 styles 所指定的 s 中包含的日期和时间。</param> 
			///	<param name="s">要解析的字符串</param> 
			///	<param name="styles">指定s表示时间的格式</param> 
			///	<param name="tz">指定s表示时间的时区</param> 
			EXPORT inline static void Parse2(DateTime &result, string &s, DateTimeStyles styles = StaDateTime
				, TimeZone tz=localTimeZone)
			{
				celerityParse::Parse(result,s.c_str(),styles,tz);
			}
			///	<summary>
			///	从指定数字，指定格式，指定添加值和添加部分获取时间
			///	<code>原型：inline static void Parse3(long dateVal,int style,int intType,long inteval);</code>
			///	</summary>
			EXPORT inline static DateTime Parse3(long long dateVal, int style, int intType, long interval, TimeZone tz = localTimeZone)
			{
				int yyyy=0,mm=0,dd=0,hh=0,mi=0,ss=0,mii=0,ticks=0;
				switch(style)
				{
				case 1:	//	yyyymm
					yyyy=dateVal/100;
					mm=dateVal%100;
					break;
				case 2://	yyyymmdd
					yyyy=dateVal/10000;
					mm=dateVal/100%100;
					dd=dateVal%100;
					break;
				case 3://	yyyymmddhh
					yyyy=dateVal/1000000;
					mm=dateVal/10000%100;
					dd=dateVal/100%100;
					hh=dateVal%100;
					break;
				case 4://	yyyymmddhhmi
					yyyy=dateVal/100000000L;
					mm=dateVal/1000000%100;
					dd=dateVal/10000%100;
					hh=dateVal/100%100;
					mi=dateVal%100;
					break;
				case 5://	yyyymmddhhmiss
					yyyy=dateVal/10000000000L;
					mm=dateVal/100000000L%100;
					dd=dateVal/1000000%100;
					hh=dateVal/10000%100;
					mi=dateVal/100%100;
					ss=dateVal%100;
					break;
				case 6://	yyyymmddhhmisstk
					yyyy=dateVal/10000000000000L;
					mm=dateVal/100000000000L%100;
					dd=dateVal/1000000000L%100;
					hh=dateVal/10000000%100;
					mi=dateVal/100000%100;
					ss=dateVal/1000%100;
					mii=dateVal%1000;
					break;
				case 7://	  yyyymmddhhmiss000000
					yyyy=dateVal/10000000000000000L;
					mm=dateVal/100000000000000L%100;
					dd=dateVal/1000000000000L%100;
					hh=dateVal/10000000000L%100;
					mi=dateVal/100000000L%100;
					ss=dateVal/1000000%100;
					mii=dateVal/1000%100;
					ticks=dateVal%1000%100;
					break;
				}
				DateTime dt(yyyy, mm,dd, hh,mi, ss,mii,ticks,tz);
				if(intType==0 || interval==0)
					return dt;
				return dt.AddDataPart(interval,DatePart(intType-1));
			}
			///	<summary>
			///	获取前几天或前几月
			///	<code>原型：inline static string getPreDate(string yyyymmdd,int pNum);</code>
			///	</summary>
			///	<param name="yyyymmdd">8位或6位字符串表示的时间</param> 
			///	<param name="pNum">要减去的数值（天或月）</param> 
			///	<returns> yyyymmdd以时间运算方法减去pNum后的字符串值 。</returns> 
			EXPORT inline static string getPreDate(string yyyymmdd, int pNum)
			{
				if(yyyymmdd.size()==8)
				{
					DateTime dt(Convert::ToInt(yyyymmdd));
					return dt.AddDays(0-pNum).ToString(ShotDate);
				}
				else if(yyyymmdd.size()==6)
				{
					DateTime dt(Convert::ToInt(yyyymmdd+"01"));
					return dt.AddMonths(0-pNum).GetYearMonthStr();
				}
				else
				{
					return yyyymmdd;
				}
			};
			///	<summary>
			///	将此实例的值转换为标准<see cref='DateTimeStyles'/>格式说明符支持的所有字符串表示形式.
			///	<code>原型：inline void GetDateTimeFormats(Array&lt;string> &amp;arr);</code>
			///	</summary>
			///	<param name="arr">字符串数组，其中的每个元素都表示此实例的值，并且已用标准 Common.DateTime 格式说明符之一格式化。</param> 
			EXPORT inline void GetDateTimeFormats(Array<string> &arr)
			{
				Array<string> tempArr=Array<string>(7);
				arr=tempArr;
				const string * weekName=this->WeekName[this->GetDayOfWeek()];
				int year,month,day,hour,minute,second,millis;
				GetDateParts(&year,&month,&day,NULL,&hour,&minute,&second,&millis);
				const string * monthName=MonthNames[month];


				char p[40];
				char f[40];
				int len=0;
				memset(p,0,40);		
				memset(f,0,40);		
				strcpy(f,"%s %s %d %02d:%02d:%02d %d");// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
				len=sprintf(p,f,weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
				p[len]='\0';
				arr[0]= p;
							
				strcpy(f,"%04d-%02d-%02d %d:%02d:%02d");   // yyyy-mm-dd hh:mi:ss
				len=sprintf(p,f,year,month,day,hour,minute,second);
				p[len]='\0';
				arr[1]= p;

				strcpy(f,"%d年%d月%d日");					// yyyy年mm月dd日
				len=sprintf(p,f,year,month,day);
				p[len]='\0';
				arr[2]= p;

				strcpy(f,"%04d-%d-%d"); 						// yyyy-mm-dd
				len=sprintf(p,f,year,month,day);
				p[len]='\0';
				arr[3]= p;

				strcpy(f,"%d:%02d:%02d");					// 	hh:mi:ss
				len=sprintf(p,f,hour,minute,second);
				p[len]='\0';
				arr[4]= p;
		 
				strcpy(f,"%04d%02d%02d");					// 	yyyymmdd
				len=sprintf(p,f,year,month,day);
				p[len]='\0';
				arr[5]= p;
					
				strcpy(f,"%d:%02d");						// 	 hh:mi 
				len=sprintf(p,f,hour,minute);
				p[len]='\0';
				arr[6]= p;
			}
			///	<summary>
			///	将此实例的值转换为标准<see cref='DateTimeStyles'/>格式说明符支持的所有字符串表示形式.
			///	<code>原型：inline void GetDateTimeFormats(Array&lt;string> &amp;arr);</code>
			///	</summary>
			///	<param name="arr">字符串数组，其中的每个元素都表示此实例的值，并且已用标准 <see cref='DateTimeStyles'/>格式说明符之一格式化。</param> 
			///	<param name="tz">指定时区</param> 
			EXPORT inline void GetDateTimeFormats(Array<string> &arr, TimeZone tz)
			{
				DateTime temp=DateTime(this->_Ticks ,tz);
				temp.GetDateTimeFormats(arr);
			}
		protected: 
			class celerityParse
			{
				public:
				inline static void Parse(DateTime & res,const char * s,DateTimeStyles styles=StaDateTime
					, TimeZone tz=localTimeZone)
				{
					s=String::Trim((char *)s);
					if(s==NULL || s[0]==0)
					{
						res=DateTime(1,1,1,0,0,0,0,0,tz);
						return;
					}
					int year=0,month=0,day=0,hour=0,minute=0,second=0,millis=0;
					int len=0;
					switch(styles)
					{
					case StaUTC:				// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
						{
							char weekName[4],monthName[4];
							memset(monthName,0,4);
							len=sscanf(s, "%s %s %d %d:%d:%d %d", weekName,monthName,&day,&hour,&minute,&second,&year);
							if(len!=7)EXP(String("输入字符时间\"")+s+String("\"不是形如格式的\"Mon May 14 02:03:55 2007\"字符串"));
							for(int i=1;i<=12;i++)
							{
								if(strcmp(MonthNames[i][2].c_str(),monthName)==0)
								{
									month=i;break;
								}
							}
							if(month==0)EXP(String("获取的月份无法匹配")+monthName);
							res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						}
						break;
					case StaDateTime:// yyyy-mm-dd hh:mi:ss
						len=sscanf(s, "%d-%d-%d %d:%d:%d", &year,&month,&day,&hour,&minute,&second);
						if(len!=6)EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"yyyy-mm-dd hh:mi:ss\"字符串");
						res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						break;
					case LongDate:				// yyyy年mm月dd日
						len=sscanf(s, "%d年%d月%d日", &year,&month,&day);
						if(len!=3)EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"yyyy年mm月dd日\"字符串");
						res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						break;
					case StaDate:		// yyyy-mm-dd
						len=sscanf(s, "%d-%d-%d", &year,&month,&day);
						if(len!=3)EXP(String("输入字符时间\"")+s+"\"不是形如格式的\"yyyy-mm-dd\"字符串");
						res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						break;
					case ShotDate: 			// 	yyyymmdd
						res=DateTime(atoi(s),tz);
						break;
					case ShotDateTime: 				// 	yyyymmddhhmiss
						{
							long long val=atoll(s);
							second	=	val%100;
							minute	=	val/100%100;
							hour	=	val/10000%100;
							day		=	val/1000000%100;
							month	=	val/100000000%100;
							year	=	val/10000000000LL;
							res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						}
						break;
					default:
						EXP(String("输入字符串\"")+s+"不是已知可识别的日期格式");
						break;
					}
				}
			};
			//
			//摘要：
			//		使用字符串拆分法
			//		yyyy-mm-dd hh:mm:ss
			//		//	"yyyy-mm-dd"     "yyyy-mm-dd hh:mm:ss"		"yyyy-mm-dd hh:mm:ss.ff"
			//	// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
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
				inline void NextChar()
				{
					if (this->pos < this->len)
					{
						this->pos++;
					}
					this->ch = ((this->pos < this->len) ? this->str[this->pos] : '\0');
				}
				inline long long Parse(string &str)
				{
					string s=str;
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
				inline bool TryParse(string &s,long long &value)
				{
					long long  time=0;
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
					int dates[3];
					if (this->NextNonDigit() == '-' || this->NextNonDigit() == '/')	// "yyyy/mm/dd "	"yyyy-mm-dd"     "yyyy-mm-dd hh:mm:ss"		"yyyy-mm-dd hh:mm:ss.ff"
					{
						if (!this->ParseInt(9999,  dates[0]))
						{
							return false;
						}
						this->NextChar();
						if (!this->ParseInt(12,  dates[1]))
						{
							return false;
						}
						const int * numArray = DateTime::IsLeapYear(dates[0]) ? DaysToMonth366 : DaysToMonth365;
						this->NextChar();
						if (!this->ParseInt((numArray[dates[1]] - numArray[dates[1] - 1]),  dates[2]))
						{
							return false;
						}
						time=DateToTicks(dates[0],dates[1],dates[2]);
						long long  num3=0;
						this->SkipBlanks();
						if(this->pos<this->str.size())
						{
							if (!this->ParseTime( num3))
							{
								return false;
							}
						}
						time += num3;
						value=time;
						return true;
					}
					else												//	// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
					{
						String::Trim(s);
						Array<string> parts;
						String::Split(parts,s,32);
						int year,month,day;
						for(int i=1;i<13;i++)
						{
							if(strcmp(parts[1].c_str(),DateTime::MonthNames[i][2].c_str()))
							{
								month=i;
								break;
							}
						}
						day=Convert::ParseInt(parts[2]);
						year=Convert::ParseInt(parts[4]);
						time=DateToTicks(year,month,day);
						time+=TimeSpan::Parse(parts[3]).getTotalTicks();
						value=time;
						value = time;
						return true;
					}
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
					time = (i * DateTime::TicksPerHour);
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
					time += (i * DateTime::TicksPerMinute);
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
			};

/////////////////////////////__OTL_date__///////////////////////////////////////////////
#if defined(__OTL_H__)
		public:
			///	<summary>
			///	将.otl_datetime 对象转换为指定格式的字符串
			///	<code>原型：static string ToString(otl_datetime &amp;_tm,DateTimeStyles style);</code>
			///	</summary>
			///	<param name="_tm">OTL时间对象。</param> 
			///	<param name="style">指定返回字符串格式。</param> 
			///	<returns>等效的-tm字符串表示形式。</returns> 
			EXPORT 	static string ToString(otl_datetime &_tm,DateTimeStyles style)
			{
				//int year=_tm.year;
				//int month=_tm.month;
				//int day=_tm.day;
				//int hour=_tm.hour;
				//int minute=_tm.minute;
				//int second=_tm.second;
				char p[40];
				memset(p,0,40);
				switch(style)
				{
				case StaUTC:				// Mon May 14 02:03:55 2007	// 星期几 月份 日期 时:分:秒 年
					{
						DateTime dt=DateTime(_tm);
						return dt.ToString(style);
					}
					break;
				case StaDateTime:	// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",_tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second);
					break;
				case LongDate:				// yyyy年mm月dd日
					sprintf(p,"%04d年%d月%d日",_tm.year,_tm.month,_tm.day);
					break;
				case StaDate:		// yyyy-mm-dd
					sprintf(p,"%04d-%02d-%02d",_tm.year,_tm.month,_tm.day);
					break;
				case StaTime: 			// 	hh:mi:ss
					sprintf(p,"%d:%02d:%02d",_tm.hour,_tm.minute,_tm.second);
					break;
				case ShotDate: 			// 	yyyymmdd
					sprintf(p,"%04d%02d%02d",_tm.year,_tm.month,_tm.day);
					break;
				case ShotTime: 				// 	 hh:mi 
					sprintf(p,"%d:%02d",_tm.hour,_tm.minute);
					break;
				case ShotDateTime: 				// 	yyyymmddhhmiss
					sprintf(p,"%04d%02d%02d%02d%02d%02d",_tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second);
					break;
				default:			// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",_tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second);
					break;
				}
				return string(p);
			}
			///	<summary>
			///	获取此对象表示时间的.otl_datetime 对象等效值
			///	<code>原型：inline otl_datetime GetOtlTime();</code>
			///	</summary>
			///	<returns>等效的otl_datetime对象。</returns> 
			inline otl_datetime GetOtlTime(){return ToOtlTime();};
			otl_datetime ToOtlTime()
			{
				otl_datetime otlTime;
				GetDateParts(&otlTime.year,&otlTime.month,&otlTime.day,NULL,&otlTime.hour,&otlTime.minute,&otlTime.second);
				return otlTime;
			}
			///	<summary>
			///	使用流操作符对此对象赋值
			///	<code>原型：DateTime&amp; operator&lt;&lt;(otl_datetime&amp; _tm);</code>
			///	</summary>
			///	<param name="_tm">OTL时间对象。</param> 
			///	<returns>此对象本身。</returns> 
			DateTime& operator<<(otl_datetime& _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);
				return *this;
			};
			///	<summary>
			///	使用OTL时间对象实例化对象
			///	<code>原型：DateTime(otl_datetime _tm);</code>
			///	</summary>
			///	<param name="_tm">OTL时间对象。</param> 
			DateTime(otl_datetime _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);
			}
			///	<summary>
			///	使用ORACLE内部时间存储格式初始化此实例对象
			///	<code>原型：DateTime(unsigned char * dtp,DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone));</code>
			///	</summary>
			///	<param name="dtp">ORACLE内部存储格式的7字节数据。</param> 
			///	<param name="nullDefault">空值时的默认值。</param> 
			DateTime(unsigned char * dtp,DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone))
			{
				if(dtp[0]==0 || dtp[1]==0 || (dtp[2]==6 && dtp[3]==31))
				{
					this->_Ticks=nullDefault._Ticks;
				}
				else
				{
					int sj=dtp[0]-100;
					int year=dtp[1]+(sj-1)*100;
					int month=dtp[2];
					int day=dtp[3];
					int hour=dtp[4]-1;
					int minute=dtp[5]-1;
					int second=dtp[6]-1;
					_init(year,month,day,hour,minute,second,0,0,localTimeZone);
				}
			}
			///	<summary>
			///	使用OTL时间对象对此对象赋值
			///	<code>原型：DateTime &amp;operator=(otl_datetime _tm);</code>
			///	</summary>
			///	<param name="_tm">OTL时间对象。</param>
			///	<returns>此对象本身。</returns> 
			DateTime &operator=(otl_datetime _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);return *this;
			};
			///	<summary>
			///	从ORACLE内部存储的时间字节获取OTL时间对象
			///	<code>原型：inline static otl_datetime GetOtlTime(unsigned char * dtp,
			///                                 DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone));</code>
			///	</summary>
			///	<param name="dtp">ORACLE内部存储格式的7字节数据。</param> 
			///	<param name="nullDefault">空值时的默认值。</param> 
			///	<returns>等效的otl_datetime对象。</returns> 
			inline static otl_datetime GetOtlTime(unsigned char * dtp,DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone))
			{
				if(dtp[0]==0 || dtp[1]==0 || (dtp[2]==6 && dtp[3]==31))
				{
					return nullDefault.GetOtlTime();
				}
				else
				{
					otl_datetime tmp;
					tmp.year=dtp[1]+(dtp[0]-101)*100;
					tmp.month=dtp[2];
					tmp.day=dtp[3];
					tmp.hour=dtp[4]-1;
					tmp.minute=dtp[5]-1;
					tmp.second=dtp[6]-1;
					return tmp;
				}
			}
#ifdef OTL_SQL_TIMESTAMP_STRUCT
			///	<summary>
			///	从OLE时间对象初始化此实例对象
			///	<code>原型：DateTime(OTL_SQL_TIMESTAMP_STRUCT * tmp);</code>
			///	</summary>
			///	<param name="tmp">OLE时间对象。</param> 
			DateTime(OTL_SQL_TIMESTAMP_STRUCT * tmp)
			{
				_init(tmp->year,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->second,0,0,localTimeZone);
			}
			///	<summary>
			///	从OLE时间对象初始化此实例对象
			///	<code>原型：inline static otl_datetime GetOtlTime(OTL_SQL_TIMESTAMP_STRUCT * tmp,
			///                                DateTime nullDefault=otl_datetime(1900,1,1,0,0,0));</code>
			///	</summary>
			///	<param name="tmp">OLE时间对象。</param> 
			///	<param name="nullDefault">空值时的默认值。</param> 
			///	<returns>等效的otl_datetime对象。</returns> 
			inline static otl_datetime GetOtlTime(OTL_SQL_TIMESTAMP_STRUCT * tmp,DateTime nullDefault=otl_datetime(1900,1,1,0,0,0))
			{
				if(tmp->year==0)
				{
					return nullDefault.GetOtlTime();
				}
				else
				{
					otl_datetime s;
					s.year=tmp->year;
					s.month=tmp->month;
					s.day=tmp->day;
					s.hour=tmp->hour;
					s.minute=tmp->minute;
					s.second=tmp->second;
					 //s.fraction=otl_from_fraction(tmp->fraction,s.frac_precision);
					return s;
				}
			}

#endif
#endif

	};
	///	<summary>
	///	重载时间对象的标准输出操作符
	///	<code>原型：inline ostream&amp; operator&lt;&lt;(ostream&amp; target, DateTime dt);</code>
	///	</summary>
	///	<param name="target">标准输出流。</param> 
	///	<param name="dt">时间对象。</param> 
	///	<returns>输出流本身。</returns> 
	EXPORT 	inline ostream& operator<<(ostream& target, DateTime dt)
	{
		target << dt.ToString();
		return target;
	}


#if defined(__OTL_H__)
	///	<summary>
	///	重载字符串与OTL时间对象的输入操作符
	///	<code>原型：inline otl_datetime&amp; operator>>(otl_datetime &amp;target,string &amp;s);</code>
	///	</summary>
	///	<param name="target">OTL时间对象。</param> 
	///	<param name="s">接收输入的字符串对象。</param> 
	///	<returns>OTL对象本身。</returns> 
	EXPORT inline otl_datetime& operator>>(otl_datetime &target,string &s)
	{
		if(target.year<=0 || target.year>=10000){s=""; return target;}
		char p[20];
		sprintf(p,"%04d-%02d-%02d %0d:%02d:%02d",target.year,target.month,target.day,target.hour,target.minute,target.second);
		s=p;
		return target;
	}

	///	<summary>
	///	重载OTL时间对象的标准输出操作符
	///	<code>原型：inline ostream&amp; operator&lt;&lt;(ostream&amp; target, otl_datetime dt);</code>
	///	</summary>
	///	<param name="target">标准输出流。</param> 
	///	<param name="dt">OTL时间对象。</param> 
	///	<returns>输出流本身。</returns> 
	EXPORT inline ostream& operator<<(ostream& target, otl_datetime dt)
	{
		string s;
		dt>>s;
		target << s;
		return target;
	}


#endif
}

#endif
