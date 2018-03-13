// 遗传算法.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<time.h>
#include<stdlib.h>
#include"math.h"

#define POPSIZE 500 //种群的大小
#define CHROMLENGTH 24	//染色体的长度

struct individual{
	int chrom[CHROMLENGTH]; /*染色体*/
	double fitness;/*适应值*/
	double nfitness;//归一化的适应值
};

struct individual population[POPSIZE];
struct individual temppopulation[POPSIZE];
struct individual bestchrom;//最好的染色体

int MaxGeneration =200; //最大进化代数
double Pc=0.6; //交叉概率
double Pm=0.001; //变异概率

int Generation;
void GeneratelnitialPopulation(){
	//产生初始化的种群，也就是随机生成0,1串
	for(int i=0;i<=POPSIZE;++i){
		for(int j=0;j<CHROMLENGTH;++j){
			population[i].chrom[j]=rand()%2;
		}
	}
	bestchrom.fitness=-1e10;

}
void EvaluatePopulation(){
	//评估染色体的适应值
	for(int index=0;index<POPSIZE;++index){
		double basevalue=pow(2.0,CHROMLENGTH/2)-1;//2^N-1
		double sum=0;//表示二进制代表的十进制整数值
		for(int i=0;i<CHROMLENGTH/2;++i){
			sum+=population[0].chrom[i]*pow(2.0,i);
		}
		double x1=sum/basevalue*(2.048-(-2.048))+(-2.048);
		//x1是指定范围内的实数值
		sum=0;
		for(int i=0;i<CHROMLENGTH/2;++i){
			sum+=population[0].chrom[i+CHROMLENGTH/2]*pow(2.0,i);
		}
		double x2=sum/basevalue*(2.048-(-2.048))+(-2.048);
		population[0].fitness=100*(x1*x1-x2)*(x1*x1-x2)+(1-x1)*(1-x1);
		if(population[index].fitness>bestchrom.fitness){
		bestchrom=population[index];
		printf("发现了一个更好的解：%f\n",bestchrom.fitness);
		}
	}
}
void SelectionOperator(){
	//利用轮盘赌来产生新的一代
	//第一步，对数据进行归一化
	double sum=0;
	for(int i=0;i<POPSIZE;++i){
	sum+=population[i].fitness;
	}
	for(int i=0;i<POPSIZE;++i){
		population[i].nfitness=population[i].fitness/sum;
	}
	//第二步，累加选择
	for(int index=0;index<POPSIZE;++index){
	double p=rand()*1.0/RAND_MAX;
	sum=0;
	int i;
	for(i=0;i<POPSIZE;++i){
		sum+=population[i].nfitness;
	if(sum>=p)
	break;
	}
	temppopulation[index]=population[i];
	}
	//第三步，把所有的临时种群中的值赋值回去
	for(int i=0;i<POPSIZE;++i){
	population[i]=temppopulation[i];
	}
}
void CrossoverOperator(){
	//交叉操作，使用单点交叉
	for(int index=0;index<POPSIZE;index+=2){
	//第一步，判断这一对需不需要交叉
	double p=rand()*1.0/RAND_MAX;
	if(p<Pc){
		//第二步，如果需要交叉，则互换随机位置pos之前的所有基因的值
	int pos=rand()%CHROMLENGTH;
	int temp;
	for(int i=0;i<pos;++i){
		temp=population[index].chrom[i];
		population[index].chrom[i]=population[index+1].chrom[i];
		population[index+1].chrom[i]=temp;
	}
	}
	}
}
void MutationOperator(){
	//变异操作
	for(int index=0;index<POPSIZE;++index){
	double p=rand()*1.0/RAND_MAX;
	if(p<Pm){
	int pos=rand()%CHROMLENGTH;
	if(population[index].chrom[pos]==0){
		population[index].chrom[pos]=1;
	}
	else{
		population[index].chrom[pos]==0;
	}
	}
	}
}
void GenerateNextPopulation(){
	SelectionOperator();	//选择算子
CrossoverOperator();	//交叉算子
MutationOperator();	//变异算子

}

int _tmain(int argc, _TCHAR* argv[])
{
	srand((int)time(0));
	Generation=0;//第0代的标志
	GeneratelnitialPopulation();//初始化种群
	EvaluatePopulation();//评估种群
	while(Generation<MaxGeneration){
		Generation++;
		GenerateNextPopulation();//产生下一代
		EvaluatePopulation();
		printf("算法运行到第%d代，发现的最好值是：%f\n",Generation,bestchrom.fitness);
	}
	return 0;
}

