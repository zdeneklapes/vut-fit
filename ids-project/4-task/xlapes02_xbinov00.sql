-- IDS - project (4nd Task)
-- Authors: Zdenek Lapes    <xlapes02>
--          Andrej Binovsky <xbinov00>
-------------------------------------------------------------------------------


--------------------- DROP -----------------------
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

--------------------- CREATE -----------------------
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
    "date"        DATE                NOT NULL,
    name          VARCHAR(100)        NOT NULL,
    surname       VARCHAR(100)        NOT NULL,
    mobile_number VARCHAR(20)         NOT NULL
        CHECK (REGEXP_LIKE(mobile_number, '^\+420\d{9}$')),
    email         VARCHAR(255)        NOT NULL
        CHECK (REGEXP_LIKE(email, '^[A-Za-z]+[A-Za-z0-9.]*@[A-Za-z0-9.-]+\.[A-Za-z]{2,4}$')),
    is_premium    CHAR(1) default 'N' NOT NULL
        CHECK (is_premium IN ('N', 'Y'))
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
    work_shift VARCHAR(5) CHECK (work_shift IN ('DAY', 'NIGHT')),

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
    type                  VARCHAR(20) NOT NULL CHECK (type IN
                                                      ('TRANSFER', 'WITHDRAWAL', 'DEPOSIT', 'CARD_PAYMENT', 'CREATE',
                                                       'CANCEL')),
    employee_fk           VARCHAR(20) NULL,
    client_fk             VARCHAR(20) NOT NULL,
    account_number_src_fk VARCHAR(20) NOT NULL,
    account_number_dst_fk VARCHAR(20) NULL,

    CONSTRAINT Do_account_number_are_not_same_fk CHECK (account_number_src_fk != account_number_dst_fk),

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


------------------------------TRIGGER ----------------------------------
-- 1. Trigger: Coverts each name and surname to lowercase
CREATE OR REPLACE TRIGGER to_lower_case
    before insert or update
    on CLIENT
    for each row
begin
    :NEW.name := LOWER(:NEW.name);
    :NEW.surname := LOWER(:NEW.surname);
end;

-- 2.Trigger: Check if user can do operation on the account.
create or replace trigger update_client_info
    before insert
    on Do
    for each row
declare
    count_1 INT;
    count_2 INT;
begin
    select COUNT(*)
    into count_1
    from Bank_account
    where client_fk = :NEW.client_FK
      and account_number = :NEW.account_number_src_fk;

    select COUNT(*)
    into count_2
    from Dispose
    where client_fk = :NEW.client_FK
      and account_number_fk = :NEW.account_number_src_fk;

    DBMS_OUTPUT.PUT_LINE(count_1);
    DBMS_OUTPUT.PUT_LINE(count_2);
    if (count_1 = 0 and count_2 = 0) then
        raise_application_error(-1, 'User do not have privileges to this account');
    end if;
exception
    when no_data_found then raise_application_error(-1, 'No data found!');
end update_client_info;

----------------------------- INSERT -----------------------------------
INSERT INTO Office (address, opening_hours_from, opening_hours_to)
VALUES ('Ceska', '09:00', '17:00');
INSERT INTO Office (address, opening_hours_from, opening_hours_to)
VALUES ('Lidicka', '09:00', '17:00');

INSERT INTO Client (birth_number, name, surname, mobile_number, email, "date")
VALUES ('111111/0000', 'Stefan', 'Celeng', '+420000000000', 'email@example1.com', TO_DATE('1998-01-30', 'YYYY-MM-DD'));
INSERT INTO Client (birth_number, name, surname, mobile_number, email, "date")
VALUES ('111111/1111', 'Stefan', 'Drevak', '+420111111111', 'email@example2.com', TO_DATE('2000-01-01', 'YYYY-MM-DD'));
INSERT INTO Client (birth_number, name, surname, mobile_number, email, "date")
VALUES ('111111/2222', 'Eduard', 'Repa', '+420222222222', 'email@example12.com', TO_DATE('2010-11-30', 'YYYY-MM-DD'));
INSERT INTO Client (birth_number, name, surname, mobile_number, email, "date")
VALUES ('111111/3333', 'Jan', 'Repa', '+420333333333', 'email@example12.com', TO_DATE('2000-12-30', 'YYYY-MM-DD'));

INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('111111/4444', 'Patrik', 'Vrba', '+420444444444', 'email@example3.com', 1);
INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('111111/5555', 'Martin', 'Hrna', '+420555555555', 'email@example4.com', 2);
INSERT INTO Employee (birth_number, name, surname, mobile_number, email, office_fk)
VALUES ('111111/6666', 'Tomas', 'Hrna', '+420666666666', 'email@example44.com', 2);

INSERT INTO Manager (company_car, client_fk)
VALUES ('KIA', '111111/4444');

INSERT INTO Worker (work_shift, client_fk)
VALUES ('DAY', '111111/5555');
INSERT INTO Worker (work_shift, client_fk)
VALUES ('NIGHT', '111111/6666');

INSERT INTO Account_type (name)
VALUES ('SAVING');
INSERT INTO Account_type (name)
VALUES ('STUDENT');
INSERT INTO Account_type (name)
VALUES ('CLASSIC');

INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('0000000000/0000', '111111/1111', 'CLASSIC');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('1111111111/0000', '111111/1111', 'CLASSIC');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('2222222222/0000', '111111/1111', 'SAVING');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('3333333333/0000', '111111/3333', 'CLASSIC');
INSERT INTO Bank_account (account_number, client_fk, account_type)
VALUES ('4444444444/0000', '111111/3333', 'SAVING');

INSERT INTO Dispose ("right", client_fk, account_number_fk)
VALUES ('BASIC', '111111/0000', '0000000000/0000');
-- INSERT INTO Dispose ("right", client_fk, account_number_fk)
-- VALUES ('BASIC', '111111/2222', '4444444444/0000');

INSERT INTO Internet_banking (id_pid, nickname, password, client_fk)
VALUES ('0000000', 'nick1', 'heslo1', '111111/0000');

INSERT INTO Do ("date", type, account_number_src_fk, client_fk)
VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'WITHDRAWAL', '0000000000/0000', '111111/1111');
INSERT INTO Do ("date", type, account_number_src_fk, client_fk)
VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'WITHDRAWAL', '0000000000/0000', '111111/0000');
INSERT INTO Do ("date", type, account_number_src_fk, client_fk, employee_fk)
VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'CREATE', '0000000000/0000', '111111/0000', '111111/4444');

INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('0000000000000000', '23', '01', '167', 'CREDIT', '111111/1111', '1111111111/0000');
INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('1111111111111111', '24', '02', '167', 'DEBIT', '111111/1111', '2222222222/0000');
INSERT INTO Payment_card (payment_card_number, expiration_year, expiration_month, cvc_code, card_type, client_fk,
                          account_number_fk)
VALUES ('2222222222222222', '24', '02', '167', 'CREDIT', '111111/3333', '3333333333/0000');


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


-----------------------------------------------------TASK 4-------------------------------------------------------------
---------------------------- TRIGGER USAGE ------------------------------
-- 1.Trigger
select name, surname
from Client;

-- 2.Trigger: Insufficient privileges to this account for this user
-- we leave following two line as comments, because it will produce error
-- INSERT INTO Do ("date", type, account_number_src_fk, client_fk)
-- VALUES (TO_DATE('2000-07-30', 'YYYY-MM-DD'), 'WITHDRAWAL', '1111111111/0000', '111111/2222');

---------------------------- PROCEDURE ------------------------------
-- 1.Procedure: Show details about bank and how many customer bank has customers
create or replace procedure bank_info
as
    users_count           number;
    bank_accounts_classic number;
    bank_accounts_student number;
    bank_accounts_saving  number;
    percent_classic       number;
    percent_student       number;
    percent_saving        number;
    all_accounts          number;
begin
    select count(*) into users_count from Client;
    select count(*) into bank_accounts_classic from Bank_account b where b.account_type = 'CLASSIC';
    select count(*) into bank_accounts_student from Bank_account b where b.account_type = 'STUDENT';
    select count(*) into bank_accounts_saving from Bank_account b where b.account_type = 'SAVING';

    all_accounts := bank_accounts_saving + bank_accounts_student + bank_accounts_classic;
    percent_classic := (bank_accounts_classic / all_accounts) * 100;
    percent_student := (bank_accounts_student / all_accounts) * 100;
    percent_saving := (bank_accounts_saving / all_accounts) * 100;

    DBMS_OUTPUT.PUT_LINE('Bank has ' || users_count || ' clients, ' || all_accounts || ' account/s from which are ' ||
                         percent_classic ||
                         '% classic accounts'
        || ', ' || percent_student || '% student accounts and ' || percent_saving || '% saving accounts');

exception
    when zero_divide then
        begin
            if all_accounts = 0 then
                DBMS_OUTPUT.PUT_LINE('No account in db!');
            end if;
        end;
end;
-- Usage example:
begin
    bank_info;
end;


-- 2.Procedure: How many users operate with specific type account?
create or replace procedure count_accounts_type(account_type_ in Account_type.name%type)
as
    cursor cursor_accounts is select distinct client_fk
                              from Bank_account b
                              where b.account_type = account_type;
    row     Bank_account.client_fk%type;
    counter INT;
begin
    counter := 0;
    open cursor_accounts;
    loop
        fetch cursor_accounts into row;
        exit when cursor_accounts%notfound;
        DBMS_OUTPUT.PUT_LINE(row);
        counter := counter + 1;
    end loop;
    close cursor_accounts;
    DBMS_OUTPUT.PUT_LINE(counter || ' clients operate with 1 or more ' || account_type_ || ' accounts');
exception
    when NO_DATA_FOUND then
        begin
            dbms_output.put_line('Account with ' || account_type_ || ' type not found!');
        end;
end;
-- Usage example:
begin
    count_accounts_type('CLASSIC');
end;


---------------------------- EXPLAIN PLAN ------------------------------
-- Explain plan: Select all client, which have more than two accounts and did already any withdrawal operation.
explain plan for
select c.birth_number, c.name, c.surname, count(Ba.client_fk)
from Client c
         join Bank_account Ba on c.birth_number = Ba.client_fk
         join Do D on Ba.account_number = D.account_number_src_fk
where D.type = 'WITHDRAWAL'
group by c.birth_number, c.name, c.surname
having count(Ba.client_fk) >= 0
order by c.name, c.surname;

select *
from table (DBMS_XPLAN.display);

-- Index: Retrieve client_fk column from Bank_account table to improve data retrieving performance for this table.
create index bank_clients on Bank_account (client_fk);

-- Explain plan: Showing that data is retrieved faster after indexing
explain plan set statement_id = 'st2' into plan_table for
select c.birth_number, c.name, c.surname, count(Ba.client_fk)
from Client c
         join Bank_account Ba on c.birth_number = Ba.client_fk
         join Do D on Ba.account_number = D.account_number_src_fk
where D.type = 'WITHDRAWAL'
group by c.birth_number, c.name, c.surname
having count(Ba.client_fk) >= 0
order by c.name, c.surname;

select *
from table (DBMS_XPLAN.display);

drop index bank_clients;

---------------------------- MATERIALIZED VIEW ------------------------------
-- Materialized view showing each user and how many account they have.
drop materialized view user_accounts;
create materialized view user_accounts
as
select c.birth_number, c.name, c.surname, count(*)
from Client c
         join Bank_account Ba on c.birth_number = Ba.client_fk
group by c.birth_number, c.name, c.surname;

select *
from user_accounts;

-- Updated only in table, but not in view
update Client
set name = 'update'
where birth_number = '111111/0000';

commit;

select *
from user_accounts;


---------------------------- GRANT ACCESS ------------------------------
GRANT ALL ON Do TO XBINOV00;
GRANT ALL ON Payment_card TO XBINOV00;
GRANT ALL ON Dispose TO XBINOV00;
GRANT ALL ON Bank_account TO XBINOV00;
GRANT ALL ON Internet_banking TO XBINOV00;
GRANT ALL ON Client TO XBINOV00;
GRANT ALL ON Worker TO XBINOV00;
GRANT ALL ON Manager TO XBINOV00;
GRANT ALL ON Employee TO XBINOV00;
GRANT ALL ON Office TO XBINOV00;
GRANT ALL ON Contain_service TO XBINOV00;
GRANT ALL ON Account_type TO XBINOV00;
GRANT ALL ON Service TO XBINOV00;
GRANT EXECUTE ON bank_info TO XBINOV00;
GRANT EXECUTE ON count_accounts_type TO XBINOV00;
GRANT ALL ON user_accounts TO XBINOV00;
