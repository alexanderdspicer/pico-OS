/*
    Core 0 is dedicated amongst many different tasks, including (but not limited to):
    - USB handling, Including:
        - Filesystem
        - Potentially Networking and Sound
    - Networking
    - 2D rendering engine (for menus, consoles, etc)
    - Sound
    - Filesystem

    Provided USB functionality if enabled, then it will be solely delegated to Core 0, and 
    provided that Sound (over USB) and Networking (over USB) are not active, then all USB
    activity will be implemented using IRQs on an as-needed basis. 2D rendering will be nominally
    performed on Core 1, EXCEPT, when another "User-level" program needs to use Core 1, in
    such cases, 2D rendering will be shunted to Core 0, at the expense of rendering artifacts
    coninciding with USB (or other Core 0) events.

    if Sound OR Networking are enabled, then IRQs (generally speaking) are likely not
    enough to satisfy the throughput requirements, and would otherwise tie up Core 0 by constantly
    switching between IRQs. In such cases, a "Round Robin" scheduler is to be used. This scheduler 
    simply iterates through a list of function pointers and executes each, as such, each "task" is
    to be optimized to the minimum size possible.
*/

#include "tasks.h"

