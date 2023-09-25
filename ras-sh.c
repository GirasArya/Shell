/*
Shell
=====
Shell adalah program yang membuat proses child untuk menjalankan string perintah yang diberikan.
Shell berupa infinite looping yang berisi siklus fork--exec--wait.
Lengkapilah kode berikut ini untuk membuat program shell sederhana!
Contoh masukan dan keluaran
---------------------------
    $ date
    Tue Dec  9 13:34:17 WIB 2014
    $ whoami
    auriza
    $ exit
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// pecah string per kata
void split_words(char *string, char **words)
{
    int i;
    words[0] = strtok(string, " \n");
    for (i = 0; words[i]; i++)
        words[i + 1] = strtok(NULL, " \n");
}

int main()
{
    char cmd[80];   //  string perintah
    char *args[20]; //  argumen string perintah

    while (1)
    {
        //  cetak prompt "$ "
        // puts("Ras personal terminal");

        //  baca string perintah
        fgets(cmd, 80, stdin);

        //  pecah string perintah per argumen
        split_words(cmd, args);
        // puts(args[0]);

        //  jika perintah = "exit"
        //      break
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }

        //  jika perintah = "cd"
        //      ganti direktori
        //      continue
        if (strcmp(args[0], "cd") == 0)
        {
            chdir(args[1]);
            continue;
        }


        //  buat proses child:
        //      exec string perintah
        //      cetak pesan error
        //      keluar dengan kode -1
        pid_t pid;
        char *msg;
        pid = fork();
        if(pid == 0){
            msg = "child";
            execvp(args[0], args);
            perror(args[0]);
            return -1;
        }
        wait(NULL);

        //  tunggu child selesai
    }

    return 0;
}