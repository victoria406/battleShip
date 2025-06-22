# Battleship – PC ⇄ Arduino Edition

A bite-sized project to practise **embedded-systems thinking** from both sides of the wire:

- **PC (C++17 / Windows)** – opens `COMx`, handshakes with the board, draws the player’s grid, and sends/receives one-byte commands.  
- **Arduino Uno R3** – holds the hidden fleet, checks hits vs. misses, and replies in human-readable status codes (`hit`, `miss`, `repeat`).

---

## Features

* 5 × 5 board for lightning-fast demos  
* Simple ASCII UI on the host  
* Line-based serial protocol with explicit `READY` handshake  
* Non-blocking reads & configurable time-outs  
* Duplicate-shot detection (`repeat`)  
* Easily extensible: bigger boards, randomised ships, LED/sound feedback, etc.

---

## Quick Start

| Step | PC side | Arduino side |
|-----|---------|--------------|
| 1 | `git clone https://github.com/victoria406/battleShip.git` | Open **arduino/battleship.ino** in the Arduino IDE |
| 2 | `cd pc` | Choose the correct board & port |
| 3 | `cmake -B build && cmake --build build --config Release` | Click **Upload** |
| 4 | `build\Battleship.exe` | _enjoy!_ |

> **Tip:** the PC executable expects the board to enumerate as **`COM3`**.  
> Change the constant near the top of **pc/main.cpp** if it appears on a different port.

---

## Serial Protocol

```txt
Host  :  open COM3 9600 8N1
Board :  "Arduino command ship is ready!\r\nREADY\r\n"
Host  :  waits until it receives the literal "READY"
Host  :  'B' '4'               → two bytes: row + column
Board :  evaluates, returns    → "hit\r\n"  (or "miss", "repeat", "Invalid")
Host  :  updates grid, prompts for next shot

