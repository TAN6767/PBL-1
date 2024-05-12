#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <ctype.h>

#define MAX_SIZE 100
#define Max_Class 30
#define Max_LastName 30
#define Max_FirstName 10
#define Max_FullName 30
#define Max_Date 15
#define Max_Gender 10
#define Max_Address 30
#define Max_FaculityCode 5
#define Max_SchoolYear 5
#define Max_Username 30
#define Max_Password 30

typedef struct 
{
    char Username[Max_Username];
    char Password[Max_Password];
} USER;


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

char FaculityCode[Max_FaculityCode];
char SchoolYear[Max_SchoolYear];
char filename[30];
char ClassName[15];
char ClassFindName[MAX_SIZE];

int StdCount = 0;
char checksort;

void RemoveEnter(char x[])
{
    size_t len = strlen(x);
    if (x[len-1] == '\n')
        x[len-1] = '\0';
}

void MakeNULL(char x[])
{
    for (int i = 0; i < (int) strlen(x) ; i++)
        x[i] = '\0';
}

char* rTrim(char x[])
{
    int i = strlen(x) - 1;
    while (isspace(x[i]))
        i--;
    x[i+1] = '\0';
    return x;
}

char* lTrim(char x[])
{
    int i = 0;
    while (isspace(x[i]))
        i++;
    if (i > 0)
        strcpy(&x[0], &x[i]);
    return x;
}

char* trim(char x[])
{
    rTrim(lTrim(x));
    char *ptr = strstr(x, "  ");
    while(ptr != NULL)
    {
        strcpy(ptr, ptr + 1);
        ptr = strstr(x, "  ");
    }
    return x;
}

char *NameStr(char x[])
{
    trim(x);
    strlwr(x);
    for (int i = 0; i < (int) strlen(x); i++)
        if (i == 0 || (i > 0 && isspace(x[i-1])))
            x[i] = toupper(x[i]);
    return x;
}

void CreateClass(char filename[])
{
    char ClassFile[30];
    sprintf(ClassFile, "%s_%s_List.dat", SchoolYear, FaculityCode);
    FILE *file = fopen(ClassFile, "r");
    if (file == NULL)
    {
        fclose(file);
        file = fopen(ClassFile, "w");
        fprintf(file, "%s\n", filename);
        fclose(file);
    }
    else
    {
        char line[100], temp[100];
        bool check = false;
        while (fgets(line, sizeof(line), file))
        {
            sscanf(line, "%s[^\n]", temp);
            if (strcmp(temp, filename) == 0)
            {
                check = true;
                break;
            }
        }
        if (check == false)
        {
            fclose(file);
            file = fopen(ClassFile, "a");
            fprintf(file, "%s\n", filename);
            fclose(file);
        }
    }
}

void SwapStudent(STUDENT *student1, STUDENT *student2)
{
    STUDENT student_temp = *student1;
    *student1 = *student2;
    *student2 = student_temp;
}

void BubbleSort(STUDENT StudentList[], int StdCount)
{
    for (int i = 0; i < StdCount - 1; i++)
        for (int j = i+1; j < StdCount ; j++)
        {
            if (strcmp(StudentList[i].ID, StudentList[j].ID) == 0)
            {
                if (strcmp(StudentList[i].FirstName, StudentList[j].FirstName) == 0)
                {
                    if (strcmp(StudentList[i].LastName, StudentList[j].LastName) > 0)
                        SwapStudent(&StudentList[i], &StudentList[j]);
                }
                else if (strcmp(StudentList[i].FirstName, StudentList[j].FirstName) > 0)
                    SwapStudent(&StudentList[i], &StudentList[j]);                  
            }
            else if (strcmp(StudentList[i].ID, StudentList[j].ID) > 0)
                SwapStudent(&StudentList[i], &StudentList[j]); 
        }
}

void ReadStudentFile(FILE *file, int *StdCount)
{
    int i = 0;
    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        char LastName[Max_LastName], FirstName[Max_FirstName], Birthday[Max_Date], Gender[Max_Gender], Address[Max_Address], ID[10], Email[30];
        sscanf(line, "%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^:]:%[^\n]", LastName, FirstName, Birthday, Gender, Address, ID, Email);

        strcpy(StudentList[i].ID, ID);
        strcpy(StudentList[i].LastName , LastName);
        strcpy(StudentList[i].FirstName, FirstName);
        strcpy(StudentList[i].Birthday, Birthday);
        strcpy(StudentList[i].Gender, Gender);
        strcpy(StudentList[i].Address, Address);
        strcpy(StudentList[i].email, Email);
        i++;
    }
    *StdCount = i;
    for (i = 0; i < *StdCount; i++)
        if (StudentList[i].ID[0] != '1')
            MakeNULL(StudentList[i].ID);
    for (i = 0; i < *StdCount; i++)
        if (StudentList[i].email[0] != '1')
            MakeNULL(StudentList[i].email);
    for (i = *StdCount ; i > 0 ; i--)
        if (strcmp(StudentList[i].ID, StudentList[i-1].ID) == 0)
            MakeNULL(StudentList[i].ID);
    for (i = *StdCount ; i > 0 ; i-- )
        if (strcmp(StudentList[i].email, StudentList[i-1].email) == 0)
            MakeNULL(StudentList[i].email);
}

void PrintToFile(FILE *file, STUDENT StudentList[], int StdCount)
{
    for (int i =0 ; i < StdCount; i++)
        {
            if (StudentList[i].ID[0] != '1')
                continue;
            else
                fprintf(file, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email);           
        }
        for (int i = 0; i < StdCount; i++)
            if (StudentList[i].ID[0] != '1')
                fprintf(file, "%s:%s:%s:%s:%s::\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address);
}

// void ListClass()
// {
//     if (strcmp(FaculityCode,"101") == 0)
//     {
//         printf("%sC1...\n", SchoolYear);
//         printf("%sCDT...\n", SchoolYear);
//         printf("%sCKHK\n", SchoolYear);   
//     }
//     else if (strcmp(FaculityCode, "102") == 0)
//     {
//         printf("%sT_DT...\n", SchoolYear);
//         printf("%sT_Nhat...\n", SchoolYear);
//         printf("%sT_KHDL...\n", SchoolYear);
//     }
// }

void Input_Student(STUDENT *student)
{
    printf("Nhập họ và lót: ");
    fgets(student->LastName, sizeof(student->LastName), stdin);
    RemoveEnter(student->LastName);
    NameStr(student->LastName);

    printf("Nhập tên: ");
    fgets(student->FirstName, sizeof(student->FirstName), stdin);
    RemoveEnter(student->FirstName);
    NameStr(student->FirstName);

    printf("Nhập ngày tháng năm sinh: ");
    fgets(student->Birthday, sizeof(student->Birthday), stdin);
    RemoveEnter(student->Birthday);
    trim(student->Birthday);

    printf("Nhập giới tính: ");
    fgets(student->Gender, sizeof(student->Gender), stdin);
    RemoveEnter(student->Gender);
    NameStr(student->Gender);

    printf("Nhập địa chỉ: ");
    fgets(student->Address, sizeof(student->Address), stdin);
    RemoveEnter(student->Address);
    NameStr(student->Address);
}

void Add_Student()
{
    int i = 0;
    char choice;
    // ListClass();
    printf("Nhập tên lớp cần thêm sinh viên: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);
    CreateClass(filename);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        fclose(file);
        file = fopen(filename, "w");
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

        file = fopen(filename, "r");
        ReadStudentFile(file, &StdCount);
        fclose(file);

        file = fopen(filename, "w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"0\n");
        
        for (int i = 0; i < StdCount; i++)
            fprintf(file, "%s:%s:%s:%s:%s::\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address);
        fclose(file);
    }
    else
    {
        fclose(file);       
        file = fopen(filename,"a");
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
        file = fopen(filename, "r");
        fscanf(file, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(file, "%c%*c", &checksort);
        ReadStudentFile(file, &StdCount);
        fclose(file);

        file = fopen(filename, "w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"0\n");
        PrintToFile(file, StudentList, StdCount);
        fclose(file);
    }
}

void SortStudent()
{
    printf("Nhập tên lớp cần sắp xếp: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);
    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Lớp %s không tồn tại!\n", ClassName);
        fclose(file);
        return;
    }
    else
    {
        fscanf(file, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(file, "%c%*c", &checksort);
        if (checksort == '1')
        {
            printf("Lớp %s đã được sắp xếp!\n", ClassName);
            return;
        }
        printf("Sắp xếp lớp %s thành công!!!\n",ClassName);
        ReadStudentFile(file, &StdCount);
        fclose(file);
        
        BubbleSort(StudentList, StdCount);

        file = fopen(filename, "w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"1\n");  
        PrintToFile(file, StudentList, StdCount);
        fclose(file);
    }
}

void InsertStudentID()
{
    int count;
    char fileID[20];
    sprintf(fileID, "id_%s_%s.dat", SchoolYear, FaculityCode);
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

    printf("Nhập tên lớp cần cấp mã số sinh viên: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Lớp %s không tồn tại!!!", ClassName);
        return;
    }
    else 
    {
        fscanf(file, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(file, "%c%*c", &checksort);
        if (checksort == '0')
        {
            printf("Vui lòng sắp xếp lớp trước khi cấp mã số sinh viên!!\n");
            return;
        }
        ReadStudentFile(file, &StdCount);
        fclose(file);
        for (int i = 0; i < StdCount ;i ++)
        {
            if (StudentList[i].ID[0] == '1')
                continue;
            char tempID[20];
            sprintf(tempID, "%s%s%04d", FaculityCode, SchoolYear, ++count);
            strcpy(StudentList[i].ID, tempID);
        }

        file = fopen(fileID,"w");
        fprintf(file,"%d",count);
        fclose(file);

        file = fopen(filename,"w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"1\n");
        PrintToFile(file, StudentList, StdCount);
        fclose(file);
    }
}

void InsertEmail()
{
    printf("Nhập tên lớp cần cấp email: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Lớp %s không tồn tại!!!\n", ClassName);
        return;
    }
    else
    {
        fscanf(file, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(file, "%c%*c", &checksort);
        ReadStudentFile(file, &StdCount);
        fclose(file);
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
            printf("Vui lòng cấp mã số sinh viên cho tất cả sinh viên trong lớp %s trước khi cấp email!!!\n",ClassName);
            return;
        }

        for (int i = 0; i < StdCount; i++)
        {
            if (StudentList[i].email[1] == '1')
                continue;
            strcpy(StudentList[i].email, StudentList[i].ID);
            strcat(StudentList[i].email,"@sv.dut.udn.vn");
        }
        file = fopen(filename,"w");
        fprintf(file, "%d\n", StdCount);
        fprintf(file,"1\n");
        PrintToFile(file, StudentList, StdCount);
        fclose(file);
    }
}

void FindStudent()
{
    char ID[10];
    printf("Nhập ID của sinh viên cần tìm kiếm: ");
    fgets(ID, sizeof(ID), stdin);
    RemoveEnter(ID);

    char line[MAX_SIZE], ClassFile[MAX_SIZE];
    bool found = false;
    
    sprintf(ClassFile, "%s_%s_List.dat", SchoolYear, FaculityCode);

    FILE *file = fopen(ClassFile, "r");
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s[^\n]", ClassFindName);
        FILE *f = fopen(ClassFindName, "r");
        if (f == NULL)
            continue;
        fscanf(f, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(f, "%c%*c", &checksort);
        ReadStudentFile(f, &StdCount);
        for (int i = 0; i < StdCount; i++)
        {
            if (strcmp(StudentList[i].ID, ID) == 0)
            {
                found = true;
                printf("Thông tin SV có ID %s:\n",ID);
                printf("Họ và tên: %s %s\n", StudentList[i].LastName, StudentList[i].FirstName);
                printf("Ngày sinh: %s\n",StudentList[i].Birthday);
                printf("Giới tính: %s\n",StudentList[i].Gender);
                printf("Địa chỉ  : %s\n",StudentList[i].Address);
                break;
            }
        }
        fclose(f);
        if (found == true)
            break;
    }
    fclose(file);
    if (found == false)
        printf("Không tìm thấy sinh viên có ID: %s\n", ID);
    
}

void RemoveStudent()
{
    char ID[20];
    printf("Nhập ID của sinh viên cần xóa: ");
    fgets(ID, sizeof(ID), stdin);
    RemoveEnter(ID);

    char line[MAX_SIZE], ClassFile[MAX_SIZE];
    bool found = false;
    
    sprintf(ClassFile, "%s_%s_List.dat", SchoolYear, FaculityCode);

    FILE *file = fopen(ClassFile, "r");
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%s[^\n]", ClassFindName);
        FILE *f = fopen(ClassFindName, "r");
        if (f == NULL)
            continue;
        fscanf(f, "%d%*c", &StdCount);
        StdCount = 0;
        fscanf(f, "%c%*c", &checksort);
        ReadStudentFile(f, &StdCount);
        for (int i = 0; i < StdCount; i++)
        {
            if (strcmp(StudentList[i].ID, ID) == 0)
            {
                found = true;
                for (int j = i; j < StdCount -1; j++)
                    StudentList[j] = StudentList[j+1];
                StdCount--;
                break;
            }
        }
        fclose(f);
        if (found == true)
        {
            f = fopen(ClassFindName, "w");
            fprintf(f, "%d\n", StdCount);
            fprintf(f, "%c\n", checksort);
            for (int i = 0; i < StdCount ; i++)
            {
                fprintf(f, "%s:%s:%s:%s:%s:%s:%s\n", StudentList[i].LastName, StudentList[i].FirstName, StudentList[i].Birthday,
                                StudentList[i].Gender, StudentList[i].Address, StudentList[i].ID, StudentList[i].email);
            }
            fclose(f);
            break;
        }
    }
    fclose(file);
    if (found == false)
        printf("Không tìm thấy sinh viên có ID : %s\n", ID);
}

void PrintToFileReport()
{
    printf("Nhập tên lớp cần in sinh viên ra file: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);
   
    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Lớp %s không tồn tại!!!\n", ClassName);
        return;
    }
    fscanf(file, "%d%*c", &StdCount);
    StdCount = 0;
    fscanf(file, "%c%*c", &checksort);
    ReadStudentFile(file, &StdCount);
    fclose(file);

    sprintf(filename, "%s_%s-report.dat", FaculityCode, ClassName);

    file = fopen(filename, "w");

    fprintf(file, "Danh sách sinh viên lớp %s:\n\n", ClassName);
    fprintf(file, "STT | Mã số sinh viên |           Họ và tên            |  Ngày sinh  | Giới tính |          Địa chỉ          |         Email\n");

    for (int i = 0; i < StdCount; i++)
    {
        strcpy(StudentList[i].FullName, StudentList[i].LastName);
        strcat(StudentList[i].FullName, " ");
        strcat(StudentList[i].FullName, StudentList[i].FirstName);
        fprintf(file, " %-2d |    %-12s | %-30s |  %-10s |    %-3s    | %-25s | %-20s\n", i+1, StudentList[i].ID, StudentList[i].FullName, StudentList[i].Birthday, 
            StudentList[i].Gender, StudentList[i].Address, StudentList[i].email);
    }
    fclose(file);
}

void PrintToScreen()
{
    printf("Nhập tên lớp cần in sinh viên ra màn hình: ");
    fgets(ClassName, sizeof(ClassName), stdin);
    RemoveEnter(ClassName);

    sprintf(filename, "%s_%s.dat", FaculityCode, ClassName);

    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Lớp %s không tồn tại!!!\n", ClassName);
        return;
    }
    fscanf(file, "%d%*c", &StdCount);
    StdCount = 0;
    fscanf(file, "%c%*c", &checksort);
    ReadStudentFile(file, &StdCount);
    fclose(file);
    
    printf("Danh sách sinh viên lớp %s:\n\n", ClassName);
    printf("STT | Mã số sinh viên |           Họ và tên            |  Ngày sinh  | Giới tính |          Địa chỉ          |         Email\n");

    for (int i = 0; i < StdCount; i++)
    {
        strcpy(StudentList[i].FullName, StudentList[i].LastName);
        strcat(StudentList[i].FullName, " ");
        strcat(StudentList[i].FullName, StudentList[i].FirstName);
        printf(" %-2d |    %-12s | %-30s |  %-10s |    %-3s    | %-25s | %-20s\n", i+1, StudentList[i].ID, StudentList[i].FullName, StudentList[i].Birthday, 
            StudentList[i].Gender, StudentList[i].Address, StudentList[i].email);
    }
}

void Start()
{
    do
    {
        printf("\n17: Khóa 2017\n");
        printf("18: Khóa 2018\n");
        printf("19: Khóa 2019\n");
        printf("20: Khóa 2020\n");
        printf("21: Khóa 2021\n");
        printf("22: Khóa 2022\n");
        printf("23: Khóa 2023\n");
        
        printf("\nNhập mã khóa: ");
        fgets(SchoolYear, sizeof(SchoolYear), stdin);
        RemoveEnter(SchoolYear);

        if (strcmp(SchoolYear, "17") != 0 && strcmp(SchoolYear, "18") != 0 && strcmp(SchoolYear, "19") != 0 &&
            strcmp(SchoolYear, "20") != 0 && strcmp(SchoolYear, "21") != 0 && strcmp(SchoolYear, "22") != 0 &&
                strcmp(SchoolYear, "23") != 0)
            printf("Vui lòng nhập lại: \n");
    } while (strcmp(SchoolYear, "17") != 0 && strcmp(SchoolYear, "18") != 0 && strcmp(SchoolYear, "19") != 0 &&
            strcmp(SchoolYear, "20") != 0 && strcmp(SchoolYear, "21") != 0 && strcmp(SchoolYear, "22") != 0 &&
                strcmp(SchoolYear, "23") != 0);

    do
    {
        printf("\n101: Khoa Cơ khí \n");
        printf("102: Khoa Công nghệ thông tin \n");
        printf("103: Khoa Cơ khí giao thông \n");
        printf("104: Khoa CN Nhiệt - Điện lạnh \n");
        printf("105: Khoa Điện \n");
        printf("106: Khoa Điện tử viễn thông \n");
        printf("107: Khoa Hóa \n");
        printf("109: Khoa Xây dựng Cầu - Đường\n");
        printf("110: Khoa Xây dựng Dân dụng - Công nghiệp \n");
        printf("111: Khoa Xây dựng Công trình thủy \n");
        printf("117: Khoa Môi trường \n");
        printf("118: Khoa Quản lí dự án \n");
        printf("121: Khoa Kiến trúc \n");
        printf("123: Khoa Công nghệ tiên tiến \n\n");

        printf("Nhập mã khoa: ");
        fgets(FaculityCode, sizeof(FaculityCode), stdin);
        RemoveEnter(FaculityCode);

        if (strcmp(FaculityCode, "101") != 0 && strcmp(FaculityCode, "102") != 0 && strcmp(FaculityCode, "103") != 0 &&
            strcmp(FaculityCode, "104") != 0 && strcmp(FaculityCode, "105") != 0 && strcmp(FaculityCode, "106") != 0 &&
                strcmp(FaculityCode, "107") != 0 && strcmp(FaculityCode, "109") != 0 && strcmp(FaculityCode, "110") != 0 &&
                    strcmp(FaculityCode, "111") != 0 && strcmp(FaculityCode, "117") != 0 && strcmp(FaculityCode, "118") != 0 &&
                        strcmp(FaculityCode, "121") != 0 && strcmp(FaculityCode, "123") != 0)
            printf("Vui lòng nhập lại!!");
    } while (strcmp(FaculityCode, "101") != 0 && strcmp(FaculityCode, "102") != 0 && strcmp(FaculityCode, "103") != 0 &&
            strcmp(FaculityCode, "104") != 0 && strcmp(FaculityCode, "105") != 0 && strcmp(FaculityCode, "106") != 0 &&
                strcmp(FaculityCode, "107") != 0 && strcmp(FaculityCode, "109") != 0 && strcmp(FaculityCode, "110") != 0 &&
                    strcmp(FaculityCode, "111") != 0 && strcmp(FaculityCode, "117") != 0 && strcmp(FaculityCode, "118") != 0 &&
                        strcmp(FaculityCode, "121") != 0 && strcmp(FaculityCode, "123") != 0);
}

bool Login()
{
    USER user[MAX_SIZE];
    int i = 0, j = 0, count = 0;
    char username[Max_Username];
    char password[Max_Password];
    char ch;
    bool found = false;

    FILE *file = fopen("user.txt", "r");
    if (file == NULL)
    {
        printf("Vui lòng tạo tài khoản trước!!!\n");
        return false;
    }

    char line[100];
    while (fgets(line, sizeof(line), file))
    {
        sscanf(line, "%[^:]:%[^\n]", user[i].Username, user[i].Password);
        i++;
    }
    printf("════ TRANG ĐĂNG NHẬP ════\n\n");
    while (true) 
    {
        j = 0;
        printf("Tên đăng nhập : ");
        fgets(username, sizeof(username), stdin);
        RemoveEnter(username);

        printf("Mật khẩu      : ");
        while (j < Max_Password)    
        {
            ch = getch(); 
            if (ch == '\r' || ch == '\n')  
                break;
            else if (ch == '\b') 
            {
                if (j > 0)
                {
                    j--;
                    printf("\b \b"); 
                }
                else
                    printf("\b");
            }
            else  
            {
                password[j] = ch;
                j++;
                printf("*"); 
            }
            password[j] = '\0';
        }

        for (j = 0; j < i; j++)
        {
            if (strcmp(user[j].Username, username) == 0 && strcmp(user[j].Password, password) == 0)
            {
                found = true;
                break;
            }
        }

        if (found == true)
        {
            printf("\n\nĐăng nhập thành công!!!\n\n");
            Sleep(500);
            for (int i = 0; i < 5; i++)
            {
                printf("\rLoading");
                for (int j = 0; j < 3; j++)
                {
                    printf(".");
                    Sleep(200);
                }
                printf("\b \b \b");
                Sleep(150);
            }
            system("cls");
            return true;
        }  
        else
        {
            system("cls");
            if (count < 3)
            {
                printf("\n\nSai tài khoản hoặc mật khẩu, vui lòng kiểm tra lại!!!\n");
                count++;
            }
        }
        if (count == 3)
            break;
    }
    printf("\nSai quá nhiều lần, thoát chương trình!!!\n");
    return false;
}

void Register()
{
    char username[Max_Username];
    char password[Max_Password];
    printf("═══ TRANG ĐĂNG KÝ ═══\n");
    printf("Tên đăng nhập: ");
    fgets(username, sizeof(username), stdin);
    RemoveEnter(username);
    FILE *file = fopen("user.txt", "a");
    fprintf(file, "%s:", username);
    printf("Mật khẩu: ");
    char ch;
    int j = 0;
    while (j < Max_Password)    
        {
            ch = getch(); 
            if (ch == '\r' || ch == '\n')  
                break;
            else if (ch == '\b') 
            {
                if (j > 0)
                {
                    j--;
                    printf("\b \b"); 
                }
                else
                    printf("\b");
            }
            else  
            {
                password[j] = ch;
                j++;
                printf("*"); 
            }
            password[j] = '\0';
        }
    fprintf(file, "%s\n", password);
    fclose(file);
    printf("\n\nĐăng kí thành công!!!\n\n");
    Sleep(500);
    for (int i = 0; i < 5; i++)
    {
        printf("\rLoading");
        for (int j = 0; j < 3; j++)
        {
            printf(".");
            Sleep(200);
        }
        printf("\b \b \b");
        Sleep(150);
    }
    system("cls");
}

void MENU()
{
    bool nhap = false;
    char key;
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
            printf("    ║ ➢  8.    In danh sách sinh viên ra màn hình     ║\n");
            printf("    ║ ➢  0.    Thoát                                  ║\n");
            printf("    ╚═════════════════════════════════════════════════╝\n\n");
    	    printf("Nhập yêu cầu của bạn: ");
            scanf("%c",&key);
            getchar();
            switch (key)
            {
                case '1':
                    Add_Student();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    break;
                case '2':
                    SortStudent();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    break;
                case '3':
                    RemoveStudent();
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    nhap = true;
                    break;
                case '4':
                    FindStudent();
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    nhap = true;
                    break;
                case '5':
                    InsertStudentID();
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    nhap = true;
                    break;
                case '6': 
                    InsertEmail();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    break;
                case '7':
                    PrintToFileReport();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    break;
                case '8':
                    PrintToScreen();
                    nhap = true;
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    break;
                case '0':
                    printf("\nBạn đã thoát khỏi chương trình thành công!!!");
                    nhap = false;
                    break;
                default:
                    printf("Không có chức năng này!!!\n");
                    printf("Vui lòng nhập lại!!!\n");
                    printf("Nhấn phím bất kì để tiếp tục");
                    getch();
                    nhap = true;
            } 
        } while(nhap);
}

void RunProgram()
{
    SetConsoleOutputCP(65001);
    int choice;
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
        return;
    }
}
