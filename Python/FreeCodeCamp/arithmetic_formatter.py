def arithmetic_arranger(problems, boolE):

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
    #get the first line
    firstLine = ""
    for problem in problems:
        if problem.split(" ")[0].__len__() > problem.split(" ")[2].__len__():
            firstLine = firstLine + "  " + problem.split(" ")[0]
        else:
            firstLine = firstLine + "  " + problem.split(" ")[2]
    arranged_problems = firstLine + "\n"

    secondLine = ""
    for problem in problems:
        if problem.split(" ")[0].__len__() > problem.split(" ")[2].__len__():
            secondLine = secondLine + problem.split(" ")[1] + " " + problem.split(" ")[0]
        else:
            secondLine = secondLine + problem.split(" ")[1] + " " + problem.split(" ")[2]
    arranged_problems = arranged_problems + secondLine + "\n"

    thirdLine = "" #dashes one
    for noOfDash in noOfDashArr:
        thirdLine = thirdLine + "-" * noOfDash
        thirdLine = thirdLine + "    "
    arranged_problems = arranged_problems + thirdLine + "\n"

    if(boolE):
        fourthLine = "" #result
        for result in resultsArray:
            fourthLine = fourthLine + str(result)
            fourthLine = fourthLine + "    "
        arranged_problems = arranged_problems + fourthLine + "\n"

    return arranged_problems

result = arithmetic_arranger(["32 + 698", "3801 - 2", "45 + 43", "123 + 49"], True)
print(result)