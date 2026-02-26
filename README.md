# Highway Route Planner in C

## Project Summary

Designed and implemented a command-driven highway route planning system in C as part of an Algorithms and Data Structures final project.

The system models service stations positioned along a highway, each managing a fleet of electric vehicles with different driving ranges. The core objective is to compute the optimal route between two stations under strict movement and tie-breaking constraints.

---

## Key Features

- Dynamic management of service stations (add/remove)
- Fleet management per station (add/remove vehicles)
- Efficient route planning between stations
- Deterministic tie-breaking for equal-length optimal paths
- Fully command-driven architecture via standard input

---

## Technical Highlights

- Modeled the problem as a directed graph:
  - Stations → Nodes
  - Reachable stations (based on vehicle autonomy) → Edges
- Implemented a BFS-based traversal to guarantee:
  - Minimum number of stops
  - Lexicographically minimal solution in case of ties
- Managed constrained resources (max 512 vehicles per station)
- Handled 32-bit integer distance values
- Ensured deterministic and efficient behavior under dynamic updates

---

## Example Command
- pianifica-percorso distanza-stazione-partenza distanza-stazione-arrivo
  translated would be: plan-route <start-station-distance> <end-station-distance>

Outputs:
- The optimal sequence of stations
- `no route` if unreachable

---

## Build & Run

```bash
gcc main.c -o route_planner
./route_planner < input.txt
