# Philosophers

This is a C-based simulation of the **Dining Philosophers Problem**, where philosophers sit around a table with a bowl of spaghetti and a fork between each pair. The challenge is to create a simulation where each philosopher must alternately think, eat, and sleep without starving to death. The project aims to teach the fundamentals of threading and synchronization mechanisms such as **mutexes** and **semaphores**.

## Overview
In this project, you'll simulate multiple philosophers sitting at a round table, each requiring two forks to eat. Philosophers must alternate between thinking, eating, and sleeping. If a philosopher has not eaten within a specific time, they will die due to starvation. The program handles this concurrency using threads and mutexes to ensure safe access to the shared resources (forks).
![](https://zhen404.com/dining_phil.png)


### Main Concepts
- **Threading**: Each philosopher is represented as a thread.
- **Mutexes**: Used to protect access to forks to prevent multiple philosophers from using the same fork simultaneously.
- **Simulation Rules**: Philosophers must eat, think, and sleep in a loop while avoiding starvation. The program stops if a philosopher dies or all philosophers have eaten a specified number of times.

## Requirements

- **C programming language**  
- **POSIX threads** (`pthread`)  
- **Makefile**  
- **Linux OS** (or Unix-like)  

### Compilation

To compile the project, run the following command:

```bash
make
```

### Running the Program

The program is executed with the following arguments:

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat (optional)]
```

**Arguments**:

- `number_of_philosophers`: The number of philosophers and forks.
- `time_to_die`: The time (in milliseconds) before a philosopher dies due to starvation.
- `time_to_eat`: The time (in milliseconds) a philosopher needs to eat.
- `time_to_sleep`: The time (in milliseconds) a philosopher spends sleeping.
- `number_of_times_each_philosopher_must_eat`: Optional. The number of times each philosopher must eat before the simulation ends.

### Example Usage

```bash
./philo 5 800 200 200 3
```

This will start a simulation with 5 philosophers, where each philosopher will die after 800ms of not eating, will take 200ms to eat, and will sleep for 200ms. The simulation stops when all philosophers have eaten at least 3 times.
