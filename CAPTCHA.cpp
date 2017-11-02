#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>


using namespace std;
using namespace cv;

int GetPixelData(Mat image, uchar* scale, int j, int i);

int main(){
	int count;
	for (count = 500; count < 501; count++) {

		cout << count << endl;

		char NUM[7] = "0";
		char buffer[30];
		char *it;
		it = _itoa(count, buffer, 10);
		strcat(NUM, it);

		char loc[] = "C:/Users/lawle/Documents/졸업논문/인터파크/";
		strcat(loc, NUM);
		strcat(loc, ".png");
		Mat image = imread(loc, CV_LOAD_IMAGE_GRAYSCALE);

		if (image.empty()) {
			std::cout << "파일을 불러올 수 없습니다." << endl;
			return -1;
		}

		uchar *scale;
		int i, j, check = 0;
		int sRow, sCol, bRow, bCol;

		int nRow = image.rows;
		int nCol = image.cols;

		for (i = 0; i < nCol; i++) {
			for (j = 0; j < nRow; j++) {
				scale = nullptr;

				if (GetPixelData(image, scale, j, i) < 200) {
					sRow = j;
					sCol = i;
					check = 1;
					break;
				}
			}
			if (check == 1)
				break;
		}

		check = 0;

		for (j = nRow - 2; j >= 0; j--) {
			for (i = nCol - 2; i >= 0; i--) {
				scale = nullptr;

				if (GetPixelData(image, scale, j, i) < 200) {
					bRow = j;
					bCol = i;
					check = 1;
					break;
				}
			}
			if (check == 1)
				break;
		}

		Rect rect(sCol, sRow, bCol - sCol, bRow - sRow);

		Mat subimage = image(rect);

		nRow = subimage.rows;
		nCol = subimage.cols;

		for (i = 0; i < nCol; i++) {
			for (j = 0; j < nRow; j++) {
				scale = nullptr;

				if (GetPixelData(subimage, scale, j, i) < 100) {
					subimage.at<uchar>(j, i) = 255;
				}
			}
		}

		for (i = 0; i < nCol; i++) {
			for (j = 0; j < nRow; j++) {
				scale = nullptr;

				if (GetPixelData(subimage, scale, j, i) != 255) {
					subimage.at<uchar>(j, i) = 0;
				}
			}
		}

		Mat medianimage;
		Mat eroded;
		Mat dilated;

		dilate(subimage, dilated, Mat());
		erode(dilated, eroded, Mat());
		dilate(eroded, medianimage, Mat());

		for (i = 0; i < nCol; i++) {
			for (j = 0; j < nRow; j++) {
				scale = nullptr;

				if (i < 25 || j < 25 || i >(nCol - 25) || j >(nRow - 25)) {
					medianimage.at<uchar>(j, i) = 255;
				}
			}
		}

		int start = 0, count = 0, st_col = 0, fin_col = 0, st_row = 0, fin_row = 0, buf = 0, nletter = 0;

		Mat Letter[6];

		for (i = 0; i < nCol; i++) {
			count = 0;

			for (j = 0; j < nRow; j++) {
				scale = nullptr;
				if (GetPixelData(medianimage, scale, j, i) == 0) {
					count++;
					if (start == 0) {
						start++;
						st_col = i;
					}
				}
			}

			if (start != 0 && count == 0) {
				fin_col = i;
				if (fin_col - st_col > 10) {
					Rect rect2(st_col, 0, fin_col - st_col - 1, nRow - 1);
					Letter[buf] = medianimage(rect2);
					buf++;
				}
				start = 0;
			}
		}


		start = 0; nletter = buf;

		Mat Letter2[6];

		for (buf = 0; buf < nletter; buf++) {
			nRow = Letter[buf].rows;
			nCol = Letter[buf].cols;

			for (j = 0; j < nRow; j++) {
				count = 0;

				for (i = 0; i < nCol; i++) {
					scale = nullptr;
					if (GetPixelData(Letter[buf], scale, j, i) == 0) {
						count++;
						if (start == 0) {
							start++;
							st_row = j;
						}
					}
				}

				if (start != 0 && count == 0) {
					fin_row = j;
					if (fin_row - st_row > 10) {
						Rect rect2(0, st_row, nCol - 1, fin_row - st_row - 1);
						Letter2[buf] = Letter[buf](rect2);
					}
					start = 0;
				}
			}
		}

		for (i = 0; i < 6; i++) resize(Letter2[i], Letter2[i], Size(32, 32));
		
		char filename1[20] = "img";
		strcat(filename1, NUM);
		strcat(filename1, "_1.jpg");
		imwrite(filename1, Letter2[0]);

		char filename2[20] = "img";
		strcat(filename2, NUM);
		strcat(filename2, "_2.jpg");
		imwrite(filename2, Letter2[1]);

		char filename3[20] = "img";
		strcat(filename3, NUM);
		strcat(filename3, "_3.jpg");
		imwrite(filename3, Letter2[2]);

		char filename4[20] = "img";
		strcat(filename4, NUM);
		strcat(filename4, "_4.jpg");
		imwrite(filename4, Letter2[3]);

		char filename5[20] = "img";
		strcat(filename5, NUM);
		strcat(filename5, "_5.jpg");
		imwrite(filename5, Letter2[4]);

		char filename6[20] = "img";
		strcat(filename6, NUM);
		strcat(filename6, "_6.jpg");
		imwrite(filename6, Letter2[5]);

		waitKey(0);

	}

	return 0;
}

int GetPixelData(Mat image, uchar* scale, int j, int i) {
	uchar *data = image.data;

	int nRow = image.rows;
	int nCol = image.cols;

	if (i > nCol || j > nRow) {
		cout << "Selected pixel is out of range." << endl;
		return -1;
	}

	scale = image.data + j*image.step + i*image.elemSize() + 0;

	return (int)*scale;
}


