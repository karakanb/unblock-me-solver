# Unblock Me Solver
The Unblock Me game was a game that was popular when I was in high school, and we spent a lot of time on it. After years, when the project to solve Unblock Me in *Analysis of Algorithms* course, it became exciting to work on the game I spent a lot of time with, which led to the implementation of this project.
In case you don't know what the Unblock Me is, it is a simple game where you move blocks to take your target block out, as follows:

![Unblock Me Screenshot](http://logonubul.com/images/unblock-me.png)

The aim was to solve this game by using two of the most popular search algorithms: *BFS* and *DFS*.

## Approach
The main approach was constructing the graph that will be searched with different states of the board by moving each of the blocks one by one. The expected outcome of the project is comparing these two algorithms by examining how they behave for this problem. The solution basically moves each of the blocks on the board for each of the possible states and checks if this board is seen before; if the board is not seen before, it is added to the list that is iterated over. The algorithm checks the current board, and if it is solved, it breaks the loops and screams "EUREKA!", which means the board is solved. Then, it backtracks the steps that brought it to the current solution, and prints the board at each state.

Those two algorithms, BFS and DFS, are implemented with recursion usually, however I had some problem with the stack size with a wrong implementation, therefore implemented it using a double-ended queue which simplifies the debugging process and differences between *BFS* and *DFS*.

## Implementation
It basically moves every block on the board, creates a new board with the moved block and adds it to the queue if it is not seen before. However, the main problem with this implementation was backtracking the solution steps. At first I tried to solve this by returning the boards from the recursion, however it became harder to manage and I could not get out of it, therefore I implemented an ID-based backtracking chain system. Each of the boards have an ID that is constructed by concatenating cell values of the 2D array version of the board, which means since there will be no duplicate boards in the queue, this hash will result to a unique ID for each board. Every possible board that is generated from the current board gets the ID of the current board as the referrer ID, which allows to trace parent of every board. Seen boards are pushed to a map with their ID as the key, and if the solution is found for a board, the `constructSolutionSteps` method of the `Solver` class traces this chain back to the first board state. Since every board has their ID and their referrer ID, it can easily follow these steps with the map implementation in constant time.

The following 3 lines of code is the heart of this traceback process.

```C++
// Construct the solution steps from the reference chain.
while (lastReference != "") {
    this->steps.push_back(this->pastSteps[lastReference]);
    lastReference = this->pastSteps[lastReference].referrer;
}
```

## Compiling and Running
The project is constructed using the precious `cmake`. You can install `cmake` with `sudo apt-get install cmake` command.

If you have CMake installed, you can create your platform specific makefile. With the makefile, you can compile and run the program easily.

```bash
cmake CMakeLists.txt    # Create the makefile.
make                    # Build the project using make.
```

The `make` command will create an executable called `unblock-me-solver.out`, which will be used to run the program. The program can be run with the following scheme:

`./unblock-me-solver.out ALGORITHM_TYPE INPUT_PATH OUTPUT_PATH`

Available algorithm types are `bfs` and `dfs`, therefore the program can be run exactly with one of the following commands:

```
./unblock-me-solver.out dfs data/input.txt data/output.txt # With DFS
./unblock-me-solver.out bfs data/input.txt data/output.txt # With BFS
```

The program will output the initial state of the board, the steps used to get to the solution, and the basic statistics such as running time and number of steps:

```
===========================

Initial board state:

. . . F . .
. . . F G .
B A A F G .
B D . . . .
C D . . . .
C . E E . .

===========================
===========================

Puzzle is solved.
Number of steps to solve:  6

===========================
===========================

Step 0

. . . F . .
. . . F G .
B A A F G .
B D . . . .
C D . . . .
C . E E . .

===========================
===========================

Step 1

. . . F . .
. . . F G .
B A A F G .
B D . . . .
C D . . . .
C E E . . .

===========================
===========================

Step 2

. . . . . .
. . . F G .
B A A F G .
B D . F . .
C D . . . .
C E E . . .

===========================
===========================

Step 3

. . . . . .
. . . . G .
B A A F G .
B D . F . .
C D . F . .
C E E . . .

===========================
===========================

Step 4

. . . . . .
. . . . G .
B A A . G .
B D . F . .
C D . F . .
C E E F . .

===========================
===========================

Step 5

. . . . G .
. . . . G .
B A A . . .
B D . F . .
C D . F . .
C E E F . .

===========================
===========================

The puzzle is solved.
The total time in seconds the algorithm took to solve the puzzle:  0.517799
The total number of boards seen to find the solution including the initial state:  164
The block with letter 'A' represents the block which is asked to be rescued.
The output states are written to the output file you provided.

===========================

```

The `The total number of boards seen to find the solution including the initial state` number indicates the number of different board states that are created while searching for the solution. In the 2D representations, the block that is represented with letter 'A' indicates the prisoner block, and the escape is at the same row with it, which means if there are no obstacles from the block 'A' to the right wall of the board, the board is solved.

## Outcomes
By running the algorithms with different datasets, it becomes pretty trivial to see the differences. First of all, **if the aim is to find the solution with the least number of steps, it needs to be solved with BFS**. However, **if the aim is to find the fastest solution, the DFS is the way to go.**

With BFS, it took 5 steps to solve the example board in 0.517799 seconds. With DFS, it took 20 steps to solve the example board in  0.00357 seconds. It is pretty clear that BFS finds the shortest path to solution where DFS finds the fastest solution. With this expected outcome, it can be said that the algorithm implementations seem to be correct.

## Further Reading
In order to learn more about breadth-first search and depth-first search, the Wikipedia pages for [BFS](https://en.wikipedia.org/wiki/Breadth-first_search) and [DFS](https://en.wikipedia.org/wiki/Depth-first_search) and their *External Links* sections may be helpful.

## Credits
The base idea of the project is inspired by the amazing work that is done by [Thanassis Tsiodras](https://github.com/ttsiodras). His blog post about the subject can be found [here](https://www.thanassis.space/unblock.html), where he uses the iOS version of the application and by processing the screenshot of the board, he maps the board to a software-based representation, where he uses breadth-first search to find the solution board. The code he used can be found [in this GitHub repository](https://github.com/ttsiodras/UnblockMeSolver).

## License
The project is licensed under MIT License.
