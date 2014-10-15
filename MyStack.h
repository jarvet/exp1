#include <string.h>
#define maxn 100
//栈的模板类，实现了栈的基本功能
template<class type>
class MyStack
{
public:

    MyStack()
    {
        top = -1;
    }

    //压栈
    void Push(type a)
    {
        if (top==maxn)
            printf("栈溢出\n");
        else
        {
            top++;
            ch[top] = a;
        }
    }

    //退栈
    void Pop()
    {
        if (IsEmpty())
            printf("栈已空\n");
        else
            top--;
    }

    //获取栈顶元素
    type GetTop()
    {
        return ch[top];
    }

    //判断栈是否为空
    bool IsEmpty()
    {
        return top < 0;
    }

private:
    type ch[maxn];//存储栈内元素
    int top;//指向栈顶
};
