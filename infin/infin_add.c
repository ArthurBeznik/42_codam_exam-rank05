#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

// Function to add two infinite numbers represented as strings
void add_infinite_numbers(char *num1, char *num2) {

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

    // Find the maximum length among the two numbers
    int maxLen = (len1 > len2) ? len1 : len2;

    // Allocate memory for the result, with space for additional digits if needed
    int resultSize = maxLen + 2; // +2 to accommodate a possible carry
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

    // Perform the addition digit by digit
    int carry = 0;
    for (int i = 0; i < maxLen; i++) {
        int digit1 = (i < len1) ? (num1[len1 - 1 - i] - '0') : 0;
        int digit2 = (i < len2) ? (num2[len2 - 1 - i] - '0') : 0;

        // Perform the addition and add to the corresponding digit in the result
        int sum = digit1 + digit2 + carry;
        carry = sum / 10;
        result[resultSize - 1 - i] = (sum % 10) + '0';
    }

    // Handle any remaining carry
    result[0] = carry + '0';

    // Find the position of the first non-zero digit after accounting for leading zeros
    int start = 0;
    while (start < resultSize - 1 && result[start] == '0') {
        start++;
    }

    // Print the result with the appropriate sign
    if (negative) {
        write(STDOUT_FILENO, "-", 1);
    }
    write(STDOUT_FILENO, result + start, resultSize - start);
    write(STDOUT_FILENO, "\n", 1);

    // Free the allocated memory
    free(result);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        write(STDOUT_FILENO, "error\n", 6);
        return 0;
    }

    add_infinite_numbers(argv[1], argv[2]);

    return 0;
}
