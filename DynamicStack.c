#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} stack;

stack *new_stack(int size) {
    stack *stk = (stack*)malloc(sizeof(stack));
    stk->array = (int*)malloc(size * sizeof(int));
    stk->size = size;
    stk->top = 0;
    return stk;
}

void push(stack *stk, int val) {
    if (stk->top == stk->size) {
        int size = stk->size *2;
        stk->size = size;
        int *copy = (int*)malloc(size*sizeof(int));
        for (int i = 0; i < stk->top; i++){
            copy[i] = stk->array[i];
        }
    free(stk->array);
    stk->array = copy;
    }
    stk->array[stk->top] = val;
    stk->top++;
}

int pop(stack *stk) {
    if (stk->top == 0) {
        return 0; 
    }
    stk->top -= 1;
    int val = stk->array[stk->top];
    return val;
}


int main() {
    stack *stk = new_stack(4);
    int n = 10;
    for(int i = 0; i < n; i++)
        push(stk, i+30);
    for(int i = 0; i < stk->top; i++)
        printf("stack[%d] : %d\n", i, stk->array[i]);
    int val = pop(stk);
    while(val != 0) {
        printf("pop : %d\n", val);
        val = pop(stk);
    }
}