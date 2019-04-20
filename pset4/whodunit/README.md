# Questions

## What's `stdint.h`?

A header file that provides a set of typedefs that specify exact-width integer types

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They provide integers that are exactly a certain number of bits so you can use the amount of space you want

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

1, 4, 4, 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

0x424d

## What's the difference between `bfSize` and `biSize`?

bfSize is the size, in bytes, of the bitmap file.
biSize is the number of bytes required by the structure.

## What does it mean if `biHeight` is negative?

The bitmap is top-down and its origin is the upper-left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file that it is trying to write to does not exist.

## Why is the third argument to `fread` always `1` in our code?

The third argument of fread specifies how many elements you want to read.
We are always reading 1 struct.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Moves the file pointer position to a specific location

## What is `SEEK_CUR`?

SEEK_CUR is the current position in the file

## Whodunit?

It was professor plum with the candlestick in the library
