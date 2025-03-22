#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include<cmath>
#define D 20 //宏定义该问题中的x和alpha向量的维度

using namespace std;


//通过计算水深总和获得原问题最优解x和对应乘子v的倒数(即水的高度height)
//通过二分法来求解
void Solution(double* alpha, double* x, double& height)
{
   
    //对于每一个v计算出一个总容量，初始值设为0
    double curVolume = 0.0;

    //初始范围设置为(0,1)
    double left = 0.0;
    double right = 1.0;


    do {
        //每次循环开始前将curVolume置零
        curVolume = 0.0;

        //取区间中点作为新的height
        height = (left + right) / 2.0;

        //计算在当下的v的标准下的x分量以及curVolume
        for (int i = 0; i < D; i++)
        {
            x[i] = max(0.0, height-alpha[i]);

            //累加x[i]即为总容量
            curVolume += x[i];
            
        }

        //x[i]累加值与目标值1的误差小于10的-12次方，视为相等
        if (fabs(curVolume - 1.0) < 1e-12) break;
        else
        {
            //若累加值大于1，则所选height过高
            if (curVolume > 1.0)
            {
                //将此次循环的height作为上临界
                right = height;
                
            }

            //若累加值小于1，则所选height过低
            if (curVolume < 1.0)
            {
                //将此次循环的height作为下临界
                left = height;
            }
        }     
    } while (1);

    //规定输出精确度到小数点后10位
    cout << fixed << setprecision(10);
    cout << "循环结束时容量为：" << curVolume << endl << endl;
}

//计算最优值
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

    // 设置随机种子
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    //随机生成实验所用的20个alpha向量的分量数据
    //参考范围（0，1）
    //精度为10^(-10)
    for (int i = 0; i < D; ++i) {
        alpha[i] = static_cast<double>(rand()) / RAND_MAX;  // 生成（0，1）内的随机浮点数
        alpha[i] = std::round(alpha[i] * 1e11) / 1e11;  // 限制精度到小数点后10位
        
    }

    //求最优解
    Solution(alpha, x, height);

    cout << fixed << setprecision(10);
    //输出alpha向量的20个分量
    cout << "alpha的20个分量:" << endl;
    for (int i = 0; i < D; ++i) {
        cout << "alpha[" << i << "] = " << alpha[i] << endl;
    }
    cout << endl;

    //输出最优解的20个分量
    cout << "x*的20个分量:" << endl;
    for (int i = 0; i < D; ++i) {
        cout << "x[" << i << "] = " << double(x[i]) << endl;
    }

    //输出对应乘子
    cout << endl<< "1/v*的值:" << height << endl;

    //输出原问题的最优值
    cout << endl << "p*的值:" << BestValue(alpha, x) << endl;

    return 0;
}
