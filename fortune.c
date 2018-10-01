/* DOS FORTUNE
 *
 *  (c) 2018 <stecdose@gmail.com>
 *  license: GPLv2
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define uint16_t    unsigned int
#define uint8_t     unsigned char
#define uint32_t    unsigned long
#define int8_t      signed char
#define int16_t     signed int
#define int32_t     signed long

#define DEFAULT_FOLDER  "C:\\GAMES\\FORTUNE\\"
#define CONFIG_FILE     "FORTUNE.CFG"

int print_cookie(char *cookie_file, uint16_t n);
uint16_t get_cookie_count(char *cookie_file);
uint16_t get_cfg_file_lines(char *config_file);
int get_rand_cat_from_cfg_file(char *config_file, char *cookie_file);


int main(int argc, char *argv[]) {
    char fortune_folder[128-11+1];    // max cmd line len - 8+3 for appending FORTUNE.CFG + '\0'
    char config_file[129];
    char cookie_file[129];
    char tmpstr[129];
    char category[129];
    uint16_t rndcookie, cookies;

    /* argument handling */
    if(argc == 1) {         // no args given, we use default fortune folder
        sprintf(fortune_folder, "%s", DEFAULT_FOLDER);
    } else if(argc == 2) {  // 1 arg given, we use this as fortune folder
        sprintf(fortune_folder, "%s", argv[1]);
    } else {                // more than one arg, error
        printf("ERROR!\r\n");
        printf("SYNTAX: FORTUNE.COM <folder>\r\n");
        exit(-1);
    }

    /* configuration file is FORTUNE.CFG (defined in CONFIG_FILE) in fortune folder 
     * backslash must be escaped in source (\ => \\)
     */
    sprintf(config_file, "%s\\%s", fortune_folder, CONFIG_FILE);

    // init random
    srand(time(NULL));

    /* now we get a random category from config file */
    while(get_rand_cat_from_cfg_file(config_file, &cookie_file) == -1);

    // assemble category name, folder+filename for cookie db
    sprintf(category, "%s", cookie_file);
    sprintf(tmpstr, "%s\\%s", fortune_folder, cookie_file);
    sprintf(cookie_file, "%s", tmpstr);

    // count cookies
    cookies = get_cookie_count(cookie_file);

    // pick a random cookie
    rndcookie = rand() % cookies;

    printf("cookie db '%s', %u cookies, #%u chosen\r\n", category, cookies, rndcookie);

    print_cookie(cookie_file, rndcookie);

    return 0;
}

uint16_t get_cookie_count(char *cookie_file) {
    FILE *f;
    uint16_t cookies;
    char tempstr[128];

    f = fopen(cookie_file, "r");
    if(f == NULL) {
        printf("get_cookie_count(): can't open cookie file '%s' for reading...\r\n", cookie_file);
        exit(-1);
    }

    cookies = 0;
    while(fgets(tempstr, 128, f)) {
         if(tempstr[0] == '%') { // cookies are seperated with a line only containing '%s'
             cookies++;
         }
    }

    fclose(f);

    return cookies;
}


/* returns number of valid entries in config file */
uint16_t get_cfg_file_lines(char *config_file) {
    FILE *f;
    uint16_t lines;
    char tmp[128];

    f = fopen(config_file, "r");
    if(f == NULL) {
        printf("get_cfg_file_lines(): can't open configuration file '%s' for reading...\r\n", config_file);
        exit(-1);
    }

    lines = 0;
    while(fgets(tmp, 128, f)) {
        lines++;
    }

    fclose(f);

    return lines;
}

int get_rand_cat_from_cfg_file(char *config_file, char *cookie_file) {
    FILE *f;
    uint16_t line, lines, num;
    char tmp[128];
    char buf[128];

    lines = get_cfg_file_lines(config_file);

    f = fopen(config_file, "r");
    if(f == NULL) {
        printf("get_rand_cat_from_cfg_file(): can't open configuration file '%s' for reading...\r\n", config_file);
        exit(-1);
    }


    num = rand() % lines;
    line = 0;
    while(fgets(tmp, 128, f)) {
        if(line == num) {   // we have found our category
            if(tmp[0] == '#') { // comment line, skip that
                return -1;
            }
            sprintf(buf, "%s", tmp);    // copy it to cat
            buf[strlen(buf)-2] = '\0';  // remove trailing \r\n
            sprintf(cookie_file, "%s", buf);
            fclose(f);
            return 0;
        }
        line++;
    }
    return -1;
}


int print_cookie(char *cookie_file, uint16_t n) {
    FILE *f;
    uint16_t cookies;
    char line[129];

    f = fopen(cookie_file, "r");
    if(f == NULL) {
        printf("print_cookie(): can't open cookie file '%s' for reading...\r\n", cookie_file);
        exit(-1);
    }

    // walk line by line, until we reach chosen cookie
    cookies = 0;
    while(fgets(line, 128, f)) {
        // actual cookie and chosen matches, no % = text to display
        if((cookies == n) && (line[0] != '%')) {
            printf("%s", line);
        }
        // actual cooke and chosen matches, and % = end of our cookie
        if((cookies == n) && (line[0] == '%')) {
            fclose(f);
            exit(0);
        }
        // actual cookie and chosen NOT matching, and % = end of some else cookie
        if(line[0] == '%') {
            cookies++;
        }
    }

    fclose(f);
}

