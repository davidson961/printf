#include "utils.h"

int is_printable(char c)
{
    return (c >= 32 && c <= 126);
}

int append_hexa_code(char c, char buffer[], int offset)
{
    char hex_digits[] = "0123456789ABCDEF";
    int high_nibble = (c >> 4) & 0xF;
    int low_nibble = c & 0xF;

    buffer[offset] = '\\';
    buffer[offset + 1] = 'x';
    buffer[offset + 2] = hex_digits[high_nibble];
    buffer[offset + 3] = hex_digits[low_nibble];

    return 4;
}
