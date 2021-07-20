from libC import *
from random import *

LEN = 10
students = (Student * LEN)()

for i in range(LEN):
	students[i].id = randint(0, 99)

bt = libC.new_tree()

if bt == None:
	exit(1)

print('Inserindo os nós: ', end='')

for i in range(LEN):
	libC.insert_node(bt, students[i])

print('\nPré ordem: ', end='')
libC.travel_tree(bt, -1)

print('\nEm ordem: ', end='')
libC.travel_tree(bt, 0)

print('\nPós ordem: ', end='')
libC.travel_tree(bt, 1)

print('\nPor profundidade: ', end='')
libC.print_tree_by_level(bt)
print()
