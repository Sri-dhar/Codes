def arithmetic_arranger(problems):

    err1 = "Error: Too many problems."
    err2 = "Error: Operator must be '+' or '-'."
    err3 = "Error: Numbers must only contain digits."
    err4 = "Error: Numbers cannot be more than four digits."

    if problems.__len__() > 5:
        return err1
    
    for problem in problems:
        if problem.split(" ")[1] != "+" and problem.split(" ")[1] != "-":
            return err2
        if not problem.split(" ")[0].isnumeric() or not problem.split(" ")[2].isnumeric():
            return err3
        if problem.split(" ")[0].__len__() > 4 or problem.split(" ")[2].__len__() > 4:
            return err4
        
    noOfDash = 0
    noOfDashArr = list()
    for problem in problems:
        if problem.split(" ")[0].__len__() > problem.split(" ")[2].__len__():
            noOfDash = problem.split(" ")[0].__len__() + 2
        else:
            noOfDash = problem.split(" ")[2].__len__() + 2
        noOfDashArr.append(noOfDash)
    
    arranged_problems = ""

    resultsArray = list()
    for problem in problems:
        if problem.split(" ")[1] == "+":
            resultsArray.append(int(problem.split(" ")[0]) + int(problem.split(" ")[2]))
        else:
            resultsArray.append(int(problem.split(" ")[0]) - int(problem.split(" ")[2]))
    
    #printing work
    

    return arranged_problems