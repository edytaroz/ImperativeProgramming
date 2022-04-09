#include <stdio.h>
#include <math.h> // for NAN

#define STACK_SIZE 10

#define OK        0
#define EMPTY    -1
#define FULL     -2
#define OVERFLOW -3

double stack[STACK_SIZE];
int top = 0;

int stack_push(double x)
{
    if (top==STACK_SIZE)
    {
        return OVERFLOW;
    }
    else
    {
        stack[top] = x;
        top += 1;
        return OK;
    }
}

double stack_pop(void)
{
    if (top == EMPTY)
    {
        return NAN;
    }
    else
    {
        double tmp = stack[top-1];
        stack[top-1] = 0;
        top -=1;
        printf("%lf",tmp);
    }
}

int stack_state(void)
{
    if (top == STACK_SIZE)
    {
        return FULL;
    }
    else
    {
        return (top);
    }
}

// FIFO queue with shifts

#define QUEUE_SIZE 10

int queue[QUEUE_SIZE];
int in = 0, curr_nr = 0;

// ONE OVERFLOW for many resigning

void queue_push(int in_nr)
{
    if (in_nr + in > QUEUE_SIZE)
    {
        printf("OVERFLOW");
        for (int i = 0; i < in_nr; ++i)
        {
            if (in < QUEUE_SIZE)
            {
                curr_nr += 1;
                queue[in] = curr_nr;
                in += 1;
            }
            else
            {
                curr_nr += 1;
            }
        }
    }
    else
    {
        for (int i = 0; i < in_nr; ++i)
        {
            curr_nr += 1;
            queue[in] = curr_nr;
            in += 1;
        }
    }
}

void queue_pop(int out_nr)
{
    if (out_nr > in)
    {
        printf("UNDERFLOW");
        for (int i = 0; i < in; ++i)
        {
            queue[i] = 0;
            in -= 1;
        }
    }
    else
    {
        for (int i = 0; i < out_nr; ++i)
        {
            queue[i] = 0;
            in -= 1;
        }
        for (int i = 0; i < in; ++i)
        {
            queue[i] = queue[out_nr+i];
            queue[out_nr+i] = 0;
        }
    }
}

void queue_state(void)
{
    if (in == 0)
    {
        printf("EMPTY");
    }
    else
    {
        for (int i = 0; i < in; ++i)
        {
            printf("%d",queue[i]);
        }
    }
}

// Queue with cyclic buffer

#define CBUFF_SIZE 10

int cbuff[CBUFF_SIZE];
int out=0, len=0;


void cbuff_push(int cli_nr)
{
    if (len == CBUFF_SIZE)
    {
        printf("OVERFLOW");
    }
    else
    {
        len += 1;
        if (len + out > CBUFF_SIZE)
        {
            cbuff[len + out - CBUFF_SIZE] = cli_nr;
        }
        else
        {
            cbuff[len + out] = cli_nr;
        }
    }
}

void cbuff_pop(void)
{
    if (len == 0)
    {
        printf("UNDERFLOW");
    }
    else
    {
        cbuff[out] = 0;
        len -= 1;
        if (out == CBUFF_SIZE)
        {
            out = 0;
        }
        else
        {
            out += 1;
        }
    }
}

void cbuff_state(void)
{
    if (len == 0)
    {
        printf("EMPTY");
    }
    else
    {
        int curr = out;
        for (int i = 0; i < len; ++i)
        {
            curr = out + i + 1;
            if (curr > CBUFF_SIZE)
            {
                curr = curr - CBUFF_SIZE;
            }
            printf("%d",cbuff[curr]);

        }
    }
}

int main(void) {
    int to_do, n, client_no, op_code;
    double x;
    scanf("%d",&to_do);
    switch(to_do) {
        case 1: // stack
            do {
                scanf("%lf",&x);
                if(x > 0) stack_push(x);
                else {
                    if(x < 0) printf("%.2f ", stack_pop());
                    else printf("\n%d\n", stack_state());
                }
            } while(x != 0);
            break;
        case 2: // FIFO queue with shifts
            do {
                scanf("%d",&n);
                if(n > 0) queue_push(n);
                else {
                    if(n < 0) queue_pop(-n);
                    else queue_state();
                }
            } while(n != 0);
            break;
        case 3: // queue with cyclic buffer
            client_no = 0;
            do {
                scanf("%d",&op_code);
                if(op_code > 0) cbuff_push(++client_no);
                else {
                    if(op_code < 0) cbuff_pop();
                    else cbuff_state();
                }
            } while(op_code != 0);
            break;
        default:
            printf("NOTHING TO DO!\n");
    }
    return 0;
}
