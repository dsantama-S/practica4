#ifndef ISOCHECK_H_INCLUDED
#define ISOCHECK_H_INCLUDED

unsigned short calculate_iso_checksum(const unsigned char data_octets[],
                                        const unsigned int number_of_octets);

#endif // ISOCHECK_H_INCLUDED
