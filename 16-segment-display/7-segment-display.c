
// include
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// define
#define BLANK_CHAR      				' '

// macro
#define CHECK_BIT(num, bit_position)	(((num) >> (bit_position)) & 1)

// enum
typedef enum segments_indexes {
    SEGMENT_A       = 0,
    SEGMENT_B       = 1,
    SEGMENT_C       = 2,
    SEGMENT_D       = 3,
    SEGMENT_E       = 4,
    SEGMENT_F       = 5,
    SEGMENT_G       = 6,
	SEGMENT_H       = 7,
    SEGMENT_K       = 8,
    SEGMENT_M       = 9,
    SEGMENT_N       = 10,
    SEGMENT_P       = 11,
    SEGMENT_R       = 12,
    SEGMENT_S       = 13,
	SEGMENT_T       = 14,
    SEGMENT_U       = 15,
    SEGMENT_DP      = 16,
    SEGMENT_TOTAL
} SEGMENT_INDEX;

// const
const uint32_t SEGMENT_ASCII[96] = {
	0b00000000000000000, /* (space) */
	0b10000000000001100, /* ! */
	0b00000001000000100, /* " */
	0b01010101000111100, /* # */
	0b01010101010111011, /* $ */
	0b01110111010011001, /* % */
	0b01001001101110001, /* & */
	0b00000001000000000, /* ' */
	0b00001010000000000, /* ( */
	0b00100000100000000, /* ) */
	0b01111111100000000, /* * */
	0b01010101000000000, /* + */
	0b00100000000000000, /* , */
	0b01000100000000000, /* - */
	0b10000000000000000, /* . */
	0b00100010000000000, /* / */
	0b00100010011111111, /* 0 */
	0b00000010000001100, /* 1 */
	0b01000100001110111, /* 2 */
	0b00000100000111111, /* 3 */
	0b01000100010001100, /* 4 */
	0b01001000010110011, /* 5 */
	0b01000100011111011, /* 6 */
	0b00000000000001111, /* 7 */
	0b01000100011111111, /* 8 */
	0b01000100010111111, /* 9 */
	0b00010001000000000, /* : */
	0b00100001000000000, /* ; */
	0b01001010000000000, /* < */
	0b01000100000110000, /* = */
	0b00100100100000000, /* > */
	0b10010100000000111, /* ? */
	0b00000101011110111, /* @ */
	0b01000100011001111, /* A */
	0b00010101000111111, /* B */
	0b00000000011110011, /* C */
	0b00010001000111111, /* D */
	0b01000000011110011, /* E */
	0b01000000011000011, /* F */
	0b00000100011111011, /* G */
	0b01000100011001100, /* H */
	0b00010001000110011, /* I */
	0b00000000001111100, /* J */
	0b01001010011000000, /* K */
	0b00000000011110000, /* L */
	0b00000010111001100, /* M */
	0b00001000111001100, /* N */
	0b00000000011111111, /* O */
	0b01000100011000111, /* P */
	0b00001000011111111, /* Q */
	0b01001100011000111, /* R */
	0b01000100010111011, /* S */
	0b00010001000000011, /* T */
	0b00000000011111100, /* U */
	0b00100010011000000, /* V */
	0b00101000011001100, /* W */
	0b00101010100000000, /* X */
	0b01000100010111100, /* Y */
	0b00100010000110011, /* Z */
	0b00010001000010010, /* [ */
	0b00001000100000000, /* \ */
	0b00010001000100001, /* ] */
	0b00101000000000000, /* ^ */
	0b00000000000110000, /* _ */
	0b00000000100000000, /* ` */
	0b01010000001110000, /* a */
	0b01010000011100000, /* b */
	0b01000000001100000, /* c */
	0b00010100000011100, /* d */
	0b01100000001100000, /* e */
	0b01010101000000010, /* f */
	0b01010001010100001, /* g */
	0b01010000011000000, /* h */
	0b00010000000000000, /* i */
	0b00010001001100000, /* j */
	0b00011011000000000, /* k */
	0b00000000011000000, /* l */
	0b01010100001001000, /* m */
	0b01010000001000000, /* n */
	0b01010000001100000, /* o */
	0b01000001011000001, /* p */
	0b01010001010000001, /* q */
	0b01000000001000000, /* r */
	0b01010000010100001, /* s */
	0b01000000011100000, /* t */
	0b00010000001100000, /* u */
	0b00100000001000000, /* v */
	0b00101000001001000, /* w */
	0b00101010100000000, /* x */
	0b00000101000011100, /* y */
	0b01100000000100000, /* z */
	0b01010001000010010, /* { */
	0b00010001000000000, /* | */
	0b00010101000100001, /* } */
	0b01100110000000000, /* ~ */
	0b00000000000000000, /* (del) */
};

// function prototype
void PrintString(char *string, uint8_t display_size, char display_symbol);
void PrintBuffer(char **buffer, int row_size, int col_size, char display_symbol);
void DrawSegmentA(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentB(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentC(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentD(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentE(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentF(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentG(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentH(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentK(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentM(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentN(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentP(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentR(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentS(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentT(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentU(char **buffer, int offset, int display_size, char display_symbol);
void DrawSegmentDP(char **buffer, int offset, int display_size, char display_symbol);

// Function pointer
void (*DRAW_SEGMENTS[SEGMENT_TOTAL])(char**, int, int, char) = {
    DrawSegmentA,
    DrawSegmentB,
    DrawSegmentC,
    DrawSegmentD,
    DrawSegmentE,
    DrawSegmentF,
    DrawSegmentG,
    DrawSegmentH,
    DrawSegmentK,
    DrawSegmentM,
    DrawSegmentN,
    DrawSegmentP,
    DrawSegmentR,
    DrawSegmentS,
    DrawSegmentT,
    DrawSegmentU,
    DrawSegmentDP
};

// main
int main()
{
char *string 		= "V1.1.2"; 
    int display_size 	= 5;
    char display_symbol = '#';
    
    PrintString(string, display_size, display_symbol);
    
    return 0;
}

// function
void PrintString(char *string, uint8_t display_size, char display_symbol) 
{
    int total_digit = 0;
    int total_row   = 0;
    int digit_col   = 0;
    int total_col   = 0;
    
    total_digit 	= strlen(string);
    total_row       = display_size * 2 + 3;
    digit_col       = display_size * 2 + 3 + 2;
    total_col       = digit_col * total_digit;
    
    printf("total_digit %d, total_row %d, col_per_digit %d, total_col %d\n\n", total_digit, total_row, digit_col, total_col);
    
    char **display;
    // Initialize segments with blank spaces
    display = (char**)malloc(total_row * sizeof(char*));
    for (int row_idx = 0; row_idx < total_row; row_idx++) 
    {
        display[row_idx] = (char*)malloc(total_col * sizeof(char));
        for (int col_idx = 0; col_idx < total_col; col_idx++) 
        {
            display[row_idx][col_idx] = BLANK_CHAR;
        }
    }
    
    // Construct the segments for each digit
    for (int digit_idx = 0; digit_idx < total_digit; digit_idx++) 
    {
        char digit = string[digit_idx];
        
        for (int seg = 0; seg < SEGMENT_TOTAL; seg++) 
        {
            if (CHECK_BIT(SEGMENT_ASCII[digit - 32], seg)) 
            {
                int offset = digit_col * digit_idx;
                DRAW_SEGMENTS[seg](display, offset, display_size, display_symbol);
            }
        }
    }

    // Print the segments
    PrintBuffer(display, total_row, total_col, display_symbol);
}
void PrintBuffer(char **buffer, int row_size, int col_size, char display_symbol)
{
    for (int row_idx = 0; row_idx < row_size; row_idx++)
    {
        // Descobrir o index do ultimo display_symbol para só iterar até aí
        int last_col_idx = 0;
        for (int col_idx = 0; col_idx < col_size; col_idx++)
        {
            if (buffer[row_idx][col_idx] == display_symbol)
            {
                last_col_idx = col_idx + 1;
            }
        }
        
        //printf("row: %d\t", row_idx);
        for (int col_idx = 0; col_idx < last_col_idx; col_idx++)
        {
            putchar(buffer[row_idx][col_idx]);
        }
        putchar('\n');
    }
}
void DrawSegmentA(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[0][offset + i] = display_symbol;
    }
}
void DrawSegmentB(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[0][offset + display_size + 1 + i] = display_symbol;
    }
}
void DrawSegmentC(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i][offset + display_size * 2 + 2] = display_symbol;
    }
}
void DrawSegmentD(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i + display_size + 1][offset + display_size * 2 + 2] = display_symbol;
    }
}
void DrawSegmentE(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size * 2 + 2][offset + display_size + 1 + i] = display_symbol;
    }
}
void DrawSegmentF(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size * 2 + 2][offset + i] = display_symbol;
    }
}
void DrawSegmentG(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i + display_size + 1][offset] = display_symbol;
    }
}
void DrawSegmentH(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i][offset] = display_symbol;
    }
}
void DrawSegmentK(char **buffer, int offset, int display_size, char display_symbol)
{
    // diagonal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i][offset + i] = display_symbol;
    }
}
void DrawSegmentM(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i][offset + display_size + 1] = display_symbol;
    }
}
void DrawSegmentN(char **buffer, int offset, int display_size, char display_symbol)
{
    // diagonal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i][offset -i + display_size * 2 + 2] = display_symbol;
    }
}
void DrawSegmentU(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size + 1][offset + i] = display_symbol;
    }
}
void DrawSegmentP(char **buffer, int offset, int display_size, char display_symbol)
{
    // horizontal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size + 1][offset + display_size + 1 + i] = display_symbol;
    }
}
void DrawSegmentT(char **buffer, int offset, int display_size, char display_symbol)
{
    // diagonal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size + i + 1][offset -i + display_size + 1] = display_symbol;
    }
}
void DrawSegmentS(char **buffer, int offset, int display_size, char display_symbol)
{
    // vertical
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[i + display_size + 1][offset + display_size + 1] = display_symbol;
    }
}
void DrawSegmentR(char **buffer, int offset, int display_size, char display_symbol)
{
    // diagonal
    for (int i = 1; i <= display_size; i++) 
    {
        buffer[display_size + 1 + i][offset + i + display_size + 1] = display_symbol;
    }
}
void DrawSegmentDP(char **buffer, int offset, int display_size, char display_symbol)
{
    buffer[display_size * 2 + 2][offset + display_size * 2 + 3] = display_symbol;
}

// end
