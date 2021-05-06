/*
 *
 * System5x7
 *
 *
 * File Name           : System5x7.h
 * Date                : 28 Oct 2008
 * Font size in bytes  : 470
 * Font width          : 5
 * Font height         : 7
 * Font first char     : 32
 * Font last char      : 127
 * Font used chars     : 94
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
#if (defined(__AVR__))
#include <avr/pgmspace.h>
#else
#include <pgmspace.h>
#endif

#ifndef angka_H
#define angka_H

#define angka6x13_WIDTH 6
#define angka6x13_HEIGHT 13

/*
 * added to allow fontname to match header file name. 
 * as well as keep the old name for backward compability
 */

#define angka6x13 angka6x13

const static uint8_t angka6x13[] PROGMEM = {
    0x03, 0xD0, 
    0x06, 
    0x0F, 
    0x30, 
    0x0A, 
    
   
    0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 
    0x06, 0x06, 
    
   
    0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, // 48
    0x08, 0x0C, 0xFE, 0xFE, 0x00, 0x00, 0x40, 0x40, 0x7F, 0x7F, 0x40, 0x40, // 49
    0x0C, 0x0E, 0x02, 0xC2, 0xFE, 0x3C, 0x70, 0x7C, 0x6F, 0x63, 0x60, 0x60, // 50
    0x0C, 0x8E, 0x82, 0x82, 0xFE, 0x7C, 0x30, 0x71, 0x41, 0x41, 0x7F, 0x3E, // 51
    0x80, 0xE0, 0x78, 0xFE, 0xFE, 0x00, 0x0F, 0x0F, 0x48, 0x7F, 0x7F, 0x48, // 52
    0x7E, 0x7E, 0x22, 0x22, 0xE2, 0xC2, 0x30, 0x70, 0x40, 0x40, 0x7F, 0x3F, // 53
    0xF0, 0xF8, 0x4C, 0x46, 0xC2, 0x82, 0x3F, 0x7F, 0x40, 0x40, 0x7F, 0x3F, // 54
    0x02, 0x02, 0x02, 0xE2, 0xFE, 0x1E, 0x00, 0x00, 0x7F, 0x7F, 0x00, 0x00, // 55
    0x7C, 0xFE, 0x82, 0x82, 0xFE, 0x7C, 0x3E, 0x7F, 0x41, 0x41, 0x7F, 0x3E, // 56
    0xFC, 0xFE, 0x02, 0x02, 0xFE, 0xFC, 0x41, 0x43, 0x62, 0x32, 0x1F, 0x0F // 57
    
};

#endif
