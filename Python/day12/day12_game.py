#number guessing game easy mode and hard mode
import random  
print("Welcome to the number guessing game!")
print("I'm thinking of a number between 1 and 100.")
difficulty = input("Choose a difficulty. Type 'easy' or 'hard': ")
number = random.randint(1,100)
if difficulty == "easy":
    attempts = 10
else:
    attempts = 5
while attempts > 0:
    print(f"You have {attempts} attempts remaining to guess the number.")
    guess = int(input("Make a guess: "))
    if guess > number:
        print("Too high.")
        attempts -= 1
    elif guess < number:
        print("Too low.")
        attempts -= 1
    else:
        print(f"You got it! The answer was {number}.")
        break
    if attempts == 0:
        print("You've run out of guesses, you lose.")
    elif attempts > 0:
        print("Guess again.")
    
