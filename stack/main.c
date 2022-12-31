#include <stdio.h>
#include <stdlib.h>

#define INIT_SIZE 2
/* tested up to 132000000 on ryzen 9 with 32GB  direct input required */
#define INIT_ELEMS 1024 

typedef struct  {
	size_t size;
	size_t* arr;
	size_t used;
}stack ;

stack* alloc_stack(stack* s, size_t size);
void resize_stack(stack* s, size_t new_size);
void print_stack(stack* s);
void push_stack(stack* s, size_t element);
size_t pop_stack(stack* s);

int main()
{
	size_t i;
	stack *my_stack = NULL;
	my_stack = (stack*)alloc_stack(my_stack, INIT_SIZE);
	print_stack(my_stack);
	for (i = 0; i < INIT_ELEMS; i++)
		push_stack(my_stack, i + 1);
	print_stack(my_stack);
	while (my_stack->used)
		printf("%d\n", pop_stack(my_stack));
	print_stack(my_stack);

	free(my_stack->arr);
	free(my_stack);
	/* according to the ISO manual nothing should happen if ptr is NULL */
	return 0;
}

stack* alloc_stack(stack* s, size_t size)
{
	s = (stack*)malloc(sizeof(stack));
	if (s == NULL)
	{
		printf("malloc1");
		exit(0);
	}
	s->arr = (size_t*)malloc(sizeof(size_t) * size);
	if (s->arr == NULL)
	{
		printf("malloc2");
		exit(0);
	}
	s->size = size;
	s->used = 0;
	return s;
}
void resize_stack(stack* s, size_t new_size)
{
	size_t* tmp;
	tmp = (size_t*)realloc(s->arr, sizeof(size_t) * new_size);
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
	size_t i;
	char separator = ' ';
	printf("{");
	for (i = 0; i < s->used; i++)
	{
		printf("%c%ld ", separator, s->arr[i]);
		separator = ',';
	}
	printf("}\n");
}
void push_stack(stack* s, size_t element)
{
	if (s->used == s->size)
		resize_stack(s, s->size * 2);
	s->arr[s->used] = element;
	s->used++;
}
size_t pop_stack(stack* s)
{
	int ret = s->arr[s->used - 1];
	s->used--;
	if (s->used && s->size / s->used > 1)
		resize_stack(s, s->size / 2);
	return ret;
}