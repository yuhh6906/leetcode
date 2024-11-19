#include <stdio.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char ch;
    char line[100]; // 假设每行不超过99个字符

    // 打开文件，只读模式
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件\n");
        return 1;
    }

    // 逐字符读取文件
    while ((ch = fgetc(file)) != EOF) {
        printf("%c", ch);
    }
    
    //逐行读取
    while(fgets(line, sizeof(line), file)){
        printf("%s", line);
    }
    // 关闭文件
    fclose(file);

    // 重新打开文件，写入模式
    file = fopen(filename, "w");  // "a" 追加内容
    if (file == NULL) {
        printf("无法创建文件\n");
        return 1;
    }

    // 向文件写入字符串
    fprintf(file, "Hello, World!\n");

    // 关闭文件
    fclose(file);

    return 0;
}