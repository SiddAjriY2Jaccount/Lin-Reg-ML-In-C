#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define maxclose 4040.95
#define minclose 3618.10
#define maxturnover 8510.50
#define minturnover 4121.30


float denormalizex(float x, float meanx)
{
  return ((x*(maxclose-minclose))+meanx);
}

float normalizex(float x, float meanx)
{
  return (x-meanx)/(maxclose - minclose);
}

float denormalizey(float y, float meany)
{
  return ((y*(maxturnover-minturnover))+meany);
}

float normalizey(float y, float meany)
{
  return (y-meany)/(maxturnover - minturnover);
}

void regression(float x[], float y[], int n, float xtest, float ytest)
{
    int epochs = 0;
    float alpha=0.0001;
    double theta_0, theta_1, h, predicted, error, errorSum, errorTimesxSum, meansqerror;

    theta_0 = 0.1;
    theta_1 = 0.1;

    //double xnorm[20];
    //double ynorm[20];

    double meanx = 0.0;
    double meany = 0.0;

    for(int k1 = 0; k1<n; k1++)
    {
      meanx += x[k1];
    }
    meanx = meanx/n;

    for(int k1 = 0; k1<n; k1++)
    {
      meany += y[k1];
    }
    meany = meany/n;

    printf("\nMean X : %f",meanx);
    //printf("%f\n", normalize(x[1], meanx));

    while(epochs<250000)
    {
        int i;
        meansqerror = 0.0;
        errorSum = 0.0;
        errorTimesxSum = 0.0;
/*
        for(i = 0; i<n; i++)
        {
          xnorm[i] = normalize(x[i], meanx);
          //ynorm[i] = normalize(y[i], meany, 2);

        }
*/
        for (i=0; i<n; i++)
        {
            h = theta_0 + theta_1*normalizex(x[i],meanx);
            error = h - normalizey(y[i],meany);
            errorSum += error;
            errorTimesxSum += error*normalizex(x[i],meanx);
            meansqerror += error*error;
        }
        printf("Error is %f\n",((1/(2.0*n))*meansqerror));
        //printf("\nSum of errors is : %d",errorSum);
        //printf("\nSum of errors into x is : %d",errorTimesxSum);
        theta_0 -= alpha*errorSum/n;
        theta_1 -= alpha*errorTimesxSum/n;
        epochs++;
    }

    predicted = theta_0 + theta_1*(normalizex(xtest,meanx));
    printf("\nPred b4 norm is : %f", predicted);
    predicted = denormalizey(predicted, meany);
    printf("\nTheta-0 value is : %f", (theta_0) );
    printf("\nTheta-1 value is : %f", (theta_1) );
    printf("\nPredicted value is : %f", predicted);
    printf("\nActual value is : %f", ytest);

}
void main()
{
  float close[20] = {4015.5, 4040.95, 3964.5, 3797.45, 3787.6, 3792.9, 3913.8, 3774.45, 3861.2, 3884.95, 3917.25, 3768.4, 3723.85, 3706.6, 3659.95, 3730.85, 3645.0, 3618.1, 3767.55, 3750.2};
  float xtest = 3809.2; // for given close
  float turnover[20] = {8024.6, 8459.9, 6805.32, 6857.09, 7628.59, 8237.99, 7495.88, 8510.5, 5944.15, 4121.3, 4832.02, 5646.27, 7667.49, 6034.44, 6340.0, 7284.36, 7063.9, 6433.88, 5360.77, 4699.12};
  float ytest = 6567.89; //turnover to be predicted
  int n1 = 20;
  regression(close, turnover, n1, xtest, ytest);
}
