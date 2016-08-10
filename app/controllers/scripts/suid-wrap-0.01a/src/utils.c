
/*
 * Copyright (c) Abraham vd Merwe <abz@blio.net>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "typedefs.h"

/*
 * Check if the given file is one of the types specified in
 * type, and that we have the necessary permissions to open
 * the file in the mode specified. Mode can be one or more of
 * the following characters: 'r' (readable), 'w' (writable),
 * 'x' (executable), e.g. "rw" would mean that we want read
 * and write permissions. Type can be one or more of the
 * following characters: 'l' (symbolic link), 'r' (regular
 * file), 'd' (directory), 'c' (character device), 'b' (block
 * device), 'f' (fifo), 's' (socket), e.g. "bsf" would mean
 * that we want a block device, socket, or a fifo. Both type
 * and mode must contain at least one character.
 */
bool fperm (const char *filename,const char *type,const char *mode)
{
   struct stat filestat;
   int i;
   /* Check parameters */
   if ((strlen (type) > 7) || (*type == '\0')) return FALSE;
   if ((strlen (mode) > 3) || (*mode == '\0')) return FALSE;
   for (i = 0; i < (int) strlen (type); i++)
	 if ((type[i] != 'l') &&
		 (type[i] != 'r') &&
		 (type[i] != 'd') &&
		 (type[i] != 'c') &&
		 (type[i] != 'b') &&
		 (type[i] != 'f') &&
		 (type[i] != 's')) return FALSE;
   for (i = 0; i < (int) strlen (mode); i++)
	 if ((mode[i] != 'r') &&
		 (mode[i] != 'w') &&
		 (mode[i] != 'x')) return FALSE;
   /* Get file permissions */
   if (stat (filename,&filestat) < 0) return FALSE;
   /* Check file types */
   if ((strchr (type,'l') != NULL) && (!S_ISLNK (filestat.st_mode))) return FALSE;
   if ((strchr (type,'r') != NULL) && (!S_ISREG (filestat.st_mode))) return FALSE;
   if ((strchr (type,'d') != NULL) && (!S_ISDIR (filestat.st_mode))) return FALSE;
   if ((strchr (type,'c') != NULL) && (!S_ISCHR (filestat.st_mode))) return FALSE;
   if ((strchr (type,'b') != NULL) && (!S_ISBLK (filestat.st_mode))) return FALSE;
   if ((strchr (type,'f') != NULL) && (!S_ISFIFO (filestat.st_mode))) return FALSE;
   if ((strchr (type,'s') != NULL) && (!S_ISSOCK (filestat.st_mode))) return FALSE;
   /* Are we almighty root? */
   if (!getuid () || !getgid ()) return (TRUE);
   /* Are we the user? */
   if (filestat.st_uid == getuid ())
	 {
		/* Check file permissions for user */
		if ((strchr (mode,'r') != NULL) && (!(S_IRUSR & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'w') != NULL) && (!(S_IWUSR & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'x') != NULL) && (!(S_IXUSR & filestat.st_mode))) return FALSE;
	 }
   /* Are we in the group then? */
   else if (filestat.st_gid == getgid ())
	 {
		/* Check file permissions for group */
		if ((strchr (mode,'r') != NULL) && (!(S_IRGRP & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'w') != NULL) && (!(S_IWGRP & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'x') != NULL) && (!(S_IXGRP & filestat.st_mode))) return FALSE;
	 }
   /* We're a lowly other then */
   else
	 {
		/* Check file permissions for other */
		if ((strchr (mode,'r') != NULL) && (!(S_IROTH & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'w') != NULL) && (!(S_IWOTH & filestat.st_mode))) return FALSE;
		if ((strchr (mode,'x') != NULL) && (!(S_IXOTH & filestat.st_mode))) return FALSE;
	 }
   return TRUE;
}

void bail (const char *fmt, ...)
{
   va_list ap;
   va_start (ap,fmt);
   vfprintf (stderr,fmt,ap);
   va_end (ap);
   fflush (stderr);
   exit (EXIT_FAILURE);
}

bool runasuser (char *user,char *group)
{
   struct passwd *pw;
   if ((pw = getpwnam (user)) == NULL) return FALSE;	/* User doesn't exist */
   if (setuid (pw->pw_uid) != 0) return FALSE;		/* Couldn't change to uid */
   if (setgid (pw->pw_gid) != 0) return FALSE;		/* Couldn't change to gid */
   return TRUE;
}

