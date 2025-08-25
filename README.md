# Philosophers
The Philosophers project simulates a classic problem involving multiple philosophers sitting around a table with a bowl of spaghetti and one fork each. The goal is to manage their eating, thinking, and sleeping behaviors using **threading** and synchronization.

Philosophers alternate between eating, thinking, and sleeping.
Each philosopher needs two forks (one on their left and one on their right) to eat.
The simulation stops when a philosopher dies of starvation or when all philosophers have eaten the specified number of times (if provided).

## Prerequisites
- A C compiler (e.g., `gcc` or `clang`)
- `make`

## Compilation
To compile philosophers:

1. Clone the repository:
```
git clone git@github.com:k2matu/42-philosophers.git philosophers
````
2. Navigate into the directory:
```
cd philosophers
```
3. Compile the program using make:
```
make
```
4. This will produce an executable named philo.

## Usage
The program takes the following arguments:
```
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
- **number_of_philosophers**: Number of philosophers and forks.
- **time_to_die** (milliseconds): Maximum time a philosopher can go without eating before dying.
- **time_to_eat** (milliseconds): Time it takes for a philosopher to eat.
- **time_to_sleep** (milliseconds): Time a philosopher spends sleeping.
- **number_of_times_each_philosopher_must_eat** (optional): If specified, the simulation stops when all philosophers have eaten this number of times.

#### Example:
To run a simulation with 5 philosophers where each philosopher has 200 milliseconds to eat, 100 milliseconds to sleep, and dies if they don’t eat within 500 milliseconds, use:
```
./philo 5 500 200 100
```
eg., Output:
```
0 1 is thinking
0 2 has taken a fork
0 4 has taken a fork
0 5 is thinking
0 4 has taken a fork
0 4 is eating
0 3 is thinking
0 2 has taken a fork
0 2 is eating
200 4 is sleeping
200 5 has taken a fork
200 5 has taken a fork
200 5 is eating
201 2 is sleeping
201 3 has taken a fork
201 3 has taken a fork
201 3 is eating
300 4 is thinking
301 2 is thinking
400 5 is sleeping
400 1 has taken a fork
400 1 has taken a fork
400 1 is eating
401 3 is sleeping
401 4 has taken a fork
401 4 has taken a fork
401 4 is eating
500 5 is thinking
501 2 died
```
