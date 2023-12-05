def arithmetic_arranger(problems, answer=False):
    err1 = "Error: Too many problems."
    err2 = "Error: Operator must be '+' or '-'."
    err3 = "Error: Numbers must only contain digits."
    err4 = "Error: Numbers cannot be more than four digits."

    if len(problems) > 5:
        return err1

    first_operand = []
    second_operand = []
    operator = []
    #Declaring lines
    first_line = []
    second_line = []
    third_line = []
    fourth_line = []

    for problem in problems:
        pieces = problem.split()
        first_operand.append(pieces[0])
        operator.append(pieces[1])
        second_operand.append(pieces[2])

    if "/" in operator or "*" in operator:
        return err2

    for i in range(len(first_operand)):
        if not (first_operand[i].isdigit() and second_operand[i].isdigit()):
            return err3

    for i in range(len(first_operand)):
        if len(first_operand[i]) > 4 or len(second_operand[i]) > 4:
            return err4


    for i in range(len(first_operand)):
        if len(first_operand[i]) > len(second_operand[i]):
            first_line.append(" " * 2 + first_operand[i])
        else:
            first_line.append(" " * (len(second_operand[i]) - len(first_operand[i]) + 2) + first_operand[i])

    for i in range(len(second_operand)):
        if len(second_operand[i]) > len(first_operand[i]):
            second_line.append(operator[i] + " " + second_operand[i])
        else:
            second_line.append(operator[i] + " " * (len(first_operand[i]) - len(second_operand[i]) + 1) + second_operand[i])

    for i in range(len(first_operand)):
        third_line.append("-" * (max(len(first_operand[i]), len(second_operand[i])) + 2))

    if answer:
        for i in range(len(first_operand)):
            if operator[i] == "+":
                ans = str(int(first_operand[i]) + int(second_operand[i]))
            else:
                ans = str(int(first_operand[i]) - int(second_operand[i]))

            if len(ans) > max(len(first_operand[i]), len(second_operand[i])):
                fourth_line.append(" " + ans)
            else:
                fourth_line.append(" " * (max(len(first_operand[i]), len(second_operand[i])) - len(ans) + 2) + ans)
        arranged_problems = "    ".join(first_line) + "\n" + "    ".join(second_line) + "\n" + "    ".join(third_line) + "\n" + "    ".join(fourth_line)
    else:
        arranged_problems = "    ".join(first_line) + "\n" + "    ".join(second_line) + "\n" + "    ".join(third_line)
    return arranged_problems

test_case = ['3 + 855', '988 + 40']

result_with_answers = arithmetic_arranger(test_case, True)
result_without_answers = arithmetic_arranger(test_case)

print("Test Case with Answers:")
print(result_with_answers)

print("\nTest Case without Answers:")
print(result_without_answers)
