#include <stddef.h>
#include <stdint.h>

enum vga_colors
{
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHTGREY,
    DARKGREY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    LIGHTBROWN,
    WHITE
};

uint8_t makeColor(enum vga_colors fg, enum vga_colors bg)
{
    return fg|bg << 4;
}

uint16_t makeVgaEntry(char c, uint8_t color)
{
    uint16_t char16 = c;
    uint16_t color16 = color;
    return char16 | color16 << 8;
}

size_t strlen(const char *str)
{
    size_t i = 0;
    for(; str[i]; i++);
    return i;
}

static const size_t VgaWidth = 80;
static const size_t VgaHeight = 25;

size_t termRow;
size_t termCol;
uint8_t termColor;
uint16_t *termBuf;

void initTerm(void)
{
    termRow = termCol = 0;
    termColor = makeColor(BLACK, WHITE);
    termBuf = (uint16_t*)0xB8000;
    for (size_t y = 0; y < VgaHeight; y++)
    {
	for (size_t x = 0; x < VgaWidth; x++)
	{
	    const size_t idx = (y * VgaWidth) + x;
	    termBuf[idx] = makeVgaEntry(' ', termColor);
	}
    }
}

void Term_setColor(uint8_t color)
{
    termColor = color;
}

void Term_putCharAt(char c, uint8_t color, size_t x, size_t y)
{
    const size_t idx = (y * VgaWidth) + x;
    termBuf[idx] = makeVgaEntry(c, color);
}

enum ScrollDir
{
    SCROLLUP = 1,
    SCROLLDOWN = -1,
};

void Term_scroll()
{
    termBuf[1*VgaWidth] = 'm';
}

void Term_putChar(char c)
{
    if (c != '\n')
    {
	Term_putCharAt(c, termColor, termCol, termRow);
	if (++termCol == VgaWidth)
	{
	    termCol = 0;
	    termRow++;
	}
    }
    else
    {
	termCol = 0;
	termRow++;
    }
    if (termRow == VgaHeight)
    {
        Term_scroll(SCROLLDOWN);
    }
}

void Term_putString(const char *data)
{
    size_t len = strlen(data);
    for (size_t i = 0; i < len; i++)
    {
	Term_putChar(data[i]);
    }
}

void kmain(void)
{
    initTerm();
    Term_putString("Fuck off!\n\n");
}
