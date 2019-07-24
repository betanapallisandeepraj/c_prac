#include<stdio.h>
#include<math.h>
#include<stdlib.h>
typedef struct Node{
	unsigned int data;
	struct Node *next;
}node;

int prime(unsigned int n,node *temp);
void save_prime(unsigned int i,node **temp);
void display_prime(node *temp);
node *create_node(unsigned int i);
unsigned int get_next_prime(node *temp);

int main()
{
	unsigned int i,j;
	node *start=NULL;
	for(i=2,j=1;i<100;i++)
	{
		if(!prime(i,start)){
			printf("prime_number_%02u:%02u\n",j,i);
			j++;
			save_prime(i,&start);
//			display_prime(start);
		}
	}
//	display_prime(start);
	return 0;
}
int prime(unsigned int n,node *temp)
{
	int c=0;
	unsigned int i,sqr;
	sqr=(unsigned int)sqrt(n);
	for(i=2;(i<=sqr)&&(i);(i=get_next_prime(temp)),(temp=temp->next))
	{
//		printf("dividing %u with prime number with %u\n",n,i);
		if(!(n%i))
		{
			c++;
			break;
		}
	}
	if(c>0)
		return -1;
	return 0;
}
unsigned int get_next_prime(node *temp)
{
	if(temp==NULL)
		return 0;
	return temp->next->data;	
}
void save_prime(unsigned int i,node **temp)
{
	node *start=*temp,*temp1,*temp2;	
	if(start==NULL)
	{
		start=(node *)create_node(i);
		*temp=start;
	}
	else
	{
		temp1=(node *)create_node(i);
		temp2=start;
		while(temp2->next!=NULL)
			temp2=temp2->next;
		temp2->next=temp1;
	}
}
void display_prime(node *temp)
{
	unsigned int i=1;
	if(temp==NULL)
	{
		printf("No node to display prime number\n");
		return;
	}
	do
	{
		printf("prime_number%u:%u\n",i,temp->data);
		i++;
		temp=temp->next;
	}
	while(temp!=NULL);
}
node *create_node(unsigned int i)
{
	node *temp;
	temp=(node *)malloc(sizeof(node));
	if(temp==NULL)
	{
		printf("Memory not available to save prime number %u\n",i);
		exit(0);
	}
	else
	{
		temp->data=i;
		temp->next=NULL;
		return temp;
	}
}

