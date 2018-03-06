#include "../../plib_next.h"
#include "lib_pc.h"

#include <stdio.h>
#include <stdlib.h>

int io_state[100][100]={{0}}; //dangerous probably shuld put in def....todo

int f_pc_in_get(pin *self)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("in_get,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}


int f_pc_out_put( pin *self,int a)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    io_state[self->addr.PORT][self->addr.PIN]=a;
    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("out_put,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}
int f_pc_out_set( pin *self)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    io_state[self->addr.PORT][self->addr.PIN]=1;
    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("out_set,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}
int f_pc_out_reset( pin *self)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    io_state[self->addr.PORT][self->addr.PIN]=0;
    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("out_reset,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}
int f_pc_out_get( pin *self)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("out_get,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}
int f_pc_out_toggel( pin *self)
{
    if(self==0)
    {
        printf("error pin emty");
        return 0;
    }
    if(io_state[self->addr.PORT][self->addr.PIN]==1)
        io_state[self->addr.PORT][self->addr.PIN]=0;
    else
        io_state[self->addr.PORT][self->addr.PIN]=1;

    int state = io_state[self->addr.PORT][self->addr.PIN];
    printf("toggel_get,%c,%d : %d\n",self->addr.PORT,self->addr.PIN,state);
    return state;
}
