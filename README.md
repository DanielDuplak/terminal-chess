# Terminal Chess

Simple terminal chess program written in C

## Compilation

To compile the program use `make`. The provided [Makefile](Makefile) defines the following targets:

- `make` or `make all` — compiles the game and tests
- `make build` — compiles the game
- `make build_tests` — compiles the tests
- `make test` — runs the project tests
- `make coverage` — displays code coverage
- `make clean` — removes compiled files


## Running the game

The compiled game, along with all other compilation results, is stored in the 'build' directory. To run the game, execute the following command: `./build/chess` (Unix)

## Libraries

* Includes the ncurses library
* Includes the [greatest](https://github.com/silentbicycle/greatest/) library
