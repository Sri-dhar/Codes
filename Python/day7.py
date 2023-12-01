#For/while if/else lists strings range modules
#hangman 

import random

b = ['sridhar', 'tuli', 'hello', 'how', 'are', 'you', 'apple', 'banana', 'kela', 'seb']

c = random.choice(b)
length = len(c)

listt = ['_'] * length

for x in listt:
    print(x,end='')

print('\n')

flag = 0
while(flag != len(c)):
    letter = input("Enter a letter: ")
    for let in c:
        if(let == letter):
            print(let,end='')
            flag +=1
        else:
            print('_',end='')0