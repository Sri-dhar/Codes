#higher or lower game
import random
import os
from day14_gamedata import data
from day14_art import logo, vs

def format_data(account):
    """Takes the account data and returns the printable format."""
    account_name = account["name"]
    account_descr = account["description"]
    account_country = account["country"]
    return f"{account_name}, a {account_descr}, from {account_country}"

def check_answer(guess, a_followers, b_followers):
    """Take the user guess and follower counts and returns if they got it right."""
    if a_followers > b_followers:
        return guess == "a"
    else:
        return guess == "b"
    
# Display art
print(logo)
score = 0
game_should_continue = True
account_b = random.choice(data)

# Game loop
while game_should_continue:
    account_a = account_b
    account_b = random.choice(data)

    while account_a == account_b:
        account_b = random.choice(data)

    print(f"Compare A: {format_data(account_a)}")
    print(vs)
    print(f"Against B: {format_data(account_b)}")

    guess = input("Who has more followers? Type 'A' or 'B': ").lower()

    a_followers = account_a["follower_count"]
    b_followers = account_b["follower_count"]
    is_correct = check_answer(guess, a_followers, b_followers)

    if is_correct:
        score += 1
        os.system('clear') 
        print(logo)
        print(f"You're right! Current score: {score}.")
    else:
        game_should_continue = False
        os.system('clear')
        print(logo)
        print(f"Sorry, that's wrong. Final score: {score}")