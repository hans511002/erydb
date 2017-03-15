#! /bin/sh
#
#/*******************************************************************************
#*  Script Name:    tarfiles.sh
#*  Date Created:   2009.04.17
#*  Author:         erydb Corp.
#*  Purpose:        tar the data collection files
#*
#*  Parameters:     hostdir
#*                  tarfile
#*                  
#******************************************************************************/
#
hostdir=$1
tarfile=$2
#
# tar the files
cd /usr/local/erydb/tools/data
tar -cf $tarfile $hostdir
#
# End of Script
