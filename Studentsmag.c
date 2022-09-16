//
// Created by Toyoui on 2022/9/14.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Student {
    char ID[20];//学号
    char Name[10];//姓名
    float Mark1;//语文成绩
    float Mark2;//数学成绩
    float Mark3;//英语成绩
    float All; //总分
    float Average;//平均成绩
} S;
S students[500];

// 载入文件
void Load();

// 写入文件
void Save();

// 1.添加学生记录
void addStudate();

// 2.修改学生记录
void modifyStudate();

// 3.删除学生记录
void deleteeStudate();

// 4.插入学生记录
void insertStudate();

// 5.输出所有学生记录
void displayStudate(S *disStu);

// 6.查询学生记录
void searchStudate();

// 7.按平均成绩排序
void sortArrdate();

// 8.输出不及格学生
void SearchLow();

// 9.输出最高分学生
void SearchHigh();

// 通过学号查学生
int Student_SearchByIndex(char id[]);

// 通过姓名查学生
int Student_SearchByName(char name[]);

// 数据复制转移
void Students_Copy(struct Student *stu, int i, int j);

// 单独输出学生信息
void Student_DisplaySingle(int index);

// 查询不及格输出
void Student_Scorel(int lownum, float score);

// 最高分计算输出
void Student_Scorec(int marknum);

// 主程序
int num = 0; //计数器
int main() {
    int i;
    while (1) {
        Load();
        printf("\t\t\t\t\t-------- 学生成绩管理系统-------\n\n\n\n");     //菜单
        printf("\t\t\t\t\t1. 增加学生记录\n\n");
        printf("\t\t\t\t\t2. 修改学生记录\n\n");
        printf("\t\t\t\t\t3. 删除学生记录\n\n");
        printf("\t\t\t\t\t4. 插入学生记录\n\n");
        printf("\t\t\t\t\t5. 显示所有记录\n\n");
        printf("\t\t\t\t\t6. 查询学生记录\n\n");
        printf("\t\t\t\t\t7. 按平均成绩排序输出\n\n");
        printf("\t\t\t\t\t8. 输出各科目不及格学生\n\n");
        printf("\t\t\t\t\t9. 输出各科目最高分\n\n");
        printf("\t\t\t\t\t0. 退出\n\n\n");
        printf("请选择(0-9):");
        scanf("%d", &i);
        switch (i) {
            case 1:
                addStudate();
                break;
            case 2:
                modifyStudate();
                break;
            case 3:
                deleteeStudate();
                break;
            case 4:
                insertStudate();
                break;
            case 5:
                printf("\t\t\t-------- 输出所有学生信息-------\n\n");
                displayStudate(students);
                break;
            case 6:
                searchStudate();
                break;
            case 7:
                sortArrdate();
                break;
            case 8:
                SearchLow();
                break;
            case 9:
                SearchHigh();
                break;
            case 0:
                exit(0);
            default:;
        }
        Save();
    }
}

// 载入学生文件
void Load() {
    FILE *fp = fopen("students.txt", "r");
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; i++) {
        fscanf(fp, "%s %s %f %f %f %f %f\n", students[i].ID, students[i].Name, &students[i].Mark1,
               &students[i].Mark2, &students[i].Mark3, &students[i].All, &students[i].Average);
    }
    fclose(fp);
}

// 保存入学生文件
void Save() {
    FILE *fp = fopen("students.txt", "w+");
    fprintf(fp, "%d\n", num);
    for (int i = 0; i < num; i++) {
        fprintf(fp, "%s %s %f %f %f %f %f\n", students[i].ID, students[i].Name, students[i].Mark1, students[i].Mark2,
                students[i].Mark3, students[i].All, students[i].Average);
    }
    fclose(fp);
}

// 1.增加学生记录
void addStudate() {
    printf("\t\t\t-------- 增加学生记录-------\n\n");
    while (1) {
        printf("请输入学号:");
        scanf("%s", &students[num].ID);
        getchar();
        printf("请输入姓名:");
        scanf("%s", &students[num].Name);
        getchar();
        printf("请输入语文成绩:");
        scanf("%f", &students[num].Mark1);
        getchar();
        printf("请输入数学成绩:");
        scanf("%f", &students[num].Mark2);
        getchar();
        printf("请输入英语成绩:");
        scanf("%f", &students[num].Mark3);
        getchar();

        students[num].All = students[num].Mark1 + students[num].Mark2 + students[num].Mark3;
        students[num].Average = students[num].All / 3;

        if (Student_SearchByIndex(students[num].ID) == -1) {
            num++;  //移向下一个位置
        } else {
            printf("学号重复，输入数据无效 !!!\n");
        }

        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 2.修改学生记录
void modifyStudate() {
    printf("\t\t\t-------- 修改学生记录-------\n\n");
    while (1) {
        char id[20];

        printf("请输入你要修改的学生学号：");
        scanf("%s", &id);
        getchar();

        int temp = Student_SearchByIndex(id);
        if (temp == -1) {
            printf("不存在此学号学生\n");
        } else {
            while (1) {
                printf("要修改的学生信息\n");
                Student_DisplaySingle(temp);

                int i;
                printf("\t\t\t\t\t1. 修改学生学号\n\n");
                printf("\t\t\t\t\t2. 修改学生姓名\n\n");
                printf("\t\t\t\t\t3. 修改学生语文成绩\n\n");
                printf("\t\t\t\t\t4. 修改学生数学成绩\n\n");
                printf("\t\t\t\t\t5. 修改学生英语成绩\n\n");
                printf("请输入数字：");
                scanf("%d", &i);

                switch (i) {
                    case 1:
                        printf("请输入学号:");
                        scanf("%s", &students[temp].ID);
                        getchar();
                        break;
                    case 2:
                        printf("请输入姓名:");
                        scanf("%s", &students[temp].Name);
                        getchar();
                        break;
                    case 3:
                        printf("请输入语文成绩:");
                        scanf("%f", &students[temp].Mark1);
                        getchar();
                        break;
                    case 4:
                        printf("请输入数学成绩:");
                        scanf("%f", &students[temp].Mark2);
                        getchar();
                        break;
                    case 5:
                        printf("请输入英语成绩:");
                        scanf("%f", &students[temp].Mark3);
                        getchar();
                        break;
                    default:
                        break;
                }

                students[temp].All =
                        students[temp].Mark1 + students[temp].Mark2 + students[temp].Mark3;    //输完数据后自动计算总成绩与平均成绩
                students[temp].Average = (students[temp].Mark1 + students[temp].Mark2 + students[temp].Mark3) / 3;

                printf("修改后的学生信息\n");
                Student_DisplaySingle(temp);

                printf("是否继续修改此学生?(y/n)\n");
                if (getchar() == 'n') {
                    getchar();
                    goto start;;
                }
            }
        }

        start:
        printf("是否继续修改其他学生?(y/n)\n");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 3.删除学生记录
void deleteeStudate() {
    printf("\t\t\t-------- 删除学生记录-------\n\n");
    int i;
    while (1) {
        char id[20];
        int index;
        printf("请输入你要删除的学生学号：");
        scanf("%s", &id);
        getchar();
        index = Student_SearchByIndex(id);

        if (index == -1) {
            printf("不存在该学生，请重新输入\n");
        } else {
            printf("该学生信息为：\n");
            Student_DisplaySingle(index);
            printf("是否删除(y/n)?");
            if (getchar() == 'y') {
                for (i = index; i < num - 1; ++i) {
                    Students_Copy(students, index, i + 1);
                }
                num--;
            }
            getchar();
        }


        printf("是否继续删除学生记录(y/n)?\n");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 4.插入学生数据
void insertStudate() {
    printf("\t\t\t-------- 插入学生数据-------\n\n");
    int dateId, temp;
    char newID[20];
    while (1) {
        printf("当前有%2d个学生数据\n", num);
        printf("请输入你要插入的学生数据位置：");
        scanf("%d", &dateId);
        getchar();

        if (dateId > num) {
            printf("所选位置错误，需要重新插入\n");
            goto newEnd;
        } else {
            printf("请输入学号:\n");
            scanf("%s", &newID);
            getchar();

            // 学号唯一性判断
            if (Student_SearchByIndex(newID) == -1) {
                temp = num;
                num++; // 成功插入数据，学生个数必增加

                // 插入位置后面数据全部后移 一个位置
                for (int i = temp - 1; i >= dateId - 1; i--) {
                    Students_Copy(students, i + 1, i);
                }

                dateId--; // 写入对应位置数据位置
                strcpy(students[dateId].ID, newID);
            } else {
                printf("学号重复，输入数据无效 !!!\n");
                goto newEnd;
            }

            printf("请输入姓名:");
            scanf("%s", &students[dateId].Name);
            getchar();
            printf("请输入语文成绩:");
            scanf("%f", &students[dateId].Mark1);
            getchar();
            printf("请输入数学成绩:");
            scanf("%f", &students[dateId].Mark2);
            getchar();
            printf("请输入英语成绩:");
            scanf("%f", &students[dateId].Mark3);
            getchar();

            students[dateId].All = students[dateId].Mark1 + students[dateId].Mark2 + students[dateId].Mark3;
            students[dateId].Average = students[dateId].All / 3;
        }

        newEnd:
        printf("是否继续插入学生记录(y/n)?\n");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 5.输出所有学生信息
void displayStudate(S *disStu) {
    printf("%10s%10s%8s%8s%8s%12s%13s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩", "平均成绩");
    printf("-------------------------------------------------------------\n");
    for (int j = 0; j < num; j++) {
        printf("%10s%10s%8.2f%8.2f%8.2f%10.2f%10.2f\n", disStu[j].ID, disStu[j].Name,
               disStu[j].Mark1, disStu[j].Mark2, disStu[j].Mark3, disStu[j].All, disStu[j].Average);
    }
}

// 6.查询学生信息
void searchStudate() {
    printf("\t\t\t-------- 查询学生信息-------\n\n");
    while (1) {
        char name[20];
        printf("请输入你要查的学生姓名：");
        scanf("%s", &name);
        getchar();

        int temp = Student_SearchByName(name);
        if (temp == -1) {
            printf("该学生不存在\n");
        } else {
            printf("你要查询的学生信息为:\n");
            Student_DisplaySingle(temp);
        }
        printf("是否继续?(y/n)");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 7.按平均成绩排序输出
void sortArrdate() {
    printf("\t\t\t-------- 按平均成绩排序输出-------\n\n");
    S studentArr[num];
    S t[1];
    for (int i = 0; i < num; ++i) {
        studentArr[i] = students[i];
    }

    // 冒泡排序
    for (int i = 0; i < num - 1; ++i) {
        for (int j = 0; j < num - i - 1; ++j) {
            if (studentArr[j].Average > studentArr[j + 1].Average) { //这是升序 降序用 <
                t[0] = studentArr[j + 1];
                studentArr[j + 1] = studentArr[j];
                studentArr[j] = t[0];
            }
        }
    }

    displayStudate(studentArr);
}

// 8.输出对应科目不及格
void SearchLow() {
    printf("\t\t\t\t-------- 输出对应科目不及格-------\n\n");
    while (1) {
        int i;
        float score1, score2, score3;
        printf("\n");
        printf("\t\t\t\t\t1. 语文不及格\n\n");
        printf("\t\t\t\t\t2. 数学不及格\n\n");
        printf("\t\t\t\t\t3. 英语不及格\n\n");
        printf("请输入数字：");
        scanf("%d", &i);
        getchar();

        switch (i) {
            case 1:
                printf("请输入语文 及格成绩：");
                scanf("%f", &score1);
                getchar();
                Student_Scorel(1, score1);
                break;
            case 2:
                printf("请输入数学 及格成绩：");
                scanf("%f", &score2);
                getchar();
                Student_Scorel(2, score2);
                break;
            case 3:
                printf("请输入英语 及格成绩：");
                scanf("%f", &score3);
                getchar();
                Student_Scorel(3, score3);
                break;
            default:
                break;
        }

        printf("是否继续查询其他科目(y/n)?\n");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 9.查找输出对应科目最高分
void SearchHigh() {
    printf("\t\t\t\t-------- 输出对应科目最高分-------\n\n");
    while (1) {
        int i;
        printf("\n");
        printf("\t\t\t\t\t1. 语文最高分\n\n");
        printf("\t\t\t\t\t2. 数学最高分\n\n");
        printf("\t\t\t\t\t3. 英语最高分\n\n");
        printf("请输入数字：");
        scanf("%d", &i);
        getchar();

        switch (i) {
            case 1:
                Student_Scorec(1);
                break;
            case 2:
                Student_Scorec(2);
                break;
            case 3:
                Student_Scorec(3);
                break;
            default:
                break;
        }

        printf("是否继续查询其他科目(y/n)?\n");
        if (getchar() == 'n') {
            break;
        }
    }
}

// 通过ID查找学生
int Student_SearchByIndex(char id[]) {
    for (int i = 0; i < num; ++i) {
        if (strcmp(students[i].ID, id) == 0) {
            return i;
        }
    }

    return -1;
}

// 通过名字查学生
int Student_SearchByName(char name[]) {
    for (int i = 0; i < num; ++i) {
        if (strcmp(students[i].Name, name) == 0) {
            return i;
        }
    }

    return -1;
}

// 数据复制转移
void Students_Copy(struct Student *stu, int i, int j) {
    // 把 j 位置的 数据 复制转移到 i位置
    strcpy(stu[i].ID, stu[j].ID);
    strcpy(stu[i].Name, stu[j].Name);
    stu[i].Mark1 = stu[j].Mark1;
    stu[i].Mark2 = stu[j].Mark2;
    stu[i].Mark3 = stu[j].Mark3;
    stu[i].All = stu[j].All;
    stu[i].Average = stu[j].Average;
}

// 单独输出学生
void Student_DisplaySingle(int index) {
    printf("%10s%10s%8s%8s%8s%12s%13s\n", "学号", "姓名", "语文", "数学", "英语", "总成绩", "平均成绩");
    printf("-------------------------------------------------------------\n");
    printf("%10s%10s%8.2f%8.2f%8.2f%10.2f%10.2f\n", students[index].ID, students[index].Name,
           students[index].Mark1, students[index].Mark2, students[index].Mark3, students[index].All,
           students[index].Average);
}

// 查找不及格并输出
void Student_Scorel(int lownum, float score) {
    int j, flag;
    if (lownum == 1) {
        j = 1;
        flag = 0;
        for (int i = 0; i < num; ++i) {
            if (students[i].Mark1 < score) {
                printf("语文%3d%10s%8.2f\n", j, students[i].Name, students[i].Mark1);
                j++;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("所有学生 语文及格\n");
        }
    }
    if (lownum == 2) {
        j = 1;
        flag = 0;
        for (int i = 0; i < num; ++i) {
            if (students[i].Mark2 < score) {
                printf("数学%3d%10s%8.2f\n", j, students[i].Name, students[i].Mark2);
                j++;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("所有学生 数学及格\n");
        }
    }
    if (lownum == 3) {
        j = 1;
        flag = 0;
        for (int i = 0; i < num; ++i) {
            if (students[i].Mark3 < score) {
                printf("英语%3d%10s%8.2f\n", j, students[i].Name, students[i].Mark3);
                j++;
                flag = 1;
            }
        }
        if (flag == 0) {
            printf("所有学生 英语及格\n");
        }
    }
}

// 计算科目成绩最高分并输出
void Student_Scorec(int marknum) {
    if (marknum == 1) {
        int max = students[0].Mark1;
        for (int i = 1; i < num; ++i) {
            if (students[i].Mark1 > max) {
                max = students[i].Mark1;
            }
        }
        for (int i = 0; i < num; ++i) {
            if (max == students[i].Mark1) {
                printf("语文最高分为：%10s%8.2f 分\n", students[i].Name, students[i].Mark1);
            }
        }
    }
    if (marknum == 2) {
        int max = students[0].Mark2;
        for (int i = 1; i < num; ++i) {
            if (students[i].Mark2 > max) {
                max = students[i].Mark2;
            }
        }
        for (int i = 0; i < num; ++i) {
            if (max == students[i].Mark2) {
                printf("数学最高分为：%10s%8.2f 分\n", students[i].Name, students[i].Mark2);
            }
        }
    }
    if (marknum == 3) {
        int max = students[0].Mark3;
        for (int i = 1; i < num; ++i) {
            if (students[i].Mark3 > max) {
                max = students[i].Mark3;
            }
        }
        for (int i = 0; i < num; ++i) {
            if (max == students[i].Mark3) {
                printf("英语最高分为：%10s%8.2f 分\n", students[i].Name, students[i].Mark3);
            }
        }
    }
}
