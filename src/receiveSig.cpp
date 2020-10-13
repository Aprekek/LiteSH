#include "fileheader.hpp"

//Получение сигналов
void signal_handler(int signal_num) 
{ 
   cout << "The interrupt signal is (" << signal_num << "). \n"; 
} 
  
void catchSignal() 
{
   int i=0, a=0;
   signal(SIGABRT, signal_handler);   
  // register signal SIGABRT and signal handler   
   cout << "How many signal you want gives?\n";
   cin >> a; 
   while(i!=a)
   { 
      cout << "Signal Handled" << endl;
       i++;
   }
} 
