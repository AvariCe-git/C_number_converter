/*  This "program" converts hexadecimal, octal, or binary numbers to decimals.
    It also converts decimals to either hexadecimal, octal or binary mumbers.
    To use it, here are the arguments passed from the command line:
    d 'prefix''number': converts a number to decimal from binary, octal or hexadecimal.
        Each number has to have the appropriate prefix: 0x for hex, 0o for octal
        and 0b for binary, followed immediately by the number without a space.
        eg: whatever -d 0xabc, to convert hex abc to decimal.
    b decimal_number: converts a decimal number to binary.
        eg whatever b 159
    o decimal_number: converts a decimal to octal.
    h decimal_number: converts a decimal to hexadecimal.
    Current version is 1.4
    2020 Antonios Giannakopoulos, https://github.com/AvariCe-git */

#include <stdio.h>                                                                  // Standard input output
#include <math.h>                                                                   // Needed for raising to powers
#include <stdlib.h>                                                                 // Needed for atoi
#include <string.h>                                                                 // Needed for strcmp
#include <stdbool.h>                                                                // Needed for boolean variables
#include <string.h>                                                                 // Needed for strlen

void check(char base[],char number[]);                                              // Checks the arguments and calls the appropriate functions
void convert_to(int base, int number);                                              // Displays the convertion of a decimal to hexadecimal, octal or binary
void print_hex(int number);                                                         // Helps output the conversion result
void convert_from(char arg1[]);                                                     // Converts a hexadecimal, octal or binary number to decimal
void print_help();                                                                  // Prints the help


int main(int argc,char* argv[]){
        
    check(argv[1],argv[2]);                                                         // Starts the whole shebang
    return 0;

}

void check(char base[], char number[]){                                             // Checks the arguments and calls the appropriate functions

    int i = 0;

    i = atoi(number);
    if(strcmp(base, "b") == 0)
        convert_to(2,i);
    else if(strcmp(base, "o") == 0)
        convert_to(8,i);
    else if (strcmp(base, "h") == 0)
        convert_to(16,i);
    else if (strcmp(base, "d") == 0)
        convert_from(number);
    else 
        print_help();

}

void convert_to(int base, int number){                                              // Displays the convertion of a decimal to hexadecimal, octal or binary
                                                                                    // It accepts two arguments: the base for the conversion (integer) and the decimal 
    bool trip = 0;                                                                  // number to convert to(integer)
    char specifics[3][15] = {"binary","octal","hexadecimal"};                       // Helps with displaying the conversion message
    char prefix[3][5] = {"0b","0o","0x"};                                           // Same
    int i = 0;                                                                      // It's the counter
    int bin[40];                                                                    // The array where the converted number lives
    for(i = 0; i < 40; i++)                                                         // Initialise the array
        bin[i] = 0; 
    printf("%d in %s is:  %s ", number, specifics[base/8],prefix[base/8]);          // Prints the message according to the base the user wants
    for(i=0; i<40; i++){                                                            // Here the conversion happens. Every repetion, the array gets the remainder of the                  
        bin[i] = number%base;                                                       // given number divided by the given base, and then it gets divided by the given base until 
        number = number/base;                                                       // it reaches the end of the array. I could have it break out of the loop the moment 
    }                                                                               // number/base is zero, but I'm lazy and it suits my needs as is.
    for (i=39; i>=0; i--){                                                          // Here it prints the conversion. It goes from the end of the array to the start.
        if(trip == 0){                                                              // First it checks if the boolean is false. If it is, it searches for a non-zero number.
            if(bin[i] != 0){                                                        //  When it's found, the boolean changes state, calls the print_hex,which prints the aforementioned number
                trip = 1;                                                           //  and stores the array's location, for the purpose of showing the biggest power of given number.
                print_hex(bin[i]);                                                  //  If the boolean is tripped, it means a non zero number has been found and after that it prints every character
                number = i;                                                         // in the array.  It's done so it only disregards the non important zeroes in the array.
            }
        }
        else
            print_hex(bin[i]);
    }
    printf("\n");
    printf("Highest power of %d is:  %d", base, number);

}

void print_hex(int number){  // Helps output the conversion result. 
                                                                                    // I used a separate function for that because the code above 
    char hex_extra[6][2] = {"A","B","C","D","E","F"};                               // was getting a little heavy for my tastes. It accepts a single integer as argument,
    if(number > 9)                                                                  // and if it's bigger than nine it means that it belongs to a hex number and prints
        printf("%s", hex_extra[number-10]);                                         // the appropriate letter. Otherwise it prints the given number.
    else
        printf("%d", number);

}

void convert_from(char arg1[]){                                                     // Converts a hexadecimal, octal or binary number to decimal
                                                                                    // It accepts a character array. It scans the first two characters to determine                                          
    int i = 0, result = 0,temp = 0,length = 0;                                      // which base it converts from, and converts accordingly. The formula for every
    length = strlen(arg1);                                                          // base is this for every loop: 
    if(strncmp(arg1,"0b",2) == 0){                                                  // conversion_number = conversion_number + array[i]*(given_base ^ (array[i]-i-1)
        for(i = 2; i < length; i++){                                                // It basically raises the base to the appropriate number in every iteration, 
            temp = arg1[i] - '0';                                                   // multiplies it to the number it finds in the array and adds it to the result.
            result = result + temp*pow(2,length-i-1);                               // It reads the number from the array by removing the ascii offset 
        }                                                                           // the (-'0' part) and casting it to integer.
        printf("%d", result);                                                       // For hexadecimal specifically, if the number it reads after removing the offset
    }                                                                               // is in the range of 17 -> 22 or 49 -> 54 means it's either A->F or a->f respectively.
    else if(strncmp(arg1,"0o",2) == 0){                                             // In that case, it just sets the read number to its proper value
        for(i = 2; i < length; i++){
            temp = arg1[i];
            result = result + temp*pow(8,length-i-1);
        }
        printf("%d", result);
    }
    else if(strncmp(arg1,"0x",2) == 0){
        for(i = 2; i < length; i++){
            temp = arg1[i] - '0';
            if(temp == 17 || temp == 49)
                temp = 10;
            if(temp == 18 || temp == 50)
                temp = 11;
            if(temp == 19 || temp == 51)
                temp = 12;
            if(temp == 20 || temp == 52)                                           
                temp = 13;
            if(temp == 21 || temp == 53)
                temp = 14;
            if(temp == 22 || temp == 54)
                temp = 15;
            result = result + temp*pow(16,length-i-1);
        }
        printf("%d", result);
    }

}

void  print_help(){                                                                 // Shows the help

    printf("This ""program"" converts hexadecimal, octal, or binary numbers to decimals.\n");
    printf(" It also converts decimals to either hexadecimal, octal or binary mumbers.\n");
    printf("To use it, here are the arguments passed from the command line:\n");
    printf("d 'prefix''number': converts a number to decimal from binary, octal or hexadecimal.\n");
    printf("    Each number has to have the appropriate prefix: 0x for hex, 0o for octal\n");
    printf("    and 0b for binary, followed immediately by the number without a space.\n");
    printf("    eg: whatever -d 0xabc, to convert hex abc to decimal.\n");
    printf("b decimal_number: converts a decimal number to binary.\n");
    printf("    eg whatever b 159\n");
    printf("o decimal_number: converts a decimal to octal.\n");
    printf("h decimal_number: converts a decimal to hexadecimal.\n");
    printf("Current version is 1.4\n");
    printf("2020 Antonios Giannakopoulos, https://github.com/AvariCe-git\n");

}