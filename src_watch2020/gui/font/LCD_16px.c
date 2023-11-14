/*******************************************************************************
 * Size: 10 px
 * Bpp: 2
 * Opts: 
 * https://freefontsdownload.net/free-modern_lcd_7-font-2180.htm
 ******************************************************************************/
#include "lvgl.h"

#ifndef LCD_16PX
#define LCD_16PX 1
#endif

#if LCD_16PX

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xe0, 0xfe, 0xac, 0x17, 0x45, 0x60,

    /* U+0022 "\"" */
    0x72, 0xf0, 0x7f, 0x0,

    /* U+0023 "#" */
    0x1c, 0xb0, 0xb0, 0xfe, 0x40, 0x9a, 0x49, 0x3a,
    0x69, 0xa0, 0x48, 0x34, 0x94, 0xa, 0xa, 0x6,
    0x9a, 0x74, 0x2, 0x6, 0x51, 0x24, 0xc, 0x3c,

    /* U+0024 "$" */
    0x3f, 0xce, 0xd7, 0x20, 0x40, 0xa0, 0xd6, 0x1f,
    0xf2, 0x49, 0x26, 0xbd, 0xf, 0x87, 0x20, 0xff,
    0x98, 0x2f, 0x9f, 0x12, 0x1d, 0x80,

    /* U+0025 "%" */
    0xb8, 0x2c, 0x74, 0x34, 0x61, 0xdf, 0x81, 0x88,
    0x6c, 0xc3, 0x4e, 0x1a, 0x70, 0xd3, 0x21, 0x2e,
    0xd, 0x31, 0x7a, 0xe, 0x50, 0x85, 0x2a,

    /* U+0026 "&" */
    0xff, 0x6, 0x50, 0x73, 0x44, 0x3f, 0xf9, 0x3e,
    0x7, 0xa5, 0xd2, 0xa6, 0x8d, 0x41, 0xff, 0xc5,
    0x68, 0xaa, 0x22, 0xf8,

    /* U+0027 "'" */
    0xe0, 0xc0,

    /* U+0028 "(" */
    0x3e, 0x21, 0x41, 0xf4, 0x50, 0x83, 0xf2, 0xd1,
    0x0,

    /* U+0029 ")" */
    0xf1, 0x1a, 0x83, 0xf4, 0xa, 0x2, 0xf, 0x2d,
    0x10,

    /* U+002A "*" */
    0xf, 0xd9, 0x5c, 0x48, 0xa9, 0xc0, 0xca, 0x85,
    0x4a, 0x85, 0x4a, 0xc0, 0xc9, 0x12, 0x80,

    /* U+002B "+" */
    0xa, 0x81, 0xc8, 0x7f, 0x9f, 0xf, 0x9f, 0xf,
    0x83, 0xfe, 0x80,

    /* U+002C "," */
    0xf0, 0x56, 0xe0,

    /* U+002D "-" */
    0x17, 0x86, 0xbb, 0x7f, 0xc0,

    /* U+002E "." */
    0x95, 0x80,

    /* U+002F "/" */
    0xf, 0x68, 0x7d, 0x87, 0xd8, 0x76, 0x21, 0xb3,
    0xd, 0x38, 0x69, 0xc3, 0x4c, 0x84, 0xb8, 0x34,
    0xc1, 0xff, 0xc9,

    /* U+0030 "0" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x7c,
    0x32, 0x38, 0x66, 0x43, 0xd0, 0x7f, 0xf1, 0x5a,
    0xc1, 0x97, 0x18,

    /* U+0031 "1" */
    0xfc, 0xd4, 0x6b, 0x7, 0xff, 0xd, 0xc, 0xc1,
    0xa0, 0xff, 0xe3, 0xe0,

    /* U+0032 "2" */
    0xff, 0x9a, 0xf1, 0xaf, 0x83, 0xff, 0x8f, 0x7e,
    0x49, 0xe, 0x95, 0xfa, 0xf, 0xfe, 0x33, 0xfc,
    0xa0, 0xf2,

    /* U+0033 "3" */
    0xff, 0x9a, 0xf1, 0xaf, 0x83, 0xff, 0x8f, 0x7e,
    0x45, 0x6, 0x77, 0xf8, 0xc3, 0xff, 0x89, 0xfe,
    0x2, 0x1e, 0x80,

    /* U+0034 "4" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xce, 0xfc, 0x92,
    0x19, 0x9f, 0xe2, 0xf, 0xfe, 0x9e,

    /* U+0035 "5" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x7f,
    0xc0, 0x90, 0xda, 0xbf, 0x8c, 0x3f, 0xf8, 0x9f,
    0xe0, 0x21, 0xe8,

    /* U+0036 "6" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x67,
    0xf2, 0x22, 0xe8, 0x55, 0x62, 0xf, 0xfe, 0x2b,
    0x58, 0x32, 0xe3,

    /* U+0037 "7" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x78,
    0x32, 0x61, 0xcc, 0x1f, 0x41, 0xff, 0xd3, 0xc0,

    /* U+0038 "8" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x77,
    0xf2, 0x22, 0xf4, 0xaa, 0xc4, 0x1f, 0xfc, 0x56,
    0xb0, 0x65, 0xc6,

    /* U+0039 "9" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc9, 0x21, 0x9d, 0xfe, 0x30, 0xff, 0xe2, 0x7f,
    0x80, 0x87, 0xa0,

    /* U+003A ":" */
    0xe7, 0x90, 0xd2, 0xb0,

    /* U+003B ";" */
    0x91, 0xce, 0xf, 0xfe, 0x27, 0x82, 0xb7,

    /* U+003C "<" */
    0xd, 0xc1, 0x66, 0xc, 0x93, 0x58, 0x47, 0x3,
    0x92, 0x16, 0x48, 0x51, 0x80,

    /* U+003D "=" */
    0x17, 0x86, 0xbb, 0x7f, 0xc1, 0xf3, 0xfe, 0x5f,
    0x40,

    /* U+003E ">" */
    0xe0, 0xca, 0x6, 0x48, 0x36, 0x43, 0x46, 0xde,
    0x14, 0x14, 0x0,

    /* U+003F "?" */
    0xff, 0x90, 0x2e, 0x32, 0xb8, 0x1a, 0x1f, 0xfc,
    0x57, 0xc8, 0x68, 0x28, 0x33, 0xc1, 0xff, 0xc0,
    0xe0, 0xf4, 0x87, 0x9c, 0x20,

    /* U+0040 "@" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1d, 0xe8, 0x3e,
    0xc2, 0xc1, 0x28, 0xb2, 0xc6, 0x80, 0x98, 0x83,
    0x93, 0xb, 0xf2, 0x3f, 0xca, 0xf, 0x20,

    /* U+0041 "A" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc9, 0x2f, 0xa8, 0xd6, 0x20, 0xff, 0xe9, 0xe0,

    /* U+0042 "B" */
    0xff, 0x21, 0x2e, 0x91, 0xac, 0x61, 0xff, 0xc6,
    0xfd, 0x12, 0xf5, 0x4d, 0x62, 0xf, 0xfe, 0x2b,
    0x58, 0x80, 0xba, 0x0,

    /* U+0043 "C" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xec, 0x3c,
    0x87, 0xce, 0x1f, 0xfd, 0x37, 0xf9, 0x41, 0xe4,

    /* U+0044 "D" */
    0xff, 0x21, 0x2e, 0x91, 0xac, 0x61, 0xff, 0xc5,
    0x83, 0x45, 0x3, 0x54, 0x1e, 0x83, 0xff, 0x8a,
    0xd6, 0x20, 0x2e, 0x80,

    /* U+0045 "E" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x7f,
    0xc0, 0x50, 0x68, 0x57, 0xe8, 0x3f, 0xf8, 0xcf,
    0xf2, 0x83, 0xc8,

    /* U+0046 "F" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x7f,
    0xc0, 0x90, 0xd1, 0x3f, 0xa0, 0xff, 0xea, 0x80,

    /* U+0047 "G" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x6c,
    0xa, 0x2, 0x6, 0x98, 0xe3, 0xe2, 0xf, 0xfe,
    0x2b, 0x58, 0x32, 0xe3,

    /* U+0048 "H" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xce, 0xfc, 0x92,
    0xfa, 0x8d, 0x62, 0xf, 0xfe, 0x9e,

    /* U+0049 "I" */
    0xfe, 0x7c, 0x3a, 0x1f, 0xfc, 0x3c, 0x32, 0x1c,
    0xe1, 0xff, 0xc8, 0xf0, 0xea, 0xc, 0x80,

    /* U+004A "J" */
    0xff, 0x9a, 0xf1, 0xaf, 0x83, 0xff, 0x98, 0x87,
    0xcc, 0xc1, 0xd4, 0xf, 0xfe, 0x23, 0x58, 0x32,
    0xe3,

    /* U+004B "K" */
    0xe0, 0xdc, 0x1d, 0x18, 0x69, 0xd0, 0xb6, 0xb,
    0xc6, 0x85, 0xd0, 0x32, 0xa4, 0x32, 0x8c, 0x3d,
    0x98, 0x7b, 0x30, 0xf6, 0x62, 0x1b, 0x20,

    /* U+004C "L" */
    0xe0, 0xff, 0xed, 0xe1, 0xf6, 0x1f, 0xfd, 0x37,
    0xf9, 0x41, 0xe4,

    /* U+004D "M" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xc6, 0xca, 0x5,
    0x1b, 0xa5, 0x31, 0x6a, 0x3, 0x81, 0x7, 0xff,
    0x4f,

    /* U+004E "N" */
    0xe0, 0xda, 0x1f, 0x61, 0xfe, 0xc3, 0xf4, 0x1d,
    0xa, 0x22, 0x99, 0x35, 0x2, 0x32, 0x9, 0xb0,
    0xf2, 0x83, 0xff, 0x8b, 0x80,

    /* U+004F "O" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x7c,
    0x32, 0x38, 0x66, 0x43, 0xd0, 0x7f, 0xf1, 0x5a,
    0xc1, 0x97, 0x18,

    /* U+0050 "P" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc9, 0x21, 0xd4, 0x7f, 0x41, 0xff, 0xd5,

    /* U+0051 "Q" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x78,
    0x32, 0x50, 0x33, 0x40, 0xf4, 0x1f, 0xfc, 0xb,
    0x40, 0xd0, 0xc, 0x8b, 0x44,

    /* U+0052 "R" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc8, 0xa0, 0xe9, 0x40, 0xf4, 0x16, 0x61, 0xec,
    0xc3, 0xd9, 0x88, 0x6c, 0x80,

    /* U+0053 "S" */
    0x3f, 0xce, 0xd7, 0x20, 0x5e, 0xf, 0xfe, 0x2a,
    0x56, 0x4d, 0x7a, 0x1f, 0xe2, 0xf, 0xfe, 0x27,
    0xf8, 0x90, 0xec,

    /* U+0054 "T" */
    0xff, 0x9f, 0x87, 0xc8, 0x7f, 0xf4, 0x20, 0xf3,
    0x7, 0x90, 0xff, 0xea, 0x61, 0x0,

    /* U+0055 "U" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xcd, 0xc3, 0x23,
    0x86, 0x64, 0x3d, 0x7, 0xff, 0x15, 0xac, 0x19,
    0x71, 0x80,

    /* U+0056 "V" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xcd, 0x83, 0x23,
    0x6, 0x64, 0x3d, 0x8, 0x51, 0xe3, 0x26, 0x4c,
    0xd6, 0xb, 0x18, 0x0,

    /* U+0057 "W" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0x41, 0xf3, 0x6,
    0xc3, 0x23, 0x86, 0x64, 0x3d, 0x7, 0xff, 0x15,
    0x86, 0xc, 0x81, 0x30,

    /* U+0058 "X" */
    0xe0, 0xda, 0x1f, 0x61, 0xfa, 0x60, 0x64, 0xcd,
    0x98, 0x15, 0xb8, 0x74, 0x86, 0x90, 0x60, 0x5b,
    0xc6, 0x4c, 0xc, 0x83, 0xff, 0x87, 0x80,

    /* U+0059 "Y" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xce, 0xfc, 0x92,
    0x19, 0xdf, 0xe3, 0xf, 0xfe, 0x27, 0xf8, 0x8,
    0x7a,

    /* U+005A "Z" */
    0xff, 0x9a, 0xf1, 0xaf, 0x8c, 0x3b, 0x10, 0xd9,
    0x86, 0x9c, 0x34, 0xe1, 0xa6, 0x42, 0x99, 0xc,
    0xb0, 0x79, 0xfe, 0x50, 0x79,

    /* U+005B "[" */
    0xf8, 0x10, 0xa0, 0xfb, 0x1c, 0x43, 0xf9, 0x40,
    0x80,

    /* U+005C "\\" */
    0x70, 0xf6, 0x1f, 0x61, 0xf2, 0x61, 0xec, 0xc3,
    0xdb, 0x7, 0xb6, 0xe, 0x66, 0xe, 0x5c, 0x1d,
    0x30, 0x7f, 0xf1, 0x0,

    /* U+005D "]" */
    0xbc, 0xc9, 0x90, 0x7f, 0xf0, 0x10, 0x98, 0x28,
    0x3f, 0xa0, 0x49, 0x80,

    /* U+005E "^" */
    0xb, 0x43, 0xa2, 0x42, 0xd9, 0x93, 0x15, 0x12,
    0x8, 0x11, 0x80,

    /* U+005F "_" */
    0xff, 0x99, 0x7e,

    /* U+0060 "`" */
    0x63, 0x78, 0x0,

    /* U+0061 "a" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc9, 0x2f, 0xa8, 0xd6, 0x20, 0xff, 0xe9, 0xe0,

    /* U+0062 "b" */
    0xff, 0x21, 0x2e, 0x91, 0xac, 0x61, 0xff, 0xc6,
    0xfd, 0x12, 0xf5, 0x4d, 0x62, 0xf, 0xfe, 0x2b,
    0x58, 0x80, 0xba, 0x0,

    /* U+0063 "c" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xec, 0x3c,
    0x87, 0xce, 0x1f, 0xfd, 0x37, 0xf9, 0x41, 0xe4,

    /* U+0064 "d" */
    0xff, 0x21, 0x2e, 0x91, 0xac, 0x61, 0xff, 0xc5,
    0x83, 0x45, 0x3, 0x54, 0x1e, 0x83, 0xff, 0x8a,
    0xd6, 0x20, 0x2e, 0x80,

    /* U+0065 "e" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x7f,
    0xc0, 0x50, 0x68, 0x57, 0xe8, 0x3f, 0xf8, 0xcf,
    0xf2, 0x83, 0xc8,

    /* U+0066 "f" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x7f,
    0xc0, 0x90, 0xd1, 0x3f, 0xa0, 0xff, 0xea, 0x80,

    /* U+0067 "g" */
    0xff, 0x91, 0xae, 0x40, 0xbc, 0x1f, 0xfc, 0x6c,
    0xa, 0x2, 0x6, 0x98, 0xe3, 0xe2, 0xf, 0xfe,
    0x2b, 0x58, 0x32, 0xe3,

    /* U+0068 "h" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xce, 0xfc, 0x92,
    0xfa, 0x8d, 0x62, 0xf, 0xfe, 0x9e,

    /* U+0069 "i" */
    0xfe, 0x7c, 0x3a, 0x1f, 0xfc, 0x3c, 0x32, 0x1c,
    0xe1, 0xff, 0xc8, 0xf0, 0xea, 0xc, 0x80,

    /* U+006A "j" */
    0xff, 0x9a, 0xf1, 0xaf, 0x83, 0xff, 0x98, 0x87,
    0xcc, 0xc1, 0xd4, 0xf, 0xfe, 0x23, 0x58, 0x32,
    0xe3,

    /* U+006B "k" */
    0xe0, 0xdc, 0x1d, 0x18, 0x69, 0xd0, 0xb6, 0xb,
    0xc6, 0x85, 0xd0, 0x32, 0xa4, 0x32, 0x8c, 0x3d,
    0x98, 0x7b, 0x30, 0xf6, 0x62, 0x1b, 0x20,

    /* U+006C "l" */
    0xe0, 0xff, 0xed, 0xe1, 0xf6, 0x1f, 0xfd, 0x37,
    0xf9, 0x41, 0xe4,

    /* U+006D "m" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xc6, 0xca, 0x5,
    0x1b, 0xa5, 0x31, 0x6a, 0x3, 0x81, 0x7, 0xff,
    0x4f,

    /* U+006E "n" */
    0xe0, 0xda, 0x1f, 0x61, 0xfe, 0xc3, 0xf4, 0x1d,
    0xa, 0x22, 0x99, 0x35, 0x2, 0x32, 0x9, 0xb0,
    0xf2, 0x83, 0xff, 0x8b, 0x80,

    /* U+006F "o" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x7c,
    0x32, 0x38, 0x66, 0x43, 0xd0, 0x7f, 0xf1, 0x5a,
    0xc1, 0x97, 0x18,

    /* U+0070 "p" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc9, 0x21, 0xd4, 0x7f, 0x41, 0xff, 0xd5,

    /* U+0071 "q" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x78,
    0x32, 0x50, 0x33, 0x40, 0xf4, 0x1f, 0xfc, 0xb,
    0x40, 0xd0, 0xc, 0x8b, 0x44,

    /* U+0072 "r" */
    0xff, 0x90, 0x2e, 0x31, 0xac, 0x1f, 0xfc, 0x8f,
    0xc8, 0xa0, 0xe9, 0x40, 0xf4, 0x16, 0x61, 0xec,
    0xc3, 0xd9, 0x88, 0x6c, 0x80,

    /* U+0073 "s" */
    0x3f, 0xce, 0xd7, 0x20, 0x5e, 0xf, 0xfe, 0x2a,
    0x56, 0x4d, 0x7a, 0x1f, 0xe2, 0xf, 0xfe, 0x27,
    0xf8, 0x90, 0xec,

    /* U+0074 "t" */
    0xff, 0x9f, 0x87, 0xc8, 0x7f, 0xf4, 0x20, 0xf3,
    0x7, 0x90, 0xff, 0xea, 0x61, 0x0,

    /* U+0075 "u" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xcd, 0xc3, 0x23,
    0x86, 0x64, 0x3d, 0x7, 0xff, 0x15, 0xac, 0x19,
    0x71, 0x80,

    /* U+0076 "v" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xcd, 0x83, 0x23,
    0x6, 0x64, 0x3d, 0x8, 0x51, 0xe3, 0x26, 0x4c,
    0xd6, 0xb, 0x18, 0x0,

    /* U+0077 "w" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0x41, 0xf3, 0x6,
    0xc3, 0x23, 0x86, 0x64, 0x3d, 0x7, 0xff, 0x15,
    0x86, 0xc, 0x81, 0x30,

    /* U+0078 "x" */
    0xe0, 0xda, 0x1f, 0x61, 0xfa, 0x60, 0x64, 0xcd,
    0x98, 0x15, 0xb8, 0x74, 0x86, 0x90, 0x60, 0x5b,
    0xc6, 0x4c, 0xc, 0x83, 0xff, 0x87, 0x80,

    /* U+0079 "y" */
    0xe0, 0xda, 0x1f, 0x61, 0xff, 0xce, 0xfc, 0x92,
    0x19, 0xdf, 0xe3, 0xf, 0xfe, 0x27, 0xf8, 0x8,
    0x7a,

    /* U+007A "z" */
    0xff, 0x9a, 0xf1, 0xaf, 0x8c, 0x3b, 0x10, 0xd9,
    0x86, 0x9c, 0x34, 0xe1, 0xa6, 0x42, 0x99, 0xc,
    0xb0, 0x79, 0xfe, 0x50, 0x79,

    /* U+007B "{" */
    0x3e, 0xa, 0x2, 0x83, 0x21, 0x46, 0x2b, 0x24,
    0x3f, 0xf8, 0xa, 0xa,

    /* U+007C "|" */
    0xe0, 0xfe, 0xac, 0x1f, 0xb0,

    /* U+007D "}" */
    0xf8, 0x82, 0x50, 0x7f, 0xd8, 0x67, 0x37, 0xf,
    0xca, 0x4, 0x10,

    /* U+007E "~" */
    0x3, 0x8e, 0x6, 0x28, 0x2a, 0x24, 0xd4, 0x49,
    0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 136, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 136, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 136, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 10, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 79, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 136, .box_w = 2, .box_h = 3, .ofs_x = 3, .ofs_y = 9},
    {.bitmap_index = 101, .adv_w = 136, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 136, .box_w = 3, .box_h = 12, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 136, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 134, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 145, .adv_w = 136, .box_w = 3, .box_h = 3, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 148, .adv_w = 136, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 153, .adv_w = 136, .box_w = 2, .box_h = 2, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 136, .box_w = 5, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 205, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 294, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 329, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 348, .adv_w = 136, .box_w = 2, .box_h = 7, .ofs_x = 3, .ofs_y = 3},
    {.bitmap_index = 352, .adv_w = 136, .box_w = 3, .box_h = 11, .ofs_x = 3, .ofs_y = -1},
    {.bitmap_index = 359, .adv_w = 136, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 372, .adv_w = 136, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 381, .adv_w = 136, .box_w = 5, .box_h = 8, .ofs_x = 2, .ofs_y = 2},
    {.bitmap_index = 392, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 436, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 472, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 488, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 508, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 543, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 563, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 577, .adv_w = 136, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 609, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 632, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 643, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 660, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 681, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 700, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 715, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 736, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 790, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 808, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 828, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 888, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 909, .adv_w = 136, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 918, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 938, .adv_w = 136, .box_w = 4, .box_h = 12, .ofs_x = 4, .ofs_y = 0},
    {.bitmap_index = 950, .adv_w = 136, .box_w = 8, .box_h = 5, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 961, .adv_w = 136, .box_w = 8, .box_h = 2, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 964, .adv_w = 136, .box_w = 3, .box_h = 3, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 967, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 983, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1003, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1019, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1039, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1058, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1094, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1108, .adv_w = 136, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1123, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1140, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1163, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1191, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1212, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1231, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1246, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1267, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1288, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1307, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1321, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1339, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1359, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1379, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1402, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1419, .adv_w = 136, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1440, .adv_w = 136, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1452, .adv_w = 136, .box_w = 2, .box_h = 12, .ofs_x = 3, .ofs_y = 0},
    {.bitmap_index = 1457, .adv_w = 136, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1468, .adv_w = 136, .box_w = 8, .box_h = 4, .ofs_x = 0, .ofs_y = 5}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 1,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t LCD_16px = {
#else
lv_font_t LCD_16px = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LCD_16PX*/

