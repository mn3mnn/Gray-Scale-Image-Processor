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
	cout << "Please enter file name of the image to open : ";

	cin >> fileName;
	strcat(fileName, ".bmp");
	readGSBMP(fileName, image);
}
//----------------------------------------------------------------------

void save_image() {
	char fileName[100];

	// Get image name to save
	cout << "Enter new image name to save: ";
	cin >> fileName;

	// Add to it .bmp extension and load image
	strcat(fileName, ".bmp");
	writeGSBMP(fileName, image);
}
//----------------------------------------------------------------------
// show filters menu 
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
		"a-  Mirror 1/2 Image\n"<<
		"c - Blur Image\n" <<
		"s - Save the image as a new file\n" <<
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

	// load the second image 
	cout << "enter the second image file name: ";
	cin >> imagename;

	strcat(imagename, ".bmp");
	readGSBMP(imagename, image2);

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			//get the average of the pixel with the corresponding pixel in second image
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
		// for every pixel in the first half of img array flip the whole column
		for (int row = 0; row < SIZE / 2; row++)
		{
			for (int col = 0; col < SIZE; col++)
			{	// flip the array cols
				temp = image[row][col];
				image[row][col] = image[SIZE - 1 - row][col];
				image[SIZE - 1 - row][col] = temp;
			}
		}
	}
	else if (choice == 'h')
	{
		// for every pixel in the first half of img array flip the whole row 
		for (int row = 0; row < SIZE; row++)
		{
			for (int col = 0; col < SIZE / 2; col++)
			{	// flip the array rows
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
	//ask the user to darken or lighten
	cout << "Do you want to (d)arken or (l)ighten? type d or l:";
	cin >> choice;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{

			if (choice == 'd')
			{
				// the darken version take each pixel and get it's half
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
					// the lighten version take each pixel smaller than 205 and add 50 to it
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
//----------------------------------------------------------------------

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

void blur() {
	int sum = 0;

	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			// check the pixels on the edges and don't change them
			if (i == 0 || j == 0)
			{
				image[i][j] = image[i][j];
			}
			else if (i == SIZE - 1 || j == SIZE - 1)
			{
				image[i][j] = image[i][j];
			}
			else
			{	// get the sum of all pixels in the neighborhood and divide the sum by 9 
				image[i][j] = (image[i][j] + image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i][j - 1] + image[i][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 9;
			}
		}
	}
}
//----------------------------------------------------------------------

void shrink()
{   
		int factor;
	cout << "1. 1/2 the normal" << endl
		 << "2. 1/4 the normal" << endl
		 << "3. 1/3 the normal" << endl
		 << "choose the new dimensions: ";

	cin >> factor;
	if (factor == 1 || factor == 2 || factor == 3)
	{
		if (factor == 1)
		{
			factor = 2;
		}
		else if (factor == 2)
		{
			factor = 4;
		}
		else if (factor == 3)
		{
			factor = 3;
		}
		// create new image2 with the new size
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image2[i / factor][j / factor] = image[i][j];
			}
		}
		// then change img and img2
		for (int i = 0; i < SIZE; i++)
		{
			for (int j = 0; j < SIZE; j++)
			{
				image[i][j] = image2[i][j];
			}
		}
	}
	else
	{
		cout << "wrong invalid";
	}
}

void enlarge() {
	void enlarge_image1();
	void enlarge_image2();
	void enlarge_image3();
	void enlarge_image4();

	int enlarge_image;
	cout << "Which quarter to enlarge 1, 2, 3 or 4? " << "\n";
	cin >> enlarge_image;

	if (enlarge_image == 1) {
		enlarge_image1();
	}
	if (enlarge_image == 2) {
		enlarge_image2();
	}
	if (enlarge_image == 3) {
		enlarge_image3();
	}
	if (enlarge_image == 4) {
		enlarge_image4();	
	}
}

//----------------------------------------------------------------------------------
void enlarge_image1()
{
	unsigned char temp[256][256];
	for (int i = 0, k = 0; i < 256 / 2; i++, k += 2)
	{
		for (int j = 0, n = 0;j < 256 / 2; j++, n += 2)
		{
			temp[k][n] = image[i][j];
			temp[k + 1][n] = image[i][j];
			temp[k][n + 1] = image[i][j];
			temp[k + 1][n + 1] = image[i][j];
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			image[i][j] = temp[i][j];
		}
	}
}
//_________________
void enlarge_image2()
{
	unsigned char temp[256][256];

	for (int i = 0, k = 0; i < 256 / 2; i++, k += 2)
	{
		for (int j = 256 / 2, n = 0;j < 256; j++, n += 2)
		{
			temp[k][n] = image[i][j];
			temp[k + 1][n] = image[i][j];
			temp[k][n + 1] = image[i][j];
			temp[k + 1][n + 1] = image[i][j];
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			image[i][j] = temp[i][j];
		}
	}
}
//_________________
void enlarge_image3()
{
	unsigned char temp[256][256];
	for (int i = 256 / 2, k = 0; i < 256; i++, k += 2)
	{
		for (int j = 0, n = 0;j < 256 / 2; j++, n += 2)
		{
			temp[k][n] = image[i][j];
			temp[k + 1][n] = image[i][j];
			temp[k][n + 1] = image[i][j];
			temp[k + 1][n + 1] = image[i][j];
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			image[i][j] = temp[i][j];
		}
	}
}
//_________________
void enlarge_image4()
{
	unsigned char temp[256][256];

	for (int i = 256 / 2, k = 0; i < 256; i++, k += 2)
	{
		for (int j = 256 / 2, n = 0;j < 256; j++, n += 2)
		{
			temp[k][n] = image[i][j];
			temp[k + 1][n] = image[i][j];
			temp[k][n + 1] = image[i][j];
			temp[k + 1][n + 1] = image[i][j];
		}
	}

	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			image[i][j] = temp[i][j];
		}
	}
	for (int i = 0; i < 256; i++) {
		for (int j = 0; j < 256; j++) {
			image[i][j] = temp[i][j];
		}
	}
}

// return 1 if choice is y, else return 0
int askNext() {
	char answer;
	cout << "Do you want to do any thing else?  'y'  or  'n' " << "\n";
	cin >> answer;

	if (answer == 'y') show_menu();

	else if (answer == 'n') {
		save_image();
		return 0;
	}
	return 1;
}
//----------------------------------------------------------------------
// Choose and Apply the filter to the img
void chooseFilters() {
	char selected;
	int run = 1;

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
		else if (selected == '8')
		{
			enlarge();
			run = askNext();
		}
		else if (selected == '9')
		{
			shrink();
			run = askNext();
		}
		else if (selected == 'a')
		{
			mirrorHalf();
			run = askNext();
		}
		else if (selected == 'c')
		{
			blur();
			run = askNext();
		}
		else if (selected == 's') save_image();
		else if (selected == '0') run = false;
		else {
			cout << "wrong choice !" << "\n";
		}
	} while (run);
}
//----------------------------------------------------------------------
int main() {
	
	load_img();

	chooseFilters();

}
