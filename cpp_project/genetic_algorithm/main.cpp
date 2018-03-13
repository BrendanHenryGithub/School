#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define POPSIZE 100
#define CHROMLENGTH 24
#define MaxGeneration 1000000
#define CROSSPERCENT 0.1
#define MUTAPERCENT 0.01
#define LEFTSCOPE -2.048
#define RIGHTSCOPE 2.048

typedef struct {
    int gene[CHROMLENGTH];
    double value1;
    double value2;
    double evaluatesScore;
    double percent;
} GENE;

double TargetFunction(double, double);
void GenerateInitialPopulation(GENE *);
void ResultPrint(int,GENE *);
void EvaluatePopulation(GENE *, GENE *);
void InitialEvaluatePopulation(GENE *,GENE *);
void DecimalValue(GENE *);
void CopyStruct(GENE * ,GENE *);
void GeneCalcul(GENE *);
void GenerateNextPopulation(GENE *);
void CalculPercent(GENE * );
void SelectionOperator(GENE *);
void CrossoverOperator(GENE *);
void MutationOperator(GENE *);

int main(){
    srand(time(NULL));
    GENE Gene[POPSIZE];
    GENE BGene;
    int Generation=0;
    GenerateInitialPopulation(Gene);
    InitialEvaluatePopulation(Gene,&BGene);
    double lastBestScore=0;
    while(Generation<MaxGeneration){
        ++Generation;
        if(BGene.evaluatesScore>lastBestScore){
            ResultPrint(Generation,&BGene);
        }
        GenerateNextPopulation(Gene);
        lastBestScore=BGene.evaluatesScore;
        EvaluatePopulation(Gene,&BGene);
    }
    return 0;
}

void GenerateInitialPopulation(GENE *Gene){
    for (int i=0;i<POPSIZE;++i){
        for (int j=0;j<CHROMLENGTH;++j){
            Gene[i].gene[j]=rand()%2;
        }
    }
}

void CopyStruct(GENE *x,GENE *y){
    (*x).value1=(*y).value1;
    (*x).value2=(*y).value2;
    (*x).evaluatesScore=(*y).evaluatesScore;
    for (int i=0;i<CHROMLENGTH;++i){
        (*x).gene[i]=(*y).gene[i];
    }
}

void GeneCalcul(GENE * Gene){
    int tmpsum1=0;
    int tmpsum2=0;
    double basevalue=pow(2,CHROMLENGTH/2)-1;
    for (int j=0;j<CHROMLENGTH/2;++j){
        if((*Gene).gene[j]!=0){
            tmpsum1+=pow(2,j);
        }
    }
    (*Gene).value1=tmpsum1/basevalue*(RIGHTSCOPE - LEFTSCOPE) + LEFTSCOPE;
    for (int j=CHROMLENGTH/2;j<CHROMLENGTH;++j){
        if((*Gene).gene[j]!=0){
            tmpsum2+=pow(2,j-CHROMLENGTH/2);
        }
    }
    (*Gene).value2=tmpsum2/basevalue*(RIGHTSCOPE - LEFTSCOPE) + LEFTSCOPE;
}

double TargetFunction(double x1,double x2){
    return 100*(x1*x1-x2)*(x1*x1-x2)+(1-x1)*(1-x1);
}

void InitialEvaluatePopulation(GENE *Gene,GENE *BGene){
    for (int i=0;i<POPSIZE;++i){
        GeneCalcul(&Gene[i]);
        Gene[i].evaluatesScore=TargetFunction(Gene[i].value1,Gene[i].value2);
    }
    CopyStruct(BGene,&Gene[0]);
    for (int i=1;i<POPSIZE;++i){
        if((*BGene).evaluatesScore<Gene[i].evaluatesScore){
            CopyStruct(BGene,&Gene[i]);
        }
    }
}

void EvaluatePopulation(GENE *Gene,GENE *BGene){
    for (int i=0;i<POPSIZE;++i){
        GeneCalcul(&Gene[i]);
        Gene[i].evaluatesScore=TargetFunction(Gene[i].value1,Gene[i].value2);
    }
    for (int i=0;i<POPSIZE;++i){
        if((*BGene).evaluatesScore<Gene[i].evaluatesScore){
            CopyStruct(BGene,&Gene[i]);
        }
    }
}

void GenerateNextPopulation(GENE * Gene){
    SelectionOperator(Gene);
    CrossoverOperator(Gene);
    MutationOperator(Gene);
}

void CalculPercent(GENE * Gene){
    double sum=0;
    for (int i=0;i<POPSIZE;++i){
        sum+=Gene[i].evaluatesScore;
    }
    for (int i=0;i<POPSIZE;++i){
        Gene[i].percent=Gene[i].evaluatesScore/sum;
    }
}

void SelectionOperator(GENE * Gene){
    CalculPercent(Gene);
    GENE Genetmp[POPSIZE];
    for (int i=0;i<POPSIZE;++i){
        double randvalue=rand()*1.0/RAND_MAX;
        double tmpsum=0;
        for(int j=0;j<POPSIZE;++j){
            if(tmpsum<randvalue){
                tmpsum+=Gene[j].percent;
            }
            else{
                CopyStruct(&Genetmp[i],&Gene[j]);
                break;
            }
        }
    }
    for (int i=0;i<POPSIZE;++i){
        CopyStruct(&Gene[i],&Genetmp[i]);
    }
}

void CrossoverOperator(GENE * Gene){
    int tmp;
    for (int i=0;i<POPSIZE-1;i+=2){
        if (rand()*1.0/RAND_MAX < CROSSPERCENT){
            int randvalue=rand()%CHROMLENGTH;
            for (int j=randvalue;j<CHROMLENGTH;++j){
                tmp=Gene[i].gene[j];
                Gene[i].gene[j]=Gene[i+1].gene[j];
                Gene[i+1].gene[j]=tmp;
            }
        }
    }
}

void MutationOperator(GENE * Gene){
    for (int i=0;i<POPSIZE;++i){
        for (int j=0;j<CHROMLENGTH;++j){
            if(rand()*1.0/RAND_MAX < MUTAPERCENT){
                if(Gene[i].gene[j]==0){
                    Gene[i].gene[j]=1;
                }
                else{
                    Gene[i].gene[j]=0;
                }
            }
        }
    }
}

void ResultPrint(int Generation, GENE *BGene){
    printf("在第%d代找到一个新的最优解：x1=%lf, x2=%lf, 目标函数取值为:%lf\n",
        Generation,(*BGene).value1,(*BGene).value2,(*BGene).evaluatesScore);
}
