CREATE TABLE IF NOT EXISTS Agent(
    AgentID INT PRIMARY KEY,
    Salary INT CHECK (salary >= 0),
    AName VARCHAR(50),
    Email VARCHAR(50),
    PhoneNum CHAR(10)
);

CREATE TABLE IF NOT EXISTS CallCentres(
    CallCentreID INT PRIMARY KEY,
    CCAddress CHAR(200),
    ManagerName CHAR(50),
    PhoneLineCount INT
);

CREATE TABLE IF NOT EXISTS WorksIn(
    AgentID INT PRIMARY KEY,
    CallCentreID INT,
    StartDate DATE NOT NULL,
    EndDate DATE,
    FOREIGN KEY (AgentID) REFERENCES Agent,
    FOREIGN KEY (CallCentreID) REFERENCES CallCentres
);

CREATE TABLE IF NOT EXISTS Training(
    ModuleNum INT PRIMARY KEY,
    TLength INT,
    TName CHAR(50) UNIQUE
);

CREATE TABLE IF NOT EXISTS TrainingCompletion(
    AgentID INT,
    ModuleNum INT,
    CompletionDate DATE,
    PRIMARY KEY (AgentID, ModuleNum),
    FOREIGN KEY (AgentID) REFERENCES Agent ON DELETE CASCADE,
    FOREIGN KEY (ModuleNum) REFERENCES Training
);



INSERT INTO CallCentres (CallCentreID, CCAddress, ManagerName, PhoneLineCount)
    VALUES (1000, '452 Burrard Street Vancouver BC Canada', 'Eric Wu', 663);

INSERT INTO CallCentres (CallCentreID, CCAddress, ManagerName, PhoneLineCount)
    VALUES (1001, '665-4462 Yonge Street Toronto ON Canada', 'Matthew Williams', 993);

INSERT INTO CallCentres (CallCentreID, CCAddress, ManagerName, PhoneLineCount)
    VALUES (1002, '33 14th Ave Calgary AB Canada', 'Jake Jones', 243);

INSERT INTO CallCentres (CallCentreID, CCAddress, ManagerName, PhoneLineCount)
    VALUES (1003, '664 Peel Street Montreal QC Canada', 'Juliette Gagnon', 318);

INSERT INTO CallCentres (CallCentreID, CCAddress, ManagerName, PhoneLineCount)
    VALUES (1004, '98 Main Street Edmonton AB Canada', 'Ashley Williams', 65);



INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (1, 60000, 'Bob Johnson', 'bobbyj@gmail.com', '6049552424');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (2, 45250, 'Michael Smith', 'msmith@gmail.com', '7781331328');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (3, 54500, 'Jeng Quon', 'jiq1989@gmail.com', '7809902212');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (4, 72400, 'Ashley Jones', 'batwomengirlz@gmail.com', '4163412322');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (5, 57000, 'Erika Brians', 'brianserika@hotmail.com', '6134383498');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (6, 61000, 'Emma Watson', 'hermione@outlook.com', '9057760862');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (7, 39000, 'Eldrick Woods', 'tigergolf@gmail.com', '4032256766');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (8, 73000, 'Guy Lafleur', 'flower10@gmail.com', '6049554567');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (9, 47800, 'Montgomery Burns', 'montybnuclear@springfield.com', '6137786945');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (10, 45200, 'Ringo Starr', 'drummerboy@gmail.com', '9059987272');

INSERT INTO Agent (AgentID, Salary, AName, Email, PhoneNum)
    VALUES (11, 61000, 'Angela Merkel', 'formerchancellor@gmail.com', '4162234546');



INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (1, 1002, '2005-07-01', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (2, 1004, '2018-09-23', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (3, 1004, '2011-01-01', '2021-07-08');

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (4, 1001, '2009-04-05', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (5, 1000, '2021-12-12', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (6, 1003, '2008-08-01', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (7, 1001, '2015-04-30', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (8, 1002, '2017-04-13', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (9, 1000, '2020-01-04', NULL);

INSERT INTO WorksIn (AgentID, CallCentreID, StartDate, EndDate)
    VALUES (10, 1003, '2007-09-12', NULL);



INSERT INTO Training (ModuleNum, TLength, TName)
    VALUES (1, 120, 'Intro To Call Centres');

INSERT INTO Training (ModuleNum, TLength, TName)
    VALUES (2, 240, 'Skills for Interacting with Customers');

INSERT INTO Training (ModuleNum, TLength, TName)
    VALUES (3, 240, 'Handling Difficult Customers');

INSERT INTO Training (ModuleNum, TLength, TName)
    VALUES (4, 60, 'Call Centre Performance Metrics');

INSERT INTO Training (ModuleNum, TLength, TName)
    VALUES (5, 480, 'Advanced Technical Training');



INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (1, 1, '2006-01-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (1, 2, '2007-03-01');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (1, 3, '2008-03-24');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (1, 4, '2009-08-17');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (1, 5, '2011-02-15');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (2, 1, '2019-01-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (3, 1, '2012-01-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (3, 2, '2013-03-22');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (3, 3, '2014-03-26');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (3, 4, '2016-08-09');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (4, 1, '2010-01-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (4, 2, '2011-03-22');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (4, 3, '2012-03-26');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (4, 4, '2013-08-09');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (4, 5, '2017-08-09');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (6, 1, '2009-06-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (6, 2, '2010-02-02');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (6, 3, '2012-03-24');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (6, 4, '2014-10-17');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (6, 5, '2017-11-15');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (7, 1, '2016-04-01');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (7, 2, '2017-01-12');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (7, 3, '2018-05-22');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (8, 1, '2018-01-07');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (8, 2, '2020-01-12');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (9, 1, '2020-03-07');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (10, 1, '2008-06-30');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (10, 2, '2010-03-22');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (10, 3, '2012-03-26');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (10, 4, '2013-08-09');

INSERT INTO TrainingCompletion (AgentID, ModuleNum, CompletionDate)
VALUES (10, 5, '2017-10-09');

