CREATE TABLE Student(
    Rno INT,
    Student_Name varchar(20),
    Dob DATE,
    Gender VARCHAR(10),
    Class VARCHAR(10),
    College VARCHAR(20),
    City VARCHAR(20),
    Marks INT,
    PRIMARY KEY(Rno)
);

INSERT INTO Student (Rno, Student_Name, Dob, Gender, Class, College, City, Marks)
VALUES
    (1, "Student 1", STR_TO_DATE('02-08-2002', '%m-%d-%Y'), "Male", "OS", "College", "Amritsar", 90),
    (2, "Student 2", STR_TO_DATE('03-06-2002', '%m-%d-%Y'), "Female", "DBMS", "College2", "Patiala", 91),
    (3, "Student 3", STR_TO_DATE('03-05-2002', '%m-%d-%Y'), "Male", "AI", "College3", "city3", 22),
    (9, "Student 4", STR_TO_DATE('05-06-2003', '%m-%d-%Y'), "Female", "DS", "College4", "city4", 28),
    (5, "Student 5", STR_TO_DATE('06-09-2003','%m-%d-%Y'), "Male", "DC", "College5", "Amritsar", 82);
