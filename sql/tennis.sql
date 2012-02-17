CREATE   TABLE PLAYERS
        (PLAYERNO       INTEGER      NOT NULL,
         NAME           CHAR(15)     NOT NULL,
         INITIALS       CHAR(3)      NOT NULL,
         BIRTH_DATE     DATE                 ,
         SEX            CHAR(1)      NOT NULL,
         JOINED         SMALLINT     NOT NULL,
         STREET         VARCHAR(30)  NOT NULL,
         HOUSENO        CHAR(4)              ,
         POSTCODE       CHAR(6)              ,
         TOWN           VARCHAR(30)  NOT NULL,
         PHONENO        CHAR(13)             ,
         LEAGUENO       CHAR(4)              ,
         PRIMARY KEY    (PLAYERNO)           );

CREATE   TABLE TEAMS
        (TEAMNO         INTEGER      NOT NULL,
         PLAYERNO       INTEGER      NOT NULL,
         DIVISION       CHAR(6)      NOT NULL,
         PRIMARY KEY    (TEAMNO)             );

CREATE   TABLE MATCHES
        (MATCHNO        INTEGER      NOT NULL,
         TEAMNO         INTEGER      NOT NULL,
         PLAYERNO       INTEGER      NOT NULL,
         WON            SMALLINT     NOT NULL,
         LOST           SMALLINT     NOT NULL,
         PRIMARY KEY    (MATCHNO)            );

CREATE   TABLE PENALTIES
        (PAYMENTNO      INTEGER      NOT NULL,
         PLAYERNO       INTEGER      NOT NULL,
         PAYMENT_DATE   DATE         NOT NULL,
         AMOUNT         DECIMAL(7,2) NOT NULL,
         PRIMARY KEY    (PAYMENTNO)          );

CREATE   TABLE COMMITTEE_MEMBERS
        (PLAYERNO       INTEGER      NOT NULL,
         BEGIN_DATE     DATE         NOT NULL,
         END_DATE       DATE                 ,
         POSITION       CHAR(20)             ,
         PRIMARY KEY    (PLAYERNO, BEGIN_DATE));
