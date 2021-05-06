

/*
 *
 * DejaVuSansItalic9
 *
 * created with FontCreator
 * written by F. Maximilian Thiele
 *
 * http://www.apetech.de/fontCreator
 * me@apetech.de
 *
 * File Name           : DejaVuSansItalic9.h
 * Date                : 28.05.2012
 * Font size in bytes  : 4572
 * Font width          : 10
 * Font height         : 10
 * Font first char     : 32
 * Font last char      : 128
 * Font used chars     : 96
 *
 * The font data are defined as
 *
 * struct _FONT_ {
 *     uint16_t   font_Size_in_Bytes_over_all_included_Size_it_self;
 *     uint8_t    font_Width_in_Pixel_for_fixed_drawing;
 *     uint8_t    font_Height_in_Pixel_for_all_characters;
 *     unit8_t    font_First_Char;
 *     uint8_t    font_Char_Count;
 *
 *     uint8_t    font_Char_Widths[font_Last_Char - font_First_Char +1];
 *                  // for each character the separate width in pixels,
 *                  // characters < 128 have an implicit virtual right empty row
 *
 *     uint8_t    font_data[];
 *                  // bit field of all characters
 */

#include <inttypes.h>
#include <avr/pgmspace.h>

#ifndef DEJAVUSANSITALIC9_H
#define DEJAVUSANSITALIC9_H

#define DEJAVUSANSITALIC9_WIDTH 10
#define DEJAVUSANSITALIC9_HEIGHT 10

static uint8_t const DejaVuSansItalic9[] PROGMEM = {
    0x11, 0xDC, // size
    0x0A, // width
    0x0A, // height
    0x20, // first char
    0x60, // char count
    
    // char widths
    0x00, 0x03, 0x03, 0x06, 0x04, 0x07, 0x06, 0x01, 0x03, 0x03, 
    0x05, 0x05, 0x01, 0x03, 0x01, 0x03, 0x05, 0x04, 0x05, 0x05, 
    0x05, 0x05, 0x04, 0x05, 0x05, 0x05, 0x02, 0x02, 0x06, 0x06, 
    0x06, 0x04, 0x08, 0x06, 0x05, 0x06, 0x06, 0x05, 0x05, 0x06, 
    0x07, 0x03, 0x03, 0x06, 0x04, 0x08, 0x07, 0x06, 0x05, 0x06, 
    0x05, 0x06, 0x05, 0x06, 0x05, 0x08, 0x06, 0x05, 0x06, 0x04, 
    0x02, 0x04, 0x04, 0x05, 0x02, 0x05, 0x05, 0x04, 0x06, 0x05, 
    0x03, 0x05, 0x05, 0x03, 0x03, 0x05, 0x03, 0x08, 0x05, 0x05, 
    0x05, 0x05, 0x04, 0x04, 0x03, 0x05, 0x05, 0x07, 0x05, 0x05, 
    0x05, 0x04, 0x01, 0x05, 0x06, 0x05, 
    
    // font data
    0x80, 0x38, 0x06, 0x00, 0x00, 0x00, // 33
    0x06, 0x00, 0x06, 0x00, 0x00, 0x00, // 34
    0x20, 0xF8, 0x2E, 0xF8, 0x2E, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 35
    0x98, 0xDC, 0xA6, 0x64, 0x00, 0x40, 0x00, 0x00, // 36
    0x1C, 0xD2, 0x2E, 0x10, 0xEC, 0x92, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 37
    0x60, 0x9C, 0x92, 0xA2, 0x64, 0x90, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 38
    0x06, 0x00, // 39
    0xF8, 0x06, 0x01, 0x00, 0x00, 0x00, // 40
    0x80, 0x61, 0x1E, 0x00, 0x00, 0x00, // 41
    0x12, 0x0C, 0x1E, 0x0C, 0x12, 0x00, 0x00, 0x00, 0x00, 0x00, // 42
    0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, // 43
    0x80, 0x00, // 44
    0x20, 0x20, 0x20, 0x00, 0x00, 0x00, // 45
    0x80, 0x00, // 46
    0x60, 0x30, 0x0C, 0x00, 0x00, 0x00, // 47
    0x78, 0x84, 0x82, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, // 48
    0x80, 0x82, 0xF2, 0x8E, 0x00, 0x00, 0x00, 0x00, // 49
    0x80, 0xC4, 0xA2, 0x92, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, // 50
    0x40, 0x84, 0x92, 0x92, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, // 51
    0x40, 0x70, 0xC8, 0x7C, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, // 52
    0x80, 0x9C, 0x92, 0x92, 0x72, 0x00, 0x00, 0x00, 0x00, 0x00, // 53
    0x78, 0x94, 0x92, 0x72, 0x00, 0x00, 0x00, 0x00, // 54
    0x82, 0x42, 0x32, 0x0E, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 55
    0x60, 0xAC, 0x92, 0x92, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, // 56
    0x80, 0x9C, 0x92, 0x72, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, // 57
    0x80, 0x08, 0x00, 0x00, // 58
    0x80, 0x08, 0x00, 0x00, // 59
    0x20, 0x20, 0x50, 0x50, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 60
    0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 61
    0x88, 0x50, 0x50, 0x50, 0x20, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 62
    0x82, 0x32, 0x0A, 0x06, 0x00, 0x00, 0x00, 0x00, // 63
    0xE0, 0x18, 0xE8, 0x94, 0x94, 0xF4, 0xCC, 0x78, 0x40, 0xC0, 0x80, 0x80, 0x80, 0x40, 0x00, 0x00, // 64
    0x80, 0x60, 0x38, 0x24, 0x3E, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 65
    0xC0, 0xB8, 0x96, 0x92, 0x6E, 0x00, 0x00, 0x00, 0x00, 0x00, // 66
    0x78, 0x84, 0x82, 0x82, 0x82, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 67
    0xC0, 0xB8, 0x86, 0x82, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 68
    0xC0, 0xB8, 0x96, 0x92, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 69
    0xC0, 0x38, 0x16, 0x12, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 70
    0x78, 0x84, 0x82, 0x82, 0x92, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 71
    0xC0, 0x38, 0x16, 0x10, 0xD0, 0x38, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 72
    0xC0, 0x38, 0x06, 0x00, 0x00, 0x00, // 73
    0x00, 0xF0, 0x0E, 0xC0, 0x00, 0x00, // 74
    0xC0, 0x38, 0x16, 0x68, 0x84, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 75
    0xC0, 0xB8, 0x86, 0x80, 0x00, 0x00, 0x00, 0x00, // 76
    0xC0, 0x38, 0x06, 0x38, 0x10, 0xC8, 0x3C, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 77
    0xC0, 0x38, 0x06, 0x38, 0xC0, 0x38, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 78
    0x78, 0x84, 0x82, 0x82, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 79
    0xC0, 0x38, 0x16, 0x12, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, // 80
    0x78, 0x84, 0x82, 0x82, 0x42, 0x3C, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, // 81
    0xC0, 0x38, 0x16, 0x72, 0x8E, 0x00, 0x00, 0x00, 0x00, 0x00, // 82
    0x40, 0x8C, 0x92, 0x92, 0x62, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 83
    0x02, 0xC2, 0x3A, 0x06, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 84
    0x78, 0x86, 0x80, 0x80, 0x78, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 85
    0x0E, 0xF0, 0x40, 0x30, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00, // 86
    0xFE, 0x60, 0x1C, 0x02, 0xFE, 0x60, 0x1C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 87
    0x80, 0x42, 0x2C, 0x10, 0x6C, 0x82, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 88
    0x02, 0xCC, 0x30, 0x0C, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, // 89
    0x80, 0xC2, 0xA2, 0x92, 0x8A, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 90
    0xC0, 0xBC, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, // 91
    0x1E, 0xE0, 0x00, 0x00, // 92
    0x80, 0xC0, 0x3D, 0x03, 0x00, 0x00, 0x00, 0x00, // 93
    0x04, 0x02, 0x02, 0x04, 0x00, 0x00, 0x00, 0x00, // 94
    0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, // 95
    0x01, 0x02, 0x00, 0x00, // 96
    0xC0, 0xA8, 0xA8, 0xE8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 97
    0xC0, 0x7C, 0x93, 0x88, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 98
    0xF0, 0x98, 0x88, 0x08, 0x00, 0x00, 0x00, 0x00, // 99
    0xF0, 0x98, 0x88, 0xC8, 0x3C, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 100
    0x70, 0xB8, 0xA8, 0xA8, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, // 101
    0xC8, 0x3E, 0x09, 0x00, 0x00, 0x00, // 102
    0xF0, 0x98, 0x88, 0xC8, 0x38, 0x80, 0x80, 0x80, 0x40, 0x00, // 103
    0xC0, 0x3C, 0x13, 0xC8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, // 104
    0xE0, 0x38, 0x01, 0x00, 0x00, 0x00, // 105
    0xC0, 0x38, 0x01, 0xC0, 0x00, 0x00, // 106
    0xC0, 0x3C, 0x23, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 107
    0xC0, 0x3C, 0x03, 0x00, 0x00, 0x00, // 108
    0xE0, 0x18, 0x08, 0xC8, 0x78, 0x10, 0xC8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 109
    0xE0, 0x38, 0x08, 0xC8, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, // 110
    0x70, 0x98, 0x88, 0xC8, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, // 111
    0xE0, 0x98, 0x88, 0xC8, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, // 112
    0xF0, 0x88, 0x88, 0xF0, 0x18, 0x00, 0x00, 0xC0, 0x00, 0x00, // 113
    0xE0, 0x38, 0x08, 0x08, 0x00, 0x00, 0x00, 0x00, // 114
    0x80, 0xB8, 0xA8, 0xE8, 0x00, 0x00, 0x00, 0x00, // 115
    0xF8, 0x8C, 0x08, 0x00, 0x00, 0x00, // 116
    0xE0, 0x98, 0x80, 0xE0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, // 117
    0x38, 0xC0, 0x60, 0x10, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 118
    0xF8, 0x60, 0x10, 0xF8, 0x40, 0x30, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 119
    0x80, 0x48, 0x30, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00, // 120
    0x00, 0xF8, 0x60, 0x10, 0x08, 0x80, 0x40, 0x00, 0x00, 0x00, // 121
    0x80, 0xC8, 0xA8, 0x98, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, // 122
    0x08, 0xF8, 0x87, 0x01, 0x00, 0x00, 0x00, 0x00, // 123
    0xFE, 0xC0, // 124
    0x80, 0x80, 0x71, 0x0F, 0x08, 0x00, 0x00, 0x40, 0x00, 0x00, // 125
    0x20, 0x10, 0x10, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, // 126
    0xFC, 0x04, 0x04, 0x04, 0xFC, 0xC0, 0x80, 0x80, 0x80, 0xC0 // 127
    
};

#endif
