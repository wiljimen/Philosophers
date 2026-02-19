*This project has been created as part of the 42 curriculum by wiljimen.*

# Philosophers

> C implementation of the classic *Dining Philosophers* problem using threads and mutexes.

---

## Description

**Philosophers** is a 42 curriculum project focused on the fundamentals of **concurrency and thread synchronization** in C.

The project simulates the *Dining Philosophers* problem, where several philosophers sit at a table and alternate between:

- Eating  
- Sleeping  
- Thinking  

To eat, a philosopher must hold two forks (shared resources).  
The challenge is to coordinate threads to avoid:

- Deadlocks.
- Starvation.
- Race conditions.

This project provides hands-on experience in managing shared resources and synchronizing multiple threads safely.

---

## Instructions

./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

### Compilation

make

### Resources

POSIX Threads Manual

man pthread_create

man pthread_mutex_lock

The Dining Philosophers Problem — Edsger Dijkstra.

This YouTube videos:
- https://www.youtube.com/watch?v=tvgU3-RzAqk&list=PL19snTOMdnWv3-ceesGoZ9FhKqPrEHJjT
- https://youtu.be/zOpzGHwJ3MU?si=a2aNsT-TXhCDnL56
- https://youtu.be/8KFvrgbuWxY?si=Evu5CrwOHTKt0BKe

### AI Usage

AI tools like ChatGPT and Gemini were used as support for:

- Understanding concurrency concepts.

- Clarifying theoretical doubts.

- Suggesting test cases.

Architecture design, implementation, and debugging were performed manually by the authors.
