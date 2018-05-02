#include "flash.h"

int main()
{
    unsigned int add = 0x1234;
    unsigned char buffer[8] = {0};
    W25Q16_Read(add,buffer,1);
    printf("%s\n",buffer);
    buffer[0] = 'a';
    buffer[7] = 'b';
    W25Q16_Write(add,buffer,1);
    buffer[0] = '\0';
    buffer[7] = '\0';
    W25Q16_Read(add,buffer,1);
    printf("%s\n",buffer);
}