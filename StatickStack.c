#include <stdlib.h>
#include <stdio.h>

typedef struct stack {
    int top;
    int size;
    int *array;
} 

    stack;
    stack *new_stack(int size) {
        stack *stk = (stack*)malloc(sizeof(stack));
        stk->array = (int*)malloc(size * sizeof(int));
        stk->size = size;
        stk->top = 0;
        return stk;
}

void push(stack *stk, int val) {
    stk->array[stk->top] = val;
    stk->top += 1;
}

int pop(stack *stk) {
    if (stk->top == 0) {
        printf("underflow");
        return 0;
    }
    stk->top -= 1;
    int val = stk->array[stk->top];
    return val;
}

int main() {
    stack *stk = new_stack(4);

    push(stk, 32);
    push(stk, 33);
    push(stk, 34);

    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));
    printf("pop : %d\n", pop(stk));

    return 0;
}