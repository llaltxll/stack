#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 2
#define INIT_ELEMS 1024

typedef struct  {
	int size;
	int* arr;
	int used;
}stack ;

stack *alloc_stack(stack *s, int size)
{
	s = (stack*)malloc(sizeof(stack));
	if (s == NULL)
	{
		printf("malloc1");
		exit(0);
	}
	s->arr = (int*)malloc(sizeof(int) * size);
	if (s->arr == NULL)
	{
		printf("malloc2");
		exit(0);
	}
	s->size = size;
	s->used = 0;
	return s;
}
void resize_stack(stack* s, int new_size)
{
	int* tmp;
	tmp = (int*)realloc(s->arr,sizeof(int) * new_size);
	if (s->arr == NULL)
	{
		printf("realloc");
		exit(0);
	}
	s->arr = tmp;
	s->size = new_size;
}
void print_stack(stack* s)
{
	int i;
	char separator = ' ';
	printf("{");
	for (i = 0;i < s->used; i++)
	{
		printf("%c%d ", separator, s->arr[i]);
		separator = ',';
	}
	printf("}\n");
}
void push_stack(stack* s, int element)
{
	if (s->used == s->size)
		resize_stack(s, s->size * 2);
	s->arr[s->used] = element;
	s->used++;
}
int pop_stack(stack* s)
{
	int ret = s->arr[s->used - 1];
	s->used--;
	if (s->used && s->size / s->used > 1)
		resize_stack(s, s->size / 2);
	return ret;
}
int main()
{
	int i,j;
	stack *my_stack = NULL;
	my_stack = (stack*)alloc_stack(my_stack, INIT_SIZE);
	//print_stack(my_stack);
	for (i = 0; i < INIT_ELEMS; i++)
		push_stack(my_stack, i + 1);
	print_stack(my_stack);
	while (my_stack->used)
		printf("%d\n", pop_stack(my_stack));
	print_stack(my_stack);

	free(my_stack->arr);
	free(my_stack);
	return 0;
}