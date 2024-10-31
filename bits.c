/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(x & y) & ~(~x & ~y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if (!x && !y)
        return 1;
    if (x && y && !((x >> 31) ^ (y >> 31)))
        return 1;
    return 0;
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int result = 0;
    int shift = ((v > 0xFFFF) << 4);
    result = result | shift;
    v = v >> shift;
    shift = ((v > 0xFF) << 3);
    result = result | shift;
    v = v >> shift;
    shift = ((v > 0xF) << 2);
    result = result | shift;
    v = v >> shift;
    shift = ((v > 0x3) << 1);
    result = result | shift;
    v = v >> shift;
    result = result | (v > 0x1);
    return result;
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int act_n = n << 3;
    int act_m = m << 3;
    int n_byte = (x >> act_n) & 0xFF;
    int m_byte = (x >> act_m) & 0xFF;
    int mask = ~((0xFF << act_n) | (0xFF << act_m));
    return ((x & mask) | (n_byte << act_m) | (m_byte << act_n));
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned mask1 = 0x55555555;
    unsigned mask1_rever = 0xAAAAAAAA;
    unsigned mask2 = 0x33333333;
    unsigned mask2_rever = 0xCCCCCCCC;
    unsigned mask3 = 0x0F0F0F0F;
    unsigned mask3_rever = 0xF0F0F0F0;
    unsigned mask4 = 0x00FF00FF;
    unsigned mask4_rever = 0xFF00FF00;
    v = ((v & mask1) << 1 | ((v & mask1_rever) >> 1));
    v = ((v & mask2) << 2 | ((v & mask2_rever) >> 2));
    v = ((v & mask3) << 4 | ((v & mask3_rever) >> 4));
    v = ((v & mask4) << 8 | ((v & mask4_rever) >> 8));
    v = ((v << 16) | (v >> 16));
    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int mask = 0xFFFFFFFF;
    mask = mask & (~(((1 << 31) >> n) << 1));
    return (x >> n) & mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int R_32 = !~x;
    x &= R_32 + 0xFFFFFFFF;
    int R_16 = !(~(x & 0xFFFF0000) & 0xFFFF0000);
    x <<= (R_16 << 4);
    int R_8 = !(~(x & 0xFF000000) & 0xFF000000);
    x <<= (R_8 << 3);
    int R_4 = !(~(x & 0xF0000000) & 0xF0000000);
    x <<= (R_4 << 2);
    int R_2 = !(~(x & 0xC0000000) & 0xC0000000);
    x <<= (R_2 << 1);
    int R_0 = !(~(x & 0x80000000) & 0x80000000);
    return (R_32 << 5) | (R_16 << 4) | (R_8 << 3) | (R_4 << 2) | (R_2 << 1) | R_0;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    if (x == 0)
        return 0;
    unsigned sign = 0, exp, frac, absolute;
    int e = 158;
    if (x < 0) {
        absolute = -x;
        sign = 0x80000000;
    } else {
        absolute = x;
        sign = 0;
    }
    while (!(absolute & 0x80000000)) {
        absolute <<= 1;
        e -= 1;
    }
    frac = (absolute & 0x7FFFFFFF) >> 8;
    unsigned rest = absolute & 0xFF;
    if (rest > 128) {
        frac++;
        if (frac >> 23) {
            frac = 0;
            e++;
        }
    }
    if (rest == 128) {
        if (frac & 1) {
            frac++;
            if (frac >> 23) {
                frac = 0;
                e++;
            }
        }
    }
    exp = e << 23;
    return sign | exp | frac;
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000;
    unsigned exp = uf & 0x7F800000;
    unsigned frac = uf & 0x007FFFFF;
    if (exp == 0x7F800000)
        return uf;
    if (exp == 0) {
        frac = frac << 1;
        if (frac & 0x00800000) {
            exp = 0x00800000;
            frac = frac & 0x007FFFFF;
        }
    } else {
        exp += 0x00800000;
        if (exp == 0x7F800000) {
            frac = 0;
        }
    }
    return sign | exp | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int sign = uf2 & (1 << 31);
    int exp = ((uf2 >> 20) & 0x7FF) - 1023;
    int frac = 0x40000000 | ((uf2 & 0x000FFFFF) << 10) | (uf1 >> 22);
    if (exp < 0)
        return 0;
    if (exp > 31)
        return 0x80000000;
    int result = frac >> (30 - exp);
    if (sign)
        return -result;
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    unsigned exp, frac, result;
    if (x < -149) {
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        exp = 0;
        frac = 1 << (x + 149);
    } else if (x < 128) {
        exp = x + 127;
        frac = 0;
    } else {
        exp = 255;
        frac = 0;
    }
    result = exp << 23 | frac;
    return result;
}
