#include <iostream>
#include <cmath>
using namespace std;

int main() {
	float biggestCoeff = 0, biggestPowerCoeff;
	int degreeOfEqu, size, numOfRoots, iterations, FPIOrNR;

	cout << "For FPI Enter 0 For NR Enter 1 : "; cin >> FPIOrNR; 	
	cout << "\nEnter Degree of Equation : "; cin >> degreeOfEqu; 
	cout << "\nEnter Number of Roots : "; cin >> numOfRoots; 
	cout << "\nEnter Number Iterations : "; cin >> iterations; 
	
	int intervalArray[2*numOfRoots];
	size = degreeOfEqu+1;
	
	float coeff[size], domain;
	
	int equFormat[size];
	for(int i = degreeOfEqu; i >= 0; i--){
		cout << "\nEnter Coeffecient X^" << i << " : "; cin >> coeff[i];
		
		equFormat[i] = coeff[i];
		if(biggestCoeff < abs(coeff[i]))
			biggestCoeff = abs(coeff[i]);
				
	}
	biggestPowerCoeff = coeff[degreeOfEqu];
	cout << "\n\nBiggest Coefficient : " << biggestCoeff << endl << "\nBiggest Power Coefficient : " << biggestPowerCoeff << endl;
	
	domain = 1 + (biggestCoeff/biggestPowerCoeff);
	cout << "-" << domain << " <= Xr <= " << domain << endl;
	
	int numOfInterval = 0, z = 0, validRoot = 0, intervalArr[2*numOfRoots];
	float result[2];
	int y = 1;
	while(validRoot != numOfRoots){
		
		for(int i = 0; i <= degreeOfEqu; i++){
			if(i == 0){
				result[z] += coeff[i];
			}else{
				result[z] += coeff[i]*pow(numOfInterval, i);	
			}
		}
		
		if(z != 0){
			if( (result[0] < 0 && result[1] > 0) || (result[0] > 0 && result[1] < 0) ){
				validRoot++;
				
				intervalArr[y-1] = numOfInterval-1;
				intervalArr[y] = numOfInterval;
				y++;
				
				cout << "\n\n" <<result[0] << endl << result[1];		
				result[0] = 0;  result[1] = 0;
				z = 0;
				continue;
			}
			else{
				//16-7 = 9 example 2 in exercise
				//Gives Error if there's invalid root 
				result[0] = result[1];	
			}
			
		}
						
		numOfInterval++; z = 1;
	}
	
	for(int j = 0;j < numOfRoots;j++){
	 	cout << "\n\nInterval Array "<< j << " : " << intervalArr[j] << ", " << intervalArr[j+1] << endl;
	}
	
	cout << "\n";
	float xVal;
	float passInterval = intervalArr[0];
	if(FPIOrNR == 0){
		//Fixed Point
		for(int iterationsNum = 0; iterationsNum < iterations; iterationsNum++){
			xVal = 0;
			for(int v = 0; v < size; v++){
				if(v != 1){
					xVal = xVal - (coeff[v] * pow(passInterval, v));
				}
			}	
			xVal = xVal / coeff[1];
			cout << "X "<< iterationsNum <<" = " << 	xVal << endl;
			passInterval = xVal;
		}
	}else{
		//Newton-Raphson
		//Derivative
		int coeffFirstDerivative[size], coeffSecondDerivative[size];
		for(int p = 1; p <= 2; p++){
			for(int c = 1; c <= degreeOfEqu; c++){
				if(p == 1)
					coeffFirstDerivative[c-1] = coeff[c]*(c);
				else if(p == 2)
					coeffSecondDerivative[c-1] = coeffFirstDerivative[c]*(c);			
			}
		}
		
		cout << "\nOrignal Equation";
		for(int xm = 0 ; xm < size ; xm++){
			cout << "\n\n X ^ " << xm << " = "<< coeff[xm] << endl;
		}
		
		cout << "\nFirst Derivative";
		for(int xm = 0 ; xm < size ; xm++){
			cout << "\n\n X ^ " << xm << " = "<< coeffFirstDerivative[xm] << endl;
		}
		
		cout << "\nSecond Derivative";
		for(int xm = 0 ; xm < size ; xm++){
			cout << "\n\n X ^ " << xm << " = "<< coeffSecondDerivative[xm] << endl;
		}
		
		xVal = 0;
		float Row = 0, Column = 0, Orginal = 0, FirstDeri = 0, SecondDeri = 0;
		bool flag = true;
		cout << "\n\n>>>TABLE<<<";
		for(int iterationsNum = 0; iterationsNum < iterations; iterationsNum++){
			Orginal = 0, FirstDeri = 0, SecondDeri = 0;
			if(flag){
				//Columns
				for(int p = 0; p <= 4; p++){
					switch(p){
						case 0:
							xVal = 0;
							for(int v = 0; v < size; v++){
								xVal = xVal + (coeff[v] * pow(passInterval, v));
							}
							cout << "\nRow = " << Row << "  ,Column = " << Column << " Value = " << xVal;
							Column++;
							Orginal = xVal;
							break;	
						
						case 1:
							xVal = 0;
							for(int v = 0; v < size; v++){
								xVal = xVal + (coeffFirstDerivative[v] * pow(passInterval, v));
							}
							cout << "\nRow = " << Row << "  ,Column = " << Column << " Value = " << xVal;
							Column++;
							FirstDeri = xVal;
							break;	
						
						case 2:	
							xVal = 0;
							for(int v = 0; v < size; v++){
								xVal = xVal + (coeffSecondDerivative[v] * pow(passInterval, v));
							}
							cout << "\nRow = " << Row << "  ,Column = " << Column << " Value = " << xVal;
							Column++;
							SecondDeri = xVal;		
							break;	
						case 3:
							if( (abs(Orginal * SecondDeri)) < (pow(FirstDeri, 2)) ){
								flag = true;
								cout << "\nRow = " << Row << "  ,Column = " << Column << " Yes";
							}else{
								flag = false;
								cout << "\nRow = " << Row << "  ,Column = " << Column << " No";
							break;
						case 4:
							xVal = 0;
							xVal = xVal + (passInterval - Orginal/FirstDeri);
							cout << "\nRow = " << Row << "  ,Column = " << Column << " Value = " << xVal;
						}	
					}
				}
				cout << "\n";
				passInterval = xVal;
				Row++;
			}
		}
	}	
	return 0;
}









