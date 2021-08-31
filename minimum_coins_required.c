#include <stdio.h>
int min_coin_req(int *val, int val_count,int target);
int main()
{
    int val[3] = {25,10,5},val_count=3,target;//target[]={25,30,35,40,65};
    int min_coin,i;
    //tar_len=sizeof(target)/sizeof(int);
    //printf("%d\n",tar_len);
    //for(i=0;i<sizeof(target)/sizeof(int);i++) {
    for(i=1;i<=15;i++) {
        //min_coin=min_coin_req(&val[0],3,target[i]);
        min_coin=min_coin_req(&val[0],val_count,val[val_count-1]*i);
        printf("minimum coins required for target=%d are %d\n",val[val_count-1]*i,min_coin);
    }
    for(i=-2;i<=30;i++) {
        min_coin=min_coin_req(&val[0],val_count,i);
        printf("minimum coins required for target=%d are %d\n",i,min_coin);
    }
    return 0;
}
int min_coin_req(int *val, int val_count,int target)
{
    int i,min_coin=0;
    for(i=0;i<val_count;) {
        if(target%val[i]==0) {
            min_coin+=target/val[i];
            break;
        } else {
            min_coin+=target/val[i];
            target%=val[i];
            i++;
        }
    }
    return min_coin;
}
