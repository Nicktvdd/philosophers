# Philosophers

In the realm of philosophy, a timeless ritual unfolds: Eat, Sleep, Spaghetti, Repeat. The "Philosophers" project invites you to explore the intricate world of multi-threading and precise timing, as we guide a group of philosophers to pick up forks and savor their spaghetti without succumbing to hunger.

## Introduction

This project originated as a collaborative endeavor, with contributions from the talented minds of [Teemu](https://github.com/Stte), [Jun](https://github.com/composerjunhee), and [Rasmus](https://github.com/RushMaverick) and me. We embarked on a collective journey to tackle the challenge at hand. At the finish, I refined the codebase and reshaped the functions to align with my coding style.

## Key Concepts

- **Multi-Threading Mastery:** Dive deep into the world of multi-threading and concurrency, mastering the art of parallelism to simulate the philosophical dining experience.

- **Precise Timing:** Explore the intricacies of timing and synchronization, ensuring that philosophers pick up their forks and dine without succumbing to the hunger pangs.

- **Collaborative Development:** Witness the evolution of a group project into a refined piece of work, where individual contributions blend seamlessly into a cohesive whole.

## Getting Started

### Prerequisites

- C compiler (e.g., GCC)
- POSIX threads library (pthread)

### Installation

1. Clone the Philosophers repository:

```shell
git clone https://github.com/Nicktvdd/philosophers.git
```

2. Build the Philosophers executable:

 ```
cd philo
make
 ```

## Usage

Run Philosophers:
```
./philo [Number of philosophers] [time to die] [time to eat] [time to sleep] (optional: [times must eat])
```
Examples:
```
./philo 1 800 200 200
./philo 5 800 200 200
./philo 1 800 200 200 7
./philo 4 410 200 200
./philo 4 300 200 100
```
Only the first and the last should die, the others should live on forever (depending on hardware functioning). Testing with more that 200 philosophers is not recommended.

# Contact

If you have any questions, feedback, or inquiries, feel free to reach out to me at nicktvdd@gmail.com.

Bon appétit! 🍝🧠
