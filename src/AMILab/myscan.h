/*
    ==================================================
    Software : AMILab
    Authors  : Karl Krissian
    Email    : karl@bwh.harvard.edu

    AMILab is a language for image processing
    ==================================================
    Copyright (C) 1996-2005  Karl Krissian

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

    ================================================== 
   The full GNU Lesser General Public License file is in Devel/Sources/Prog/LesserGPL_license.txt
*/


#ifndef _SCAN_H_
#define _SCAN_H_

#include <stdio.h>
#include "ami_function.h"

void yyiperror(const char*);
int yyiplex();

typedef unsigned int yy_size_t;

struct yy_buffer_state
	{
	FILE *yy_input_file;

	char *yy_ch_buf;		/* input buffer */
	char *yy_buf_pos;		/* current position in input buffer */

	/* Size of input buffer in bytes, not including room for EOB
	 * characters.
	 */
	yy_size_t yy_buf_size;

	/* Number of characters read into yy_ch_buf, not including EOB
	 * characters.
	 */
	int yy_n_chars;

	/* Whether we "own" the buffer - i.e., we know we created it,
	 * and can realloc() it to grow it, and should free() it to
	 * delete it.
	 */
	int yy_is_our_buffer;

	/* Whether this is an "interactive" input source; if so, and
	 * if we're using stdio for input, then we want to use getc()
	 * instead of fread(), to make sure we stop fetching input after
	 * each newline.
	 */
	int yy_is_interactive;

	/* Whether we're considered to be at the beginning of a line.
	 * If so, '^' rules will be active on the next match, otherwise
	 * not.
	 */
	int yy_at_bol;

	/* Whether to try to fill the input buffer when we reach the
	 * end of it.
	 */
	int yy_fill_buffer;

	int yy_buffer_status;
#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
	/* When an EOF's been seen but there's still some text to process
	 * then we mark the buffer as YY_EOF_PENDING, to indicate that we
	 * shouldn't try reading from the input source any more.  We might
	 * still have a bunch of tokens to match, though, because of
	 * possible backing-up.
	 *
	 * When we actually see the EOF, we change the status to "new"
	 * (via yyrestart()), so that the user can continue scanning by
	 * just pointing yyin at a new input file.
	 */
#define YY_BUFFER_EOF_PENDING 2
	};

typedef struct yy_buffer_state *YY_BUFFER_STATE;

#define yyconst const

YY_BUFFER_STATE yyip_scan_string( yyconst char *yy_str );
YY_BUFFER_STATE yyip_scan_buffer( char *base, yy_size_t size);

void yyip_delete_buffer  ( YY_BUFFER_STATE b );

YY_BUFFER_STATE yyip_create_buffer(FILE*,int);

void yyip_switch_to_buffer ( YY_BUFFER_STATE );
void yyip_load_buffer_state ( void );

#define YY_MAX_BUF 100

int  yyip_switch_to_file( const  char* );
void yyip_switch_to_string( const char*  );
void yyip_popup_buffer();
void yyip_reinit_current_buffer();
int yyip_parse();
int continue_parse();
void print_buf_info(YY_BUFFER_STATE b);

void yyip_switch_to_block( const AmiInstructionBlock_ptr& b );


extern int     yyiplineno;
extern string  GB_current_file;
extern char *yyiptext;
extern FILE *yyipin;

extern int               yy_num_buf;
extern YY_BUFFER_STATE   yy_buf_stack[YY_MAX_BUF];
extern int               yyERROR;
 
// YY_BUFFER_STATE yy_current_buffer = 0;

#define YY_CURRENT_BUFFER (yy_num_buf?yy_buf_stack[yy_num_buf-1]:fprintf(stderr,"YY_CURRENT_BUFFER \t empty stack \n"));

#define YY_BUFFER_NEW 0
#define YY_BUFFER_NORMAL 1
#define YY_BUFFER_EOF_PENDING 2

#define YY_BUF_SIZE 32000

// void set_input_file( char* );

#endif
