#ifndef LICENSE_H
#define LICENSE_H
#include "LicCommon.h"
#include "Array.h"
#include "Enums.h"
#include "Convert.h"  
#include "Functions.h"
#include "DateTimeFun.h"
#include "TimeSpan.h"
#include "DateTime.h"
#include "Decoding.h"
#include "Encoding.h"


namespace License
{
	using namespace Common;
	struct erydbLicense;
	extern unsigned long long checkLicTimes;
	extern DateTime zeroTime;
	extern erydbLicense * dblicense;
	extern string getHostId();
	extern bool checkLicense(string & msg);
	extern bool checkLicense(string & msg,string &warn);
	extern erydbLicense *  getLicense(const char * file=NULL);
	extern int getPmCountLimit();
	extern int getUmCountLimit();
	extern DateTime & getExpTime();
	extern DateTime & getExpTime();
	extern char * getHostIds();
	extern string toString(erydbLicense *lic=NULL);
	extern string toStringInfo(erydbLicense *lic = NULL);


}

#endif // LICENSE_H
 