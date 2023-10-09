#ifndef YOBANI_SPRITE_FONT_H
#define YOBANI_SPRITE_FONT_H

#include "bn_sprite_font.h"
#include "bn_utf8_characters_map.h"
#include "bn_sprite_items_yobani_variable_8x8_font.h"
#include "bn_sprite_items_yobani_fixed_16x16_font.h"

constexpr bn::utf8_character yobani_variable_8x8_sprite_font_utf8_characters[] = {
	"Á", "É", "Í", "Ó", "Ú", "Ü", "Ñ", "á", "é", "í", "ó", "ú", "ü", "ñ", "¡", "¿"
};

constexpr int8_t yobani_variable_8x8_sprite_font_character_widths[] = {
	6,  // 32
	3,  // 33 !
	6,  // 34 "
	7,  // 35 #
	8,  // 36 $
	8,  // 37 %
	8,  // 38 &
	3,  // 39 '
	4,  // 40 (
	4,  // 41 )
	6,  // 42 *
	7,  // 43 +
	3,  // 44 ,
	7,  // 45 -
	3,  // 46 .
	8,  // 47 /
	8,  // 48 0
	7,  // 49 1
	8,  // 50 2
	8,  // 51 3
	8,  // 52 4
	8,  // 53 5
	8,  // 54 6
	8,  // 55 7
	8,  // 56 8
	8,  // 57 9
	3,  // 58 :
	3,  // 59 ;
	7,  // 60 <
	7,  // 61 =
	7,  // 62 >
	7,  // 63 ?
	8,  // 64 @
	8,  // 65 A
	8,  // 66 B
	8,  // 67 C
	8,  // 68 D
	8,  // 69 E
	8,  // 70 F
	8,  // 71 G
	8,  // 72 H
	8,  // 73 I
	8,  // 74 J
	8,  // 75 K
	8,  // 76 L
	8,  // 77 M
	8,  // 78 N
	8,  // 79 O
	8,  // 80 P
	8,  // 81 Q
	8,  // 82 R
	8,  // 83 S
	8,  // 84 T
	8,  // 85 U
	8,  // 86 V
	8,  // 87 W
	8,  // 88 X
	8,  // 89 Y
	8,  // 90 Z
	8,  // 91 [
	8,  // 92
	4,  // 93 ]
	7,  // 94 ^
	7,  // 95 _
	3,  // 96 `
	5,  // 97 a
	4,  // 98 b
	4,  // 99 c
	5,  // 100 d
	4,  // 101 e
	5,  // 102 f
	5,  // 103 g
	5,  // 104 h
	4,  // 105 i
	4,  // 106 j
	5,  // 107 k
	4,  // 108 l
	7,  // 109 m
	5,  // 110 n
	4,  // 111 o
	4,  // 112 p
	5,  // 113 q
	4,  // 114 r
	4,  // 115 s
	5,  // 116 t
	4,  // 117 u
	4,  // 118 v
	6,  // 119 w
	5,  // 120 x
	4,  // 121 y
	5,  // 122 z
	5,  // 123 {
	3,  // 124 |
	5,  // 125 }
	8,  // 126 ~
	7,  // Á
	6,  // É
	7,  // Í
	7,  // Ó
	7,  // Ú
	7,  // Ü
	7,  // Ñ
	5,  // á
	5,  // é
	5,  // í
	5,  // ó
	6,  // ú
	6,  // ü
	5,  // ñ
	3,  // ¡
	7,  // ¿
};

constexpr bn::span<const bn::utf8_character> yobani_variable_8x8_sprite_font_utf8_characters_span(yobani_variable_8x8_sprite_font_utf8_characters);

constexpr auto yobani_variable_8x8_sprite_font_utf8_characters_map = bn::utf8_characters_map<yobani_variable_8x8_sprite_font_utf8_characters_span>();

constexpr bn::sprite_font yobani_variable_8x8_sprite_font(
	bn::sprite_items::yobani_variable_8x8_font,
	yobani_variable_8x8_sprite_font_utf8_characters_map.reference(),
	yobani_variable_8x8_sprite_font_character_widths);

constexpr bn::sprite_font yobani_fixed_16x16_sprite_font(bn::sprite_items::yobani_fixed_16x16_font);

#endif