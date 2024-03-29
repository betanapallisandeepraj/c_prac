#include <stdio.h>
#include <string.h>

#define SIZE 1024
void ffname(char *line)
{
    int i=1,j=0;
    char *dt; 
    char name[SIZE];
    strtok(line,"("); 
    dt = strchr(line,' '); 
    if(dt[i] == '*')
        i++;
    while(dt[i] != '\0')
    {
        name[j]=dt[i];
        i++;
        j++;
    }
    name[j] ='\0';
//    printf("Function name is: %s\n", name);
    printf("%s\n", name);
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        printf("Give the filename \n");
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }
    int i, lines =0, funlines =0,count =0, fn =0, flag =0;
    char c[SIZE],b[SIZE];
    FILE *fd;
    fd = fopen(argv[1],"r");
    while(fgets(c,SIZE,fd))
    {   
        lines++;
        i=0;
        for(i=0;i<strlen(c);i++)
        {
            while( c[i] =='\t' || c[i] == ' ')
            {
                i++;
            }
            if( c[i] == '{')
            {
                count++;
                if(flag)
                {
                    funlines++;
                }
                if(count == 1)
                {
                    fn++;
//                    printf("Function %d is Started..............\n", fn); 
                    flag = 1;
                    ffname(b);
                }
                break;
            }
            else if( c[i] == '}')
            {
                count--;
                if(!count)
                { 
                    flag = 0;
//                    printf("No of lines in the function %d is: %d\n", fn, funlines);
//                    printf("Function %d is finished..........\n", fn);
                    funlines = 0;
                }
                else
                {
                    funlines++;
                }
                break;
            }
            else if(flag)
            {
                funlines++;
                break;
            }
        }
        strcpy(b,c);
    }
//    printf("Total no of function%d\n",fn);
//    printf("Total no of lines%d\n",lines);
    return 0;
}
