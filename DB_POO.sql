USE DB_POO;

DROP TABLE IF EXISTS Utilizatori
DROP TABLE IF EXISTS Admini

CREATE TABLE Utilizatori (
    id INT PRIMARY KEY IDENTITY(1,1),  
    id_in_app INT NOT NULL,          
    email VARCHAR(100) NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt NVARCHAR(256) NOT NULL,
    nume VARCHAR(255) NOT NULL,
    prenume VARCHAR(255) NOT NULL,
    telefon VARCHAR(255) NOT NULL,
    bio VARCHAR(255)
);

CREATE TABLE Admini (
    id INT PRIMARY KEY IDENTITY(1,1),
    email VARCHAR(100) NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt NVARCHAR(256) NOT NULL,
    nume VARCHAR(255) NOT NULL,
    prenume VARCHAR(255) NOT NULL,
    cod_personal VARCHAR(255) NOT NULL,
    nivel INT NOT NULL DEFAULT 1 -- nivel permisiune
);


INSERT INTO Admini (email, password_hash, salt, nume, prenume, cod_personal, nivel)
VALUES (
    'ad1@gmail.com',
    '961b6dd3ede3cb8ecbaacbd68de040cd78eb2ed5889130cceb4c49268ea4d506',   -- înlocuiește cu output-ul din qDebug
    'a',
    'Popescu',
    'Ion',
    '1',
    1
);


INSERT INTO Admini (email, password_hash, salt, nume, prenume, cod_personal, nivel)
VALUES (
    'ad2@gmail.com',
    '961b6dd3ede3cb8ecbaacbd68de040cd78eb2ed5889130cceb4c49268ea4d506',   -- înlocuiește cu output-ul din qDebug
    'a',
    'Florin',
    'Mihalache',
    '1',
    1
);

INSERT INTO Admini (email, password_hash, salt, nume, prenume, cod_personal, nivel)
VALUES (
    'ad3@gmail.com',
    '961b6dd3ede3cb8ecbaacbd68de040cd78eb2ed5889130cceb4c49268ea4d506',   -- înlocuiește cu output-ul din qDebug
    'a',
    'Mihaela',
    'Preda',
    '2',
    1
);


SELECT * FROM Admini;
