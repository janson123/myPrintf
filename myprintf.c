/*
 *Filename: myprintf.c *
 *Created by: [Jared Anson] *
 *Last Modified by: [Jared Anson] * 
 */

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

//function prototypes
void printint(int i);
void printstring(char* c);
void printhex(int h);
void myprintf(const char *fmt, ...);


// takes an int and prints it to the console.
void printint(int i){
  char googol[100];
  int index = 0;
  int printPosition = 0;
  // converts negative to positive, and puts a '-' to the console
  if(i < 0){
    i = -i;
    putchar('-');
  }
  while(i > 0){
    googol[index] = 48 + (i % 10); // 0's ascii value is 48, mod 10 gives you the 1s place value. 
    i = i/10; // peals off the 1s place
    printPosition++;
    index++;
  }
  //printPosition always ends up one more than you need it to be
  // take the case of the int 11, printPosition would be 2 but 
  // there is nothing stored there. 1 and 1 are stored at index 1 and 0 respectively.
  // so you need to lower it one.
  printPosition--;
  while(printPosition >= 0){
    putchar(googol[printPosition]);
    printPosition--;
  }
}


// Print string takes a char pointer, and prints out the string associated
// with it to the console.
void printstring(char* c){   
  int index = 0;
  while(c[index] != '\0'){
    putchar(c[index]); // puts the value stored to the console.
    index++;
  }
}

//takes an integer and prints out the hexadecimal form of that integer
void printhex(int h){
  int count = 0;
  int anotherIndex = 0;
  int value;
  char result[100]; // large array for large ints
  for(h; h > 0; count++){
    value = h % 16; //hex is base 16
    if (value < 10) { // anything less than 10 is an int in hexadecimal, 10-15 are letters
      value += 48; //ints
    }else {
      value += 55; //letters    
    }
    result[count] = value;
    h = h/16; // peels away for each iteration
  }
  //the count will always be one more than the actual index we want due to indexing starting at 0.
  // if count was 5, we need to start at the index 4 and go backwards
  // since there is nothing stored at index 5.
  anotherIndex = count - 1;
  while(anotherIndex >= 0) {
    putchar(result[anotherIndex]); // puts that value to the console.
    anotherIndex--; 
  }
}

// behaves similarly to printf. Can print char, strings, int, and hecadecimal.
void myprintf(const char *fmt, ...) {
  const char *p;
  va_list argp;
  int i;
  char *s;

  va_start(argp, fmt);

  for (p = fmt; *p != '\0'; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }
    switch (*++p) {
    case 'c':
      i = va_arg(argp, int);
      putchar(i);
      break;

    case 'd':
      i = va_arg(argp, int);
      printint(i);
      break;

    case 's':
      s = va_arg(argp, char *);
      printstring(s);
      break;

    case 'x':
      i = va_arg(argp, int);
      printhex(i);
      break;

    case '%':
      putchar('%');
      break;
    }
  }
  va_end(argp);
}
