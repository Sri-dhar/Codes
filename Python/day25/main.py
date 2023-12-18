# with open("weather_data.csv") as data_file:
#     data = data_file.readlines()
#     print(data)
    

# import csv

# with open("weather_data.csv") as data_file:
#     data = csv.reader(data_file)
#     temperatures = []
#     for row in data:
#         print(row)
    #     if row[1] != "temp":
    #         temperatures.append(int(row[1]))
    # print(temperatures)

import pandas as pd

data = pd.read_csv("weather_data.csv")
print(data['day'])
print('----------------------------------------------------')
print(data)

print(type(data))
print('----------------------------------------------------')
print(type(data['temp']))

data_dict = data.to_dict()
# print(data_dict)

temp_list = data['temp'].to_list()
print(temp_list)
print()
print("The mean is:")
print(data['temp'].mean())

print (data[data.day == 'Monday'])