#! /usr/bin/perl -w
#
# $Id: genMsgId.pl 3048 2012-04-04 15:33:45Z rdempsey $
#

open FH, "< ./MessageFile.txt" or die;

$frontmatter = <<'EOD';
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
/******************************************************************************************
* $Id: genMsgId.pl 3048 2012-04-04 15:33:45Z rdempsey $
*
******************************************************************************************/
/**
 * @file
 */
#ifndef LOGGING_MESSAGEIDS_H
#define LOGGING_MESSAGEIDS_H

namespace logging {

EOD

$backmatter = <<'EOD';

}//namespace logging

#endif //LOGGING_MESSAGEIDS_H

EOD

print $frontmatter;

while (<FH>)
{
	chomp;
	next if (/^$/);
	next if (/^#/);
	($msgid, undef) = split;
	printf "const unsigned M%04d = %d;\n", $msgid, $msgid;
}

print $backmatter;

close FH;

