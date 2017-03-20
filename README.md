# erydb
基于MariaDB的分布式列式数据库，并行MPP扩展，支持GFS HDFS存储及外部存储，百亿数据秒查 秒级汇总，mysql数据库自动多主备份

## install prerequisites
To install erydb binary you will need:

  * a CentOS7  linux host configured for software development

Along with a working C++ compiler and GNU software development tools you will need the following extra packages:

  * expect
  * zlib-devel
  * ncurses-devel
  * libxml2-devel
  * readline-devel
ex:
yum install -y  net-snmp-agent-libs boost-system boost-date-time boost-filesystem boost-thread boost-regex lz4 zlib snappy rsync expect readline ncurses nmap lsof libxml2 

## install steps
### 1、在要安装的所有主机上先做好相互的SSH免密登录
### 2、下载包到 /root目录
### 3、tar xf erydb-5.0-0.bin.tar.gz -C /usr/local
### 4、cd /usr/local/erydb && ./bin/postConofingure


<h1>交流</h1>
QQ：34954344 <br>
邮箱：hans511002@sohu.com <br>