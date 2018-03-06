#ifdef ATMEAGAXXX
#ifndef LIB_PC_H_INCLUDED
#define LIB_PC_H_INCLUDED

int f_pc_in_get(pin *self);

int f_pc_out_put(pin *self, int a);
int f_pc_out_set(pin *self);
int f_pc_out_reset(pin *self);
int f_pc_out_get(pin *self);
int f_pc_out_toggel(pin *self);


#endif // LIB_PC_H_INCLUDED
#endif