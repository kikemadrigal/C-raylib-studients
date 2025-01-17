@echo off&cls&call:main %1&goto:EOF

:main
    echo Murciadevs 2025
    rem Ckequeando parámetros
    if [%1]==[] (call :create_desktop)
    if [%1]==[web] (call :create_web)
    if [%1]==[android] (call :create_android)

    rem Si el argumento no está vacío, ni es dsk, ni es cas, etc
    rem If the argument is not empty, neither is it dsk, nor is it cas, etc.
    rem if [%1] NEQ [] (
    rem     if [%1] NEQ [web] (
    rem         if [%1] NEQ [android] (
    rem             if [%1] NEQ [clean] (call :help)   
    rem         )
    rem     )
    rem )    
goto:eof

:help
     echo No reconozco la sintaxis, pon:
     echo .
     echo make [web] [android]
goto:eof

:create_desktop
    rem ----------------------------------
    rem compilando para windows
    rem ----------------------------------
    rem Ve al artículo https://murciadevs.tipolisto.es/wp-admin/edit.php?post_type=post para ver como instalar un compilador de C en widows
    rem en resumen para compilar en widws necesitas tener instalado Msys2+mingw32-make y raylib
    gcc -o game.exe src\physics.c src\ecs.c src\game.c src\input.c src\player.c src\main.c -I.\include -lraylib -lgdi32 -lwinmm
    .\game.exe
goto:eof

:create_web
    echo Elegiste crear web
    rem ----------------------------------
    rem compilando para web con emscripten
    rem https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5)
    rem para generar la musica xm: https://github.com/milkytracker/MilkyTracker/releases/tag/v1.05.01
    rem ----------------------------------
    rem https://www.youtube.com/watch?v=j6akryezlzc
    start emcc -o main.html src\physics.c src\ecs.c src\game.c src\input.c src\player.c src\main.c -Wall -std=c99 -D_DEFAULT_SOURCE -Wno-missing-braces -Wunused-result -Os -I.\include -I C:\raylib\src -I C:\raylib\src\external -L C:\raylib\src -s USE_GLFW=3 -s ASYNCIFY -s TOTAL_MEMORY=67108864 -s FORCE_FILESYSTEM=1 --preload-file resources --preload-file sounds --shell-file C:\raylib\src\shell.html C:\raylib\src\web\libraylib.web.a -DPLATFORM_WEB -s EXPORTED_RUNTIME_METHODS=ccall
    rem copy main.data docs
    rem copy main.html docs
    rem copy main.js docs
    rem copy main.wasm docs
goto:eof

:create_android
    rem ----------------------------------
    echo Not implemented
goto:eof

