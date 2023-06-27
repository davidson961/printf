#include "main.h"
#include <unistd.h>
#define BUFF_SIZE 1024
void print_buffer(char buffer[], int *buff_ind);
int handle_print(const char *format, int *i, va_list list, char buffer[],
int flags, int width, int precision, int size);
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size);

int _printf(const char *format, ...)
{
int i, printed = 0, printed_chars = 0;
int flags, width, precision, size, buff_ind = 0;
va_list list;
char buffer[BUFF_SIZE];
if (format == NULL)
return -1;
va_start(list, format);
for (i = 0; format[i] != '\0'; i++)
{
if (format[i] != '%')
{
buffer[buff_ind++] = format[i];
if (buff_ind == BUFF_SIZE)
print_buffer(buffer, &buff_ind);
printed_chars++;
}
else
{
print_buffer(buffer, &buff_ind);
flags = 0; /* call get_flags(format, &i) */
width = 0; /* get_width(format, &i, list) */
precision = 0; /* get_precision(format, &i, list) */
size = 0; /* get_size(format, &i) */
++i;
printed = handle_print(format, &i, list, buffer,
flags, width, precision, size);
if (printed == -1)
return -1;
printed_chars += printed;
}
}
print_buffer(buffer, &buff_ind);
va_end(list);
return printed_chars;
}
void print_buffer(char buffer[], int *buff_ind)
{
if (*buff_ind > 0)
{
write(1, buffer, *buff_ind);
*buff_ind = 0;
}
}
int handle_write_char(char c, char buffer[], int flags, int width, int precision, int size)
{
int i = 0;
char padd = '';
/* unused parameter */
(void)size;
(void)precisio;
if (flags & F_ZERO)
padd = '0';
buffer[i++] = c;
buffer[i] = '\0';
if (width > 1)
{
buffer[BUFF_SIZE - 1] = '\0';
for (i = 0; i < width - 1; i++)
buffer[BUFF_SIZE - i - 2] = padd;
if (flags & F_MINUS)
return write(1, &buffer[0], 1) + write(1, &buffer[BUFF_SIZE - i - 1], width - 1);
else
return write(1, &buffer[BUFF_SIZE - i - 1], width - 1) + write(1, &buffer[0], 1);
}
return write(1, &buffer[0], 1);
}
int handle_print(const char *format, int *i, va_list, char buffer[], int flags, int width, int precision, int size)
{
int unknow_len = 0, printed_chars = -1;
fmt_t fmt_types[] = {
{'c', handle_write_char},
/* add other format specifiers and theri correspondig handling functions here */
{'\0', NULL}
};
for (int j = 0; fmt_types[j].fmt != '\0'; j++)
{
if (format[*i] == fmt_types[j].fmt)
{
if (fmt_types[j].func != NULL)
printed_chars = fmt_types[j].func(va_arg(list, int), buffer, flags, width, precision, size);
unknow_len = 1;
break;
}
}
if (!unknow_len)
{
buffer[0] = '%';
buffer[1] = format[*i];
buffer[2] = '\0';
printed_chars = handle_write_char('%', buffer, flags, width, precision, size);
printed_chars += handle_write_char(format[*i], buffer, flags, width, precision,size);
}
return printed_chars;
}
