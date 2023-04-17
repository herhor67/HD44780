#pragma once

// http://1.bp.blogspot.com/-3rGvx1WiEHQ/VRJQyqSIqTI/AAAAAAAASAc/Gs9DN97CM8Q/s1600/PCF8574-LCD-HD44780-schemat.png

// Pin mappings
// P0 -> RS
// P1 -> RW
// P2 -> E
// P3 -> Backlight
// P4 -> D4
// P5 -> D5
// P6 -> D6
// P7 -> D7

// https://en.wikipedia.org/wiki/Hitachi_HD44780_LCD_controller

// RS - only used wor writing characters, otherwise 0
// RW - not used (only write)
// E - used internally for clocking data in

struct lcd_config_t
{
	uint8_t columns;		  /*!< Number of columns. Must be populated prior to calling lcd_init(). */
	uint8_t rows;			  /*!< Number of rows. Must be populated prior to calling lcd_init(). */
	uint8_t display_function; /*!< Current state of display function flag. Must be populated prior to calling lcd_init(). */
	uint8_t display_control;  /*!< Current state of display control flag. Must be populated prior to calling lcd_init(). */
	uint8_t display_mode;	  /*!< Current state of display mode flag. Must be populated prior to calling lcd_init(). */
	uint8_t backlight;		  /*!< Current state of backlight. */
};

struct lcd_dims_t
{
	uint8_t y;
	uint8_t x;
};

enum lcd_command_t : uint8_t
{
	LCD_DO_NOTHING /*   */ = 0b00000000,
	LCD_CLEAR_DISPLAY /**/ = 0b00000001,
	LCD_CURSOR_HOME /*  */ = 0b00000010,
	LCD_SET_ENTRY /*    */ = 0b00000100,
	LCD_SET_CONTROL /*  */ = 0b00001000,
	LCD_SET_MODE /*     */ = 0b00010000,
	LCD_SET_FUNCTION /* */ = 0b00100000,
	LCD_SET_CGR_ADDR /* */ = 0b01000000,
	LCD_SET_DDR_ADDR /* */ = 0b10000000,
};

// Refer Datasheet -> Table 6 for details

// display entry {
enum lcd_entry_t : uint8_t
{
	LCD_ENTRY_DECREMENT = 0b00000000, // Decrements DDRAM and shifts cursor left
	LCD_ENTRY_INCREMENT = 0b00000010, // Increments DDRAM and shifts cursor right
};
enum lcd_shift_t : uint8_t
{
	LCD_DISPLAY_NOSHIFT = 0b00000000, // Display does not shift
	LCD_DISPLAY_SHIFT = 0b00000001,	  // Shifts entire display. Right if decrement. Left if increment
};
// }

// display control {
enum lcd_display_t : uint8_t
{
	LCD_DISPLAY_OFF = 0b00000000, // Display OFF
	LCD_DISPLAY_ON = 0b00000100,  // Display ON
};

enum lcd_cursor_t : uint8_t
{
	LCD_CURSOR_OFF = 0b00000000, // Cursor OFF
	LCD_CURSOR_ON = 0b00000010,	 // Cursor ON
};

enum lcd_blink_t : uint8_t
{
	LCD_BLINK_OFF = 0b00000000, // Blink OFF
	LCD_BLINK_ON = 0b00000001,	// Blink ON
};
// }

// display shift {
enum lcd_move_t : uint8_t
{
	LCD_CURSOR_MOVE = 0b00000000,  // Move Cursor
	LCD_DISPLAY_MOVE = 0b00001000, // Move Display
};

enum lcd_dir_t : uint8_t
{
	LCD_MOVE_LEFT = 0b00000000,	 // Shift Left
	LCD_MOVE_RIGHT = 0b00000100, // Shift Right
};
// }

// display function {
enum lcd_mode_t : uint8_t
{
	LCD_4BIT = 0b00000000,
	LCD_8BIT = 0b00010000, // 1 << 4
};

enum lcd_lines_t : uint8_t
{
	LCD_1LINE = 0b00000000,
	LCD_2LINE = 0b00001000, // 1 << 3
};

enum lcd_dots_t : uint8_t
{
	LCD_5x8DOTS = 0b00000000,
	LCD_5x10DOTS = 0b00000100, // 1 << 2
};
// }

enum lcd_backlight_t : uint8_t
{
	LCD_BACKLIGHT_OFF = 0b00000000,
	LCD_BACKLIGHT_ON = 0b00001000, // 1 << 3
};

struct display_entry_t
{
	lcd_entry_t entry;
	lcd_shift_t shift;
	operator uint8_t() const
	{
		return entry | shift;
	}
};

struct display_control_t
{
	lcd_display_t display;
	lcd_cursor_t cursor;
	lcd_blink_t blink;
	operator uint8_t() const
	{
		return display | cursor | blink;
	}
};

struct display_mode_t
{
	lcd_move_t move;
	lcd_dir_t direction;
	operator uint8_t() const
	{
		return move | direction;
	}
};

struct display_function_t
{
	lcd_mode_t mode;
	lcd_lines_t lines;
	lcd_dots_t dots;
	operator uint8_t() const
	{
		return mode | lines | dots;
	}
};
