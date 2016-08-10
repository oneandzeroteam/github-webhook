
# -*- sh -*-

# Copyright (c) Abraham vd Merwe <abz@blio.net>
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 3. Neither the name of the University nor the names of its contributors
#    may be used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

# Name of program
PROGNAME = suid-wrap

##
## You don't need to edit this
##

ifeq (${SYSTYPE},"debian")
prefix = ${DESTDIR}/usr
bindir = ${prefix}/sbin
else
ifeq (${SYSTYPE},"default")
prefix = /usr/local
bindir = ${prefix}/sbin
else
TEST_ONLY = 1
endif
endif

BINGRP = bin
BINOWN = root
BINMODE = 0555

CC = colorgcc
CFLAGS = -Wall -O2 -Winline

LD = ld
LDFLAGS = -O2
LDLIBS =

INSTALL = install
INSTALL_PROGRAM = ${INSTALL} -s
INSTALL_DATA = ${INSTALL}

SOURCES = wrapper.c utils.c
OBJECTS = ${SOURCES:%.c=%.o}

##
## RULES
##

.PHONY: all clean install uninstall distclean do-it-all with-depends without-depends

all: do-it-all

ifeq (.depends,${wildcard .depends})
include .depends
do-it-all: with-depends
else
do-it-all: without-depends
endif

without-depends: depend with-depends

with-depends: ${PROGNAME}

${PROGNAME}: ${OBJECTS}
	${CC} ${LDFLAGS} $^ -o $@ ${LDLIBS}

depend:
	rm -f .depends
	set -e; for F in ${SOURCES}; do ${CC} -MM ${CPPFLAGS} $$F >> .depends; done

clean:
	rm -f .depends *~ ${OBJECTS} ${PROGNAME}

distclean: clean

ifndef TEST_ONLY
install: all
	${INSTALL} -d ${bindir}
	${INSTALL_PROGRAM} -g ${BINGRP} -o ${BINOWN} -m ${BINMODE} ${PROGNAME} ${bindir}

uninstall:
	rm -f ${bindir}/${PROGNAME}
endif

