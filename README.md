# Assembly Line Simulation Project

Welcome to the Assembly Line Simulation project README. This project simulates an assembly line where customer orders move through different stations until they're completed or face challenges along the way.

## Table of Contents

1. [Introduction](#introduction)
2. [Features](#features)
3. [Getting Started](#getting-started)
4. [Usage](#usage)
5. [Project Structure](#project-structure)
6. [Contributing](#contributing)
7. [License](#license)

---

## Introduction

Hey there! Ever wondered how orders get processed on a real assembly line? This project dives into that world, simulating how orders move through stations, get assembled, and sometimes hit a bump in the road.

---

## Features

- **Order Flow:** Watch as orders progress from `g_pending` to `g_completed` or `g_incomplete`.
  
- **Workstation Dynamics:** Each `Station` and `Workstation` plays a role in moving orders along efficiently.

- **Error Handling:** Robust mechanisms ensure the simulation keeps running smoothly even when issues arise.

- **Modular Design:** Components like `CustomerOrder` and `Utilities` are designed for easy customization and extension.

---

## Getting Started

Ready to dive in? Follow these simple steps:

1. **Clone the Repository:**
   ```bash
   git clone <repository_url>
   cd AssemblyLineSimulation
   ```

2. **Build the Project:**
   ```bash
   g++ -std=c++11 *.cpp -o assembly_line_simulation
   ```

3. **Run the Simulation:**
   ```bash
   ./assembly_line_simulation <input_file_1> <input_file_2> <input_file_3> <input_file_4>
   ```

---

## Usage

Once the simulation is running, keep an eye on the console output to see orders moving through different stations. It's like peeking behind the curtain of a real assembly line!

---

## Project Structure

- **`Station` and `Workstation` Classes:** Manage the flow of items and orders through the assembly line.

- **`CustomerOrder` Class:** Represents customer orders with functions for handling item fills and order statuses.

- **`Utilities` Class:** Provides utilities for parsing input files and managing tokens.

---

## Contributing

Feel like contributing to make this simulation even better? Fork the repository, make your changes, and send us a pull request. Let's build this assembly line together!


