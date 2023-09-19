#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// Function to multiply two infinite numbers represented as strings
void multiply_infinite_numbers(char *num1, char *num2) {
	
    // Calculate the lengths of the input numbers
    int len1 = strlen(num1);
    int len2 = strlen(num2);

    // Determine the sign of the result
    bool negative = false;
    if (num1[0] == '-') {
        negative = !negative;
        num1++; // Skip the negative sign
        len1--;
    }
    if (num2[0] == '-') {
        negative = !negative;
        num2++; // Skip the negative sign
        len2--;
    }

    // Allocate memory for the result, with space for additional digits if needed
    int resultSize = len1 + len2 + 1;
    char *result = (char *)malloc((resultSize + 1) * sizeof(char));
    if (result == NULL) {
        write(STDOUT_FILENO, "error\n", 6);
        return;
    }

    // Initialize the result to zero
    for (int i = 0; i < resultSize; i++) {
        result[i] = '0';
    }
    result[resultSize] = '\0';

    // Perform the multiplication digit by digit
    for (int i = len1 - 1; i >= 0; i--) {
        for (int j = len2 - 1; j >= 0; j--) {
            int digit1 = num1[i] - '0';
            int digit2 = num2[j] - '0';

            // Perform the multiplication and add to the corresponding digit in the result
            int product = digit1 * digit2;
            int sum = result[i + j + 1] - '0' + product;
            result[i + j + 1] = (sum % 10) + '0';
            result[i + j] += sum / 10;
        }
    }

    // Find the position of the first non-zero digit after accounting for leading zeros
    int start = 0;
    while (start < resultSize && result[start] == '0') {
        start++;
    }

    // Print the result with the appropriate sign
    if (negative) {
        write(STDOUT_FILENO, "-", 1);
    }
    write(STDOUT_FILENO, result + start, resultSize - start - 1);
    write(STDOUT_FILENO, "\n", 1);

    // Free the allocated memory
    free(result);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        write(STDOUT_FILENO, "error\n", 6);
        return 0;
    }

    multiply_infinite_numbers(argv[1], argv[2]);

    return 0;
}
