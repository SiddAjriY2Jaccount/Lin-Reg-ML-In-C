#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define maxclose 2061.15
#define minclose 1861.7

float denormalizey(float y, float meany)
{
  return ((y*(maxclose-minclose))+meany);
}

float normalizey(float y, float meany)
{
  return (y-meany)/(maxclose - minclose);
}

void plot(float m2, float b2) {
  FILE * gnuplot = popen("gnuplot -p","w");
  //fprintf(gnuplot, "ls(x) = (%lf)*x + %lf\n",m2,b2);
  fprintf(gnuplot, "close(x) = (%lf)*x + %lf\n",m2,b2);
  fprintf(gnuplot, "plot \"dataPlot.txt\" u 1:2 w l , close(x)\n");
  fflush(gnuplot);
  fclose(gnuplot);
}

void regression(float y[], int n, int xtest, float ytest)
{
    int epochs = 0;
    float alpha=0.001;
    double theta_0, theta_1, h, predicted, error, errorSum, errorTimesxSum, meansqerror;

    FILE *fptr;

    fptr = fopen("errorplotcpse.txt", "w");

    theta_0 = 0.1;
    theta_1 = 0.1;

    //double xnorm[20];
    //double ynorm[20];

    double meanx = 0.0;
    double meany = 0.0;

    for(int k1 = 0; k1<n; k1++)
    {
      meanx += k1;
    }
    meanx = meanx/n;

    for(int k1 = 0; k1<n; k1++)
    {
      meany += y[k1];
    }
    meany = meany/n;

    printf("\nMean X : %f",meanx);
    //printf("%f\n", normalize(x[1], meanx));

    while(epochs<2500)
    {
        int i;
        meansqerror = 0.0;
        errorSum = 0.0;
        errorTimesxSum = 0.0;
        float errorJ;
/*
        for(i = 0; i<n; i++)
        {
          xnorm[i] = normalize(x[i], meanx);
          //ynorm[i] = normalize(y[i], meany, 2);

        }
*/
        for (i=0; i<n; i++)
        {
            h = theta_0 + theta_1*i;
            error = h - normalizey(y[i],meany);
            errorSum += error;
            errorTimesxSum += error*i;
            meansqerror += error*error;
        }
        printf("Error is %f\n",((1/(2.0*n))*meansqerror));
        ///
        errorJ = ((1/(2.0*n))*meansqerror);

        if(fptr == NULL)
        {
          printf("Error!");
          exit(1);
        }

        fprintf(fptr,"%d\t%f\n", epochs, errorJ);
        //fclose(fptr);
        //printf("\nSum of errors is : %d",errorSum);
        //printf("\nSum of errors into x is : %d",errorTimesxSum);
        theta_0 -= alpha*errorSum/n;
        theta_1 -= alpha*errorTimesxSum/n;
        epochs++;
    }
    //fclose(fptr);

    predicted = theta_0 + theta_1*xtest;
    //printf("\nPred b4 norm is : %f", predicted);
    predicted = denormalizey(predicted, meany);
    printf("\nTheta-0 value is : %f", (theta_0) );
    printf("\nTheta-1 value is : %f", (theta_1) );
    printf("\nPredicted value is : %f", predicted);
    printf("\nActual value is : %f", ytest);
    plot(theta_1, theta_0);
}


void main()
{
  float close[40] = {2061.15, 2038.95, 2004.1, 2031.65, 2039.75, 2038.65, 2024.15, 2018.35, 2025.3, 2013.55, 2030.5, 2033.9, 2031.5, 2028.2, 2006.0, 1996.25, 1981.45, 1977.1, 1965.55, 1967.7, 1966.2, 1963.9, 1977.3, 1981.8, 1970.1, 1937.6, 1968.8, 1987.05, 1932.55, 1910.8, 1925.85, 1886.2, 1861.7, 1896.8, 1895.25, 1901.1, 1944.1, 1954.95, 1996.3, 1998.9};
  int n1 = 38;
  int xtest = 39;
  float ytest = close[39];
  regression(close, n1, xtest, ytest);
}
