
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

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#include "typedefs.h"
#include "utils.h"

int my_system (const char *command)
{
   int pid, status;
   if (command == 0)
	 return 1;
   pid = fork ();
   if (pid == -1)
	 return -1;
   if (pid == 0)
	 {
		char *argv[4];
		argv[0] = "sh";
		argv[1] = "-c";
		argv[2] = (char *) command;
		argv[3] = NULL;
		execve ("/bin/sh",argv,environ);
		exit (127);
	 }
   do
	 {
		if (waitpid (pid,&status,0) == -1)
		  {
			 if (errno != EINTR) return -1;
		  }
		else
		  {
			 return WEXITSTATUS (status);
		  }
	 }
    while (TRUE);
}

int main (int argc,char *argv[])
{
   int errcode=0;
   char cur_path[255];
   char *p=NULL;
   strncpy(cur_path, argv[0], 255);
   p=cur_path+strlen(cur_path);
   while (*(--p)!='/');
   *p=0;
   strcat(cur_path, "/install_from_git.sh");
   runasuser ("root","root");
   errcode = my_system (cur_path);
   return errcode;
}

