# Objectif : Modeling the [Philosophers' problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

## Introduction of thread and mutex
- Philosophers are represented by threads.
- forks are represented by mutex.
  ![apercu](https://github.com/souelgha/42_Philosophers/blob/main/philo.png)

## Build and start
run a make
```bash
make
```
use this configuration to start 
  ``` bash
 ./philo 5 800 200 200 3
```
  - argv[1] = nb philosophers
  - argv[2] = time to die(ms)
  - argv[3] = time to eat(ms)
  - argv[4] = time to sleep(ms)
  - argv[5] = nb meal to eat (optionnal)

## Output
The output of the program is in the format <timestamp> <philosopher (1 to number_of_philosophers)> <action>
The logged messages are always in sequential order.



[visualiszer](https://nafuka11.github.io/philosophers-visualizer/)

