#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "host.h"
#include "print.h"
#include "debug.h"

#define KEYMAP( \
	K00, K01, K02, K03, K04,      K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, \
	K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, \
	K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, \
	K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C,      K3E, \
	K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4B, K4C, K4D, K4E, \
	K50, K51, K52,                K56,           K59, K5A, K5B, K5C, K5D, K5E  \
) { \
	{ KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04,    KC_NO, KC_##K06, KC_##K07, KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E }, \
	{ KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17, KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E }, \
	{ KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27, KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E }, \
	{ KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37, KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C,    KC_NO, KC_##K3E }, \
	{ KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47, KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E }, \
	{ KC_##K50, KC_##K51, KC_##K52, KC_NO,    KC_NO,    KC_NO,    KC_##K56, KC_NO,    KC_NO,    KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E }  \
}

#include "keymap.h"

#define KEYMAPS_SIZE    (sizeof(keymaps) / sizeof(keymaps[0]))
#define FN_ACTIONS_SIZE (sizeof(fn_actions) / sizeof(fn_actions[0]))

/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
	if (layer < KEYMAPS_SIZE) {
		return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
	} else {
		// fall back to layer 0
		return pgm_read_byte(&keymaps[0][(key.row)][(key.col)]);
	}
}

/* translates Fn keycode to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
	action_t action;
	if (FN_INDEX(keycode) < FN_ACTIONS_SIZE) {
		action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
	} else {
		action.code = ACTION_NO;
	}
	return action;
}

/*
 * Macro definition
 */
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
	switch (id) {
		case HELLO:
			return (record->event.pressed ?
				MACRO( I(0), T(H), T(E), T(L), T(L), W(255), T(O), END ) :
				MACRO_NONE );
	}
	return MACRO_NONE;
}
