#ifndef BIT_MATH_H
#define BIT_MATH_H
#define SET_BIT(REG,BIT_NO) (REG=REG|(1<<BIT_NO))
#define CLEAR_BIT(REG,BIT_NO) (REG=REG&(~(1<<BIT_NO)))
#define TOGGLE_BIT(REG,BIT_NO) (REG=REG^(1<<BIT_NO))
#define GET_BIT(REG,BIT_NO) ((REG>>BIT_NO)&1)
#endif