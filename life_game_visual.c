#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "raylib.h"

#define n 52 // 除去外围后为50x50
#define B2 2 // 0 和 3个1, 0 变 1
#define S2 2
#define S3 3 // 除了3以外, 1 变 0

#define WIDTH 800
#define HEIGHT 800

int** Init_Data() {
    // 初始化表格数据
    int** data = (int**)malloc(n*sizeof(int*));
    for (int i = 0;i < n;i++) {
        *(data+i) = (int*)calloc(n,sizeof(int));
    }
    return data;
}

// 定义数组以存储初始坐标
int** Init_Coordinate(int** data) {
    printf("请输入初始坐标(x,y):\n[输入0结束,x y<=%d]\n",n-2);
    int x = 0,y = 0;
    while(1) {
        int adjust = scanf("%d,%d",&x,&y);
        if (adjust == EOF) break;
        // clear the buffer
        if (adjust == 0) {
            while (getchar() != '\n');
            continue;
        }

        // define the exit patterns
        if ((adjust == 1 && x == 0) || (adjust == 2 && x == 0 && y == 0)) break;

        // check the coordinate (if x(y) <= 0)
        if (x <= 0 || x >= n-1 || y <= 0 || y >= n-1) continue;

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
            if  ((*(*(data+i)+j) == 1) && ((one_num == S2) || (one_num == S3))) *(*(new_data+i)+j) = 1;
            else if ((*(*(data+i)+j) == 0) && (one_num == B2)) *(*(new_data+i)+j) = 1;
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
// void Print_Data(int** data) {
//     printf("\n-----------------------\n");
//     for (int i = 1;i < n-1;i++) {
//         for (int j = 1;j < n-1;j++) {
//             if (*(*(data+i)+j) == 1) {
//                 // printf("\033[43m%d\033[0m ",*(*(data+i)+j));
//                 printf("\033[32m%d\033[0m ",0);
//             }
//             else {
//                 printf("%d ",*(*(data+i)+j));
//             }
//         }
//         printf("\n");
//     }
//     //通过覆盖原内容实现原地刷新
//     printf("\033[22A"); // 20+2(第n次\n-----------------------\n)
// }

// 绘制图像
void DrawGraph(int **data) {
    // define the side length
    int sideLength = WIDTH / (n - 2);
    // draw the graph(in one frame)
    for (int i = 1; i < n-1; i++) {
        for (int j = 1; j < n-1; j++) {
            if (*(*(data + i)+j)) {
                DrawRectangle((i - 1) * sideLength, (j - 1) * sideLength, sideLength, sideLength, BLACK);
            }
            // else {
            //     DrawRectangle((i - 1) * sideLength, (j - 1) * sideLength, sideLength, sideLength, WHITE);
            // }
        }
    }
}

int main() {
    // init the data
    int** data = Init_Data();

    // 定义初始坐标
    data = Init_Coordinate(data);

    SetTargetFPS(60);

    // set the frame counter
    int frameCount = 0;
    // update once after ten frame
    int stepInterVal = 20;

    InitWindow(WIDTH, HEIGHT, "Game of Life --raylib");
    while(!WindowShouldClose()) {
        frameCount++;
        BeginDrawing();
            ClearBackground(WHITE);

            DrawGraph(data);
            DrawFPS(10, 10);

            if (frameCount >= stepInterVal) {
                // 计算结果
                data = Data_Progress(data); 
                // update the graph
                frameCount = 0;
            }

        EndDrawing();
    }
    CloseWindow();
    free(data);
    return 0;
}
