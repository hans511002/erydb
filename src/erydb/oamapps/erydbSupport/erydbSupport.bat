@echo off
pushd .
set help=
if "%1" == "-h" (set help=true)
if "%1" == "/h" (set help=true)
if "%1" == "--help" (set help=true)
if "%help%"=="true" (
  echo The Erydb Support Report creates a report that can be sent to Erydb
  echo for help with field support. There are no options to this command.
  set help=
  exit /B 0 
)

echo.  
echo Running the Erydb Support Report, outputting to ErydbSupportReport.txt

call :func > ErydbSupportReport.txt 2>&1

echo.  
echo Report finished

popd
exit /B 0

:ErrorExit

echo.  
echo Error - Failed to find Erydb Install Directory in Windows Registry, Exiting
popd
exit /B 1

:func

  setlocal
  set key="HKLM\SOFTWARE\Erydb\Erydb"
  set homeValue=ErydbHome
  set configValue=ConfigFile

  for /f "tokens=3,*" %%a in ('reg query %key% /ve 2^>NUL ^| findstr REG_SZ') do (
    set ErydbInstall=%%b
   )

  if "%ErydbInstall%" == "" (
  	for /f "tokens=2,*" %%a in ('reg query %key% /ve 2^>NUL ^| findstr REG_SZ') do (
    	set ErydbInstall=%%b
   	)
  )

  ::error out if can't locate Install Directory
  if "%ErydbInstall%" == "" GOTO ErrorExit

echo #######################################################################
echo #                                                                     #
echo #     Erydb Support Report - %date% %time%
echo #                                                                     #
echo #######################################################################
echo.
echo.
echo =======================================================================
echo =                    Software/Version Report                          =
echo =======================================================================
echo. 
echo.
echo -- Erydb Software Version --
type %ErydbInstall%\etc\ErydbVersion.txt
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
echo -- Erydb Process Status -- 
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
echo -- Windows Erydb Registry Values --
echo.

  echo ErydbInstall = %ErydbInstall%

  for /f "tokens=2,*" %%a in ('reg query %key% /v %homeValue% 2^>NUL ^| findstr %homeValue%') do (
    set ErydbHome=%%b
  )
  echo ErydbHome    = %ErydbHome%

  for /f "tokens=2,*" %%a in ('reg query %key% /v %configValue% 2^>NUL ^| findstr %configValue%') do (
    set ConfigFile=%%b
  )
  echo ConfigFile     = %ConfigFile%
echo.
echo.
echo -- Erydb System Configuration Information -- 
echo.
cd %ErydbInstall%\bin
for /f "delims=" %%a in ('getConfig.exe DBBC NumBlocksPct') do @echo NumBlocksPct = %%a
for /f "delims=" %%a in ('getConfig.exe HashJoin TotalUmMemory') do @echo TotalUmMemory = %%a
for /f "delims=" %%a in ('getConfig.exe VersionBuffer VersionBufferFileSize') do @echo VersionBufferFileSize = %%a
for /f "delims=" %%a in ('getConfig.exe ExtentMap FilesPerColumnPartition') do @echo FilesPerColumnPartition = %%a
for /f "delims=" %%a in ('getConfig.exe ExtentMap ExtentsPerSegmentFile') do @echo ExtentsPerSegmentFile = %%a
echo.
echo.
echo -- Erydb System Configuration File --
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
dir "%ErydbInstall%\dbrm\"
echo.   
echo  -- View Table Locks --
echo.   
cd %ErydbInstall%\bin\
viewtablelock.exe
echo.   
echo.    
echo   -- BRM Extent Map  --
echo.    
cd %ErydbInstall%\bin\
editem.exe -i
echo.
echo.
echo =======================================================================
echo =                   Log Report                                        =
echo =======================================================================
echo. 
echo -- Erydb Platform Logs --
echo. 
type "%ErydbInstall%\log\ErydbLog.txt"
echo. 
echo. 
echo -- Erydb MySQl log --
echo.
type "%ErydbInstall%\mysqldb\*.err" 
echo.
echo. 
echo -- Erydb Bulk Load Logs --
echo. 
dir "%ErydbInstall%\bulk\data"
echo. 
dir "%ErydbInstall%\bulk\log"
echo. 
dir "%ErydbInstall%\bulk\job"
echo.
echo -- Check for Errors in Bulk Logs --
echo.
cd "%ErydbInstall%\bulk\log"
findstr /spin /c:"error" *
findstr /spin /c:"failed" *
cd "%ErydbInstall%\bulk\job"
findstr /spin /c:"error" *
findstr /spin /c:"failed" *
echo.
echo =======================================================================
echo =                    DBMS Report                                      =
echo =======================================================================
echo.
echo -- DBMS Erydb Mysql Version -- 
echo.
mysql --user=root -e status
echo. 
echo -- DBMS EryDB System Column  -- 
echo. 
mysql --user=root -e "desc erydbsys.syscolumn"
echo. 
echo -- DBMS EryDB System Table  -- 
echo. 
mysql --user=root -e "desc erydbsys.systable"
echo. 
echo -- DBMS EryDB System Table Data -- 
echo.
mysql --user=root -e "select * from erydbsys.systable"
echo. 
echo -- DBMS EryDB Databases -- 
echo.
mysql --user=root -e "show databases"
echo.
echo -- DBMS EryDB variables -- 
echo. 
mysql --user=root -e "show variables"
echo. 
echo -- DBMS EryDB config file -- 
echo.
type "%ErydbInstall%\my.ini"
echo.
echo -- Active Queries -- 

::cd \Erydb\genii\oamapps\erydbSupport


