// Program: edit_imgs.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//
// Group A  S11, 12
// Authors: monaem tarek 20210220 
//			youssef 
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

void load_img() {
	char fileName[100];
	cout << "Ahlan ya user ya habibi \n"
		<< "Please enter file name of the image to process : ";

	cin >> fileName;
	strcat(fileName, ".bmp");
	readGSBMP(fileName, image);
}


void save_image() {
	char fileName[100];

	// Get gray scale image target file name
	cout << "Enter the target image file name: ";
	cin >> fileName;

	// Add to it .bmp extension and load image
	strcat(fileName, ".bmp");
	writeGSBMP(fileName, image);
}

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
		"8 - Enlarge Image\n" <<
		"9 - Shrink Image\n" <<
		"a - Mirror 1 / 2 Image\n" <<
		"b - Shuffle Image\n" <<
		"c - Blur Image\n" <<
		"s - Save the image to a file\n" <<
		"0 - Exit" << endl;
}
// black and white filter 
void bwFilter() {
	double avg = 0.0 ;

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
// invert the image 
void invertFilter() {

}

void mergeFilter() {

}

void flipFilter() {
	// ask to flip h or v 
	char choice;
	int temp;
	cout << "Flip (h)orizontally or (v)ertically ?" << endl;
	cin >> choice;
	
	if (choice == 'v') 
	{
		// for every pixel in the img array flip the whole column
		for (int row = 0; row < SIZE /2; row++)
		{
			for (int col = 0; col < SIZE ; col++)
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

void darkenLightenFilter() {

}

void rotateFilter() {

}

int main() {
	char selected;
	load_img();
	show_menu();
	// get the selected filter 
	cin >> selected;

	if (selected == '1')
	{
		bwFilter();
	}
	else if (selected == '2')
	{
		invertFilter();
	}
	else if (selected == '3')
	{
		mergeFilter();
	}
	else if (selected == '4')
	{
		flipFilter();
	}
	else if (selected == '5')
	{
		darkenLightenFilter();
	}
	else if (selected == '6')
	{
		rotateFilter();
	}
	else if (selected == '0')
	{
		save_image();
	}
	save_image();
}


