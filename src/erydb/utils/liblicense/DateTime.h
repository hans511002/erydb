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
	///	��ʾʱ���ϵ�һ�̣�ͨ�������ں͵����ʱ���ʾ����С������΢�롣
	///	</summary>
	///	<remarks>
	///	��ȷ�ı�ʾһ��ʱ��������ȷ��΢�롣
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
			///	ʱ��Ŀ̶�������ȷ��΢�룬����ʱ����롣ǰ��λ�洢ʱ����Ϣ����59λ�洢ʱ��ֵ.
			///	</summary>
			unsigned long long _Ticks;        // ǰ5λ��ʾʱ��
		public:
			///	<summary>
			///	��tm����ת����ָ����ʽ���ַ�������
			///	<code>ԭ�ͣ�inline static string ToString(tm &amp;_tm,DateTimeStyles style=StaDateTime);</code>
			///	</summary>
			///	<param name="_tm">tm����C��׼��ʱ��ṹ��</param>
			///	<param name="style">Ҫת���ɵĸ�ʽ<see cref="DateTimeStyles"/>,Ĭ��Ϊ��׼��ʽ StaDateTime[yyyy-mm-dd hh:mi:ss] </param>
			///	<returns>����tm��Ӧ���ַ���������ʽ</returns>
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
				case StaUTC:				// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
					sprintf(p,"%s %s %d %02d:%02d:%02d %d",weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
					break;
				case StaDateTime:// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %0d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				case LongDate:				// yyyy��mm��dd��
					sprintf(p,"%04d��%d��%d��",year,month,day);
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



#if defined(_MSC_VER)        // windows �µļ���������
			///	<summary>
			///	ֱ�ӻ�ȡCPU����[����] ���ε��÷���ֵ�����CPUƵ�ʼ�Ϊ��   ���뼶
			///	<code>ԭ�ͣ�inline static unsigned __int64 GetCycleCount();</code>
			///	</summary>
			///	<returns>64λ�޷���������CPU���μ���ֵ</returns>
			EXPORT	inline static unsigned __int64 GetCycleCount()
			{ 
			__asm _emit 0x0F 
			__asm _emit 0x31 
			};
			///	<summary>
			///	ֱ�ӻ�ȡCPU����[����] ���ε��÷���ֵ�����CPUƵ�ʼ�Ϊ��   ���뼶
			///	<code>ԭ�ͣ�inline static unsigned __int64 GetCycleCount2();</code>
			///	</summary>
			///	<returns>64λ�޷���������CPU���μ���ֵ</returns>
			inline static unsigned __int64 GetCycleCount2() 
			{ 
			__asm RDTSC 
			};
#ifdef _TIMERAPI_H_
			///	<summary>
			///	���뼶 ��Ҫ���ض�ý�庯����
			///	<code>ԭ�ͣ�inline static unsigned long GetMMTime();</code>
			///	</summary>
			///	<returns>��ý��ʱ�������ʱ��</returns>
			EXPORT	inline static unsigned long GetMMTime()
			{
				return timeGetTime();
			};

			///	<summary>
			///	��ȡϵͳ�ļ�������Ƶ�� ΢�뼶
			///	<code>ԭ�ͣ�inline static unsigned long long GetPerformanceUnit();</code>
			///	</summary>
			///	<returns>����ϵͳ������Ƶ��</returns>
			EXPORT inline static unsigned long long GetPerformanceUnit()
			{
				LARGE_INTEGER tc;
				QueryPerformanceFrequency(&tc); 
				return tc.QuadPart;
			};
			///	<summary>
			///	��ȡϵͳ�������� ���η���ֵ����Լ�������Ƶ�ʼ�Ϊ��  ΢�뼶
			///	<code>ԭ�ͣ�inline static unsigned long long GetPerformanceCounter();</code>
			///	</summary>
			///	<returns>����ϵͳ��������ֵ</returns>
			EXPORT	inline static unsigned long long GetPerformanceCounter()
			{
				LARGE_INTEGER tc;
				QueryPerformanceCounter(&tc);
				return tc.QuadPart;
			};
#endif
			///	<summary>
			///	ϵͳ��������
			///	</summary>
			static unsigned long long sysPerformanceUnit;
			///	<summary>
			///	CPU��Ƶ
			///	</summary>
			static unsigned long long sysCpuUnit;
#endif
			///	<summary>
			///	��ʱ�����ת����oracle�洢��ʽ
			///	<code>ԭ�ͣ�inline static unsigned char * ToOracleDate(DateTime &amp;dt,unsigned char * tempStr);</code>
			///	</summary>
			///	<param name="dt">Ҫת����ʱ�����</param>
			///	<param name="tempStr">Ŀ��洢�ռ�ָ�룬���ڴ洢ת�����ֵ</param>
			///	<returns>����tempStrָ��</returns>
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
			///	��oracle�洢��ʽת��ʱ�����
			///	<code>ԭ�ͣ�inline static DateTime GetDateFromOracle(unsigned char * dtp,DateTime * nullDefault=NULL);</code>
			///	</summary>
			///	<param name="dtp">7�ֽڵ�oracle�洢��ʽ����</param>
			///	<param name="nullDefault">ָ��Ϊ�ջ��쳣ʱ��Ĭ��ʱ��ֵ</param>
			///	<returns>ת�����õ�ʱ�������oracle����ʾ��ʱ���쳣���򷵻���Сʱ��ֵ</returns>
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
			///	���ڵ����� ������,Ӣ����,Ӣ�ļ�д
			///	</summary>
			static const string WeekName[7][3];
			///	<summary>
			///	�����·ݵ�����  ������,Ӣ����,Ӣ�ļ�д
			///	</summary>
			static const string MonthNames[13][3];
			
			///	<summary>
			///	13���� ��ʶÿ��������
			///	</summary>
			static  const int  DaysToMonth365[];
			///	<summary>
			///	13���� ��ʶÿ��������
			///	</summary>
			static  const int  DaysToMonth366[];
			///	<summary>
			///	UTC ��׼ʱ���ж��ٺ���  62135596800000
			///	</summary>
			static const long long MillesPerUTCSta;
			///	<summary>
			///	100���ж��ٺ���
			///	</summary>
			static const long long MillesPer2100Year;
			///	<summary> 
			///	��������  315537897599999
			///	</summary>
			static const long long MaxMillesSecond;
			///	<summary> 
			///	��Сʱ��  0
			///	</summary>
			static const long long MinMillesSecond;
			
			///	<summary> 
			///	100�������	36524
			///	</summary>
			static const int  DaysPer100Years; 
			///	<summary> 
			///	400�������	146097
			///	</summary>
			static const int  DaysPer400Years ;
			///	<summary> 
			///	4�������	1461
			///	</summary>
			static const int  DaysPer4Years ;
			///	<summary> 
			///	1�������	365
			///	</summary>
			static const int  DaysPerYear ;
			///	<summary> 
			///	һ����ٺ���	86400000
			///	</summary>
			static const int  MillisPerDay ;
			///	<summary> 
			///	1Сʱ���ٺ���	3600000
			///	</summary>
			static const int  MillisPerHour ;
			///	<summary> 
			///	1���Ӷ��ٺ���	60000
			///	</summary>
			static const int  MillisPerMinute ;
			///	<summary> 
			///	1����ٺ���	1000
			///	</summary>
			static const int  MillisPerSecond ;

			///	<summary> 
			///	���ʱ��̶��� 0x461040BCB9F1FFFLL
			///	</summary>
			static const long long MaxTicks ;//= 0x461040BCB9F1FFFLL;
			///	<summary> 
			///	��Сʱ��̶��� 0
			///	</summary>
			static const long long MinTicks;// = 0L;

			///	<summary> 
			///	ʱ��α�룬���������ֱ�ӻ�ȡʱ������ 0xF800000000000000LL
			///	</summary>
			static const long long TicksCeiling ;
			///	<summary> 
			///	ʱ��̶�α�룬���������ֱ�ӻ�ȡʱ�䲿�� 0x7FFFFFFFFFFFFFFLL
			///	</summary>
			static const long long TicksMask;
			///	<summary> 
			///	һ���ж��ٿ̶�����΢�룩 0x141DD76000LL
			///	</summary>
			static const long long TicksPerDay;
			///	<summary> 
			///	һСʱ�ж��ٿ̶�����΢�룩 0xD693A400LL
			///	</summary>
			static const long long TicksPerHour;
			///	<summary> 
			///	һ�����ж��ٿ̶�����΢�룩 0x3e8LL
			///	</summary>
			static const long long TicksPerMillisecond;
			///	<summary> 
			///	һ�����ж��ٿ̶�����΢�룩 0x3938700LL
			///	</summary>
			static const long long TicksPerMinute;
			///	<summary> 
			///	һ���ж��ٿ̶�����΢�룩 0xF4240LL
			///	</summary>
			static const long long TicksPerSecond;
			///	<summary> 
			///	UTC��׼ʱ��̶�����΢�룩 0xDCBFFEFF2BC000LL
			///	</summary>
			static const long long TicksPerUTCSta;
			///	<summary> 
			///	��׼ʱ������ 0xE7791F700ll
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
			///	��ǰ����ʱ��
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
				this->_Ticks=DateTime::TicksPerUTCSta+ tv.tv_sec* DateTime::TicksPerSecond+tv.tv_usec;	//΢��
				//printf("tv_sec; %d\n",tv.tv_sec) ;
				//printf("tv_usec; %d\n",tv.tv_usec);
				//printf("tz_minuteswest; %d\n",tz.tz_minuteswest);   // ʱ����Ϣ   UTC�뵱ǰʱ��ʱ���ֵ��  ������
				//printf("tz_dsttime,%d\n",tz.tz_dsttime);
#else
				
#ifdef _FILETIME_
				FILETIME ft;
				GetSystemTimeAsFileTime( &ft ); //����100���� ��  ���ܱ�time����
				_Ticks = ft.dwHighDateTime; _Ticks =(_Ticks<<32) | (long long)ft.dwLowDateTime;
				//_Ticks = (((long long)ft.dwHighDateTime)*4294967296LL) + (long long)ft.dwLowDateTime;
				_Ticks/=10;
				_Ticks+=50491123200000000LL;//50491094400000000LL; ��1600�� 1601��tickΪ50491123200000000 				//*this=this->AddYears(1600);
#elif defined(_SYSTEMTIME_)
				SYSTEMTIME st;
				GetSystemTime(&st);	////��ȷ������ 
				//_init(st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute,st.wSecond,st.wMilliseconds,0,tz);
				unsigned long long ys=DateToTicks(st.wYear, st.wMonth, st.wDay);
				unsigned long long ds=TimeToTicks(st.wHour, st.wMinute, st.wSecond);
				unsigned long long num =  ys+ds;
				num += st.wMilliseconds*TicksPerMillisecond;
				num=(num>this->MaxTicks)?this->MaxTicks:num;
				num=(num<this->MinTicks)?this->MinTicks:num;
				this->_Ticks=num=num - tz * this->TicksPerHour;
#else
				//int l=(GetCycleCount() /2660) % 1000000;			//	��ȷ��΢��
				int l = 0;
				//l = (GetTickCount() % this->MillisPerSecond)*this->TicksPerMillisecond;		//��ȷ������

				//unsigned long long l=GetPerformanceCounter();
				//l = (((l * DateTime::TicksPerSecond ) / GetPerformanceUnit() )% DateTime::TicksPerSecond);	//	��ȷ��΢��,���ܽϵ�
				time_t t = time(NULL);
				this->_Ticks = DateTime::TicksPerUTCSta + (unsigned long long)t * DateTime::TicksPerSecond + l;
#endif
				
#endif
				//��ϼ���ʱ��
				tl=32+tz;
				tl=tl<<59;		//	��5λʱ����ʶ
				this->_Ticks=tl | _Ticks;
			}
			inline void _init(long long t,TimeZone tz=localTimeZone)
			{
				this->_Ticks=t>0?t:0;
				if(t>this->MaxTicks)this->_Ticks=this->MaxTicks;
				//��ϼ���ʱ��
				unsigned long long tl=0;
				tl=32+tz;
				tl=tl<<59;		//	��5λʱ����ʶ
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
				tl=tl<<59;		//	��5λʱ����ʶ
				this->_Ticks=tl | _Ticks;
			}

		public:
			///	<summary> 
			///	��ȡ�Ӹ������α�׼ʱ�䵽ָ��ʱ�������
			///	<code>ԭ�ͣ�inline static long getUtcSec(DateTime &amp; dt);</code>
			///	</summary>
			///	<param name="dt">ʱ�����<see cref="DateTime"/></param>
			///	<returns>���ظ������α�׼ʱ�䵽dt����ʾ��ʱ�������</returns>
			EXPORT	inline static long getUtcSec(DateTime & dt){ return (dt.GetTicks() - DateTime::TicksPerUTCSta) / DateTime::TicksPerSecond; };
			///	<summary> 
			///	��ȡ�Ӹ������α�׼ʱ�䵽��ʵ������ʾ��ʱ�������
			///	<code>ԭ�ͣ�inline long getUtcSec();</code>
			///	</summary>
			///	<returns>����Щʵ����UTCʱ�������</returns>
			EXPORT	inline long getUtcSec(){ return ((_Ticks & this->TicksMask) - DateTime::TicksPerUTCSta) / DateTime::TicksPerSecond; };
			///	<summary> 
			///	�������յ���������ת��Ϊʱ��̶�����΢�룩
			///	<code>ԭ�ͣ�inline static unsigned long long DateToTicks(int year, int month, int day);</code>
			///	</summary>
			///	<param name="year">��</param>
			///	<param name="month">��</param>
			///	<param name="day">��</param>
			///	<returns>���شӹ�Ԫһ��һ��һ����ʱ������뵽ָ�������յĿ̶���</returns>
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
			///	��ʱ�䲿��ת��Ϊʱ��̶�����΢�룩
			///	<code>ԭ�ͣ�inline static unsigned long long TimeToTicks(int hour, int minute, int second);</code>
			///	</summary>
			///	<param name="hour">Сʱ</param>
			///	<param name="minute">����</param>
			///	<param name="second">��</param>
			///	<returns>���ض�Ӧ�Ŀ̶�����΢������</returns>
			EXPORT	inline static unsigned long long TimeToTicks(int hour, int minute, int second)
			{
				if ((((hour < 0) || (hour >= 0x18)) || ((minute < 0) || (minute >= 60))) || ((second < 0) || (second >= 60)))
				{
					EXP("ArgumentOutOfRange_BadHourMinuteSecond");
				}
				return TimeSpan::TimeToTicks(hour, minute, second);
			}

			///	<summary>
			///	���ʱ��ֵ 9999-12-31 23:59:59 	315537897599999 ���� 
			///	</summary>
			static  const DateTime  MaxValue;
			///	<summary>
			///	��Сʱ��ֵ 0001-1-1 0:00:00  	0 ���� 
			///	</summary>
			static  const DateTime  MinValue;
			///	<summary>
			///	ָ����UTCʱ���������ʱ����Ϣ��ʼ��ʱ����� 
			///	<code>ԭ�ͣ�DateTime(unsigned int  sec,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="sec">��UTCʱ�������</param>
			///	<param name="tz">sec��Ҫ��ʾ��ʱ��ʱ��<see cref="TimeZone"/></param>
			EXPORT	DateTime(unsigned int  sec, TimeZone tz = localTimeZone)
			{
				long long t=DateTime::TicksPerUTCSta+ (long long)sec * DateTime::TicksPerSecond;
				this->_Ticks=t>0?t:0;
				if(t>this->MaxTicks)this->_Ticks=this->MaxTicks;
				unsigned long long tl=0;
				tl=32+tz;
				tl=tl<<59;		//	��5λʱ����ʶ
				this->_Ticks=tl | _Ticks;
			};
			///	<summary>
			///	ָ��C��ʱ��ṹ�����ʼ��ʱ����� 
			///	<code>ԭ�ͣ�DateTime(tm &amp;_tm);</code>
			///	</summary>
			///	<param name="_tm">Cʱ��ṹ����</param> 
			EXPORT	DateTime(tm &_tm)
			{
				this->_init( _tm.tm_year+1900,_tm.tm_mon+1,_tm.tm_mday,_tm.tm_hour,_tm.tm_min,_tm.tm_sec,0,0,localTimeZone);
			}
			///	<summary>
			///	ָ��ʱ�����Ե�ǰʱ���ʼ������ 
			///	<code>ԭ�ͣ�DateTime(TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="tz">ʱ����Ϣ</param> 
			EXPORT	DateTime(TimeZone tz = localTimeZone)
			{
				this->_init(tz);
			}
			///	<summary>
			///	��΢��Ϊ��λ��ʾ�����ں�ʱ�䡣��׼ʱ�䣺1��1��1��0ʱ0��0�� 
			///	<code>ԭ�ͣ�DateTime(long long t, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="t">��΢��Ϊ��λ��ʾ�����ں�ʱ��̶���</param> 
			///	<param name="tz">ʱ����Ϣ</param> 
			EXPORT	DateTime(long long t, TimeZone tz = localTimeZone)
			{
				this->_init((long long)(t & this->TicksMask),tz);
			};
			///	<summary>
			///	��΢��Ϊ��λ��ʾ�����ں�ʱ�䡣��׼ʱ�䣺1��1��1��0ʱ0��0�� 
			///	<code>ԭ�ͣ�DateTime(unsigned long long t, TimeZone tz);</code>
			///	</summary>
			///	<param name="t">��΢��Ϊ��λ��ʾ�����ں�ʱ��̶���</param> 
			///	<param name="tz">ʱ����Ϣ</param> 
			EXPORT	DateTime(unsigned long long t, TimeZone tz)
			{
				this->_init((long long)(t & this->TicksMask),tz);
			};
			///	<summary>
			///	��΢��Ϊ��λ��ʾ�����ں�ʱ�䡣��׼ʱ�䣺1��1��1��0ʱ0��0�� 
			///	<code>ԭ�ͣ�DateTime(unsigned long long t);</code>
			///	</summary>
			///	<param name="t">��΢��Ϊ��λ��ʾ�����ں�ʱ��̶���</param> 
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
			///	�� <see cref='DateTime'/>�ṹ����ʵ����ʼ��Ϊָ���ꡢ�¡��ա�Сʱ�����ӡ��롢���롢΢���ָ��ʱ����ʱ�䡣
			///	<code>ԭ�ͣ�DateTime(int year, int month, int day, int hour=0, int minute=0, int second=0,
			///                       int millisecond=0,int ticks=0, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="year">��</param> 
			///	<param name="month">��</param> 
			///	<param name="day">��</param> 
			///	<param name="hour">Сʱ</param> 
			///	<param name="minute">��</param> 
			///	<param name="second">��</param> 
			///	<param name="millisecond">����</param> 
			///	<param name="ticks">΢��</param> 
			///	<param name="tz">ָ��ʱ��Ķ�Ӧʱ��</param>
			EXPORT	DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0, int millisecond = 0, int ticks = 0, TimeZone tz = localTimeZone)
			{
				this->_init( year,month,day,hour,minute,second,millisecond,ticks,tz);
			}
			///	<summary>
			///	��8λ������ʾ�������ճ�ʼ��. ��:20071128��
			///	<code>ԭ�ͣ�DateTime(int date,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="date">8λ���ڲ���</param> 
			///	<param name="tz">��Ӧʱ��</param> 
			EXPORT	DateTime(int date, TimeZone tz = localTimeZone)   //20071128 
			{
				int year,month,day;
				year  = date/10000;
				month = (date/100) % 100;
				day  = date % 100;
				this->_init(year,month,day,0,0,0,0,0,tz);
			}
			
			//*******************************����������*****************************************                                    
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
			///	��ȡ��ʵ������ʾ���ڵ���ݲ��֡�
			///	<code>ԭ�ͣ�inline int GetYear();</code>
			///	</summary>
			///	<returns>�����겿��</returns> 
			EXPORT	inline int GetYear()
			{
				return this->GetDatePart(0);		 
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ���ڵ��·ݲ��֡�����ɲ��֣���ʾΪ 1 �� 12 ֮���һ��ֵ��
			///	<code>ԭ�ͣ�inline int GetMonth();</code>
			///	</summary>
			///	<returns>�����²���</returns> 
			EXPORT	inline int GetMonth()
			{
				return this->GetDatePart(2);		 
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ������Ϊ�����еĵڼ��졣����ɲ��֣���ʾΪ 1 �� 31 ֮���һ��ֵ��
			///	<code>ԭ�ͣ�inline int GetDay();</code>
			///	</summary>
			///	<returns>�����ղ���</returns> 
			EXPORT	inline int GetDay()
			{
				return this->GetDatePart(3);
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ���ڵ�Сʱ���֡�Сʱ��ɲ��֣���ʾΪ 0 �� 23 ֮���һ��ֵ��
			///	<code>ԭ�ͣ�inline int GetHour();</code>
			///	</summary>
			///	<returns>����Сʱ����</returns> 
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
			///	��ȡ��ʵ������ʾ���ڵķ��Ӳ��֡�������ɲ��֣���ʾΪ 0 �� 59 ֮���һ��ֵ��
			///	<code>ԭ�ͣ�inline int GetMinute();</code>
			///	</summary>
			///	<returns>���ط��Ӳ���</returns> 
			EXPORT	inline int GetMinute()
			{
				long long hs=(long long)((_Ticks & this->TicksMask)%this->TicksPerHour);
				return (int) (hs / this->TicksPerMinute);
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ���ڵ��벿�֡����������� 0 �� 59 ֮�䣩��
			///	<code>ԭ�ͣ�inline int GetSecond();</code>
			///	</summary>
			///	<returns>��ʵ������ʾ���ڵ��벿��</returns> 
			EXPORT	inline int GetSecond()
			{
				long long ds=(this->_Ticks & this->TicksMask) % this->TicksPerMinute;	
				return (int) (ds/this->TicksPerSecond);
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ���ڵĺ��벿�֡������������� 0 �� 999 ֮�䣩��
			///	<code>ԭ�ͣ�inline int GetMillessecond();</code>
			///	</summary>
			///	<returns>��ʵ������ʾ���ڵĺ��벿��</returns> 
			EXPORT	inline int GetMillessecond()
			{
				return (int)((this->_Ticks & this->TicksMask) % this->TicksPerSecond)/this->TicksPerMillisecond;
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ���ڵ�΢�벿�֡�΢���������� 0 �� 999 ֮�䣩��
			///	<code>ԭ�ͣ�inline int GetMicrosecond();</code>
			///	</summary>
			///	<returns>��ʵ������ʾ���ڵ�΢�벿��</returns> 
			EXPORT	inline int GetMicrosecond(){ return (this->_Ticks & this->TicksMask) % this->TicksPerMillisecond; };
			///	<summary>
			///	��ȡ��ʾ��ʵ�������ں�ʱ��Ŀ̶���΢������
			///	<code>ԭ�ͣ�inline unsigned long long GetTicks();</code>
			///	</summary>
			///	<returns>��ʵ������ʾ���ڵ�΢�벿��</returns> 
			EXPORT	inline unsigned long long GetTicks()
			{
				return (this->_Ticks & this->TicksMask);
			}
			///	<summary>
			///	��ȡ��ʵ������ʾ�������Ǹ����еĵڼ��졣�����еĵڼ��죬��ʾΪ 1 �� 366 ֮���һ��ֵ��
			///	<code>ԭ�ͣ�inline int GetDayOfYear();</code>
			///	</summary>
			///	<returns>��ʵ������ʾ�������Ǹ����еĵڼ���</returns> 
			EXPORT	inline int GetDayOfYear()
			{
				return this->GetDatePart(1);		 
			}
			///	<summary>
			///	��ȡ��ʵ����ת��ʱ������ʾ�����������ڼ���һ��<see cref="Common.DayOfWeek"/>ö�ٳ�������ָʾ���ڼ���������ֵ�ķ�Χ���㣨��ʾ�����գ���������ʾ����������
			///	<code>ԭ�ͣ�inline DayOfWeek GetDayOfWeek(TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="tz">ָ��ʱ��</param> 
			///	<returns>���ڼ�</returns> 
			EXPORT	inline DayOfWeek GetDayOfWeek(TimeZone tz = localTimeZone)
			{
				return (DayOfWeek) ((int) ((((long)(((_Ticks & this->TicksMask)+tz*DateTime::TicksPerHour) / this->TicksPerDay)) + 1) % ((long) 7)));
			};
			///	<summary>
			///	���ص�ǰʱ������ʾ���������ơ�type=0 �������� 1 Ӣ��ȫ�� 2 Ӣ�ļ�д��
			///	<code>ԭ�ͣ�inline const string &amp;GetWeekName(int type,TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="type">ָ�����ر�ʾ��ʽ</param> 
			///	<param name="tz">ָ��ʱ��</param> 
			///	<returns>��ǰʱ������ʾ����������</returns> 
			EXPORT	inline const string &GetWeekName(int type, TimeZone tz = localTimeZone)
			{
				type=type%3;
				DayOfWeek index= this->GetDayOfWeek(tz);
				return DateTime::WeekName[index][type];
			}
			///	<summary>
			///	��ȡ��ʵ�������ڲ��֡��µ� <see cref="DateTime"/>�����������ʵ����ͬ��ʱ��ֵ����Ϊ��ҹ 12:00:00 (00:00:00)��
			///	<code>ԭ�ͣ�inline DateTime GetDate();</code>
			///	</summary>
			///	<returns>��ʵ�������ڲ�������ʾ�������ڶ���</returns> 
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
			///	��ȡ��ʵ����ָ�����֡�
			///	<code>ԭ�ͣ�inline int GetDatePart(DatePart dp);</code>
			///	</summary>
			///	<param name="dp">ָ��Ҫ���ص�����ʱ�䲿��<see cref='DatePart'/></param> 
			///	<returns>��ȡ��ʵ����ָ������</returns> 
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
			///	���ô�ʵ����ʾʱ���ʱ����
			///	<code>ԭ�ͣ�inline void SetTimeZone(TimeZone tz);</code>
			///	</summary>
			///	<param name="tc">ָ��ʱ��<see cref='TimeZone'/></param> 
			EXPORT	inline void SetTimeZone(TimeZone tz)
			{
				unsigned long long tl =32+tz;
				tl=tl<<59;		//	��5λʱ����ʶ
				this->_Ticks=(tl | (_Ticks & this->TicksMask ));
			}
			///	<summary>
			///	��ȡ��ʵ����ʾʱ���ʱ����
			///	<code>ԭ�ͣ�inline TimeZone GetTimeZone();</code>
			///	</summary>
			///	<returns>��ȡ��ʵ����ʾʱ���ʱ��</returns> 
			EXPORT	inline TimeZone GetTimeZone()
			{
				int tz=(_Ticks>>59);if(tz>16)tz-=32;
				return (TimeZone)tz;
			};
			///	<summary>
			///	��ȡһ��<see cref='DateTime'/>���󣬸ö�������Ϊ�˼�����ϵĵ�ǰ���ں�ʱ�䣬��ʾΪ����ʱ�䡣
			///	<code>ԭ�ͣ�inline static DateTime Now();</code>
			///	</summary>
			///	<returns>���ص�ǰ������ϵĵ�ǰ���ں�ʱ�䣬��ʾΪ����ʱ��</returns> 
			EXPORT	inline static DateTime Now()
			{
				return DateTime();
			}
			///	<summary>
			///	��ȡ��ʵ����ʱ�䲿�֡�
			///	<code>ԭ�ͣ�inline TimeSpan GetTimeOfDay();</code>
			///	</summary>
			///	<returns>��ȡ��ʵ���ĵ����ʱ�䣬����ʾ��������ҹ�����Ѿ���ʱ��Ĳ���</returns> 
			EXPORT	inline TimeSpan GetTimeOfDay()
			{
				long long d=((_Ticks & this->TicksMask) % this->TicksPerDay);
				return TimeSpan(d);
			}
			///	<summary>
			///	��ȡ��ǰʱ������ڲ��֡�
			///	<code>ԭ�ͣ�inline static DateTime GetToday();</code>
			///	</summary>
			///	<returns>��ȡ��ǰʱ������ڲ��֣���ʱ����ɲ�������Ϊ 00:00:00</returns> 
			EXPORT	inline static DateTime GetToday()
			{
				return DateTime::Now().GetDate();
			}
			///	<summary>
			///	��ȡһ��<see cref='DateTime'/>����,�ö�������Ϊ�˼�����ϵĵ�ǰ���ں�ʱ�䣬����ʾΪЭ��ͨ��ʱ�� (UTC)��
			///	<code>ԭ�ͣ�inline static DateTime GetUtcNow();</code>
			///	</summary>
			///	<returns>�˼�����ϵĵ�ǰ���ں�ʱ�䣬��ʱ����ɲ�������Ϊ 00:00:00</returns> 
			EXPORT	inline static DateTime GetUtcNow()
			{
				return DateTime(GMT0);
			}

			///	<summary>
			///	��ȡ��ʱ��ʵ���е�ָ�����֣��������ء�
			///	<code>ԭ�ͣ�inline void GetDateParts(int * year,int * month,int * day,int * dayOfyear,int * hour=NULL,
			///                                   int* minute=NULL,int *second=NULL,int *millis=NULL,int * ticks=NULL);</code>
			///	</summary>
			///	<param name="year">������</param> 
			///	<param name="month">������</param> 
			///	<param name="day">������</param> 
			///	<param name="hour">����Сʱ</param> 
			///	<param name="minute">���ط�</param> 
			///	<param name="second">������</param> 
			///	<param name="millisecond">���غ���</param> 
			///	<param name="ticks">����΢��</param> 
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
			///	��ȡ��ʱ��ʵ���е�ָ��ĳһ���֡�
			///	<code>ԭ�ͣ�inline int GetDatePart(int part);</code>
			///	</summary>
			///	<returns>���ض�Ӧʱ��ֵ����</returns> 
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
			///	������<see cref='DateTime'/>������ֵΪ�ڵ�ǰʱ��ʵ���ϼ�һָ��ʱ�䲿�ֵ�ָ��ֵ��
			///	<code>ԭ�ͣ�inline DateTime Add(long long value, long long scale);</code>
			///	</summary>
			///	<param name="value">ָ��ֵ</param> 
			///	<param name="scale">ָ����λ</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵΪ�ڵ�ǰʱ��ʵ���ϼ�һָ��ʱ�䲿�ֵ�ָ��ֵ��</returns> 
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
			///	��ָ����<see cref='TimeSpan'/>��ֵ�ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime Add(TimeSpan value);</code>
			///	</summary>
			///	<param name="value">ָ��ʱ����</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ��ʱ����֮�͡�</returns> 
			EXPORT inline DateTime Add(TimeSpan value)
			{
				return this->Add(value._ticks,1);
			};
			///	<summary>
			///	��ָ����΢�����ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddTicks(long long ticks);</code>
			///	</summary>
			///	<param name="value">ʱ��̶�����΢����</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ��΢��ʱ��֮�͡�</returns> 
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
			///	��ָ���ĺ������ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddMillesSecond(long long value);</code>
			///	</summary>
			///	<param name="value">������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ�ĺ���ʱ��֮�͡�</returns> 
			EXPORT inline DateTime AddMillesSecond(long long value)
			{
				return this->Add(value,this->TicksPerMillisecond);
			}
			///	<summary>
			///	��ָ���������ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddDays(int value);</code>
			///	</summary>
			///	<param name="value">�����������Ǹ���Ҳ����������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ������֮�͡�</returns> 
			EXPORT inline DateTime AddDays(int value)
			{
				return this->Add(value, this->TicksPerDay);
			}
			///	<summary>
			///	��ָ����Сʱ���ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddHours(int value);</code>
			///	</summary>
			///	<param name="value">Сʱ���������Ǹ���Ҳ����������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ��Сʱ��֮�͡�</returns> 
			EXPORT inline DateTime AddHours(int value)
			{
				return this->Add(value, this->TicksPerHour);
			}
			///	<summary>
			///	��ָ���ķ������ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddMinutes(int value);</code>
			///	</summary>
			///	<param name="value">�������������Ǹ���Ҳ����������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ�ķ�����֮�͡�</returns> 
			EXPORT inline DateTime AddMinutes(int value)
			{
				return this->Add(value, this->TicksPerMinute);
			}
			///	<summary>
			///	��ָ�����·����ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddMonths(int months);</code>
			///	</summary>
			///	<param name="months">�·����������Ǹ���Ҳ������������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����months ����ʾ���·���֮�͡�</returns> 
			EXPORT inline DateTime AddMonths(int months)
			{
				if ((months < -120000) || (months > 120000)) //һ����
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
					month=12 - abs(num4 - 11) % 12;			//month = 12 + ((num4 + 1) % 12);   //����ȡģ��MS���е��㷨
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
			///	��ָ���������ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddMonths(int value);</code>
			///	</summary>
			///	<param name="value">�����������Ǹ���Ҳ������������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ������֮�͡�</returns> 
			EXPORT inline DateTime AddSeconds(int value)
			{
				return this->Add(value, this->TicksPerSecond);
			}
			///	<summary>
			///	��ָ����������ӵ���ʵ����ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddYears(int value);</code>
			///	</summary>
			///	<param name="value">������������Ǹ���Ҳ������������</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ�������֮�͡�</returns> 
			EXPORT inline DateTime AddYears(int value)
			{
				if ((value < -10000) || (value > 10000))
				{
					EXP("years: ArgumentOutOfRange_DateTimeBadYears");
				}
				return this->AddMonths(value * 12);
			}
			///	<summary>
			///	��ָ������ֵ��Ӽӵ���ʵ����ָ������ֵ�ϡ�
			///	<code>ԭ�ͣ�inline DateTime AddDataPart(int number,DatePart dp);</code>
			///	</summary>
			///	<param name="number">�����Ǹ���Ҳ������������</param> 
			///	<param name="dp">ָ��Ҫ��ӵ���ʵ�����ĸ������ϡ�</param> 
			///	<returns>һ���µ�<see cref='DateTime'/>������ֵ�Ǵ�ʵ������ʾ�����ں�ʱ����value ����ʾ����֮�͡�</returns> 
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
			///	�Ƚ�<see cref='DateTime'/>����ʵ�����������������ֵ��ָʾ��
			///	<code>ԭ�ͣ�inline static int Compare(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="t1">��һ��<see cref='DateTime'/>��</param> 
			///	<param name="t2">�ڶ���<see cref='DateTime'/>��</param> 
			///	<returns>�з������֣�ָʾ t1 �� t2 �����ֵ��ֵ���� ���� С���� t1 С�� t2�� �� t1 ���� t2�� ������ t1 ���� t2��</returns> 
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
			///	����ʵ����ָ��<see cref='DateTime'/>������бȽϲ����ض������ֵ��ָʾ.
			///	<code>ԭ�ͣ�inline int CompareTo(DateTime value);</code>
			///	</summary>
			///	<param name="value">Ҫ�Ƚϵ�<see cref='DateTime'/>����</param>
			///	<returns>�з������֣�ָʾ��ʵ���� value ���������ֵ��ֵ˵��: С���� ��ʵ��С�� value�� �� ��ʵ������ value�� ������ ��ʵ������value����</returns> 
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
			///	����ָ��������е�����
			///	<code>ԭ�ͣ�inline static int DaysInMonth(int year, int month);</code>
			///	</summary>
			///	<param name="year">���</param>
			///	<param name="month">�·ݣ����� 1 �� 12 ֮���һ�����֣���</param>
			///	<returns> ָ�� year �� month �����������磬��� month ���� 2����ʾ���£����򷵻�ֵΪ 28 �� 29������ȡ���� year �Ƿ�Ϊ���ꡣ</returns> 
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
			///	����һ��ֵ����ֵָʾ��ʵ���Ƿ���ָ����<see cref='DateTime'/>ʵ�����
			///	<code>ԭ�ͣ�inline bool Equals(DateTime value);</code>
			///	</summary>
			///	<param name="value">Ҫ���ʵ�����бȽϵ�<see cref='DateTime'/>ʵ��</param>
			///	<param name="month">�·ݣ����� 1 �� 12 ֮���һ�����֣���</param>
			///	<returns> ��� value �������ڴ�ʵ����ֵ����Ϊ true������Ϊ false��</returns> 
			EXPORT inline bool Equals(DateTime value)
			{
				return ((_Ticks & this->TicksMask)==value.GetTicks());
			}
			///	<summary>
			///	����һ��ֵ����ֵָʾ<see cref='DateTime'/>������ʵ���Ƿ����
			///	<code>ԭ�ͣ�inline static bool Equals(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="t1">Ҫ���бȽϵ�<see cref='DateTime'/>ʵ��1</param>
			///	<param name="t2">Ҫ���бȽϵ�<see cref='DateTime'/>ʵ��2��</param>
			///	<returns> �������<see cref='DateTime'/> ֵ��ȣ���Ϊ true������Ϊ false��</returns> 
			EXPORT inline static bool Equals(DateTime t1, DateTime t2)
			{
				return (t1.GetTicks()==t2.GetTicks());
			}
			///	<summary>
			///	����ָ��������Ƿ�Ϊ�����ָʾ
			///	<code>ԭ�ͣ�inline static bool Equals(DateTime t1, DateTime t2);</code>
			///	</summary>
			///	<param name="year">��λ�����</param> 
			///	<returns> ��� year Ϊ���꣬��Ϊ true������Ϊ false��</returns> 
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
			///	������ڸ�������ʱ������ʾ���������ϸ�ָ������ת��Ϊ��׼�ַ�����ʽ����
			///	<code>ԭ�ͣ�inline static string getDateAddDur(time_t NowTime,int dur=0);</code>
			///	</summary>
			///	<param name="NowTime">ʱ����</param> 
			///	<param name="dur">Ҫ��ӵ�����</param> 
			///	<returns> NowTime����dur������ʾ��ʱ���Ӧ���ַ�����ʽ��</returns> 
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
			///	���ַ�����ʾ��ʱ�����ָ���������ٷ����ַ���ʱ��
			///	<code>ԭ�ͣ�inline static string getDateAddDur(string str,int dur=0);</code>
			///	</summary>
			///	<param name="str">�ַ�����ʽ��ʾ��ʱ��</param> 
			///	<param name="dur">Ҫ��ӵ�����</param> 
			///	<returns> str����ʾʱ�����dur���Ӧ���ַ�����ʾ��ʽ��</returns> 
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
			///	��ָ��ʱ������ּ���ָ�����ת��Ϊ����ʱ���ַ�����ʾ��ʽ
			///	<code>ԭ�ͣ�inline static string getDateAddDur(int year, int month, int day,
			///                                        int hour=0, int minute=0, int second=0,int dur=0);</code>
			///	</summary>
			///	<param name="year">��</param> 
			///	<param name="month">��</param> 
			///	<param name="day">��</param> 
			///	<param name="hour">ʱ</param> 
			///	<param name="minute">��</param> 
			///	<param name="second">��</param> 
			///	<param name="dur">Ҫ��ӵ�����</param>  
			///	<returns>��Ӧ���ַ�����ʾ��ʽ��</returns> 
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
			///	��ȡUTC�������
			///	<code>ԭ�ͣ�inline static time_t DateToUTCSecond(int year, int month, int day,
			///                                         int hour=0, int minute=0, int second=0);</code>
			///	</summary>
			///	<param name="year">��</param> 
			///	<param name="month">��</param> 
			///	<param name="day">��</param> 
			///	<param name="hour">ʱ</param> 
			///	<param name="minute">��</param> 
			///	<param name="second">��</param> 
			///	<returns>���UTC������</returns> 
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
				result=(time_t)(allsec-DateTime::localTimeZone * 3600 -TicksPerUTCSta/DateTime::TicksPerSecond) ;   // ��ȥ����ʱ��ʱ��
				return result;
			}
		public:

			///	<summary>
			///	�Ӵ�ʵ���м�ȥָ�������ں�ʱ��
			///	<code>ԭ�ͣ�inline TimeSpan Subtract(DateTime value);</code>
			///	</summary>
			///	<param name="value"><see cref='DateTime'/>��һ��ʵ��</param> 
			///	<returns>���ʱ����<see cref='TimeSpan'/>,�����ڴ�ʵ������ʾ�����ں�ʱ���ȥ value ����ʾ�����ں�ʱ��</returns> 
			EXPORT inline TimeSpan Subtract(DateTime value)
			{
				return TimeSpan(this->GetTicks()-value.GetTicks());
			};
			///	<summary>
			///	�Ӵ�ʵ���м�ȥָ��ʱ����
			///	<code>ԭ�ͣ�inline DateTime &amp;Subtract(TimeSpan value);</code>
			///	</summary>
			///	<param name="value"><see cref='TimeSpan'/>��һ��ʵ��</param> 
			///	<returns>��ʵ������</returns> 
			EXPORT inline DateTime &Subtract(TimeSpan value)
			{
				this->_Ticks-=value.getTotalTicks();
				return *this;
			};
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�ĳ������ַ�����ʾ��ʽ yyyy��mm��dd��
			///	<code>ԭ�ͣ�inline string ToLongDateString();</code>
			///	</summary>
			///	<returns>һ���ַ���,���磺yyyy��mm��dd�ա�</returns> 
			EXPORT inline string ToLongDateString()
			{
				int year,month,day;
				GetDateParts(&year,&month,&day,NULL);

				char p[20];
				char f[20];
				strcpy(f,"%d��%d��%d��");
				sprintf(p,f,year,month,day);
				//_result=p;
				return p;
			}
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�ĳ�ʱ���ַ�����ʾ��ʽ hh:mi:ss
			///	<code>ԭ�ͣ�inline string ToLongTimeString();</code>
			///	</summary>
			///	<returns>һ���ַ��������磺hh:mi:ss��</returns> 
			EXPORT 	inline string ToLongTimeString()
			{
				return this->ToString(StaTime);
			} 
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�Ķ������ַ�����ʾ��ʽ yyyy-mm-dd
			///	<code>ԭ�ͣ�inline string ToShortDateString();</code>
			///	</summary>
			///	<returns>һ���ַ��������磺yyyy-mm-dd��</returns> 
			EXPORT inline string ToStaDateString()
			{
				return this->ToString(StaDate);
			}
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�Ķ������ַ�����ʾ��ʽ yyyymmdd
			///	<code>ԭ�ͣ�inline string ToShortDateString();</code>
			///	</summary>
			///	<returns>һ���ַ��������磺yyyymmdd��</returns> 
			EXPORT inline string ToShortDateString()
			{
				return this->ToString(ShotDate);
			}
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�Ķ�ʱ���ַ�����ʾ��ʽ hh:mi
			///	<code>ԭ�ͣ�inline string ToShortTimeString();</code>
			///	</summary>
			///	<returns>һ���ַ��������磺hh:mi��</returns> 
			EXPORT inline string ToShortTimeString()
			{
				return this->ToString(ShotTime);
			}
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч�Ķ�ʱ���ַ�����ʾ��ʽ yyyymmddhhmiss
			///	<code>ԭ�ͣ�inline string ToShotDateTimeString();</code>
			///	</summary>
			///	<returns>һ���ַ��������磺yyyymmddhhmiss��</returns> 
			EXPORT inline string ToShotDateTimeString(){ return this->ToString(ShotDateTime); }
			///	<summary>
			///	����ʵ����ֵת��Ϊ���Ч���ַ�����ʾ
			///	<code>ԭ�ͣ�inline string ToString(DateTimeStyles  format=StaDateTime);</code>
			///	</summary>
			///	<param name="format">ָ�������ַ�����ʽ</param> 
			///	<returns>��ʵ����ֵ���ַ�����ʾ��ʽ����ʽ��formatָ����</returns> 
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
				case StaUTC:				// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
					sprintf(p,"%s %s %d %02d:%02d:%02d %d",weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
					break;
				case StaDateTime:// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %02d:%02d:%02d",year,month,day,hour,minute,second);
					break;
				case LongDate:				// yyyy��mm��dd��
					sprintf(p,"%04d��%d��%d��",year,month,day);
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
			///	ʹ��ָ����ʱ����Ϣ����ʵ����ֵת��Ϊ���ĵ�Ч�ַ�����ʾ��ʽ
			///	<code>ԭ�ͣ�inline string ToString(TimeZone tz);</code>
			///	</summary>
			///	<param name="tz">ָ��ʱ��</param> 
			///	<returns>��ʵ����ֵ���ַ�����ʾ��ʽ��</returns> 
			EXPORT inline string ToString(TimeZone tz)
			{
				DateTime temp=DateTime(this->_Ticks ,tz);
				return  temp.ToString();
			};
			///	<summary>
			///	ʹ��ָ����ʽ����ʵ����ֵת�������Ч���ַ�����ʾ
			///	<code>ԭ�ͣ�inline string ToString(TimeZone tz);</code>
			///	</summary>
			///	<param name="format">��ʽ�ַ���</param> 
			///	<returns>format ָ���Ĵ�ʵ����ֵ���ַ�����ʾ��ʽ����</returns> 
			EXPORT inline string ToString(string format)
			{
				string temp=format;
				format=String::ToLower(String::Trim(temp));
				if(format=="yyyy-mm-dd hh:mi:ss")
				{
					return ToString(StaDateTime);
				}
				else if(format=="yyyy��mm��dd��")
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
			///	ʹ��ָ����ʽ��ʱ������ʵ����ֵת��Ϊ���ĵ�Ч�ַ�����ʾ��ʽ
			///	<code>ԭ�ͣ�inline string ToString(string format,TimeZone tz);</code>
			///	</summary>
			///	<param name="format">��ʽ�ַ���</param> 
			///	<param name="tz">ָ��ʱ��</param> 
			///	<returns>format ��tz ָ���Ĵ�ʵ����ֵ���ַ�����ʾ��ʽ����</returns> 
			EXPORT inline string ToString(string format, TimeZone tz)
			{
				DateTime temp=DateTime(this->_Ticks ,tz);
				return temp.ToString(format);
			}
			///	<summary>
			///	���ش�ʵ�������²���
			///	<code>ԭ�ͣ�inline string GetYearMonthStr();</code>
			///	</summary>
			///	<returns>6λ�ַ�����ʽ��ʾ���¡�</returns> 
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
			///	����8λ������ʾ�Ĵ�ʵ���������ղ���
			///	<code>ԭ�ͣ�inline string GetYearMonthDay();</code>
			///	</summary>
			///	<returns>8λ������ʾ�Ĵ�ʵ���������ա�</returns> 
			EXPORT inline int GetYearMonthDay()
			{
				int year,month,day;
				GetDateParts(&year,&month,&day,NULL);
				return year*10000+month*100+day;
			};
			///	<summary>
			///	����6λ������ʾ�Ĵ�ʵ�������²���
			///	<code>ԭ�ͣ�inline int GetYearMonth();</code>
			///	</summary>
			///	<returns>6λ������ʾ�Ĵ�ʵ�������¡�</returns> 
			EXPORT inline int GetYearMonth()
			{
				int year,month;
				GetDateParts(&year,&month,NULL,NULL);
				return year*100+month;
			};
			///	<summary>
			///	����14λ������ʾ�Ĵ�ʵ����������ʱ���벿��
			///	<code>ԭ�ͣ�inline long long GetFullDate();</code>
			///	</summary>
			///	<returns>14λ������ʾ�Ĵ�ʵ����������ʱ���벿�֡�</returns> 
			EXPORT inline long long GetFullDate()
			{
				int year,month,day,hour,minute,second,millis;
				GetDateParts(&year,&month,&day,NULL,&hour,&minute,&second,&millis);
				long long res=year*10000000000L;
				return res+month*100000000L+day*1000000L+hour*10000L+minute*100L+second;
			}
			///	<summary>
			///	ʹ��ָ����ʱ����Ϣ�͸�ʽ����ʽ,�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static DateTime Parse2(const char * s, DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">Ҫ�������ַ���</param> 
			///	<param name="styles">ָ��s��ʾʱ��ĸ�ʽ</param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			///	<returns><see cref='DateTime'/>,��Ч���� tz �� styles ��ָ���� s �а��������ں�ʱ�䡣</returns> 
			EXPORT inline static DateTime Parse2(const char * s, DateTimeStyles styles = StaDateTime, TimeZone tz = localTimeZone)
			{
				DateTime res;
				celerityParse::Parse(res,s,styles,tz);
				return res;
			}
			///	<summary>
			///	ʹ��ָ����ʱ����Ϣ�͸�ʽ����ʽ,�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static DateTime Parse2(string &amp; s, DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">Ҫ�������ַ���</param> 
			///	<param name="styles">ָ��s��ʾʱ��ĸ�ʽ</param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			///	<returns><see cref='DateTime'/>,��Ч���� tz �� styles ��ָ���� s �а��������ں�ʱ�䡣</returns> 
			EXPORT inline static DateTime Parse2(string & s, DateTimeStyles styles = StaDateTime, TimeZone tz = localTimeZone)
			{
				DateTime res;
				celerityParse::Parse(res,s.c_str(),styles,tz);
				return res;
			}
			///	<summary>
			///	�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static DateTime Parse(string s, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="s">Ҫ�������ַ���,��ʽ�������������ڣ� yyyy-mm-dd hh:mm:ss "yyyy-mm-dd"
			///                "yyyy-mm-dd hh:mm:ss"  Mon May 14 02:03:55 2007(���ڼ� �·� ���� ʱ:��:�� ��) </param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			///	<returns><see cref='DateTime'/>,��Ч���� tz��ָ���� s �а��������ں�ʱ�䡣</returns> 
			EXPORT inline static DateTime Parse(string s, TimeZone tz = localTimeZone)
			{
				StringParser parser2;
				long long ticks= parser2.Parse(s);
				ticks -= tz * TicksPerHour;
				return DateTime(ticks,tz);
			}
			///	<summary>
			///	�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static void Parse(DateTime &amp;result,string s, TimeZone tz=localTimeZone)</code>
			///	</summary>
			///	<param name="result"> ���˷�������ʱ�����ת���ɹ���������� s �а��������ں�ʱ���Ч�� Common.DateTime ֵ�����ת��ʧ�ܣ���Ϊ Common.DateTime.MinValue�����
			///     s ����Ϊ�գ����߲��������ں�ʱ�����Ч�ַ�����ʾ��ʽ����ת��ʧ�ܡ��ò���δ����ʼ���������ݡ�</param> 
			///	<param name="s">Ҫ�������ַ���,��ʽ�������������ڣ� yyyy-mm-dd hh:mm:ss "yyyy-mm-dd"
			///                "yyyy-mm-dd hh:mm:ss"  Mon May 14 02:03:55 2007(���ڼ� �·� ���� ʱ:��:�� ��) </param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			EXPORT inline static void Parse(DateTime &result, string s, TimeZone tz = localTimeZone)
			{
				result=DateTime::Parse(s,tz);
			}
			///	<summary>
			///	ʹ��ָ����ʱ����Ϣ�͸�ʽ����ʽ,�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static void Parse2(DateTime &amp;result,const char *s,
			///                                 DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="result"><see cref='DateTime'/>,��Ч���� tz �� styles ��ָ���� s �а��������ں�ʱ�䡣</param> 
			///	<param name="s">Ҫ�������ַ���</param> 
			///	<param name="styles">ָ��s��ʾʱ��ĸ�ʽ</param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			EXPORT inline static void Parse2(DateTime &result, const char *s, DateTimeStyles styles = StaDateTime
				, TimeZone tz=localTimeZone)
			{
				celerityParse::Parse(result,s,styles,tz);
			}
			///	<summary>
			///	ʹ��ָ����ʱ����Ϣ�͸�ʽ����ʽ,�����ں�ʱ���ָ���ַ�����ʾ��ʽת��Ϊ���Ч��<see cref='DateTime'/>
			///	<code>ԭ�ͣ�inline static void Parse2(DateTime &amp;result,string &amp; s,
			///                                 DateTimeStyles styles=StaDateTime, TimeZone tz=localTimeZone);</code>
			///	</summary>
			///	<param name="result"><see cref='DateTime'/>,��Ч���� tz �� styles ��ָ���� s �а��������ں�ʱ�䡣</param> 
			///	<param name="s">Ҫ�������ַ���</param> 
			///	<param name="styles">ָ��s��ʾʱ��ĸ�ʽ</param> 
			///	<param name="tz">ָ��s��ʾʱ���ʱ��</param> 
			EXPORT inline static void Parse2(DateTime &result, string &s, DateTimeStyles styles = StaDateTime
				, TimeZone tz=localTimeZone)
			{
				celerityParse::Parse(result,s.c_str(),styles,tz);
			}
			///	<summary>
			///	��ָ�����֣�ָ����ʽ��ָ�����ֵ����Ӳ��ֻ�ȡʱ��
			///	<code>ԭ�ͣ�inline static void Parse3(long dateVal,int style,int intType,long inteval);</code>
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
			///	��ȡǰ�����ǰ����
			///	<code>ԭ�ͣ�inline static string getPreDate(string yyyymmdd,int pNum);</code>
			///	</summary>
			///	<param name="yyyymmdd">8λ��6λ�ַ�����ʾ��ʱ��</param> 
			///	<param name="pNum">Ҫ��ȥ����ֵ������£�</param> 
			///	<returns> yyyymmdd��ʱ�����㷽����ȥpNum����ַ���ֵ ��</returns> 
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
			///	����ʵ����ֵת��Ϊ��׼<see cref='DateTimeStyles'/>��ʽ˵����֧�ֵ������ַ�����ʾ��ʽ.
			///	<code>ԭ�ͣ�inline void GetDateTimeFormats(Array&lt;string> &amp;arr);</code>
			///	</summary>
			///	<param name="arr">�ַ������飬���е�ÿ��Ԫ�ض���ʾ��ʵ����ֵ���������ñ�׼ Common.DateTime ��ʽ˵����֮һ��ʽ����</param> 
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
				strcpy(f,"%s %s %d %02d:%02d:%02d %d");// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
				len=sprintf(p,f,weekName[2].c_str(),monthName[2].c_str(),day,hour,minute,second,year);
				p[len]='\0';
				arr[0]= p;
							
				strcpy(f,"%04d-%02d-%02d %d:%02d:%02d");   // yyyy-mm-dd hh:mi:ss
				len=sprintf(p,f,year,month,day,hour,minute,second);
				p[len]='\0';
				arr[1]= p;

				strcpy(f,"%d��%d��%d��");					// yyyy��mm��dd��
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
			///	����ʵ����ֵת��Ϊ��׼<see cref='DateTimeStyles'/>��ʽ˵����֧�ֵ������ַ�����ʾ��ʽ.
			///	<code>ԭ�ͣ�inline void GetDateTimeFormats(Array&lt;string> &amp;arr);</code>
			///	</summary>
			///	<param name="arr">�ַ������飬���е�ÿ��Ԫ�ض���ʾ��ʵ����ֵ���������ñ�׼ <see cref='DateTimeStyles'/>��ʽ˵����֮һ��ʽ����</param> 
			///	<param name="tz">ָ��ʱ��</param> 
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
					case StaUTC:				// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
						{
							char weekName[4],monthName[4];
							memset(monthName,0,4);
							len=sscanf(s, "%s %s %d %d:%d:%d %d", weekName,monthName,&day,&hour,&minute,&second,&year);
							if(len!=7)EXP(String("�����ַ�ʱ��\"")+s+String("\"���������ʽ��\"Mon May 14 02:03:55 2007\"�ַ���"));
							for(int i=1;i<=12;i++)
							{
								if(strcmp(MonthNames[i][2].c_str(),monthName)==0)
								{
									month=i;break;
								}
							}
							if(month==0)EXP(String("��ȡ���·��޷�ƥ��")+monthName);
							res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						}
						break;
					case StaDateTime:// yyyy-mm-dd hh:mi:ss
						len=sscanf(s, "%d-%d-%d %d:%d:%d", &year,&month,&day,&hour,&minute,&second);
						if(len!=6)EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"yyyy-mm-dd hh:mi:ss\"�ַ���");
						res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						break;
					case LongDate:				// yyyy��mm��dd��
						len=sscanf(s, "%d��%d��%d��", &year,&month,&day);
						if(len!=3)EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"yyyy��mm��dd��\"�ַ���");
						res=DateTime(year,month,day,hour,minute,second,millis,0,tz);
						break;
					case StaDate:		// yyyy-mm-dd
						len=sscanf(s, "%d-%d-%d", &year,&month,&day);
						if(len!=3)EXP(String("�����ַ�ʱ��\"")+s+"\"���������ʽ��\"yyyy-mm-dd\"�ַ���");
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
						EXP(String("�����ַ���\"")+s+"������֪��ʶ������ڸ�ʽ");
						break;
					}
				}
			};
			//
			//ժҪ��
			//		ʹ���ַ�����ַ�
			//		yyyy-mm-dd hh:mm:ss
			//		//	"yyyy-mm-dd"     "yyyy-mm-dd hh:mm:ss"		"yyyy-mm-dd hh:mm:ss.ff"
			//	// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
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
					else												//	// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
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
			///	��.otl_datetime ����ת��Ϊָ����ʽ���ַ���
			///	<code>ԭ�ͣ�static string ToString(otl_datetime &amp;_tm,DateTimeStyles style);</code>
			///	</summary>
			///	<param name="_tm">OTLʱ�����</param> 
			///	<param name="style">ָ�������ַ�����ʽ��</param> 
			///	<returns>��Ч��-tm�ַ�����ʾ��ʽ��</returns> 
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
				case StaUTC:				// Mon May 14 02:03:55 2007	// ���ڼ� �·� ���� ʱ:��:�� ��
					{
						DateTime dt=DateTime(_tm);
						return dt.ToString(style);
					}
					break;
				case StaDateTime:	// yyyy-mm-dd hh:mi:ss
					sprintf(p,"%04d-%02d-%02d %d:%02d:%02d",_tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second);
					break;
				case LongDate:				// yyyy��mm��dd��
					sprintf(p,"%04d��%d��%d��",_tm.year,_tm.month,_tm.day);
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
			///	��ȡ�˶����ʾʱ���.otl_datetime �����Чֵ
			///	<code>ԭ�ͣ�inline otl_datetime GetOtlTime();</code>
			///	</summary>
			///	<returns>��Ч��otl_datetime����</returns> 
			inline otl_datetime GetOtlTime(){return ToOtlTime();};
			otl_datetime ToOtlTime()
			{
				otl_datetime otlTime;
				GetDateParts(&otlTime.year,&otlTime.month,&otlTime.day,NULL,&otlTime.hour,&otlTime.minute,&otlTime.second);
				return otlTime;
			}
			///	<summary>
			///	ʹ�����������Դ˶���ֵ
			///	<code>ԭ�ͣ�DateTime&amp; operator&lt;&lt;(otl_datetime&amp; _tm);</code>
			///	</summary>
			///	<param name="_tm">OTLʱ�����</param> 
			///	<returns>�˶�����</returns> 
			DateTime& operator<<(otl_datetime& _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);
				return *this;
			};
			///	<summary>
			///	ʹ��OTLʱ�����ʵ��������
			///	<code>ԭ�ͣ�DateTime(otl_datetime _tm);</code>
			///	</summary>
			///	<param name="_tm">OTLʱ�����</param> 
			DateTime(otl_datetime _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);
			}
			///	<summary>
			///	ʹ��ORACLE�ڲ�ʱ��洢��ʽ��ʼ����ʵ������
			///	<code>ԭ�ͣ�DateTime(unsigned char * dtp,DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone));</code>
			///	</summary>
			///	<param name="dtp">ORACLE�ڲ��洢��ʽ��7�ֽ����ݡ�</param> 
			///	<param name="nullDefault">��ֵʱ��Ĭ��ֵ��</param> 
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
			///	ʹ��OTLʱ�����Դ˶���ֵ
			///	<code>ԭ�ͣ�DateTime &amp;operator=(otl_datetime _tm);</code>
			///	</summary>
			///	<param name="_tm">OTLʱ�����</param>
			///	<returns>�˶�����</returns> 
			DateTime &operator=(otl_datetime _tm)
			{
				this->_init( _tm.year,_tm.month,_tm.day,_tm.hour,_tm.minute,_tm.second,0,0,localTimeZone);return *this;
			};
			///	<summary>
			///	��ORACLE�ڲ��洢��ʱ���ֽڻ�ȡOTLʱ�����
			///	<code>ԭ�ͣ�inline static otl_datetime GetOtlTime(unsigned char * dtp,
			///                                 DateTime nullDefault=DateTime(1900,1,1,0,0,0,0,0,localTimeZone));</code>
			///	</summary>
			///	<param name="dtp">ORACLE�ڲ��洢��ʽ��7�ֽ����ݡ�</param> 
			///	<param name="nullDefault">��ֵʱ��Ĭ��ֵ��</param> 
			///	<returns>��Ч��otl_datetime����</returns> 
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
			///	��OLEʱ������ʼ����ʵ������
			///	<code>ԭ�ͣ�DateTime(OTL_SQL_TIMESTAMP_STRUCT * tmp);</code>
			///	</summary>
			///	<param name="tmp">OLEʱ�����</param> 
			DateTime(OTL_SQL_TIMESTAMP_STRUCT * tmp)
			{
				_init(tmp->year,tmp->month,tmp->day,tmp->hour,tmp->minute,tmp->second,0,0,localTimeZone);
			}
			///	<summary>
			///	��OLEʱ������ʼ����ʵ������
			///	<code>ԭ�ͣ�inline static otl_datetime GetOtlTime(OTL_SQL_TIMESTAMP_STRUCT * tmp,
			///                                DateTime nullDefault=otl_datetime(1900,1,1,0,0,0));</code>
			///	</summary>
			///	<param name="tmp">OLEʱ�����</param> 
			///	<param name="nullDefault">��ֵʱ��Ĭ��ֵ��</param> 
			///	<returns>��Ч��otl_datetime����</returns> 
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
	///	����ʱ�����ı�׼���������
	///	<code>ԭ�ͣ�inline ostream&amp; operator&lt;&lt;(ostream&amp; target, DateTime dt);</code>
	///	</summary>
	///	<param name="target">��׼�������</param> 
	///	<param name="dt">ʱ�����</param> 
	///	<returns>���������</returns> 
	EXPORT 	inline ostream& operator<<(ostream& target, DateTime dt)
	{
		target << dt.ToString();
		return target;
	}


#if defined(__OTL_H__)
	///	<summary>
	///	�����ַ�����OTLʱ���������������
	///	<code>ԭ�ͣ�inline otl_datetime&amp; operator>>(otl_datetime &amp;target,string &amp;s);</code>
	///	</summary>
	///	<param name="target">OTLʱ�����</param> 
	///	<param name="s">����������ַ�������</param> 
	///	<returns>OTL������</returns> 
	EXPORT inline otl_datetime& operator>>(otl_datetime &target,string &s)
	{
		if(target.year<=0 || target.year>=10000){s=""; return target;}
		char p[20];
		sprintf(p,"%04d-%02d-%02d %0d:%02d:%02d",target.year,target.month,target.day,target.hour,target.minute,target.second);
		s=p;
		return target;
	}

	///	<summary>
	///	����OTLʱ�����ı�׼���������
	///	<code>ԭ�ͣ�inline ostream&amp; operator&lt;&lt;(ostream&amp; target, otl_datetime dt);</code>
	///	</summary>
	///	<param name="target">��׼�������</param> 
	///	<param name="dt">OTLʱ�����</param> 
	///	<returns>���������</returns> 
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
