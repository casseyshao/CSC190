// Lab 6

#include <stdlib.h>
#include <stdio.h>

unsigned char FSR(unsigned char x);
unsigned char prng(unsigned char x, unsigned char pattern);
int crypt(char *data, unsigned int size, unsigned char password);

/* feedback shift register */
unsigned char FSR(unsigned char x) {
   unsigned char oldbit0 = x & 0x1; /* extract bit 0 */
   unsigned char r = x >> 1;        /* shift right   */
   unsigned char newbit7 = oldbit0 << 7; /* move bit0 to the bit7 pos */
   r = r | newbit7; /* rotate the old value of bit 0 into the bit 7 pos */
   return r;
}

/* XORs the shifted and rotated value of x with "pattern" */
unsigned char prng(unsigned char x, unsigned char pattern) {
   return FSR(x)^pattern;
}

/* "data" is a caller-allocated char array of size "size+1"
 * (+1 because we need to include an '\0' char)
 * "password" will be the starting value for the prng and cannot be zero
 * return 0 for success and -1 for failure
 * "data" holds the input string, and will also be used to store the output */
int crypt(char *data, unsigned int size, unsigned char password){
   unsigned char prngVal = password;
   if (data == NULL) {
      return -1;
   }
   for (int i=0;i<size;i++) {
      prngVal = prng(prngVal,0xb8);
      data[i] = data[i]^prngVal; 
   }
   return 0;
}

/* test code is below */
int main(void) {

   // testing feedback shift register
   // test FSR()
   printf("TESTING FSR():\n");
   unsigned char x = 147;
   unsigned char rVal = FSR(x);
   printf("%d\n",rVal); // should be 201
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 228
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 114
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 57
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 156
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 78
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 39
   rVal = FSR(rVal);
   printf("%d\n",rVal); // should be 147 (repeats with a period of 8)

   // test prng()
   // test with pattern=0xb8
   // period is also 8
   printf("TESTING prng():\n");
   rVal = prng(x,0xb8);
   printf("%d\n",rVal); // should be 113
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);
   rVal = prng(rVal,0xb8);
   printf("%d\n",rVal);

   // test crypt()
   printf("TESTING crypt():\n");
   char data[] = "Encryption";
   crypt(data,10,0x30);
   printf("Encrypted: %s\n",data);
   crypt(data,10,0x30);
   printf("Unencrypted: %s\n",data);

   return 0;
}
