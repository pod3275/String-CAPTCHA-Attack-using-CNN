#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void GetPixelData2(Mat image, uchar* blue, uchar* green, uchar* red, int j, int i);
int GetPixelData(Mat image, uchar* blue, uchar* green, uchar* red, int j, int i);
int main(){
	Mat image = imread("C:/Users/lawle/Documents/졸업논문/인터파크/0001.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (image.empty()) {
		std::cout << "파일을 불러올 수 없습니다." << endl;
		return -1;
	}

	uchar *blue, *green, *red;
	int i, j, check = 0;
	int sRow, sCol, bRow, bCol;

	int nRow = image.rows;
	int nCol = image.cols;

	cout << image.rows << " " << image.cols << endl;

	for (i = 0; i < nCol; i++) {
		for (j = 0; j < nRow; j++) {
			blue = nullptr;
			green = nullptr;
			red = nullptr;

			if (GetPixelData(image, blue, green, red, j, i) == 1) {
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
			blue = nullptr;
			green = nullptr;
			red = nullptr;

			if (GetPixelData(image, blue, green, red, j, i) == 1) {
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
			blue = nullptr;
			green = nullptr;
			red = nullptr;
			GetPixelData2(subimage, blue, green, red, j, i);
		}
	}
	
	namedWindow("image", CV_WINDOW_AUTOSIZE);
	imshow("image", subimage);

	waitKey(0);
	return 0;
}

int GetPixelData(Mat image, uchar* blue, uchar* green, uchar* red, int j, int i) {
	uchar *data = image.data;

	int nRow = image.rows;
	int nCol = image.cols;

	if (i > nCol || j > nRow) {
		cout << "Selected pixel is out of range." << endl;
		return -1;
	}

	blue = image.data + j*image.step + i*image.elemSize() + 0;
	green = image.data + j*image.step + i*image.elemSize() + 1;
	red = image.data + j*image.step + i*image.elemSize() + 2;

	if ((int)*blue < 200 || (int)*green < 200 || (int)*red < 200)		
		return 1;
	else
		return 0;
}

void GetPixelData2(Mat image, uchar* blue, uchar* green, uchar* red, int j, int i) {
	uchar *data = image.data;

	int nRow = image.rows;
	int nCol = image.cols;

	if (i > nCol || j > nRow) {
		cout << "Selected pixel is out of range." << endl;
		return ;
	}

	blue = image.data + j*image.step + i*image.elemSize() + 0;
	green = image.data + j*image.step + i*image.elemSize() + 1;
	red = image.data + j*image.step + i*image.elemSize() + 2;

	if ((int)*blue < 100 && (int)*red < 100 && (int)*green < 100) {
		Vec3b* pixel = image.ptr<Vec3b>(j);
		pixel[i][0] = 255;
		pixel[i][1] = 255;
		pixel[i][2] = 255;
	}
}
