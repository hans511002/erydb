// ==============================================================
//progame      Common::String
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
#include "MYString.h"  

namespace Common
{
	// 摘要:
    //     表示空字符串。此字段为只读。
	const char String::WhitespaceChars[]={'\t','\n','\v','\f','\r',' ','\b','\a'};
	//
	//
    // 摘要:
    //     字符拆分,返回包含此实例中的子字符串的 Common.String 数组。
    //
    // 参数:
    //   separator:
    //     分隔此实例中子字符串的 ASCII 字符。
    //
    // 返回结果:
    //     一个数组，其元素包含此实例中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
	//
	void String::Split(Array<String>  &result,char separator,StringSplitOptions options,int count)
	{
		if(separator==0)
		{
			if(count>this->size() || count==0)count=this->size();
			result.resize(count);
			for(int i=0;i<result.size();i++)
				result[i]=String(this->at(i));
		}
		else
		{
			bool remove=(options==RemoveEmptyEntries);
			int len=1;
			int index=-1,prevIndex=index;
			while((index=this->IndexOf(separator,index+1,0))>-1)
			{
				if(remove && prevIndex==index-1)continue;
				len++;
				prevIndex=index;
				if(count!=0 && count<=len )break;
			}
			result.resize(len);
			index=-1;prevIndex=index;
			int i=0,startIndex=index+1;
			while((index=this->IndexOf(separator,startIndex,0))>-1)
			{
				if(remove && prevIndex==index-1)
				{
					startIndex=index+1;
					prevIndex=index;continue;
				}
				result[i]=this->SubString(startIndex,index-prevIndex-1);
				startIndex=index+1;
				prevIndex=index;
				i++;
				if(count!=0 && count<=i )return;
			}
			result[i]=this->SubString(startIndex);
		}
	}
    //
    // 摘要:
    //     字符数组拆分,返回包含此字符串中的子字符串（由指定的 Common.Char 数组的元素分隔）的 Common.String 数组。参数指定要返回子字符串的最大数量，以及是否要返回空数组元素。
    //
    // 参数:
    //   count:
    //     要返回的子字符串的最大数量。
    //
    //   options:
    //     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
    //     以包含返回的数组中的空数组元素。
    //
    //   separator:
    //     分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null。
    //
    // 返回结果:
    //     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
    void String::Split(Array<String>  &result,Array<char> & separator, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		String temp=String::Join(separator,"");
		Split(result, temp, false, options, count);
	}
	//
	// 摘要:
	//     字符串拆分,返回包含此字符串中的子字符串（由指定的 Common.Char 数组的元素分隔）的 Common.String 数组。参数指定是否返回空数组元素。
	//
	// 参数:
	//   options:
	//     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
	//     以包含返回的数组中的空数组元素。
	//
	//   separator:
	//     分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null。
	//
	// 返回结果:
	//     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
	//
    void String::Split(Array<String>  &result,String separator,bool isString, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		if(isString)
		{
			if(separator.empty())
			{
				result.resize(1);
				result[0]=*this;
			}
			else
			{
				int slen=separator.size();
				Array<int> indexs;
				int index=-1;
				while((index=this->IndexOf(separator,index+slen,false))>-1)
					indexs.push_back(index);
				indexs.push_back(this->size());
				if(!remove || indexs[0]!=0)
					result.push_back(this->SubString(0,indexs[0]));
				int ilen=indexs.size();
				for(int i=1;i<ilen;i++)
				{
					if(!remove || indexs[i]!=indexs[i-1]+slen)
						if(count==0 || result.size()<count)
						result.push_back(this->SubString(indexs[i-1]+slen,indexs[i]-indexs[i-1]-slen));
				}
				//int size=0;
				//int prevIndex=index;
				//while((index=this->IndexOf(separator,index+slen,0))>-1)
				//{
				//	if(remove && prevIndex==index-(int)slen && (size!=0||index==0))
				//	{
				//		prevIndex=index;
				//		continue;
				//	}
				//	size++;
				//	prevIndex=index;
				//	if(count!=0 && size>=count)break;
				//}
				////result= Array<String>(size);
				//if((remove && (count==0 || size<count ) && prevIndex!=this->size()-slen)||(!remove && (count==0 || size<count)))
				//	size++;

				//result.resize(size);
				//index=-1;prevIndex=index;
				//int i=0,startIndex=index+1;
				//while((index=this->IndexOf(separator,startIndex,0))>-1)
				//{
				//	if(remove && prevIndex==index-(int)slen && (i!=0||index==0))
				//	{
				//		prevIndex=index;
				//		startIndex=index+slen;
				//		continue;
				//	}
				//	if(i==0)
				//	{
				//		result[i]=this->SubString(startIndex,index);
				//	}
				//	else
				//	{
				//		result[i]=this->SubString(startIndex,index-startIndex);
				//	}
				//	startIndex=index+slen;
				//	prevIndex=index;
				//	i++;
				//	if(count!=0 && i>=count)return;
				//}
				//if(i<result.size())result[i]=this->SubString(startIndex);
			}
		}
		else
		{
			Array<int> indexs;
			const char * p=this->c_str();
			const char * sp=separator.c_str();
			int i=0;
			while(p[i])
			{
				if(strchr(sp,p[i]))
					indexs.push_back(i);
				i++;
			}
			indexs.push_back(this->size());
			if(!remove || indexs[0]!=0)
				result.push_back(this->SubString(0,indexs[0]));
			int ilen=indexs.size();
			int slen=1;
			for(int i=1;i<ilen;i++)
			{
				if(!remove || indexs[i]!=indexs[i-1]+slen)
					if(count==0 || result.size()<count)
					result.push_back(this->SubString(indexs[i-1]+slen,indexs[i]-indexs[i-1]-slen));
			}
			//String temp=separator;
			//int len=0,i=0, prevIndex=-1,spLen=0;
			////const char * p=this->c_str();
			//while(p[i])
			//{
			//	if(temp.IndexOf(p[i])>-1)
			//	{
			//		if(remove && prevIndex==i-1)
			//		{
			//			prevIndex=i;
			//			i++;
			//			continue;
			//		}
			//		prevIndex=i;
			//		len++;
			//		i++;
			//		if(count!=0 && len>=count)break;
			//	}
			//	else
			//	{
			//		i++;
			//	}
			//}
			//if((remove && (count==0 || len<count ) && prevIndex!=this->size()-1)||(!remove && (count==0 || len<count)))
			//	len++;
			//result.resize(len);
			//len=0; prevIndex=-1; i=0,spLen=0;
			//p=this->c_str();
			//while(p[i])
			//{
			//	if(temp.IndexOf(p[i])>-1)
			//	{
			//		if(remove && prevIndex==i-1)
			//		{
			//			prevIndex=i;
			//			i++;
			//			continue;
			//		}
			//		result[len]=this->SubString(i-spLen,spLen);
			//		prevIndex=i;
			//		len++;
			//		spLen=0;
			//		if(len>=result.size())break;
			//	}
			//	else
			//	{
			//		if(i<=(int)this->size()-1)//arr[len]=this->SubString(prevIndex+1);
			//		{
			//			spLen++;
			//		}
			//	}
			//	i++;
			//}
			//if(len<result.size())result[len]=this->SubString(prevIndex+1);
		}
	}

    //
    // 摘要:
    //     字符串数组拆分,返回包含此字符串中的子字符串（由指定的 Common.String 数组的元素分隔）的 Common.String 数组。参数指定要返回子字符串的最大数量，以及是否要返回空数组元素。
    //
    // 参数:
    //   count:
    //     要返回的子字符串的最大数量。
    //
    //   options:
    //     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
    //     以包含返回的数组中的空数组元素。
    //
    //   separator:
    //     分隔此字符串中子字符串的字符串数组、不包含分隔符的空数组或null。
    //
    // 返回结果:
    //     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符串分隔。有关更多信息，请参见备注部分。
	void String::Split(Array<String>  &result,Array<String> &separators, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		int  index = 0,Size=this->size()+1;
		int  num1 = separators.size();
		const char * chRef=this->c_str();
		int * sepList = new int[Size];				//	拆分字符串索引
		int * lengthList = new int[Size];			//	拆分字符串长度
		String::memset(sepList,0,sizeof(int)*Size);
		String::memset(lengthList,0,sizeof(int)*Size);

		for (int  i = 0; ((i < this->size()) && (index < this->size())); i++)
        {
			for (int  j = 0; (j < separators.size()); j++)
            {
				if (!separators[j].empty())
                {
					int  num5 = separators[j].size();
					if (((chRef[i] == separators[j][0]) && (num5 <= ((int)this->size()- i))))
                    {
                        if(((num5 == 1) || (String::strcmp(chRef, i, separators[j].c_str(), 0, num5) == 0)))
                        {
                            sepList[index] = i;
                            lengthList[index] = num5;
                            index++;
                            i += (num5 - 1);
                            break;
                        }
                    }
                }
            }
        }
		if(sepList[index-1]+lengthList[index-1]==(int)this->size())
		{
			sepList[index]=this->size();
			lengthList[index]=1;
		}
		else
		{
			sepList[index]=this->size();
			lengthList[index]=1;
		}
		int startIndex = 0;
		int * nullIndex = new int[index+1];			//	标识是否为空字符串
		String::memset(nullIndex,0,sizeof(int)*(index+1));
        //拆分字符串位置
		//for(int i=0;i<size;i++)
		//{
		//	if(lengthList[i]!=0)
		//		printf("sepList[%d]=%d\t lengthList[%d]=%d\n",i,sepList[i] ,i,lengthList[i]);
		//}
		int len=index+1;
		int size=0;
		for (int  i = 0; ((i < index+1) && (startIndex <=this->size())); i++)
		{
			if(remove && sepList[i] - startIndex==0)
			{
				nullIndex[i]=1;
			}
			else
			{
				size++;
			}
			startIndex = sepList[i] + lengthList[i];
		}
        //空字符串位置
		//for(int i=0;i<len;i++)
		//{
		//	printf("nullIndex[%d]=%d\t \n",i,nullIndex[i] );
		//}
		//result= Array<String>(size);
        if(count!=0 && size>=count)size=count;
		result.resize(size);
		size=0;
		startIndex=0;
		index=0;
		for (int  i = 0; ((i < len) && (startIndex <= this->size())); i++)
		{
			if(nullIndex[index++]==0 && size<result.size())
			{
				 result[size++]=this->SubString(startIndex, (sepList[i] - startIndex));
			}
			startIndex =sepList[i] +lengthList[i];
		}
		//for(int i=0;i<size;i++)
		//	printf("String arr[%d]:%s\n",i,result[i].c_str());

		delete sepList;
		delete lengthList;
		delete nullIndex;
	}
	//
	//
    // 摘要:
    //     字符拆分,返回包含此实例中的子字符串的 Common.string 数组。
    //
    // 参数:
    //   separator:
    //     分隔此实例中子字符串的 ASCII 字符。
    //
    // 返回结果:
    //     一个数组，其元素包含此实例中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
	//
	void String::Split(Array<string>  &result,string str,char separator,StringSplitOptions options,int count)
	{
		if(separator==0)
		{
			if(count>str.size() || count==0)count=str.size();
			result.resize(count);
			for(int i=0;i<result.size();i++)
				result[i]=string(&str.at(i));
		}
		else
		{
			bool remove=(options==RemoveEmptyEntries);
			int len=1;
			int index=-1,prevIndex=index;
			while((index=String::IndexOf(str,separator,index+1,false))>-1)
			{
				if(remove && prevIndex==index-1)continue;
				len++;
				prevIndex=index;
				if(count!=0 && count<=len )break;
			}
			result.resize(len);
			index=-1;prevIndex=index;
			int i=0,startIndex=index+1;
			while((index=String::IndexOf(str,separator,startIndex,false))>-1)
			{
				if(remove && prevIndex==index-1)
				{
					startIndex=index+1;
					prevIndex=index;continue;
				}
				result[i]=str.substr(startIndex,index-prevIndex-1);
				startIndex=index+1;
				prevIndex=index;
				i++;
				if(count!=0 && count<=i )return;
			}
			result[i]=str.substr(startIndex);
		}
	}
    //
    // 摘要:
    //     字符数组拆分,返回包含此字符串中的子字符串（由指定的 Common.Char 数组的元素分隔）的 Common.string 数组。参数指定要返回子字符串的最大数量，以及是否要返回空数组元素。
    //
    // 参数:
    //   count:
    //     要返回的子字符串的最大数量。
    //
    //   options:
    //     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
    //     以包含返回的数组中的空数组元素。
    //
    //   separator:
    //     分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null。
    //
    // 返回结果:
    //     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
    void String::Split(Array<string>  &result,string str,Array<char> & separator, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		string temp=String::Join(separator,"");
		Split(result,str, temp, false, options, count);
	}
	//
	// 摘要:
	//     字符串拆分,返回包含此字符串中的子字符串（由指定的 Common.Char 数组的元素分隔）的 Common.string 数组。参数指定是否返回空数组元素。
	//
	// 参数:
	//   options:
	//     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
	//     以包含返回的数组中的空数组元素。
	//
	//   separator:
	//     分隔此字符串中子字符串的 ASCII 字符数组、不包含分隔符的空数组或null。
	//
	// 返回结果:
	//     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符分隔。有关更多信息，请参见备注部分。
	//
    void String::Split(Array<string>  &result,string str,string separator,bool isString, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		if(isString)
		{
			if(separator.empty())
			{
				result.resize(1);
				result[0]=str;
			}
			else
			{

				int slen=separator.size();
				Array<int> indexs;
				int index=-1;
				while((index=String::IndexOf(str,separator,index+slen,false))>-1)
					indexs.push_back(index);
				indexs.push_back(str.size());
				if(!remove || indexs[0]!=0)
					result.push_back(str.substr(0,indexs[0]));
				int ilen=indexs.size();
				for(int i=1;i<ilen;i++)
				{
					if(!remove || indexs[i]!=indexs[i-1]+slen)
						if(count==0 || result.size()<count)
						result.push_back(str.substr(indexs[i-1]+slen,indexs[i]-indexs[i-1]-slen));
				}
				return;

				//int size=0;
				//int prevIndex=index;
				//while((index=String::IndexOf(str,separator,index+1,0))>-1)
				//{
				//	if(remove && prevIndex==index-(int)separator.size()  && (size!=0||index==0))
				//	{
				//		prevIndex=index;
				//		continue;
				//	}
				//	size++;
				//	prevIndex=index;
				//	if(count!=0 && size>=count)break;
				//}
				////result= Array<string>(size);
				//if((remove && (count==0 || size<count ) && prevIndex!=str.size()-separator.size())||(!remove && (count==0 || size<count)))
				//	size++;

				//result.resize(size);
				//index=-1;prevIndex=index;
				//int i=0,startIndex=index+1;
				//while((index=String::IndexOf(str,separator,startIndex,0))>-1)
				//{
				//	if(remove && prevIndex==index-(int)separator.size() && (i!=0||index==0))
				//	{
				//		prevIndex=index;
				//		startIndex=index+separator.size();
				//		continue;
				//	}
				//	if(i==0)
				//	{
				//		result[i]=str.substr(startIndex,index);
				//	}
				//	else
				//	{
				//		result[i]=str.substr(startIndex,index-startIndex);
				//	}
				//	startIndex=index+separator.size();
				//	prevIndex=index;
				//	i++;
				//	if(count!=0 && i>=count)return;
				//}
				//if(i<result.size())result[i]=str.substr(startIndex);
			}
		}
		else
		{
			Array<int> indexs;
			const char * p=str.c_str();
			const char * sp=separator.c_str();
			int i=0;
			while(p[i])
			{
				if(strchr(sp,p[i]))
					indexs.push_back(i);
				i++;
			}
			indexs.push_back(str.size());
			if(!remove || indexs[0]!=0)
				result.push_back(str.substr(0,indexs[0]));
			int ilen=indexs.size();
			int slen=1;
			for(int i=1;i<ilen;i++)
			{
				if(!remove || indexs[i]!=indexs[i-1]+slen)
					if(count==0 || result.size()<count)
					result.push_back(str.substr(indexs[i-1]+slen,indexs[i]-indexs[i-1]-slen));
			}



			//string temp=separator;
			//int len=0,i=0, prevIndex=-1,spLen=0;
			//const char * p=str.c_str();
			//while(p[i])
			//{
			//	if(String::IndexOf(temp,p[i])>-1)
			//	{
			//		if(remove && prevIndex==i-1)
			//		{
			//			prevIndex=i;
			//			i++;
			//			continue;
			//		}
			//		prevIndex=i;
			//		len++;
			//		i++;
			//		if(count!=0 && len>=count)break;
			//	}
			//	else
			//	{
			//		i++;
			//	}
			//}
			//if((remove && (count==0 || len<count ) && prevIndex!=str.size()-1)||(!remove && (count==0 || len<count)))
			//	len++;
			//result.resize(len);
			//len=0; prevIndex=-1; i=0,spLen=0;
			//p=str.c_str();
			//while(p[i])
			//{
			//	if(String::IndexOf(temp,p[i])>-1)
			//	{
			//		if(remove && prevIndex==i-1)
			//		{
			//			prevIndex=i;
			//			i++;
			//			continue;
			//		}
			//		result[len]=str.substr(i-spLen,spLen);
			//		prevIndex=i;
			//		len++;
			//		spLen=0;
			//		if(len>=result.size())break;
			//	}
			//	else
			//	{
			//		if(i<=(int)str.size()-1)//arr[len]=str.substr(prevIndex+1);
			//		{
			//			spLen++;
			//		}
			//	}
			//	i++;
			//}
			//if(len<result.size())result[len]=str.substr(prevIndex+1);
		}
	}

    //
    // 摘要:
    //     字符串数组拆分,返回包含此字符串中的子字符串（由指定的 Common.string 数组的元素分隔）的 Common.string 数组。参数指定要返回子字符串的最大数量，以及是否要返回空数组元素。
    //
    // 参数:
    //   count:
    //     要返回的子字符串的最大数量。
    //
    //   options:
    //     指定 Common.StringSplitOptions.RemoveEmptyEntries 以省略返回的数组中的空数组元素，或指定 Common.StringSplitOptions.None
    //     以包含返回的数组中的空数组元素。
    //
    //   separator:
    //     分隔此字符串中子字符串的字符串数组、不包含分隔符的空数组或null。
    //
    // 返回结果:
    //     一个数组，其元素包含此字符串中的子字符串，这些子字符串由 separator 中的一个或多个字符串分隔。有关更多信息，请参见备注部分。
	void String::Split(Array<string>  &result,string str,Array<string> &separators, StringSplitOptions options, int count)
	{
		bool remove=(options==RemoveEmptyEntries);
		int  index = 0,Size=str.size()+1;
		int  num1 = separators.size();
		const char * chRef=str.c_str();
		int * sepList = new int[Size];				//	拆分字符串索引
		int * lengthList = new int[Size];			//	拆分字符串长度
		String::memset(sepList,0,sizeof(int)*Size);
		String::memset(lengthList,0,sizeof(int)*Size);

		for (int  i = 0; ((i < str.size()) && (index < str.size())); i++)
        {
			for (int  j = 0; (j < separators.size()); j++)
            {
				if (!separators[j].empty())
                {
					int  num5 = separators[j].size();
					if (((chRef[i] == separators[j][0]) && (num5 <= ((int)str.size()- i))))
                    {
                        if(((num5 == 1) || (String::strcmp(chRef, i, separators[j].c_str(), 0, num5) == 0)))
                        {
                            sepList[index] = i;
                            lengthList[index] = num5;
                            index++;
                            i += (num5 - 1);
                            break;
                        }
                    }
                }
            }
        }
		if(sepList[index-1]+lengthList[index-1]==(int)str.size())
		{
			sepList[index]=str.size();
			lengthList[index]=1;
		}
		else
		{
			sepList[index]=str.size();
			lengthList[index]=1;
		}
		int startIndex = 0;
		int * nullIndex = new int[index+1];			//	标识是否为空字符串
		String::memset(nullIndex,0,sizeof(int)*(index+1));
        //拆分字符串位置
		//for(int i=0;i<size;i++)
		//{
		//	if(lengthList[i]!=0)
		//		printf("sepList[%d]=%d\t lengthList[%d]=%d\n",i,sepList[i] ,i,lengthList[i]);
		//}
		int len=index+1;
		int size=0;
		for (int  i = 0; ((i < index+1) && (startIndex <=str.size())); i++)
		{
			if(remove && sepList[i] - startIndex==0)
			{
				nullIndex[i]=1;
			}
			else
			{
				size++;
			}
			startIndex = sepList[i] + lengthList[i];
		}
        //空字符串位置
		//for(int i=0;i<len;i++)
		//{
		//	printf("nullIndex[%d]=%d\t \n",i,nullIndex[i] );
		//}
		//result= Array<string>(size);
        if(count!=0 && size>=count)size=count;
		result.resize(size);
		size=0;
		startIndex=0;
		index=0;
		for (int  i = 0; ((i < len) && (startIndex <= str.size())); i++)
		{
			if(nullIndex[index++]==0 && size<result.size())
			{
				 result[size++]=str.substr(startIndex, (sepList[i] - startIndex));
			}
			startIndex =sepList[i] +lengthList[i];
		}
		//for(int i=0;i<size;i++)
		//	printf("string arr[%d]:%s\n",i,result[i].c_str());
		delete sepList;
		delete lengthList;
		delete nullIndex;
	};
}
