
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <stack>

using namespace std;

stack<unsigned char> brackets;
stack<unsigned char> operators;

void print(char a[],int len){
	int i,j;
	for (i=0;i<len&&a[i]!=' ';i++);
	if (i<len)
	{
		j=i;
		for (;i<len;i++){
			if (a[i]!=' ')
			{
				a[j++]=a[i];
			}
		}
		a[j]=0;
	}
	cout<<a<<endl;
}

void remove_brackets(char a[],int left,int right)
{
    a[left]=' ';
    a[right]=' ';
}

int is_operand(char a)
{
    return a!='+'&&a!='-'&&a!='*'&&a!='/'&&a!='('&&a!=')'&&a!=0;
}

int operators_compare(char a,char b)
{
    int a_pri,b_pri;
    
    a_pri=(a=='+'||a=='-')?1:2;
    b_pri=(b=='+'||b=='-')?1:2;
    
    return a_pri-b_pri;
}

int operators_check(char left,char right,char cur)
{
    int left_pri,right_pri,cur_pri;
    
    left_pri=(left=='+'||left=='-'||left=='('||left==0)?1:2;
    right_pri=(right=='+'||right=='-'||right==')'||right==0)?1:2;
    cur_pri=(cur=='+'||cur=='-')?1:2;
    
    if (cur_pri>=right_pri) {
        if (cur_pri>left_pri) {
            return 1;
        } else if (cur_pri==left_pri&&left!='-'&&left!='/') {
            return 1;
        }
    }
    return 0;
}

int main()
{
    char a[512];
    int i,j;
    int t;
    int len;
    int p_right,p_left,p_opt;
    char cur;
    char inner_opt,left_opt,right_opt;
    int num;
    
	cin>>num;
    
    for (j=0; j<num; j++) {
        cin>>a;
        
        for (i=0,len=strlen(a); i<=len; i++) {
            cur=a[i];
            
            if (is_operand(cur)) {
                continue;
            }
            
            if(!brackets.empty()) {
                t=brackets.top();
                if (a[t]==')') {//found ')' on the stack top, now we can check...
                    p_right=t;//the position of right bracket
                    brackets.pop();
                    p_left=brackets.top();//the location of left bracket
                    brackets.pop();
                    if (operators.empty()) {
                        //there is no operators between (), which means we can remove ()
                        remove_brackets(a,p_left,p_right);
                        goto push_char;
                    }
                    p_opt=operators.top();//the location of the operator between ()
                    if (p_opt<p_left) {//if the operator is not between ()
                        //there is no operators between (), which means we can remove ()
                        remove_brackets(a,p_left,p_right);
                        goto push_char;
                    }
                    operators.pop();
                    inner_opt=a[p_opt];//the operator between ()
                    left_opt=p_left>0?a[p_left-1]:0;//the operator before (
                    right_opt=cur;//the operator after )
                    if(operators_check(left_opt,right_opt,inner_opt)>0) {
                        remove_brackets(a,p_left,p_right);
						if (left_opt=='('&&right_opt==')')
						{
							operators.push(p_opt);
						}
                    }
                }
            }
        push_char:
            if (cur=='('||cur==')') {//push brackets
                brackets.push(i);
            } else if(cur>0){//push operators
                if (operators.empty()) {
                    goto push_operator;
                }
                p_left=brackets.empty()?0:brackets.top();//the location of (
                p_opt=operators.top();//the location of the operator between current ()
                if (p_opt<p_left) {//if the operator is not between ()
                    goto push_operator;
                }
                if (operators_compare(a[p_opt],cur)>0) {
                    operators.pop();
                }else continue;
                
            push_operator:
                operators.push(i);
            }
        }
        
		print(a,len);
		while(!operators.empty())
			operators.pop();
    }
	return 0;
}

