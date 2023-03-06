/* das-model.cpp
 * JML190001 - John Lawler
 * CS4375.004 Project Three
 * 02/28/23
 * Program uses functions to do a gradient descent and calculate confusion matrix in order to create
 * a linear regression. Program displays timings, and appropriate charactersitics of the regression.
 */
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
const double LEARNRATE = 0.001;

double calculateModel(double, double, int);
double calculateError(int, double);
double calculateSigmoid(double);
double calculateBias(double, double);
double calculateCoefficient(double, double, int);
double calculateAccuracy(double, int);
double divide(double, double);

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

	vector<int> ID(MAXLEN);			string IDIn;		// vector to hold all of the ID nums, string to hold current line val
	vector<int> pclass(MAXLEN);		string pclassIn;	// vector to hold all pasenger class data, string to hold current line val
	vector<int> survived(MAXLEN);	string survivedIn;	// vector to hold bool survived data, string to hold current line val
	vector<int> sex(MAXLEN);		string sexIn;		// vector to hold sex data, string to hold current line val
	vector<double> age(MAXLEN);		string ageIn;		// vector to hold age data, string to hold current line val

	string currentLine;									// current line for reading in csv
	getline(inFS, currentLine);							// get headers
	cout << "Heading: " << currentLine << endl;			// display headers
	int numObservations = 0;							// number of observations

	// get data from ifstream
	while (inFS.good()) {

		// cannot parse for some reason, leaving as string
		getline(inFS, IDIn, ',');

		// get pclass and parse to int
		getline(inFS, pclassIn, ',');
		pclass.at(numObservations) = stoi(pclassIn);
		
		// get survived and parse to int
		getline(inFS, survivedIn, ',');
		survived.at(numObservations) = stoi(survivedIn);

		// get sex and parse to int
		getline(inFS, sexIn, ',');
		sex.at(numObservations) = stoi(sexIn);

		// get age and parse to double, there are fractional ages so double instead of int
		getline(inFS, ageIn, '\n');
		age.at(numObservations) = stod(ageIn);

		numObservations++;
	}

	// close file when done
	cout << "Closing file " << fileName << "." << endl;
	inFS.close();
	
	// resize vectors to free up space
	ID.resize(numObservations);
	pclass.resize(numObservations);
	survived.resize(numObservations);
	sex.resize(numObservations);
	age.resize(numObservations);

	cout << "Number of records read from " << fileName << ": " << numObservations << endl;

	// create train and test
	int trainSize = 800, testSize = numObservations - trainSize;

	// variables for gradient descent
	double errorValue, sigmoid, linearModel, bias = 1.0, correspondingCoefficient = 1.0;
	int currTerm, numIter = MAXLEN;			// note: the number of iterations happens to be the same as the MAXLEN, but it may not be suitable for larger sets

	auto start = chrono::high_resolution_clock::now();	// start clock

	// Gradient Descent, uses functions to show steps more clearly
	for (int i = 0; i < numIter * numObservations; i++) {
		currTerm = i % trainSize;

		// calculate linear model for the descent
		linearModel = calculateModel(bias, correspondingCoefficient, sex.at(currTerm));

		// calculate error
		errorValue = calculateError(survived.at(currTerm), calculateSigmoid(linearModel));

		// calculate weights
		bias = calculateBias(bias, errorValue);
		correspondingCoefficient = calculateCoefficient(correspondingCoefficient, errorValue, sex.at(currTerm));
	}

	auto end1 = chrono::high_resolution_clock::now();						// stop clock

	auto time1 = chrono::duration_cast<chrono::milliseconds>(end1 - start);	// calculate time of gradient descent

	// display weights and time
	cout << "\n\nWeights: [" << bias << "] [" << correspondingCoefficient << "]" << endl;
	cout << "Weights Time: " << time1.count() << "ms\n";

	// create confusion matrix
	double confusionMatrix[2][2] = { 0.0, 0.0, 0.0, 0.0 };

	for (int i = trainSize; i < numObservations; i++) {
		linearModel = calculateModel(bias, correspondingCoefficient, sex.at(i));
		sigmoid = calculateSigmoid(linearModel);

		if (sigmoid <= 0.5)
			confusionMatrix[0][survived.at(i)] += 1.0;
		else
			confusionMatrix[1][survived.at(i)] += 1.0;
	}

	// get times for confusion matrix and total time
	auto end2 = chrono::high_resolution_clock::now();		// stop clock
	auto time2 = chrono::duration_cast<chrono::milliseconds>(end2 - end1);
	auto time3 = time2 + time1;

	// display confusion matrix
	cout << "\nConfusion Matrix:\n" << confusionMatrix[0][0] << " " << confusionMatrix[0][1] <<
		endl << confusionMatrix[1][0] << " " << confusionMatrix[1][1] << endl;

	// display timings
	cout << "\nConfusion Matrix Time: " << time2.count() << "ms" << endl;
	cout << "\nTotal Algorithm Time: " << time3.count() << "ms" << endl;

	// print accuracy, sensitivity, specificity
	cout << "\nAccuracy: " << calculateAccuracy(confusionMatrix[0][0] + confusionMatrix[1][1], testSize);
	cout << "\nSensitivity: " << divide(confusionMatrix[1][1], confusionMatrix[1][1] + confusionMatrix[1][0]);
	cout << "\nSpecificity: " << divide(confusionMatrix[0][0], confusionMatrix[0][0] + confusionMatrix[0][1]);

	// program stop for executable
	cout << "\n\nPress enter to end program...";
	cin.get();

	// end program
	cout << "\nProgram terminated.";

	return 0;


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