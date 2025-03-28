# ✍️ Philosophers - 42 School Project
# 🌟 Overview
    Philosophers is a C programming project from the 42 School curriculum, tackling the classic "Dining Philosophers"   problem—a concurrency challenge where multiple entities (philosophers) share limited resources (forks) without causing deadlock or starvation. This repository contains two implementations:
    - Mandatory Part: Uses threads and mutexes to simulate philosophers eating, thinking, and sleeping.
    - Bonus Part: Uses processes and semaphores instead, offering an alternative approach to concurrency.   The program takes arguments like the number of philosophers, time to die, eat, and sleep: 
    ./philo 5 800 200 200 (Mandatory)
    ./philo_bonus 5 800 200 200 (Bonus)

# ✨ Features
    Mandatory (Threads):
        Simulates philosophers with threads (pthreads) and mutexes for fork management.
        Ensures thread safety and proper resource sharing.
    Bonus (Processes):
        Simulates philosophers with processes (via fork()) and semaphores for synchronization.
        Manages inter-process coordination.
    Common Features:
        Death detection to stop simulation if a philosopher starves.
        Configurable eating, sleeping, and death timers.

# 🚀 Installation
    Clone the repo:
          git clone https://github.com/b-kolani/philosophers.git
    Enter the directory:
    cd philo (mandatory) / philo_bonus (bonus)
# Compile:
    For the mandatory part (threads): make
    For the bonus part (processes): make

# 🖥️ Usage
    - Mandatory (Threads): ./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_meals] Example:
    ./philo 4 410 200 200
    - Bonus (Processes): ./philo_bonus [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_meals] Example:
    ./philo_bonus 4 410 200 200
    - Arguments explained:
        number_of_philosophers: Total philosophers (and forks).
        time_to_die: Time (ms) before a philosopher dies if they don’t eat.
        time_to_eat: Time (ms) a philosopher spends eating.
        time_to_sleep: Time (ms) a philosopher spends sleeping.
        number_of_meals (optional): Times each philosopher must eat before exiting.

# 📂 Project Structure
    philo.c Main function and simulation logic for the mandatory part (threads)
    philo_bonus.c Main function and simulation logic for the bonus part (processes)
    Makefile Build rules for both mandatory and bonus targets

# 🎓 Learning Outcomes
    - Mandatory: Mastered multi-threading with pthreads, mutex-based synchronization, and concurrency management.
    - Bonus: Mastered process creation with fork(), semaphore-based synchronization, and inter-process communication.
    Gained deep understanding of resource sharing, deadlock prevention, and time handling in concurrent systems.
    Improved skills in modular coding, error handling, and debugging.

# ⚙️ Requirements
    OS: UNIX-based (Linux, macOS).
    Compiler: CC or similar.
    Standard C libraries (pthread for mandatory, semaphore support for bonus).

# 👤 Author
    [KOlani Biman / b-kolani]
