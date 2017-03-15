
install(PROGRAMS post-install 
                pre-uninstall 
                remote_command.sh  
                erydbLogRotate 
                transactionLog 
                transactionLogArchiver.sh  
                module_installer.sh 
                startupTests.sh  
                user_installer.sh 
                performance_installer.sh  
                remote_scp_get.sh 
                erydbAlias 
                run.sh 
                upgrade-erydb.sh  
                post-mysql-install 
                post-mysqld-install 
                binary_installer.sh  
                os_check.sh 
                erydb 
                erydbSyslog 
                erydbSyslog-ng 
                syslogSetup.sh  
                remote_scp_put.sh 
                erydbUninstall.sh 
                erydb.def  
                remotessh.exp 
                rsync.sh 
                remote_command_verify.sh  
                erydb.conf 
                erydbSyslog7 
                master-rep-erydb.sh  
                slave-rep-erydb.sh 
                disable-rep-erydb.sh  
                myCnf-include-args.text 
                myCnf-exclude-args.text
                erydb.service
                DESTINATION ${ENGINE_BINDIR})
                
install(FILES  module DESTINATION ${ENGINE_LOCALDIR})

