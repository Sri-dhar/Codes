# coffee machine project
import day15_CoffeeData

# print report
# Check resources sufficient?
# Process coins
# Check transaction successful?
# Make coffee

print("Welcome to the Coffee Machine!")
print("Please select a drink from the menu below:")
print("espresso: $1.50")
print("latte: $2.50")
print("cappuccino: $3.00")


def check_resources(coffee_choice):
    # check resources sufficient
    for ingredient in day15_CoffeeData.MENU[coffee_choice]["ingredients"]:
        if day15_CoffeeData.MENU[coffee_choice]["ingredients"][ingredient] > day15_CoffeeData.resources[ingredient]:
            print(f"Sorry, there is not enough {ingredient}.")
            return False
    return True


def process_coins():
    # process coins
    print("Please insert coins.")
    quarters = int(input("How many quarters?: "))
    dimes = int(input("How many dimes?: "))
    nickles = int(input("How many nickles?: "))
    pennies = int(input("How many pennies?: "))
    total = (quarters * 0.25) + (dimes * 0.10) + (nickles * 0.05) + (pennies * 0.01)
    return total


def check_transaction(coffee_choice, total):
    # check transaction successful
    if total < day15_CoffeeData.MENU[coffee_choice]["cost"]:
        print("Sorry, that's not enough money. Money refunded.")
        return False
    else:
        day15_CoffeeData.profit += day15_CoffeeData.MENU[coffee_choice]["cost"]
        for ingredient in day15_CoffeeData.MENU[coffee_choice]["ingredients"]:
            day15_CoffeeData.resources[ingredient] -= day15_CoffeeData.MENU[coffee_choice]["ingredients"][ingredient]
        return True


def make_coffee(coffee_choice):
    # make coffee
    print(f"Here is your {coffee_choice} ☕️. Enjoy!")


def coffee_machine():
    while True:
        user_choice = input("What would you like? (espresso/latte/cappuccino): ")
        if user_choice == "off":
            break
        elif user_choice == "report":
            print(f"Water: {day15_CoffeeData.resources['water']}ml")
            print(f"Milk: {day15_CoffeeData.resources['milk']}ml")
            print(f"Coffee: {day15_CoffeeData.resources['coffee']}g")
            print(f"Money: ${day15_CoffeeData.profit}")
        else:
            if check_resources(user_choice):
                total = process_coins()
                if check_transaction(user_choice, total):
                    make_coffee(user_choice)


coffee_machine()
