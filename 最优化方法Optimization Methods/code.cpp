#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include<cmath>
#define D 20 //�궨��������е�x��alpha������ά��

using namespace std;


//ͨ������ˮ���ܺͻ��ԭ�������Ž�x�Ͷ�Ӧ����v�ĵ���(��ˮ�ĸ߶�height)
//ͨ�����ַ������
void Solution(double* alpha, double* x, double& height)
{
   
    //����ÿһ��v�����һ������������ʼֵ��Ϊ0
    double curVolume = 0.0;

    //��ʼ��Χ����Ϊ(0,1)
    double left = 0.0;
    double right = 1.0;


    do {
        //ÿ��ѭ����ʼǰ��curVolume����
        curVolume = 0.0;

        //ȡ�����е���Ϊ�µ�height
        height = (left + right) / 2.0;

        //�����ڵ��µ�v�ı�׼�µ�x�����Լ�curVolume
        for (int i = 0; i < D; i++)
        {
            x[i] = max(0.0, height-alpha[i]);

            //�ۼ�x[i]��Ϊ������
            curVolume += x[i];
            
        }

        //x[i]�ۼ�ֵ��Ŀ��ֵ1�����С��10��-12�η�����Ϊ���
        if (fabs(curVolume - 1.0) < 1e-12) break;
        else
        {
            //���ۼ�ֵ����1������ѡheight����
            if (curVolume > 1.0)
            {
                //���˴�ѭ����height��Ϊ���ٽ�
                right = height;
                
            }

            //���ۼ�ֵС��1������ѡheight����
            if (curVolume < 1.0)
            {
                //���˴�ѭ����height��Ϊ���ٽ�
                left = height;
            }
        }     
    } while (1);

    //�涨�����ȷ�ȵ�С�����10λ
    cout << fixed << setprecision(10);
    cout << "ѭ������ʱ����Ϊ��" << curVolume << endl << endl;
}

//��������ֵ
double BestValue(double* alpha, double* x)
{
    double sum = 0;
    for (int i = 0; i < D; i++)

        sum += -log(alpha[i] + x[i]) / log(exp(1));

    return sum;
}



int main() {
    double alpha[D] = { 0 };
    double x[D] = { 0 };
    double height = 0;

    // �����������
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //�������ʵ�����õ�20��alpha�����ķ�������
    //�ο���Χ��0��1��
    //����Ϊ10^(-10)
    for (int i = 0; i < D; ++i) {
        alpha[i] = static_cast<double>(rand()) / RAND_MAX;  // ���ɣ�0��1���ڵ����������
        alpha[i] = std::round(alpha[i] * 1e11) / 1e11;  // ���ƾ��ȵ�С�����10λ
        
    }

    //�����Ž�
    Solution(alpha, x, height);

    cout << fixed << setprecision(10);
    //���alpha������20������
    cout << "alpha��20������:" << endl;
    for (int i = 0; i < D; ++i) {
        cout << "alpha[" << i << "] = " << alpha[i] << endl;
    }
    cout << endl;

    //������Ž��20������
    cout << "x*��20������:" << endl;
    for (int i = 0; i < D; ++i) {
        cout << "x[" << i << "] = " << double(x[i]) << endl;
    }

    //�����Ӧ����
    cout << endl<< "1/v*��ֵ:" << height << endl;

    //���ԭ���������ֵ
    cout << endl << "p*��ֵ:" << BestValue(alpha, x) << endl;

    return 0;
}
