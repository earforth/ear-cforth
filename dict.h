struct _word
{
	struct _word *next; 
	char *name;
	fnp fn;
	struct _word **wplist;//word类型指针数组(指针的指针)
};
typedef struct _word word;

word *dict_head, *pushh;


#define	STACK_LEN	100
 cell DS[STACK_LEN], RS[STACK_LEN], TS[10];//(data return temp)stack
 cell *DP, *RP, *TP;//stack pointer
 word  **IP;//word类型指针数组(指针的指针)

