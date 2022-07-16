-- IDS - project (2nd Task)
-- Authors: Zdenek Lapes    <xlapes02>
--          Andrej Binovsky <xbinov00>
-------------------------------------------------------------------------------


---------- drop
DROP TABLE Do;
DROP TABLE Payment_card;
DROP TABLE Dispose;
DROP TABLE Bank_account;
DROP TABLE Internet_banking;
DROP TABLE Client;

DROP TABLE Worker;
DROP TABLE Manager;
DROP TABLE Employee;
DROP TABLE Office;


DROP TABLE Contain_service;
DROP TABLE Account_type;
DROP TABLE Service;


---------- create
CREATE TABLE Office -- Pobocka
(
    id_office          INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    address            VARCHAR(100) NOT NULL,
    opening_hours_from VARCHAR(20)  NOT NULL,
    opening_hours_to   VARCHAR(20)  NOT NULL
);

CREATE TABLE Client -- Klient
(
    birth_number  VARCHAR(20) PRIMARY KEY
        CHECK (
            REGEXP_LIKE(birth_number, '^\d{2}(0[1-9]|1[0-2]|5[1-9]|6[0-2])(0[1-9]|1[0-9]|2[0-9]|3[0-1])\/\d{3,4}$')
            ),
    name          VARCHAR(100) NOT NULL,
    surname       VARCHAR(100) NOT NULL,
    mobile_number VARCHAR(20)  NOT NULL
        CHECK (REGEXP_LIKE(mobile_number, '^\+420\d{9}$')),
    email         VARCHAR(255) NOT NULL
        CHECK (REGEXP_LIKE(email, '^[A-Za-z]+[A-Za-z0-9.]*@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$'))
);

CREATE TABLE Employee -- Zamestnane
(
    birth_number  VARCHAR(20) PRIMARY KEY
        CHECK (
            REGEXP_LIKE(birth_number, '^\d{2}(0[1-9]|1[0-2]|5[1-9]|6[0-2])(0[1-9]|1[0-9]|2[0-9]|3[0-1])\/\d{3,4}$')
            ),
    name          VARCHAR(100) NOT NULL,
    surname       VARCHAR(100) NOT NULL,
    mobile_number VARCHAR(13)  NOT NULL
        CHECK (REGEXP_LIKE(mobile_number, '^\+420\d{9}$')),
    email         VARCHAR(255) NOT NULL
        CHECK (REGEXP_LIKE(email, '^[A-Za-z]+[A-Za-z0-9.]*@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$')),

    office_fk     INT          NOT NULL,
    CONSTRAINT Employee_office_fk
        FOREIGN KEY (office_fk) REFERENCES Office (id_office) ON DELETE SET NULL
);

CREATE TABLE Manager -- Veduci
(
    company_car VARCHAR(50),

    client_fk   VARCHAR(20) PRIMARY KEY,
    CONSTRAINT Manager_client_fk
        FOREIGN KEY (client_fk) REFERENCES Employee (birth_number) ON DELETE CASCADE
);

CREATE TABLE Worker -- Pracovnik
(
    work_shift VARCHAR(3) CHECK (work_shift IN ('DAY', 'NIGHT')),

    client_fk  VARCHAR(20) PRIMARY KEY,
    CONSTRAINT Employee_client_fk
        FOREIGN KEY (client_fk) REFERENCES Employee (birth_number) ON DELETE CASCADE
);

CREATE TABLE Account_type -- Typ uctu
(
    name VARCHAR(255) PRIMARY KEY
);

CREATE TABLE Bank_account -- Bankvni ucet
(
    account_number VARCHAR(20) PRIMARY KEY
        CHECK (REGEXP_LIKE(account_number, '^(\d{6}-)?\d{10}\/\d{4}$')),

    client_fk      VARCHAR(20)  NOT NULL,
    account_type   VARCHAR(255) NOT NULL,
    CONSTRAINT Bank_account_client_fk
        FOREIGN KEY (client_fk) REFERENCES Client (birth_number) ON DELETE CASCADE,
    CONSTRAINT Account_type_fk
        FOREIGN KEY (account_type) REFERENCES Account_type (name) ON DELETE CASCADE
);

CREATE TABLE Dispose -- Disponuje
(
    CONSTRAINT Dispose_pk PRIMARY KEY (client_fk),
    "right"           VARCHAR(255) NOT NULL
        CHECK ("right" IN ('BASIC', 'MEDIUM', 'FULL')),

    client_fk         VARCHAR(20)  NOT NULL,
    account_number_fk VARCHAR(20)  NOT NULL,
    CONSTRAINT Dispose_client_fk
        FOREIGN KEY (client_fk) REFERENCES Client (birth_number) ON DELETE CASCADE,
    CONSTRAINT Dispose_account_number_fk
        FOREIGN KEY (account_number_fk) REFERENCES Bank_account (account_number) ON DELETE SET NULL
);

CREATE TABLE Internet_banking -- Internetove bankovnictvi
(
    id_pid    VARCHAR(7) PRIMARY KEY
        CHECK (REGEXP_LIKE(id_pid, '^\d{7}$')),
    nickname  VARCHAR(100) NOT NULL,
    password  VARCHAR(100) NOT NULL,

    client_fk VARCHAR(20)  NOT NULL,
    CONSTRAINT Internet_banking_client_fk
        FOREIGN KEY (client_fk) REFERENCES Client (birth_number) ON DELETE CASCADE
);

CREATE TABLE Do -- Vykonava
(
    id_operation          INT GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    "date"                DATE        NOT NULL,
    type                  VARCHAR(20) NOT NULL
        CHECK (type IN ('TRANSFER', 'WITHDRAWAL', 'DEPOSIT', 'CARD_PAYMENT')),


    employee_fk           VARCHAR(20) NULL,
    account_number_src_fk VARCHAR(20) NOT NULL,
    account_number_dst_fk VARCHAR(20) NULL,
    CONSTRAINT Do_account_number_are_not_same_fk CHECK (account_number_src_fk != account_number_dst_fk
        ),
    CONSTRAINT Do_employee_fk
        FOREIGN KEY (employee_fk) REFERENCES Employee (birth_number) ON DELETE SET NULL,
    CONSTRAINT Do_bank_account_src_fk
        FOREIGN KEY (account_number_src_fk) REFERENCES Bank_account (account_number) ON DELETE CASCADE,
    CONSTRAINT Do_bank_account_dsk_fk
        FOREIGN KEY (account_number_dst_fk) REFERENCES Bank_account (account_number) ON DELETE SET NULL
);

CREATE TABLE Payment_card -- Kreditni karta
(
    payment_card_number VARCHAR(100) PRIMARY KEY
        CHECK (REGEXP_LIKE(payment_card_number, '^\d{16}$')),
    expiration_year     VARCHAR(2)   NOT NULL
        CHECK (REGEXP_LIKE(expiration_year, '^\d{2}$')),
    expiration_month    VARCHAR(2)   NOT NULL
        CHECK (REGEXP_LIKE(expiration_month, '^(0[1-9]|1[0-2])$')),
    cvc_code            VARCHAR(3)   NOT NULL
        CHECK (REGEXP_LIKE(cvc_code, '^\d{3}$')),
    card_type           VARCHAR(255) NOT NULL
        CHECK (card_type IN ('CREDIT', 'DEBIT')),

    client_fk           VARCHAR(20)  NOT NULL,
    account_number_fk   VARCHAR(20)  NOT NULL,
    CONSTRAINT Payment_card_client_fk
        FOREIGN KEY (client_fk) REFERENCES Client (birth_number) ON DELETE SET NULL
);

CREATE TABLE Service -- Sluzba
(
    name        VARCHAR(255) PRIMARY KEY,
    description VARCHAR(255) NULL
);

CREATE table Contain_service -- Obsahuje sluzbu
(
    type_fk    VARCHAR(255) NOT NULL,
    service_fk VARCHAR(255) NOT NULL,
    CONSTRAINT Contain_type_fk
        FOREIGN KEY (type_fk) REFERENCES Account_type (name) ON DELETE CASCADE,
    CONSTRAINT Contain_service_type_fk
        FOREIGN KEY (service_fk) REFERENCES Service (name) ON DELETE CASCADE,

    CONSTRAINT Contain_service_fk PRIMARY KEY (type_fk, service_fk)
);

---------- insert
INSERT INTO Office (address, opening_hours_from, opening_hours_to)
VALUES ('Ceska', '09:00', '17:00');
INSERT INTO Office (address, opening_hours_from, opening_hours_to)
VALUES ('Lidicka', '09:00', '17:00');

INSERT INTO Client (birth_number, name, surname, mobile_number, email)
VALUES ('020202/0001', 'Stefan', 'Celeng', '+420000000001', 'email@example1.com');
INSERT INTO Client (birth_number, name, surname, mobile_number, email)
VALUES ('020202/0002', 'Stefan', 'Drevak', '+420000000002', 'email@example2.com');
INSERT INTO Client (birth_number, name, surname, mobile_number, email)
VALUES ('020202/1002', 'Eduard', 'Repa', '+420000000012', 'email@example12.com');
INSERT INTO Client (birth_number, name, surname, mobile_number, email)
VALUES ('111111/1002', 'Jan', 'Repa', '+420000000012', 'email@example12.com');

INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('020202/0003', 'Patrik', 'Vrba', '+420000000003', 'email@example3.com', 1);
INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('020202/0004', 'Martin', 'Hrna', '+420000000004', 'email@example4.com', 2);
INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('020202/0011', 'Tomas', 'Hrna', '+420000000033', 'email@example44.com', 2);


INSERT INTO Manager (company_car, client_fk)
VALUES ('KIA', '020202/0003');

INSERT INTO Worker (work_shift, client_fk)
VALUES ('DAY', '020202/0004');

INSERT INTO Account_type (name)
VALUES ('SAVING');
INSERT INTO Account_type (name)
VALUES ('STUDENT');
INSERT INTO Account_type (name)
VALUES ('CLASSIC');

INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('0123456789/0001', '020202/0001', 'SAVING');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('0123456789/0002', '020202/1002', 'CLASSIC');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('0123456777/0002', '111111/1002', 'CLASSIC');

INSERT INTO Dispose ("right", client_fk, account_number_fk)
VALUES ('BASIC', '020202/0002', '0123456789/0001');
INSERT INTO Dispose ("right", client_fk, account_number_fk)
VALUES ('BASIC', '111111/1002', '0123456789/0001');

INSERT INTO Internet_banking (id_pid, nickname, password, client_fk)
VALUES ('1234567', 'prezyvka1', 'heslo1', '020202/0001');

INSERT INTO Do ("date", type, account_number_src_fk)
VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'WITHDRAWAL', '0123456789/0001');

INSERT INTO Do ("date", type, account_number_src_fk)
VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'WITHDRAWAL', '0123456789/0001');


INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('0000000000000001', '23', '01', '167', 'CREDIT', '020202/0001', '0123456789/0001');
INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('0000000000000002', '24', '02', '167', 'DEBIT', '020202/0001', '0123456789/0001');
INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('0000000000000003', '24', '02', '167', 'CREDIT', '111111/1002', '0123456777/0002');


INSERT INTO Service (name, description)
VALUES ('SMS_NOTIFICATION', 'Sms notification after the bank operation');

INSERT INTO Service (name, description)
VALUES ('FREE_WITHDRAWAL', 'Free ATM withdrawal from foreign ATMS');

INSERT INTO Contain_service (type_fk, service_fk)
VALUES ('SAVING', 'SMS_NOTIFICATION');
INSERT INTO Contain_service (type_fk, service_fk)
VALUES ('SAVING', 'FREE_WITHDRAWAL');
INSERT INTO Contain_service (type_fk, service_fk)
VALUES ('STUDENT', 'SMS_NOTIFICATION');
INSERT INTO Contain_service (type_fk, service_fk)
VALUES ('CLASSIC', 'FREE_WITHDRAWAL');

-----------------------------------------------------TASK 3-------------------------------------------------------------

-- Who Works in office on address Lidicka
-- SELECT WITH 2 JOIN TABLES
SELECT E.birth_number, E.name, E.surname
FROM Office O,
     Employee E
WHERE E.office_fk = O.id_office
  AND O.address = 'Lidicka';

-- Which payment cards and their type have bank account with number '0123456789/0001'
-- SELECT WITH 2 JOIN TABLES
SELECT PC.payment_card_number AS "CARD_NUMBER", PC.card_type AS "CARD_TYPE"
FROM Payment_card PC,
     Bank_account BA
WHERE PC.account_number_fk = BA.account_number
  AND BA.account_number = '0123456789/0001';


-- Which services has bank account with number '0123456789/0001'
-- SELECT WITH 3 JOIN TABLES (I DID 4)
SELECT S.name AS "SERVICE_NAME", S.description
FROM Bank_account BA,
     Contain_service CS,
     Account_type AT,
     Service S
WHERE CS.service_fk = S.name
  AND CS.type_fk = AT.name
  AND BA.account_type = AT.name
  AND BA.account_number = '0123456789/0001';

-- Which clients owns bank account and how many
-- SELECT WITH GROUP BY AND FUNCTION
SELECT C.birth_number, C.name, C.surname, COUNT(*)
FROM Client C,
     Bank_account Ba
WHERE C.birth_number = BA.client_fk
GROUP BY C.birth_number, C.name, C.surname;

-- How many people works in each Office
-- SELECT WITH GROUP BY AND FUNCTION
SELECT O.address, COUNT(*) AS "NUMBER_OF_EMPLOYEES"
FROM Office O,
     Employee E
WHERE E.office_fk = O.id_office
GROUP BY O.id_office, O.address;

-- SELECT WITH EXISTS PREDICATE
-- Which clients have only credit cards?
SELECT *
FROM Bank_account B
         JOIN Payment_card P ON B.account_number = P.account_number_fk
WHERE P.card_type = 'CREDIT'
  AND NOT EXISTS(SELECT *
                 FROM Payment_card P
                 where B.account_number = P.account_number_fk
                   and P.card_type != 'CREDIT');

-- SELECT WITH IN PREDICATE WITH INNER SELECT
-- Which clients have classic accounts?
SELECT *
from Bank_account B
where account_type IN (
    Select *
    from Account_type A
    where A.NAME = 'CLASSIC')
