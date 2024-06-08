#include<stdio.h>
#include "pbl1_function.h"

int main()
{
    SetConsoleOutputCP(65001);
    int choice;
    system("cls");
    printf("1. Đăng nhập\n");
    printf("2. Đăng kí tài khoản\n");
    printf("3. Thoát chương trình\n");
    printf("\nNhập lựa chọn của bạn: ");
    scanf("%d",&choice);
    getchar();
    switch (choice)
    {
    case 1:
        system("cls");
        if (Login() == true)
        {
        Start();
        MENU();
        }
        break;
    case 2:
        system("cls");
        Register();
        Start();
        MENU();
        break;
    case 3:
        printf("Thoát chương trình thành công!\n");
        return 0;
    }
}
