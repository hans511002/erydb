// ==============================================================
//progame      Common::Encoding  
//company      hans
//copyright    Copyright (c) hans  2007-4     2008-06
//version      1.0
//Author       hans
//date         2007-4     2008-06
//description  Common namespace
//				This library is free software. Permission to use, copy,
//				modify and redistribute it for any purpose is hereby granted
//				without fee, provided that the above copyright notice appear
//				in all copies.
// ==============================================================

#include "Encoding.h"
#include "license.h"

namespace License
{
	   char   *  base64char = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	//矩阵加密
	//先打乱，再移位
	void Encoding::matrixEncode(const char * src,char * dest,const char * password)
	{
		int srcLen=strlen(src);
		int passLen=strlen(password);
		int * asize=new int[passLen];
		char * p=new char[srcLen+1];
		memset(p,0,srcLen+1);
		for(int i=0;i< passLen;i++)
		{
			asize[i]=password[i] % 8;
		}
		chaosEncode(src,p,passLen);
		memset(dest, 0, srcLen + 1);
		shiftEncode(p,dest,asize,passLen);
		delete [] asize;
		delete [] p;
	}
	//镜像加密(补反)
	void Encoding::MSLEncode(const char * src,char * dest)
	{
		unsigned char * tp=(unsigned char *)src;
		unsigned char c=*tp;
		while(c)
		{
			if(c>128)
				*dest=c & 0x7F;
			else if(c<128)
				*dest=c | 0x80;
			tp++;dest++;
			c=*tp;
		}
	}
	//倒置加密
	void Encoding::anasEncode(const char * src,char * dest)
	{
		int srcLen=strlen(src);
		char * tp=(char *)src+srcLen-1;
		while(srcLen--)
		{
			*dest=*tp;
			dest++;tp--;
		}
	}
	//移位加密(按字节循环移位)
	void Encoding::shiftEncode(const char * src,char * dest,int size)
	{
		size=size%8;
		if(size==0){strcpy(dest,src);return;}
		unsigned char * tp=(unsigned char *)src;
		unsigned char c,tc;
		while(*tp)
		{
			c=*tp;
			tc=c>>size;
			*dest=(c<<(8-size)) | tc;
			tp++;dest++;
		}
	}
	//多移位加密
	void Encoding::shiftEncode(const char * src,char * dest,int * asize,int len)
	{
		unsigned char * tp=(unsigned char *)src;
		unsigned char c,tc;
		int size=0;
		while(*tp)
		{
			for(int i=0;i<len && *tp;i++)
			{
				c=*tp;
				if(asize[i]!=0)
				{
					tc=c>>asize[i];
					*dest=(c<<(8-asize[i])) | tc;
				}
				else
				{
					*dest=c;
				}
				tp++;dest++;
			}
		}
	}
	void Encoding::chaosEncode(const char * src,char * dest,int len)
	{
		int srcLen=strlen(src);
		for(int i=0;i<len;i++)
		{
			int pos=i;
			while(pos<srcLen)
			{
				*dest=src[pos];
				dest++;
				pos+=len;
			}
		}
	}
	char * Encoding::base64_encode(const unsigned char * bindata, char * base64, int binlength)
	{
		int i, j;
		unsigned char current;
		for (i = 0, j = 0; i < binlength; i += 3)
		{
			current = (bindata[i] >> 2);
			current &= (unsigned char)0x3F;
			base64[j++] = base64char[(int)current];
			current = ((unsigned char)(bindata[i] << 4)) & ((unsigned char)0x30);
			if (i + 1 >= binlength)
			{
				base64[j++] = base64char[(int)current];
				base64[j++] = '=';
				base64[j++] = '=';
				break;
			}
			current |= ((unsigned char)(bindata[i + 1] >> 4)) & ((unsigned char)0x0F);
			base64[j++] = base64char[(int)current];
			current = ((unsigned char)(bindata[i + 1] << 2)) & ((unsigned char)0x3C);
			if (i + 2 >= binlength)
			{
				base64[j++] = base64char[(int)current];
				base64[j++] = '=';
				break;
			}
			current |= ((unsigned char)(bindata[i + 2] >> 6)) & ((unsigned char)0x03);
			base64[j++] = base64char[(int)current];

			current = ((unsigned char)bindata[i + 2]) & ((unsigned char)0x3F);
			base64[j++] = base64char[(int)current];
		}
		base64[j] = '\0';
		return base64;
	}
	void Encoding::base64_encode(FILE * fp_in, FILE * fp_out)
	{
		unsigned char bindata[2050];
		char base64[4096];
		size_t bytes;
		while (!feof(fp_in))
		{
			bytes = fread(bindata, 1, 2049, fp_in);
			base64_encode(bindata, base64, bytes);
			fprintf(fp_out, "%s", base64);
		}
	}
}
