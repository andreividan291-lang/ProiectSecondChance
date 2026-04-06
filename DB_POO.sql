USE DB_POO;
DROP TABLE IF EXISTS Utilizatori

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
    id_in_app INT NOT NULL,
    email VARCHAR(100) NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt NVARCHAR(256) NOT NULL,
    nume VARCHAR(255) NOT NULL,
    nivel INT NOT NULL DEFAULT 1 -- nivel permisiune
);

SELECT * FROM Utilizatori;

