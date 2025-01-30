# Maximum Clique Finder

This repository contains an implementation of a **Bron-Kerbosch** algorithm, which finds the largest clique in an undirected graph. A **clique** is a subset of vertices such that every two vertices are adjacent.

## Features

- Efficient algorithm for finding the maximum clique.
- Utilizes smart pivoting while detecting potential cliques.

## Algorithm

This program uses the **Bron-Kerbosch algorithm** with pivoting for optimal performance. The Bron-Kerbosch algorithm is a recursive backtracking algorithm used to enumerate all maximal cliques in an undirected graph efficiently.
More specifically, this implementation detects and prints a maximum clique within the possible ones.

## Usage

You can run the program using the Makefile.
Alternatively you can use the following command:
```
gcc main.c vertex.h vertex.c -o {object_file_name}.o
```

### Input Format

The input graph should be provided as an adjacency matrix. For example:

**Adjacency Matrix Format:**

```
n
0 1 1 0
1 0 1 1
1 1 0 1
0 1 1 0
```
n - No. of total vertices.
Do note that for asymmetrical matrices the algorithm will read it as though it was symmetrical.

## Acknowledgments

- The original published paper can be found here: [https://dl.acm.org/doi/10.1145/362342.362367](https://dl.acm.org/doi/10.1145/362342.362367)
