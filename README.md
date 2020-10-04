# C_number_converter
Converts decimals to hexadecimal, octal and binary and vice verca


This "program" converts hexadecimal, octal, or binary numbers to decimals.
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
