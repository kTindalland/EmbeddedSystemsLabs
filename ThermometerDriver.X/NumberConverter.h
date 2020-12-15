#ifndef __NUMBERCONVERTER
#define __NUMBERCONVERTER

char nbrcnvt_convert_digit(int digit);
void nbrcnvt_convert_integer(int number, char* output);
void nbrcnvt_convert_double(double number, char* output);
int nbrcnvt_check_length_int(int number);
int nbrcnvt_check_length_double(double number);

#endif
