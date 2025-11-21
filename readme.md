# Pixel Pong

## Descripción

`Pixel Pong` es una versión minimalista del videojuego `Pong`, programada en
`C++`, con rutinas críticas en ensamblador `x86-64`. El proyecto tiene como
objetivo demostrar las posibilidades de integración que existen entre código de
de alto y bajo nivel. Para la interfaz gráfica del juego, se emplea la
biblioteca `Raylib`.

Este proyecto es parte del curso **CI0119 - Proyecto Integrador de Lenguaje
Ensablador**, impartido por el Ing. Sleyter Angulo (Escuela de Ciencias de la
Computación e Informática - UCR), durante el II ciclo lectivo del año 2025. Los
integrantes del grupo de trabajo encargados de elaborar este proyecto son:

- [Brandon Alfaro](brandon.alfarosaborio@ucr.ac.cr)
- [David Orias](david.orias@ucr.ac.cr)
- [Enrique Ramírez](enrique.ramirez@ucr.ac.cr)
- [Joaquín Rodríguez](joaquin.rodriguezcontreras@ucr.ac.cr)

## Características principales

El juego es una réplica del ya conocido `Pong`, adaptado al contexto particular
del curso. Al iniciar, se muestra una pantalla de bienvenida que permite iniciar
la partida. La experiencia de juego consiste de un solo jugador humano contra un
bot.

Existe la posibilidad de pausar la partida con la tecla `space`. hacerlo brinda
la posibilidad de regresar a la pantalla principal de juego o retornar a la
partida.

El jugador humano es capaz de moverse hacia arriba y hacia abajo únicamente.
Es capaz de hacerlo presionando las teclas de `up` y `down` del teclado. Por
otro lado, el bot se mueve automáticamente de arriba a abajo a una velocidad
constante.

Se obtiene un punto cuando se logra que la pelota llegue a la pared de nuestra
contraparte.

## Requisitos de uso

Para ejecutar el videojuego, es necesario lo siguiente:

- Tener instalado el compilador `g++`

- Tener instalado `NASM`

- Tener instalada la biblioteca [Raylib](https://www.raylib.com/)

- Sistema operativo `Linux` `x86-64`

- Tener instalado `arduino-cli`

## Ejecución

Para ejecutar el juego, debe abrir una terminar en
`/Pixel_Pong_PI_Ensamblador_Grupo04`, ingresar `make clean`, luego `make` y
finalmente `make run`.
Seguidamente, se abrirá una ventana con el juego.

Si desea jugar de tal manera que pueda mover al jugador con un Joystick de
Arduino, lo puede hacer ingresando `make clean; make upload-arduino; make run`
en la terminal.

Para pruebas (con Google Tests), se debe ingresar `make test`

## Fuentes

Efectos de sonido: [Mixkit](https://mixkit.co/free-sound-effects/arcade/)

Instrucciones para x86-64: [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/)

Versión online de Pong: [Pong Game](https://www.ponggame.org)

Archivos para comunicación con Arduino: Adaptados con Inteligencia Artificial a partir de código facilitado por el Prof. Sleyter Angulo.

Implementación del Slider: [Claude | Anthropic](https://www.claude.ai)

Sugerencias de casos de prueba unitarios: [Claude | Anthropic](https://www.claude.ai)

Consultas sobre instrucciones en ensamblador: [Claude | Anthropic](https://www.claude.ai)
