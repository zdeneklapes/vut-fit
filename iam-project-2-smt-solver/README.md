IAM 2st HW - smt solver
---

Author
---
* Zdenek Lapes \<xlapes02>

Task
---
**The Eight Queens Strike Back**

Use an SMT solver (e.g. Z3, see web interface or install it from a repository: "$ sudo aptitude install z3" on Debian/Ubuntu) to solve the 8 queens problem (cf. the previous homework). The following file encodes a part of the problem (every row has at least one queen and every row and every column have at most one queen). Add the rest of the constraints into the marked space. The result are the values of the variables y-pos-a to y-pos-h obtained from the model. You should need only the functions already used in the file, and functions (+ lhs rhs) and (- lhs rhs). Submit the modified file as "xlogin00.smt" into WIS (Logika: úkol 2).

Note: even a correct formula encoding the desired property might be too hard for Z3 to solve. If Z3 does not terminate, try giving it more hints (additional formulae constraining the search space).

Result
---
**gained points: 6/6**
