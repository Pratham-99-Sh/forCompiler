import random

def print_solution(board):
    for row in board:
        row_string = ""
        for col in board:
            if col == row:
                row_string += "Q "
            else:
                row_string += ". "
        print(row_string)
    print()

def is_safe(board, row, col):
    for i, j in enumerate(board):
        if j == col or abs(i - row) == abs(j - col):
            return False
    return True

def min_conflicts(n, max_steps=1000):
    board = [random.randint(0, n - 1) for _ in range(n)]

    for _ in range(max_steps):
        conflicted_rows = [row for row in range(n) if not is_safe(board, row, board[row])]

        if not conflicted_rows:
            return board

        random_row = random.choice(conflicted_rows)
        min_conflict_col = min(
            (col for col in range(n) if col != board[random_row]),
            key=lambda col: sum(1 for row in range(n) if not is_safe(board, row, col))
        )

        board[random_row] = min_conflict_col

    return None

if __name__ == "__main__":
    n = int(input("Enter the number of queens: "))
    solution = min_conflicts(n)

    if solution:
        print("Solution found using Minimum Conflicts:")
        print_solution(solution)
    else:
        print("No solution found using Minimum Conflicts.")
