# Dining Philosophers

The classic computer science problem of the [Dining Philosophers](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## About the problem

A user defined amount of philosophers dine together at a table. Each of them brings one fork, but needs two to eat, so they have to share with each other.
They all have a user defined:

* Time to eat. - The time it takes for a philosopher to eat. During that time, they will need to hold two forks.

* Time to sleep. - The time a philosopher will spend sleeping.

* Time to die. - If a philosopher didn’t start eating "Time to die" milliseconds since the beginning of their last meal or the beginning of the simulation, they die.

## WHY?

This problem aims to illustrate [Concurrency](https://en.wikipedia.org/wiki/Concurrency_(computer_science)), proper use of shared resources and time efficiency.

## How was it solved?

The problem was solved in two separate ways:

1. Using **threads** for synchronous operations between philosophers and **mutexes** to ensure proper use of the resources.

2. Using **Processes**(forks) and **semaphores**, for the same reasons, respectively.