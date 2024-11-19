//
// Created by yuhuanghua on 2024/7/29.
//

#ifndef LEEDCODE_C_MATHS_H
#define LEEDCODE_C_MATHS_H


class Bit {
/* 67. 二进制求和
 * 给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。*/
    string addBinary(string a, string b) {
        /*整体思路是将两个字符串较短的用 0 补齐，使得两个字符串长度一致，然后从末尾进行遍历计算，得到最终结果。*/
        int m = a.size();
        int n = b.size();
        string ans;
        int ca = 0;//进位
        for (int i = m - 1, j = n - 1; i >= 0 || j >= 0 ; --i, --j) {
            int sum = ca;
            sum += i >= 0 ? a[i] - '0' : 0;
            sum += j >= 0 ? b[j] - '0' : 0;
            ans += to_string(sum % 2);
            ca = sum / 2;
        }
        if(ca != 0){
            ans += to_string(ca);
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }

/* 190. 颠倒给定的 32 位无符号整数的二进制位。
 * 输入：n = 00000010100101000001111010011100
 * 输出：964176192 (00111001011110000010100101000000)
 * 解释：输入的二进制串 00000010100101000001111010011100 表示无符号整数 43261596，
     */
    uint32_t reverseBits(uint32_t n) {
        uint32_t rev = 0; // 初始化 rev 为 0，用于存储反转后的结果
        for (int i = 0; i < 32 && n > 0; ++i) { // 遍历每一位
            /* n & 1：使用按位与操作获取 n 的最低位（即最右侧的比特位）
             * << (31 - i)：将这个比特位向左移动 (31 - i) 位。这是因为我们要将最低位放到反转后正确的位置。
             * 例如，第一位（i = 0）应该放到最高位（位置 31），第二位（i = 1）放到位置 30，依此类推。
             * rev |= ...：使用按位或操作将这个移动后的比特位合并到 rev 中。*/
            rev |= (n & 1) << (31 - i); // 将当前位放到 rev 的正确位置
            n >>= 1; // 右移 n，准备处理下一位  每次处理完最低位后，就通过右移操作移除最低位，为处理下一位做准备。
        }
        return rev; // 返回反转后的结果
    }

/* 191. 位1的个数
 * 给定一个正整数 n，编写一个函数，获取一个正整数的二进制形式并返回其二进制表达式中设置位的个数（也被称为汉明重量）。*/
    int hammingWeight(int n) {
        int res = 0;
        while(n > 0){
            if(n % 2 == 1){
                res++;
            }
            n = n / 2;
        }
        return res;
    }

/* 136. 只出现一次的数据
 * 给你一个 非空 整数数组 nums ，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
 * 你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。*/
    int singleNumber(vector<int>& nums) {
        /* 思路1:
         * 任何数和 0 做异或运算，结果仍然是原来的数，即 a⊕0=a。
         * 任何数和其自身做异或运算，结果是 0，即 a⊕a=0。
         * 异或运算满足交换律和结合律，即 a⊕b⊕a=b⊕a⊕a=b⊕(a⊕a)=b⊕0=b。
        */

        int ret = 0;
        for(auto& n : nums){
            ret ^= n;
        }
        return ret;
        /* 思路2: 用map*/

        unordered_map<int, int> map;
        for(auto& n : nums){
            if(map.find(n) != map.end()){
                map.erase(n);
            }else{
                map[n] = 1;
            }
        }
        int ret = 0;
        for(auto& n: map){
            ret = n.first;
        }
        return ret;
    }


/* 137. 只出现一次的数据
  * 给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 。请你找出并返回那个只出现了一次的元素。你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。*/
     int singleNumber_II(vector<int>& nums) {
        unordered_map<int, int> map;
        for(auto& n : nums){
            if(map.find(n) != map.end()){
                map[n]++;
            }else{
                map[n] = 1;
            }
        }
        int ret = 0;
        for(auto& n: map){
            if(n.second == 1) ret = n.first;
        }
        return ret;
     }


/* 201. 数字范围按位与
 * 给你两个整数 left 和 right ，表示区间 [left, right] ，返回此区间内所有数字 按位与 的结果（包含 left 、right 端点）。
 * 示例 1：输入：left = 5, right = 7    输出：4
 * 示例 2：输入：left = 0, right = 0    输出：0
 * */
    int rangeBitwiseAnd(int left, int right) {
        /*重要：对所有数字执行按位与运算的结果是所有对应二进制字符串的公共前缀再用零补上后面的剩余位。*/
        int step = 0;
        while(left < right){        // 找到公共前缀
            left >>= 1;
            right >>= 1;
            step++;
        }
        return left <<= step;
    }
};


class Maths{
/* 9. 回文数
 * 给你一个整数 x ，如果 x 是一个回文整数，返回 true ；否则，返回 false 。
 * 回文数是指正序（从左向右）和倒序（从右向左）读都是一样的整数。例如，121 是回文，而 123 不是。*/
    bool isPalindrome(int x) {
        long long y = 0;//需要longlong
        int xx = x;
        while(xx > 0){
            y = y * 10 + xx % 10;
            xx /= 10;
        }
        return x==y;
    }


/* 66. 加1 ：给定一个由整数组成的非空数组所表示的非负整数，在该数的基础上加一。最高位数字存放在数组的首位， 数组中每个元素只存储单个数字。
 * 你可以假设除了整数 0 之外，这个整数不会以零开头。*/
    vector<int> plusOne(vector<int>& digits) {
        int ca = 0;
        vector<int> ans(digits.size());
        for (int i = digits.size() - 1; i >= 0 ; --i) {
            if(i == digits.size() - 1){
                ans[i] = (digits[i] + 1) % 10;
                ca = (digits[i] + 1) / 10;
            }else{
                ans[i] = (ca + digits[i]) % 10;
                ca = (digits[i] + ca) / 10;
            }
        }
        if(ca > 0){
            ans.insert(ans.begin(), ca);
        }
        return ans;
    }



/* 172. 阶乘后的零
 * 给定一个整数 n ，返回 n! 结果中尾随零的数量。提示 n! = n * (n - 1) * (n - 2) * ... * 3 * 2 * 1
 * 示例 2：输入：n = 5   输出：1    解释：5! = 120 ，有一个尾随 0
 * */
    int trailingZeroes(int n) {
//        int sum = 1;
//        for (int i = 1; i <= n; ++i) {
//            sum *= i;
//        }
//        int res = 0;
//        while(sum > 0){
//            if(sum % 10 == 0) res++;
//            sum /= 10;
//        }
//        return res;

        /*n! 尾零的数量即为 n! 中因子 10 的个数，而 10=2×5，因此转换成求 n! 中质因子 2 的个数和质因子 5 的个数的较小值。
         * 由于质因子 5 的个数不会大于质因子 2 的个数（具体证明见方法二），我们可以仅考虑质因子 5 的个数。
         * 而 n! 中质因子 5 的个数等于 [1,n] 的每个数的质因子 5 的个数之和，我们可以通过遍历 [1,n] 的所有 5 的倍数求出。
        */
        int ans = 0;
        for (int i = 5; i <= n; i += 5) {
            for (int x = i; x % 5 == 0; x /= 5) {
                ++ans;
            }
        }
        return ans;
    }


/* 69. x的平方根
 * 给你一个非负整数 x ，计算并返回 x 的 算术平方根 。由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
 * 注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。*/
    int mySqrt(int x) {
        if(x == 0) return 0;
        for (int i = 1; i < x; ++i) {
            if(i * i <= x && (i+1) * (i+1) > x) return i;
        }
        return -1;
    }

    /* 方法2 ：二分查找*/
    int mySqrtII(int x) {
        int l = 0, r = x, ans = -1;
        while (l <= r) {
            int mid = l + (r - l) / 2;
            if ((long long)mid * mid <= x) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return ans;
    }

/* 50. 实现 pow(x, n) ，即计算 x 的整数 n 次幂函数（即，xn ）。 字节面试题
 * 方法1：递归
 * 方法2：迭代*/

    double power(double x, int y) {
        if (y == 0) {
            return 1;
        }
        if (y < 0) {
            return 1 / power(x, -y);
        }
        double half = power(x, y / 2); //可能会导致栈溢出或效率低下，特别是在y非常大的时候。因此，我们通常使用迭代的方式来实现快速幂算法
        if (y % 2 == 0) {
            return half * half;
        } else {
            return half * half * x;
        }
    }

    /*迭代方法的核心思想是利用指数的二进制表示，通过不断平方基数并根据指数的二进制位进行乘法操作，从而达到快速计算的目的。*/
    double power(double x, int y) {
        double res = 1;
        long long exponent = y;//指数 注意是longlong
        if(exponent < 0){//负指数的情况下，统一处理
            exponent = -exponent;
            x = 1/x;
        }
        while(exponent > 0){
            if(exponent % 2 == 1){
                res *= x;
            }
            x = x * x;  // 迭代情况: 每次迭代
            exponent /= 2;
        }
        return res;

    }
};

#endif //LEEDCODE_C_MATHS_H
