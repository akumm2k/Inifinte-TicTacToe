# Unrestricted n-in-a-row 2-D TicTacToe

- Positions are accepted as coordinates (a, b) entered as `a b` via stdin.
- Winner needs to score n tiles in a row. This can be changed by passing the number of tiles in a row required to win in the call to ViewController::play()

## Sample run

```
g++ -std=c++17 main.cpp
./a.out
```

```
Enter tiles to win:
5
Enter Player 1's name: 
Tyler
Enter Player 2's name: 
Josh
Tyler's turn: 0 0
Move made: (0, 0)
Josh's turn: 1 1
Move made: (1, 1)
Tyler's turn: 0 1
Move made: (0, 1)
Josh's turn: 2 2
Move made: (2, 2)
Tyler's turn: 0 1
Invalid move! Tile occupied.
Tyler's turn: 0 2
Move made: (0, 2)
Josh's turn: 3 3
Move made: (3, 3)
Tyler's turn: 0 4
Move made: (0, 4)
Josh's turn: 4 4
Move made: (4, 4)
Tyler's turn: 0 3
Move made: (0, 3)
Winner: Tyler
-(0, 0)-(0, 1)-(0, 2)-(0, 3)-(0, 4)-
```
Alternatively, one can use different tests from the `tests/` directory, or better yet, one can use their own, using redirection as so: `./[path-to-executable] < [path-to-test-file]`

## Implementation

The program uses hashmap to reserve coordinates. This allows forgoing coordinate validity checks. It is also space-efficient, compared to matrices in storing the game state.