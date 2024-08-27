#include <iostream>
#include <string>
#include <fstream>


using namespace std;


class V_Nearest_Neighbors
{
   int has_disease;
   int no_disease;
   float range_x = 0.0;
   float range_y = 0.0;


   public:
   float percent_has_disease;
   float percent_no_disease;
   const static int max_data = 100;
   float range = 0;
   float test_x;
   float test_y;
   float x[max_data];
   float y[max_data];
   float target[max_data];
   int hasDisease;
   int noDisease;
   float vNN_Percent(int hasDisease, int noDisease);
   float vNN_Algorithim(float range, float test_x, float test_y, float x[max_data], float y[max_data], float target[max_data]);
};


float V_Nearest_Neighbors:: vNN_Percent(int hasDisease, int noDisease)
{
   return 0;
}


float V_Nearest_Neighbors:: vNN_Algorithim(float range, float test_x, float test_y, float x[max_data], float y[max_data], float target[max_data])
{
   has_disease = 0;
   no_disease = 0;
   range_x = 0.0;
   range_y = 0.0;
   range_x = 60 * (range/100);
   range_y = 175 * (range/100) * 2.3;
   for(int i = 0; i <= max_data - 1; i++)
   {
       if(x[i] <= (test_x + range_x) && x[i] >= (test_x - range_x) && y[i] <= (test_y + range_y) && y[i] >= (test_y - range_y))
       {
           if(x[i] != test_x && y[i] != test_y)
           {
               if(target[i] == 1)
               {
                   no_disease += 1;
               }
               else if(target[i] == -1)
               {
                   has_disease += 1;
               }
           }
       }
   }
   //cout << "vNN : " << has_disease << " " << no_disease << endl;
   percent_has_disease = float(has_disease) / float(has_disease + no_disease);
   percent_no_disease = float(no_disease) / float(has_disease + no_disease);
   return percent_has_disease;
}
