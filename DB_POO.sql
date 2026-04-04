USE DB_POO;
DROP TABLE IF EXISTS Utilizatori

CREATE TABLE Utilizatori (
    id INT PRIMARY KEY IDENTITY(1,1),
    email VARCHAR(100) NOT NULL UNIQUE,
    parola VARCHAR(255) NOT NULL,
    nume VARCHAR(255) NOT NULL,
    prenume VARCHAR(255) NOT NULL,
    telefon VARCHAR(255) NOT NULL,
    bio VARCHAR(255)
    --tip_utilizator VARCHAR(255) NOT NULL
);

SELECT * FROM Utilizatori;