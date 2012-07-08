#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>

#include "chardata.h"

static void show_help (void);
static void process (char *line);

static void onechar (unsigned char u);
static int numeric (char *str);
static void ronechar (int c);
static void catinfo (char c);

static char buf[1024];

int main (int argc, char *argv[]) {
    char *line;
    int i;

    /* no arguments defined yet */

    /* allow quick lookups on the command line */
    for (i=1; i<argc; i++) {
        if (strlen(argv[i])) {
            process(argv[i]);
        }
    }
    if (argc > 1) return 0;

    do {
        if (isatty(fileno(stdin))) {
            line = readline("texref> ");
            if (!line) break;
        } else {
            int len;
            line = fgets(buf, sizeof(buf), stdin);
            if (!line) break;
            line = strdup(line);
            if (!line) break;
            len = strlen(line);
            if (len && line[len-1] == '\n') {
                if (len > 1 && line[len-2] == '\r') {
                    line[len-2] = '\0';
                    len -= 2;
                } else {
                    line[len-1] = '\0';
                    len--;
                }
            }
            if (len == sizeof(buf)-1) {
                fprintf(stderr, "Input line too long. Cowardly exiting.\n");
                return 2;
            }
        }
        if (line[0] == '\0') {
            free(line);
            continue;
        }
        add_history(line);
        process(line);
        free(line);
    } while (!feof(stdin));
    return 0;
}

static void show_help (void) {
    printf("\n"
           "help        Show this help message\n"
           "quit        Quit the program\n"
           "exit        Same as quit\n"
           "<character> Information about <character>\n"
           "<number>    Information about character with this decimal value\n"
           "<catcode>   Information about catcode with this decimal value\n"
           "\"<hex>      Information about character with this hex value\n"
           "\'<oct>      Information about character with this octal value\n"
           "<other>     Information about each character in <other>\n");
}

static void process (char *line) {
    int len, rchr, i;
    len = strlen(line);

    /* check for special commands */
    if (strcmp(line, "quit") == 0
            || strcmp(line, "exit") == 0) {
        exit(0);
    }
    if (strcmp(line, "quit") == 0) return;
    if (strcmp(line, "help") == 0) {
        show_help();
        return;
    }

    /* accept different numeric inputs
     * and do reverse lookups */
    if ((rchr = numeric(line)) >= 0) {
        if (rchr < 16 && line[0] >= '0' && line[1] <= '9') {
            catinfo(rchr);
        }
        ronechar(rchr);
        return;
    }

    /* print character-by-character information */
    for (i=0; i<len; i++) {
        onechar(line[i]);
    }
}

static void onechar (unsigned char u) {
    /* print character information */
    if (u < 32) {
        printf("ASCII %5s ^%c     ", charval[u], '@'+u);
    } else if (u < 63) {
        printf("ASCII ->%c<- ^%c     ", u, '@'+u);
    } else if (u == 63) {
        printf("ASCII ->%c<- ^<DEL> ", u);
    } else if (u < 96) {
        printf("ASCII ->%c<- ^%-5s ", u, charval[u-'@']);
    } else if (u < 127) {
        printf("ASCII ->%c<- ^%c     ", u, u-'@');
    } else if (u == 127) {
        printf("ASCII <DEL> ^?     ");
    } else {
        printf("                   ");
    }
    printf("\"0x%1$02x = \'0%1$03o = %1$3d cat: %2$2hhd %3$s\n",
            u, catcode[u], catdesc[(int)catcode[u]]);
}

static int numeric (char *str) {
    int r, base, len, i;

    len = strlen(str);
    if (len == 0) return -1;
    if ((*str >= '0' && *str <= '9')) { /* decimal */
        base = 10;
    } else if (len > 1 && *str == '\"') { /* hex */
        base = 16; str++; len--;
    } else if (len > 1 && *str == '\'') { /* octal */
        base = 8; str++; len--;
    } else { /* invalid */
        return -1;
    }

    /* 4 more characters should be enough */
    if (len > 4) return -1;

    /* assume remaining characters should be digits in our base */
    r = 0; /* result */

    if (base == 8) {
        for (i=0; i<len; i++) {
            if (str[i] < '0' || str[i] > '7') return -1;
            r = r*base + (str[i]-'0');
            if (r > 255) return -1;
        }
    } else if (base == 10) {
        for (i=0; i<len; i++) {
            if (str[i] < '0' || str[i] > '9') return -1;
            r = r*base + (str[i]-'0');
            if (r > 255) return -1;
        }
    } else if (base == 16) {
        char x;
        if (len > 2 && str[0] == '0' && str[1] == 'x') {
            /* drop 0x... */
            str+=2;
            len-=2;
        }
        for (i=0; i<len; i++) {
            if (str[i] >= '0' && str[i] <= '9') {
                x = str[i]-'0';
            } else if (str[i] >= 'a' && str[i] <= 'z') {
                x = 10 + str[i]-'a';
            } else if (str[i] >= 'A' && str[i] <= 'Z') {
                x = 10 + str[i]-'A';
            } else return -1;
            r = r*base + x;
            if (r > 255) return -1;
        }
    } else { /* unknown base? */
        return -1;
    }

    return r;
}

static void ronechar (int c) {
    if (c < 0 || c > 255) return;
    onechar ((unsigned char) c);
}

static void catinfo (char c) {
    if (c < 0 || c > 15) return;
    printf("CATCODE %2hhd: %s\n", c, catdesc[(int)c]);
}
