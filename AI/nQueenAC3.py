# AC3 algorithm for NQueen Problem
import copy
import numpy as np


def AC3(board, constraints):
    queue = copy.copy(constraints)
    while len(queue) != 0:
        chk = queue.pop(0)
        if MadeConsistent(board, chk):
            # add to queue
            pass



N = input("Enter the value of N: ")
Board = np.ones((N, N))
AC3(Board, [])
