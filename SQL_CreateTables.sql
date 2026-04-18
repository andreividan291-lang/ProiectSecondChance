USE DB_POO
GO

DROP TABLE IF EXISTS Utilizatori
DROP TABLE IF EXISTS Admini
DROP TABLE IF EXISTS Produse

CREATE TABLE Utilizatori (
    id INT PRIMARY KEY IDENTITY(1,1),  
    email VARCHAR(100) NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt NVARCHAR(256) NOT NULL,
    nume VARCHAR(255) NOT NULL,
    prenume VARCHAR(255) NOT NULL,
    telefon VARCHAR(255) NOT NULL,
    bio VARCHAR(255),
    portofel DECIMAL(10,2) NOT NULL DEFAULT 0
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

CREATE TABLE Produse (
    id              INT IDENTITY(1,1) PRIMARY KEY,
    id_vanzator     INT            NOT NULL,
    nume            NVARCHAR(200)  NOT NULL,
    descriere       NVARCHAR(MAX)  NULL,
    poza_cale       NVARCHAR(500)  NULL,          -- calea relativa pe server, ex: "uploads/produse/abc.jpg"
    pret            DECIMAL(10,2)  NOT NULL CHECK (pret >= 0),
    categorie       NVARCHAR(100)  NOT NULL,
    stare           NVARCHAR(50)   NOT NULL DEFAULT 'Nou'
                        CHECK (stare IN ('Nou', 'Folosit', 'Reconditionat')),  
    data_listare    DATETIME       NOT NULL DEFAULT GETDATE(),

    CONSTRAINT FK_Produse_Utilizatori
        FOREIGN KEY (id_vanzator) REFERENCES Utilizatori(id)
        ON DELETE CASCADE
);

-- Index pentru cautare rapida dupa vanzator
CREATE INDEX IX_Produse_Vanzator ON Produse(id_vanzator);

-- Index pentru cautare dupa categorie
CREATE INDEX IX_Produse_Categorie ON Produse(categorie);