/* SELECTION:  List the names of agents and their salaries for employees who have a salary greater than 50,000 */
SELECT AName, Salary
FROM Agent
WHERE Salary > 50000;

/* PROJECTION:  List the CallCentreID, address, and manager name of all call centres in the database */
SELECT CallCentreID, CCAddress, ManagerName
FROM CallCentres;

/* JOIN: Join the Agent, Training, and TrainingCompletion tables to find the names and emails of the agents who have completed the training module named ‘Handling Difficult Customers’ */
SELECT T.modulenum, T.tlength, T.tname
FROM Agent as A, Training as T, TrainingCompletion as TC
WHERE A.AgentID = TC.AgentID AND T.ModuleNum = TC.ModuleNum AND A.agentid = 2;

/* OLD - IGNORE FOR NOW*/
SELECT A.AName, A.Email
FROM Agent AS A, Training AS T, TrainingCompletion AS TC
WHERE A.AgentID = TC.AgentID AND T.ModuleNum = TC.ModuleNum AND T.TName = 'Handling Difficult Customers';

/* AGGREGATION: In English: List the name and salary of the agent who earns the highest agent salary in the company */
SELECT AName, Salary AS HighestSalary
FROM Agent
WHERE Salary = 
  (SELECT MAX (Salary)
   FROM Agent);

/* NESTED AGGREGATION with GROUP BY:
For each call centre (listed by their ID), list the average salary earned by the agents who work in that call centre */
SELECT CallCentreID, AVG(Salary)
FROM Agent AS A, WorksIn AS W
WHERE A.AgentID = W.AgentID
GROUP BY CallCentreID;


/* DIVISION: Find the names of the agents who have completed all the training modules */
SELECT AName
FROM Agent AS A
WHERE NOT EXISTS
    ((SELECT T.ModuleNum
      FROM Training AS T)
     EXCEPT
     (SELECT TC.ModuleNum
      FROM TrainingCompletion AS TC
      WHERE TC.AgentID = A.AgentID));
