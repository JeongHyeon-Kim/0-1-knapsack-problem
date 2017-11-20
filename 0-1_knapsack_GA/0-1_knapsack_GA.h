#ifndef KNAPSACK_H
#define KNAPSACK_H
#include <vector>
#include <random>

#define CROSS_OVER_RATE 0.8 //교배 확률
#define POP_SIZE 10 //개체군 크기

//각 예제에 대해서만 주석을 해제하여 확인
//예제 1행렬
//#define ITEM_COUNT 3
//#define BAG_WEIGHT 10
//int u[2][ITEM_COUNT] = {
//	{ 4, 1, 11 },//무게
//	{ 10, 1, 100 }//가치
//};

//예제 2행렬
//#define ITEM_COUNT 4
//#define BAG_WEIGHT 5
//int u2[2][ITEM_COUNT] = {
//	{ 2, 3, 4, 5 }, //무게
//	{ 3, 4, 5, 6 } //가치
//};

//예제 3행렬
//#define ITEM_COUNT 5
//#define BAG_WEIGHT 20
//int u3[2][ITEM_COUNT] = {
//	{ 2 , 7 , 1 , 4 , 1 }, //무게
//	{ 5 , 3 , 2 , 9 , 6 }//가치
//};

//예제 4행렬
//#define ITEM_COUNT 6
//#define BAG_WEIGHT 10
//int u4[2][ITEM_COUNT] = {
//	{ 4, 5, 3, 7, 8, 6 }, //무게
//	{ 3, 5, 4, 3, 10, 5 }//가치
//};

//예제 5행렬
#define ITEM_COUNT 7
#define BAG_WEIGHT 20
int u5[2][ITEM_COUNT] = {
	{ 5, 4, 8, 5, 6, 6, 7 }, //무게
	{ 6, 2, 7, 4, 5, 3, 9 }//가치
};

using namespace std;
class knapsack
{
public:
	struct population
	{
		int fitness; //적응도=가치
		int weight; //무게 저장
		int pop[ITEM_COUNT]; //유전자 인코딩
	};
public:
	knapsack();
	void initPopulation(vector<population> &pop, vector<knapsack::population> &initBuffer);//초기화 함수
	void calFitness(vector<population> &pop, int userInput[][ITEM_COUNT]);//적응도 계산 함수
	void sortByFitness(vector<population> &sort);//적응도 순으로 정렬하는 함수(elitism효과)
	void mate(vector<population> &mate1, vector<population> &mate2);//교배를 위한 ㅎ마수
	void copyNewGeneration(vector<population> &copyFrom, vector<population> &copyTo);//다음 세대로 가기위해 복사하는 함수
	void mutate(vector<population> &mutate, vector<population> &buffer);//돌연변이를 생성하는 함수
	void swap(vector<knapsack::population> &pop, vector<knapsack::population> &buffer);//buffer와 pop내용을 서로 치환
	int randGenerate(int rand_num);//랜덤 숫자 생성 함수
	void print(vector<knapsack::population> &pop); //출력 함수
	bool fitness_sort(const population & x, const population & y); //유전자를 적응도 순으로 정렬
	void solve(int userInput[][ITEM_COUNT]);

private:
	int popSize; //유전자의 갯수
	int maxB; //최대 가치 저장
	int bagWeight; //가방 무게
};
#endif
