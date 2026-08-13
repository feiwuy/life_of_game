// 蚁穴迷宫宇宙
// B3/S1234
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define n 22 // 除去外围后为20x20

int** Init_Data() {
    // 初始化表格数据22x22个0
    int** data = (int**)malloc(n*sizeof(int*));
    for (int i = 0;i < n;i++) {
        *(data+i) = (int*)calloc(n,sizeof(int));
    }
    return data;
}

// 定义数组以存储初始坐标
int** Init_Coordinate(int** data) {
    printf("请输入初始坐标(x,y):\n[输入00结束,x y<=%d]\n",n-2);
    int x = 0,y = 0;
    while(1) {
        scanf("%d,%d",&x,&y);
        if (x == 0 || y == 0) break;
        *(*(data+x)+y) = 1;
    }
    return data;
}

// 处理数据
int** Data_Progress(int** data) {
    // 定义新数组存放数据
    int** new_data = Init_Data();
    for (int i = 1;i < n-1;i++) {
        for (int j = 1;j < n-1;j++) {
            *(*(new_data+i)+j) = *(*(data+i)+j);
            int one_num = 0;
            // 判断四周八个格是否有至少m个1
            if (*(*(data+i-1)+j-1)) one_num++;
            if (*(*(data+i-1)+j)) one_num++;
            if (*(*(data+i-1)+j+1)) one_num++;
            if (*(*(data+i)+j-1)) one_num++;
            if (*(*(data+i)+j+1)) one_num++;
            if (*(*(data+i+1)+j-1)) one_num++;
            if (*(*(data+i+1)+j)) one_num++;
            if (*(*(data+i+1)+j+1)) one_num++;
            if  ((*(*(data+i)+j) == 1) && ((one_num == 1) || (one_num == 2)) || (one_num == 3) || (one_num == 4)) *(*(new_data+i)+j) = 1;
            else if ((*(*(data+i)+j) == 0) && (one_num == 3)) *(*(new_data+i)+j) = 1;
            else *(*(new_data+i)+j) = 0;
        }
    }
    for (int i = 0;i < n;i++) {
        free(*(data+i));
    }
    free(data);
    return new_data;
}

// 打印数据
void Print_Data(int** data) {
    printf("\n-----------------------\n");
    for (int i = 1;i < n-1;i++) {
        for (int j = 1;j < n-1;j++) {
            if (*(*(data+i)+j) == 1) {
                // printf("\033[43m%d\033[0m ",*(*(data+i)+j));
                printf("\033[32m%d\033[0m ",0);
            }
            else {
                printf("%d ",*(*(data+i)+j));
            }
        }
        printf("\n");
    }
}

int main() {

    int** data = Init_Data();
    // 定义初始坐标
    data = Init_Coordinate(data);

    // 处理数据
    system("clear");
    for (int i = 0;i < 100;i++) {
        data = Data_Progress(data); 
        printf("第%d轮",i);
        Print_Data(data);
        sleep(1);
        system("clear");
    }


    return 0;
}
