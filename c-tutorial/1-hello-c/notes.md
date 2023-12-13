# Lesson One Notes 

- \# include <stdio.h> is a header file library for the std.io module which inclueds output functions such as printf(). 
- C Statements end ith a colon 
- C uses the standard `main()` function syntax (`int main()`) to represent that it returns an `int`
- `printf` does not insert a new line. To insert a new line you can use the `\n` flag in the text.  
- Single line comments are written with `\\` like in other languages
- Multi Line comments are written with `/* */`
- Variables are written as usual `type varName = value` 
- To print out a varibale you can use the format string with `printf("My var => <var type for example %d>", myVar")`
- constants are declared as follows: `const <type> <varName> = <value>`
- It is good practice to write constants in uppercase in the C Programing Language. 
- Variables are mutable by default

## Print variable types 

- `%d` = Integer 
- `%f` = Float 
- `%c` = Char

## Primitive Data Types 

- int 
    - This Represents a whole number 
    - Size: 2 or 4 bytes 
- float 
    - Sotres fractional numbers containing one or more decimals 
    - Sufficient for storing 6-7 decimal digits 
    - Size: 4 Bytes 
- double
    - Stores Fractional numbers sufficient for 15 decimal digits 
    - 8 bytes
- char 
    - stores a single character
    - 1 byte

## Type Conversion 

- Types can be explicitly or implicitly converted 
- It is best to avoid implicit converisioon i.e `float myNum = 9.99; printf("%d", myNum);`
- Explicit conversion would look like this: `int myNum = (int) 9.99; // This will convert to 9`

## Conditionals 

- Conditionals work as in other languages with `if`, `else`, `else if`, ternary `true ? printf("is true") : printf("is false")` and switch statements
- They are all written as you would expect

## Loops 

- `for`, `while` and `do while` loops are all available and are written as in other languages 
- within for loops you do have to declare the `i` variable before the loop which differs from other languages such as Java/JavaScript

## Arrays 

- Arrays are fixed length and contain a single data type. 
- However, there is no length property as in other languages thus it must be calculated in an ass backward way. 
    - This can be done through pointer arithmetic or using a `sizeof` hack 
        - pointers: int arr_len = *(&arr + 1) - arr; 
        - sizeof: long arr_len = (long) sizeof(arr) / sizeof(arr[0]); 
