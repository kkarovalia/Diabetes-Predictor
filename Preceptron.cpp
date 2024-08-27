#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;


class Preceptron
{
   float calc_prediction = 0;
   float weight[6];
   float update = 0;
   float eta = 0.01;
   float standard_deviation_x = 0;
   float standard_deviation_y = 0;
   float mean_x = 0;
   float mean_y = 0;
   float total_x = 0;
   float total_y = 0;
   float variance_x = 0;
   float variance_y = 0;
   int n_iter = 100;
   int c = 0;
   int z = 0;
   int test_x;
   int test_y;
   int min_error = 0;


   public:


   const static int max_data = 768;
   int errors = 0;
   int error_array[5481];
   float target[max_data];
   float x[max_data];
   float y[max_data];
   float std_x[max_data];
   float std_y[max_data];
   float Preceptron_learning_algorithim(int n_iter, float eta, float x[max_data], float y[max_data], float target[max_data], int test_x, int test_y);
   float Predict(int i);
   float Calculate(int i);
   float Sign_Predict(float x, float y);
   float Calculate(float x, float y);
   float Sigmoid_Predict(int test_x, int test_y);


};


float Preceptron:: Calculate(float x, float y)
{
   calc_prediction = ((weight[1] * x) + (weight[2] * y)) + weight[0];
   return calc_prediction;
}


float Preceptron:: Sign_Predict(float x, float y)
{
   if(Calculate(x, y) >= 0)
   {
       return 1;
   }
   else
   {
       return -1;
   }
}


float Preceptron:: Sigmoid_Predict(int test_x, int test_y)
{
   if((1 / (1 + exp(-(Calculate(test_x, test_y))))) > 0.5)
   {
       return 1;
   }
   else
   {
       return -1;
   }
}


float Preceptron:: Preceptron_learning_algorithim(int n_iter, float eta, float x[max_data], float y[max_data], float target[max_data], int test_x, int test_y)
{
   //cout << n_iter << " " << max_data << endl;
   weight[0] = 1;
   weight[1] = 1;
   weight[2] = 1;


   min_error = 500;


   c = 0;
   for(int j = 0; j <= n_iter - 1; j++)
   {
       errors = 0;
       for(int i = 0; i <= max_data - 1; i++)
       {
          
           update = eta * (target[i] - Sign_Predict(x[i], y[i]));
           //cout << c << "====> "<< weight[0] << "| " << x[i] << "| " << y[i] << "| " << weight[1] << "| " << weight[2] << "| " << Predict(x[i], y[i]) << "|" << Calculate(x[i], y[i]) << endl;
           weight[0] += update;
           weight[1] += update * x[i];
           weight[2] += update * y[i];
           if(update != 0)
           {
               errors += 1;
           }
           c += 1;


       }
       if(min_error > errors)
       {
           min_error = errors;
           cout << "-> " << j << " " << min_error << endl;
       }
   }
   cout << "----> ["<< weight[0] << ", " << weight[1] << ", " << weight[2] << "]" << endl;
   cout << (-weight[0]/weight[2])/(weight[0]/weight[1]) << "x + " << (-weight[0]/weight[2]) << endl;
   cout << "Error Percent: " << float(min_error) / (float(max_data))  << " " << min_error << endl;
  
   if(Sign_Predict(test_x, test_y) == 1)
   {
       // If the person doesn't have diabetes then the error is what percent they don't have diabetes.
       return (float(min_error) / (float(max_data))) * 100;
   }
   else
   {
       // If the person has diabetes then 100 minus error is what percent they have diabetes.
       return 100 - ((float(min_error) / (float(max_data))) * 100);
   }
  
  //return Sigmoid_Predict(test_x, test_y);
}
