#include <stdio.h>
#include <stdlib.h>
#include "MyStack.h"
//???��׺���ʽ:9+8*7+(6+5)*(-(4-1*2+3))
//???���׺���ʽΪ:9 8 7 * + 6 5 + 4 1 2 * - 3 + ̖ؓ * +

char infix[maxn];//��׺
char postfix[maxn*2];//��׺

//�ж��Ƿ������ֻ�С����
bool IsNum(char a)
{
    if ((a>='0' && a<='9') || a == '.')
        return 1;
    else
        return 0;
}

//��ȡ���ȼ���
int pri(char a)
{
    //+��-���ȼ�Ϊ1��*��/��%Ϊ2��������Ϊ3
    switch (a)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '(':
    case ')':
        return 3;
    default:
        return 0;
    }
}

//��׺ת��׺
void InfixToPostfix()
{
    MyStack<char> stk;
    int l=strlen(infix);

    for (int i=0; i<l; i++)
    {
        if (IsNum(infix[i])|| (infix[i]=='-' && infix[i-1] == '('))//�����ֻ򸺺ţ����������׺���ʽ����
        {
            sprintf(postfix+strlen(postfix),"%c",infix[i]);
        }
        else
        {
            switch (infix[i])
            {
            case '+':
            case '-':
            case '%':
            case '*':
            case '/':
            case '(':
                //��ջ����������ȼ����ڵ�ǰ���������ջ�����������
                while ( !stk.IsEmpty() && stk.GetTop()!='(' && pri(infix[i]) <= pri(stk.GetTop()) )
                {
                    sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
                    stk.Pop();
                }

                stk.Push(infix[i]);//����ǰ�����ѹջ
                if (strlen(postfix)>0)
                    sprintf(postfix+strlen(postfix)," ");
                break;

            case ')':
                //����ǰ�������ȫ������
                while ( !stk.IsEmpty() && stk.GetTop()!='(')
                {
                    sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
                    stk.Pop();
                }
                stk.Pop();//������
                break;
            }
        }
    }
    //��ջ�ſ�
    while (!stk.IsEmpty())
        if (stk.GetTop()!='(')
        {
            sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
            stk.Pop();
        }
}

//�����׺���ʽ��ֵ
float Calculate()
{
    MyStack<float> stk;
    int l = strlen(postfix);
    float op1,op2,ans,tt = 0;

    for (int i=0,j=0; i<l; i++)
    {
        if (postfix[i]==' ' && IsNum(postfix[i-1]))//���������Ĳ�����j��i�������������ַ���תΪ����
        {
            sscanf(postfix+j,"%f",&tt);
            stk.Push(tt);
            j = i + 1;
        }
        else if (!IsNum(postfix[i+1]) &&
                 (postfix[i]=='+'||postfix[i]=='-'||
                  postfix[i]=='*'||postfix[i]=='/'||
                  postfix[i]=='%'))//���������������ջ��������Ԫ�ؽ���������ѹջ
        {
            op1 = stk.GetTop();
            stk.Pop();
            op2 = stk.GetTop();
            stk.Pop();
            switch (postfix[i])
            {
            case '+':
                ans = op1 + op2;
                break;
            case '-':
                ans = op2 - op1;
                break;
            case '*':
                ans = op1 * op2;
                break;
            case '/':
                ans = op2 / op1;
                break;
            case '%':
                ans = int(op2) % int(op1);
                break;
            default:
                break;
            }
            stk.Push(ans);
            j = i + 1;
        }

    }
    return ans;
}

int main()
{
    //������׺���ʽ�������˼����ţ���ʱ���и���ǰ��Ϊ(��������ǰ������Ϊ(���Դ�����
    printf("��������׺���ʽ��");
    infix[0]='(';
    scanf("%s",infix+1);
    sprintf(infix+strlen(infix),")");

    InfixToPostfix();

    printf("��׺���ʽΪ��%s\n",postfix);
    float ans = Calculate();
    printf("������Ϊ��%.2f\n",ans);

    return 0;
}
