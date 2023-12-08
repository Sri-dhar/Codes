from prettytable import PrettyTable as pt

table = pt()

table.add_column("Pokemon",['Pikachu','Bulbasaur','Charlizard'])
table.add_column("HP",[324,2442,2344])

table.align = 'l'
print(table)
