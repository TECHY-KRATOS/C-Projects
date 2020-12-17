#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <io.h>
#include <unistd.h>
#include <conio.h>

void diaryprint();

int Encryptfile();

int deletefile();

int main()
{
    char pass[31];
    char prepass[31];
    char filepass[31];
    int check;
    char diary[2000];
    printf("WELCOME TO DIGITAL DIARY ALL RIGHTS RESERVED TO KRATOS PVT. LTD\n");
    printf("NOTE : This is a beta tester\nGive your valuable feedback to \"ashishcbscboard@gamil.com\"\n");
    FILE *ptr = NULL;
    FILE *fptr2 = NULL;
    FILE *dairyentry = NULL;
    check = mkdir("C:\\Diary_Management");
    if (access("C:\\Diary_Management\\passowrd.txt", F_OK) == 0)
    {
        //printf("file exists\n");
    }
    else
    {
        //printf("file doesn't exist\n");
        ptr = fopen("C:\\Diary_Management\\passowrd.txt", "w");
        printf("Enter your new password :\n");
        gets(pass);
        fputs(pass, ptr);
        fclose(ptr);
        Encryptfile();
        //system("cls");
    }
    fptr2 = fopen("C:\\Diary_Management\\passowrd.txt", "r");
    fscanf(fptr2, "%s", filepass);
    fclose(fptr2);
    printf("Enter your password\n");
    scanf("%s", &prepass);
    if (strcmp(filepass, prepass) == 0)
    {
        //printf("Password is Correct\n");
        dairyentry = fopen("C:\\Diary_Management\\Dairy.txt", "a");
        if (access("C:\\Diary_Management\\Dairy.txt", F_OK) == 0)
        {
            printf("Your Previous logs are below:\n");
            diaryprint(dairyentry);
            printf("Do you to add more stuff press y for YES and n for No\n");
            printf("Press d to delete diary or password\n");
            char stuff[2];
            char chose[2] = "y";
            char del[2] = "d";
            scanf("%s", &stuff);

            if (strcmp(stuff, chose) == 0)
            {
                getwchar();
                gets(diary);
                fputs(diary, dairyentry);
            }

            else if (strcmp(stuff, del) == 0)
            {
                deletefile();
                exit(1);
            }
            else
            {
                exit(1);
            }
        }
        else
        {
            getwchar();
            gets(diary);
            fputs(diary, dairyentry);
            fclose(dairyentry);
        }
    }
    else
    {
        printf("incorrect\n");
        exit(1);
    }
    fclose(dairyentry);
    return 0;
}

int Encryptfile()
{
    char ch;
    FILE * fptr1 ,* fptr2;

    fptr1 = fopen("C:\\Diary_Management\\password.txt","r");

    if (fptr1 == NULL)
    {
        printf("Error while opening file\n");
        printf("Press any key to exit....\n");
        getchar();
        return 0;
    }

    fptr2 = fopen("temp.txt","w");
    if (fptr2 == NULL)
    {
        printf("Error while opening file\n");
        printf("Press any key to exit....\n");
        getchar();
        return 0;
    }

    ch = fgetc(fptr1);
    while (ch != EOF)
    {
        ch = ch+100;
        fputc(ch,fptr2);
        ch = fgetc(fptr1);
    }
    fclose(fptr1);
    fclose(fptr2);
    fptr1 = fopen("C:\\Diary_Management\\password.txt","w");
    if (fptr1 == NULL)
    {
        printf("Error while opening file\n");
        printf("Press any key to exit....\n");
        getchar();
        return 0;
    }
    fptr2 = fopen("temp.txt","r");
    if (fptr2 == NULL)
    {
        printf("Error while opening file\n");
        printf("Press any key to exit....\n");
        getchar();
        return 0;
    }
    ch = fgetc(fptr2);
    while (ch != EOF)
    {
        ch = fputc(ch, fptr1);
        ch = fgetc(fptr2);
    }
    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

void diaryprint()
{
    FILE *diaryentry1;
    char Dairy[2000];
    diaryentry1 = fopen("C:\\Diary_Management\\Dairy.txt", "r");
    fgets(Dairy, 2000, diaryentry1);
    puts(Dairy);
    fclose(diaryentry1);
}

int deletefile()
{
    char oper;
    printf("Press d to delete Dairy\n");
    scanf("%c", &oper);
    if (strcmp(oper, "d") == 0)
    {
        int del = remove("C:\\Diary_Management\\Dairy.txt");
        if (!del)
        {
            printf("The file is Deleted successfully");
        }
        else
        {
            printf("the file is not Deleted");
        }
    }
    else
    {
        return 0;
    }
    return 0;
}

int passwordreset()
{
    char oldpass[16];
    char checkpass[16];
    char newpass[16];
    char confirm[16];
    FILE*password;
    password = fopen("C:\\Diary_Management\\password.txt","w+");
    if (password == NULL)
    {
        printf("Error while opening file\n");
        printf("Press any key to continue...\n");
        getwchar();
        fclose(password);
        return 0;
    }
    fgets(oldpass,16,password);
    printf("Only 3 attempts for security purpose\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d chance\n\n",i+1);
        printf("Enter your Password\n");
        gets(checkpass);
        if (checkpass == oldpass)
        {
            printf("Access granted!\n");
            break;
        }
        else
        {
            printf("Incorrect Password\n");
        }
        
    }
    printf("Enter your new password\n");
    gets(newpass);
    for (int i = 0; i < 3; i++)
    {
        printf("Confirm your password\n");
        gets(confirm);
        if (confirm == newpass)
        {
            fputs(newpass,password);
            printf("Password Changed successfully!\n");
            fclose(password);
            return 0;
        }
        
    }
    printf("Too many attempts\n");
    fclose(password);
    return 0;
}
