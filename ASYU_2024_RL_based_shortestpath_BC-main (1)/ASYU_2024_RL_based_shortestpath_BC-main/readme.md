# ASYU_2024_RL_based_shortestpath_BC

Using reinforcement learning to find the shortest paths.

## Requirements

- numpy
- networkx



# Project Documentation

## Overview

This project contains several Python scripts for training deep reinforcement learning models to compute shortest paths, running simulations, and generating plots. Below is an explanation of each component and how to use them.

## Training

### `shortest_path.py`
This file contains the logic for finding the shortest paths in a graph. It's configured to work with various graph input files. To use it, make sure to modify the file to load the correct graph files as indicated in the comments. The necessary `.txt` files should be specified for the graph.

### `deep_rl_shortest.py` & `run_sim.py`
These two files work together for training and running simulations using deep reinforcement learning for shortest path calculation:
- **`deep_rl_shortest.py`**: Used for training the model.
- **`run_sim.py`**: Runs the simulation and outputs the results.

**Note**: These files are not fully automated. You need to manually specify the `.txt` file names and other relevant details in the code.

## Plotting

The following scripts automatically generate plots once the directories and input files are correctly set up.

### `Exec_t_figure.py`
This script generates a plot for execution time

**Usage**:
```bash
$ python3 Exec_t_figure.py {link_factor} {network_name}
```
ex run: 
```bash
$ python3 Exec_t_figure.py d_bw NSF
```

### `Perc_RS_figure.py`
This script generates a plot for percentage of requests serviced per time intervals

**Usage**:
```bash
$ Perc_RS_figure.py {link factor} {network name}
```

ex run: 
```bash
$ Perc_RS_figure.py bw US
```

