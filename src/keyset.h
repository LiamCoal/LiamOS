/**
 * An entire file dedicated to the keyset variable.
 * Its quite large
 * 
 * ? EX: keyset[1] = ESC
 */

const char keyset[0xFF] = {
    0, // KBD buffer full, don't do anything
    0, // ESC pressed, don't do anything
    '1',
    '2',
    '3',
    '4',
    '5',
    '6',
    '7',
    '8',
    '9',
    '0',
    '-',
    '=',
    '\b', // Backspace
    '\t', // Tab
    'Q',
    'W',
    'E',
    'R',
    'T',
    'Y',
    'U',
    'I',
    'O',
    'P',
    '[',
    ']',
    '\n', // Enter/Return
    0, // Ctrl pressed, don't do anything
    'A',
    'S',
    'D',
    'F',
    'G',
    'H',
    'J',
    'K',
    'L',
    ';',
    0, // Function key, don't do anything
    '\'', // Quote
    '`',
    0, // LShift pressed, don't do anything
    '\\', // Backslash
    'Z',
    'X',
    'C',
    'V',
    'B',
    'N',
    'M',
    ',',
    '.',
    '/',
    0, // RShift pressed, don't do anything
    0, // Grey*... what does that mean...
    ' ',
    0, // CapsLock pressed, don't do anything
    /**
     * Prepare yourself for the madness you're 
     * about to see...
     */
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // NumLock pressed, don't do anything
    0, // ScrollLock pressed, don't do anything
    0, // Home pressed, don't do anything
    0, // Up pressed, don't do anything
    0, // PgUp pressed, don't do anything
    0, // Grey-... wat
    0, // Left pressed, don't do anything
    0, // KeyPad, don't do anything
    0, // Right pressed, don't do anything
    0, // Another Grey one (grey+)
    0, // End pressed, don't do anything
    0, // Down pressed, don't do anything
    0, // PgDn pressed, don't do anything
    0, // Insert pressed, don't do anything
    0, // Delete pressed, don't do anything
    0, // SysReq pressed, don't do anything
    0, // F11 (version 2?) pressed, don't do anything
    0, // Left \ pressed, don't do anything
    0, // Shouldn't be reached?
    0, // Function key, don't do anything
    0, // F15 (version 47?), don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // Function key, don't do anything
    0, // -- pressed, what are these keys
    0, // EraseEOF pressed, don't do anything
    0, // Copy/Play pressed, don't do anything
    0, // Shouldn't be reached?
    0, // Shouldn't be reached?
    0, // CrSel pressed, don't do anything
    0, // Yet another weird button ([*])
    0, // ExSel pressed, don't do anything
    0, // -- pressed, again?
    0, // Clear pressed, don't do anything
    0, // "Note2", more like "version 2000000"
    0, // "Note2", more like "version 2000001"
    0, // "Note2", more like "version 2000002"
    0, // "Note2", more like "version 2000003"
    0, // "Note2", more like "version 2000004"
    0, // "Note2", more like "version 2000005"
    0, // "Note2", more like "version 2000006"
    0, // "Note2", more like "version 2000007"
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, // Self tested? Good! But I don't care.
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0, 0, // Prefix codes
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Reserved
    0, // ECHO?
    0, // #reserved
    0, // Prefix code
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, // Reserved
    0, // ACK
    0, 0, // "diag" failures
    0, // RESEND
    0 // Keyboard error
};
