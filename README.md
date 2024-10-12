# 42-so_long, by Maxime Rochedy

Welcome to my repository of **so_long**, a 2D game project I developed as part of my studies at **École 42**. This project earned a score of **115/100**, thanks to additional features such as **enemies** and a **move counter** displayed directly in the game window, rather than in the shell.

This version of **so_long** is designed to be **cross-compatible** between **Linux** and **macOS**, making it easy to run on both operating systems. In this repository, you'll find everything you need to compile and play the game on either platform. Even though it was carefully crafted and was evaluated by three different students, errors may still exist. Your feedback is highly appreciated!

<img width="198" alt="115/100 grade" src="https://github.com/user-attachments/assets/60b65ad4-55a9-4582-b631-76a0ecc6751d">

## About the Project

**so_long** is a fundamental project in the 42 curriculum that introduces students to basic game development concepts using **C** and the **MiniLibX** graphics library. The goal of the game is simple: guide your character through a maze, collect all the items, and find the exit while avoiding obstacles. This version of **so_long** includes some additional features to enhance the experience, like enemies and a real-time move counter in the game window.

This project was developed by **Maxime Rochedy**, under the login **mrochedy**, as part of the 42 common core curriculum. The goal of so_long is to make developers discover graphics libraries and games for the first time with a simple and straightforward game.

Please note that while this code is provided for **learning purposes**, you should not copy it for your own submissions. Using this repository responsibly will help you enhance your understanding of graphics libraries for game development. Please respect the 42 school's policies on plagiarism.

## Getting started

This project is compatible on Linux and macOS.

> If you are on macOS, make sure you have installed Xcode Command Line Tools.

To play the game, first clone the repository like so:

```bash
git clone https://github.com/mrochedy/42-so_long.git
cd 42-so_long
```

Then build and launch the game:

```bash
make
./so_long [map_file.ber]
```

The map file should be in the `.ber` format, as required by the **so_long** specifications. A `maps` folder is present at the root of the repository and contains many different maps to test the game with.

### Map Requirements

Maps must conform to the **so_long** project specifications, which are the following:

- The map must contain **exactly 1 exit** (`E`), **1 starting position** (`P`) and **at least 1 collectible** (`C`).
- The map must be **rectangular**.
- The map must be **closed/surrounded by walls** (`1`).
- There has to be a **valid path** in the map.
- The map can contain **empty squares** (`0`) and **enemies** (`e`).

My `maps` folder contains some invalid maps, for testing purposes. Custom maps can be created for more challenging gameplay, just be sure they follow the rules of the **so_long** project.

## Contributing

If you found this version of **so_long** helpful or if you have any suggestions for improvements, feel free to **⭐️ star ⭐️** the repository or create a pull request. Contributions are always welcome, but please do not submit this code as your own for official 42 project submissions. Let's help keep the learning process authentic!

Thank you for visiting and happy coding!
