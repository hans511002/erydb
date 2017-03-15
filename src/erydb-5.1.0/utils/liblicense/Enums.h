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
	///	ָ�����������
	///	</summary>
	///	<remarks>
	/// <code>
	///		NONE		=       0,//δ֪���ͣ����ڲ���������
	///		CHAR		=       1,//char
	///		INT 		=       3,
	///		DOUBLE		=       4,
	///		STRING		=       5,//string ����
	///		DATE		=       12,
	///		LONG		=       20,
	///		LLONG		=       64,
	/// </code>
	///	</remarks>
	enum varType
	{
		NONE		=		0,//δ֪���ͣ����ڲ���������
		CHAR		=       1,//char
		INT			=       3,
		DOUBLE		=       4,
		STRING		=       5,//string ����
		DATE		=       12,
		LONG		=       20,
		LLONG		=		64,
	};    
	///	<summary>
	///	ָ�����õ� Overload:String.Split ���ط�����������ʡ�Է���ֵ�еĿ����ַ�����
	///	</summary>
	///	<remarks>
	/// <code>
	///		NONE = 0,//����ֵ�������п��ַ���������Ԫ��
	///		RemoveEmptyEntries = 1,//����ֵ���������п��ַ���������Ԫ�� 
	/// </code>
	///	</remarks>
	enum StringSplitOptions
	{
		None =0 ,
		RemoveEmptyEntries = 1
	};

	///	<summary>
	///	ʱ�����͡�
	///	</summary>
	///	<remarks>
	/// <code>
	///		Local = 0,//��ʾ��ʱ��Ϊ����ʱ��
	///		Utc = 1,//��ʾ��ʱ��Ϊ UTC 
	/// </code>
	///	</remarks>
	enum DateTimeKind
	{
		Local = 0,
		Utc = 1
	};
	///	<summary>
	///	���ڼ���
	///	</summary>
	///	<remarks>
	/// <code>
	///		Sunday = 0,//     ��ʾ�����ա�
	///		Monday = 1,//     ��ʾ����һ��
	///		Tuesday = 2,//     ��ʾ���ڶ���
	///		Wednesday = 3,//     ��ʾ��������
	///		Thursday = 4,//     ��ʾ�����ġ�
	///		Friday = 5,//     ��ʾ�����塣
	///		Saturday = 6//     ��ʾ�������� 
	/// </code>
	///	</remarks>
	enum DayOfWeek
	{
		Sunday = 0,//     ��ʾ�����ա�
		Monday = 1,//     ��ʾ����һ��
		Tuesday = 2,//     ��ʾ���ڶ���
		Wednesday = 3,//     ��ʾ��������
		Thursday = 4,//     ��ʾ�����ġ�
		Friday = 5,//     ��ʾ�����塣
		Saturday = 6//     ��ʾ��������
	};
	///	<summary>
	///	ʱ���ʽ��
	///	</summary>
	///	<remarks>
	/// <code>
	///		StaUTC,//	Wed Jan 02 02:03:55 1980	// ���ڼ� �·� ���� ʱ:��:�� ��
	///		StaDateTime, //	yyyy-mm-dd hh:mi:ss
	///		LongDate,//	yyyy��mm��dd��
	///		StaDate,//	yyyy-mm-dd
	///		StaTime,//	hh:mi:ss
	///		ShotDate,//	yyyymmdd
	///		ShotTime,//	hh:mi
	///		ShotDateTime,//	yyyymmddhhmiss
	/// </code>
	///	</remarks>
	enum DateTimeStyles
	{
		StaUTC,//	Wed Jan 02 02:03:55 1980	// ���ڼ� �·� ���� ʱ:��:�� ��
		StaDateTime, //	yyyy-mm-dd hh:mi:ss
		LongDate,//	yyyy��mm��dd��
		StaDate,//	yyyy-mm-dd
		StaTime,//	hh:mi:ss
		ShotDate,//	yyyymmdd
		ShotTime,//	hh:mi
		ShotDateTime,//	yyyymmddhhmiss
	};
	///	<summary>
	///	ʱ��ֵ��
	///	</summary>
	///	<remarks>
	/// <code>
	///		GMT_1=-1,     //��1  ��
	///		GMT_2=-2,     //��2  ��
	///		GMT_3=-3,     //��3  ��
	///		GMT_4=-4,     //��4  ��
	///		GMT_5=-5,     //��5  ��
	///		GMT_6=-6,     //��6  ��
	///		GMT_7=-7,     //��7  ��
	///		GMT_8=-8,     //��8  ��
	///		GMT_9=-9,     //��9  ��
	///		GMT_10=-10,   //��10 ��
	///		GMT_11=-11,   //��11 ��
	///		GMT_12=-12,   //��12 ��
	///		GMT0=0,       //��0  ��
	///		GMT1=1,       //��1  ��
	///		GMT2=2,       //��2  ��
	///		GMT3=3,       //��3  ��
	///		GMT4=4,       //��4  ��
	///		GMT5=5,       //��5  ��
	///		GMT6=6,       //��6  ��
	///		GMT7=7,       //��7  ��
	///		GMT8=8,       //��8  ��
	///		GMT9=9,       //��9  ��
	///		GMT10=10,     //��10 ��
	///		GMT11=11,     //��11 ��
	///		GMT12=12      //��12 ��
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
	///	ʱ�䲿�֡�
	///	</summary>
	///	<remarks>
	/// <code>
	///		Year,//��
	///		yearDay,//һ���еĵڶ�����
	///		Month,//��
	///		Day,//��
	///		Hour,//Сʱ
	///		Minute,//����
	///		Second,//��
	///		MillesSecond,//����
	///		WeekDay,//���ڼ�
	///		Usec//΢��
	/// </code>
	///	</remarks>
	enum DatePart
	{
		Year=0,//��
		yearDay,//һ���еĵڶ�����
		Month,//��
		Day,//��
		Hour,//Сʱ
		Minute,//����
		Second,//��
		MillesSecond,//����
		WeekDay,//���ڼ�
		Usec//΢�� Ҳ���Ƕ�Ӧ�Ŀ̶� ticks
	};
	///	<summary>
	///	���ݿ��ֶ�ӳ�����͡�����һ���ֶε������Ϣ
	///	</summary>
	///	<remarks>
	/// <code> 
	/// </code>
	///	</remarks>
	struct ColumnInfo
	{
		///	<summary>
		///	�ֶ�����,��д��ʽ��ʾ
		///	</summary>
		string name;
		///	<summary>
		///	���ݿ��ڲ���������
		///	</summary>
		///	<remarks><code> 
		///	�ֶε��ڲ��������ʹ��롣����CHAR�����ѡ����е����ִ��������ص��������������������
		///	����η���SQL��䡣�����ʹ��osql3��ʹ������Ϊ0��lngflg������oparse����˵��ORACLE�汾6�Ļ�����
		///	ʹ������Ϊ1��lnkflg������oparse�Ļ���CHAR�������������1������dbtype����96��
		///	ѡ����е�USER�������Ƿ����������ʹ���1��
		/// </code></remarks>
		int  dbtype;
		///	<summary>
		///	��Ӧ��otl��������
		///	</summary>
		int  otl_var_dbtype;
		///	<summary>
		///	���ݿ��ڲ��ֶδ�С
		///	</summary>
		///	<remarks><code> 
		///	oracle�������       		      ֵ
		///	CHAR,VARCHAR2,RAW 		        �����еĳ���
		///	NUMBER            		        22(�ڲ�����)
		///	DATE             		         7(�ڲ�����)
		///	LONG LONGRAW     		          0
		///	ROWID            			      (ϵͳ����)
		///	������������1�ĳ���(��:to_char())��dsize��ͬ
		/// </code></remarks>
		int  dbsize;
		///	<summary>
		///	��ֵ�ֶεľ��ȣ�������λ����
		///	</summary>
		///	<remarks><code> 
		///	��������ѡ�����ľ��ȣ�������һ������������λ����
		///	�������Ҫ����ֵ���ͰѸò���ָ��Ϊ0��
		/// </code></remarks>
		int  prec;
		///	<summary>
		///	�����������ֶεĶ��꣬С��λ���ȡ��������Ҫ����ֵ���ͰѸò�����Ϊ0��
		///	</summary>
		///	<remarks><code> 
		///	�����������ֶεĶ��ꡣ�������Ҫ����ֵ���ͰѸò�����Ϊ0��
		///	���ڰ汾6��RDBMS��odescr���������Ķ������Ķ���;��ȡ����ڸ�����������0���ȺͶ��ꡣ������ʾ��
		///	SQL��������			      ����		����
		///	NUMBER(p)				    p         0
		///	NUMBER(p,s)   			    p         S
		///	NUMBER        			    0         0
		///	float(n)       	        	0         0
		///	����ORACLE7��SQL����REAL��DOUBLE PRECISION��DOUBLE��DOUBLE(N)	����ʵ�ʵľ��Ⱥ�-127�Ķ��ꡣ
		/// </code></remarks>
		int  scale;
		///	<summary>
		///	��ʶ�ֶ��Ƿ��Ϊ null ֵ
		///	</summary>
		///	<remarks><code> 
		///	���룺�����Ҫѡ�������Null״̬����Ѹò���ָ��Ϊ0��
		///	���������в�����Nullֵ���򷵻�0���������Nullֵ�򷵻ط�0��
		/// </code></remarks>
		int  nullok;
		///	<summary>
		///	�ֶ���������
		///	</summary>
		string typeName;
		ColumnInfo():dbtype(0),otl_var_dbtype(0),dbsize(0),prec(0),scale(0),nullok(0){}
	};



	// for FileSystem                                              
	///	<summary>
	///	Ŀ¼����ѡ��
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
	///	�ļ�ָ���ƶ�ģʽ
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
	///	�ļ�����
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
	///	�ļ�����ģʽ
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
	///	�ļ�����Ȩ��
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
	///	�ļ�����
	///	</summary>
	///	<remarks>
	/// <code> 
	///		Archive = 0x20,			//����ļ�
	///		Compressed = 0x800,		//ѹ���ļ�
	///		Device = 0x40,			//����
	///		Directory = 0x10,		//Ŀ¼
	///		Encrypted = 0x4000,		//����
	///		Hidden = 2,				//����
	///		Normal = 0x80,			//����
	///		ReadOnly = 1,			//ֻ��
	///		ReparsePoint = 0x400,	
	///		SparseFile = 0x200,
	///		Systemic = 4,				//ϵͳ
	///		Temporary = 0x100		//��ʱ
	/// </code>
	///	</remarks>
	enum FileAttributes
	{
		Archive = 0x20,			//����ļ�
		Compressed = 0x800,		//ѹ���ļ�
		Device = 0x40,			//����
		Directory = 0x10,		//Ŀ¼
		Encrypted = 0x4000,		//����
		Hidden = 2,				//����
		Normal = 0x80,			//����
		ReadOnly = 1,			//ֻ��
		ReparsePoint = 0x400,	
		SparseFile = 0x200,
		Systemic = 4,				//ϵͳ
		Temporary = 0x100		//��ʱ
	};

}
#endif
