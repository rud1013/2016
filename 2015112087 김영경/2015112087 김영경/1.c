#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

double getRandomNumber(const double min, const double max)//랜덤으로 좌표 생성
{
	double temp = (double)rand() / (double)RAND_MAX;
	temp = min + (max - min)*temp;

	return temp;
}

bool isInsideCircle(const double x, const double y)//원 안에 있는 점인지 확인
{
	const double x_c = 0.5;
	const double y_c = 0.5;
	const double r = 0.5;

	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r*r;

	if (f > 0.0) return false;//결과가 0보다 크면 원 밖에 있는점
	else return true;
}

void main()
{
	FILE *of = fopen("circle.txt", "w");//파일을 "Write"형식으로 연다
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		double x = getRandomNumber(0.0, 1.0);//x좌표 생성
		double y = getRandomNumber(0.0, 1.0);//y좌표 생성

		if (isInsideCircle(x, y) == true)//생성된 자표가 원 안에 있는지 아닌지 판단
			fprintf(of, "%f, %f\n", x, y);//파일에 좌표 입력
	}

	fclose(of);//파일 닫음
}