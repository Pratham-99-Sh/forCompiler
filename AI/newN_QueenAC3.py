def is_safe(board, row, col):
    n = len(board)

    for i in range(row):
        if board[i] == col:
            return False

    for i, j in zip(range(row, -1, -1), range(col, -1, -1)):
        if board[i] == j:
            return False

    for i, j in zip(range(row, -1, -1), range(col, n)):
        if board[i] == j:
            return False

    return True

def ac3(board, row, n):
    if row == n:
        return True

    for col in range(n):
        if is_safe(board, row, col):
            board[row] = col

            if ac3(board, row + 1, n):
                return True

            board[row] = -1  # Backtrack

    return False

def nqueens_ac3(n):
    board = [-1] * n

    if not ac3(board, 0, n):
        return None  # No solution found

    return board

def print_solution(board):
    if board is None:
        print("No solution found.")
        return

    for row in board:
        row_string = ""
        for col in range(len(board)):
            if col == row:
                row_string += "Q "
            else:
                row_string += ". "
        print(row_string)
    print()


n = int(input("Enter board size: "))
solution = nqueens_ac3(n)
print_solution(solution)