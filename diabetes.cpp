
#include <iostream>
#include <string>
#include <fstream>
#include "Preceptron.cpp"
#include "V_Nearest_Neighbors.cpp"



using namespace std;


const int max_data = 768;
int c = 0;
//396541
int n_iter = 20395;
int has_diabetes = 0;
int no_diabetes = 0;
int test_x = 25; //age
int test_y = 80; //glucose levels
float xRange = 0.0;
float yRange = 0.0;
float eta = 0.01;
float update = 0.0;
float glucose[max_data];
float age[max_data];
float target[max_data];
string string_target[max_data];
string string_glucose[max_data];
string string_age[max_data];
string raw_data[max_data];
string procesed_data[max_data][9];
float weight[3];
float calc_prediction = 0;


/*
float calculate(int i)
{
   //cout << weight[1] << "==" << age[i] << endl;
   calc_prediction = ((weight[1] * age[i]) + (weight[2] * glucose[i])) + weight[0];
   return calc_prediction;
}


float predict(int i)
{
   if(calculate(i) >= 0)
   {
       return 1;
   }
   else
   {
       return -1;
   }
}


void preceptron_learning_algorithim()
{
   weight[0] = 0.0;
   weight[1] = 0.0;
   weight[2] = 0.0;
   c = 0;
   for(int j = 0; j <= n_iter - 1; j++)
   {
       for(int i = 0; i <= max_data - 1; i++)
       {
           update = eta * (target[i] - predict(i));
           //cout << c << "| " << update << "| " << age[i] << "| " << glucose[i] << "| " << weight[1] << "| " << weight[2] << "| " << calculate(i) << endl;
           weight[0] += update;
           weight[1] += update * age[i];
           weight[2] += update * glucose[i];
           c += 1;
       }
   }
   cout << "----> ["<< weight[0] << ", " << weight[1] << ", " << weight[2] << "]" << endl;
}


*/
int main()
{
   ifstream file;
   file.open("Diabetes.data");
   string line;


   for(int i = 0; i <= max_data; i++)
   {
       raw_data[i] = line;
       getline(file, line);
   }
   file.close();
  
   for(int j = 0; j <= max_data - 1; j++)
   {
       c = 0;
       for(int i = 0; i <= raw_data[j + 1].length() - 1; i++)
       {
           if(raw_data[j + 1].at(i) == ',' || raw_data[j + 1].at(i) == '\n')
           {
               c += 1;
               i += 1;
           }
           procesed_data[j][c] += raw_data[j + 1].at(i);
       }
   }
  


   for(int i = 0; i <= max_data - 1; i++)
   {
       string_glucose[i] = procesed_data[i][1];
       glucose[i] = stof(string_glucose[i]);
       string_age[i] = procesed_data[i][7];
       age[i] = stof(string_age[i]);
       string_target[i] = procesed_data[i][8];
       target[i] = stof(string_target[i]);


       if(target[i] == 0)
       {
           target[i] = 1;
       }
       else
       {
           target[i] = -1;
       }
   }
   //preceptron_learning_algorithim();
   cout << "Testing Algorithims with values " << test_x << " " << test_y << ", age and glucose respectively." << endl;
   Preceptron p;
   float has_diabetes_preceptron = p.Preceptron_learning_algorithim(n_iter, eta, age, glucose, target, test_x, test_y);
   cout << "According to Preceptron Alrogithim : " << has_diabetes_preceptron << "% has diabetes." << endl;
   V_Nearest_Neighbors v;
   float has_diabetes_vNN = (v.vNN_Algorithim(20.0, test_x, test_y, age, glucose, target)) * 100;
   cout << "According to vNN Algorithim : " << has_diabetes_vNN << "% has diabetes." << endl;
   cout << "Together " << ((has_diabetes_preceptron + has_diabetes_vNN) / 200) * 100 << "% has diabetes." << endl;


}


/*
0 - Pregancy
1 - Glucose
2 - Blood Pressure
3 - Skin Thickness
4 - Insulin
5 - BMI
6 - Diabetes Pedigree Function
7 - Age
8 - Outcome


Notes:


--> Optimal iterations for Preceptron Algorithim for Age v. Glucose is 3991
taking into account all 768 values with 242 errors in the final loop. The
least number of errors are 238 which can be achived with 4073 iterations.
Both of these test cases were tested with learning rates of 0.01 eta.


--> Updates:
Desmos Graph: https://www.desmos.com/calculator/gywvcstpns


>With a general quadratic boundary equation, (calc_prediction = ((weight[1] * x * x) + (weight[2] * y * y) + (weight[3] * x * y) + (weight[4] * x) + (weight[5]) * y) + weight[0];)
Quadratic Equation: w0*x*x + w1*y*y + w2*x*y + w3*x + w4*y + w5
Optimal quadratic boundary achived with weights set to default 1 and 8254 iterations
with a error of 232 out of 768.


>Another solution with quadratic boundary is 396541 iterations with 220 errors out of 768
but with a less promissing boundary despite lower errors.
*/
