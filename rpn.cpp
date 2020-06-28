#include<stack>
#include<iostream>
using namespace std;

#define da 9
//优先级表
const char youxianji[da][da] = { //运算符优先等级 [栈顶] [当前]
    /*              |-------------------- 当 前 运 算 符 --------------------| */
    /*              +      -      *      /      ^      !      (      )      \0 */
    /* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
    /* 栈  * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 顶  / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
    /* 运  ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
    /* 算  ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
    /* 符  ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
    /* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
    /* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};

char *removespace(char *s)
{                       
    char*p=s,*q=s;
    while(true)
    {
        while(isspace(*q))
            q++;
        if('\0'==*q)
        {
            *p='\0';
            return s;
        }
        *p++=*q++;//p作输出字符串，q作对比字符串，遇空格则q自增，p就会跳过
    }
}


float cal(const char &s1,float s2)
{
    
    int sum=1;
    if((int)s2==0)
        return sum;
    while(s2>1)
    {
        sum=sum*s2;
        s2--;
    }
    return sum;
}

float cal(const float&num1,const char&op,float&num2)
{
    switch(op)
    {
        case '+':
            return  num1+num2;
        case '-' :
            return num1-num2;
        case '*':
            return num1*num2;
        case '/':
            return num1/num2;
        case '^':
            {
                if(num1==0)
                return 0;
                if(num2==0)
                return 1;
                int sum=1;
                while(num2--)
                    sum*=num1;
                return sum;
            } 
        default:
            return false;//这句话其实并不需要
    }
}
void readnumber(char * &a,stack<float>& s2 )
// 对指针的地址使用引用是为了能够在函数内修改指针地址，比如说在一个函数
// 内将一个原指针指向另一个新指针，但注意的是，即使我们不使用引用也能修改原指针指向的值
{
    s2.push(*a-48);

    while(isdigit(*(++a)))
    {
        float b=s2.top();
        s2.pop();
        s2.push(b*10+*a-48);
    }
    if('.'!=*a) return ;
    float fraction =1;//小数点部分
    while(isdigit(*(++a)))
    {
        float b=s2.top();
        s2.pop();
        s2.push(b+(*a-48)*(fraction/10));
    }
}


//9 +(8*(4-2)+3!)^2  - 12
float qiuzhi(char *a)
{
    stack<char> s1;// chaozuofu
    // stack<float> s2;// chaozuoshu
    // s1.push('\0');
    // float c,c1,c2;
    // char op;
    // while(!s1.empty())
    // {
    //     if(isdigit(*a))
    //     {
    //         readnumber(a,s2);//操作数大于一位的情况
            
    //     }
//         else 
//         switch(youxianji[3][4])
//         {
//             case '<':
//                 s1.push(*a);
//                 a++;
//                 break;
//             case '>':
//                 op=s1.top();
//                 s1.pop();
//                 if('!'==op)
//                 {
//                     c=s2.top();//switch 语句中不能定义变量，因为不能确定作用域
//                     s2.pop();          //修改方法
// //1、【缩小作用域】将case 1的代码用{ }括起来，设定清楚变量i的作用域，避免其他case访问
// //2、【扩大作用域】将变量i放到switch外部，switch中的每个case都可以访问
//                     s2.push(cal(op,c));
//                 }//单目操作符
//                 else
//                 {
//                     c1=s2.top();
//                     s2.pop();
//                     c2=s2.top();
//                     s2.pop();
//                     s2.push(cal(c2,op,c1));
//                 }//双目操作符
//                 break;
//             case '=':
//                 s1.pop();
//                 a++;
//                 break;//针对括号和\0字符
//             default:
//                 exit(-1);
//         }
    // }
    // float now=s2.top();
    // s2.pop();
    // return now;
}

int main()
{
    
    char a[30]="9 +(8*(4-2)+3!)^2  - 12";
    // cout<<removespace(a)<<endl;
    cout<<(qiuzhi(removespace(a)))<<endl;
    
    return 0;
}