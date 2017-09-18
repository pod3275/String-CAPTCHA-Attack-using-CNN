#include <iostream>
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int GetPixelData(Mat image, uchar* scale, int j, int i);

int main(){
	Mat image = imread("C:/Users/lawle/Documents/졸업논문/인터파크/0002.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (image.empty()) {
		std::cout << "파일을 불러올 수 없습니다." << endl;
		return -1;
	}

	namedWindow("원본", CV_WINDOW_AUTOSIZE);
	imshow("원본", image);	

	uchar *scale;
	int i, j, check = 0;
	int sRow, sCol, bRow, bCol;

	int nRow = image.rows;
	int nCol = image.cols;

	cout << image.rows << " " << image.cols << endl;

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

	cout << sRow << " " << sCol << endl;


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
	cout << bRow << " " << bCol << endl;

	Rect rect(sCol, sRow, bCol-sCol, bRow-sRow);

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
	medianBlur(eroded, medianimage, 3);
	namedWindow("d+e+m", CV_WINDOW_AUTOSIZE);
	imshow("d+e+m", medianimage);

	for (i = 0; i < nCol; i++) {
		for (j = 0; j < nRow; j++) {
			scale = nullptr;

			if (i < 25 || j < 25 || i > (nCol-25) || j > (nRow-25)) {
				medianimage.at<uchar>(j, i) = 255;
			}
		}
	}


	int start = 0, count = 0, st_col = 0, fin_col = 0, buf = 0;

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

	namedWindow("Letter1", CV_WINDOW_AUTOSIZE);
	imshow("Letter1", Letter[0]);
	namedWindow("Letter2", CV_WINDOW_AUTOSIZE);
	imshow("Letter2", Letter[1]);
	namedWindow("Letter3", CV_WINDOW_AUTOSIZE);
	imshow("Letter3", Letter[2]);
	namedWindow("Letter4", CV_WINDOW_AUTOSIZE);
	imshow("Letter4", Letter[3]);
	namedWindow("Letter5", CV_WINDOW_AUTOSIZE);
	imshow("Letter5", Letter[4]);
	namedWindow("Letter6", CV_WINDOW_AUTOSIZE);
	imshow("Letter6", Letter[5]);

	namedWindow("제거", CV_WINDOW_AUTOSIZE);
	imshow("제거", medianimage);

	waitKey(0);
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


