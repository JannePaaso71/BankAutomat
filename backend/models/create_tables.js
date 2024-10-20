
let conn = require("../database");

/**
 * Call createTablesIfNotExists on application startup to create tables into database.
 */
createTablesIfNotExists = async () => {
    const sqlTables = [`
    CREATE TABLE IF NOT EXISTS Customers (
        id_customers INT PRIMARY KEY AUTO_INCREMENT,
        firstname VARCHAR(40),
        lastname VARCHAR(40)
    );`,
    `
    CREATE TABLE IF NOT EXISTS Accounts (
        id_accounts INT PRIMARY KEY AUTO_INCREMENT,
        saldo DECIMAL(15,2) NOT NULL ,
        credit_limit DECIMAL(15,2)
    );`,
    `
    CREATE TABLE IF NOT EXISTS UsersToAccounts (
        id_utoa INT PRIMARY KEY AUTO_INCREMENT,
        id_accounts INT NOT NULL,
        id_customers INT NOT NULL,
        owner BOOL NOT NULL,
        FOREIGN KEY (id_accounts) REFERENCES Accounts(id_accounts),
        FOREIGN KEY (id_customers) REFERENCES Customers(id_customers)
    );`,
    `
    CREATE TABLE IF NOT EXISTS Transactions (
        id_transactions INT PRIMARY KEY AUTO_INCREMENT,
        id_customers INT NOT NULL,
        id_account INT NOT NULL,
        date DATETIME NOT NULL ,
        amount DECIMAL(15,2) NOT NULL ,
        action ENUM('withdraw', 'deposit'),
        FOREIGN KEY (id_customers) REFERENCES Customers(id_customers),
        FOREIGN KEY (id_account) REFERENCES Accounts(id_accounts)
    );`,
    `
    CREATE TABLE IF NOT EXISTS Cards (
        id_cards INT PRIMARY KEY AUTO_INCREMENT,
        pin VARCHAR(255) ,
        id_customers INT NOT NULL ,
        FOREIGN KEY (id_customers) REFERENCES Customers(id_customers) ON DELETE CASCADE
    );`,
    `
    CREATE TABLE IF NOT EXISTS CardsToAccounts (
        id_ctoa INT PRIMARY KEY AUTO_INCREMENT,
        id_accounts INT NOT NULL ,
        id_cards INT NOT NULL,
        FOREIGN KEY (id_accounts) REFERENCES Accounts(id_accounts),
        FOREIGN KEY (id_cards) REFERENCES Cards(id_cards) ON DELETE CASCADE ON UPDATE CASCADE
    );`,
    `
    CREATE TABLE IF NOT EXISTS Operators (
        id_operators INT PRIMARY KEY AUTO_INCREMENT,
        username VARCHAR(25) NOT NULL UNIQUE,
        password VARCHAR(255) NOT NULL
    );`,
    ];
    let sqlProceduresAndFunctions = [
        // Create new bank card with either 1 or 2 bank accounts attached.

    
           `
CREATE PROCEDURE IF NOT EXISTS createCard(IN pin_code VARCHAR(255), IN owner_id INT, IN account_id0 INT, IN account_id1 INT,
                                          OUT success BOOLEAN, OUT new_card_id INT)
BEGIN
    DECLARE card_id INT;
    SET success = FALSE;

    IF account_id1 IS NULL THEN
        START TRANSACTION;
        INSERT INTO Cards(pin, id_customers) VALUES (pin_code, owner_id);
        SET card_id = LAST_INSERT_ID();
        SET new_card_id = card_id;
        INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id0);
        SET success = TRUE;
        COMMIT;
    ELSE
        IF checkValidAccountTypesForCard(account_id0, account_id1) THEN
            START TRANSACTION;
            INSERT INTO Cards(pin, id_customers) VALUES (pin_code, owner_id);
            SET card_id = LAST_INSERT_ID();
            SET new_card_id = card_id;
            INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id0);
            INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id1);
            SET success = TRUE;
            COMMIT;
        ELSE
            SET success = FALSE;
            SELECT success, 0;
        END IF;
    END IF;
END;
`, /* Update a card with new pin (HASH!) and associated bank account(s). */ `
CREATE PROCEDURE IF NOT EXISTS updateCard(IN card_id INT, IN owner_id INT, IN pin_code VARCHAR(255), IN account_id0 INT,
                                          IN account_id1 INT, OUT success BOOLEAN)
BEGIN
    IF cardExists(card_id) THEN
        IF account_id1 IS NULL THEN
            START TRANSACTION;
            UPDATE Cards SET pin=pin_code, id_customers=owner_id WHERE id_cards = card_id;
            DELETE FROM CardsToAccounts WHERE id_cards = card_id;
            INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id0);
            SET success = TRUE;
            COMMIT;
        ELSE
            IF checkValidAccountTypesForCard(account_id0, account_id1) THEN
                START TRANSACTION;
                UPDATE Cards SET pin=pin_code, id_customers=owner_id WHERE id_cards = card_id;
                DELETE FROM CardsToAccounts WHERE id_cards = card_id;
                INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id0);
                INSERT INTO CardsToAccounts(id_cards, id_accounts) VALUES (card_id, account_id1);
                SET success = TRUE;
                COMMIT;
            ELSE
                SET success = FALSE;
            END IF;
        END IF;
    ELSE
        SET success=FALSE;
    END IF;
END;`,`


/**
         * Created by Janne Paaso
         * Procedure below create new accounts if not exist already.
         */

CREATE PROCEDURE IF NOT EXISTS createAccount(IN customers_id INT, IN _saldo DECIMAL(15,2), IN _credit_limit DECIMAL(15,2),
                                              OUT success BOOLEAN, OUT new_account_id INT)
BEGIN
SET success = FALSE;
    IF customerExist(customers_id) THEN
        START TRANSACTION ;
        INSERT INTO Accounts(saldo, credit_limit) VALUES (_saldo, _credit_limit);
        SET new_account_id = LAST_INSERT_ID();
        INSERT INTO UsersToAccounts(id_accounts, id_customers, owner) VALUES (new_account_id, customers_id, TRUE);
        SET success = TRUE;
        COMMIT ;
    ELSE
        SET success = FALSE;
        SET new_account_id = 0;
    END IF;
END;`,`


/**
         * Created by Janne Paaso
         * Function below check that id_customer exists.
         */

CREATE FUNCTION IF NOT EXISTS customerExist(customers_id INT)
RETURNS BOOLEAN
BEGIN
    DECLARE result_id INT;
    SELECT id_customers INTO result_id FROM Customers WHERE id_customers=customers_id;
    IF (result_id > 0) THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;`,`

CREATE FUNCTION IF NOT EXISTS checkValidAccountTypesForCard(acc_id_1 INT, acc_id_2 INT)
RETURNS BOOLEAN
BEGIN
    DECLARE acc_1_type DECIMAL(15,2);
    DECLARE acc_2_type DECIMAL(15,2);

    SELECT credit_limit INTO acc_1_type FROM Accounts WHERE id_accounts=acc_id_1;
    SELECT credit_limit INTO acc_2_type FROM Accounts WHERE id_accounts=acc_id_2;
    IF (acc_1_type IS NULL AND acc_2_type IS NULL) OR (acc_1_type IS NOT NULL AND acc_2_type IS NOT NULL) THEN
        RETURN FALSE;
    ELSE
        RETURN TRUE;
    END IF;
END;`,`

CREATE FUNCTION IF NOT EXISTS cardExists(card_id INT)
RETURNS BOOLEAN
BEGIN
    DECLARE result_id INT;
    SELECT id_cards INTO result_id FROM Cards WHERE id_cards=card_id;
    IF (result_id > 0) THEN
        RETURN TRUE;
    ELSE
        RETURN FALSE;
    END IF;
END;

/**
         * // Function to verify that each account to be associated with a card are of different type (credit/debit).
         * Procedure below gets account types for a card (for sequence diagram for choose account).
         */
`, ` 

CREATE PROCEDURE IF NOT EXISTS getAccountTypes( IN card_id INT,
                                                OUT card1_type ENUM('none', 'debit', 'credit'),
                                                OUT card2_type ENUM('none', 'debit', 'credit'),
                                                OUT success BOOL)
BEGIN
    DECLARE account_count INT;

    SELECT COUNT(*) INTO account_count FROM CardsToAccounts WHERE id_cards=card_id;
    IF (account_count = 2) THEN
        SET card1_type = 'debit';
        SET card2_type = 'credit';
        SET success = TRUE;

        ELSE IF (account_count = 1) THEN
            SET card1_type = 'debit';
            SET card2_type = 'none';
            SET success = TRUE;
        ELSE
            SET success = FALSE;
        END IF;
    END IF;
END;
        `,`
        
CREATE PROCEDURE IF NOT EXISTS getBalance(  IN _card_id INT, IN _card_type ENUM('debit', 'credit'),
                                            OUT _balance DECIMAL(15,2), OUT _credit_limit DECIMAL(15,2))
BEGIN
IF (_card_type = 'debit') THEN
    SELECT saldo, credit_limit
    INTO _balance, _credit_limit
    FROM CardsToAccounts CA JOIN Accounts A
        ON CA.id_accounts = A.id_accounts
    WHERE CA.id_cards=_card_id AND credit_limit IS NULL;
ELSE
    SELECT saldo, credit_limit
    INTO _balance, _credit_limit
    FROM CardsToAccounts CA JOIN Accounts A
        ON CA.id_accounts = A.id_accounts
    WHERE CA.id_cards=_card_id AND credit_limit IS NOT NULL;
END IF;
END;
        `,`
CREATE FUNCTION IF NOT EXISTS getAccount(_card_id INT, credit_or_debit ENUM('debit', 'credit'))
RETURNS INT
BEGIN
    DECLARE account_number INT;

    IF (credit_or_debit = 'credit') THEN
        SELECT A.id_accounts
            FROM CardsToAccounts C JOIN Accounts A
            ON A.id_accounts = C.id_accounts
            WHERE C.id_cards=_card_id AND A.credit_limit IS NOT NULL
            INTO account_number;
    ELSE
        SELECT A.id_accounts
            FROM CardsToAccounts C JOIN Accounts A
            ON A.id_accounts = C.id_accounts
            WHERE C.id_cards=_card_id AND A.credit_limit IS NULL
            INTO account_number;
    END IF;
    return account_number;
END;`

        /**
         * Procedure below gets request to withraw money and the type of account. The procedeure cheks that the 
         * account has enough money and implements the transaction if there is. If there is not enough money, the provcedure returns fault.
         */

// ALKAA RAHAN NOSTO FUNKTIOT JA PROSEDUURIT

,`

CREATE PROCEDURE IF NOT EXISTS withdrawal(IN _card_id INT, IN _credit_or_debit ENUM('debit', 'credit'), IN _amount DECIMAL(15,2),
                                          OUT _success BOOL)
BEGIN
DECLARE _balance DECIMAL(15,2);
DECLARE _credit_limit DECIMAL(15,2);
DECLARE _account_id INT;
DECLARE _action_type ENUM("withdraw","deposit");

START TRANSACTION;
SET _account_id = getAccount(_card_id, _credit_or_debit);
SELECT A.saldo, A.credit_limit FROM Accounts A
        WHERE A.id_accounts=_account_id
        INTO _balance, _credit_limit;
IF (_credit_limit IS NOT null AND _credit_limit + _balance >= _amount) THEN
    IF (_amount >= 0) THEN SET _action_type = "withdraw"; ELSE SET _action_type = "deposit"; END IF;
    UPDATE Accounts A SET A.saldo=A.saldo-_amount WHERE A.id_accounts=_account_id;
    INSERT INTO Transactions(id_customers,id_account,date, amount, action) 
        VALUES((SELECT id_customers FROM Cards WHERE id_cards = _card_id),
        getAccount(_card_id, _credit_or_debit), NOW(), _amount, _action_type);
    SET _success = TRUE;
    COMMIT;
ELSEIF (_balance >= _amount) THEN
IF (_amount >= 0) THEN SET _action_type = "withdraw"; ELSE SET _action_type = "deposit"; END IF;
    UPDATE Accounts A SET A.saldo=A.saldo-_amount WHERE A.id_accounts=_account_id;
INSERT INTO Transactions(id_customers,id_account,date, amount, action) 
    VALUES((SELECT id_customers FROM Cards WHERE id_cards = _card_id),
    getAccount(_card_id, _credit_or_debit), NOW(), _amount, _action_type);    
    
    SET _success = TRUE;
    COMMIT;
ELSE
    SET _success = FALSE;
    ROLLBACK ;
END IF;
COMMIT;
END;`

// Lisää tapahtumat transactioihin -> rivillä 243 UPdaten perään.

    ];
    sqlTables.forEach(stmt => {
        conn.execute(stmt, (error, result, fields) => {
            if (error) {
                console.log("Creating tables: ERROR: " + error);
            }
        });
    });
    sqlProceduresAndFunctions.forEach(stmt => {
        conn.query(stmt, (error, result) => {
            if (error) {
                console.log("Creating procedures: ERROR: " + error);
            }
        });
    });
}

module.exports = createTablesIfNotExists;


       