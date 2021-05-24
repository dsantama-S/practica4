#include "isocheck.h"
#include <stdio.h>
#include <stdlib.h>

unsigned short calculate_iso_checksum(const unsigned char data_octets[],
const unsigned int number_of_octets)
{
    int i;
    unsigned short Co=0, C1=0, iso_checksum=0;
    unsigned char CK1, CK2;
    for (i=0; i<number_of_octets; i++)
    {
        Co = (Co+ data_octets[i]) % 255;
        C1 = (C1+Co) % 255;
    }

    CK1 = ~(Co + C1) % 255;
    CK2 = C1 % 255;

    if (CK1 == 0)

    {
        CK1 = 255;
    }
    if (CK2 == 0)
    {
        CK2 = 255;
    }
    iso_checksum = (CK1 << 8) | (CK2);
    return iso_checksum;
}
