#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
struct st_stack;
typedef struct st_stack{
    int overflow;
    int underflow;
    int pointer;
    int current_size;
    int *data;
    void (*push)(int,struct st_stack *working);
    int (*pop)(struct st_stack *working);
    int (*peek)(struct st_stack *working);
}st_stack;
typedef struct st_stack stack;

void fun_push(int item,struct st_stack *working)
{
    /*
    The current pointer points at the current index.
    if the index is -1, then we need to malloc.
    if the index is >-1, then we need to realloc
    if the current size is greater than the pointer than just assign
    */
    if(working->data == (void*)0)
    {
        working->current_size = 1;
        working->data = (int*)malloc(sizeof(int)*1);
        working->pointer = 0;
        
    }
    else if(working->pointer>= working->current_size)
    {
        working->current_size *= 2;
        working->data = (int*)realloc(working->data,sizeof(int)*working->current_size);
    }
    else
    {
        /* Do Nothing */
    }
    working->underflow = 0;
    working->data[working->pointer] = item;
    working->pointer++;
}

int fun_pop(struct st_stack *working)
{   
    /*
    The pop mechanism should pop the values from top if there is no overflow
    in the else case if the pointer is already at -1 then set the underflow flag. Then return -1 in the case of the 
    */
    int return_value = 0;
    if((working->underflow != 1) && (working->pointer >0))
    {
        return_value = working->data[--working->pointer];
    }
    else
    {
        return_value = -1;
        /*
        This is the place where we handle the area where we have the under-flow condition.if not done is also fine. Biut just in case for the sake of the conept.
        */
        if(working->pointer==0)
        {
            working->underflow = 1;
        }
    }
    return return_value;
}

int fun_peek(struct st_stack *working)
{
    /* 
    Peek and give the value on the top of the data array, must have thought why 0?? why not -1 because when we initialize the structure
    in the beginning it just makes poitner set to 0.
    */
    int return_value = 0;
    if(working->pointer != 0)
    {   
        return_value = working->data[working->pointer-1];
    }
    else
    {
        return_value = -1;
    }
    return return_value;
}
int main(){
    stack *stack1 = (stack*)malloc(sizeof(stack));
    stack1->push = &fun_push;
    stack1->pop = &fun_pop;
    stack1->peek = &fun_peek;
    stack1->data = (void*)0; /* keep the data null initially */

    stack1->push(69,stack1);
    stack1->push(72,stack1);
    stack1->push(108,stack1);
    
    printf(" %d\n",stack1->peek(stack1));
    (void)stack1->pop(stack1);
    printf(" %d\n",stack1->peek(stack1));
    (void)stack1->pop(stack1);
    printf(" %d\n",stack1->peek(stack1));
    

    return 0;
}