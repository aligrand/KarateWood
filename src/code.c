#include "code.h"

#include <stdlib.h>

Byte *modEncode(Byte *input, int size, Byte change)
{
    Byte *output = malloc(size * sizeof(Byte));

    for (int i = 0; i < size; i++)
    {
        output[i] = (input[i] + change) % (UCHAR_MAX + 1); 
    }
    
    return output;
}

Byte *modDecode(Byte *input, int size, Byte change)
{
    Byte *output = malloc(size * sizeof(Byte));

    for (int i = 0; i < size; i++)
    {
        output[i] = (input[i] - change) % (UCHAR_MAX + 1); 
    }
    
    return output;
}