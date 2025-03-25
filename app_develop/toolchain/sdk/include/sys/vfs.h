
#ifndef _STATFS_H_
#define _STATFS_H_

#include <sys/types.h>

struct statfs {
    long    f_type;     /* type of file system (see below) */
    long    f_bsize;    /* optimal transfer block size */
    long    f_blocks;   /* total data blocks in file system */
    long    f_bfree;    /* free blocks in fs */
    long    f_bavail;   /* free blocks avail to non-superuser */
    long    f_files;    /* total file nodes in file system */
    long    f_ffree;    /* free file nodes in fs */
    long    f_fsid;     /* file system id */
    long    f_namelen;  /* maximum length of filenames */
};

typedef struct statfs kfs_stat;

int statfs(const char *path, struct statfs *st);
int lstat(const char *filename, struct stat *st);


#endif /* _STATFS_H_ */
