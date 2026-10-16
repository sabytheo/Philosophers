*This project has been created as part of the 42 curriculum by tsaby.*

# Philosophers

> *I never thought philosophy would be so deadly.*

## Description

**Philosophers** is an implementation of the classic *dining philosophers* problem in C, built as part of the 42 curriculum.

A number of philosophers sit around a round table with a bowl of spaghetti in the middle and one fork between each pair of neighbours. A philosopher needs both the fork on their left and the fork on their right to eat; after eating they sleep, then think, then try to eat again. If a philosopher goes longer than `time_to_die` milliseconds without starting a meal, they die and the simulation stops.

The goal of the project is to learn the basics of concurrent programming: threads, mutexes, data races and deadlocks.

- Every philosopher is a **thread** (`pthread_create`).
- Every fork is protected by a **mutex**, and so are the shared state (last meal time, meal count, stop flag) and the output, so that log lines never overlap.
- **Deadlocks** are avoided with resource ordering: every philosopher always locks the two fork mutexes in the same global order, so a circular wait can never happen.
- A **monitor** loop in the main thread checks every philosopher's last meal time and stops the simulation as soon as one dies, or when everyone has eaten `number_of_times_each_philosopher_must_eat` times.
- Sleeping is done with a custom `usleep` loop so that the simulation reacts quickly when it has to stop and the timings stay precise.

## Instructions

### Compilation

```bash
cd philo
make
```

The program is compiled with `-Wall -Wextra -Werror` and only depends on `pthread`.

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

All times are in milliseconds. Arguments must be positive integers.

```bash
./philo 5 800 200 200       # nobody should die
./philo 5 800 200 200 7     # stops once everyone has eaten 7 times
./philo 4 310 200 100       # a philosopher dies
./philo 1 800 200 200       # only one fork: the philosopher dies
```

### Output

Every state change is printed as `timestamp_in_ms philosopher_id action`:

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
...
```

## Project structure

```
philo/
├── Makefile
├── include/philo.h        # structures: rules, philosophers, forks
└── sources/
    ├── philo.c            # argument parsing, initialisation, main
    ├── check_args.c       # argument validation, cleanup
    ├── thread.c           # philosopher routine and monitor
    ├── eat.c              # taking forks and eating
    ├── utils.c            # time helpers, death and "full" checks
    └── definitely_not_libft.c
```

## Resources

- [The dining philosophers problem — Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- [POSIX threads programming — LLNL](https://hpc-tutorials.llnl.gov/posix/)
- `man pthread_create`, `man pthread_mutex_lock`, `man gettimeofday`
