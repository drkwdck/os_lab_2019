#include <sys/types.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        printf("Error while fork");
        return 1;
    }
    else
    {
        if (child_pid == 0)
        {
            execv("sequential",argv);
        }
    }
 
    return 0;
}
