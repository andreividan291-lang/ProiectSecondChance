USE DB_POO

SELECT * FROM Admini

SELECT * FROM Utilizatori

SELECT * FROM Produse

SELECT * FROM Favorite

SELECT * FROM 

-- ══════════════════════════════════════════════════════
-- Produse pentru Userul 1 (a@.com)
-- ══════════════════════════════════════════════════════
INSERT INTO Produse (id_vanzator, nume, descriere, pret, categorie, stare) VALUES
(1, 'Adidas Samba', 'Adidasi clasici albi, marimea 42', 250.00, 'Incaltaminte', 'Folosit'),
(1, 'Nike Air Force', 'Pereche noua, cutie originala, marimea 41', 400.00, 'Incaltaminte', 'Nou'),
(1, 'Geaca Zara', 'Geaca de toamna, marimea M, culoare negru', 150.00, 'Imbracaminte', 'Folosit'),
(1, 'Bluza H&M', 'Bluza casual albastru deschis, marimea L', 60.00, 'Imbracaminte', 'Nou'),
(1, 'Pantaloni Bershka', 'Pantaloni slim fit negri, marimea 32', 90.00, 'Imbracaminte', 'Folosit');

-- ══════════════════════════════════════════════════════
-- Produse pentru Userul 2 (b@.com)
-- ══════════════════════════════════════════════════════
INSERT INTO Produse (id_vanzator, nume, descriere, pret, categorie, stare) VALUES
(2, 'Converse All Star', 'Tenisi negri marimea 40, putin purtati', 180.00, 'Incaltaminte', 'Folosit'),
(2, 'Botine din piele', 'Botine maro, marimea 38, stare foarte buna', 320.00, 'Incaltaminte', 'Reconditionat'),
(2, 'Rochie eleganta', 'Rochie de seara rosie, marimea S', 200.00, 'Imbracaminte', 'Nou'),
(2, 'Tricou Tommy Hilfiger', 'Tricou alb logo Tommy, marimea M', 110.00, 'Imbracaminte', 'Folosit'),
(2, 'Papuci Nike', 'Papuci de casa Nike, marimea 43', 80.00, 'Incaltaminte', 'Nou');

-- ══════════════════════════════════════════════════════
-- Produse pentru Userul 3 (c@.com)
-- ══════════════════════════════════════════════════════
INSERT INTO Produse (id_vanzator, nume, descriere, pret, categorie, stare) VALUES
(3, 'Vans Old Skool', 'Vans negri marimea 39, folositi 3 luni', 160.00, 'Incaltaminte', 'Folosit'),
(3, 'Puma Suede', 'Adidasi Puma gri marimea 44, noi in cutie', 290.00, 'Incaltaminte', 'Nou'),
(3, 'Jacheta Pull&Bear', 'Jacheta denim albastra marimea L', 130.00, 'Imbracaminte', 'Folosit'),
(3, 'Fusta Mango', 'Fusta plisata bej marimea S, purtata o data', 95.00, 'Imbracaminte', 'Folosit'),
(3, 'Camasa Reserved', 'Camasa in carouri rosu/alb marimea XL', 75.00, 'Imbracaminte', 'Nou');

-- Verificare
SELECT p.id, p.nume, p.categorie, p.pret, p.stare, p.poza_cale, u.email as vanzator
FROM Produse p
INNER JOIN Utilizatori u ON u.id = p.id_vanzator
ORDER BY p.id_vanzator, p.categorie;
	
	UPDATE Produse 
SET poza_cale = 'D:\Poze_Produse_POO\nike.jpg'
WHERE nume = 'Nike Air Force';
