## Title
Sorting Algorithms & Performance Benchmark

## Full Name 
Hani Omar

# group 
Group 01

# academy year
2026/2027

# Language & Version
C11 (ISO/IEC 9899:2011)

# The Library used
stdio.h
stdlib.h
windows.h
psapi.h

# Instructions to install
Open a terminal in the project folder, compile the source files, and run the executable:
gcc -std=c11 -O2 src/main.c src/sorting.c src/benchmark.c src/utils.c -o sorting.exe -lpsapi
sorting.exe

# Algorithm Descriptions & Complexities

## Bubble Sort: 
Repeatedly steps through the array, compares adjacent elements, and swaps them if they are in the wrong order. With an early-exit flag, it stops early when a pass makes no swaps.
Time: Best $O(n)$ (already sorted with early exit) | Average $O(n^2)$ | Worst $O(n^2)$
Space: $O(1)$ auxiliary (in-place)

## Selection Sort: 
Divides the array into a sorted left part and an unsorted right part, repeatedly finding the minimum element from the unsorted part and placing it at the end of the sorted part.
Time: Best $O(n^2)$ | Average $O(n^2)$ | Worst $O(n^2)$
Space: $O(1)$ auxiliary (in-place)

## Insertion Sort: 
Builds the sorted array one element at a time by taking the next element and shifting larger elements to the right until finding its proper position.
Time: Best $O(n)$ (already sorted) | Average $O(n^2)$ | Worst $O(n^2)$
Space: $O(1)$ auxiliary (in-place)

## Merge Sort: 
Uses a divide-and-conquer approach—splits the array in half recursively, sorts each half, and merges the sorted halves back together.
Time: Best $O(n \log n)$ | Average $O(n \log n)$ | Worst $O(n \log n)$
Space: $O(n)$ auxiliary (uses temporary subarrays during merging, plus $O(\log n)$ recursion stack)

## Quick Sort: 
Selects a pivot element (median-of-three: first, middle, and last elements in our implementation), partitions elements around the pivot so smaller elements go before it and larger ones after it, then recursively sorts both sides.
Time: Best $O(n \log n)$ | Average $O(n \log n)$ | Worst $O(n^2)$ (unbalanced partitions)
Space: $O(\log n)$ average recursion stack ($O(n)$ worst-case stack depth)

# The comparison results

## array 1000 element

+----------------------+------------+---------------+---------------+------+
| Algorithm            | Array Size | Time (ms)     | Memory (MB)   | Rank |
+----------------------+------------+---------------+---------------+------+
| Bubble Sort          | 1000       | 9.294         | 4.8906        | 5    |
| Selection Sort       | 1000       | 3.838         | 4.8906        | 4    |
| Insertion Sort       | 1000       | 1.326         | 4.8906        | 3    |
| Merge Sort           | 1000       | 0.305         | 4.8906        | 2    |
| Quick Sort           | 1000       | 0.143         | 4.8906        | 1    |
+----------------------+------------+---------------+---------------+------+

## array 5000 element

+----------------------+------------+---------------+---------------+------+
| Algorithm            | Array Size | Time (ms)     | Memory (MB)   | Rank |
+----------------------+------------+---------------+---------------+------+
| Bubble Sort          | 5000       | 163.476       | 4.8906        | 5    |
| Selection Sort       | 5000       | 89.006        | 4.8906        | 4    |
| Insertion Sort       | 5000       | 43.747        | 4.8906        | 3    |
| Merge Sort           | 5000       | 0.812         | 4.8906        | 1    |
| Quick Sort           | 5000       | 0.823         | 4.8906        | 2    |
+----------------------+------------+---------------+---------------+------+

## array 10000 element

+----------------------+------------+---------------+---------------+------+
| Algorithm            | Array Size | Time (ms)     | Memory (MB)   | Rank |
+----------------------+------------+---------------+---------------+------+
| Bubble Sort          | 10000      | 635.918       | 4.8906        | 5    |
| Selection Sort       | 10000      | 196.698       | 4.8906        | 4    |
| Insertion Sort       | 10000      | 106.053       | 4.8906        | 3    |
| Merge Sort           | 10000      | 2.073         | 4.8906        | 2    |
| Quick Sort           | 10000      | 1.526         | 4.8906        | 1    |
+----------------------+------------+---------------+---------------+------+

## array 50000 element

+----------------------+------------+---------------+---------------+------+
| Algorithm            | Array Size | Time (ms)     | Memory (MB)   | Rank |
+----------------------+------------+---------------+---------------+------+
| Bubble Sort          | 50000      | Skipped       | Skipped       | -    |
| Selection Sort       | 50000      | Skipped       | Skipped       | -    |
| Insertion Sort       | 50000      | Skipped       | Skipped       | -    |
| Merge Sort           | 50000      | 11.113        | 4.8906        | 2    |
| Quick Sort           | 50000      | 9.854         | 4.8906        | 1    |
+----------------------+------------+---------------+---------------+------+

## array 100000 element

+----------------------+------------+---------------+---------------+------+
| Algorithm            | Array Size | Time (ms)     | Memory (MB)   | Rank |
+----------------------+------------+---------------+---------------+------+
| Bubble Sort          | 100000     | Skipped       | Skipped       | -    |
| Selection Sort       | 100000     | Skipped       | Skipped       | -    |
| Insertion Sort       | 100000     | Skipped       | Skipped       | -    |
| Merge Sort           | 100000     | 25.010        | 4.8906        | 2    |
| Quick Sort           | 100000     | 20.287        | 4.8906        | 1    |
+----------------------+------------+---------------+---------------+------+

## specifications of my machine

CPU: Intel(R) Core(TM) i5-7200U CPU @ 2.50GHz (2.71 GHz)
Memory: 8.00 GB	Speed:	2133 MHz
Windows: 11 Pro

## Critical Analysis

### Best Algorithm by Scenario

## Large random datasets ($n \ge 100,000$):
Quick Sort: is best in practice when average execution time matters most (`20.287 ms` on `100,000` random elements) while keeping memory usage low (`4.8906 MB` process working set).

## *Guaranteed worst-case speed or stability:
Merge Sort: is ideal when consistent $O(n \log n)$ performance is required regardless of input order (`25.010 ms` on `100,000` random elements), provided extra auxiliary memory is acceptable.

## Small or nearly sorted arrays:
Insertion Sort: works efficiently on small inputs (`1.326 ms` at `1,000` elements) or nearly sorted data where shifting requires minimal work and recursion overhead is avoided.

## Tight memory / minimal swaps:
Selection Sort: uses $O(1)$ extra space and performs at most $O(n)$ swaps, though its $O(n^2)$ comparisons make it slow on large datasets (`196.698 ms` at `n = 10,000`).

## Basic learning / simple checks:
Bubble Sort: is mainly useful for demonstrating adjacent swaps and early exit, as it is the slowest on large inputs (`635.918 ms` at `n = 10,000`).

### Do Experiments Match Theory?
**Yes.** On `10,000` random elements, $O(n \log n)$ algorithms (**Quick Sort** at `1.526 ms` and **Merge Sort** at `2.073 ms`) vastly outperform $O(n^2)$ algorithms (`106.053 ms` to `635.918 ms`), matching theoretical growth rates. Scaling from `1,000` to `10,000` elements ($10\times$ increase) caused **Bubble Sort** to take roughly $68\times$ longer (`9.294 ms` to `635.918 ms`), confirming quadratic growth, while **Quick Sort** scaled near-linearly (`0.143 ms` to `1.526 ms`, and `20.287 ms` at `100,000`). Note that using median-of-three pivot selection keeps **Quick Sort** efficient on sorted inputs as well.

### Problems Faced & Solutions

# Invalid input handling:
Entering non-numeric characters caused `scanf` input issues; fixed by validating input return values and clearing remaining buffer characters cleanly.

# Accurate multi-run timing:
Reusing the same array across `5` benchmark runs would measure already-sorted data after the first pass; solved by copying the original array before each run and freeing the copy afterward.

# Long wait times on large $O(n^2)$ runs:
Running `5` iterations of quadratic algorithms on `50,000` and `100,000` elements took excessive time; solved by automatically skipping $O(n^2)$ algorithms above `10,000` elements during full comparison mode while benchmarking Merge Sort and Quick Sort up to `100,000` elements.


## Overview
A C program implementing and comparing five sorting algorithms (**Bubble Sort**, **Selection Sort**, **Insertion Sort**, **Merge Sort**, and **Quick Sort**) across different array sizes and input distributions, measuring execution time and memory usage through an interactive menu.

#   S o r t i n g _ H o m e W o r k 