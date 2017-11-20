#include <iostream>
#include <Windows.h>
#include <time.h>
#include <algorithm>
#include "0-1 knapsack GA.h"
using namespace std;
typedef vector<knapsack::population> chromosomes; //vector 생성

//생성자
knapsack::knapsack() : popSize(POP_SIZE), maxB(0), bagWeight(BAG_WEIGHT) {} //개체군 크기 10, 가방 무게 초기화
void knapsack::initPopulation(chromosomes &initPop, chromosomes &initBuffer)
{
	knapsack::population p; //유전자 정보를 담을 struct 선언

	int gene = 0;//인코딩할 숫자 저장 변수
	printf("12121623 정보통신공학과 김정현\n");
	printf("초기 유전자\n");
	for (int i = 0; i < popSize; i++)
	{
		for (int j = 0; j < ITEM_COUNT; j++)//인코딩 길이
		{
			gene = randGenerate(2);//0~1까지 숫자 인코딩, Binary Encoding
			p.pop[j] = gene; //인코딩 숫자 삽입, 길이 COUNT
			printf("%d", p.pop[j]); //인코딩된 것 확인
		}
		printf("\n");
		initPop.push_back(p);//vector에 삽입
	}
	Sleep(1000);
	system("cls");
	initBuffer.resize(popSize); //임시저장공간 벡터, pop과 동일하게 개체군 크기인 10의 크기를 할당
}
int knapsack::randGenerate(int rand_num)
{
	int genenNum = rand() % rand_num; //0~1까지 난수 발생, Binary Encoding 사용

	return genenNum;
}
void knapsack::calFitness(chromosomes &pop, int userInput[][ITEM_COUNT])
{
	int fit = 0;
	int weight = 0;
	for (int i = 0; i < popSize; i++)//개체 집단, 유전자의 갯수
	{
		for (int j = 0; j < ITEM_COUNT; j++) //인코딩의 길이, input배열의 열 갯수(아이템의 갯수)
		{
			if (pop[i].pop[j] == 1) //넣음
			{
				weight += userInput[0][j]; //무게 더해주고
				fit += userInput[1][j]; //적응도 -> 가치를 더해준다
				pop[i].weight = weight;//무게를 그걸로 최신화
				pop[i].fitness = fit;//적응도 역시 그걸로 최신화

				if (weight > bagWeight) { pop[i].fitness = 0; break; } //들어온 무게가 최대 무게보다 크면 적응도 0
			}
			else //안넣음
			{
				weight += 0; //0을 더하고 
				fit += 0;//0을 더하고 
				pop[i].weight = weight; //그걸로 최신화
				pop[i].fitness = fit;//그걸로 최신화
			}
		}
		//다음 유전자를 위해 초기화
		weight = 0;
		fit = 0;
	}

}

void knapsack::copyNewGeneration(chromosomes &copyFrom, chromosomes &copyTo)//다음 세대, 이때 엘리티즘 적용 필요
{
	for (int i = 0; i < popSize; i++)
	{
		for (int j = 0; j < ITEM_COUNT; j++)
		{
			copyTo[i].pop[j] = copyFrom[i].pop[j];
		}
		copyTo[i].fitness = copyFrom[i].fitness;
	}
}

void knapsack::mutate(chromosomes &mutate, chromosomes &buffer)//돌연변이
{
	//무작위로 유전자 둘의 인덱스 선택
	int pIndex1 = randGenerate(popSize);
	int  pIndex2 = randGenerate(popSize);

	//인코딩된 숫자 중 랜덤하게 하나만을 선택
	int index1 = randGenerate(ITEM_COUNT); 
	int index2 = randGenerate(ITEM_COUNT);

	//돌연변이한 부분 확인(애니메이션 구현을 위한 부분, 결과만 보기 위해선 주석)
	printf("돌연변이한 유전자\n");
	for (int i = 0; i < ITEM_COUNT; i++)//인코딩 길이
	{
			printf("%d", buffer[pIndex1].pop[i]);
	}
	printf(" -> ");
	
	//위의 내용을 바탕으로 한 유전자의 한 인코딩 값만 바꿈
	buffer[pIndex1].pop[index1] = mutate[pIndex2].pop[index2]; //여긴 주석하면 안됨

	//돌연변이한 부분 확인(애니메이션 구현을 위한 부분, 결과만 보기 위해선 주석)
	for (int i = 0; i < ITEM_COUNT; i++)//인코딩 길이
	{
		printf("%d", buffer[pIndex1].pop[i]);
	}
	printf("\n");

	Sleep(1000);
	system("cls");
}

void knapsack::mate(chromosomes &mate1, chromosomes &mate2) //crossover(교배)
{
	copyNewGeneration(mate1, mate2); //mate1에서 mate2로 복사(buffer로 복사)

	for (int i = 0; i < ITEM_COUNT * CROSS_OVER_RATE; i++) //유전자의 인코딩 된 것의 80프로만 교배
	{
		//무작위로 유전자 둘의 인덱스를 선택
		int index1 = randGenerate(popSize);
		int index2 = randGenerate(popSize);

		if (mate2[i].weight < bagWeight || mate2[i].weight > bagWeight) //만약 최대 무게보다 크거나 작다면
		{
			mate2[index1].pop[i] = mate1[index2].pop[i]; //교배로 생성
		}
	}

	//교배된 것 확인(애니메이션 구현 부분, 결과만 보기 위해선 주석)
	printf("12121623 정보통신공학과 김정현\n");
	printf("교배된 유전자\n");
	for (int i = 0; i < popSize; i++)
	{
		for (int j = 0; j < ITEM_COUNT; j++)//인코딩 길이
		{
			printf("%d", mate2[i].pop[j]);
		}
		printf("\n");
	}
	Sleep(1000);
	mutate(mate1, mate2);//돌연변이 생성
}

void knapsack::sortByFitness(chromosomes &sort)
{
	//적응도 순으로 sorting, elitism 적용
	std::sort(sort.begin(), sort.end(),	[](const population & x, const population & y) -> bool { return(x.fitness > y.fitness); });//내림차순 정렬
	
	//정렬된 것 확인(애니메이션 구현 부분, 결과만 보기 위해선 주석)
	printf("정렬된 유전자\n");
	for (int i = 0; i < popSize; i++)
	{
		for (int j = 0; j < ITEM_COUNT; j++)//인코딩 길이
		{
			printf("%d", sort[i].pop[j]);
		}
		printf("\n");
	}
	Sleep(1000);
}

void knapsack::swap(chromosomes &pop, chromosomes &buffer) //버퍼에 있는 것과 실제 사용하는 유전자 서로 바꾸기
{
	chromosomes *temp = &pop;
	pop = buffer;
	buffer = *temp;
}

void knapsack::print(chromosomes &pop)
{
	
	if (pop[0].fitness > maxB) //0번째 들어있는게 가장 fitness가 크도록 정렬했음
	{
		maxB = pop[0].fitness;
	}
	cout << "Max Benefit : " << maxB << endl; //최고의 적응도

	//애니메이션 구현을 위한 부분, 결과만 보기 위해선 주석
	Sleep(1000);
	system("cls");
}

void knapsack::solve(int userInput[][ITEM_COUNT])
{
	chromosomes initPop, initBuffer, *pop, *buffer;

	initPopulation(initPop, initBuffer);//초기화 완료

	pop = &initPop; //한 것의 주소값으로 넘겨줌
	buffer = &initBuffer;//call by reference

	for (int i = 0; i < 100; i++) //과정을 n번 진행
	{
		printf("12121623 정보통신공학과 김정현\n");
		printf("%d세대 - ", i + 1);
		calFitness(*pop, userInput); //userinput 배열에 들어온것과 pop을 통해 적응도 계산
		sortByFitness(*pop);
		print(*pop);
		mate(*pop, *buffer);//교배와 mutate로 생성된 것을
		swap(*pop, *buffer);//여기서 교체
	}
}

int main()
{
	//각 예제에 대해서만 주석을 해제하여 확인
	//예제 1 실행

	/*printf("12121623 정보통신공학과 김정현\n");
	knapsack ks;
	clock_t start = clock();
	ks.solve(u);
	clock_t end = clock();
	double t = (double)(end - start) / CLOCKS_PER_SEC;
	printf("\n소요 시간: %fs.\n", t);
	printf("12121623 정보통신공학과 김정현\n");*/

	//예제 2 실행

	/*printf("12121623 정보통신공학과 김정현\n");
	srand(unsigned(time(NULL)));
	knapsack ks2;
	clock_t start2 = clock();
	ks2.solve(u2);
	clock_t end2 = clock();
	double t2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
	printf("\n소요 시간: %fs.\n", t2);
	printf("12121623 정보통신공학과 김정현\n");*/

	//예제 3 실행
	/*printf("12121623 정보통신공학과 김정현\n");
	srand(unsigned(time(NULL)));
	knapsack ks3;
	clock_t start3 = clock();
	ks3.solve(u3);
	clock_t end3 = clock();
	double t3 = (double)(end3 - start3) / CLOCKS_PER_SEC;
	printf("\n소요 시간: %fs.\n", t3);
	printf("12121623 정보통신공학과 김정현\n");*/

	//예제 4 실행
	/*printf("12121623 정보통신공학과 김정현\n");
	srand(unsigned(time(NULL)));
	knapsack ks4;
	clock_t start4 = clock();
	ks4.solve(u4);
	clock_t end4 = clock();
	double t4 = (double)(end4 - start4) / CLOCKS_PER_SEC;
	printf("\n소요 시간: %fs.\n", t4);
	printf("12121623 정보통신공학과 김정현\n");*/

	//예제 5 실행
	/*printf("12121623 정보통신공학과 김정현\n");
	srand(unsigned(time(NULL)));
	knapsack ks5;
	clock_t start5 = clock();
	ks5.solve(u5);
	clock_t end5 = clock();
	double t5 = (double)(end5 - start5) / CLOCKS_PER_SEC;
	printf("\n소요 시간: %fs.\n", t5);
	printf("12121623 정보통신공학과 김정현\n");*/

	///애니메이션 구현 부분 애니메이션을 보기위해선 이 부분을 주석 해제하고 위의 실행결과 부분을 주석
	//애니메이션 구현(예제 5의 경우임)
	srand(unsigned(time(NULL)));
	knapsack ks5;
	clock_t start5 = clock();
	ks5.solve(u5);
	clock_t end5 = clock();
	double t5 = (double)(end5 - start5) / CLOCKS_PER_SEC;
	printf("12121623 정보통신공학과 김정현\n");

	return 0;
}
