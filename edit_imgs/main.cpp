// Program: Gray Scale Image Processor
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//
// Group A  S11, 12
// Authors: monaem tarek 20210220 
//			youssef Ihab 20210466
//			magdy 
// 
// Date:    1/4/2022
// Version: 1.0
#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <cstring>
#include <fstream>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char sketch[SIZE][SIZE];

void load_img() {
	char fileName[100];
	cout << "Ahlan ya user ya habibi \n"
		<< "Please enter file name of the image to process : ";

	cin >> fileName;
	strcat(fileName, ".bmp");
	readGSBMP(fileName, image);
}

//----------------------------------------------------------------------
void save_image() {
	char fileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> fileName;

	// Add to it .bmp extension and load image
	strcat(fileName, ".bmp");
	writeGSBMP(fileName, image);
}
//----------------------------------------------------------------------
// show the filters menu 
void show_menu() {
	cout <<
		"Please select a filter to apply or 0 to exit :\n" <<
		"1 - Black & White Filter\n" <<
		"2 - Invert Filter\n" <<
		"3 - Merge Filter\n" <<
		"4 - Flip Image\n" <<
		"5 - Darken and Lighten Image\n" <<
		"6 - Rotate Image\n" <<
		"7 - Detect Image Edges\n" <<
		"a-  Mirror 1/2 Image\n"<<
		"s - Save the image to a file\n" <<
		"0 - Exit" << endl;
}
//----------------------------------------------------------------------
// black and white filter 
void bwFilter() {
	long double avg = 0.0;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			avg += image[i][j];
		}
	}
	avg /= (SIZE * SIZE);

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (image[i][j] > avg) {
				image[i][j] = 255;
			}
			else {
				image[i][j] = 0;
			}
		}
	}
}
//----------------------------------------------------------------------
// invert the image 
void invertFilter() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			image[i][j] = 255 - image[i][j];
		}
	}
}

//----------------------------------------------------------------------
void mergeFilter() {
	char imagename[100];

	cout << "enter the second image file name: ";
	cin >> imagename;

	strcat(imagename, ".bmp");
	readGSBMP(imagename, image2);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = (image[i][j] + image2[i][j]) / 2;
		}
	}
}

//----------------------------------------------------------------------
void flipFilter() {
	// ask to flip h or v 
	char choice;
	int temp;
	cout << "Flip (h)orizontally or (v)ertically ?" << endl;
	cin >> choice;

	if (choice == 'v')
	{
		// for every pixel in the img array flip the whole column
		for (int row = 0; row < SIZE / 2; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{	// flip the arrays cols
				temp = image[row][col];
				image[row][col] = image[SIZE - 1 - row][col];
				image[SIZE - 1 - row][col] = temp;
			}
		}
	}
	else if (choice == 'h')
	{
		// for every pixel in the img array flip the whole row 
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE / 2; col++)
			{	// flip the arrays rows
				temp = image[row][col];
				image[row][col] = image[row][SIZE - 1 - col];
				image[row][SIZE - 1 - col] = temp;

			}
		}
	}
}

//----------------------------------------------------------------------
void darkenLightenFilter() {
	char choice;
	cout << "Do you want to (d)arken or (l)ighten? type d or l:";
	cin >> choice;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

			if (choice == 'd')
			{
				image[i][j] = image[i][j] /2;
			}
			else if (choice == 'l')
			{

				if (image[i][j] > 205)
				{
					image[i][j] = 255;
				}
				else
				{
					image[i][j] = image[i][j] + 50;
				}
			}
			else
			{
				cout << "wrong input";
			}
		}
	}
}

//----------------------------------------------------------------------
void rotateFilter() {
	int deg = 0;
	void rotate_image90(), rotate_image180(), rotate_image270();
	cout << "Rotate (90), (180) or (360) degrees?" << endl;
	cin >> deg;
	
	if (deg == 90)
	{
		rotate_image90();
	}
	else if (deg == 180)
	{
		rotate_image180();
	}
	else if (deg == 270)
	{
		rotate_image270();
	}
}

//----------------------------------------------------------------------
void rotate_image90() {

	for (int i = 0; i < SIZE; i++) {
		for (int j = i + 1; j < SIZE; j++) {
			swap(image[i][j], image[j][i]);
		}
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE / 2; j++) {
			swap(image[j][i], image[SIZE - j - 1][i]);
		}
	}
}
//----------------------------------------------------------------------
void rotate_image180() {
	int temp;
	for (int i = 0;i < SIZE / 2;i++)
	{
		for (int j = 0;j < SIZE;j++)
		{
			temp = image[i][j];
			image[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
			image[SIZE - 1 - i][SIZE - 1 - j] = temp;
		}
	}
}
//----------------------------------------------------------------------
void rotate_image270() {
	int temp;
	for (int i = 0; i < (SIZE); i++) {
		for (int j = i + 1; j < (SIZE); j++) {
			swap(image[i][j], image[j][i]);
		}
	}
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE / 2; j++) {
			swap(image[j][i], image[SIZE - j - 1][i]);
		}
	}
	for (int i = 0;i < SIZE / 2;i++)
	{
		for (int j = 0;j < SIZE;j++)
		{
			temp = image[i][j];
			image[i][j] = image[SIZE - 1 - i][SIZE - 1 - j];
			image[SIZE - 1 - i][SIZE - 1 - j] = temp;
		}
	}
}

//----------------------------------------------------------------------
void detectImageEdges() {
	double avg = 0.0;
	// make a new white image which is sketch[][]
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
				sketch[i][j] = 255;
		}
	}
	// apply black and white filter to the image and then detect the edges
	bwFilter();
	// loop and look for the black pixels between black pixel and white pixel
	// then copy this black pixel to the new array   ->   sketch[][]
	for (int i = 0; i < SIZE; i++)
	{	
		if (i == 0 || i == SIZE - 1)
		{
			continue;
		}

		for (int j = 0; j < SIZE; j++)
		{
			if (j == 0 || j == SIZE-1)
			{
				continue;
			}
			// check right and left 
			if (image[i][j] == 0 && image[i][j+1] != image[i][j-1])
			{
				sketch[i][j] = 0;
			}
			// check up and down
			if (image[i][j] == 0 && image[i-1][j] != image[i+1][j])
			{
				sketch[i][j] = 0;
			} 
			// check the hour hand of 2 and 8    ->     ' / '
			if (image[i][j] == 0 && image[i - 1][j+1] != image[i + 1][j-1])
			{
				sketch[i][j] = 0;
			}
			// check the hour hand of 10 and 4   ->     ' \ '
			if (image[i][j] == 0 && image[i + 1][j+1] != image[i - 1][j-1])
			{
				sketch[i][j] = 0;
			}
		}
	}
	// overwrite the image array with sketch array 
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			image[i][j] = sketch[i][j];
		}
	}
}
// return 1 if choice is y, else return 0
int askNext() {
	char answer;
	cout << "Do you want to do any thing else?  'y'  or  'n' " << endl;
	cin >> answer;

	if (answer == 'y') show_menu();

	else if (answer == 'n') {
		save_image();
		return 0;
	}

	return 1;
}

void mirrorHalf() {
	char choice;
	cout << "Mirror (l)eft, (r)ight, (u)pper, (d)own side?\n";
	cin >> choice;

	// mirror the left half 
	if (choice == 'l') 
	{	// loop for pixels in the left half 
		// assign it to the opposite pixels in the other half
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE / 2; j++)
			{
				image[i][SIZE - 1 - j] = image[i][j];
			}
		}
	}
	// mirror the right half 
	if (choice == 'r')
	{	// loop for pixels in the left half 
		// make those pixels equal to the opposite pixels in the other half 
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE / 2; j++)
			{
				image[i][j] = image[i][SIZE - 1 - j];
			}
		}
	}
	// mirror the upper half 
	if (choice == 'u')
	{	// loop for pixels in the upper half 
		// assign it to the opposite pixels in the other half
		for (int i = 0; i < SIZE / 2; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[SIZE - 1 - i][j] = image[i][j];
			}
		}
	}
	// mirror the down half 
	if (choice == 'd')
	{	// loop for pixels in the upper half 
		// make those pixels equal to the opposite pixels in the other half 
		for (int i = 0; i < SIZE / 2; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image[SIZE - 1 - i][j];
			}
		}
	}
}

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main() {
	char selected;
	int run = 1;
	load_img();
	
	do {
		show_menu();
		// get the selected filter 
		cin >> selected;

		if (selected == '1')
		{
			bwFilter();
			run = askNext();
		}
		else if (selected == '2')
		{
			invertFilter();
			run = askNext();
		}
		else if (selected == '3')
		{
			mergeFilter();
			run = askNext();
		}
		else if (selected == '4')
		{
			flipFilter();
			run = askNext();
		}
		else if (selected == '5')
		{
			darkenLightenFilter();
			run = askNext();
		}
		else if (selected == '6')
		{
			rotateFilter();
			run = askNext();
		}
		else if (selected == '7')
		{
			detectImageEdges();
			run = askNext();

		}
		else if (selected == 'a')
		{
			mirrorHalf();
			run = askNext();

		}
		else if (selected == 's') save_image();
		else if (selected == '0') run = false;
		else{
			cout << "wrong choice !" << endl;
		}
	} while (run);
}
