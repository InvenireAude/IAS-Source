#!/bin/bash

IAS_TEST_DS_CONNECT=iadev/password

sqlplus / as sysdba <<EOF
DROP USER iadev CASCADE;

CREATE USER iadev IDENTIFIED BY password;

REVOKE ALL PRIVILEGES FROM iadev;

GRANT CREATE SESSION TO iadev;
GRANT CREATE TABLE TO iadev;
GRANT CREATE VIEW TO iadev;
GRANT CREATE PROCEDURE TO iadev;
GRANT CREATE SEQUENCE TO iadev;
GRANT CREATE TRIGGER TO iadev;

GRANT UNLIMITED TABLESPACE TO iadev;

exit
EOF

sqlplus -S ${IAS_TEST_DS_CONNECT} <<EOF

   DROP VIEW ADDRESS_VW;
   DROP VIEW CUSTOMER_VW;

   TRUNCATE TABLE ADDRESS;
   TRUNCATE TABLE CUSTOMER;

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
        WAKEUP     TIMESTAMP,
        UPDATED    TIMESTAMP,
        RAWDATA    BLOB);

  CREATE TABLE ADDRESS(
         CUSTOMER_ID INTEGER,
         STREET      VARCHAR(128),
         BLOCK       NUMBER,
         TYPE        CHAR(1),
         COUNTRY      VARCHAR(64),
        FOREIGN KEY (CUSTOMER_ID) REFERENCES CUSTOMER(ID)
      );

 CREATE VIEW ADDRESS_VW AS SELECT * FROM ADDRESS ORDER BY 1,2,3,4;
 CREATE VIEW CUSTOMER_VW AS SELECT * FROM CUSTOMER ORDER BY 1;

 DELETE FROM ADDRESS;
   DELETE FROM CUSTOMER;

   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(1,'Johny','Kowalski','Koval',41);

   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(2,'Walter','Smith','Junior',14);

   INSERT INTO CUSTOMER(ID,FIRSTNAME,LASTNAME,MIDDLENAME,AGE) VALUES
	(3,'Sammy','Novak','Nova',24);

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE) VALUES
        (1,'Eastwoods',123,'N');

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (1,'Westwoods',321,'F','Canada');

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE,COUNTRY) VALUES
        (2,'Sunset',1009,'F','USA');

   INSERT INTO ADDRESS(CUSTOMER_ID,STREET,BLOCK,TYPE) VALUES
        (3,'Sunrise',91,'N');


   SELECT COUNT(1) CUSTOMERS FROM CUSTOMER;
   SELECT COUNT(1) ADDRESSES FROM ADDRESS;



CREATE OR REPLACE PROCEDURE TESTADD(A1 IN NUMBER, A2 IN OUT NUMBER, A3 OUT NUMBER) AS
BEGIN
   A2 := A1;
   A3 := 2  * A2;
END;
/
show errors;

CREATE TABLE TT1 (
 COL1 NUMBER(10,2)
);

CREATE OR REPLACE PROCEDURE TESTADD2(A1 IN NUMBER, A2 IN OUT NUMBER, A3 OUT TT1.COL1%TYPE ) AS
BEGIN
  A2 := A1;
  A3 := 33.3333;
END;
/
show errors;

CREATE OR REPLACE FUNCTION GETCUSTOMERS (maxid IN NUMBER)
 RETURN sys_refcursor
AS
   res sys_refcursor;
 BEGIN
   OPEN res FOR select id FROM CUSTOMER WHERE id <= maxid;
   RETURN res;
 END;
/
show errors;

CREATE OR REPLACE FUNCTION GETNUM(id IN NUMBER)
 RETURN NUMBER
AS
 BEGIN
   RETURN 100 * id;
 END;
/
show errors;


--select * from table(getcustomers(2));

EOF
