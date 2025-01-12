
rem ----------------------------------
rem compilando para windows
rem ----------------------------------
rem Ve al artículo https://murciadevs.tipolisto.es/wp-admin/edit.php?post_type=post para ver como instalar un compilador de C en widows
rem en resumen para compilar en widws necesitas tener instalado Msys2+mingw32-make y raylib
rem gcc -o game.exe src\game.c src\input.c src\player.c src\main.c -I.\include -lraylib -lgdi32 -lwinmm
rem .\game.exe


rem ----------------------------------
rem compilando para web con emscripten
rem https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
rem ----------------------------------
rem https://www.youtube.com/watch?v=j6akryezlzc
emcc -o main.html src\game.c src\input.c src\player.c src\main.c -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I.\include -I C:\raylib\src -I C:\raylib\src\external -L C:\raylib\src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --shell-file C:\raylib\src\shell.html C:\raylib\src\web\libraylib.web.a -DPLATFORM_WEB -s EXPORTED_RUNTIME_METHODS=ccall

