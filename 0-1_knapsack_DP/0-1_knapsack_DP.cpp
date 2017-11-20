#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include <time.h>
int K[21][21]; //결과를 담을 행렬 생성
int knapsack(int n, int W, int price[], int weight[]){

    for(int i=0;i<=n;i++){//초기화
        K[i][0] = 0;
    }
    for(int w=0;w<=W;w++){//초기화
        K[0][w] = 0;
    }

    for(int i=1;i<=n;i++){
        for(int w=1;w<=W;w++){
            if(weight[i]>w)
                K[i][w] = K[i-1][w];//무게가 아직 w보다 크다면 이전 단계의 무게를 쓴다.
            else{
                int selected_val = K[i-1][w-weight[i]] + price[i]; //그 물건을 넣었을 때의 가치
                int unselected_val = K[i-1][w];//그 물건을 넣지 않앗을 때의 가치
                K[i][w] = (selected_val > unselected_val) ? selected_val : unselected_val; //가치가 큰 것을 넣는다.
            }
			//애니메이션 구현 부분(애니메이션을 보기 위해선 여기를 주석 해제하고 아랫 부분을 주석)
			printf("12121623 정보통신공학과 김정현\n");
			for (int i = 0; i <= n; i++) {
				for (int j = 0; j <= W; j++) {
					printf("%3d", K[i][j]);
				}
				printf("\n");
			}
			printf("\n");
			Sleep(1000);
			system("cls");
        }
    }
	//결과 출력 부분(실행 최종결과를 보기 위해선 여기를 주석 해제하고 윗 부분을 주석)
	/*for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= W; j++) {
			printf("%3d", K[i][j]);
		}
		printf("\n");
	}*/
    return K[n][W];
}

int main(){
	//문제 실행결과를 보기위에선 이 부분을 주석해제하고 아래를 애니메이션 부분을 주석
	////예제 1
	//printf("12121623 정보통신공학과 김정현\n");
	//int item_cnt = 3; //아이템 갯수
 //   int price[4] = {0, 10, 1, 100}; //아이템의 갯수 3개
 //   int weight[4] = {0, 4, 1, 11}; //각 무게
 //   int Weight = 10; //배낭 최대 무게 10kg

	//clock_t start = clock();
	//int max_val = knapsack(item_cnt, Weight, price, weight);
	//clock_t end = clock();
	//double t = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("\n소요 시간: %fs.\n", t);
	//printf("max price: %d\n\n", max_val);
	//
	////예제 2
	//printf("12121623 정보통신공학과 김정현\n");
	//int item_cnt2 = 4; //아이템 갯수
	//int price2[5] = { 0, 3, 4, 5, 6 }; //아이템의 갯수 4개
	//int weight2[5] = { 0, 2, 3, 4, 5 };
	//int Weight2 = 5; //배낭 최대 무게 5kg

	//clock_t start2 = clock();
	//int max_val2 = knapsack(item_cnt2, Weight2, price2, weight2);
	//clock_t end2 = clock();
	//double t2 = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("\n소요 시간: %fs.\n", t2);
	//printf("max price: %d\n\n", max_val2);

	////예제 3
	//printf("12121623 정보통신공학과 김정현\n");
	//int item_cnt3 = 5; //아이템 갯수
	//int price3[6] = { 0, 5, 3, 2, 9, 6 };//아이템의 갯수 5개
	//int weight3[6] = {0, 2, 7, 1, 4, 1 };
	//int Weight3 = 20; //배낭 최대 무게 20kg
	//
	//clock_t start3 = clock();
	//int max_val3 = knapsack(item_cnt3, Weight3, price3, weight3);
	//clock_t end3 = clock();
	//double t3 = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("\n소요 시간: %fs.\n", t3);
	//printf("max price: %d\n\n", max_val3);

	////예제 4
	//printf("12121623 정보통신공학과 김정현\n");
	//int item_cnt4 = 6; //아이템 갯수
	//int price4[7] = { 0, 3, 5, 4, 3, 10, 5 };//아이템의 갯수 6개
	//int weight4[7] = { 0, 4, 5, 3, 7, 8, 6 };
	//int Weight4 = 10; //배낭 최대 무게 10kg

	//clock_t start4 = clock();
	//int max_val4 = knapsack(item_cnt4, Weight4, price4, weight4);
	//clock_t end4 = clock();
	//double t4 = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("\n소요 시간: %fs.\n", t4);
	//printf("max price: %d\n\n", max_val4);

	////예제 5
	//printf("12121623 정보통신공학과 김정현\n");
	//int item_cnt5 = 7; //아이템 갯수
	//int price5[8] = { 0, 6, 2, 7, 4, 5, 3, 9 };//아이템의 갯수 5개
	//int weight5[8] = { 0, 5, 4, 8, 5, 6, 6, 7 };
	//int Weight5 = 20; //베낭 20kg

	//clock_t start5 = clock();
	//int max_val5 = knapsack(item_cnt5, Weight5, price5, weight5);
	//clock_t end5 = clock();
	//double t5 = (double)(end - start) / CLOCKS_PER_SEC;
	//printf("\n소요 시간: %fs.\n", t5);
	//printf("max price: %d\n", max_val5);
	
	//애니메이션 구현 부분 애니메이션을 보기위해선 이 부분을 주석 해제하고 위의 실행결과 부분을 주석
	//애니메이션 구현(예제 1의 경우임)
	int item_cnt = 3; //아이템 갯수
	int price[4] = { 0, 10, 1, 100 }; //아이템의 갯수 3개
	int weight[4] = { 0, 4, 1, 11 }; //각 무게
	int Weight = 10; //배낭 최대 무게 10kg

	int max_val = knapsack(item_cnt, Weight, price, weight);
	printf("max price: %d\n\n", max_val);
    return 0;
}
