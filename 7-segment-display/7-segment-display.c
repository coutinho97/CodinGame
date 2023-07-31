
//https://www.codingame.com/ide/puzzle/7-segment-display

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define BLANK_CHAR      ' '

#define CHECK_BIT(num, bit_position)            (((num) >> (bit_position)) & 1)

typedef enum segments_indexes {
    SEGMENT_A       = 0,
    SEGMENT_B       = 1,
    SEGMENT_C       = 2,
    SEGMENT_D       = 3,
    SEGMENT_E       = 4,
    SEGMENT_F       = 5,
    SEGMENT_G       = 6,
    SEGMENT_DOT     = 7,
    SEGMENT_TOTAL   = 8
} SEGMENT;

const uint8_t SEGMENTS[10] = {
    /* dot,g,f,e,d,c,b,a */
    0b00111111, /* 0 */
    0b00000110, /* 1 */
    0b01011011, /* 2 */
    0b01001111, /* 3 */
    0b01100110, /* 4 */
    0b01101101, /* 5 */
    0b01111101, /* 6 */
    0b00000111, /* 7 */
    0b01111111, /* 8 */
    0b01101111, /* 9 */
};

void PrintNumber(long number, int size, char symbol) 
{
    int total_row = 0;
    int total_col = 0;
    int total_digit = 0;
    int col_per_digit = 0;
    int digits[15] = {0};
    int digit = 0;

    // Convert the number to an array of digits
    if (number == 0) 
    {
        digits[total_digit++] = 0;
    } 
    else 
    {
        while (number > 0) 
        {
            digits[total_digit++] = number % 10;
            number /= 10;
        }
    }

    // Reverse the digits array to get them in the correct order
    int temp;
    for (int i = 0; i < total_digit / 2; i++)
    {
        temp = digits[i];
        digits[i] = digits[total_digit - i - 1];
        digits[total_digit - i - 1] = temp;
    }

    total_row = 3 + (2 * size);
    col_per_digit = 2 + size + 1;               // + 1 espaço entrw digitos
    total_col = col_per_digit * total_digit;

    char segments[total_row][total_col];

    // Initialize segments with blank spaces
    for (int row_idx = 0; row_idx < total_row; row_idx++) 
    {
        for (int col_idx = 0; col_idx < total_col; col_idx++) 
        {
            segments[row_idx][col_idx] = BLANK_CHAR;
        }
    }

    // Construct the segments for each digit
    for (int digit_idx = 0; digit_idx < total_digit; digit_idx++) 
    {
        digit = digits[digit_idx];
        
        for (int seg = SEGMENT_A; seg <= SEGMENT_G; seg++) 
        {
            if (CHECK_BIT(SEGMENTS[digit], seg)) 
            {
                // Draw the segment for the current digit
                switch (seg) 
                {
                    case SEGMENT_A:
                        
                        for (int i = 1; i <= size; i++) 
                        {
                            segments[0][col_per_digit * digit_idx + i] = symbol;
                        }
                    break;
                    
                    case SEGMENT_B:
                        
                        for (int i = 1; i <= size; i++) 
                        {
                            segments[i][col_per_digit * digit_idx + size + 1] = symbol;
                        }
                    break;
                    
                    case SEGMENT_C:
                        
                        for (int i = 0; i < size; i++) 
                        {
                            segments[size + 2 + i][col_per_digit * digit_idx + size + 1] = symbol;
                        }
                    break;
                    
                    case SEGMENT_D:
                        
                        for (int i = 1; i <= size; i++) 
                        {
                            segments[size + size + 2][col_per_digit * digit_idx + i] = symbol;
                        }
                    break;
                    
                    case SEGMENT_E:
                        
                        for (int i = 0; i < size; i++) 
                        {
                            segments[size + 2 + i][col_per_digit * digit_idx] = symbol;
                        }
                    break;
                    
                    case SEGMENT_F:
                            
                        for (int i = 1; i <= size; i++) 
                        {
                            segments[i][col_per_digit * digit_idx] = symbol;
                        }
                    break;
                    
                    case SEGMENT_G:
                        
                        for (int i = 1; i <= size; i++) 
                        {
                            segments[size + 1][col_per_digit * digit_idx + i] = symbol;
                        }
                    break;
                }
            }
        }
    }

    // Print the segments
    for (int row_idx = 0; row_idx < total_row; row_idx++)
    {
        // Descobrir o index do ultimo symbol para só iterar até aí
        int last_col_idx = 0;
        
        for (int col_idx = 0; col_idx < total_col; col_idx++)
        {
            if (segments[row_idx][col_idx] == symbol)
            {
                last_col_idx = col_idx + 1;
            }
        }
        
        for (int col_idx = 0; col_idx < last_col_idx; col_idx++)
        {
            putchar(segments[row_idx][col_idx]);
        }
        
        putchar('\n');
    }
}

int main()
{
    long number; 
    int size;
    char simbol[2];

    scanf("%ld", &number); fgetc(stdin);
    scanf("%[^\n]", simbol);
    scanf("%d", &size);

    PrintNumber(number, size, simbol[0]);

    return 0;
}
