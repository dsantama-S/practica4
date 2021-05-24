#ifndef AUX_FUNCTIONS_H_INCLUDED
#define AUX_FUNCTIONS_H_INCLUDED

unsigned short merge_2_hex(u8 hex1, u8 hex2);

unsigned int merge_4_hex(u8 hex1,u8 hex2,u8 hex3,u8 hex4);

void reject_tc(u8 tc_array[], int size, bool rejected);

bool search_V2_TC(u8 tc_array[]);

void split_short(u8* char1, u8* char2, u16 split);

void give_expected_value(u8 array[], u8 starting_val, u32 number_bytes);

void correct_values_1(int number_errors1, int number_errors2, int number_errors3);

void correct_values_2(int number_of_load_errors_1, int number_of_load_errors_2, int number_of_check_errors);

void gen_TCs_6_2(u8 tc_array[], u16 number_bytes, u8 initial_value, u8 strt_ad1, u8 strt_ad2, u8 strt_ad3, u8 strt_ad4, bool correct_checksum);

void gen_TCs_6_9(u8 tc_array[], u16 number_bytes, u8 strt_ad1, u8 strt_ad2, u8 strt_ad3, u8 strt_ad4, bool correct_checksum);


#endif // AUX_FUNCTIONS_H_INCLUDED
