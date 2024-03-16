def calculate_diversity(group):
    diversity = 0
    for i in range(len(group)):
        for j in range(i+1, length(group)):
            diversity += abs(group[i] - group[j])
    
    return diversity



n = int(input("Enter the no. of students : "))
k = int(input("Enter the no. of groups : "))
