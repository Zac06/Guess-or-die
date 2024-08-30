# Guess or DIE

This game, build around my own SDL2 abstraction layer (SDL_base), is a guessing game (take for example the show \"Who wants to be a millionaire?\"), that gives you some... penalties, you could say. 

---

WARNING: **SAVE YOUR WORK** before launching the game. Penalties are mild, but annoying if you're |working on something important. Have fun!

---

### Compiling
#### Windows
Execute the following command in the project's root directory, after installing SDL2, SDL2_mixer, SDL2_ttf and SDL2_image:
```
g++ -Ofast -L C:/SDL2-w64/lib -Iinclude src/*.cpp src/base_elements/*.cpp src/gui_elements/*.cpp src/rendering/*.cpp src/game_elements/*.cpp -o bin/windows/GuessOrDie -m64 -lmingw32 -lole32 -lntdll -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -mwindows
```
