<p align="center">
    <img href="Assets/banner.jpg" src="Assets/banner.jpg" width="100%">
</p>

> Saturday. July 2nd, 2016

# Raptor B - RoboCup Rescue Maze

<img align="right" src="Assets/RaptorB.jpg" width="30%">

Aiming to participate in the **RoboCup Rescue Maze** competition, we developed a **robot** capable of travelling a **maze** looking for **heat victims**.

This repository contains the latest version of the source code used in that robot on RoboCup Germany in 2016.

The code here is published "as is", which means there was no code review nor it's granted to work properly (this repository is just for archival purposes).

See the robot working: [watch video](https://www.youtube.com/watch?v=Wu9DYnvc1BU&list=PLDN8gBFJnTTuKxWZ3ajpXCG3o9lmeILe6&index=3)

**Raptor B Team (2016):**
- Italo Lelis de Carvalho, João Pedro Rosada Canesin

**Instructor:**
- Igor Araujo Dias Santos

---

## Software

### Tremaux Algorithm 

To explore the maze, it's used an algorithm called "Tremaux". This algorithm makes the robot goes right always as possible. If the robot cannot go right, it goes forward and, in the last scenario, goes left.

| ![](Assets/tremaux2.png) | ![](Assets/tremaux1.png) |
|-|-|

You can read more about Tremaux Algorithm in here: [Interlude • Tremaux’s Algorithm
](http://blog.jamisbuck.org/2014/05/12/tremauxs-algorithm.html)

### A* Algorithm

To make the robot return to it's initial position, a pathfinder algorithm called A* (A-Star) is used. Both distances of each position on the map to the destination and to the current position are evaluated, and them the algorithm routes the path with the least sum of those distances. This assures that the robot will follow the shortest path possible to it's initial position.

| ![](Assets/a_star1.png) | ![](Assets/a_star2.png) |
|-|-|

The implementation of the algorithm is based on the project [A* Search on Processing](https://github.com/italohdc/maze-solving).


## Hardware

We used two microcontrollers on the robot: an [Arduino Due](Due/) as the main board and an [Arduino Nano](Nano/) as a secondary board.

The [Arduino Due](Due/) executes functions to handle actuators and most sensors, as well as the main algorithm.

The [Arduino Nano](Nano/) reads the heat sensor and communicates with the main board.

<p align="center">
    <img href="Assets/hardware.png" src="Assets/hardware.png" width="100%">
</p>

### Components

- Microcontrollers
    - **Arduino Due** (Main):
        - 1x **Light sensors**
        - 1x **Inertial Measurement Unit**
        - 4x **Ultrasonic sensors**
        - 8x **Infrared sensors**
    - **Arduino Nano** (Secondary):
        - 4x **Temperature sensors**

- Motors
    - 4x **DC Motors** (connected to H-Bridges)
    - 1x **Servo Motors**

- LCD Display
    - **LEDs**
    - **Push-Buttons**

---

## Awards

| Year | Competition           | Location               | Position |
|------|-----------------------|------------------------|----------|
| 2012 | LARC* / CBR**         | Fortaleza, Brazil      | 2nd      |
| 2013 | RoboCup Junior        | Eindhoven, Netherlands | 2nd      |
| 2013 | LARC/CBR              | Fortaleza, Brazil      | 1st      |
| 2014 | RoboCup Junior        | João Pessoa, Brazil    | 3rd      |
| 2014 | LARC/CBR              | São Carlos, Brazil     | 1st      |
| 2015 | LARC/CBR              | Uberlândia, Brazil     | 1st      |
| 2016 | RoboCup Junior        | Leipzig, Germany       | 9th      |

\* LARC - Latin American Robotics Competition

\** CBR - Brazilian Robotics Competition

## Acknowledgments

This project was made possible with the effort of many people. There was hard work and countless nights staying up until late.

I would like to thanks those indirectly related to this project, as our parents, faculty and event organizers. Also, a special thanks to those directly related to this project, who helped it grow the way it did:

- [Colégio Nossa Senhora de Fatima - Sacramentinas](http://colegiosacramentinas.com.br/)
- Andrique Figueiredo Amorim
- Daniel Hymer dos Santos Frota
- Hugo Santos Dias
- Joao Paulo Sandes Brito
- Joao Pedro Vilas Boas Silva
- Luiz Victor Fonseca Brasil
- Luisa Silva Oliveira
- Marilia de Mello Amorim Novais e Silva
