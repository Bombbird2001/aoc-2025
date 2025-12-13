import numpy as np
from ortools.linear_solver import pywraplp

with open("input.txt", "r") as f:
    total = 0

    for line in f.readlines():
        data = line.split(" ")
        slots = len(data[-1][1:-1].split(","))
        system = np.array([[0 for _ in range(len(data) - 2)] for _ in range(slots)])
        target = np.array(list(map(int, data[-1][1:-2].split(","))))

        for i in range(1, len(data) - 1):
            for slot in data[i][1:-1].split(","):
                system[int(slot)][i - 1] += 1
        combined = np.hstack((system, target.reshape((-1, 1))))
        # print(combined)

        solver = pywraplp.Solver.CreateSolver("SAT")
        variables = [solver.IntVar(0, solver.infinity(), f"x{i}") for i in range(len(data) - 2)]
        for i in range(slots):
            lhs = combined[i][0] * variables[0]
            for j in range(1, combined.shape[1] - 1):
                lhs = lhs + combined[i][j] * variables[j]
            solver.Add(lhs == combined[i][-1])
        solver.Minimize(sum(variables))
        if solver.Solve() == pywraplp.Solver.OPTIMAL:
            print(solver.Objective().Value())
            total += solver.Objective().Value()
        else:
            print("No optimal solution")

    print(total)