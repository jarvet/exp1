#include <string.h>
#define maxn 100
//ջ��ģ���࣬ʵ����ջ�Ļ�������
template<class type>
class MyStack
{
public:

    MyStack()
    {
        top = -1;
    }

    //ѹջ
    void Push(type a)
    {
        if (top==maxn)
            printf("ջ���\n");
        else
        {
            top++;
            ch[top] = a;
        }
    }

    //��ջ
    void Pop()
    {
        if (IsEmpty())
            printf("ջ�ѿ�\n");
        else
            top--;
    }

    //��ȡջ��Ԫ��
    type GetTop()
    {
        return ch[top];
    }

    //�ж�ջ�Ƿ�Ϊ��
    bool IsEmpty()
    {
        return top < 0;
    }

private:
    type ch[maxn];//�洢ջ��Ԫ��
    int top;//ָ��ջ��
};
