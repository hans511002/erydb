#erydb
FROM erydb-runtool
#ENTRYPOINT ["/bin/bash","/run.sh"]
ADD files/* /usr/local/
RUN  chmod +x -R /usr/local/  && mv /usr/local/*.sh /  \
  && mkdir p /usr/lib64/galera-3 &&  mv /usr/local/libgalera_smm.so  /usr/lib64/galera-3/ \
  && mv  /usr/local/garb.service /usr/lib/systemd/system/garb.service \
  && mv  /usr/local/garbd /usr/bin/ \
  && mv  /usr/local/garb-systemd /usr/bin/ \
  && mv /usr/local/dblicense.dat /usr/local/erydb/etc/ 
CMD ["/bin/bash","/run.sh"]