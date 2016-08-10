
# -*- sh_mode -*-

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
# THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS `AS IS'' AND
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

# debian	compile for debian system (i.e. if you want to make a debian package)
# default	compile for a normal system (i.e. everything goes to /usr/local)
# NOTE: Leave this undefined if you just want to check out suid-wrap first (i.e. you don't want to install anything)
SYSTYPE = "debian"

export SYSTYPE
export DESTDIR

all:
	${MAKE} -C src all
	${MAKE} -C man all

install:
	${MAKE} -C src install
	${MAKE} -C man install

uninstall:
	${MAKE} -C src uninstall
	${MAKE} -C man uninstall

clean:
	rm -f *~

distclean: clean
	${MAKE} -C src distclean
	${MAKE} -C man distclean
	rm -f build-stamp debian/{postinst.debhelper,prerm.debhelper,substvars,files}
	rm -rf debian/tmp

