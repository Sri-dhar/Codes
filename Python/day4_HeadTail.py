import random
a = random.randint(0,1)
# if(a == 0):
#     print("Tails") 
# elif(a == 1):
#     print("Heads")

a = random.randint(0,1)
i = 0
head = 0
tail = 0
while(i<1000):
    if a == 0: 
        tail += 1
    else: 
        head += 1
    a = random.randint(0,1)
    i += 1

print("Heads: ", head)
print("Tails: ", tail)

#checking if the probability of getting heads or tails is 50%