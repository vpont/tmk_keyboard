#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/delay.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"

#ifndef DEBOUNCE
#   define DEBOUNCE	5
#endif
static uint8_t debouncing = DEBOUNCE;

/* matrix state(1:on, 0:off) */
static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static matrix_row_t read_cols(void);
static void init_cols(void);
static void unselect_rows(void);
static void select_row(uint8_t row);

inline
uint8_t matrix_rows(void)
{
	return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
	return MATRIX_COLS;
}

void matrix_init(void)
{
	// initialize row and col
	unselect_rows();
	init_cols();

	// initialize matrix state: all keys off
	for (uint8_t i=0; i < MATRIX_ROWS; i++) {
		matrix[i] = 0;
		matrix_debouncing[i] = 0;
	}
}

uint8_t matrix_scan(void)
{
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		select_row(i);
		_delay_us(30);  // without this wait read unstable value.
		matrix_row_t cols = read_cols();
		if (matrix_debouncing[i] != cols) {
			matrix_debouncing[i] = cols;
			if (debouncing) {
				debug("bounce!: "); debug_hex(debouncing); debug("\n");
			}
			debouncing = DEBOUNCE;
		}
		unselect_rows();
	}

	if (debouncing) {
		if (--debouncing) {
			_delay_ms(1);
		} else {
			for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
				matrix[i] = matrix_debouncing[i];
			}
		}
	}

	return 1;
}

bool matrix_is_modified(void)
{
	if (debouncing) return false;
	return true;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
	return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
	return matrix[row];
}

void matrix_print(void)
{
	print("\nr/c 0123456789ABCDEF\n");
	for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
		phex(row); print(": ");
		pbin_reverse16(matrix_get_row(row));
		print("\n");
	}
}

uint8_t matrix_key_count(void)
{
	uint8_t count = 0;
	for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
		count += bitpop16(matrix[i]);
	}
	return count;
}

/* Column pin configuration
 * col: C0  C1  C2  C3  C4  C5  C6  C7  C8  C9  C10 C11 C12 C13 C14
 * pin: B0  B1  B2  B3  B7  D0  D1  D2  C6  D3  C7  D7  B4  B5  B6
 */
static void  init_cols(void)
{
	DDRB  &= ~(1<<7 | 1<<6 | 1<< 5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
	PORTB |=  (1<<7 | 1<<6 | 1<< 5 | 1<<4 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
	DDRC  &= ~(1<<7 | 1<<6);
	PORTC |=  (1<<7 | 1<<6);
	DDRD  &= ~(1<<7 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
	PORTD |=  (1<<7 | 1<<3 | 1<<2 | 1<<1 | 1<<0);
}

static matrix_row_t read_cols(void)
{
	return	(PINB&(1<<0) ? 0 : (1<<0)) |
		(PINB&(1<<1) ? 0 : (1<<1)) |
		(PINB&(1<<2) ? 0 : (1<<2)) |
		(PINB&(1<<3) ? 0 : (1<<3)) |
		(PINB&(1<<7) ? 0 : (1<<4)) |
		(PIND&(1<<0) ? 0 : (1<<5)) |
		(PIND&(1<<1) ? 0 : (1<<6)) |
		(PIND&(1<<2) ? 0 : (1<<7)) |
		(PINC&(1<<6) ? 0 : (1<<8)) |
		(PIND&(1<<3) ? 0 : (1<<9)) |
		(PINC&(1<<7) ? 0 : (1<<10)) |
		(PIND&(1<<7) ? 0 : (1<<11)) |
		(PINB&(1<<4) ? 0 : (1<<12)) |
		(PINB&(1<<5) ? 0 : (1<<13)) |
		(PINB&(1<<6) ? 0 : (1<<14));
}

/* Row pin configuration
 * row: R0  R1  R2  R3  R4  R5
 * pin: F0  F1  F4  F5  F6  F7
 */
static void unselect_rows(void)
{
	DDRF  &= ~0b11110011;
	PORTF &= ~0b11110011;
}

static void select_row(uint8_t row)
{
	switch (row) {
		case 0 :
			DDRF  |= (1<<0);
			PORTF &= ~(1<<0);
			break;
		case 1 :
			DDRF  |= (1<<1);
			PORTF &= ~(1<<1);
			break;
		case 2 :
			DDRF  |= (1<<4);
			PORTF &= ~(1<<4);
			break;
		case 3 :
			DDRF  |= (1<<5);
			PORTF &= ~(1<<5);
			break;
		case 4 :
			DDRF  |= (1<<6);
			PORTF &= ~(1<<6);
			break;
		case 5 :
			DDRF  |= (1<<7);
			PORTF &= ~(1<<7);
			break;
	}
}
