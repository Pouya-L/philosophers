# 42_Philosophers

## Description
The dining philosophers problem is a well-known example in the field of computer science, frequently utilized in the design of concurrent algorithms to demonstrate synchronization challenges and methods for addressing them. Initially proposed in 1965 by Edsger Dijkstra as a student examination task, it was framed in the context of computers vying for access to tape drive peripherals. The problem received its current interpretation shortly thereafter, thanks to Tony Hoare.

[More info on Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Mandatory Part
`philo`: This program simulates philosophers using threads and mutex. Each philosopher is represented as a thread. There is one fork between each philosopher, protected by a mutex. Philosophers must adhere to the specified rules: eating, thinking, or sleeping without conflicts. The aim is to learn how to deal with deadlocks and how to lower contention. Also we need to know how to synchronize and desynchronize threads at each given state.  

Program arguments: `number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]`.

## Usage
Both programs share the same usage format: `./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]`

## Compilation
Run `make` to compile the program and have the object files. 
Run `make v` to clean and recompile and delete the object files to keep it less cluttered. 

## Norm Compliance
Ensure compliance with the project's norms regarding leaks, crashes, undefined behavior, and coding standards.

## Note
The only issue I had with this project is that the approach you take in the end is going to be somewhat similar to other people and there isn't much room for creativity at my level.

## Resources
- [The dining Philosophers | by oceanO](https://medium.com/@jalal92/the-dining-philosophers-7157cc05315)
- [Philosophers visualizer by nafuka11 on github](https://nafuka11.github.io/philosophers-visualizer/)
- [Video tutorials on threads - CodeVault](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
