#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

//랜덤으로 좌표 생성
double getRandomNumber(const double min, const double max)
{
	double temp = (double)rand() / (double)RAND_MAX;
	temp = min + (max - min)*temp;

	return temp;
}

bool isInsideCircle(const double x, const double y)//타원안에 있는 점인지 판단
{
	const double x_c = 0.5;
	const double y_c = 0.3;
	const double r = 0.5;//장축의 반지름
	const double r_ = 0.3;//단축의 반지름
	
	//타원안의 점인지 판단하기 위한 식
	const double f = (x - x_c)*(x - x_c) / (r*r) + (y - y_c)*(y - y_c) / (r_*r_);

	if (f > 1.0) return false;//결과 값이 1보다 크면 타원 밖의 점
	else return true;
}

void main()
{
	FILE *of = fopen("ellipse.txt", "w");//파일을 "Write"형식으로 연다
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		double x = getRandomNumber(0.0, 1.0);//x좌표 생성
		double y = getRandomNumber(0.0, 0.6);//y좌표 생성

		if (isInsideCircle(x, y) == true)//타원안의 점인지 판단
			fprintf(of, "%f, %f\n", x, y);
	}

	fclose(of);//파일 종료
}