# This is EryDB 5.0.0

## Build prerequisites
To build EryDB from source you will need:

  * a CentOS/RHEL 7 linux host configured for software development

Along with a working C++ compiler and GNU software development tools you will need the following extra packages:

  * expect
  * zlib-devel
  * ncurses-devel
  * libxml2-devel
  * readline-devel

## Build steps

### Build environment

    mkdir erydb-src
    cd erydb-src

### EryDB MySQL

    wget -Omysql-4.6.2-1.tar.gz https://github.com/erydb/mysql/archive/4.6.2-1.tar.gz
    tar -zxf mysql-4.6.2-1.tar.gz
    ln -s mysql-4.6.2-1 mysql
    cd mysql
    ./configure --prefix=$HOME/erydb/mysql
    make
    make install
    
### EryDB

    cd ..
    wget -Oerydb-4.6.2-1.tar.gz https://github.com/erydb/archive/4.6.2-1.tar.gz
    tar -zxf erydb-4.6.2-1.tar.gz
    ln -s erydb-4.6.2-1 erydb
    cd erydb
    ./configure --prefix=$HOME/erydb
    make
    make install
    
This will leave you with `$HOME/erydb` as a binary tree. Follow the Binary Download
instructions in the EryDB 4.6 Installation Guide (available on http://www.erydb.co/).

## How to Contribute
  * You may submit your contributions via GitHub pull requests.
  * The submission must be by the original author.
  * Along with any pull requests, please state that the contribution is your original work
and that you license the work to the project under the project's open source license
and the EryDB Contributor Agreement
(see EryDBContributorAgreement.pdf). Whether or not you state this explicitly,
by submitting any copyrighted material via pull request, email, or other means you agree to
license the material under the project's open source license and warrant that you have the
legal authority to do so.
  * The EryDB Project committee will review your pull request and shall decide when and
whether to merge your request in the main EryDB project. The EryDB Project
committee will inform you of any decision regarding your request.

