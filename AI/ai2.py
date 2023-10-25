import heapq

class Node:
    def __init__(self, position, parent=None, cost=0):
        self.position = position
        self.parent = parent
        self.cost = cost

def heuristic(node, goal):
    x1, y1 = node.position
    x2, y2 = goal.position
    return abs(x1 - x2) + abs(y1 - y2)

def astar(start, goal, grid):
    open_list = []
    closed_list = set()

    heapq.heappush(open_list, (start.cost, start))
    
    while open_list:
        current_cost, current_node = heapq.heappop(open_list)

        if current_node.position == goal.position:
            # Goal reached, construct and return the path
            path = []
            while current_node:
                path.append(current_node.position)
                current_node = current_node.parent
            return path[::-1]

        closed_list.add(current_node)

        for neighbor in get_neighbors(current_node, grid):
            if neighbor in closed_list:
                continue

            new_cost = current_node.cost + 1
            if neighbor not in open_list:
                heapq.heappush(open_list, (new_cost + heuristic(neighbor, goal), neighbor))
            elif new_cost < neighbor.cost:
                neighbor.cost = new_cost
                neighbor.parent = current_node

    return None

def get_neighbors(node, grid):
    x, y = node.position
    neighbors = []
    rows, cols = len(grid), len(grid[0])

    # Add adjacent nodes (up, down, left, right)
    for dx, dy in [(0, 1), (0, -1), (1, 0), (-1, 0)]:
        new_x, new_y = x + dx, y + dy
        if 0 <= new_x < rows and 0 <= new_y < cols and grid[new_x][new_y] != 1:
            neighbors.append(Node((new_x, new_y), parent=node, cost=node.cost + 1))

    return neighbors

# Define the grid (0 = empty, 1 = obstacle)
grid = [
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 0, 0, 0, 1, 1, 1, 0],
    [0, 1, 0, 0, 0, 0, 0, 0, 0, 0],
    [0, 1, 0, 1, 1, 0, 1, 1, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 1, 0, 0, 0, 1, 0, 0],
    [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],
]

start = Node((0, 0))
goal = Node((6, 9))

path = astar(start, goal, grid)

if path:
    print("Shortest Path:")
    for row in range(len(grid)):
        for col in range(len(grid[0])):
            if (row, col) == start.position:
                print("S", end=" ")
            elif (row, col) == goal.position:
                print("G", end=" ")
            elif (row, col) in path:
                print("*", end=" ")
            elif grid[row][col] == 1:
                print("#", end=" ")
            else:
                print(".", end=" ")
        print()
else:
    print("No path found!")


