#ifndef BLSL_WRAPPER
#define BLSL_WARPPER

#include <stdio.h>
#include <stdlib.h>




FILE* blsl_in;
FILE* blsl_out;



typedef struct blsl_s1
{
	struct blsl_s2* val;
	struct blsl_s1* rest;
} blsl_stack;


typedef struct blsl_s2
{
	char c;
	int rep;
	struct 	blsl_s2* loop_back;
	struct blsl_s2* next;
} blsl_node;


int blsl_gen(char* src, char* out)
{
	char c;
	blsl_in  = fopen(src, "r");
	if (!blsl_in) return -1;
	blsl_out = fopen(out, "w");

	blsl_node* start = NULL;
	blsl_node* loc   = NULL;

	blsl_stack* stack = NULL;



	int acc = 0;
	while (1)
	{
		c = fgetc(blsl_in);

		switch (c)
		{
			case 'l':
			case 'j':
			case 'z':
			case 's':
			case 't':
			case 'i':
			case 'o':
			if (start == NULL)
			{
				start = malloc(sizeof(blsl_node*));
				loc = start;
				loc->c = c;
				loc->next = NULL;
			}
			else
			{
				loc->next = malloc(sizeof(blsl_node*));
				loc = loc->next;
				loc->c = c;
				loc->next = NULL;
			}
			break;

			case '<':
			if (start == NULL)
			{
				start = malloc(sizeof(blsl_node*));
				loc = start;
				loc->c = c;
				loc->next = NULL;
				loc->rep = acc - 1;
				//printf("DEBUG: %d\n", acc);
			}
			else
			{
				loc->next = malloc(sizeof(blsl_node*));
				loc = loc->next;
				loc->c = c;
				loc->next = NULL;
				loc->rep = acc - 1;
			}
			if (stack == NULL)
			{
				stack = malloc(sizeof(blsl_stack*));
				stack->val = loc;
				stack->rest = NULL;
			}
			else
			{
				blsl_stack* temp = malloc(sizeof(blsl_stack*));
				temp->rest = stack;
				temp->val  = loc;
				stack = temp;
			}

			break;

			case '>':
			if (stack == NULL)
			{
				while (start != NULL)
				{
					blsl_node* temp = start;
					start = start->next;
					free(temp);
				}


				return -2;
			}
			
			loc->next = malloc(sizeof(blsl_node*));
			loc = loc->next;
			loc->next = NULL;
			loc->c = c;
			loc->loop_back = stack->val;
			loc->rep = -1;
			blsl_stack* temp = stack->rest;
			free(stack);
			stack = temp;
			break;

			case '\\':;
			char v = fgetc(blsl_in);
			if (v == '+')
			{
				acc++;
				break;
			}
			if (v == '-')
			{
				acc--;
				break;
			}
			int __val = 0;
			int loop = 1;
			while (loop)
			{
				switch (v)
				{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					__val = __val*10 + v - 48;
					v = fgetc(blsl_in);
					break;
					default:
					loop = 0;
					ungetc(v, blsl_in);
					break;
				}
			}
			acc = __val;
			break;
		}
		if (c == EOF) break;
	}
	//printf("CHAIN MADE\n");
	//printf("%d\n", start);


	blsl_node* runner;
	/* 
	runner = start;
	while (runner != NULL)
	{
		printf("%d -> %c", runner, runner->c);
		if (runner->c == '<') printf(" -> %d", runner->rep);
		if (runner->c == '>') printf(" -> %d", runner->loop_back);
		printf("\n");
		runner = runner->next;
	}
	/* */
	//printf("\n\n\n");
	

	runner = start;
	while (runner != NULL)
	{
		c = runner->c;

		switch (c)
		{
			case 'l':
			case 'j':
			case 's':
			case 'z':
			case 'o':
			case 't':
			case 'i':
			fputc(c, blsl_out);
			//putchar(c); putchar('\n');
			runner = runner->next;
			break;

			case '<':
			runner = runner->next;
			break;

			case '>':
			//if (runner->loop_back->rep != 0) runner = runner->loop_back;
			//else runner = runner->next;
			if (runner->rep == -1) runner->rep = runner->loop_back->rep;
			if (runner->rep ==  0)
			{
				runner->rep = -1;
				runner = runner->next;
			}
			else
			{
				runner->rep--;
				runner = runner->loop_back;
			}
			break;
		}
	}


	while (start != NULL)
	{
		blsl_node* temp = start;
		start = start->next;
		free(temp);
	}


	fclose(blsl_out);
	fclose(blsl_in);
	return 1;
}














#endif
