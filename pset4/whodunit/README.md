# Questions

## What's `stdint.h`?

Library for different -bit integer assignment

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

typedef structure to assign same int bit-type to variables.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

`BYTE`  8 bits = 1 byte
`DWORD` 32 bits = 4 bytes
`LONG`  signed 32 bits = 4 bytes
`WORD`  16 bits = 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

The first two bytes of any BMP file must contain ASCII B then ASCII M.

## What's the difference between `bfSize` and `biSize`?

bfSize is the size of the bmp file. biSize is the size of the structure in bytes.

## What does it mean if `biHeight` is negative?

If biHeight is postive, the image is bottom up. If biHeight is negative, the image is bottom down.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount specifies the BMP's color depth - the number of bits per pixel.

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

fopen might return a NULL pointer if the file that fopen is trying to write to doesn't exist.

## Why is the third argument to `fread` always `1` in our code?

We are going through every (1) pixel.

## What value does line 65 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
RGBTRIPLE is 3 bytes, width is 3, so 3*3 = 9, which has remainder, so we add 3  more lines to bee able to /4 without remainders.

## What does `fseek` do?

fseek changes pointer offset.

## What is `SEEK_CUR`?

SEEK_CUR is the current position indicator in the file.

## Whodunit?

It was Professor Plum with the candlestick in the library.
