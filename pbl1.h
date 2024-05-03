#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>

#define MAX_SIZE 100
#define Max_Class 30
#define Max_LastName 20
#define Max_FirstName 7
#define Max_FullName 30
#define Max_Date 12
#define Max_Gender 10
#define Max_Address 20
#define Max_FaculityCode 10

struct Student
{
    char LastName[Max_LastName];
    char FirstName[Max_FirstName];
    char FullName[Max_FullName];
    char Birthday[Max_Date];
    char Gender[Max_Gender];
    char Address[Max_Address];
    char ID[10];
    char email[25];
};
typedef struct Student STUDENT;
STUDENT StudentList[MAX_SIZE];

char FaculityCode[10];
char SchoolYear[10];
char filename[30];
char ClassList[MAX_SIZE][MAX_SIZE];

int StdCount = 0;
int ClasslistCount = 0;

void RemoveEnter(char x[])
{
    size_t len = strlen(x);
    if (x[len-1] == '\n')
    {
        x[len-1] = '\0';
    }
}

void SwapStudent(STUDENT *student1, STUDENT *student2)
{
    STUDENT student_temp = *student1;
    *student1 = *student2;
    *student2 = student_temp;
}

void ReadStudentFile(FILE *file, int *StdCount)
{
    int i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char LastName[Max_LastName], FirstName[Max_FirstName], Birthday[Max_Date], Gender[Max_Gender], Address[Max_Address], ID[10], Email[30];
        sscanf(line, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^\n]", LastName, FirstName, Birthday, Gender, Address, ID, Email);

        strcpy(StudentList[i].LastName , LastName);
        strcpy(StudentList[i].FirstName, FirstName);
        strcpy(StudentList[i].Birthday, Birthday);
        strcpy(StudentList[i].Gender, Gender);
        strcpy(StudentList[i].Address, Address);
        strcpy(StudentList[i].ID, ID);
        strcpy(StudentList[i].email, Email);


        i++;
    }
    *StdCount = i;
    for (i = *StdCount ; i > 0 ; i-- )
    {
        if (strcmp(StudentList[i].ID, StudentList[i-1].ID) == 0)
        {
            for (int j = 0; j < strlen(StudentList[i].ID); j++)
                StudentList[i].ID[j] = '\0';
        }
    }
    for (i = *StdCount ; i > 0 ; i-- )
    {
        if (strcmp(StudentList[i].email, StudentList[i-1].email) == 0)
        {
            for (int j = 0; j < strlen(StudentList[i].email); j++)
                StudentList[i].email[j] = '\0';
        }
    }
}

void Input_Student(STUDENT *student)
{
    printf("Nhập họ và lót: ");
    fgets(student->LastName, sizeof(student->LastName), stdin);
    RemoveEnter(student->LastName);

    printf("Nhập tên: ");
    fgets(student->FirstName, sizeof(student->FirstName), stdin);
    RemoveEnter(student->FirstName);

    printf("Nhập ngày tháng năm sinh: ");
    fgets(student->Birthday, sizeof(student->Birthday), stdin);
    RemoveEnter(student->Birthday);

    printf("Nhập giới tính: ");
    fgets(student->Gender, sizeof(student->Gender), stdin);
    RemoveEnter(student->Gender);

    printf("Nhập địa chỉ: ");
    fgets(student->Address, sizeof(student->Address), stdin);
    RemoveEnter(student->Address);
}

void Add_Student()
{

    int i = 0;
    char choice;
    char ClassName[15];
    printf("Nhập tên lớp cần thêm sinh viên: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.txt", FaculityCode, ClassName);

    FILE *check = fopen(filename, "r");

    if (check == NULL)
    {
        fclose(check);
;
        FILE *file = fopen(filename, "w");

        do
        {
            STUDENT newstudent;

            printf("\nNhập sinh viên thứ %d: \n",i+1);
            Input_Student(&newstudent);
            fprintf(file, "%s:%s:%s:%s:%s::\n", newstudent.LastName, newstudent.FirstName, newstudent.Birthday,
                                newstudent.Gender, newstudent.Address);

            i++;
            do 
            {
                printf("Bạn có muốn tiếp tục không [Y/N] ? ");
                scanf("%c", &choice);
                getchar();
            } while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
        } while (choice != 'N' && choice != 'n');

        fclose(file);

        FILE *input = fopen(filename, "r");
        ReadStudentFile(input, &StdCount);
        fclose(input);

        FILE *new = fopen(filename, "w");
        fprintf(new, "%d\n", StdCount);
        fprintf(new,"0\n");
        
        for (int i = 0; i < StdCount; i++)
            fprintf(new, "%s:%s:%s:%s:%s::\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address);
        fclose(new);
    }
    else
    {
        fclose(check);
        
        FILE *file = fopen(filename,"a");

         do
        {
            STUDENT newstudent;

            printf("\nNhập sinh viên thứ %d: \n",i+1);
            Input_Student(&newstudent);
            fprintf(file, "%s:%s:%s:%s:%s::\n", newstudent.LastName, newstudent.FirstName, newstudent.Birthday,
                                newstudent.Gender, newstudent.Address);
            i++;
            do 
            {
                printf("Bạn có muốn tiếp tục không [Y/N] ? ");
                scanf("%c", &choice);
                getchar();
            } while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y');
        } while (choice != 'N' && choice != 'n');

        fclose(file);
        char checksort;
        FILE *input = fopen(filename, "r");
        fscanf(input, "%[^\n]%*c", &StdCount);
        StdCount = 0;
        fscanf(input, "%[^\n]%*c", &checksort);
        ReadStudentFile(input, &StdCount);
        fclose(input);

        FILE *new = fopen(filename, "w");
        fprintf(new, "%d\n", StdCount);
        fprintf(new,"0\n");
        for (int i = 0 ; i < StdCount; i++)
        {
                fprintf(new, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email); 
        }
        fclose(new);
    }
    
}

void SortStudent()
{
    char ClassName[15];
    printf("Nhập tên lớp cần sắp xếp: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.txt", FaculityCode, ClassName);

    FILE *check = fopen(filename, "r");

    if (check == NULL)
    {
        printf("Lớp chưa tồn tại!\n");
        fclose(check);
        return;
    }
    else
    {
        fscanf(check, "%[^\n]%*c", &StdCount);
        StdCount = 0;
        char checksort;
        fscanf(check, "%[^\n]%*c", &checksort);
        if (checksort == '1')
        {
            printf("Lớp đã được sắp xếp!\n");
            return;
        }
        printf("Sắp xếp lớp %s thành công!!!\n",ClassName);
        ReadStudentFile(check, &StdCount);
        fclose(check);
       for (int i = 0; i < StdCount - 1; i++)
       {
           for (int j = i+1; j < StdCount ; j++)
           {
               if (strcmp(StudentList[i].FirstName, StudentList[j].FirstName) == 0)
               {
                   if (strcmp(StudentList[i].LastName, StudentList[j].LastName) > 0)
                       SwapStudent(&StudentList[i], &StudentList[j]);
               }
               else if (strcmp(StudentList[i].FirstName, StudentList[j].FirstName) > 0)
                   SwapStudent(&StudentList[i], &StudentList[j]);
           }
       }

        FILE *file = fopen(filename, "w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"1\n");
        
        for (int i =0 ; i < StdCount; i++)
        {
            if (StudentList[i].ID[0] != '1')
                fprintf(file, "%s:%s:%s:%s:%s::\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address);
            else if (StudentList[i].email[0] != '1')
            {
                fprintf(file, "%s:%s:%s:%s:%s:%s:\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID);
            }
            else
                fprintf(file, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email);
            
        }
        fclose(file);
    }
}

void InsertStudentID()
{
    int count;
    char fileID[20];
    sprintf(fileID, "id_%s_%s.txt", SchoolYear, FaculityCode);
    FILE *ID = fopen(fileID,"r");
    if (ID == NULL)
    {
        ID = fopen(fileID, "w");
        fprintf(ID,"0");
        fclose(ID);
        ID = fopen(fileID, "r");
    }
    fscanf(ID,"%d",&count);
    fclose(ID);

    char ClassName[15];
    printf("Nhập tên lớp cần cấp mã số sinh viên: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.txt", FaculityCode, ClassName);

    FILE *check = fopen(filename, "r");
    if (check == NULL)
    {
        printf("Lớp %s không tồn tại!!!", ClassName);
    }
    else 
    {
        fscanf(check, "%[^\n]%*c", &StdCount);
        StdCount = 0;
        char checksort;
        fscanf(check, "%[^\n]%*c", &checksort);
        if (checksort == '0')
        {
            printf("Vui lòng sắp xếp lớp trước khi cấp mã số sinh viên!!\n");
            return;
        }
        ReadStudentFile(check, &StdCount);
        fclose(check);
        for (int i = 0; i < StdCount ;i ++)
        {
            if (StudentList[i].ID[0] == '1')
                continue;
            char tempID[20];
            sprintf(tempID, "%s%s%04d", FaculityCode, SchoolYear, ++count);
            strcpy(StudentList[i].ID, tempID);
        }

        FILE *f = fopen(fileID,"w");
        fprintf(f,"%d",count);
        fclose(f);

        FILE *new = fopen(filename,"w");
        fprintf(new, "%d\n", StdCount);
        fprintf(new,"1\n");
        for (int i = 0; i < StdCount; i++)
            fprintf(new, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email);
        fclose(new);
    }
}

void InsertEmail()
{
    char ClassName[15];
    printf("Nhập tên lớp cần cấp email: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.txt", FaculityCode, ClassName);

    FILE *check = fopen(filename, "r");
    if (check == NULL)
    {
        printf("Lớp không tồn tại!!!\n");
    }
    else
    {
        fscanf(check, "%[^\n]%*c", &StdCount);
        StdCount = 0;
        char checksort;
        fscanf(check, "%[^\n]%*c", &checksort);
        ReadStudentFile(check, &StdCount);
        fclose(check);
        bool InsertID = true;
        for (int i = 0; i < StdCount; i++)
        {
            if (StudentList[i].ID[0] != '1')
            {
                InsertID = false;
                break;
            }
        }

        if (!InsertID)
        {
            printf("Vui lòng cấp mã số sinh viên cho tất cả sinh viên trong lớp trước khi cấp email!!!\n");
            return;
        }
        for (int i = 0; i < StdCount; i++)
        {
            if (StudentList[i].email[1] == '1')
                continue;
            strcpy(StudentList[i].email, StudentList[i].ID);
            strcat(StudentList[i].email,"@sv.dut.udn.vn");
        }
        FILE *new = fopen(filename,"w");
        fprintf(new, "%d\n", StdCount);
        fprintf(new,"1\n");
        for (int i = 0; i < StdCount; i++)
            fprintf(new, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email);
        fclose(new);

    }
}

void FindStudent()
{
    
}

void Start()
{
    printf("Nhập mã khóa: ");
    fgets(SchoolYear, sizeof(SchoolYear), stdin);
    RemoveEnter(SchoolYear);

    printf("\n101: Khoa Cơ khí \n");
    printf("102: Khoa Công nghệ thông tin \n");
    printf("103: Khoa Cơ khí giao thông \n");
    printf("104: Khoa CN Nhiệt - Điện lạnh \n");
    printf("105: Khoa Điện \n");
    printf("106: Khoa Điện tử viễn thông \n");
    printf("107: Khoa Hóa \n");
    printf("109: Khoa Xây dựng Cầu - Đường");
    printf("110: Khoa Xây dựng Dân dụng - Công nghiệp \n");
    printf("111: Khoa Xây dựng Công trình thủy \n");
    printf("117: Khoa Môi trường \n");
    printf("118: Khoa Quản lí dự án \n");
    printf("121: Khoa Kiến trúc \n");
    printf("123: Khoa Công nghệ tiên tiến \n\n");

    printf("Nhập mã khoa: ");
    fgets(FaculityCode, sizeof(FaculityCode), stdin);
    RemoveEnter(FaculityCode);
}



void MENU()
{
    bool nhap = false;
    int key;
    do
    	{
            printf("\n\n");
            printf("    ╔═════════════════════════════════════════════════╗\n");
            printf("    ║            QUẢN LÍ DANH SÁCH SINH VIÊN          ║\n");
            printf("    ╠═════════════════════════════════════════════════╣\n");
            printf("    ║ ➢  1.    Thêm sinh viên                         ║\n");
            printf("    ║ ➢  2.    Sắp xếp danh sách                      ║\n");
            printf("    ║ ➢  3.    Xóa sinh viên                          ║\n");
            printf("    ║ ➢  4.    Tìm sinh viên                          ║\n");
            printf("    ║ ➢  5.    Cấp mã sinh viên                       ║\n");
            printf("    ║ ➢  6.    Cấp email                              ║\n");
            printf("    ║ ➢  7.    In danh sách sinh viên ra file         ║\n");
            printf("    ║ ➢  0.    Thoát                                  ║\n");
            printf("    ╚═════════════════════════════════════════════════╝\n\n");

    	    printf("Nhập yêu cầu của bạn: ");
            scanf("%d",&key);
            getchar();
            switch (key)
            {
                case 1:
                    Add_Student();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục\n");
                    getch();
                    break;
                case 2:
                    SortStudent();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục\n");
                    getch();
                    break;
                case 3:
                    nhap = true;
                    break;
                case 4:
                    nhap = true;
                    break;
                case 5:
                    InsertStudentID();
                    printf("Nhấn phím bất kì để tiếp tục\n");
                    getch();
                    nhap = true;
                    break;
                case 6: 
                    InsertEmail();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục\n");
                    getch();
                    break;
                case 7:
                    nhap = true;
                    break;
                case 0: 
                    nhap = false;
                    break;
                default:
                    nhap = true;
            } 
        } while(nhap);
}

void RunProgram()
{
    SetConsoleOutputCP(65001);

    Start();
    MENU();
}
