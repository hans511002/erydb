-- Create table with named references constraint and on delete action
CREATE TABLE erydb.PART_1453
(p_29 numeric(5,2) primary key,
 constraint fooby
  foreign key (p_29)
   references Customers(p_partkey)
   on delete restrict)
engine=erydb;
