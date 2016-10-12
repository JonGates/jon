#ifndef LOGINLOG_H
#define LOGINLOG_H


#include <errno.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <utime.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <utmp.h>
#include <utmpx.h>
#include <stddef.h>
#include <pwd.h>
#include <lastlog.h>
#include <getopt.h>
#include <ctype.h>
#include <stdlib.h>

#define UTMPFILE "/var/run/utmp"
#define WTMPFILE "/var/log/wtmp"
#define LASTLOGFILE "/var/log/lastlog"

int listLogInfo(const char *username);
int utmpUser(const char *filename,const char *username,const char *ip);
int wtmpUser(const char *filename,const char *username,const char *ip);
int modLastLog(const char *filename, const char *username, const char *ip, const char *ttyname, const char *str_time);

#endif