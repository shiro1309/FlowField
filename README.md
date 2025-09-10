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


YourGameName/
├── src/
│   ├── main.c           // Main game loop and initialization
│   ├── game.h           // Game-specific declarations and structures
│   ├── game.c           // Game logic, updates, and drawing
│   ├── entities/        // (Optional) For Entity-Component-System (ECS) or complex entities
│   │   ├── player.h
│   │   ├── player.c
│   │   └── ...
│   ├── systems/         // (Optional) For ECS systems
│   │   ├── rendering_system.h
│   │   ├── rendering_system.c
│   │   └── ...
│   └── utils/           // Helper functions and utilities
│       ├── collision.h
│       ├── collision.c
│       └── ...
├── assets/
│   ├── textures/        // Image files (PNG, JPG)
│   ├── sounds/          // Sound effects (WAV, OGG)
│   ├── music/           // Background music (MP3, OGG)
│   ├── fonts/           // Font files (TTF, OTF)
│   └── models/          // 3D models (GLTF, OBJ)
├── build/               // Compiled executables and intermediate files
├── lib/                 // raylib library files (if not using a system-wide installation)
├── include/             // raylib header files (if not using a system-wide installation)
├── Makefile             // (Or other build system files like CMakeLists.txt, .vscode/tasks.json)
└── README.md            // Project description and instructions