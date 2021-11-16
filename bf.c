/**
 * bf
 * Copyright (C) 2021 Ted Johnson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>

static int tape[30000];
static int *tape_ptr = tape;

/* Return a pointer to the next ']', skipping subsequent [ ] loops */
char *bf_jmp(char *program_ptr) {
	while (*program_ptr != ']')
		if (*program_ptr++ == '[')
			program_ptr = bf_jmp(program_ptr);
	return program_ptr + 1;
}

/* Execute the brainfuck program */
void bf_run(char *program_ptr) {
	while (*program_ptr) {
		switch (*program_ptr++) {
			case '>': tape_ptr++; break;
			case '<': tape_ptr--; break;
			case '+': (*tape_ptr)++; break;
			case '-': (*tape_ptr)--; break;
			case '.': putchar(*tape_ptr); break;
			case ',': *tape_ptr = getchar(); break;
			case ']': return;
			case '[':
				while (*tape_ptr)
					bf_run(program_ptr);
				program_ptr = bf_jmp(program_ptr);
				break;
		}
	}
}

int main(int argc, char **argv) {
	if (argc == 2)
		bf_run(argv[1]);
	return 0;
}

/* Something of a code golf attempt (300 bytes) */
/*
#define a(b,c)case b:c;break;
char q[30000];*t=q;
*j(char*p){while(*p!=']')if(*p++=='[')p=j(p);return p+1;}
r(char*p){while(*p)switch(*p++){a('>',t++)a('<',t--)a('+',(*t)++)a('-',(*t)--)a('.',putchar(*t))a(',',*t=getchar())a(']',return)a('[',while(*t)r(p);p=j(p))}}
main(int c,char**v){if(c==2)r(v[1]);}
*/