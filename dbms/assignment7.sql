USE dbmsLab;
DROP TABLE IF EXISTS Orders;
DROP TABLE IF EXISTS Customers;
DROP TABLE IF EXISTS SalesPeople;
FLUSH TABLES Orders, Customers, SalesPeople;

CREATE TABLE SalesPeople (
Snum INT NOT NULL,
Sname VARCHAR(255) UNIQUE NOT NULL,
City VARCHAR(255) NOT NULL,
Comm DECIMAL(10,2) NOT NULL,
PRIMARY KEY (Snum)
);

INSERT INTO SalesPeople (Snum, Sname, City, Comm) VALUES
(1001, 'Peel', 'London', .12),
(1002, 'Serres', 'Sanjose', .13),
(1004, 'Motika', 'Landon', .11),
(1007, 'Rifkin', 'Barcelona', .15),
(1003, 'Axelrod', 'Newyork', .10);


CREATE TABLE Customers (
  Cnum INT NOT NULL,
  Cname VARCHAR(255) NOT NULL,
  City VARCHAR(255) NOT NULL,
  Snum INT NOT NULL,
  PRIMARY KEY (Cnum),
  FOREIGN KEY (Snum) REFERENCES SalesPeople(Snum)
);

INSERT INTO Customers (Cnum, Cname, City, Snum) VALUES
(2001, 'Hoffman', 'London', 1001),
(2002, 'Giovanni', 'Rome', 1003),
(2003, 'Liu', 'Sanjose', 1002),
(2004, 'Grass', 'Berlin', 1002),
(2006, 'Clemens', 'London', 1001),
(2008, 'Cisneros', 'Sanjose', 1007),
(2007, 'Pereira', 'Rome', 1004);


CREATE TABLE Orders (
  Onum INT NOT NULL,
  Amt DECIMAL(10,2) NOT NULL,
  Odate DATE NOT NULL,
  Cnum INT NOT NULL,
  Snum INT NOT NULL,
  PRIMARY KEY (Onum),
  FOREIGN KEY (Cnum) REFERENCES Customers(Cnum),
  FOREIGN KEY (Snum) REFERENCES SalesPeople(Snum)
);

INSERT INTO Orders (Onum, Amt, Odate, Cnum, Snum) VALUES
(3001, 18.69, '1990-10-03', 2008, 1007),
(3003, 767.19, '1990-10-03', 2001, 1001),
(3002, 1900.10, '1990-10-03', 2007, 1004),
(3005, 5160.45, '1990-10-03', 2003, 1002),
(3006, 1098.16, '1990-10-03', 2008, 1007),
(3009, 1713.23, '1990-10-04', 2002, 1003),
(3007, 75.75, '1990-10-04', 2004, 1002),
(3008, 4273.00, '1990-10-05', 2006, 1001),
(3010, 1309.95, '1990-10-06', 2004, 1002),
(3011, 9891.88, '1990-10-06', 2006, 1001);


SELECT * FROM SalesPeople;
SELECT * FROM Customers;
SELECT * FROM Orders;

-- output of 2 and 4 are somewhat wrong

-- 1.) With and without Subquery
SELECT DISTINCT Sname FROM SalesPeople WHERE City IN (SELECT DISTINCT City FROM Customers);
SELECT DISTINCT Sname FROM SalesPeople JOIN Customers ON SalesPeople.City = Customers.City;

-- 2.) With and without Subquery
SELECT Sname, Cname FROM SalesPeople INNER JOIN Customers ON SalesPeople.Snum = Customers.Snum
WHERE SalesPeople.City IN (SELECT DISTINCT City FROM Customers);

SELECT Sname, Cname FROM SalesPeople JOIN Customers ON SalesPeople.City = Customers.City;

-- 3.) With and without Subquery
SELECT Sname FROM SalesPeople WHERE 
City IN (SELECT City FROM Customers WHERE SalesPeople.Snum = Customers.Snum);

SELECT DISTINCT Sname FROM 
SalesPeople JOIN Customers ON 
SalesPeople.Snum = Customers.Snum 
WHERE SalesPeople.City = Customers.City;


-- 4.) using corelated subquery
SELECT SP.Sname, C.Cname
FROM SalesPeople SP
JOIN Customers C ON SP.Snum = C.Snum
WHERE EXISTS (
    SELECT 1
    FROM Customers C2
    WHERE C2.City = SP.City AND C2.Snum = SP.Snum
);

-- 5.)
SELECT SP.Sname, C.Cname
FROM SalesPeople SP
JOIN Customers C ON SP.Snum = C.Snum;

SELECT SP.Sname
FROM SalesPeople SP
WHERE SP.Snum NOT IN (SELECT C.Snum FROM Customers C);

-- 6.)
SELECT Cname
FROM Customers
WHERE Snum IS NULL;

-- 7.)
SELECT Snum, MAX(Amt)
FROM Orders
GROUP BY Snum;

-- 8.)
SELECT SP.Sname, MAX(O.Amt)
FROM SalesPeople SP
JOIN Orders O ON SP.Snum = O.Snum
GROUP BY SP.Snum;

-- 9.)
SELECT O.Snum, O.Onum, O.Amt
FROM Orders O
WHERE O.Amt > (SELECT AVG(O2.Amt) FROM Orders O2 WHERE O2.Snum = O.Snum);

-- 10.)
SELECT SP.Sname
FROM SalesPeople SP
WHERE (SELECT COUNT(*) FROM Customers C WHERE C.Snum = SP.Snum) > 2;


