#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	DEBUGER  CLOSE
#ifndef	DEBUGER 
#define	DEBUG(str)	printf("[DEBUG]%s\n",str);
#define	DEBUG2(str1,str2)	printf("[DEBUG]%s %s\n",str1,str2);
#else
#define	DEBUG(str)	
#define	DEBUG2(str1,str2)	
#endif 

#define	cell	int //long long	// to keep all the sizes same as cell
typedef void(*fnp)();//funcion pointer


#include "dict.h"
#include "str.h"
#include "code.h"

int search_word(char *w)
{
	word * dict=dict_head;
	while (strcmp(dict->name,w))
	{
		dict=dict->next;
		if(dict==NULL)
		{
			if (!is_num(w))	 return 0;

			*tmp_lp=pushh;	tmp_lp++;
			*tmp_lp=(word*)atoi(w);	tmp_lp++;

			return 1;			
		}
	}
	DEBUG2("success find: ",w)
	*tmp_lp=dict;	tmp_lp++;
	return 1;
}

void init()
{
	DP=DS-1;*DP=0;
	RP=RS-1;*RP=0;
	TP=TS-1;*TP=0;
	tmp_lp=tmp_list;
	DEBUG("INIT()")
//	DS[0]=123;DS[1]=456;DP=DS+2;
}

void explain()
{
	IP=tmp_list;
	
	while(IP != tmp_lp)
	{
		(*IP)->fn();
		++IP;
	}DEBUG("explaining")
}

void compile(char *s)
{
	s=ignore_blankchar( s);
	
	char *name=NULL;
	if (*s==':')
	{
		s++;
		name=ignore_blankchar(s);
		s=name;
		s=split_word(s);
	}

	char *w;
	while (*s!=0)
	{
		s=ignore_blankchar(s);
		w=s;
		s=split_word(s);

		if(!search_word(w) )
		{
			printf("\n[%s]?\n",w);
			init();
			return;
		}
	}
	*tmp_lp=0;

	if (name==NULL)
		explain();
	else
		colon(name);
	tmp_lp=tmp_list;//临时区初始化
}

void checkcmd(char*s)
{
	strcat(cmdstr," ;");
	s=ignore_blankchar(s);
	char c=*s;
	while ( *s!=';')
		s++;
	if (c==':') 
		s++;
	*s=0;
}

void main() 
{
	init();
	dict_head=NULL;
	

pushh=code("push",push);
	code("bye",bye);
	code("dup",dup);
	code("swap",swap);
	code("over",over);
	code("drop",drop);
	
	code(">r",tor);
	code("r>",rto);
	code("r@",rat);

	code(">t",tot);
	code("t>",tto);
	code("t@",tat);

	code("+",add);
	code("-",sub);
	code("*",mul);
	code("/",divv);


	code("words",words);

	code("ret",ret);
	code(";",ret);
	code("dolist",dolist);


	printf("ear-cforth version 0.2\nplease input 'words' to see the dictionary\n");
	while (1)
	{
		showDS();
		printf(">>>");	gets(cmdstr);
		checkcmd(cmdstr);
		compile(cmdstr);
	}
}

