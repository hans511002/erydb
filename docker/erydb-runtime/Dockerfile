#erydb
FROM centos-ssh
MAINTAINER hans
RUN yum install -y  epel-release &&  yum install -y  libaio jemalloc  thrift  net-snmp  lzo  net-snmp-agent-libs \
 boost-system boost-date-time boost-filesystem boost-thread boost-regex lz4  zlib snappy rsync expect readline ncurses\
  nmap lsof libxml2 file-5.11-31.el7.x86_64 sudo-1.8.6p7-16.el7.x86_64  && yum clean all
