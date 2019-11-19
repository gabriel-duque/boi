# Purpose of this project

* Explore how the Game Boy actually works

* Learn about emulation and low-level details

* Discover hardware

* Nostalgia

# Table of contents

* Quick history of the Game Boy

* Game Boy specifications

* CPU

* Graphics

# A quick history of the Game Boy

* First release: 1989 (until 2005)

* Code name: DMG-01

* About 118 M sales

* ~1500 Games

# Different types of Game Boy

Original series:

* Game Boy (DMG-01): 1989

* Game Boy Pocket (MGB-001): 1996

* Game Boy Light (MGB-101): 1998

* Game Boy Color (CGB-001): 1998

Arm CPU based Game Boy (backwards compatible) :

* Game Boy Advance (AGB-001): 2001

* Game Boy Advance SP (AGS-001): 2003

* Game Boy Advance SP (AGB-101): 2005

# Specifications

* CPU: 1Mhz - 8 bits

* RAM: 8KB

* VRAM: 8KB

* Resolution: 160 x 144

* 4 colors (shades of "gray")

* 10 sprites per line

Probably the last used 8 bit system for video games.

# Interior

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/dmg_front.png}

\end{center}

# Interior

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/dmg_back.png}

\end{center}

# The DMG chip

* CPU core

* Interrupt controller

* Timer

* Memory management unit

* Boot ROM

* Joypad input

* Serial data transfer (not implemented)

* Sound controller (not implemented)

* Pixel processing unit

# The CPU: Sharp LR35902

* Sort of like an Intel 8080, but not really

* Sort of like an Zilog Z80, but not really

A f****** mess!

# The CPU: Sharp LR35902

\begin{center}

\includegraphics[width=0.4\textwidth]{assets/cpu1.png}

\end{center}

# The CPU: Sharp LR35902

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/cpu2.png}

\end{center}

# The CPU: Sharp LR35902

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/cpu3.png}

\end{center}

# Registers

8 bit registers:

|     |     |
|:---:|:---:|
|  A  |  F  |
|  B  |  C  |
|  D  |  E  |
|  H  |  L  |

16 bit registers:

|           |
|:---------:|
|    SP     |
|    PC     |

Flag register:

\begin{center}

| Z | N | H | C | - | - | - | - |

\end{center}

# Instructions

\begin{center}

\includegraphics[width=1\textwidth]{assets/op.png}

\end{center}

# CB-prefix

\begin{center}

\includegraphics[width=1\textwidth]{assets/op_cb.png}

\end{center}

# Interrupt model

* Jumps to fixed location in RAM

* You jump there by using special instructions

# System clocks

|      |      |
|:----:|:----:|
| CPU  | 4 MHz|
| RAM  | 1 MHz|
| PPU  | 4 MHz|
| VRAM | 2 MHz|

\begin{center}

1 machine cycle @ 1MHz

\end{center}

# The bootup sequence

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/boot.png}

\end{center}

# Header

\begin{center}

\includegraphics[width=0.8\textwidth]{assets/header.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem1.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem2.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem3.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem4.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem5.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem6.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem7.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem8.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem11.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem12.png}

\end{center}

# Memory map

\begin{center}

\includegraphics[width=1.0\textwidth]{assets/mem13.png}

\end{center}

# Pixel processing unit

* 160x144 pixels

* 4 shades of "gray"

* 8x8 tiles

* 20x18 tiles

* 40 sprites (10 per line)

* 8 KB VRAM

# Pixel processing unit

3 grounds in graphics:

* Background

* Window

* Sprites (Nintendo calls them objects)

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/tet.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/tet_scale.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/dk.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/dk_scale.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/bg_tile.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/tiles.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/tennis_bg.png}

\end{center}

# Pixel processing unit

Actually the background is just a view of a bigger surface
which is 32x32 tiles.

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/views.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/win.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/win_score.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/sprites.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.35\textwidth]{assets/oam.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/gup.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/gupa.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/gdown.png}

\end{center}

# Pixel processing unit

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/gdowna.png}

\end{center}

# It's meme time

\begin{center}

\includegraphics[width=0.7\textwidth]{assets/selfies.png}

\end{center}

# Just for the lulz

\begin{center}

\includegraphics[width=0.5\textwidth]{assets/cam.jpg}

\end{center}

# Just for the lulz

\begin{center}

\includegraphics[width=0.55\textwidth]{assets/print.jpg}

\end{center}

# Just for the lulz

\begin{center}

\includegraphics[width=0.9\textwidth]{assets/images.jpg}

\end{center}

# Source code

If you want to check the code out:

\begin{center}

https://git.zuh0.com/boi

\end{center}

You can send patches by mail!

It is \textbf{commented}.

Resources:

\begin{center}

https://github.com/gbdev/awesome-gbdev

http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf

https://gbdev.gg8.se/files/roms/blargg-gb-tests/

\end{center}
