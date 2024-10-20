
CREATE DATABASE IF NOT EXISTS ATM_T;
USE ATM_T;

CREATE TABLE Customers (
    id_customers INT PRIMARY KEY AUTO_INCREMENT,
    firstname VARCHAR(40),
    lastname VARCHAR(40)
);

CREATE TABLE Accounts (
    id_accounts INT PRIMARY KEY AUTO_INCREMENT,
    saldo DECIMAL(15,2) NOT NULL ,
    credit_limit DECIMAL(15,2)
);

CREATE TABLE UsersToAccounts (
    id_utoa INT PRIMARY KEY AUTO_INCREMENT,
    id_accounts INT NOT NULL,
    id_customers INT NOT NULL,
    owner BOOL NOT NULL,
    FOREIGN KEY (id_accounts) REFERENCES Accounts(id_accounts),
    FOREIGN KEY (id_customers) REFERENCES Customers(id_customers)
);

CREATE TABLE Transactions (
    id_transactions INT PRIMARY KEY AUTO_INCREMENT,
    id_customers INT NOT NULL,
    id_account INT NOT NULL,
    date DATETIME NOT NULL ,
    amount DECIMAL(15,2) NOT NULL ,
    action ENUM('withdraw', 'deposit'),
    FOREIGN KEY (id_customers) REFERENCES Customers(id_customers),
    FOREIGN KEY (id_account) REFERENCES Accounts(id_accounts)
);

CREATE TABLE Cards (
    id_cards INT PRIMARY KEY AUTO_INCREMENT,
    pin VARCHAR(255)
);

CREATE TABLE CardsToAccounts (
    id_ctoa INT PRIMARY KEY AUTO_INCREMENT,
    id_accounts INT NOT NULL ,
    id_cards INT NOT NULL,
    FOREIGN KEY (id_accounts) REFERENCES Accounts(id_accounts),
    FOREIGN KEY (id_cards) REFERENCES Cards(id_cards)
);

CREATE TABLE Operators (
    id_operators INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(25) NOT NULL UNIQUE,
    password VARCHAR(255) NOT NULL
)