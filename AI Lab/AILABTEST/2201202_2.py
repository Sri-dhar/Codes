def water_jug_problem(cj1, cj2, target):
    jug1 = 0
    jug2 = 0

    while jug1 != target and jug2 != target:
        if jug1 == 0:
            jug1 = cj1
            print(f"Fill jug 1 ({jug1} litres)")
        elif jug2 == cj2:
            jug2 = 0
            print(f"Empty jug 2 (0 litres)")
        else:
            sj1 = cj2 - jug2
            if jug1 <= sj1:
                jug2 += jug1
                jug1 = 0
                print(f"Pour water from jug 1 to jug 2 ({jug2} litres)")
            else:
                jug1 -= sj1
                jug2 = cj2
                print(f"Fill jug 2 ({jug2} litres)")

    print("Target reached!")


x = int(input("Enter the capacity of the first jug"))
y = int(input("Enter the capacity of the second jug"))
z = int(input("Enter the target value"))

#swapping x and y if x> y
if(x>y):
    x,y = y,x

#calling the functino to print the steps 

print()
water_jug_problem(x,y,z);

