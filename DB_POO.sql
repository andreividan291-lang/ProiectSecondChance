-- ============================================================
--  Second Chance - Baza de date
--  Ruleaza in MySQL / SSMS (MySQL Workbench / phpMyAdmin)
-- ============================================================

CREATE DATABASE IF NOT EXISTS second_chance
    CHARACTER SET utf8mb4
    COLLATE utf8mb4_unicode_ci;

USE second_chance;

-- ------------------------------------------------------------
--  Tabela utilizatori  (profil public)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS utilizatori (
    id          INT          NOT NULL AUTO_INCREMENT,
    nume        VARCHAR(100) NOT NULL,
    rol         ENUM('admin', 'client') NOT NULL DEFAULT 'client',
    creat_la    DATETIME     NOT NULL DEFAULT CURRENT_TIMESTAMP,

    PRIMARY KEY (id)
);

-- ------------------------------------------------------------
--  Tabela conturi  (autentificare)
-- ------------------------------------------------------------
CREATE TABLE IF NOT EXISTS conturi (
    id              INT          NOT NULL AUTO_INCREMENT,
    utilizator_id   INT          NOT NULL,
    email           VARCHAR(150) NOT NULL,
    parola_hash     VARCHAR(255) NOT NULL,
    salt            VARCHAR(64)  NOT NULL,
    activ           TINYINT(1)   NOT NULL DEFAULT 1,

    PRIMARY KEY (id),
    UNIQUE  KEY uk_email (email),
    FOREIGN KEY (utilizator_id)
        REFERENCES utilizatori(id)
        ON DELETE CASCADE
        ON UPDATE CASCADE
);

-- ------------------------------------------------------------
--  Date de test  (parola: "Test1234!")
--  salt si hash generate cu SHA-256 in Qt - vezi DatabaseManager
-- ------------------------------------------------------------
INSERT INTO utilizatori (nume, rol) VALUES
    ('Admin SecondChance', 'admin'),
    ('Ion Popescu',        'client');

INSERT INTO conturi (utilizator_id, email, parola_hash, salt, activ) VALUES
    (1, 'admin@secondchance.ro',
        '5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8',
        'salt_admin_placeholder',
        1),
    (2, 'ion.popescu@email.com',
        '5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8',
        'salt_client_placeholder',
        1);
