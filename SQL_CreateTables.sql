USE master
GO

DROP DATABASE DB_POO
GO

CREATE DATABASE DB_POO
GO

USE DB_POO
GO

CREATE TABLE Utilizatori (
    id            INT           PRIMARY KEY IDENTITY(1,1),
    email         VARCHAR(100)  NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt          NVARCHAR(256) NOT NULL,
    nume          VARCHAR(255)  NOT NULL,
    prenume       VARCHAR(255)  NOT NULL,
    telefon       VARCHAR(255)  NOT NULL,
    bio           VARCHAR(255)  NULL,
    portofel      DECIMAL(10,2) NOT NULL DEFAULT 0
);

CREATE TABLE Admini (
    id            INT           PRIMARY KEY IDENTITY(1,1),
    email         VARCHAR(100)  NOT NULL UNIQUE,
    password_hash NVARCHAR(256) NOT NULL,
    salt          NVARCHAR(256) NOT NULL,
    nume          VARCHAR(255)  NOT NULL,
    prenume       VARCHAR(255)  NOT NULL,
    cod_personal  VARCHAR(255)  NOT NULL,
    nivel         INT           NOT NULL DEFAULT 1
);

CREATE TABLE Produse (
    id           INT            PRIMARY KEY IDENTITY(1,1),
    id_vanzator  INT            NOT NULL,
    nume         NVARCHAR(200)  NOT NULL,
    descriere    NVARCHAR(MAX)  NULL,
    poza_cale    NVARCHAR(500)  NULL,
    pret         DECIMAL(10,2)  NOT NULL CHECK (pret >= 0),
    categorie    NVARCHAR(100)  NOT NULL,
    stare        NVARCHAR(50)   NOT NULL DEFAULT 'Nou'
                     CHECK (stare IN ('Nou', 'Folosit', 'Reconditionat')),
    vandut       BIT            NOT NULL DEFAULT 0,
    data_listare DATETIME       NOT NULL DEFAULT GETDATE(),
    CONSTRAINT FK_Produse_Utilizatori
        FOREIGN KEY (id_vanzator) REFERENCES Utilizatori(id)
        ON DELETE CASCADE
);

CREATE TABLE Favorite (
    id            INT      PRIMARY KEY IDENTITY(1,1),
    id_user       INT      NOT NULL,
    id_produs     INT      NOT NULL,
    data_adaugare DATETIME NOT NULL DEFAULT GETDATE(),
    CONSTRAINT FK_Fav_User   FOREIGN KEY (id_user)   REFERENCES Utilizatori(id) ON DELETE CASCADE,
    CONSTRAINT FK_Fav_Produs FOREIGN KEY (id_produs) REFERENCES Produse(id),
    CONSTRAINT UQ_Fav        UNIQUE (id_user, id_produs)
);

CREATE TABLE Comenzi (
    id            INT         PRIMARY KEY IDENTITY(1,1),
    cumparator_id INT         NOT NULL,
    vanzator_id   INT         NOT NULL,
    produs_id     INT         NOT NULL,
    status        VARCHAR(50) NOT NULL DEFAULT 'finalizata',
    data_comanda  DATETIME    NOT NULL DEFAULT GETDATE(),
    CONSTRAINT FK_Comenzi_Cumparator FOREIGN KEY (cumparator_id) REFERENCES Utilizatori(id),
    CONSTRAINT FK_Comenzi_Vanzator   FOREIGN KEY (vanzator_id)   REFERENCES Utilizatori(id),
    CONSTRAINT FK_Comenzi_Produs     FOREIGN KEY (produs_id)     REFERENCES Produse(id)
);

CREATE TABLE Review_uri (
    id            INT            PRIMARY KEY IDENTITY(1,1),
    comanda_id    INT            NOT NULL UNIQUE,
    cumparator_id INT            NOT NULL,
    vanzator_id   INT            NOT NULL,
    nota          INT            NOT NULL CHECK (nota BETWEEN 1 AND 5),
    comentariu    NVARCHAR(1000) NULL,
    data_review   DATETIME       NOT NULL DEFAULT GETDATE(),
    CONSTRAINT FK_Review_Comanda    FOREIGN KEY (comanda_id)    REFERENCES Comenzi(id),
    CONSTRAINT FK_Review_Cumparator FOREIGN KEY (cumparator_id) REFERENCES Utilizatori(id),
    CONSTRAINT FK_Review_Vanzator   FOREIGN KEY (vanzator_id)   REFERENCES Utilizatori(id)
);

CREATE TABLE Notificari (
    id          INT           PRIMARY KEY IDENTITY(1,1),
    id_user     INT           NOT NULL,
    mesaj       NVARCHAR(500) NOT NULL,
    citita      BIT           NOT NULL DEFAULT 0,
    data        DATETIME      NOT NULL DEFAULT GETDATE(),
    CONSTRAINT FK_Notificari_User FOREIGN KEY (id_user) REFERENCES Utilizatori(id) ON DELETE CASCADE
);

GO

CREATE INDEX IX_Produse_Vanzator  ON Produse(id_vanzator);
CREATE INDEX IX_Produse_Categorie ON Produse(categorie);

GO

CREATE PROCEDURE sp_GetProduseClient
    @id_utilizator INT,
    @text_cautare  NVARCHAR(200) = NULL,
    @categorie     NVARCHAR(100) = NULL
AS
BEGIN
    SET NOCOUNT ON;

    SELECT
        p.id,
        p.nume,
        p.pret,
        p.categorie,
        p.stare,
        p.vandut,
        p.[data_listare],
        u.nume + ' ' + u.prenume AS vanzator,
        u.id AS id_vanzator
    FROM Produse p
    INNER JOIN Utilizatori u ON u.id = p.id_vanzator
    WHERE
        p.id_vanzator <> @id_utilizator
        AND p.vandut = 0
        AND (@text_cautare IS NULL OR p.nume LIKE '%' + @text_cautare + '%')
        AND (@categorie    IS NULL OR p.categorie LIKE '%' + @categorie + '%')
    ORDER BY p.[data_listare] DESC;
END
GO

ALTER TABLE Produse
ADD CONSTRAINT CHK_Produse_Categorie
CHECK (categorie IN ('Incaltaminte', 'Imbracaminte'));

USE DB_POO
GO
EXEC sp_GetProduseClient @id_utilizator = 1

SELECT p.id, p.id_vanzator, p.vandut FROM Produse p

USE DB_POO
GO

CREATE VIEW vw_NotaVanzatori AS
SELECT 
    vanzator_id,
    COUNT(*) AS nr_review_uri,
    CAST(AVG(CAST(nota AS FLOAT)) AS DECIMAL(3,1)) AS nota_medie
FROM Review_uri
GROUP BY vanzator_id;
GO

SELECT * FROM vw_NotaVanzatori
