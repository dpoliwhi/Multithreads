<p align="center">
<img src="misc/mainpic.JPG" alt="drawing"/>
</p>


# Parallel programming
### Implementation of several algorithms with parallel programming<br>
The app allows you to measure the execution time of each algorithm when running in a **single thread** and in **multithreaded mode**<br>

## Architecture

The general architecture of the program is based on the **MVC** pattern, has a console interface, which is located in the Interface directory.<br> The main algorithms are located in the Model directory.<br>
_____
## Algorithms
-  Ant colony optimization algorithm **(ACO)** to solve the traveling salesman problem
- **Winograd algorithm** of matrix multiplication
- Solving systems of linear equations **(SLE)** using the Gaussian elimination method
____
### ACO algorithm

<p align="center">
<img src="misc/aco.png" alt="drawing" width="350"/>
</p>
The algorithm will give the result of the route length closest to the minimum value.<br> A feature of the algorithm - the highest speed and maximum proximity to real life <br> Object-oriented approach allows you to repeat the life of an ant colony, reproduce the trip for food along the trails, choosing the path according to the pheromones left on the trail. <br><br>
Files with graphs are located in the *datasets* directory and are presented as *.txt* files with adjacency matrices. <br>
The application also allows you to convert *.txt* file to *.dot* file (item 2 of the main menu of the console interface) <br>
To view the graph, you need to install the appropriate extension for the IDE (for example, Graphviz for VS Code)<br><br>

#### Multithreads
Algo implemented in a simple way (without parallelism) and with *Multithreads* in **Pipeline mode**.<br>
Pipelining is generally based on dividing the algorithm to be executed into smaller parts, called stages, and allocating a separate thread to each of them.
<p align="center">
<img src="misc/aco2.png" alt="drawing" width="350"/>
</p>

________

### Winograd algorithm
<p align="center">
<img src="misc/win.png" alt="drawing" width="350"/>
</p>

The program allows you to enter the dimensions of matrices<br>
Then you can choice the mode of input data *(random or manual)*<br>

All input data is validated<br>

#### Multithreads
Algo implemented in a simple way (without parallelism), with **Pipeline parallelism** and with **Classic parallelism** .<br>

<p align="center">
<img src="misc/win2.png" alt="drawing" width="350"/>
</p>

Classic parallelism divides the number of execution 
with the number of threads equal to 2, 4, 8, ..., 4 * (number of logical computer processors)<br>

________

### SLE algorithm
<p align="center">
<img src="misc/sle.png" alt="drawing" width="450"/>
</p>

Algorithm allows you to enter SLE matrix manualy or load from file (*datasets directory*)<br>

All input data is validated<br>

#### Multithreads
Algo implemented in a simple way (without parallelism) and with **Pipeline parallelism**

<p align="center">
<img src="misc/sle2.png" alt="drawing" width="350"/>
</p>

********* 

## Makefile
The root directory contains a Makefile with the following targets:

* **make ant** - run *ACO* algorithm<br>
* **make gauss** - run *SLE* algorithm<br>
* **make winograd** - run *Winograd* algorithm<br>
* check / clang - starts checking all files for style norms, leaks, and **cppcheck**
* clean - performs a complete cleanup of installation files

