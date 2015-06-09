static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* 0: Default Layer */
	KEYMAP( \
		 ESC,   F1,   F2,   F3,   F4,         F5,   F6,   F7,   F8,   F9,  F10,  F11,  F12,  BRK, \
		 GRV,    1,    2,    3,    4,    5,    6,    7,    8,    9,    0, MINS,  EQL, BSPC,  FN2, \
		 TAB,    Q,    W,    E,    R,    T,    Y,    U,    I,    O,    P, LBRC, RBRC,  ENT,  FN3, \
		CAPS,    A,    S,    D,    F,    G,    H,    J,    K,    L, SCLN, QUOT, NUHS,        FN4, \
		LSFT, NUBS,    Z,    X,    C,    V,    B,    N,    M, COMM,  DOT, SLSH, RSFT,   UP,  DEL, \
		LCTL, LGUI, LALT,                    SPC,             RALT,  FN1,  FN0, LEFT, DOWN, RGHT  \
	),
	/* 1: Function Layer 1 (MODIFIERS) */
	KEYMAP( \
		TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PSCR, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, \
		TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, PGUP,  INS, \
		TRNS, TRNS, TRNS,                   TRNS,             TRNS,  FN1,  FN0, HOME, PGDN,  END  \
	),
	/* 2: Function Layer 2 (EXTRA) */
	KEYMAP( \
		TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,  PWR, \
		TRNS, BTN1, BTN2, BTN3, BTN4, BTN5, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, MSTP, TRNS, \
		TRNS, TRNS, MS_U, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, MYCM, TRNS, TRNS, MPLY, TRNS, \
		TRNS, MS_L, MS_D, MS_R, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS, TRNS,       TRNS, \
		TRNS, TRNS, TRNS, TRNS, CALC, TRNS, TRNS, TRNS, MAIL, TRNS, TRNS, TRNS, TRNS, VOLU, MUTE, \
		TRNS, TRNS, TRNS,                   TRNS,             TRNS,  FN1,  FN0, MPRV, VOLD, MNXT  \
	)
};

enum macro_id {
	HELLO,
};

static const uint16_t PROGMEM fn_actions[] = {
	[0] = ACTION_LAYER_MOMENTARY(1),
	[1] = ACTION_LAYER_MOMENTARY(2),
	[2] = ACTION_MACRO(HELLO)
};
