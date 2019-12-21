#include <ctype.h>
#include <stdio.h>
#include <string>
using namespace std;

char s[50];
int top = -1;

void push(char elem)
{
    s[++top] = elem;
}

char pop()
{
    return (s[top--]);
}

int pr(char elem)
{
    switch (elem)
    {
        case '#':
            return 0;
        case '(':
            return 1;
        case '+':
        case '-':
            return 2;
        case '*':
        case '/':
            return 3;
    }
}

void reverseChar(char* str, int len)
{
    for(int i=0; i<len/2; i++)
    {
        char temp=str[i];
        str[i]=str[len-i-1];
        str[len-i-1]=temp;
    }
}

int main()
{
    char infx[50], pofx[50], prefx[50], ch, elem;
    bool flag = false;
    int check = 0;
    int i = 0, k = 0;

    printf("\n\nRead the Infix Expression ? ");
    scanf("%s", infx);
    printf("\n\nPress 1 for prefix and 2 for postfix (default postfix) ? ");
    scanf("%d", &check);

    switch(check)
    {
        case 1:
            flag = true;
            break;
        default:
            flag = false;
            break;
    }

    if(flag){
        reverseChar(infx, strlen(infx));
    }
    push('#');
    while ((ch = infx[i++]) != '\0')
    {
        if (ch == '(')
            push(ch);
        else if (isalnum(ch)) pofx[k++] = ch;
        else if (ch == ')')
        {
            while (s[top] != '(')
            {
                pofx[k++] = pop();
            }
            elem = pop();
        }
        else
        {
            while (pr(s[top]) >= pr(ch))
            {
                pofx[k++] = pop();
            }
            push(ch);
        }
    }
    while (s[top] != '#')
    {
        pofx[k++] = pop();
    }

    pofx[k] = '\0';
    if(flag){
        reverseChar(pofx, strlen(pofx));
        printf("\n\nGiven Infix Expression: %s Prefix Expression: %s\n", infx, pofx);

    }else{
        printf("\n\nGiven Infix Expression: %s Postfix Expression: %s\n", infx, pofx);
    }
}