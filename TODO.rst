===============================================
Boi: a humble GameBoy emulator implemented in C
===============================================

Init:
=====

    [x] initialize CPU

    [x] load ROM

    [x] initialize memory

    [ ] initialize graphics

CPU:
====

    [x] implement all structs

    [x] main CPU cycle loop

    [ ] interrupt handler

    [-] implement opcodes

    [ ] handle clock

ESP32:
======

    [ ] implement screen driver

    [ ] implement button driver

    [ ] integrate it into emulator

Tests:
======

    [ ] do error handling well

    [ ] write unit tests

    [ ] write integration tests

    [ ] pass `Blargg's`_ tests

.. _Blargg's: https://gbdev.gg8.se/files/roms/blargg-gb-tests/

GPU:
====

    [ ] initialize GPU memory

    [ ] implement GPU cycle

Misc:
=====

    [ ] implement a CPU state dump

    [x] game Loop

    [ ] grep for TODO everywhere
