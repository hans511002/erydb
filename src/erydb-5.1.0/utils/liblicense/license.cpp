
#include "license.h"

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
#include "boost/tokenizer.hpp"
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include "boost/filesystem/operations.hpp"
using namespace boost;
namespace fs = boost::filesystem;

#include "installdir.h"

namespace License
{
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

	using namespace Common;
	erydbLicense * dblicense = NULL;
	DateTime zeroTime(0);
	unsigned	long long checkLicTimes = 0;
	bool checkLicense(string & msg, string &warn){
		if (checkLicense(msg)){
			if (!dblicense->hostLen){
				warn ="This is a trial license,if host lage than three, valid for three months";
			}
			DateTime now;
			if ((dblicense->expTime-now).getDays()<10){
				warn = string("Your license will soon be available. : ") + dblicense->expTime.ToStaDateString();
			}
			return true;
		}
		return false;
	}
	bool checkLicense(string & msg){
		erydbLicense * lic = getLicense();
		if (!lic){
			msg = "Not read to valid license";
			return false;
		}
		DateTime now;
		if (now > lic->expTime){
			msg = "The license has expired";
			dblicense = NULL;
			return false;
		}
		//not accset version
		if (lic->hostLen){
			if (lic->hostIndex){
				return true;
			}
			else{
				msg = "The license is not this machine's.";
				dblicense = NULL;
				return false;
			}
		}
		else
		{
			if (lic->pmHostCount> 3 &&  now > lic->buildTime && ((now-lic->buildTime).getDays()>90)){
				msg = "Trial license has expired";
				dblicense = NULL;
				return false;
			}
			else if (now < lic->buildTime)
			{
				msg = "Bad Trial license ";
				dblicense = NULL;
				return false;
			}
		}
		return true;
	}
	erydbLicense * getLicense(const char * _file){
		if (dblicense != NULL){
			return dblicense;
		}
		char * file="dblicense.dat";
		std::string configFile;
		if (_file){
			configFile = _file;
		}else{
			string installDir;
	#if !defined(_MSC_VER) 
			installDir = startup::StartUp::installDir();
	#endif
			fs::path configFilePath = fs::path(installDir) / fs::path("etc") / fs::path(file);
			configFile = configFilePath.string();
		}
		for (int i = 0; i < 20; i++)
		{
			if (access(configFile.c_str(), R_OK) != 0) {
				if (i >= 15)
				{
					ostringstream oss;
					oss << "error accessing dblicense file  " <<
						configFile << ": " << strerror(errno);
					cerr << oss.str() << endl;
					return NULL;
				}
				sleep(1);   
			}
			else
				break;
		}
		FILE * licFile = fopen(configFile.c_str(), "rb");
		if (!licFile){
			ostringstream oss;
			oss << "error open dblicense file  " <<
				configFile << ": " << strerror(errno);
			cerr << oss.str() << endl;
			return NULL;
		}
		char base64[8192];
		memset(base64, 0, 8192);
		size_t blen = fread(base64, 1, 8192, licFile);

		fclose(licFile);
		if (blen <= 0){
			ostringstream oss;
			oss << "error read dblicense file  " <<
				configFile << ": " << strerror(errno);
			cerr << oss.str() << endl;
			return NULL;
		}
		unsigned char dest[8192];
		memset(dest, 0, 8192);
		int len = Decoding::base64_decode(base64, dest);
		memset(base64, 0, 8192);
		Decoding::matrixDecode((const char*)dest, base64, "hans");
		memset(dest, 0, 8192);
		len = Decoding::base64_decode(base64, dest);
		//for (int i = 0; i < len; i++){
		//	printf("%0x", dest[i]);
		//	if (i % 16 == 15){
		//		printf("\n");
		//	}
		//}
		//printf("\n");
		if (len >= 32){
			dblicense = new erydbLicense();
			dblicense->pmHostCount = Convert::toInt(dest);
			dblicense->umHostCount = Convert::toInt(dest + 4);
			dblicense->buildTime = DateTime(Convert::toLong(dest + 8));
			dblicense->expTime = DateTime(Convert::toLong(dest + 16));
			dblicense->version = Convert::toInt(dest + 24);
			dblicense->hostLen = Convert::toInt(dest + 28);
			//cout << "pmHostCount=" << dblicense->pmHostCount << endl;
			//cout << "umHostCount=" << dblicense->umHostCount << endl;
			//cout << "buildTime=" << dblicense->buildTime << endl;
			//cout << "expTime=" << dblicense->expTime << endl;
			//cout << "version=" << dblicense->version << endl;
			//cout << "hostLen=" << dblicense->hostLen << endl;

			String hostid((char *)(dest + 32));
			int hsl = len - 32;// strlen((char *)dest + 32);
			if (hsl && dblicense->hostLen){
				if (hsl != dblicense->hostLen * 8){
					ostringstream oss; oss << "error check dblicense ,bad license data  ";
					cerr << oss.str() << endl;
					delete dblicense;
					return NULL;
				}
				dblicense->hostids=new char[hsl];
				strcpy(dblicense->hostids, (char *)dest + 32); 
				memset(dblicense->hostid, 0, 8);
				
				string  shid= getHostId();
				//res = sethostid(0x837b1d2c);
				memcpy(dblicense->hostid, shid.c_str(), 8);
				char * p=dblicense->hostids;
				for (int i = 0; i < dblicense->hostLen;i++){
					if (strncmp(dblicense->hostids + (i * 8), dblicense->hostid, 8) == 0){
						dblicense->hostIndex= i+1;
						return dblicense;
					}
				}
				ostringstream oss; oss << "error check dblicense ,not this host license ";
				cerr << oss.str() << endl;
				delete dblicense;
				return NULL;
			}
			
		}
		return dblicense;
	};
	string getHostId(){
		long int id = 0;
#ifndef _MSC_VER
		id= gethostid();
#endif
		char hid [8];
		//printf("current hostid is: %x\n", id);
		sprintf(hid, "%x", id);
		string shid(hid);
		return shid;
	}
	int getPmCountLimit(){
		if (dblicense){
			return dblicense->pmHostCount;
		}
		return 0;
	}
		  ;
	 int getUmCountLimit(){
		if (dblicense){
			return dblicense->umHostCount;
		}
		return 0;
	}
	 DateTime & getExpTime(){
		 if (dblicense){
			 return dblicense->expTime;
		 }
		 return zeroTime;
	 }
	 DateTime &  getBuildTime(){
		 if (dblicense){
			 return dblicense->buildTime;
		 }
		 return  zeroTime;
	 }
	 char * getHostIds(){
		 if (dblicense){
			 return dblicense->hostids;
		 }
		 return NULL;
	 }
	 string toString(erydbLicense *lic){
		 if (!lic){
			 lic = dblicense;
		 }
		 if (lic){
			 String str = "PM:";
			 str  += String(lic->pmHostCount);
			 str += "\nUM:" + String(lic->umHostCount);
			 str += String("\nbuildTime:" )+ lic->buildTime.ToString();
			 str += String("\nexpTime:" )+ lic->expTime.ToString();
			 return str;
		 }
		 else{
			 return "";
		 }
	 }
	 string toStringInfo(erydbLicense *lic){
		 if (!lic){
			 lic = dblicense;
		 }
		 if (lic){
			 String str = "PM:";
			 str += String(lic->pmHostCount);
			 str += "\nUM:" + String(lic->umHostCount);
			 str += String("\nbuildTime:") + lic->buildTime.ToString();
			 str += String("\nexpTime:") + lic->expTime.ToString();
			 str += String("\nhostLen:") + lic->hostLen;
			 str += String("\nhostids:");
			 for (int i = 0; i< lic->hostLen; i++){
				 str += String(lic->hostids, i * 8, 8);
			 }
			 return str;
		 }
		 else{
			 return "";
		 }
	 }
}
