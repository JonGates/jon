/*Resever & restore file's atime & mtime*/
#include "rewrite_time.h"

/*save file's atime & mtime*/
int save_time(const char * filename){
	if(stat(filename,&statbuf)<0){
		perror("Stat error");
		return -1;
	}
	return 0;
}

/*restore atime & mtime*/
int restore_time(const char * filename){
	struct utimbuf timebuf;
	uid_t owner = 0;   
    gid_t group = 0;
	
	timebuf.actime = statbuf.st_atime;
	timebuf.modtime = statbuf.st_mtime;
	owner = statbuf.st_uid;
    group = statbuf.st_gid;
	
	if (chown (filename, owner, group) < 0){
        perror("chown ");
		return -1;
      }

	if(utime(filename,&timebuf)<0){
		perror("utime ");
		return -1;
	}
	return 0;
}