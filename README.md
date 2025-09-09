# Raylib C Project

This is a simple Raylib project written in C. It serves as a starting point for building games or graphical applications using the [Raylib](https://www.raylib.com/) library.

---

## Compile
gcc src/main.c -o main -I/mingw64/include -L/mingw64/lib -lraylib -lopengl32 -lgdi32 -lwinmm

## Run
./main

project-root/
│── .vscode
│   │── tasks.json
│   └── c_cpp_properties.json
│── src/
│   └── main.c      # Entry point of the program
│── README.md
└── .gitignore