//
//  main.c
//  miGong
//
//  Created by JACK on 2017/10/9.
//  Copyright © 2017年 JACK. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

typedef struct direction{
    int now;
    int x;
    int y;
    int way;
    int north;
    int south;
    int west;
    int east;
}direction;
//建立栈
typedef struct stack{
    int x;
    int y;
    int way;
    struct stack *next;
}result;
//go to stack
int pushStack(result *top,direction *unit){
    result *p = (result *)malloc(sizeof(result));
    if (!p) {
        return 0;
    }
    p->x = unit->x;
    p->y = unit->y;
    p->way = unit->way;
    p->next = top->next;
    top->next = p;
    return 1;
}
//out of stack
int popStack(result *top){
    result *p ;
    if (top->next==NULL) {
        return 0;
    }
    p = top->next;
    top->next = p->next;
    free(p);
    return 1;
}
result *getStackTop(result *top){
    
    if (top->next) {
        return top->next;
    }else
        return NULL;
}
//判空 ( 1==空，0==不空 )
int stackIsEmpty(result *top){
    
    if (top->next == NULL) {
        return 1;
    }
    return 0;
}
//choice
int choice(result *top,direction *unit){
    result *now ;
    if (unit->east==0) {
        unit->way = 1;
        unit->now = 3;
        pushStack(top, unit);
    }else if (unit->south == 0){
        unit->way = 2;
        unit->now = 3;
        pushStack(top, unit);
    }else if (unit->west == 0){
        unit->way = 3;
        unit->now = 3;
        pushStack(top, unit);
    }else if (unit->north == 0){
        unit->way = 4;
        unit->now = 3;
        pushStack(top, unit);
    }else{
        unit->now = 1;
        now = getStackTop(top);
        popStack(top);
        return now->way;
    }
    return 8;
}
void print(result *top){
    if (top->next) {
        print(top->next);
        printf("(%d,%d,%d)",top->next->x,top->next->y,top->next->way);
    }
}
int main(int argc, const char * argv[]) {
    int row = 0,column = 0,i=1,j,uRow,uColumu;
    result *top = (result *)malloc(sizeof(result));//初始化栈
    top->next = NULL;
    direction  map[12][12];
    char number[12];
    scanf("%d %d",&row,&column);
    uRow = row;
    uColumu = column;
    for (; uRow>0; uRow--,i++) {
        scanf("%s",number);
        for (j=1; j<=uColumu; j++) {
            map[i][j].now = (int)(number[j-1]-'0');
            map[i][j].y = j;
            map[i][j].x = i;
            if (map[i][j].now!=1&&map[i][j].now!=0) {
                printf("Error\n");
                return 0;
            }
        }
    }
    i=1,j=1;
    while (!(i==row && j==column)) {
        if (j+1<=column) {
            map[i][j].east = map[i][j+1].now;
        }else{
            map[i][j].east = 1;
        }
        if (i+1<=row) {
            map[i][j].south = map[i+1][j].now;
        }else{
            map[i][j].south = 1;
        }
        if (j-1>=1) {
            map[i][j].west = map[i][j-1].now;
        }else{
            map[i][j].west = 1;
        }
        if (i-1>=1) {
            map[i][j].north = map[i-1][j].now;
        }else{
            map[i][j].north = 1;
        }
        //开始搜索
            switch (choice(top, &map[i][j])) {
                case 8:
                    switch (map[i][j].way) {
                        case 1:
                            j = j+1;
                            map[i][j].y = j;
                            break;
                        case 2:
                            i= i+1;
                            map[i][j].x = i;
                            break;
                        case 3:
                            j = j-1;
                            map[i][j].y = j;
                            break;
                        case 4:
                            i = i-1;
                            map[i][j].x = i;
                            break;
                    }
                    break;
                case 1:
                    j = j-1;
                    map[i][j].y = j;
                    break;
                case 2:
                    i = i-1;
                    map[i][j].x = i;
                    break;
                case 3:
                    j = j+1;
                    map[i][j].y = j;
                    break;
                case 4:
                    i = i+1;
                    map[i][j].x = i;
                    break;
            }
        }//完成搜索
   //打印结果
    print(top);
    return 0;
}
