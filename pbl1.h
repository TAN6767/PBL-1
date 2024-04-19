#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>

#define MAX_SIZE 100
#define max_class 30
#define max_lastname 30
#define max_firstname 10
#define max_fullname 40
#define max_Faculity 3
#define max_Lop 10
#define max_Date 12
#define max_sex 5
#define max_address 30
#define max_emailsv 30
#define max_schoolyear 3

struct SinhVien
{
    char lastname[max_lastname];
    char firstname[max_firstname];
    char fullname[max_fullname];
    char birthday[max_Date];
    char sex[max_sex];
    char address[max_address];
    char ID[100];
    char email[max_emailsv];
    bool checksort;
    bool checkMSSV;
    bool checkemail;
};
typedef struct SinhVien SV;

SV list[MAX_SIZE];
char class[max_class];

int n = 0;
int stdcount;

char faculitycode[max_Faculity];
char schoolyear[max_schoolyear];
char filename[MAX_SIZE];
char ID[10];


void NhapSV(SV *sv);
void NhapSVN(SV list[],int *n);
void SapXepDanhSachSV(SV list[],int n);
void XoaEnter(char x[]);
void CapMaSV(SV list[],int n);
void CapEmailSV(SV list[],int n);
void InDanhSachSV(SV list[],int n);
void TimKiemSV(SV list[], int n);
void XoaSV(SV list[], int n);
void MainMenu();

void XoaEnter(char x[])
{
    size_t len = strlen(x);
	if(x[len-1]=='\n')
    {
		x[len-1]='\0';
    }
}

void SVswap(SV *sv1, SV *sv2)
{
    SV temp = *sv1;
    *sv1 = *sv2;
    *sv2 = temp;
}

void DocFile(int *stdcount)
{
    sprintf(filename, "%s.txt", class);

    FILE *file;

    file = fopen(filename, "r");

    char line[MAX_SIZE];

    *stdcount = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        (*stdcount)++;
    }

    fclose(file);
}

void SapXepBubbleSort(SV list[], int stdcount)
{
    for (int i = 0; i < stdcount - 1; i++)
    {
        for (int j = 0; j < stdcount - i - 1; j++)
        {
            
            int compareFirstname = strcmp(list[j].firstname, list[j + 1].firstname);
            
            if (compareFirstname == 0)
            {
                int compareLastname = strcmp(list[j].lastname, list[j + 1].lastname);
            
                if (compareLastname == 0)
                {
                    int compareBirthday = strcmp(list[j].birthday, list[j + 1].birthday);

                    if (compareBirthday > 0 || strcmp(list[j + 1].birthday, "") == 0)
                    {
                        SVswap(&list[j], &list[j + 1]);
                    }
                }
                else if (compareLastname > 0) // Nếu lastname lớn hơn, hoán đổi chúng
                {
                    SVswap(&list[j], &list[j + 1]);
                }
            }
            else if (compareFirstname > 0)
            {
                SVswap(&list[j], &list[j + 1]);
            }
        }
    }

    for (int i = 0; i< stdcount; i++)
    {
        list[i].checksort = true;
    }
}

void NhapBanDau()
{
    printf("Nhập mã khóa: ");
    scanf("%s", schoolyear);

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
    scanf("%s",faculitycode);

}

void NhapSV(SV *Sv)
{
    printf("Nhap họ lót: "); //Nhập họ và tên lót
    fgets(Sv->lastname,max_lastname,stdin);
    XoaEnter(Sv->lastname);

    printf("Nhập tên: "); // Nhập tên
    fgets(Sv->firstname,max_firstname,stdin);
    XoaEnter(Sv->firstname);

    printf("Nhập ngày sinh: "); // Nhập ngày tháng năm sinh
    fgets(Sv->birthday,max_Date,stdin);
    XoaEnter(Sv->birthday);

    printf("Nhập giới tính: "); // Nhấp giới tính
    fgets(Sv->sex,max_sex,stdin);
    XoaEnter(Sv->sex);

    printf("Nhập địa chỉ: "); // Nhập địa chỉ
    fgets(Sv->address,max_address,stdin);
    XoaEnter(Sv->address);

    strcpy(Sv->fullname,Sv->lastname);
    strcat(Sv->fullname," ");
    strcat(Sv->fullname,Sv->firstname);

    Sv->checksort = false;
    Sv->checkMSSV = false;
    Sv->checkemail = false;
}

void NhapSVN(SV list[],int *n)
{

    int p;
    do
    {
        printf("Nhập số lượng sinh viên cần thêm: "); //Nhập số lương sinh viên thêm vào
        scanf("%d",&p);
        getchar();
        if (p<=0) 
        {
            printf("Số lượng sinh viên không hợp lệ!!!\n");
            printf("Vui lòng nhập lại!!!\n");
            getch();
        }
    } while(p<=0);
    fflush(stdin);
    *n = p;

    int i=0;
    char choice;

    do
    {
        printf("\nNhập sinh viên thứ %d: \n",i+1);
        NhapSV(&list[i]);

        i++;
        *n = i;
        if (i == p)
            break;
        do
        {
            printf("Bạn có muốn tiếp tục không? [y/n]");
            scanf("%c", &choice);
        } while (choice != 'n' && choice != 'N' && choice != 'y' && choice != 'Y' );
        getchar();
        if (choice == 'n') break;
        
    } while (i < p);
}

void TaoFile(SV list[], int n)
{
    sprintf(filename, "%s.txt", class);

    FILE *file;
    file = fopen(filename, "a");

    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%-30s | %-10s | %-3s | %-30s\n", list[i].fullname, list[i].birthday,list[i].sex, list[i].address);
    }

    fclose(file);
}

void PrintToFile(SV list[], int stdcount) 
{
    sprintf(filename, "%s.txt",class ); // Tạo tên file dựa trên tên lớp

    FILE *file;
    file = fopen(filename, "w");
     if (file == NULL) 
        {
            printf("Không thể mở file %s\n", filename);
            return;
        }
    for (int i = 0; i < stdcount; i++) 
    {
       
        if (list[i].checkMSSV == false)
        {

        fprintf(file, "%2d. | %-30s | %-10s | %-3s | %-30s\n", i+1, list[i].fullname, list[i].birthday,list[i].sex, list[i].address);

        }
        else if (list[i].checkemail == false)
        {
            fprintf(file, "%2d. | %-30s | %-10s | %-3s | %-30s| %-20s\n", i+1, list[i].fullname, list[i].birthday, 
                list[i].sex, list[i].address, list[i].ID);
        }
        else 
        {
            fprintf(file, "%2d. | %-30s | %-10s | %-3s | %-30s| %-10s | %-20s\n", i+1, list[i].fullname, list[i].birthday, 
                list[i].sex, list[i].address, list[i].ID, list[i].email);
        }
    }

    fclose(file); 
}

void CapMSSV(SV list[], int stdcount)
{

    for (int i = 0; i< stdcount; i++)
    {
        if (list[i].checksort == false)
        {
            printf("Vui lòng sắp xếp danh sách trước ❌\n");
            return;
        }
    }

    for (int i = 0; i < stdcount; i++)
    {
        char tempID[MAX_SIZE];
        sprintf(tempID, "%s%s%04d",faculitycode, schoolyear, i + 1);

        strcpy(list[i].ID, tempID);
        list[i].checkMSSV = true;
    }
    printf("Cấp MSSV thành công ✅\n");
}

void CapEmail(SV list[], int stdcount)
{
    for (int i = 0 ;i < stdcount;i++)
    {
        if (list[i].checkMSSV == false) 
        {
            printf("Vui lòng cấp MSSV trước ❌\n");
            return ;
        }
    }
    for (int i=0; i < stdcount; i++)
    {
        strcpy(list[i].email,list[i].ID);
        strcat(list[i].email,"@sv.dut.udn.vn");
        list[i].checkemail = true;
    }
    printf("Cấp email thành công ✅\n");
    PrintToFile(list, stdcount);
}

void TimKiemSVtheoID(SV list[], int n, char ID[])
{
    bool found = false;
    for (int i=0; i<n; i++)
    {
        if (strcmp(list[i].ID,ID) == 0)
        {
            found = true;
            printf("Thông tin SV có ID %s:\n",ID);
            printf("Họ và tên: %s\n", list[i].fullname);
            printf("Ngày sinh: %s\n",list[i].birthday);
            printf("Giới tính: %s\n",list[i].sex);
            printf("Địa chỉ: %s\n",list[i].address);
            printf("Mã sinh viên: %s\n",list[i].ID);
        }
    }

    if (found == false)
    {
        printf("Không tìm thấy sinh viên có ID %s!\n",ID);
    }
}

void XoaSVtheoID(SV list[], int stdcount, char ID[])
{
    bool found = false;

    for (int i = 0; i < stdcount ; i++)
    {
        if (strcmp(list[i].ID, ID) == 0)
        {
            found = true;
            for (int j = i ; j < stdcount ; j++)
            {
                list[i] = list[i+1];
            }
            stdcount--;

            FILE *file;
            file = fopen(filename, "w");
            PrintToFile(list, stdcount);
            fclose(file);

        }
        break;
    }

    if (!found) printf("Không tìm thấy sinh viên có ID muốn xóa!!!\n");
}

void GanMang(SV list[])
{
    sprintf(filename, "%s.txt", class);

    FILE *file;
    file = fopen(filename, "r");

    int i;
    char line[MAX_SIZE];

    char fullname[max_fullname], birthday[max_Date], sex[max_sex], address[max_address];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        sscanf(line, "%30s %10s %5s %30s",fullname, birthday, sex, address);

        strcpy(list[i].fullname,fullname);
        strcpy(list[i].birthday,birthday);
        strcpy(list[i].sex, sex);
        strcpy(list[i].address,address);

        i++;
    }

    fclose(file);
}

void XemDanhSachTheoLop()
{
    char class[max_class];
    printf("Nhập lớp cần xem: ");
    fgets(class, sizeof(class), stdin);
    XoaEnter(class); 

    char filename[MAX_SIZE];
    sprintf(filename, "%s.txt", class);

    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Không tìm thấy thông tin sinh viên của lớp %s\n", class);
        return;
    }

    printf("Danh sách sinh viên của lớp %s:\n", class);

    char line[MAX_SIZE];
    while (fgets(line, sizeof(line), file) != NULL)
    {
        printf("%s", line);
    }

    fclose(file);
}

void MainMenu(SV list[])
{
    bool nhap=false;
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
        printf("    ║ ➢  7.    In danh sách sinh viên ra màn hình     ║\n");
        printf("    ║ ➢  0.    Thoát                                  ║\n");
        printf("    ╚═════════════════════════════════════════════════╝\n\n");

    	printf("Nhập yêu cầu của bạn: ");
        scanf("%d",&key);
        getchar();
        switch (key)
        {
            case 1:
                printf("Nhập tên lớp cần thêm sinh viên: ");
                fgets(class, max_class, stdin);
                XoaEnter(class);
                NhapSVN(list,&n);
                
                TaoFile(list, n);
                printf("Bạn đã nhập thành công ✅!\n");
                nhap=true;
                printf("Nhấn phím bất kì để tiếp tục!\n");
                getch();
                break;
            case 2:
                printf("Nhập tên lớp cần sắp xếp: ");
                fgets(class,max_class,stdin);
                XoaEnter(class);
                GanMang(list);
                DocFile(&stdcount);
                SapXepBubbleSort(list,stdcount);
                PrintToFile(list,stdcount);
                printf("Danh sách đã được sắp xếp ✅\n");
                printf("Nhấn phím bất kì để tiếp tục!\n");
                getch();
                nhap = true;
                break;
            case 3:
                printf("Nhập ID của sinh viên muốn xóa: ");
                fgets(ID,10,stdin);
                XoaEnter(ID);
                XoaSVtheoID(list,stdcount,ID);
                getch();
                nhap = true;
                break;
            case 4:
                printf("Nhập ID của sinh viên cần tìm kiếm: ");
                fgets(ID,10,stdin);
                XoaEnter(ID);
                TimKiemSVtheoID(list,stdcount,ID);
                getch();
                nhap = true;
                break;
            case 5:
                printf("Nhập tên lớp cần cấp MSSV: ");
                fgets(class,max_class,stdin);
                XoaEnter(class);
                GanMang(list);
                DocFile(&stdcount);
                CapMSSV(list,stdcount);
                printf("Nhấn phím bất kì để tiếp tục!");
                getch();
                nhap = true;
                break;
            case 6:
                printf("Nhập tên lớp cần cấp email: ");
                fgets(class,max_class,stdin);
                XoaEnter(class);
                GanMang(list);
                DocFile(&stdcount);
                CapEmail(list,stdcount);
                printf("Nhấn phím bất kì để tiếp tục!\n");
                getch();
                nhap = true;
                break;
            case 7:
                XemDanhSachTheoLop();
                printf("Nhấn phím bất kì để tiếp tục: ");
                nhap = true;
                getch();
                break;
            case 0:
                nhap = false;
                printf("Bạn đã thoát khỏi chương trình!!!");
                break;
            default:
                printf("Không có chức năng này!!!\n");
                printf("Nhấn phím bất kì để tiếp tục\n");
                getch();
                nhap = true;

        }
    }
    while(nhap);
}

void RunProgram()
{
    NhapBanDau();
    MainMenu(list);
}
