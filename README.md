# Concurrent Disk-Backed Key-Value Store

A thread-safe, disk-backed key-value store built in C++ with write-ahead logging (WAL), crash recovery, and a multithreaded benchmarking framework to evaluate system performance under concurrent workloads.

---

## Overview

This project implements a simple storage engine that supports concurrent `PUT` and `GET` operations while ensuring durability through write-ahead logging. It is designed to explore core systems concepts such as synchronization, disk I/O, and performance bottlenecks under load.

---

## Features

- Thread-safe key-value store using `std::shared_mutex`
- Write-Ahead Logging (WAL) for durability
- Crash recovery by replaying WAL on startup
- Concurrent read/write handling with proper synchronization
- Multithreaded benchmarking framework
- Throughput and P99 latency measurement

---

## Architecture

### Write Path (`PUT`)
1. Acquire exclusive lock  
2. Append operation to WAL  
3. Update in-memory hash map  

### Read Path (`GET`)
1. Acquire shared lock  
2. Fetch value from in-memory store  

### Recovery
- On startup, the WAL file is replayed to rebuild the in-memory state

---

## Benchmarking

The project includes a benchmarking tool to evaluate:

- Throughput (operations per second)
- P99 latency (tail latency)
- Performance under different concurrency levels
- Behavior under different workloads:
  - Write-heavy (0% reads)
  - Mixed (50% reads)
  - Read-heavy (90% reads)

---

## Sample Results

```

==== Write Heavy (0% reads) ====
Threads: 1 | Throughput: 400000 ops/sec | P99 Latency: 0.0065 ms
Threads: 2 | Throughput: 370370 ops/sec | P99 Latency: 0.008417 ms
Threads: 4 | Throughput: 314961 ops/sec | P99 Latency: 0.109583 ms
Threads: 8 | Throughput: 157480 ops/sec | P99 Latency: 0.342834 ms

==== Mixed (50% reads) ====
Threads: 1 | Throughput: 1.25e+06 ops/sec | P99 Latency: 0.002083 ms
Threads: 2 | Throughput: 769231 ops/sec | P99 Latency: 0.047958 ms
Threads: 4 | Throughput: 533333 ops/sec | P99 Latency: 0.0885 ms
Threads: 8 | Throughput: 286738 ops/sec | P99 Latency: 0.230833 ms

==== Read Heavy (90% reads) ====
Threads: 1 | Throughput: 5e+06 ops/sec | P99 Latency: 0.001833 ms
Threads: 2 | Throughput: 2.5e+06 ops/sec | P99 Latency: 0.015833 ms
Threads: 4 | Throughput: 1.6e+06 ops/sec | P99 Latency: 0.042833 ms
Threads: 8 | Throughput: 898876 ops/sec | P99 Latency: 0.113583 ms

```

---

## Key Observations

- Write-heavy workloads do not scale well due to lock contention and serialized WAL writes  
- Read-heavy workloads achieve higher throughput due to shared locking  
- P99 latency increases with higher concurrency due to contention and disk I/O  
- WAL introduces a bottleneck for write operations  

---

## Build Instructions

```bash
g++ src/wal.cpp src/kv_store.cpp benchmark/benchmark.cpp -I src -std=c++20 -O2 -pthread -o kv_benchmark
```

## Run Benchmark

```bash
./kv_benchmark
```