/* standard ASCII control characters */

static const char charval[32][6] = {
    "<NUL>", "<SOH>", "<STX>", "<ETX>", "<EOT>", "<ENQ>", "<ACK>", "<BEL>",
    "<BS>" , "<HT>" , "<LF>" , "<VT>" , "<FF>" , "<CR>" , "<SO>" , "<SI>" ,
    "<DLE>", "<DC1>", "<DC2>", "<DC3>", "<DC4>", "<NAK>", "<SYN>", "<ETB>",
    "<CAN>", "<EM>" , "<SUB>", "<ESC>", "<FS>" , "<GS>" , "<RS>" , "<US>"
};

/* Shortened definitons from the TeX documentation. I make no claim to
 * ownership of this list */

static const char catdesc[16][20] = {
    "Escape (\\)",
    "Begin group ({)",
    "End group (})",
    "Math shift ($)",
    "Align tab (&)",
    "EOL",
    "Parameter (#)",
    "Superscript (^)",
    "Subscript (_)",
    "Ignored (<NUL>)",
    "Space",
    "Letter (a-zA-Z)",
    "Other",
    "Active (~)",
    "Comment (%)",
    "Invalid (<DEL>)"
};

/* This information was gathered from the output of LaTeX and may not
 * be accurate on systems with different configurations.
 */

static const char catcode[256] = {
    /* control characters */
    15, 15, 15, 15, 15, 15, 15, 15, 15, 10, 12, 15, 13,  5, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
    /* punctuation */
    10, 12, 12,  6,  3, 14,  4, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    /* numbers and maths punctuation */
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    /* letters */
    12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 12,  0, 12,  7,  8,
    12, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
    11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,  1, 12,  2, 13, 15,
    /* non-ASCII */
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
    12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12
};
