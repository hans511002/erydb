
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

int main(int argc, char** argv)
{ 
	char * file = NULL;
	if (argc > 1)file = argv[1];
	erydbLicense * lic = getLicense(file);
	if (lic){
		cout << License::toString(lic)<<endl;
	}
}
