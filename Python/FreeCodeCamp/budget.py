class Category:

    ledger = list()
    name = ""
    balance = 0
    spent = 0
    def __init__(self, name):
        self.name = name
        self.ledger = list()
        self.balance = 0
        self.spent = 0

    def check_funds(self, amount):
        if self.balance >= amount:
            return True
        else:
            return False

    def get_balance(self):
        return self.balance

    def deposit(self, amount, description = ""):
        self.ledger.append({"amount": amount, "description": description})
        self.balance += amount

    def withdraw(self, amount, description = ""):
        if self.check_funds(amount):
            self.ledger.append({"amount": -amount, "description": description})
            self.balance -= amount
            self.spent += amount
            return True
        else:
            return False

    def transfer(self, amount, category):
        if self.check_funds(amount):
            self.withdraw(amount, "Transfer to " + category.name)
            category.deposit(amount, "Transfer from " + self.name)
            return True
        else:
            return False

    def __str__(self):

        padding = "*" * ((30 - len(self.name)) // 2)
        title = padding + self.name + padding + "\n"

        items = ""
        for item in self.ledger:
            items += item["description"][:23].ljust(23) +str("{:.2f}".format(item["amount"])).rjust(7) + "\n"
        total = "Total: " + str(self.balance)
        return title + items + total


def create_spend_chart(categories):

    total = 0
    spent = list()
    names = list()

    for category in categories:
        total += category.spent
        spent.append(category.spent)
        names.append(category.name)

    for i in range(len(spent)):
        spent[i] = int((spent[i] / total) * 100)
    #percentage calculation done

    heading = "Percentage spent by category\n"

    for i in range(10, -1, -1):
        line = str(i * 10).rjust(3) + "| "
        for j in range(len(spent)):
            if spent[j] >= (i * 10):
                line += "o  "
            else:
                line += "   "
        heading += line + "\n"

    heading += "    " + "-" * (len(categories) * 3 + 1) + "\n"
    #dashed line done

    max = 0
    for name in names:
        if len(name) > max:
            max = len(name)
    #max len name found
    for i in range(max):
        line = " "*5
        for j in range(len(names)):
            if i < len(names[j]):
                line += names[j][i] + "  "
            else:
                line += " "*3
        heading += line
        if i < max - 1:
            heading += "\n"
    return heading
