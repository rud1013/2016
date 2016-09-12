#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

double getRandomNumber(const double min, const double max)//�������� ��ǥ ����
{
	double temp = (double)rand() / (double)RAND_MAX;
	temp = min + (max - min)*temp;

	return temp;
}

bool isInsideCircle(const double x, const double y)//�� �ȿ� �ִ� ������ Ȯ��
{
	const double x_c = 0.5;
	const double y_c = 0.5;
	const double r = 0.5;

	const double f = (x - x_c)*(x - x_c) + (y - y_c)*(y - y_c) - r*r;

	if (f > 0.0) return false;//����� 0���� ũ�� �� �ۿ� �ִ���
	else return true;
}

void main()
{
	FILE *of = fopen("circle.txt", "w");//������ "Write"�������� ����
	srand((unsigned)time(NULL));

	for (int i = 0; i < 10000; i++)
	{
		double x = getRandomNumber(0.0, 1.0);//x��ǥ ����
		double y = getRandomNumber(0.0, 1.0);//y��ǥ ����

		if (isInsideCircle(x, y) == true)//������ ��ǥ�� �� �ȿ� �ִ��� �ƴ��� �Ǵ�
			fprintf(of, "%f, %f\n", x, y);//���Ͽ� ��ǥ �Է�
	}

	fclose(of);//���� ����
}