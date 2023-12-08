import os

def add(n1,n2):
    '''This Function adds two numbers''' #function documentation 
    return n1+n2

def sub(n1,n2):
    '''This Function subtracts two numbers'''
    return n1-n2

def mul(n1,n2):
    '''This Function multiplies two numbers'''
    return n1*n2

def div(n1,n2):
    '''This Function divides two numbers'''
    return n1/n2

operations = {
    "+":add,
    "-":sub,
    "*":mul,
    "/":div
}

def calculator():
    num1 = float(input("Enter First Number: "))
    for symbol in operations:
        print(symbol)
    should_continue = True
    while should_continue:
        operation_symbol = input("Pick an operation: ")
        num2 = float(input("Enter Next Number: "))
        calculation_function = operations[operation_symbol]
        answer = calculation_function(num1,num2)
        print(f"{num1} {operation_symbol} {num2} = {answer}")
        if input(f"Type 'y' to continue calculating with {answer}, or type 'n' to start a new calculation: ") == "y":
            num1 = answer
        else:
            os.system('clear')
            should_continue = False
            calculator()

calculator()
