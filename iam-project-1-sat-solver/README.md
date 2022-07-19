IAM 1st HW - N QUEENS PROBLEM
---

Author
---
* Zdenek Lapes \<xlapes02>

Task
---
**The Eight Queens Problem**
Deadline: 22 March 2022
Consider the generalized Eight queens problem, i.e., the problem generalized to a chessboard of the size N x N and N queens, for a natural number N. Encode the generalized problem into a propositional formula that is satisfiable iff (if and only if) the problem has a solution, and a model of the formula encodes the solution. Write a computer program (in a language of your preference, although I suggest to use a scripting language such as Python in order to do it quickly) that outputs a CNF formula encoding the problem. The parameter N should be the single input argument. The CNF formula should be output in the DIMACS format. Use variable numbers for cells in a sequence, starting from the upper left corner, going first to the right and then down. That is, variables number 1 to N represent cells in the first row (left to right), variables number N+1 to 2N represent cells in the second row, etc. See below for N = 8.

Use a SAT solver (e.g. MiniSat or its web interface; minisat is available in many package managers, such as apt, dnf, etc.) to check whether the formula is satisfiable, and obtain the model. Submit the source files in a zip archive named xlogin00.zip (with xlogin00 substituted by your login) into WIS (Logika: úkol 1).

Note: don't spend too much time polishing your code --- a short script doing the work is sufficient.


How to run
---
```bash
python3 -m venv venv
source venv/bin/activate
pip3 install -r requirements.txt
python3 queens.py [your_queens_count]
```

Available commands for **make**
---
```
make clean
make run N="your_queens_count"
make compile
make zip
make scp
```

Result
---
**gained points: 6/6**
