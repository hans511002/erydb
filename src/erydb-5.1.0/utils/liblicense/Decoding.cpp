// ==============================================================
//progame      Common::Decoding  
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
#include "license.h"
#include "Decoding.h"
#include "Encoding.h"

namespace  License
{
	//矩阵解密
	//先移位，再还原位置
	void Decoding::matrixDecode(const char * src,char * dest,const char * password)
	{
		int srcLen=strlen(src);
		int passLen=strlen(password);
		int * asize=new int[passLen+1];
		char * p=new char[srcLen+1];
		memset(p,0,srcLen+1);
		for(int i=0;i< passLen;i++)
		{
			asize[i]=password[i] % 8;
		}
		shiftDecode(src,p,asize,passLen);
		memset(dest, 0, srcLen + 1);
		chaosDecode(p,dest,passLen);
		delete [] asize;
		delete [] p;
	}
	//镜像解密(补反)
	void Decoding::MSLDecode(const char * src,char * dest)
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
	//倒置解密
	void Decoding::anasDecode(const char * src,char * dest)
	{
		int srcLen=strlen(src);
		char * tp=(char *)src+srcLen-1;
		while(srcLen--)
		{
			*dest=*tp;
			dest++;tp--;
		}
	}
	//移位解密(按字节循环反向移位)
	void Decoding::shiftDecode(const char * src,char * dest,int size)
	{
		size=size%8;
		if(size==0){strcpy(dest,src);return;}
		unsigned char * tp=(unsigned char *)src;
		unsigned char c,tc;
		size=size%8;
		while(*tp)
		{
			c=*tp;
			tc=c<<size;
			*dest=(tc>>(8-size)) | tc;
			dest++;tp++;
		}
	}
	//多移位加密
	void Decoding::shiftDecode(const char * src,char * dest,int * asize,int len)
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
					tc=c<<asize[i];
					*dest=(c>>(8-asize[i])) | tc;
				}
				else
				{
					*dest=c;
				}
				tp++;dest++;
			}
		}
	}
	void Decoding::chaosDecode(const char * src,char * dest,int len)
	{
		int srcLen=strlen(src);
		for(int i=0;i<len;i++)
		{
			int pos=i;
			while(pos<srcLen)
			{
				dest[pos]=*src;
				pos+=len;
				src++;
			}
		}
	}

	int Decoding::base64_decode(const char * base64, unsigned char * bindata)
	{
		int i, j;
		unsigned char k;
		unsigned char temp[4];
		for (i = 0, j = 0; base64[i] != '\0'; i += 4)
		{
			memset(temp, 0xFF, sizeof(temp));
			for (k = 0; k < 64; k++)
			{
				if (base64char[k] == base64[i])
					temp[0] = k;
			}
			for (k = 0; k < 64; k++)
			{
				if (base64char[k] == base64[i + 1])
					temp[1] = k;
			}
			for (k = 0; k < 64; k++)
			{
				if (base64char[k] == base64[i + 2])
					temp[2] = k;
			}
			for (k = 0; k < 64; k++)
			{
				if (base64char[k] == base64[i + 3])
					temp[3] = k;
			}

			bindata[j++] = ((unsigned char)(((unsigned char)(temp[0] << 2)) & 0xFC)) |
				((unsigned char)((unsigned char)(temp[1] >> 4) & 0x03));
			if (base64[i + 2] == '=')
				break;

			bindata[j++] = ((unsigned char)(((unsigned char)(temp[1] << 4)) & 0xF0)) |
				((unsigned char)((unsigned char)(temp[2] >> 2) & 0x0F));
			if (base64[i + 3] == '=')
				break;

			bindata[j++] = ((unsigned char)(((unsigned char)(temp[2] << 6)) & 0xF0)) |
				((unsigned char)(temp[3] & 0x3F));
		}
		return j;
	}
	void Decoding::base64_decode(FILE * fp_in, FILE * fp_out)
	{
		int i;
		unsigned char bindata[2050];
		char base64[4096];
		size_t bytes;
		while (!feof(fp_in))
		{
			for (i = 0; i < 2048; i++)
			{
				base64[i] = fgetc(fp_in);
				if (base64[i] == EOF)
					break;
				else if (base64[i] == '\n' || base64[i] == '\r')
					i--;
			}
			bytes = base64_decode(base64, bindata);
			fwrite(bindata, bytes, 1, fp_out);
		}
	}

}

