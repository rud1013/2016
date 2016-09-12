#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

//�������� ��ǥ ����
double getRandomNumber(const double min, const double max)
{
	double temp = (double)rand() / (double)RAND_MAX;
	temp = min + (max - min)*temp;

	return temp;
}

bool isInsideCircle(const double x, const double y)//Ÿ���ȿ� �ִ� ������ �Ǵ�
{
	const double x_c = 0.5;
	const double y_c = 0.3;
	const double r = 0.5;//������ ������
	const double r_ = 0.3;//������ ������
	
	//Ÿ������ ������ �Ǵ��ϱ� ���� ��
	const double f = (x - x_c)*(x - x_c) / (r*r) + (y - y_c)*(y - y_c) / (r_*r_);

	if (f > 1.0) return false;//��� ���� 1���� ũ�� Ÿ�� ���� ��
	else return true;
}

void main()
{
	FILE *of = fopen("ellipse.txt", "w");//������ "Write"�������� ����
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		double x = getRandomNumber(0.0, 1.0);//x��ǥ ����
		double y = getRandomNumber(0.0, 0.6);//y��ǥ ����

		if (isInsideCircle(x, y) == true)//Ÿ������ ������ �Ǵ�
			fprintf(of, "%f, %f\n", x, y);
	}

	fclose(of);//���� ����
}