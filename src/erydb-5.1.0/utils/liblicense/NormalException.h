// ==============================================================
//progame      Common::Exception  simple exception class
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

#ifndef __Common_Exception_H__
#define __Common_Exception_H__

#include "LicCommon.h"  

namespace Common
{ 
	///	<summary>
	///	异常信息类
	///	</summary>
	///	<remarks>
	///	用于程序执行中异常信息的捕获与传递
	///	</remarks>
    /// <example><code>
    /// </code></example>
	class NormalException :public std::exception
	{
	public:
		const char* what(){ return Message.c_str(); }
		///	<summary>
		///	存储异常描述信息
		///	</summary>
		string Message;
		NormalException(){};
		///	<summary>
		///	解析对象构造函数，用于指定参数及参数检验条件初始化解析对象
		///	<code>原型：Exception(string s);</code>
		///	</summary>
		///	<param name="s">异常描述信息</param>
		NormalException(string s){
			this->Message = s;
	};
		///	<summary>
		///	获取异常信息数据指针
		///	<code>原型：const char  * GetMessage();</code>
		///	</summary>
		const char  * GetMessage()
		{
			return this->Message.c_str();
		}
		~NormalException()throw (){};
	};

	inline ostream& operator<<(ostream& target, const NormalException& s)
	{
		target << s.Message;
		return target;
	};
	inline static string getErrMsg(){return strerror(errno);};
	inline static string getErrMsg(int errCode){return strerror(errCode);};
	inline int getErrCode(){return errno;};
}
#ifndef EXP
#define EXP(msg) {String MSG=String(__FILE__)+String(":")+String(__LINE__)+String("\n");/* cout<<__FILE__<<": error  on line "<< __LINE__<<endl ;*/throw NormalException(MSG+msg);}
#endif
#ifndef PERR
#define PERR(msg) cout<<__FILE__<<msg<<":"<< " error on line "<< __LINE__<<endl ;
#endif
#ifndef ERR_FILE_LINE
#define ERR_FILE_LINE String("ERROR:")+String(__FILE__)+":"+ String(" on line ")+String(__LINE__)
#endif

#endif

