#include<stdio.h>
#include <cctype>
#include <conio.h>
#include <cstring>

int main()
{
    int np,i,j,k,temp;
    char prods[10][10],follow[10][10],Imad[10][10],f;
    printf("enter no. of productions\n");
    scanf("%d",&np);
    printf("enter grammar\n");
    for(i=0;i<np;i++)
    {
        scanf("%s",&prods[i]);
    }
    for(i=0; i<np; i++)
    {
        if(i==0)
        {
            printf("Follow(%c) = $\n",prods[0][0]);//Rule1
        }
        for(j=3;prods[i][j]!='\0';j++)
        {
            int temp2=j;

            //Rule-2: production A->xBb then everything in first(b) is in follow(B)
            if(prods[i][j] >= 'A' && prods[i][j] <= 'Z')
            {
                if((strlen(prods[i])-1)==j)
                {
                    printf("Follow(%c)=Follow(%c)\n",prods[i][j],prods[i][0]);
                }
                temp=i;
                f=prods[i][j];
                if(!isupper(prods[i][j+1])&&(prods[i][j+1]!='\0'))
                    printf("Follow(%c)=%c\n",f,prods[i][j+1]);
                if(isupper(prods[i][j+1]))
                {
                    for(k=0;k<np;k++)
                    {
                        if(prods[k][0]==prods[i][j+1])
                        {
                            if(!isupper(prods[k][3]))
                                repeat:
                                {
                                    printf("Follow(%c)=%c\n",f,prods[k][3]);
                                }
                            else
                            {
                                i=k;
                                j=2;
                                goto repeat;
                            }
                        }}}
                i=temp;
            }
            j=temp2;
        }
    }
    getch();
}
