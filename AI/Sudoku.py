from math import sqrt
from copy import deepcopy
from time import time
from queue import PriorityQueue

class SudokuTable:
    def __init__(self, table):
        self.table = table.copy()
        self.table_len = int(sqrt(len(table)))
        initial_domain = list(range(1, self.table_len + 1))
        self.domain = {}
        for i in range(0, self.table_len):
            for j in range(0, self.table_len):
                if not self.table[i * self.table_len + j]:  # is empty
                    self.domain[(i, j)] = list(filter(lambda x: x not in self.get_constrains(i, j), initial_domain))

        self.count_empty_variables = table.count(0)

    def __str__(self):
        s = ''
        for i in range(0, self.table_len):
            s += str(self.table[i*self.table_len:(i+1)*self.table_len])+'\n'
        return s

    def get_constrains(self, i, j):
        # row constrains
        constrains = self.table[i * self.table_len:(i + 1) * self.table_len]

        # column constrains
        for a in range(0, self.table_len):
            constrains.append(self.table[a * self.table_len + j])

        # inner table constrains
        a = int(sqrt(self.table_len))
        x = int(i/a)
        y = int(j/a)
        for i in range(x*a, (x+1)*a):
            for j in range(y*a, (y+1)*a):
                constrains.append(self.table[i * self.table_len + j])

        constrains = list(set(constrains))
        constrains.remove(0)
        return constrains

    def set_domain_values(self):
        initial_domain = list(range(1, self.table_len + 1))
        self.domain = {}
        for i in range(0, self.table_len):
            for j in range(0, self.table_len):
                if not self.table[i * self.table_len + j]:  # is empty
                    self.domain[(i, j)] = list(filter(lambda x: x not in self.get_constrains(i, j), initial_domain))

    def update_domain(self, i, j, value):
        domain = deepcopy(self.domain)
        for x in range(0,self.table_len):
            if x != j and domain.get((i,x)) and (value in domain.get((i,x))):
                domain[(i,x)].remove(value)
            if x != i and domain.get((x,j)) and (value in domain.get((x,j))):
                domain[(x,j)].remove(value)

        a = int(sqrt(self.table_len))
        x = int(i/a)
        y = int(j/a)
        for m in range(x*a, (x+1)*a):
            for n in range(y*a, (y+1)*a):
                if (m != i or n!=j) and domain.get((m,n)) and (value in domain.get((m,n))):
                    domain[(m,n)].remove(value)
        return domain


    def set_variable(self, i, j, value):
        self.table[i * self.table_len + j] = value

    def remove_variable(self, i, j):
        self.table[i * self.table_len + j] = 0

    def is_consistent(self, i, j, value):
        constrains = self.get_constrains(i,j)
        if value not in constrains:
            return True
        return False

def minimum_remaining_value(sudoku):
    min_length = sudoku.table_len
    for i in range(0, sudoku.table_len):
        for j in range(0, sudoku.table_len):
            if sudoku.table[i * sudoku.table_len + j] == 0:
                if len(sudoku.domain[(i, j)]) < min_length:
                    min_length = len(sudoku.domain[(i, j)])
                    pos = [(i, j)]
                elif len(sudoku.domain[(i, j)]) == min_length:
                    pos.append((i, j))
    return pos

def degree_heuristic(sudoku, pos):
    max_degree = -1
    for i, j in pos:
        if not sudoku.table[i * sudoku.table_len + j]:
            count = sudoku.table[i * sudoku.table_len:(i + 1) * sudoku.table_len].count(0)
            for a in range(0, sudoku.table_len):
                if not sudoku.table[a * sudoku.table_len + j]:
                    count += 1
            a = int(sqrt(sudoku.table_len))
            m = int(i/a)
            n = int(j/a)
            for k in range(m*a, (m+1)*a):
                for l in range(n*a, (n+1)*a):
                    if not sudoku.table[k * sudoku.table_len + l]:
                        if k != i or l != j:
                            count += 1
                        if k == i and l == j:
                            count += 1
            count -= 3
            if count > max_degree:
                max_degree = count
                x, y = i, j
    return x, y

def select_unassigned_variable(sudoku, choice):
    if choice == 0:  # first cell that is empty
        pos = table.index(0)
        return int(pos/sudoku.table_len), int(pos%sudoku.table_len)

    if choice == 1:  # minimum remaining value
        pos = minimum_remaining_value(sudoku)
        return pos[0]

    if choice == 2: # MRV + degree heuristic
        pos = minimum_remaining_value(sudoku)
        return degree_heuristic(sudoku, pos)

def least_constraint_value(sudoku, i, j):
    values = PriorityQueue()
    for value in sudoku.domain[(i, j)]:
        new_domain = sudoku.update_domain(i, j, value)
        constraint = 0
        for key in new_domain.keys():
            constraint += len(new_domain[key])
        values.put((constraint, value))
    ordered_domain = []
    while not values.empty():
        a = values.get()
        ordered_domain.append(a[1])

    ordered_domain.reverse()
    return ordered_domain

def order_domain_values(sudoku, choice, i, j):
    if choice == 0:  # in order
        return sorted(sudoku.domain[(i, j)])
    if choice == 1:
        return least_constraint_value(sudoku, i, j)

def recursive_backtrack(assignment, sudoku, SUV, ODV):
    if len(assignment) == sudoku.count_empty_variables:
        return assignment
    i,j = select_unassigned_variable(sudoku, choice=SUV)
    #print('i',i,'j',j)
    #print(sudoku)
    last_domain = deepcopy(sudoku.domain)
    for value in order_domain_values(sudoku, choice=ODV, i=i, j=j):
        #print(value)
        if sudoku.is_consistent(i, j, value):
            assignment[(i, j)] = value
            sudoku.set_variable(i, j, value)
            sudoku.domain = deepcopy(last_domain)
            sudoku.domain = sudoku.update_domain(i, j, value)
            result = recursive_backtrack(assignment, sudoku, SUV, ODV)
            if result:
                return result
            assignment.pop((i, j))
            sudoku.domain = deepcopy(last_domain)

            sudoku.remove_variable(i, j)
    return False

def backtrack(table, SUV, ODV):
    sudoku = SudokuTable(table)
    result = recursive_backtrack({}, sudoku, SUV, ODV)
    print(sudoku)

if __name__ == '__main__':
    table = []
    print('Enter the sudoku table:')
    for i in range(0, 9):
        line = input().split()
        for j in range(0, 9):
            table.append(int(line[j]))
    
    print('\nSelect the unassigned variable heuristic:')
    print('0 - first cell that is empty')
    print('1 - minimum remaining value')
    print('2 - MRV + degree heuristic')
    SUV = int(input())

    print('\nSelect the order domain values heuristic:')
    print('0 - in order')
    print('1 - least constraint value')
    ODV = int(input())

    time_start = time()
    backtrack(table, SUV, ODV)
    print('time cost', time() - time_start, 's')

'''
5 3 0 0 7 0 0 0 0
6 0 0 1 9 5 0 0 0
0 9 8 0 0 0 0 6 0
8 0 0 0 6 0 0 0 3
4 0 0 8 0 3 0 0 1
7 0 0 0 2 0 0 0 6
0 6 0 0 0 0 2 8 0
0 0 0 4 1 9 0 0 5
0 0 0 0 8 0 0 7 9
'''