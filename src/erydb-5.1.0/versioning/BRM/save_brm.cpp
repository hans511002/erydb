/* Copyright (C) 2014 EryDB, Inc.

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; version 2 of
   the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA. */

/*****************************************************************************
 * $Id: save_brm.cpp 1910 2013-06-18 15:19:15Z rdempsey $
 *
 ****************************************************************************/

/*
 * Saves the current state of the BRM data structures.
 *
 * More detailed description
 */

#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;

#include "brmtypes.h"
#include "rwlock.h"
#include "mastersegmenttable.h"
#include "extentmap.h"
#include "copylocks.h"
#include "vss.h"
#include "vbbm.h"
#include "blockresolutionmanager.h"
#include "ERYDBDataFile.h"
#include "ERYDBPolicy.h"
using namespace erydbdatafile;
using namespace BRM;

#include "configcpp.h"

int main (int argc, char **argv)
{
	BlockResolutionManager brm;
	config::Config *config = config::Config::makeConfig();
	int err;
	string prefix, currentFilename;
	ERYDBDataFile* currentFile = NULL;

	if (argc > 1)
		prefix = argv[1];
	else {
		prefix = config->getConfig("SystemConfig", "DBRMRoot");
		if (prefix.length() == 0) {
			cerr << "Error: Need a valid erydb configuation file" << endl;
			exit(1);
		}
	}

	erydbdatafile::ERYDBPolicy::configERYDBPolicy();

	err = brm.saveState(prefix);
	if (err == 0)
		cout << "Saved to " << prefix << endl;
	else {
		cout << "Save failed" << endl;
		exit(1);
	}

	(void)::umask(0);

	currentFilename = prefix + "_current";
	currentFile = ERYDBDataFile::open(ERYDBPolicy::getType(currentFilename.c_str(),
									ERYDBPolicy::WRITEENG),
									currentFilename.c_str(),
									"wb",
									0);

	if (!currentFile) {
		cerr << "Error: could not open " << currentFilename << "for writing" << endl;
		exit(1);
	}
	try {
#ifndef _MSC_VER
		prefix += '\n';
#endif
		currentFile->write(prefix.c_str(), prefix.length());
	}
	catch (exception &e) {
		cerr << "Error: failed to write to " << currentFilename << ": " << e.what() << endl;
		exit(1);
	}
	try {
		delete currentFile;
		currentFile = NULL;
	}
	catch (exception &e) {
		cerr << "Error: failed to close " << currentFilename << ": " << e.what() << endl;
		exit(1);
	}

	return 0;
}
