#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

void coefficientCalculation(int, double*, double*, double*, double*);
int removeDuplicatePoints(int, double*, double*);

int main() {
    // Variables' Declaration
    int numPoints = 0;
    double *vecX, *vecY, coefA, coefB;

    // Read the total number of points and make sure is a positive number
    printf("Insert the number of points of the set: ");
    while (numPoints <= 0) {
        scanf("%d", &numPoints);
        if (numPoints <= 0) {
          printf("The number introduced is not a positive number\n");
        }
    }
    if (numPoints == 1) {
      printf("With only one point we can't solve this problem\n");
      return 0;
    }
    
    // Allocate memory for the vectors of points
    vecX = (double*)malloc(numPoints*sizeof(double));
    vecY = (double*)malloc(numPoints*sizeof(double));
    if (vecX == NULL || vecY == NULL) {
      printf("Memory error... Shutting down the program.\n");
      return 0;
    }

    // Read the x coordinates of the points and make sure there are different values
    printf("Now, introduce the x coordinate of each of the %d points:\n", numPoints);
    bool rep = true;
    for (int i=0; i<numPoints; i++) {
      scanf("%lf", &vecX[i]);
      if (i > 0 && vecX[i] != vecX[i-1]) {
        rep = false;
      }
    }
    // If all the values are the same, the line is vertical and E(a, b) = 0
    if (rep) {
      printf("The x values are all the same, so the line that we're looking for is vertical and E(a, b)=0\n");
      return 0;
    }

    // Read the y coordinates of the points
    printf("Now, introduce the y coordinate of each of the %d points:\n", numPoints);
    for (int i=0; i<numPoints; i++) {
      scanf("%lf", &vecY[i]);
    }

    // Check for duplicates
    printf("Let's print the points:\n");
    for (int k=0; k<numPoints; k++) {
      printf("(%.2lf, %.2lf)\n", vecX[k], vecY[k]);
    }
    printf("\n");
    numPoints = removeDuplicatePoints(numPoints, vecX, vecY);

    printf("Let's print the points again without duplicates:\n");
    for (int k=0; k<numPoints; k++) {
      printf("(%.2lf, %.2lf)\n", vecX[k], vecY[k]);
    }

    // Let's solve the equation system
    coefficientCalculation(numPoints, vecX, vecY, &coefA, &coefB);

    // Let's calculate the residual value of the line    
    double residualValue = 0;
    for (int i=0; i<numPoints; i++) {
      residualValue += (vecY[i] - coefA - coefB*vecX[i])*(vecY[i] - coefA - coefB*vecX[i]);
    }
    residualValue = sqrt(residualValue);

    // Print the results
    printf("Number of different points: %d\n", numPoints);
    printf("Best approximation line: y = (%.2lf) + (%.2lf)x\n", coefA, coefB);
    printf("Minimal residual value: E = %e\n", residualValue);

    // Let's free the space
    free(vecY);
    free(vecX);
    return 0;
}

void coefficientCalculation(int numPoints, double *vecX, double *vecY, double *coefA, double *coefB) {
  // Let's calculate the terms that we'll need
  double sumVecX = 0., sumVecY = 0., sumXtimesY = 0., sumSquareX = 0.;
  for (int i=0; i<numPoints; i++) {
    sumVecX += vecX[i];
    sumVecY += vecY[i];
    sumXtimesY += vecX[i]*vecY[i];
    sumSquareX += vecX[i]*vecX[i];
  }

  *coefB = (numPoints*sumXtimesY - sumVecX*sumVecY)/(numPoints*sumSquareX - sumVecX*sumVecX);
  *coefA = (sumVecY - *coefB*sumVecX)/numPoints;
}

int removeDuplicatePoints(int numPoints, double *vecX, double *vecY) {
  if (numPoints == 1) return 1;
  int newNumPoints = numPoints;
  for (int i=0; i<newNumPoints; i++) {
    for (int j=i-1; j>=0; j--) {
      if (vecX[i] == vecX[j] && vecY[i] == vecY[j]) {
        if (i < newNumPoints-1) {
          double temp = vecX[i];
          vecX[i] = vecX[newNumPoints-1];
          vecX[newNumPoints-1] = temp;
          temp = vecY[i];
          vecY[i] = vecY[newNumPoints-1];
          vecY[newNumPoints-1] = temp;
          i--;
        }        
        newNumPoints--;
        break;
      }
    }    
  }
  return newNumPoints;
}
