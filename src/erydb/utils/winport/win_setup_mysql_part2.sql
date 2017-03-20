INSTALL PLUGIN erydb SONAME 'liberymysql.dll';
CREATE FUNCTION calgetstats RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calsettrace RETURNS INTEGER SONAME 'liberymysql.dll';
CREATE FUNCTION calsetparms RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calflushcache RETURNS INTEGER SONAME 'liberymysql.dll';
CREATE FUNCTION calgettrace RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calgetversion RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calonlinealter RETURNS INTEGER SONAME 'liberymysql.dll';
CREATE FUNCTION calviewtablelock RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calcleartablelock RETURNS STRING SONAME 'liberymysql.dll';
CREATE FUNCTION calgetsqlcount RETURNS STRING SONAME 'liberymysql.dll';

create database if not exists erydbsys;
use erydbsys;

drop table if exists systable restrict;
drop table if exists syscolumn restrict;

-- SYSTABLE
create table if not exists systable (
	tablename varchar(128),
	`schema` varchar(128),
	objectid int,
	createdate date,
	lastupdate date,
	init int,
	next int,
	numofrows int,
	avgrowlen int,
	numofblocks int,
	autoincrement int
	) engine=erydb comment='SCHEMA SYNC ONLY';

-- SYSCOLUMN
create table if not exists syscolumn (
	`schema` varchar(128),
	tablename varchar(128),
	columnname varchar(128),
	objectid int,
	dictobjectid int,
	listobjectid int,
	treeobjectid int,
	datatype int,
	columnlength int,
	columnposition int,
	lastupdate date,
	defaultvalue varchar(64),
	nullable int,
	scale int,
	prec int,
	autoincrement char(1),
	distcount int,
	nullcount int,
	minvalue varchar(64),
	maxvalue varchar(64),
	compressiontype int,
	nextvalue bigint
	) engine=erydb comment='SCHEMA SYNC ONLY';

