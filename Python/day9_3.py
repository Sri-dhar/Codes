#Bidding Game
import os
os.system('clear')
print("Welcome to the secret auction program.")
bidders = dict()

def add_bidder(name, bid):
    global bidders
    bidders.update({name:bid})

while(True):
    name = input("Enter your name : ")
    bid = int(input("Enter your bid : "))
    add_bidder(name, bid)
    choice = input("Do you want to add another bidder? (y/n) : ")
    if choice =='n': 
        os.system('clear')
        break
    os.system('clear')

max_bid = 0
for key in bidders:
    if bidders[key] > max_bid:
        max_bid = bidders[key]
        max_bidder = key

print(f"The winner is {max_bidder} with a bid of ${max_bid}.")