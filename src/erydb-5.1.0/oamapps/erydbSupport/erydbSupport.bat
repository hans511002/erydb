@echo off
pushd .
set help=
if "%1" == "-h" (set help=true)
if "%1" == "/h" (set help=true)
if "%1" == "--help" (set help=true)
if "%help%"=="true" (
  echo The EryDB Support Report creates a report that can be sent to EryDB
  echo for help with field support. There are no options to this command.
  set help=
  exit /B 0 
)

echo.  
echo Running the EryDB Support Report, outputting to EryDBSupportReport.txt

call :func > EryDBSupportReport.txt 2>&1

echo.  
echo Report finished

popd
exit /B 0

:ErrorExit

echo.  
echo Error - Failed to find EryDB Install Directory in Windows Registry, Exiting
popd
exit /B 1

:func

  setlocal
  set key="HKLM\SOFTWARE\erydb\EryDB"
  set homeValue=EryDBHome
  set configValue=ConfigFile

  for /f "tokens=3,*" %%a in ('reg query %key% /ve 2^>NUL ^| findstr REG_SZ') do (
    set EryDBInstall=%%b
   )

  if "%EryDBInstall%" == "" (
  	for /f "tokens=2,*" %%a in ('reg query %key% /ve 2^>NUL ^| findstr REG_SZ') do (
    	set EryDBInstall=%%b
   	)
  )

  ::error out if can't locate Install Directory
  if "%EryDBInstall%" == "" GOTO ErrorExit

echo #######################################################################
echo #                                                                     #
echo #     EryDB Support Report - %date% %time%
echo #                                                                     #
echo #######################################################################
echo.
echo.
echo =======================================================================
echo =                    Software/Version Report                          =
echo =======================================================================
echo. 
echo.
echo -- EryDB Software Version --
type %EryDBInstall%\etc\erydbVersion.txt
echo. 
echo -- mysql Software Version --
mysql --user=root -e status
echo. 
echo -- Windows Version --
ver
echo.
echo.
echo =======================================================================
echo =                    Status Report                                    =
echo =======================================================================
echo.  
echo. 
echo -- EryDB Process Status -- 
echo. 

tasklist /FI "Imagename eq mysqld.exe"
tasklist /FI "Imagename eq controllernode.exe"   
tasklist /FI "Imagename eq workernode.exe"
tasklist /FI "Imagename eq PrimProc.exe"
tasklist /FI "Imagename eq ExeMgr.exe"      
tasklist /FI "Imagename eq DDLProc.exe"           
tasklist /FI "Imagename eq DMLProc.exe"         
tasklist /FI "Imagename eq WriteEngineServer.exe"

echo. 
echo. 
echo =======================================================================
echo =                    Configuration Report                             =
echo =======================================================================
echo.
echo -- Windows EryDB Registry Values --
echo.

  echo EryDBInstall = %EryDBInstall%

  for /f "tokens=2,*" %%a in ('reg query %key% /v %homeValue% 2^>NUL ^| findstr %homeValue%') do (
    set EryDBHome=%%b
  )
  echo EryDBHome    = %EryDBHome%

  for /f "tokens=2,*" %%a in ('reg query %key% /v %configValue% 2^>NUL ^| findstr %configValue%') do (
    set ConfigFile=%%b
  )
  echo ConfigFile     = %ConfigFile%
echo.
echo.
echo -- EryDB System Configuration Information -- 
echo.
cd %EryDBInstall%\bin
for /f "delims=" %%a in ('getConfig.exe DBBC NumBlocksPct') do @echo NumBlocksPct = %%a
for /f "delims=" %%a in ('getConfig.exe HashJoin TotalUmMemory') do @echo TotalUmMemory = %%a
for /f "delims=" %%a in ('getConfig.exe VersionBuffer VersionBufferFileSize') do @echo VersionBufferFileSize = %%a
for /f "delims=" %%a in ('getConfig.exe ExtentMap FilesPerColumnPartition') do @echo FilesPerColumnPartition = %%a
for /f "delims=" %%a in ('getConfig.exe ExtentMap ExtentsPerSegmentFile') do @echo ExtentsPerSegmentFile = %%a
echo.
echo.
echo -- EryDB System Configuration File --
echo.
type "%ConfigFile%"
echo.  
echo.  
echo -- System Process Status -- 
echo. 
tasklist /v
echo.
echo =======================================================================
echo =                   Resource Usage Report                             =
echo =======================================================================
echo. 
echo -- System Information--
echo. 
systeminfo
echo. 
echo -- IP Configuration Information --
echo. 
ipconfig
echo.
echo  -- Disk BRM Data files --
echo.   
dir "%EryDBInstall%\dbrm\"
echo.   
echo  -- View Table Locks --
echo.   
cd %EryDBInstall%\bin\
viewtablelock.exe
echo.   
echo.    
echo   -- BRM Extent Map  --
echo.    
cd %EryDBInstall%\bin\
editem.exe -i
echo.
echo.
echo =======================================================================
echo =                   Log Report                                        =
echo =======================================================================
echo. 
echo -- EryDB Platform Logs --
echo. 
type "%EryDBInstall%\log\EryDBLog.txt"
echo. 
echo. 
echo -- EryDB MySQl log --
echo.
type "%EryDBInstall%\mysqldb\*.err" 
echo.
echo. 
echo -- EryDB Bulk Load Logs --
echo. 
dir "%EryDBInstall%\bulk\data"
echo. 
dir "%EryDBInstall%\bulk\log"
echo. 
dir "%EryDBInstall%\bulk\job"
echo.
echo -- Check for Errors in Bulk Logs --
echo.
cd "%EryDBInstall%\bulk\log"
findstr /spin /c:"error" *
findstr /spin /c:"failed" *
cd "%EryDBInstall%\bulk\job"
findstr /spin /c:"error" *
findstr /spin /c:"failed" *
echo.
echo =======================================================================
echo =                    DBMS Report                                      =
echo =======================================================================
echo.
echo -- DBMS EryDB Mysql Version -- 
echo.
mysql --user=root -e status
echo. 
echo -- DBMS Mysql EryDB System Column  -- 
echo. 
mysql --user=root -e "desc erydbsys.syscolumn"
echo. 
echo -- DBMS Mysql EryDB System Table  -- 
echo. 
mysql --user=root -e "desc erydbsys.systable"
echo. 
echo -- DBMS Mysql EryDB System Table Data -- 
echo.
mysql --user=root -e "select * from erydbsys.systable"
echo. 
echo -- DBMS Mysql EryDB Databases -- 
echo.
mysql --user=root -e "show databases"
echo.
echo -- DBMS Mysql EryDB variables -- 
echo. 
mysql --user=root -e "show variables"
echo. 
echo -- DBMS Mysql EryDB config file -- 
echo.
type "%EryDBInstall%\my.ini"
echo.
echo -- Active Queries -- 

::cd \EryDB\genii\oamapps\erydbSupport


