#include <stdio.h>
#include "NumberConverter.h"

/* Doubles will only convert the first digit after the decimal point. */
/* Converter will only handle numbers between 153 and -50. */

char nbrcnvt_convert_digit(int digit ) {
	if (digit >= 0 && digit <= 9) {
		return 48 + digit; /* ASCII 0 character is code 48. */
	}
	else { /* Invalid. */
        return 48 + digit;
		//return 69; /* ASCII code for E. Represents Error. */
	}
}

void nbrcnvt_convert_integer(int number, char* output) {
	int tens;
	int units;
	int count = 0;
	int has_hundred = 0;

	if (number < 0) {
		output[count] = '-';
		count++;
		number = number * -1;
	}

	if (number >= 100 && number <= 153) {
		output[count] = '1';
		count++;
		number = number - 100;
		has_hundred = 1;
	}

	units = number % 10;
	tens = (number - units) / 10;

	if (has_hundred == 1 || tens != 0) {
		output[count] = nbrcnvt_convert_digit(tens);
		count++;
	}

	output[count] = nbrcnvt_convert_digit(units);
	count++;

	output[count] = '\0';



}

void nbrcnvt_convert_double(double number, char* output) {
	int decimal;
	int tens;
	int units;
	int count = 0;
	int has_hundred = 0;

	if (number < 0) {
		output[count] = '-';
		count++;
		number = number * -1;
	}

	if (number >= 100 && number <= 153) {
		output[count] = '1';
		count++;
		number = number - 100;
		has_hundred = 1;
	}

	units = (int)number % 10;
	tens = (number - units) / 10;

	if (has_hundred == 1 || tens != 0) {
		output[count] = nbrcnvt_convert_digit(tens);
		count++;
	}

	output[count] = nbrcnvt_convert_digit(units);
	count++;

	output[count] = '.';
	count++;

	decimal = (int)(number * 10) % 10;
	output[count] = nbrcnvt_convert_digit(decimal);
	count++;

	output[count] = '\0';
}

int nbrcnvt_check_length_int(int number) {
	if (number < 0 && number > -10) {
		return 3; /* -X\0 */
	}
	else if (number < -9 && number >= -50) {
		return 4; /* -XX\0 */
	}
	else if (number >= 0 && number <= 9) {
		return 2; /* X\0 */
	}
	else if (number >= 10 && number <= 99) {
		return 3;
	}
	else if (number >= 100 && number <= 153) {
		return 4;
	}
	else { /* Default */
		return -1;
	}
}

int nbrcnvt_check_length_double(double number) {
	if (number < 0 && number > -10) {
		return 5; /* -X.X\0 */
	}
	else if (number < -9) {
		return 6; /* -XX.X\0 */
	}
	else if (number >= 0 && number <= 9) {
		return 4; /* X.X\0 */
	}
	else if (number >= 10 && number <= 99) {
		return 5;
	}
	else if (number >= 100 && number <= 153) {
		return 6;
	}
	else { /* Default */
		return -1;
	}
}
