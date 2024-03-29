#!/bin/bash


IAS_TEST_DS_SQLITE_DB=/tmp/test.db

sqlite3 ${IAS_TEST_DS_SQLITE_DB} <<EOF

   DROP VIEW ADDRESS_VW;
   DROP VIEW CUSTOMER_VW;

   DROP TABLE ADDRESS;
   DROP TABLE CUSTOMER;

   CREATE TABLE CUSTOMER(
        ID         INTEGER PRIMARY KEY,
        FIRSTNAME  VARCHAR(128),
        LASTNAME   VARCHAR(128),
        MIDDLENAME VARCHAR(128),
        AGE        INTEGER,
        MONEY      NUMBER(10,2),
        BIRTHDATE  DATE,
        WAKEUP     DATETIME,
        UPDATED    TIMESTAMP,
        RAWDATA    CLOB);

  CREATE TABLE ADDRESS(
         CUSTOMER_ID INTEGER,
         STREET      VARCHAR(128),
         BLOCK       NUMBER,
         TYPE        CHAR(1),
         COUNTRY     VARCHAR(64),
        FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMER(ID)
      );

  CREATE VIEW ADDRESS_VW AS SELECT * FROM ADDRESS ORDER BY 1,2,3,4;
  CREATE VIEW CUSTOMER_VW AS SELECT * FROM CUSTOMER ORDER BY 1;

EOF
