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

/* Return zero if brainfuck program is valid (parentheses are balanced) */
static int bf_bal(char *program) {
	int balance = 0;
	while (*program) {
		switch (*program++) {
			case '[': balance++; break;
			case ']': balance--; break;
		}
	}
	return balance;
}

/* Given a pointer to after a '[', returns pointer to after corresponding ']' */
static char *bf_jmp(char *program_ptr) {
	while (*program_ptr != ']')
		if (*program_ptr++ == '[')
			program_ptr = bf_jmp(program_ptr);
	return program_ptr + 1;
}

/* Execute brainfuck program and return the new tape pointer */
static int *bf_run(char *program_ptr, int *tape_ptr) {
	while (*program_ptr && *program_ptr != ']') {
		switch (*program_ptr++) {
			case '>': tape_ptr++; break;
			case '<': tape_ptr--; break;
			case '+': (*tape_ptr)++; break;
			case '-': (*tape_ptr)--; break;
			case '.': putchar(*tape_ptr); break;
			case ',': *tape_ptr = getchar(); break;
			case '[':
				while (*tape_ptr)
					tape_ptr = bf_run(program_ptr, tape_ptr);
				program_ptr = bf_jmp(program_ptr);
				break;
		}
	}
	return tape_ptr;
}

int main(int argc, char **argv) {
	if (argc != 2 || bf_bal(argv[1]))
		return 1;
	int tape[30000] = {0};
	bf_run(argv[1], tape);
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
