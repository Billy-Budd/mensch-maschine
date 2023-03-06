/* the-model.cpp
 * JML190001 - John Lawler
 * CS4375.004 Project Three
 * 03/06/23
 * Program is largely based on das-model-linreg.cpp and uses many of the same functions.
 * This uses naive bayes to predict survivability on age, sex, and pclass.
 */
#define _USE_MATH_DEFINES // purely used for pi constant
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <cmath>
#include <cstdlib>
using namespace std;

// by convention, constants are global variables
const int MAXLEN = 10000;
const double e = exp(1);
const double pi = M_PI;
const double LEARNRATE = 0.001;

double calculateModel(double, double, int);
double calculateError(int, double);
double calculateSigmoid(double);
double calculateBias(double, double);
double calculateCoefficient(double, double, int);
double calculateAccuracy(double, int);
double divide(double, double);
double survivalCalc(double, double, double, double);
double sumVector(vector<int>); 
double meanVector(vector<int>);
double sumVector(vector<double>);
double meanVector(vector<double>);
double variance(vector<double>);
double calculateLikelihood(double, double, double);

int main(int argc, char** argv) {

	// elements to create vectors from Boston.csv
	ifstream inFS;

	// attempt to open csv, return error 1 if failure
	string fileName = "titanic_project.csv";
	cout << "Opening file " << fileName << endl;
	inFS.open(fileName);
	if (!inFS.is_open()) {
		cout << "Could not open file " << fileName << endl;
		return 1;
	}

	int trainSize = 800;

	vector<int> IDTrain(MAXLEN);			string IDIn;		// vector to hold all of the ID nums, string to hold current line val
	vector<int> pclassTrain(MAXLEN);		string pclassIn;	// vector to hold all pasenger class data, string to hold current line val
	vector<int> survivedTrain(MAXLEN);		string survivedIn;	// vector to hold bool survived data, string to hold current line val
	vector<int> sexTrain(MAXLEN);			string sexIn;		// vector to hold sex data, string to hold current line val
	vector<double> ageTrain(MAXLEN);		string ageIn;		// vector to hold age data, string to hold current line val

	vector<int> IDTest(MAXLEN);
	vector<int> pclassTest(MAXLEN);
	vector<int> survivedTest(MAXLEN);
	vector<int> sexTest(MAXLEN);
	vector<double> ageTest(MAXLEN);

	string currentLine;									// current line for reading in csv
	getline(inFS, currentLine);							// get headers
	cout << "Heading: " << currentLine << endl;			// display headers
	int numObservations = 0;							// number of observations
	
	// get data from ifstream
	while (inFS.good()) {

		if (numObservations < trainSize) {
			// cannot parse for some reason, leaving as string
			getline(inFS, IDIn, ',');

			// get pclass and parse to int
			getline(inFS, pclassIn, ',');
			pclassTrain.at(numObservations) = stoi(pclassIn);

			// get survived and parse to int
			getline(inFS, survivedIn, ',');
			survivedTrain.at(numObservations) = stoi(survivedIn);

			// get sex and parse to int
			getline(inFS, sexIn, ',');
			sexTrain.at(numObservations) = stoi(sexIn);

			// get age and parse to double, there are fractional ages so double instead of int
			getline(inFS, ageIn, '\n');
			ageTrain.at(numObservations) = stod(ageIn);
		}

		else {
			// cannot parse for some reason, leaving as string
			getline(inFS, IDIn, ',');

			// get pclass and parse to int
			getline(inFS, pclassIn, ',');
			pclassTest.at(numObservations - trainSize) = stoi(pclassIn);

			// get survived and parse to int
			getline(inFS, survivedIn, ',');
			survivedTest.at(numObservations - trainSize) = stoi(survivedIn);

			// get sex and parse to int
			getline(inFS, sexIn, ',');
			sexTest.at(numObservations - trainSize) = stoi(sexIn);

			// get age and parse to double, there are fractional ages so double instead of int
			getline(inFS, ageIn, '\n');
			ageTest.at(numObservations - trainSize) = stod(ageIn);
		}
		

		numObservations++;
	}

	// close file when done
	cout << "Closing file " << fileName << "." << endl;
	inFS.close();

	cout << "Number of records read from " << fileName << ": " << numObservations << endl;

	// resize vectors to free up space
	IDTrain.resize(trainSize);
	pclassTrain.resize(trainSize);
	survivedTrain.resize(trainSize);
	sexTrain.resize(trainSize);
	ageTrain.resize(trainSize);

	IDTest.resize(numObservations - trainSize);
	pclassTest.resize(numObservations - trainSize);
	survivedTest.resize(numObservations - trainSize);
	sexTest.resize(numObservations - trainSize);
	ageTest.resize(numObservations - trainSize);

	double livedPercent = meanVector(survivedTrain), diedPercent = 1 - livedPercent;
	double numberOfSex0 = 0, numberOfSex1 = 0, 
		sex0Lived = 0, sex1Lived = 0,
		numberOfPClass1 = 0, numberOfPClass2 = 0, numberOfPClass3 = 0, 
		livedPClass1 = 0, livedPClass2 = 0, livedPClass3 = 0,
		totalLived = 0;

	vector<double> survivalAge, diedAge;

	// train model
	for (int i = 0; i < trainSize; i++) {

		if (sexTrain.at(i) == 0) {
			numberOfSex0++;
			if (survivedTrain.at(i) == 1) {
				sex0Lived++;
				totalLived++;
				survivalAge.push_back(ageTrain.at(i));
			}

			else 
				diedAge.push_back(ageTrain.at(i));
			
		}

		else if (sexTrain.at(i) == 1) {
			numberOfSex1++;
			if (survivedTrain.at(i) == 1) {
				sex1Lived++;
				totalLived++;
				survivalAge.push_back(ageTrain.at(i));
			}

			else
				diedAge.push_back(ageTrain.at(i));
		}

		if (pclassTrain.at(i) == 1) {
			numberOfPClass1++;
			if (survivedTrain.at(i) == 1) {
				livedPClass1++;
				survivalAge.push_back(ageTrain.at(i));
			}

			else
				diedAge.push_back(ageTrain.at(i));
		}

		else if (pclassTrain.at(i) == 2) {
			numberOfPClass2++;
			if (survivedTrain.at(i) == 1) {
				livedPClass2++;
				survivalAge.push_back(ageTrain.at(i));
			}

			else 
				diedAge.push_back(ageTrain.at(i));
				
		}

		else {
			numberOfPClass3++;
			if (survivedTrain.at(i) == 1) {
				livedPClass3++;
				survivalAge.push_back(ageTrain.at(i));
			}

			else
				diedAge.push_back(ageTrain.at(i));
		}
	} // for loop

	cout << "\n\nInitial sex survival likelihoods: \n";
	cout << "Sex 0: " << survivalCalc(numberOfSex0, sex0Lived, trainSize, totalLived) << endl
		<< "Sex 1: " << survivalCalc(numberOfSex1, sex1Lived, trainSize, totalLived) << endl;

	cout << "\n\nSurvival averages per sex: ";
	cout << "\nSex 0: " << divide(sex0Lived, totalLived)
		<< "\nSex 1: " << divide(sex1Lived, totalLived);

	cout << "\n\nInitial passenger class survival likelihoods: \n";
	cout << "Passenger Class 1: " << survivalCalc(numberOfPClass1, livedPClass1, trainSize, totalLived) << endl
		<< "Passenger Class 2: " << survivalCalc(numberOfPClass2, livedPClass2, trainSize, totalLived) << endl
		<< "Passenger Class 3: " << survivalCalc(numberOfPClass3, livedPClass3, trainSize, totalLived) << endl;

	cout << "\n\nSurvival averages per class: "
		<< "\nPassenger Class 1: " << divide(livedPClass1, totalLived)
		<< "\nPassenger Class 2: " << divide(livedPClass2, totalLived)
		<< "\nPassenger Class 3: " << divide(livedPClass3, totalLived);

	// create vars for predictions
	double averageAgeDied = meanVector(diedAge), 
		averageAgeLived = meanVector(survivalAge), 
		averageAge = meanVector(ageTrain),
		ageVariance = variance(ageTrain),
		ageDiedVariance = variance(diedAge),
		ageLivedVariance = variance(survivalAge);

	double prob1[2] = { divide(totalLived, trainSize), divide(trainSize - totalLived, trainSize) };
	double prob2[2] = { divide(numberOfSex0, trainSize), divide(numberOfSex1, trainSize) };
	double prob3[3] = { divide(numberOfPClass1, trainSize), divide(numberOfPClass2, trainSize), divide(numberOfPClass3, trainSize) };


	// show vars
	cout << "\n\nAge Data: "
		<< "\nAverage Death Age: " << averageAgeDied << " | Variance of Death Age: " << ageDiedVariance 
		<< "\nAverage Survival Age: " << averageAgeLived << " | Variance Lived Age: " << ageLivedVariance;
	
	cout << "\n\nPrediction Priors: \n"
		<< "Lived: " << prob1[0] << " | Died: " << prob1[1] << endl
		<< "Sex 0: " << prob2[0] << " | Sex 1: " << prob2[1] << endl
		<< "Passenger Class 1: " << prob3[0] << " | Passenger Class 2: "
		<< prob3[1] << " | Passenger Class 3: "
		<< prob3[2];

	// create probability arrays for accessing predictions
	double sexLiveProb[2] = { divide(sex0Lived, totalLived), divide(sex1Lived, totalLived) },
		sexDieProb[2] = { survivalCalc(numberOfSex0, sex0Lived, trainSize, totalLived), survivalCalc(numberOfSex1, sex1Lived, trainSize, totalLived) },
		pclassLiveProb[3] = { divide(livedPClass1, totalLived), divide(livedPClass2, totalLived), divide(livedPClass3, totalLived) },
		pclassDieProb[3] = { survivalCalc(numberOfPClass1, livedPClass1, trainSize, totalLived), 
			survivalCalc(numberOfPClass2, livedPClass2, trainSize, totalLived),
			survivalCalc(numberOfPClass3, livedPClass3, trainSize, totalLived) };

	vector<double> predictions;

	double died, survived;

	// make predictions
	for (int i = 0; i < (numObservations - trainSize); i++) {
		died = prob1[1] * sexDieProb[sexTest.at(i)] * pclassDieProb[pclassTest.at(i) - 1]
			* calculateLikelihood(ageTest.at(i), averageAgeDied, ageDiedVariance);
		survived = prob1[0] * sexLiveProb[sexTest.at(i)] * pclassLiveProb[pclassTest.at(i) - 1]
			* calculateLikelihood(ageTest.at(i), averageAgeLived, ageLivedVariance);
		predictions.push_back(survived / (died + survived));

	}
	
	// create confusion matrix
	double confusionMatrix[2][2] = { 0.0, 0.0, 0.0, 0.0 };

	for (int i = trainSize; i < numObservations; i++) {
		
		if (predictions.at(i - trainSize) <= 0.5)
			confusionMatrix[0][survivedTest.at(i - trainSize)] += 1.0;
		else
			confusionMatrix[1][survivedTest.at(i - trainSize)] += 1.0;
	}

	// show first 10 predictions
	cout << "\n\nFirst 10 Predictions: \n";
	for (int i = 0; i < 10; i++)
		cout << predictions.at(i) << endl;

	// display confusion matrix
	cout << "\n\nConfusion Matrix:\n" << confusionMatrix[0][0] << " " << confusionMatrix[0][1] <<
		endl << confusionMatrix[1][0] << " " << confusionMatrix[1][1] << endl;

	// print accuracy, sensitivity, specificity
	cout << "\nAccuracy: " << calculateAccuracy(confusionMatrix[0][0] + confusionMatrix[1][1], numObservations - trainSize);
	cout << "\nSensitivity: " << divide(confusionMatrix[1][1], confusionMatrix[1][1] + confusionMatrix[1][0]);
	cout << "\nSpecificity: " << divide(confusionMatrix[0][0], confusionMatrix[0][0] + confusionMatrix[0][1]);

	// program stop for executable
	cout << "\n\nPress enter to end program...";
	cin.get();

	// end program
	cout << "\nProgram terminated.";

	return 0;

}

// calculate likelihood with given formula
double calculateLikelihood(double x, double mean, double variance) {
	return pow(e, -1 * ((x - mean) * (x - mean)) / (2 * variance)) / sqrt(2 * pi * variance);
}

// calculate variance
double variance(vector<double> vector) {
	double mean = meanVector(vector), var1 = 0, var2 = 0;
	for (int i = 0; i < vector.size(); i++) {
		var1 = (vector.at(i) - mean);
		var2 += (var1 * var1);
	}

	return sqrt(var2 / ((double)(vector.size() - 1)));
}

// versus survival calculator
double survivalCalc(double total, double lived, double size, double totalLived) {
	return ((total - lived) / (size - totalLived));
}

// returns the sum of a vector
double sumVector(vector<double> vector) {
	double sum  = 0;
	for (int i = 0; i < vector.size(); i++)
		sum += vector.at(i);
	return sum;
}

// returns the mean of a vector
double meanVector(vector<double> vector) {
	return sumVector(vector) / vector.size();
}

// returns the sum of a vector of ints
double sumVector(vector<int> vector) {
	double sum= 0;
	for (int i = 0; i < vector.size(); i++)
		sum += vector.at(i);
	return sum;
}

// returns the mean of a vector of ints
double meanVector(vector<int> vector) {
	return sumVector(vector) / vector.size();
}

// calculates model for descent with equation -(bias + coefficient * sex)
double calculateModel(double bias, double coefficient, int sex) {
	return -(bias + coefficient * sex);
}

// calculates error with equation survival - sigmoid
double calculateError(int survival, double sigmoid) {
	return survival - sigmoid;
}

// calculates sigmoid with equation 1.0 / (1 + e^linearModel)
double calculateSigmoid(double model) {
	return 1.0 / (1 + exp(model));
}

// calculates bias with equation bias + learnRate * error
double calculateBias(double bias, double error) {
	return bias + LEARNRATE * error;
}

// calculates coefficient with equation coefficient + learnRate * error * sex corresponding to the current term
double calculateCoefficient(double coefficient, double error, int sex) {
	return coefficient + LEARNRATE * error * sex;
}

// calculate accuracy by taking top row of confusion matrix sum and the test size
double calculateAccuracy(double confusion, int size) {
	return confusion / size;
}

// this one is because it was a bit difficult to follow inline
double divide(double numerator, double denominator) {
	return numerator / denominator;
}