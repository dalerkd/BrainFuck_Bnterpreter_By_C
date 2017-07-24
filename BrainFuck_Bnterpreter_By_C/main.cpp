//2017年7月24日,星期一 23:41

#include <stdio.h>


/*"><+-,.[]"*/;//存放待分析的源码
char source[512] = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";


#define MEMORY_LIMIT 512
char memory[MEMORY_LIMIT] = { 0 };//提供给BrainFuck用的内存



struct jmpStack
{
    jmpStack()
    {
        pJmpMemory = nullptr;
        pJmpControl = nullptr;
    }
    char* pJmpMemory;//内存
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
                throw("The source is a error,it want to Break through the cage !");//试图冲出牢笼
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
                --jmpStackTop;                        //退栈
                break;
            }
            else
            {
                p = g_Stack[jmpStackTop -1].pJmpControl;//修改IP
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

书写过程调试三次解决三个BUG:                现象:
1. 和设计思路不符,遗忘一个-1			    死循环
2. 和设计思路不符,遗忘一个*取内容			死循环
3. 和设计思路不符,遗忘一个*取内容			打印结果错误

*/
#include <stdlib.h>

int main()
{

    lexer();

    system("pause");

    return 0;
}

