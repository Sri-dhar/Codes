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
