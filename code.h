
#define	cmdstr_len	1024
//缓存区
char cmdstr[cmdstr_len];
word *tmp_list[cmdstr_len/4];
word **tmp_lp=tmp_list;


//STACK OPERATE 
void bye()	 {exit(0);}//结束程序
void push(){IP++;DP++;*DP=(cell)*IP;}
void dup(){DP++;*DP=*(DP-1);DEBUG("entering dup")}
void swap(){cell t=*DP; *DP=*(DP-1); *(DP-1)=t;}
void over(){*(DP+1)=*(DP-1);DP++;}
void drop(){DP--;}
//RS
void tor()	{RP++;*RP=*DP;DP--;}
void rto()	{DP++;*DP=*RP;RP--;}
void rat()	{DP++;*DP=*RP;}
//TS
void tot()	{TP++;*TP=*DP;DP--;}
void tto()	{DP++;*DP=*TP;TP--;}
void tat()	{DP++;*DP=*TP;}
//+-*/
void add(){ *(DP-1)=*(DP-1)+(*DP); DP--;}
void sub(){ *(DP-1)=*(DP-1)-(*DP); DP--;}
void mul(){ *(DP-1)=*(DP-1)*(*DP); DP--;}
void divv(){ *(DP-1)=*(DP-1)/(*DP); DP--;}



void words()
{	word*wtmp=dict_head;
	do
	{
		printf("%s ",wtmp->name);
	} while(wtmp=wtmp->next);
	printf("\n");		
}


void ret()	{IP=(word**)*RP;	RP--;DEBUG("entering ret")}
void dolist()
{
	RP++;
	*RP=(cell)IP;
	IP=(*IP)->wplist-1;
	DEBUG("entering dolist")
}




void showDS()
{
	printf("DS> ");
	for (int *i=DS;i<=DP ;i++ )
		printf("%d ",*i);
	printf("\n");
/*
	printf("tmplist> ");
	for (word **j=tmp_list;j<=tmp_lp ;j++ )
		printf("%d ",*j);
	printf("\n");
//*/
/*
	printf("RS> ");
	for (cell *k=RS;k<=RP ;k++ )
		printf("%d ",*k);
	printf("\n");
//*/
}



word * code(char*s, fnp  fp)
{
	
	word *w=(word*)malloc(sizeof(word));
	w->next=dict_head;
	dict_head=w;
	w->fn=fp;
	w->wplist=NULL;
	w->name=s;

	return w;
}

void colon(char*s)
{
	word *w=(word*)malloc(sizeof(word));
	w->next=dict_head;
	dict_head=w;
	w->fn=dolist;

	w->name=(char*)malloc(strlen(s)+1);
	strcpy(w->name,s);

	int n=(int)tmp_lp-(int)tmp_list;
	w->wplist=(word**)malloc(n);
	memcpy(w->wplist,tmp_list, n);
	
}
