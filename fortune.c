/* DOS FORTUNE 
 * 
 *  (c) 2018 <stecdose@gmail.com>
 *  license: GPLv2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define uint16_t    unsigned

#define DEFAULT_FOLDER  "C:\\GAMES\\FORTUNE\\"
#define DEFAULT_CONFIG  "FORTUNE.CFG"

static char folder[128];
char cfg[128];

int main(int argc, char *argv[]) {
    FILE *f;

    char str[129];
    char tmp[129];
    uint16_t lines, cookies;
    int i;

    if(argc == 1) {     // no args given
        sprintf(folder, "%s", DEFAULT_FOLDER);
    } else if(argc == 2) {
        sprintf(folder, "%s", argv[1]);
    }
    sprintf(cfg, "%s\\%s", folder, DEFAULT_CONFIG);

    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    lines = 0;
    while(fgets(str, 128, f)) {
        lines++;
    }
    fclose(f);

    srand(time(NULL));
    i = rand() % lines;

    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }

    lines = 0;
    while(fgets(str, 128, f)) {
        if(lines == i) {
            str[strlen(str)-1] = '\0';
            sprintf(tmp, "%s", str);
        }
        lines++;
    }
    fclose(f);

    sprintf(cfg, "%s\\%s", folder, tmp);

    printf("fortune db '%s', ", cfg);

    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("\r\ncan't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    cookies = 0;
    while(fgets(str, 128, f)) {
        if(str[0] == '%') {
            cookies++;
        }
    }
    fclose(f);

    i = rand() % cookies;

    printf("%d cookies, chosen %d\r\n", cookies, i);
    printf("\r\n");

    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    cookies = 0;
    while(fgets(str, 128, f)) {
        if((cookies == i) && (str[0] != '%')) {
            printf("%s", str);
        }
        if((cookies == i) && (str[0] == '%')) {
            fclose(f);
            exit(0);
        }

        if(str[0] == '%') {
            cookies++;
        }
    }

    fclose(f);

    exit(0);
}
