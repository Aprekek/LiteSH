#include <iostream>
#include <csignal>
 
using namespace std;
/*Функция  signal  позволяет  программе  определить, как
      следует обрабатывать сигналы от операционной  системы*/

sig_atomic_t signalled = 0;

void handler(int sig)
{
    signalled = 1;
}

void SignalHandler(const int sig)
{
    //Выполнение нужных действий
    SetSigActionToDefault(sig);
}
 
void SetSigActionToDefault(const int setSignal)
{
    sigset_t    mySig;
    sigemptyset(&mySig);//инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов
    sigaddset(&mySig, setSignal);//добавляют сигналы signum к set и удаляют эти сигналы из набора соответственно
    sigprocmask(SIG_UNBLOCK, &mySig, NULL); //используется для изменения действий процесса при получении соответствующего сигнала
    signal(setSignal, SIG_DFL); //обработка сигнала
    kill(getpid(), setSignal);
    signal(setSignal, SignalHandler);
}
//signal(SIGTSTP, SignalHandler);

//Если группа процессов запускается как фоновое задание, оболочка сама должна оставаться на переднем плане и продолжать читать команды с терминала.

/* Put a job in the background.  If the cont argument is true, send
   the process group a SIGCONT signal to wake it up.  */

void putJobBackground (job *j, int cont)
{
  /* Send the job a continue signal, if necessary.  */
  if (cont)//0 or 1
    if (kill (-j->pgid, SIGCONT) < 0)
      perror ("kill (SIGCONT)");
}



int main()
{
    signal(SIGINT, handler);//Прерывание CTRL+C
    
    raise(SIGINT);//посылает исполняющейся в текущий момент программе сигнал, который задается параметром signal
	while (true)
	{
		if (signalled)
		    cout << "Signal is handled\n";
		else
		    cout << "Signal is not handled\n";
	}
    return 0;
}
