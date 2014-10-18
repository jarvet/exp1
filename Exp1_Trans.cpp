#include <stdio.h>
#include <stdlib.h>
#include "MyStack.h"
//???中缀表达式:9+8*7+(6+5)*(-(4-1*2+3))
//???其后缀表达式为:9 8 7 * + 6 5 + 4 1 2 * - 3 + 負號 * +

char infix[maxn];//中缀
char postfix[maxn*2];//后缀

//判断是否是数字或小数点
bool IsNum(char a)
{
    if ((a>='0' && a<='9') || a == '.')
        return 1;
    else
        return 0;
}

//获取优先级。
int pri(char a)
{
    //+、-优先级为1，*、/、%为2，（、）为3
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

//中缀转后缀
void InfixToPostfix()
{
    MyStack<char> stk;
    int l=strlen(infix);

    for (int i=0; i<l; i++)
    {
        if (IsNum(infix[i])|| (infix[i]=='-' && infix[i-1] == '('))//是数字或负号，则输出到后缀表达式数组
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
                //若栈顶运算符优先级高于当前运算符，则将栈内运算符弹出
                while ( !stk.IsEmpty() && stk.GetTop()!='(' && pri(infix[i]) <= pri(stk.GetTop()) )
                {
                    sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
                    stk.Pop();
                }

                stk.Push(infix[i]);//将当前运算符压栈
                if (strlen(postfix)>0)
                    sprintf(postfix+strlen(postfix)," ");
                break;

            case ')':
                //将（前的运算符全部弹出
                while ( !stk.IsEmpty() && stk.GetTop()!='(')
                {
                    sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
                    stk.Pop();
                }
                stk.Pop();//弹出（
                break;
            }
        }
    }
    //将栈排空
    while (!stk.IsEmpty())
        if (stk.GetTop()!='(')
        {
            sprintf(postfix+strlen(postfix)," %c",stk.GetTop());
            stk.Pop();
        }
}

//计算后缀表达式的值
float Calculate()
{
    MyStack<float> stk;
    int l = strlen(postfix);
    float op1,op2,ans,tt = 0;

    for (int i=0,j=0; i<l; i++)
    {
        if (postfix[i]==' ' && IsNum(postfix[i-1]))//发现完整的操作数j到i，将操作数由字符串转为数字
        {
            sscanf(postfix+j,"%f",&tt);
            stk.Push(tt);
            j = i + 1;
        }
        else if (!IsNum(postfix[i+1]) &&
                 (postfix[i]=='+'||postfix[i]=='-'||
                  postfix[i]=='*'||postfix[i]=='/'||
                  postfix[i]=='%'))//发现运算符，弹出栈顶的两个元素进行运算再压栈
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
    //输入中缀表达式，在两端加括号，此时所有负号前均为(，而减号前不可能为(，以此区分
    printf("请输入中缀表达式：");
    infix[0]='(';
    scanf("%s",infix+1);
    sprintf(infix+strlen(infix),")");

    InfixToPostfix();

    printf("后缀表达式为；%s\n",postfix);
    float ans = Calculate();
    printf("运算结果为：%.2f\n",ans);

    return 0;
}
