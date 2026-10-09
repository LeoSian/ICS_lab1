/* 
 * CS:APP Data Lab 
 * 
 * <Please put your name and userid here>
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
#include "bits.h"

// P1
/* 
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 1 左移 31 位 */
  return 1 << 31;
}

// P2
/* 
 * bitXor - x^y using only ~ and & 
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* 德摩根律：x|y = ~(~x & ~y)，再去掉同为 1 的位 */
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* 负数时 x>>31 是全 1，和 -x 相与 */
  int isNegative = x >> 31;
  return (~x + 1) & isNegative;
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* 取出 src 字节，清掉 dst 字节，再填进去 */
  int srcShift = src << 3;
  int dstShift = dst << 3;
  int byte = (x >> srcShift) & 0xFF;
  int dstMask = 0xFF << dstShift;
  return (x & ~dstMask) | (byte << dstShift);
}

// P5
/* 
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* 算术右移后把高 n 位清零 */
  int topBits = ((1 << 31) >> n) << 1;
  return (x >> n) & ~topBits;
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* 掩码 0x0F0F0F0F，高低 4 位各移 4 位 */
  int lowNibbles = 0x0F | (0x0F << 8);
  lowNibbles = lowNibbles | (lowNibbles << 16);
  return ((x & lowNibbles) << 4) | ((x >> 4) & lowNibbles);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* 先把最低的 0 填上，再找最低的 0 */
  int filled = x | (x + 1);
  return ~filled & (filled + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 异或折半，最后看第 0 位 */
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return ~x & 1;
}

// P9
/* 
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* 逻辑右移，再把移出去的位补到高处 */
  int right = n & 31;
  int left = (~right + 1) & 31;
  int topBits = ((1 << 31) >> right) << 1;
  return ((x >> right) & ~topBits) | (x << left);
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* 加上 half-1 和商的最低位，再清掉低 n 位 */
  int half = (1 << n) >> 1;
  int quotientIsOdd = (x >> n) & 1;
  int biased = x + half + ~0 + quotientIsOdd;
  return (biased >> n) << n;
}

// P11
/* 
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* (x&y) + ((x^y)>>1) 是向下取整的中点，和为奇数且 x 较大时加 1 */
  int diffBits = x ^ y;
  int floorMid = (x & y) + (diffBits >> 1);
  int xIsAbove = (floorMid + ~x + 1) >> 31;
  return floorMid + (diffBits & xIsAbove & 1);
}


// P12
/* 
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* x 只小于一个端点，或者等于端点 */
  int xorA = x ^ a;
  int xorB = x ^ b;
  int diffA = x + ~a + 1;
  int diffB = x + ~b + 1;
  int lessA = diffA ^ (xorA & (diffA ^ x));
  int lessB = diffB ^ (xorB & (diffB ^ x));
  int belowOne = ((lessA ^ lessB) >> 31) & 1;
  return belowOne | !xorA | !xorB;
}

// P13
/* 
 * mul5Sat - return x*5, and if x*5 overflow, change the result to 
 * INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* 2x、4x、5x 有一个变号就是溢出 */
  int times4 = x << 2;
  int times5 = times4 + x;
  int overflow = ((x ^ (x << 1)) | (x ^ times4) | (x ^ times5)) >> 31;
  int limit = (x >> 31) ^ ~(1 << 31);
  return (overflow & limit) | (~overflow & times5);
}

// P14
/* 
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 两次加法各记一次溢出方向，加起来就是结果 */
  int sumXY = x + y;
  int upXY = ((~x & ~y & sumXY) >> 31) & 1;
  int downXY = (x & y & ~sumXY) >> 31;
  int sum = sumXY + z;
  int upZ = ((~sumXY & ~z & sum) >> 31) & 1;
  int downZ = (sumXY & z & ~sum) >> 31;
  return upXY + downXY + upZ + downZ;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 乘 3 再右移 1 位或 2 位，向偶数舍入 */
  unsigned sign = uf & 0x80000000;
  unsigned exp = (uf >> 23) & 0xFF;
  unsigned mant = uf & 0x7FFFFF;
  unsigned triple;
  unsigned shift = 1;
  unsigned dropped;
  unsigned half;
  if (exp == 0xFF)
    return uf;
  if (exp == 0)
    exp = 1;
  else
    mant = mant | 0x800000;
  triple = mant + (mant << 1);
  if (triple >> 25) {
    shift = 2;
    exp = exp + 1;
  }
  mant = triple >> shift;
  dropped = triple & ((1 << shift) - 1);
  half = 1 << (shift - 1);
  if (dropped > half || (dropped == half && (mant & 1)))
    mant = mant + 1;
  if (exp == 0xFF)
    return sign | 0x7F800000;
  return sign | (((exp - 1) << 23) + mant);
}

// P16
/* 
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* 小于 1 的单独处理，其余直接在位模式上舍入 */
  unsigned sign = uf & 0x80000000;
  unsigned magnitude = uf & 0x7FFFFFFF;
  unsigned exp = magnitude >> 23;
  unsigned one;
  unsigned fraction;
  unsigned half;
  if (exp >= 150)
    return uf;
  if (exp < 127) {
    if (magnitude > 0x3F000000)
      return sign | 0x3F800000;
    return sign;
  }
  one = 1 << (150 - exp);
  fraction = uf & (one - 1);
  half = one >> 1;
  uf = uf - fraction;
  if (fraction > half || (fraction == half && (uf & one)))
    uf = uf + one;
  return uf;
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 左移到最高位为 1，留高 24 位，按丢掉的 8 位舍入 */
  unsigned sign = x & 0x80000000;
  unsigned magnitude = x;
  unsigned exp = 157;
  unsigned dropped;
  if (x == 0)
    return 0;
  if (sign)
    magnitude = -magnitude;
  while (!(magnitude & 0x80000000)) {
    magnitude = magnitude << 1;
    exp = exp - 1;
  }
  dropped = magnitude & 0xFF;
  magnitude = magnitude >> 8;
  if (dropped > 0x80 || (dropped == 0x80 && (magnitude & 1)))
    magnitude = magnitude + 1;
  return sign | ((exp << 23) + magnitude);
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 按 2 位、4 位、8 位分组求和 */
  int mask1 = 0x55 | (0x55 << 8);
  int mask2 = 0x33 | (0x33 << 8);
  int mask4 = 0x0F | (0x0F << 8);
  mask1 = mask1 | (mask1 << 16);
  mask2 = mask2 | (mask2 << 16);
  mask4 = mask4 | (mask4 << 16);
  x = (x & mask1) + ((x >> 1) & mask1);
  x = (x & mask2) + ((x >> 2) & mask2);
  x = (x + (x >> 4)) & mask4;
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* 16、8、4、2、1 位依次交换 */
  int mask16 = 0xFF | (0xFF << 8);
  int mask8 = mask16 ^ (mask16 << 8);
  int mask4 = mask8 ^ (mask8 << 4);
  int mask2 = mask4 ^ (mask4 << 2);
  int mask1 = mask2 ^ (mask2 << 1);
  x = (x << 16) | ((x >> 16) & mask16);
  x = ((x & mask8) << 8) | ((x >> 8) & mask8);
  x = ((x & mask4) << 4) | ((x >> 4) & mask4);
  x = ((x & mask2) << 2) | ((x >> 2) & mask2);
  x = ((x & mask1) << 1) | ((x >> 1) & mask1);
  return x;
}
