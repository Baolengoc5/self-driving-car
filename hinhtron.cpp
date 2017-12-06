#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
	Mat src, src_gray;

	/// đọc ảnh
	src = imread("bienbao.jpg", 1);

	if (!src.data)
	{
		return -1;
	}

	// Chuyển sang màu xám
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//Áp dụng một mờ Gaussian để giảm tiếng ồn và tránh phát hiện vòng tròn giả:
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	vector<Vec3f> circles;

	//Tiến hành áp dụng chuyển đổi HoughCircles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0);

	/*src_gray : Nhập hình ảnh (màu xám)
	circles : Một vector lưu trữ các bộ có 3 giá trị: x_ {c}, y_ {c}, rcho mỗi vòng tròn được phát hiện.
	CV_HOUGH_GRADIENT : Xác định phương pháp phát hiện. Hiện tại đây chỉ là một trong có sẵn trong OpenCV
	dp = 1 : Tỷ số nghịch đảo của độ phân giải
	min_dist = src_gray.rows / 8 : Khoảng cách tối thiểu giữa các trung tâm phát hiện
	param_1 = 200 : ngưỡng trên cho máy dò cạnh canny bên trong
	param_2 = 100 *: ngưỡng để phát hiện trung tâm.
	min_radius = 0 : phát hiện đài phát thanh tối thiểu. Nếu không rõ, hãy đặt số không theo mặc định.
	max_radius = 0 : Bán kính tối đa được phát hiện. Nếu không biết, hãy đặt zero theo mặc định*/

	//vẽ đường tròn đã dò
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);
	//imshow("demo",);
	waitKey(0);
	return 0;
}