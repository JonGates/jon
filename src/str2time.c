#include "str2time.h"

/* converts from "YYYY:MM:DD:hh:mm:ss:uuuuuu" to time_t*/
time_t str2time(const char *s){
    struct tm tm;
    #define DELIM   ':'
    memset(&tm, 0, sizeof(tm));
    if (s) {
        tm.tm_year = atoi(s) - 1900;
        if ( (s = strchr(s, DELIM))) {
            tm.tm_mon = atoi(++s) - 1;
            if ( (s = strchr(s, DELIM))) {
                tm.tm_mday = atoi(++s);
                if ( (s = strchr(s, DELIM))) {
                    tm.tm_hour = atoi(++s);
                    if ( (s = strchr(s, DELIM))) {
                        tm.tm_min = atoi(++s);
                        if ( (s = strchr(s, DELIM))) {
                            tm.tm_sec = atoi(++s);
                        }
                    }
                }
            }
        }
    }
    return mktime(&tm);

}