#ifndef OL71_WS6_H
#define OL71_WS6_H

#include <stddef.h> /* size_t */

unsigned long Pow2(unsigned int x, int y);
int IsPowOfTwoLoop(unsigned int n);
int IsPowOfTwo(unsigned int n);
unsigned int AddOne(unsigned int num);
void PrintThreeBits(const unsigned int arr[], size_t arr_length);
unsigned char ByteMirrorLoop(unsigned char uchar);
unsigned char ByteMirror(unsigned char uchar);
int AreBothBitsOn(unsigned char uchar);
int IsOneBitOn(unsigned char uchar);
unsigned char SwapBits(unsigned char uchar);
unsigned int ClosestMultiplyOf16(unsigned int num);
void SwapVars(unsigned int *a, unsigned int *b);
unsigned int CountSetBitsLoop(unsigned int num);
unsigned int CountSetBits(unsigned int num);
void PrintFloat(float fnum);

#endif /* OL71_WS6_H */
