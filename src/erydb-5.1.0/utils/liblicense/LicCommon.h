#ifndef __Common_H__
#define __Common_H__
#include <string>
#include <sstream>
#include <exception>
#include <iostream>
#include <unistd.h> 
using namespace std;

#if defined(_MSC_VER) && defined(LIBCONFIG_DLLEXPORT)
#define EXPORT declspec(dllexport)
#else
#define EXPORT
#endif
 

#ifdef _MSC_VER 
#define STDSPACE std
#else
#define STDSPACE 

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdarg.h>
#include <time.h>
#include "math.h"
#include <list>
#include <vector>
#include <map>
#include <set>
#include <limits.h>
#include <fcntl.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stack> 
#include <cctype>   // isdigit()
#include <numeric>
#include <iomanip>
#include <fstream>
#include <string.h>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/timeb.h>
# include <unistd.h>
//# include <semaphore.h>
//# include <sys/sem.h>
//# include <sys/mman.h>
//# include <sys/shm.h>
//# include <sys/user.h>
//# include <netinet/in.h>
//# include <arpa/inet.h>
//# include <dirent.h> 
//# include <sys/dir.h>
//# include <sys/types.h>
//# include <sys/stat.h>
//# include <sys/socket.h>
//# include <sys/file.h>
//# include <sys/io.h>
//# include <sys/wait.h>
//# include <sys/ioctl.h>
//# include <net/if.h>
//# include <net/if_arp.h>
//# include <termio.h>
//# include <netdb.h>
//# include <utime.h>
//# include <sys/io.h>
# include <iconv.h>
# include <sys/time.h>
//# include <sys/select.h>
#endif

namespace Common
{
	class String;
	class DateTime;
	class TimeSpan;
	class Convert;
}
#include "NormalException.h" 

#endif