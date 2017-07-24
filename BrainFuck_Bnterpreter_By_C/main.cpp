//2017��7��24��,����һ 23:41

#include <stdio.h>


/*"><+-,.[]"*/;//��Ŵ�������Դ��
char source[512] = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";


#define MEMORY_LIMIT 512
char memory[MEMORY_LIMIT] = { 0 };//�ṩ��BrainFuck�õ��ڴ�



struct jmpStack
{
    jmpStack()
    {
        pJmpMemory = nullptr;
        pJmpControl = nullptr;
    }
    char* pJmpMemory;//�ڴ�
    char* pJmpControl;//brainfuck code
};

#define STACK_LIMIT 256
jmpStack g_Stack[STACK_LIMIT];

int jmpStackTop = 0;



void lexer()
{

    char* p = nullptr;
    char* pMemory = nullptr;
    pMemory = memory;

    p = source;

    while (*p != '\0')
    {
        switch (*p)
        {
        case '>':
        {
            ++pMemory;
            if (pMemory >= memory + MEMORY_LIMIT)
            {
                throw("Memory not enough.");
            }
            break;
        }
        case '<':
        {
            --pMemory;
            if (pMemory<memory)
            {
                throw("The source is a error,it want to Break through the cage !");//��ͼ�������
            }
            break;
        }
        case '+':
        {
            ++(*pMemory);
            break;
        }
        case '-':
        {
            --(*pMemory);
            break;
        }
        case ',':
        {
            printf("Please input a char!\r\n");
            scanf_s("%c",pMemory,1);
            break;
        }
        case '.':
        {
            printf("%c ", *pMemory);
            break;
        }
        case '[':
        {
            g_Stack[jmpStackTop].pJmpControl = p;
            g_Stack[jmpStackTop].pJmpMemory = pMemory;

            ++jmpStackTop;

            break;
        }
        case ']':
        {
            if (jmpStackTop == 0)
            {
                throw("source error,lose a '['");
            }
            if (0 == *(g_Stack[jmpStackTop - 1].pJmpMemory))
            {
                --jmpStackTop;                        //��ջ
                break;
            }
            else
            {
                p = g_Stack[jmpStackTop -1].pJmpControl;//�޸�IP
            }


            break;
        }

        default:
        {
            break;
        }



        }//end swtich
        ++p;

    }//end while

}


/*

��д���̵������ν������BUG:                ����:
1. �����˼·����,����һ��-1			    ��ѭ��
2. �����˼·����,����һ��*ȡ����			��ѭ��
3. �����˼·����,����һ��*ȡ����			��ӡ�������

*/
#include <stdlib.h>

int main()
{

    lexer();

    system("pause");

    return 0;
}

