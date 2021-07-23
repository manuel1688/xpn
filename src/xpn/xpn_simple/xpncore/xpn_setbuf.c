/*
 * Copyright (c) 1987, 1997, 2006, Vrije Universiteit, Amsterdam,
 * The Netherlands All rights reserved. Redistribution and use of the MINIX 3
 * operating system in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 *     * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 
 *     * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 
 *     * Neither the name of the Vrije Universiteit nor the names of the
 *     software authors or contributors may be used to endorse or promote
 *     products derived from this software without specific prior written
 *     permission.
 * 
 *     * Any deviations from these conditions require written permission
 *     from the copyright holder in advance
 * 
 * 
 * Disclaimer
 * 
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS, AUTHORS, AND
 *  CONTRIBUTORS ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN
 *  NO EVENT SHALL PRENTICE HALL OR ANY AUTHORS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 *  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 *  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 *  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * setbuf.c - control buffering of a stream
 */
/* $Header$ */

#include	<stdio.h>
#include	"xpn/xpn_simple/loc_incl.h"

int xpn_setvbuf(register FILE *stream, char *buf, int mode, size_t size);

void
xpn_setbuf(register FILE *stream, char *buf)
{
	(void) xpn_setvbuf(stream, buf, (buf ? _IOFBF : _IONBF), (size_t) BUFSIZ);
}

void
xpn_setbuffer(register FILE *stream, char *buf, size_t size)
{
	(void) xpn_setvbuf(stream, buf, (buf ? _IOFBF : _IONBF), size);
}

void
xpn_setlinebuf(register FILE *stream)
{
	(void ) xpn_setvbuf(stream, (char *) NULL, _IOLBF, 0);
}