
#include "license.h"

#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
using namespace boost;
namespace fs = boost::filesystem;

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#ifdef HAVE_ALLOCA_H
#include <alloca.h>
#endif
#include "installdir.h"

using namespace License;
using namespace Common;


//3 3 "2016-12-12 12:00:00" 5001001 "a8c00aa0"
int main(int argc, char** argv)
{
	//char cnt[64];
	//char code[128];
	//memset(code, 0, 128);
	//strcpy((char*)cnt, "1234567890abcdefghijklmnopqrstuvwxyz9876");

	//char* password = "hans";
	//	int passLen = strlen(password); 
	//int * asize = new int[passLen];
	//for (int i = 0; i< passLen; i++)
	//{
	//	asize[i] = password[i] % 8;
	//}
	//Encoding::chaosEncode((const char *)cnt, code, 4);
	//cout << code << endl;
	//memset(cnt, 0, 64);
	//Encoding::shiftEncode((const char *)code, cnt, asize, passLen);
	//cout << cnt << endl;

	//memset(code, 0, 128);
	//Decoding::shiftDecode((const char*)cnt, code, asize, passLen);
	//cout << code << endl;
	//memset(cnt, 0, 64);
	//Decoding::chaosDecode(code, cnt, 4);
	//cout << cnt << endl;

	//memset(code, 0, 128);
	//Encoding::matrixEncode((const char*)cnt, (char*)code, "hans");
	//memset(cnt, 0, 64);
	//Decoding::matrixDecode((const char*)code, cnt, "hans");
	//strcpy((char*)cnt, "1234567890abcdefghijklmnopqrstuvwxyz9876");
	struct erydbLicense{
		int pmHostCount;
		int umHostCount;
		DateTime buildTime;
		DateTime expTime;
		int version;
		char hostid[8];
		int hostIndex;
		int hostLen;
		char * hostids;
		erydbLicense() :pmHostCount(0), umHostCount(0), buildTime(0), expTime(0), version(0), hostLen(0), hostids(0), hostIndex(0){};

	};
	if (argc < 5 ){
		cout << "usetag:pmcount umCount expTime version hostids " << endl;
		return -1;
	}
 
	erydbLicense dblicense;
	dblicense.pmHostCount = Convert::ToInt(argv[1]);
	dblicense.umHostCount = Convert::ToInt(argv[2]);
	dblicense.buildTime = DateTime();
	dblicense.expTime = DateTime(DateTime::Parse(argv[3]));
	dblicense.version = Convert::ToInt(argv[4]);
	int dlen = 32;
	if (argc > 5){
		String hostStr = argv[5];
		Array<String> hosts = hostStr.Split(",");
		dblicense.hostLen = hosts.size();
		dblicense.hostids = new char[dblicense.hostLen * 8];
		for (int i = 0; i < dblicense.hostLen; i++){
			const	char * str = hosts.at(i).c_str();
			if (hosts.at(i).length() != 8){
				cout << "Every host ID must be 8 bits " << endl;
				return -1;
			}
			memcpy(dblicense.hostids + i * 8, str,8);
		}
		dlen += dblicense.hostLen * 8;
	}
	cout << "pmHostCount=" << dblicense.pmHostCount << endl;
	cout << "umHostCount=" << dblicense.umHostCount << endl;
	cout << "buildTime=" << dblicense.buildTime << endl;
	cout << "expTime=" << dblicense.expTime << endl;
	cout << "version=" << dblicense.version << endl;
	cout << "hostLen=" << dblicense.hostLen << endl;
	cout << "hostids=" << String(dblicense.hostids, 0, dblicense.hostLen * 8) << endl;
	unsigned char  * dest = new unsigned char[dlen*2];
	memset(dest, 0, dlen);
	memcpy(dest, &dblicense.pmHostCount, 4);
	memcpy(dest + 4, &dblicense.umHostCount, 4);
	unsigned long long time = dblicense.buildTime.GetTicks();
	memcpy(dest + 8, &time, 8);
	time = dblicense.expTime.GetTicks();
	memcpy(dest + 16, &time, 8);
	memcpy(dest + 24, &dblicense.version, 4);
	memcpy(dest + 28, &dblicense.hostLen, 4);
	if (dblicense.hostLen)
	memcpy(dest + 32, dblicense.hostids, dblicense.hostLen * 8);
	//strcpy((char*)dest, "1234567890abcdefghijklmnopqrstuvwxyz9876");
	if (dblicense.hostids)
	{
		delete[] dblicense.hostids;
		dblicense.hostids = NULL;
	}
	for (int i = 0; i < dlen; i++){
		if (i % 16 == 0){
			printf("\n");
		}
		printf("%0x", dest[i]);
	}
	printf("\n");
	char  * base64 = new char[dlen * 2];
	memset(base64, 0, dlen * 2);
	char * baseCode = License::Encoding::base64_encode(dest, base64, dlen);
	int len = strlen(base64);
	memset(dest, 0, dlen);
	Encoding::matrixEncode((const char*)base64, (char*)dest, "hans");
	memset(base64, 0, dlen * 2);
	baseCode = License::Encoding::base64_encode(dest, base64, len);
	cout << baseCode << endl;
	memset(dest, 0, dlen); 
	delete[] dest;
	dest = NULL;
	string   configFile("dblicense.dat");
	FILE * licFile = fopen(configFile.c_str(), "wb");
	if (!licFile){
		ostringstream oss;
		oss << "error open dblicense file  " <<
			configFile << ": " << strerror(errno);
		cerr << oss.str() << endl;
		return 1;
	}
	fwrite(baseCode, 1, strlen(baseCode), licFile);
	fclose(licFile);
	delete[] base64;
	base64 = NULL;
	License::erydbLicense * lic = License::getLicense(configFile.c_str());
	if (lic){
		cout << License::toStringInfo(lic) << endl;
	}
}

