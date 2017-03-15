// ==============================================================
//progame      Common:hashMath functions 
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

#ifndef __Common_hashMath_H__  
#define __Common_hashMath_H__
#include "LicCommon.h"

namespace Common
{
	class hashMath
	{
		//static char p[40];
	public :
		//2.1 PHP中出现的字符串Hash函数 0%
		inline static unsigned int hashpjw(const char *key, unsigned int nKeyLength) 
		{ 
			char *arKey=(char *)key;
			unsigned int h = 0, g; 
			//char *arEnd=arKey+nKeyLength; 
			while (*arKey) 
			{
				h = (h << 4) + *arKey++; 
				if ((g = (h & 0xF0000000))) 
				{ 
					h = h ^ (g >> 24); 
					h = h ^ g; 
				}
			}
			return h;
		} 
		//2.2 OpenSSL中出现的字符串Hash函数  OpenSSL_Hash1: 重复度太高
		inline static unsigned int lh_strhash(const char *str,unsigned int l) 
		{ 
			int i; 
			unsigned int ret=0; 
			unsigned short *s; 
			if (str == NULL) return(0); 
			l=(l+1)/2; 
			s=(unsigned short *)str; 
			for (i=0; i<l;i++)
				ret^=(s[i]<<(i&0x0f)); 
			return(ret); 
		}

		//OpenSSL_Hash2:
		inline static unsigned int lh_strhash2(const char *c,unsigned int l) 
		{ 
			unsigned int ret=0; 
			long n; 
			unsigned int v; 
			int r;
			if ((c == NULL) || (*c == '\0')) 
				return(ret); 
			/* 
			unsigned char b[16]; 
			MD5(c,strlen(c),b); 
			return(b[0]|(b[1]<<8)|(b[2]<<16)|(b[3]<<24)); 
			*/ 
			n=0x100;
			while (*c)
			{
				v=n|(*c); 
				n+=0x100;
				r= (int)((v>>2)^v)&0x0f;
				ret=(ret<<(32-r));
				ret&=0xFFFFFFFFL;
				ret^=v*v;
				c++;
			}
			return((ret>>16)^ret); 
		} 

		//2.3 MySql中出现的字符串Hash函数  1%
		inline static unsigned int calc_hashnr(const char *key, unsigned int len) 
		{ 
			const char *end=key+len; 
			unsigned long hash; 
			for (hash = 0; key < end; key++) 
			{ 
				hash *= 16777619; 
				hash ^= (unsigned int) *(unsigned char*) key; 
			} 
			return (hash); 
		}
		inline static unsigned int calc_hashnr_caseup(const char *key, unsigned int len) 
		{ 
			const char *end=key+len; 
			unsigned int hash; 
			for (hash = 0; key < end; key++) 
			{ 
				hash *= 16777619; 
				hash ^= (unsigned int) (unsigned char) toupper(*key); 
			} 
			return (hash); 
		} 
// Calc hashvalue for a key                                     			//3%
		inline static unsigned int calc_hashnr2(const char *key,unsigned int length) 
		{ 
			register unsigned int nr=1, nr2=4; 
			while (length--) 
			{ 
				nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) *key++))+ (nr << 8); 
				nr2+=3; 
			} 
			return((unsigned int) nr); 
		} 
// Calc hashvalue for a key, case indepenently                                      
		inline static  unsigned int calc_hashnr_caseup2(const char *key, unsigned int length) 
		{ 
			register unsigned int nr=1, nr2=4; 
			while (length--) 
			{ 
				nr^= (((nr & 63)+nr2)*((unsigned int) (unsigned char) toupper(*key++)))+ (nr << 8); 
				nr2+=3; 
			} 
			return((unsigned int) nr); 
		} 


	//2.4 另一个经典字符串Hash函数 0%
		inline static unsigned int hashsp(const char *str, int l) 
		{ 
			register unsigned int h; 
			register unsigned char *p=(unsigned char *)str;
			for (h = 0; --l >= 0; h = h*31 + *p++);
			return h;
		} 
		inline static unsigned int hashsp2(const char* ptr, int size)
		{
			register unsigned h;
			register unsigned char * key = (unsigned char *)ptr;
			for (h = 0; --size >= 0; h = h*29 + *key++);
			return h;
		};
		inline static unsigned int hashsp(const char* ptr, int size,int mark,bool ignoreCase=false )
		{
			register unsigned h;
			register unsigned char * key = (unsigned char *)ptr;
			
			if(ignoreCase)
				for (h = 0; --size >= 0; h = h*mark + toupper(*key++));
			else
				for (h = 0; --size >= 0; h = h*mark + *key++);
			return h;
		};
		//Blizzard hash  seed1 = cryptTable[(dwHashType << 8) + ch] ^ (seed1 + seed2);
		inline static unsigned int Hashbl_caseup(const char * str, unsigned int dwHashType=0)
		{ 
			unsigned char *key = (unsigned char *)str;
			unsigned int seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
			int ch;
			while(*key != 0)
			{ 
				ch = toupper(*key++);
				seed1 = ((dwHashType << 8) + ch) ^ (seed1 + seed2);
				seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; 
			}
			return seed1;
		};
		//%90
		inline static unsigned int Hashbl(const char * str, unsigned int dwHashType=0)
		{ 
			unsigned char *key = (unsigned char *)str;
			unsigned int seed1 = 0x7FED7FED, seed2 = 0xEEEEEEEE;
			int ch;
			while(*key != 0)
			{ 
				ch = *key++;
				seed1 = ((dwHashType << 8) + ch) ^ (seed1 + seed2);
				seed2 = ch + seed1 + seed2 + (seed2 << 5) + 3; 
			}
			return seed1;
		};

		//char *
		inline static unsigned int calc_hashnr(const char * key)		{return calc_hashnr(key,strlen(key));};
		inline static unsigned int hashpjw(const char * key)			{return hashpjw(key,strlen(key));};
		inline static unsigned int hashsp(const char * key)				{return hashsp(key,strlen(key));};
		inline static unsigned int hashsp2(const char * key)			{return hashsp2(key,strlen(key));};
		inline static unsigned int calc_hashnr_caseup(const char * key)	{return calc_hashnr_caseup(key,strlen(key));};
		inline static unsigned int calc_hashnr2(const char * key)		{return calc_hashnr2(key,strlen(key));};
		inline static unsigned int calc_hashnr_caseup2(const char * key){return calc_hashnr_caseup2(key,strlen(key));};
		//string
		inline static unsigned int hashpjw(const string &key)			{return hashpjw(key.c_str(),key.size());};
		inline static unsigned int lh_strhash(const string &key)		{return lh_strhash(key.c_str(),key.size());};
		inline static unsigned int lh_strhash2(const string &key)		{return lh_strhash2(key.c_str(),key.size());};
		inline static unsigned int calc_hashnr(const string &key)		{return calc_hashnr(key.c_str(),key.size());};
		inline static unsigned int calc_hashnr_caseup(const string &key){return calc_hashnr_caseup(key.c_str(),key.size());};
		inline static unsigned int calc_hashnr2(const string &key)		{return calc_hashnr2(key.c_str(),key.size());};
		inline static unsigned int calc_hashnr_caseup2(const string &key){return calc_hashnr_caseup2(key.c_str(),key.size());};
		inline static unsigned int hashsp(const string &key)			{return hashsp(key.c_str(),key.size());};
		inline static unsigned int hashsp2(const string &key)			{return hashsp2(key.c_str(),key.size());};
		
		inline static unsigned int Hashbl(const string &key, unsigned int dwHashType=0){return Hashbl(key.c_str(),dwHashType);};

#define FORMAT_INT char p[40];int len=sprintf(p,"%d",key);
#define FORMAT_LONG char p[40];int len=sprintf(p,"%ld",key);
#define FORMAT_LLONG char p[40];int len=sprintf(p,"%lld",key);
		//int
		inline static unsigned int hashpjw(const int &key){FORMAT_INT return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const int &key){FORMAT_INT return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const int &key){FORMAT_INT return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const int &key){FORMAT_INT return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const int &key){FORMAT_INT return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const int &key){FORMAT_INT return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const int &key){FORMAT_INT return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const int &key){FORMAT_INT return hashsp(p,len);};
		inline static unsigned int hashsp2(const int & key){if(!key)return hashsp(key);return key;}
		inline static unsigned int Hashbl(const int &key, unsigned int dwHashType=0){FORMAT_INT return Hashbl(p,dwHashType);};
		//long
		inline static unsigned int hashpjw(const long &key){FORMAT_LONG return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const long &key){FORMAT_LONG return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const long &key){FORMAT_LONG return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const long &key){FORMAT_LONG return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const long &key){FORMAT_LONG return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const long &key){FORMAT_LONG return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const long &key){FORMAT_LONG return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const long &key){FORMAT_LONG return hashsp(p,len);};
		inline static unsigned int hashsp2(const long & key){if(!key)return hashsp(key);return key & 0xFFFFFFFF;}
		inline static unsigned int Hashbl(const long &key, unsigned int dwHashType=0){FORMAT_LONG return Hashbl(p,dwHashType);};
		//long long
		inline static unsigned int hashpjw(const long long &key){FORMAT_LLONG return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const long long &key){FORMAT_LLONG return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const long long &key){FORMAT_LLONG return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const long long &key){FORMAT_LLONG return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const long long &key){FORMAT_LLONG return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const long long &key){FORMAT_LLONG return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const long long &key){FORMAT_LLONG return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const long long &key){FORMAT_LLONG return hashsp(p,len);};
		inline static unsigned int hashsp2(const long long &key){FORMAT_LLONG return hashsp2(p,len);};
		inline static unsigned int Hashbl(const long long &key, unsigned int dwHashType=0){FORMAT_LLONG return Hashbl(p,dwHashType);};
#undef FORMAT_LONG
#undef FORMAT_LLONG
#undef FORMAT_INT
#define FORMAT_INT char p[40];int len=sprintf(p,"%u",key);
#define FORMAT_LONG char p[40];int len=sprintf(p,"%lu",key);
#define FORMAT_LLONG char p[40];int len=sprintf(p,"%llu",key);
		//unsigned int
		inline static unsigned int hashpjw(const unsigned int &key){FORMAT_INT return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const unsigned int &key){FORMAT_INT return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const unsigned int &key){FORMAT_INT return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const unsigned int &key){FORMAT_INT return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const unsigned int &key){FORMAT_INT return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const unsigned int &key){FORMAT_INT return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const unsigned int &key){FORMAT_INT return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const unsigned int &key){FORMAT_INT return hashsp(p,len);};
		inline static unsigned int hashsp2(const unsigned int & key){if(!key)return hashsp(key);return key;}
		inline static unsigned int Hashbl(const unsigned int &key, unsigned int dwHashType=0){FORMAT_INT return Hashbl(p,dwHashType);};
		//unsigned long
		inline static unsigned int hashpjw(const unsigned long &key){FORMAT_LONG return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const unsigned long &key){FORMAT_LONG return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const unsigned long &key){FORMAT_LONG return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const unsigned long &key){FORMAT_LONG return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const unsigned long &key){FORMAT_LONG return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const unsigned long &key){FORMAT_LONG return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const unsigned long &key){FORMAT_LONG return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const unsigned long &key){FORMAT_LONG return hashsp(p,len);};
		inline static unsigned int hashsp2(const unsigned long & key){if(!key)return hashsp(key);return key & 0xFFFFFFFF;}
		inline static unsigned int Hashbl(const unsigned long &key, unsigned int dwHashType=0){FORMAT_LONG return Hashbl(p,dwHashType);};
		//unsigned long long
		inline static unsigned int hashpjw(const unsigned long long &key){FORMAT_LLONG return hashpjw(p,len);};
		inline static unsigned int lh_strhash(const unsigned long long &key){FORMAT_LLONG return lh_strhash(p,len);};
		inline static unsigned int lh_strhash2(const unsigned long long &key){FORMAT_LLONG return lh_strhash2(p,len);};
		inline static unsigned int calc_hashnr(const unsigned long long &key){FORMAT_LLONG return calc_hashnr(p,len);};
		inline static unsigned int calc_hashnr_caseup(const unsigned long long &key){FORMAT_LLONG return calc_hashnr_caseup(p,len);};
		inline static unsigned int calc_hashnr2(const unsigned long long &key){FORMAT_LLONG return calc_hashnr2(p,len);};
		inline static unsigned int calc_hashnr_caseup2(const unsigned long long &key){FORMAT_LLONG return calc_hashnr_caseup2(p,len);};
		inline static unsigned int hashsp(const unsigned long long &key){FORMAT_LLONG return hashsp(p,len);};
		inline static unsigned int hashsp2(const unsigned long long & key){if(!key)return hashsp(key);return key & 0xFFFFFFFF;}
		inline static unsigned int Hashbl(const unsigned long long &key, unsigned int dwHashType=0){FORMAT_LLONG return Hashbl(p,dwHashType);};
#undef FORMAT_LONG
#undef FORMAT_LLONG
#undef FORMAT_INT
		//int GetHashTablePos(char *lpszString, SOMESTRUCTURE *lpTable, int nTableSize)
		//{ 
		//	long nHash = HashString(lpszString), nHashPos = nHash % nTableSize;
		//	if (lpTable[nHashPos].bExists && !strcmp(lpTable[nHashPos].pString, lpszString)) 
		//		return nHashPos; 
		//	else 
		//		return -1; //Error value 
		//};
		//int GetHashTablePos(char *lpszString, MPQHASHTABLE *lpTable, int nTableSize)
		//{ 
		//	const int HASH_OFFSET = 0, HASH_A = 1, HASH_B = 2;
		//	int nHash = HashString(lpszString, HASH_OFFSET);
		//	int nHashA = HashString(lpszString, HASH_A);
		//	int nHashB = HashString(lpszString, HASH_B);
		//	int nHashStart = nHash % nTableSize, nHashPos = nHashStart;
		//	while (lpTable[nHashPos].bExists)
		//	{ 
		//		if (lpTable[nHashPos].nHashA == nHashA && lpTable[nHashPos].nHashB == nHashB) 
		//			return nHashPos; 
		//		else 
		//			nHashPos = (nHashPos + 1) % nTableSize;
		//		if (nHashPos == nHashStart) 
		//			break; 
		//	}
		//	return -1; //Error value 
		//};


	};
	
}
#endif
