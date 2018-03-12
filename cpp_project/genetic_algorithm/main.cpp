#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define MaxGeneration 100

void TargetFunction(GENE *);
void GenerateInitialPopulation(GENE *);
void TestPrint(GENE *,GENE *);
void EvaluatePopulation(GENE *, GENE *);
void DecimalValue(GENE *);
void CopyStruct(GENE * ,GENE *);
void GeneCalcul(GENE *);
void GenerateNextPopulation(GENE *);


typedef struct {
    int gene[8];
    double value1;
    double value2;
    double evaluatesScore;
} GENE;

int main(){
    srand(time(NULL));
    GENE Gene[4];
    GENE BGene;
    int Generation=0;
    GenerateInitialPopulation(Gene);
    EvaluatePopulation(Gene,&BGene);
    /**while(Generation<MaxGeneration){
        ++Generation;
        GenerateNextPopulation();
        EvaluatePopulation();
    }**/
    TestPrint(Gene,&BGene);
    return 0;
}

void GenerateNextPopulation(GENE * Gene){
    
}

void GeneCalcul(GENE * Gene){
    int tmpsum1=0;
    int tmpsum2=0;
    for (int j=0;j<4;++j){
        if((*Gene).gene[j]!=0){
            tmpsum1+=pow(2,j);
        }
    }
    // printf("tmpsum1:%d\n",tmpsum1);
    (*Gene).value1=tmpsum1/15.0*(2.047+2.048) - 2.048;
    for (int j=4;j<8;++j){
        if((*Gene).gene[j]!=0){
            tmpsum2+=pow(2,j-4);
        }
    }
    // printf("tmpsum2:%d\n",tmpsum2);
    (*Gene).value2=tmpsum2/15.0*(2.047+2.048) - 2.048;
}

void CopyStruct(GENE *x,GENE *y){
    (*x).evaluatesScore=(*y).evaluatesScore;
    (*x).value1=(*y).value1;
    (*x).value2=(*y).value2;
    for (int i=0;i<4;++i){
        (*x).gene[i]=(*y).gene[i];
    }
}

void EvaluatePopulation(GENE *Gene,GENE *BGene){
    for (int i=0;i<4;++i){
        // int tmpsum1=0;
        // int tmpsum2=0;
        // for (int j=0;j<4;++j){
        //     if(Gene[i].gene[j]!=0){
        //         tmpsum1+=pow(2,j);
        //     }
        // }
        // printf("tmpsum1:%d\n",tmpsum1);
        // Gene[i].value1=tmpsum1/15.0*(2.047+2.048) - 2.048;
        // for (int j=4;j<8;++j){
        //     if(Gene[i].gene[j]!=0){
        //         tmpsum2+=pow(2,j-4);
        //     }
        // }
        // printf("tmpsum2:%d\n",tmpsum2);
        // Gene[i].value2=tmpsum2/15.0*(2.047+2.048) - 2.048;
        GeneCalcul(&Gene[i]);
        Gene[i].evaluatesScore=TargetFunction(Gene[i].value1,Gene[i].value2);
    }
    // (*BGene).evaluatesScore=Gene[0].evaluatesScore;
    // for (int j=0;j<8;++j){
    //     (*BGene).gene[j]=Gene[0].gene[j];
    // }
    // (*BGene).value1=Gene[0].value1;
    // (*BGene).value2=Gene[0].value2;
    CopyStruct(BGene,&Gene[0]);
    for (int i=1;i<4;++i){
        if((*BGene).evaluatesScore<Gene[i].evaluatesScore){
            // (*BGene).evaluatesScore=Gene[i].evaluatesScore;
            // for (int j=0;j<8;++j){
            //     (*BGene).gene[j]=Gene[0].gene[j];
            // }
            // (*BGene).value1=Gene[i].value1;
            // (*BGene).value2=Gene[i].value2;
            CopyStruct(&BGene,&Gene[i]);
        }
    }
}

void TargetFunction(GENE *Gene){
    x=(*Gene).value1;
    y-(*Gene).value2;
    (*Gene).evaluatesScore=100*pow((x*x+y*y),2)+pow((1-x),2);
}

void GenerateInitialPopulation(GENE *Gene){
    for (int i=0;i<4;++i){
        for (int j=0;j<8;++j){
            Gene[i].gene[j]=rand()%2;
        }
    }
}

void TestPrint(GENE *Gene , GENE *BGene){
    for (int i=0;i<4;++i){
        for (int j=0;j<8;++j){
            printf("%d",Gene[i].gene[j]);
        }
        printf("\n");
    }
    for (int j=0;j<8;++j){
        printf("%d",(*BGene).gene[j]);
    }
    printf("\n");
    printf("%f\n",(*BGene).evaluatesScore);
    printf("%d\n",(*BGene).value1);
}
