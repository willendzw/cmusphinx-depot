/* ====================================================================
 * Copyright (c) 1999-2001 Carnegie Mellon University.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer. 
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * This work was supported in part by funding from the Defense Advanced 
 * Research Projects Agency and the National Science Foundation of the 
 * United States of America, and the CMU Sphinx Speech Consortium.
 *
 * THIS SOFTWARE IS PROVIDED BY CARNEGIE MELLON UNIVERSITY ``AS IS'' AND 
 * ANY EXPRESSED OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL CARNEGIE MELLON UNIVERSITY
 * NOR ITS EMPLOYEES BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ====================================================================
 *
 */
/*
 * srvcore.h -- Raw socket functions packaged up a bit better.
 * 
 * HISTORY
 * 
 * 02-May-95	M K Ravishankar (rkm@cs.cmu.edu) at Carnegie Mellon University.
 * 		Adapted from Brian Milnes's initial version.
 */

#ifndef _SRVCORE_H_
#define _SRVCORE_H_

#include <s2types.h>

#if (defined(WIN32) && !defined(__CYGWIN__))
#include "win32sock.h"
#else
#include "posixsock.h"
#endif

int32 server_initialize (int32 port);	/* Initialize server, use port as binding addr.
					   Return 0 if successful, -1 otherwise. */

SOCKET server_await_conn ( void );	/* Await connection request from client.
					   Configure accepted socket in TCP_NODELAY,
					   nonblocking mode.  Return accepted socket */

void server_close_conn (SOCKET);	/* Close connection to client over socket */

void server_end (void);			/* Before winding up program */

int32 server_send_block (SOCKET sd, char *buf, int32 len);
					/* Send len bytes from buf over socket, until all
					   bytes sent.  Return #bytes sent, -1 if error. */

int32 server_recv_noblock (SOCKET sd, char *buf, int32 len);
					/* Receive upto len bytes into buf over socket.
					   Return #bytes read (possibly 0 for non-blocking
					   socket), -1 if EOF, -2 if error. */

int32 server_recv_block (SOCKET sd, char *buf, int32 len);
					/* Similar to server_recv_noblock but blocks if no data */

void server_openlog ( void );		/* For logging all recvd data for debugging */
void server_closelog ( void );

#endif
