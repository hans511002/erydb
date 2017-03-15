// ==============================================================
//progame      Common namespace using enums
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

#ifndef __Common_Enums_H__
#define __Common_Enums_H__
 

namespace Common
{
	///	<summary>
	///	指定对象的类型
	///	</summary>
	///	<remarks>
	/// <code>
	///		NONE		=       0,//未知类型，用于参数开关项
	///		CHAR		=       1,//char
	///		INT 		=       3,
	///		DOUBLE		=       4,
	///		STRING		=       5,//string 对象
	///		DATE		=       12,
	///		LONG		=       20,
	///		LLONG		=       64,
	/// </code>
	///	</remarks>
	enum varType
	{
		NONE		=		0,//未知类型，用于参数开关项
		CHAR		=       1,//char
		INT			=       3,
		DOUBLE		=       4,
		STRING		=       5,//string 对象
		DATE		=       12,
		LONG		=       20,
		LLONG		=		64,
	};    
	///	<summary>
	///	指定适用的 Overload:String.Split 重载方法包含还是省略返回值中的空子字符串。
	///	</summary>
	///	<remarks>
	/// <code>
	///		NONE = 0,//返回值包括含有空字符串的数组元素
	///		RemoveEmptyEntries = 1,//返回值不包括含有空字符串的数组元素 
	/// </code>
	///	</remarks>
	enum StringSplitOptions
	{
		None =0 ,
		RemoveEmptyEntries = 1
	};

	///	<summary>
	///	时间类型。
	///	</summary>
	///	<remarks>
	/// <code>
	///		Local = 0,//表示的时间为本地时间
	///		Utc = 1,//表示的时间为 UTC 
	/// </code>
	///	</remarks>
	enum DateTimeKind
	{
		Local = 0,
		Utc = 1
	};
	///	<summary>
	///	星期几。
	///	</summary>
	///	<remarks>
	/// <code>
	///		Sunday = 0,//     表示星期日。
	///		Monday = 1,//     表示星期一。
	///		Tuesday = 2,//     表示星期二。
	///		Wednesday = 3,//     表示星期三。
	///		Thursday = 4,//     表示星期四。
	///		Friday = 5,//     表示星期五。
	///		Saturday = 6//     表示星期六。 
	/// </code>
	///	</remarks>
	enum DayOfWeek
	{
		Sunday = 0,//     表示星期日。
		Monday = 1,//     表示星期一。
		Tuesday = 2,//     表示星期二。
		Wednesday = 3,//     表示星期三。
		Thursday = 4,//     表示星期四。
		Friday = 5,//     表示星期五。
		Saturday = 6//     表示星期六。
	};
	///	<summary>
	///	时间格式。
	///	</summary>
	///	<remarks>
	/// <code>
	///		StaUTC,//	Wed Jan 02 02:03:55 1980	// 星期几 月份 日期 时:分:秒 年
	///		StaDateTime, //	yyyy-mm-dd hh:mi:ss
	///		LongDate,//	yyyy年mm月dd日
	///		StaDate,//	yyyy-mm-dd
	///		StaTime,//	hh:mi:ss
	///		ShotDate,//	yyyymmdd
	///		ShotTime,//	hh:mi
	///		ShotDateTime,//	yyyymmddhhmiss
	/// </code>
	///	</remarks>
	enum DateTimeStyles
	{
		StaUTC,//	Wed Jan 02 02:03:55 1980	// 星期几 月份 日期 时:分:秒 年
		StaDateTime, //	yyyy-mm-dd hh:mi:ss
		LongDate,//	yyyy年mm月dd日
		StaDate,//	yyyy-mm-dd
		StaTime,//	hh:mi:ss
		ShotDate,//	yyyymmdd
		ShotTime,//	hh:mi
		ShotDateTime,//	yyyymmddhhmiss
	};
	///	<summary>
	///	时区值。
	///	</summary>
	///	<remarks>
	/// <code>
	///		GMT_1=-1,     //西1  区
	///		GMT_2=-2,     //西2  区
	///		GMT_3=-3,     //西3  区
	///		GMT_4=-4,     //西4  区
	///		GMT_5=-5,     //西5  区
	///		GMT_6=-6,     //西6  区
	///		GMT_7=-7,     //西7  区
	///		GMT_8=-8,     //西8  区
	///		GMT_9=-9,     //西9  区
	///		GMT_10=-10,   //西10 区
	///		GMT_11=-11,   //西11 区
	///		GMT_12=-12,   //西12 区
	///		GMT0=0,       //东0  区
	///		GMT1=1,       //东1  区
	///		GMT2=2,       //东2  区
	///		GMT3=3,       //东3  区
	///		GMT4=4,       //东4  区
	///		GMT5=5,       //东5  区
	///		GMT6=6,       //东6  区
	///		GMT7=7,       //东7  区
	///		GMT8=8,       //东8  区
	///		GMT9=9,       //东9  区
	///		GMT10=10,     //东10 区
	///		GMT11=11,     //东11 区
	///		GMT12=12      //东12 区
	/// </code>
	///	</remarks>
	enum TimeZone
	{
		GMT_1=-1,
		GMT_2=-2,
		GMT_3=-3,
		GMT_4=-4,
		GMT_5=-5,
		GMT_6=-6,
		GMT_7=-7,
		GMT_8=-8,
		GMT_9=-9,
		GMT_10=-10,
		GMT_11=-11,
		GMT_12=-12,
		GMT0=0,
		GMT1=1,
		GMT2=2,
		GMT3=3,
		GMT4=4,
		GMT5=5,
		GMT6=6,
		GMT7=7,
		GMT8=8,
		GMT9=9,
		GMT10=10,
		GMT11=11,
		GMT12=12
	};
	///	<summary>
	///	时间部分。
	///	</summary>
	///	<remarks>
	/// <code>
	///		Year,//年
	///		yearDay,//一年中的第多少天
	///		Month,//月
	///		Day,//日
	///		Hour,//小时
	///		Minute,//分钟
	///		Second,//秒
	///		MillesSecond,//毫秒
	///		WeekDay,//星期几
	///		Usec//微秒
	/// </code>
	///	</remarks>
	enum DatePart
	{
		Year=0,//年
		yearDay,//一年中的第多少天
		Month,//月
		Day,//日
		Hour,//小时
		Minute,//分钟
		Second,//秒
		MillesSecond,//毫秒
		WeekDay,//星期几
		Usec//微秒 也就是对应的刻度 ticks
	};
	///	<summary>
	///	数据库字段映射类型。描述一个字段的相关信息
	///	</summary>
	///	<remarks>
	/// <code> 
	/// </code>
	///	</remarks>
	struct ColumnInfo
	{
		///	<summary>
		///	字段名称,大写形式表示
		///	</summary>
		string name;
		///	<summary>
		///	数据库内部数据类型
		///	</summary>
		///	<remarks><code> 
		///	字段的内部数据类型代码。对于CHAR项（包括选择表中的文字串），返回的数据类型码可能依赖于
		///	你如何分析SQL语句。如果你使用osql3或使用设置为0的lngflg参数的oparse或者说在ORACLE版本6的环境下
		///	使用设置为1的lnkflg参数的oparse的话，CHAR项返回数据类型码1，否则dbtype返回96。
		///	选择表中的USER函数总是返回数据类型代码1。
		/// </code></remarks>
		int  dbtype;
		///	<summary>
		///	对应的otl数据类型
		///	</summary>
		int  otl_var_dbtype;
		///	<summary>
		///	数据库内部字段大小
		///	</summary>
		///	<remarks><code> 
		///	oracle表的类型       		      值
		///	CHAR,VARCHAR2,RAW 		        表中列的长度
		///	NUMBER            		        22(内部长度)
		///	DATE             		         7(内部长度)
		///	LONG LONGRAW     		          0
		///	ROWID            			      (系统依赖)
		///	返回数据类型1的长度(如:to_char())和dsize相同
		/// </code></remarks>
		int  dbsize;
		///	<summary>
		///	数值字段的精度（数字总位数）
		///	</summary>
		///	<remarks><code> 
		///	返回数字选择表项的精度，精度是一个数的数字总位数。
		///	如果不需要精度值，就把该参数指定为0。
		/// </code></remarks>
		int  prec;
		///	<summary>
		///	返回数字型字段的定标，小数位精度。如果不需要定标值，就把该参数作为0。
		///	</summary>
		///	<remarks><code> 
		///	返回数字型字段的定标。如果不需要定标值，就把该参数作为0。
		///	对于版本6的RDBMS，odescr返回真正的定点数的定标和精度。对于浮点数，返回0精度和定标。如下所示：
		///	SQL数据类型			      精度		定标
		///	NUMBER(p)				    p         0
		///	NUMBER(p,s)   			    p         S
		///	NUMBER        			    0         0
		///	float(n)       	        	0         0
		///	对于ORACLE7，SQL类型REAL、DOUBLE PRECISION、DOUBLE和DOUBLE(N)	返回实际的精度和-127的定标。
		/// </code></remarks>
		int  scale;
		///	<summary>
		///	标识字段是否可为 null 值
		///	</summary>
		///	<remarks><code> 
		///	输入：如果需要选择列项的Null状态，则把该参数指定为0。
		///	输出：如果列不允许Null值，则返回0；如果允许Null值则返回非0。
		/// </code></remarks>
		int  nullok;
		///	<summary>
		///	字段类型名称
		///	</summary>
		string typeName;
		ColumnInfo():dbtype(0),otl_var_dbtype(0),dbsize(0),prec(0),scale(0),nullok(0){}
	};



	// for FileSystem                                              
	///	<summary>
	///	目录查找选项
	///	</summary>
	///	<remarks>
	/// <code> 
	///	AllDirectories = 1,
	///	TopDirectoryOnly = 0
	/// </code>
	///	</remarks>
	enum SearchOption
	{
		// Fields
		AllDirectories = 1,
		TopDirectoryOnly = 0
	};
	///	<summary>
	///	文件指针移动模式
	///	</summary>
	///	<remarks>
	/// <code> 
	///	Begin = 0,
	///	Current =1,
	///	End =2,
	/// </code>
	///	</remarks>
	enum SeekOrigin
	{
		Begin = 0,
		Current = 1,
		End = 2
	};
	///	<summary>
	///	文件类型
	///	</summary>
	///	<remarks>
	/// <code> 
	///	Text = 0,
	///	Binarry =1, 
	/// </code>
	///	</remarks>
	enum FileType
	{
		Text=0,
		Binarry=1,
	};
	///	<summary>
	///	文件操作模式
	///	</summary>
	///	<remarks>
	/// <code> 
	///		Append = 6,
	///		Create = 2,
	///		CreateNew = 1,
	///		Open = 3,
	///		OpenOrCreate = 4,
	///		Truncate = 5
	/// </code>
	///	</remarks>
	enum FileMode
	{
		Append = 6,
		Create = 2,
		CreateNew = 1,
		Open = 3,
		OpenOrCreate = 4,
		Truncate = 5
	};
	///	<summary>
	///	文件操作权限
	///	</summary>
	///	<remarks>
	/// <code> 
	///	Read = 1,
	///	ReadWrite = 3,
	///	Write = 2
	/// </code>
	///	</remarks>
	enum FileAccess
	{
		Read = 1,
		ReadWrite = 3,
		Write = 2
	};
	///	<summary>
	///	文件属性
	///	</summary>
	///	<remarks>
	/// <code> 
	///		Archive = 0x20,			//打包文件
	///		Compressed = 0x800,		//压缩文件
	///		Device = 0x40,			//驱动
	///		Directory = 0x10,		//目录
	///		Encrypted = 0x4000,		//加密
	///		Hidden = 2,				//隐藏
	///		Normal = 0x80,			//常规
	///		ReadOnly = 1,			//只读
	///		ReparsePoint = 0x400,	
	///		SparseFile = 0x200,
	///		Systemic = 4,				//系统
	///		Temporary = 0x100		//临时
	/// </code>
	///	</remarks>
	enum FileAttributes
	{
		Archive = 0x20,			//打包文件
		Compressed = 0x800,		//压缩文件
		Device = 0x40,			//驱动
		Directory = 0x10,		//目录
		Encrypted = 0x4000,		//加密
		Hidden = 2,				//隐藏
		Normal = 0x80,			//常规
		ReadOnly = 1,			//只读
		ReparsePoint = 0x400,	
		SparseFile = 0x200,
		Systemic = 4,				//系统
		Temporary = 0x100		//临时
	};

}
#endif
