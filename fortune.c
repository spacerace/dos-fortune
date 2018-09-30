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
    } else {
        printf("too much arguments!\r\n");
        exit(-1);
    }
    sprintf(cfg, "%s\\%s", folder, DEFAULT_CONFIG);

    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    lines = 0;
    // count lines of config file (each one is a cookie database/category
    while(fgets(str, 128, f)) {     
        lines++;
    }
    fclose(f);

    // pick a random line (category)
    srand(time(NULL));
    i = rand() % lines;

    // open config again
    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }

    // get content of randomly chosen line (filename of cookie file)
    lines = 0;
    while(fgets(str, 128, f)) {
        if(lines == i) {
            str[strlen(str)-1] = '\0';
            sprintf(tmp, "%s", str);
            continue;   // we stop scanning here, we have the filename
        }
        lines++;
    }
    fclose(f);

    // assemble folder+filename
    sprintf(cfg, "%s\\%s", folder, tmp);
    printf("fortune db '%s', ", cfg);

    // now open cookie file
    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("\r\ncan't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    
    // count cookies
    cookies = 0;
    while(fgets(str, 128, f)) {
        if(str[0] == '%') {     // cookies are seperated with a line only containing '%'
            cookies++;
        }
    }
    fclose(f);

    // now choose a random cookie
    i = rand() % cookies;
    printf("%d cookies, chosen #%d\r\n\r\n", cookies, i);

    // open cookie file
    f = fopen(cfg, "r");
    if(f == NULL) {
        printf("can't open '%s' for reading...\r\n", cfg);
        exit(-1);
    }
    // walk line by line, until we reach chosen cookie
    cookies = 0;
    while(fgets(str, 128, f)) {
        // actual cookie and chosen matches, no % = text to display
        if((cookies == i) && (str[0] != '%')) {
            printf("%s", str);
        }
        // actual cooke and chosen matches, and % = end of our cookie
        if((cookies == i) && (str[0] == '%')) {
            fclose(f);
            exit(0);
        }
        // actual cookie and chosen NOT matching, and % = end of some else cookie
        if(str[0] == '%') {
            cookies++;
        }
    }

    fclose(f);

    exit(0);
}
