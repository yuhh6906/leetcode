//
// Created by yuhuanghua on 2023/9/6.
//

#ifndef TEST_C___STACK_TEST_H
#define TEST_C___STACK_TEST_H
#include <cstring>
#include <stack>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*最小栈*/
class MinStack {
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.push(INT_MAX);
    }

    void push(int val) {
        x_stack.push(val);
        min_stack.push(min(min_stack.top(), val));
    }

    void pop() {
        x_stack.pop();
        min_stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int getMin() {
        return min_stack.top();
    }
};

class stack_test {
public:
    /*基本计算器
     * 给你一个字符串表达式 s ，请你实现一个基本计算器来计算并返回它的值
     * s 由数字、'+'、'-'、'('、')'、和 ' ' 组成
     * 输入：s = "(1+(4+5+2)-3)+(6+8)" 输出：23*/
    int calculate(string s) {
        //
        int i = 0;
        int sign = 1;
        int res = 0;
        stack<int> opt;//用来记录括号前是正数还是负数
        opt.push(1);
        while(i < s.size()){
            if(s[i] == '+'){
                sign = opt.top();
                ++i;
            } else if(s[i] == '-'){
                sign = -opt.top();
                ++i;
            } else if(s[i] == ' '){
                ++i;
            } else if(s[i] == '('){
                opt.push(sign);
                ++i;
            } else if(s[i] == ')'){
                opt.pop();
                ++i;
            } else{
                long num = 0;
                while (i < s.size() && s[i] >= '0'&& s[i] <= '9'){
                    num = num*10 + s[i] - '0';
                    ++i;
                }
                res = res + sign*num;
            }
        }
        return res;
    }

    /*逆波兰表达式求值
     * 给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。请你计算该表达式。返回一个表示表达式值的整数。
     * 有效的算符为 '+'、'-'、'*' 和 '/'*/
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (int i = 0; i < tokens.size(); ++i) {
            //判断是否是一个数字
            string str = tokens[i];
            if(str != "+" && str != "-" && str != "*" && str != "/"){
                //atio用于将字符串->整数类型（int）。int atoi(const char* str); c_str()
                //c_str() 是 std::string 类提供的一个成员函数，用于返回一个以 null 结尾的字符数组（C 风格字符串）的指针。
                stk.push(atoi(str.c_str()));
            } else{
                int a = stk.top();
                stk.pop();
                int b = stk.top();
                stk.pop();
                switch (str[0]) {
                    case '+':
                        stk.push(a + b);
                        break;
                    case '-':
                        stk.push(b - a);
                        break;
                    case '*':
                        stk.push(a * b);
                        break;
                    case '/':
                        stk.push(b/a);
                        break;
                }
            }
        }
        return stk.top();
    }


/* 简化路径
给你一个字符串 path ，表示指向某一文件或目录的 Unix 风格 绝对路径 （以 '/' 开头），请你将其转化为更加简洁的规范路径。
 在 Unix 风格的文件系统中，一个点（.）表示当前目录本身；此外，两个点 （..） 表示将目录切换到上一级（指向父目录）；
 两者都可以是复杂相对路径的组成部分。任意多个连续的斜杠（即，'//'）都被视为单个斜杠 '/' 。 对于此问题，任何其他格式的点（例如，'...'）均被视为文件/目录名称。*/
    string simplifyPath(string path) {
        auto split = [] (const string s, char delim) -> vector<string>{
            vector<string> ans;
            string cur;
            for(char ch : s){
                if(ch == delim){
                    ans.push_back(cur);
                    cur = "";
                } else{
                    cur += ch;
                }
            }
            ans.push_back(move(cur));
            return ans;
        };

        vector<string> names = split(path, '/');
        vector<string> stack;
        for(string str : names){
            if(str == ".."){
                if(!stack.empty()){
                    stack.pop_back();
                }
            } else if(!str.empty() && str != "."){
                stack.push_back(move(str));
            }
        }
        string ans;
        if(stack.empty()){
            return "/";
        } else{
            for(string str: stack){
                ans += "/" + move(str);
            }
        }
        return ans;
    }


    //有效的括号： 判断【】（） {}
    bool isValid(string s) {
        int n = s.size();
        if(n % 2 !=0){
            return false;
        }
        unordered_map<char, char> pair = {
                {')', '('},
                {']', '['},
                {'}', '{'}
        };
        stack<char> stk;
        for(char ch : s){
            if(pair.count(ch) != 0){
                if(stk.empty() || stk.top() != pair[ch]){
                    return false;
                }
                stk.pop();
            } else{
                stk.push(ch);
            }
        }
        return stk.empty();
    }
};


#endif //TEST_C___STACK_TEST_H
