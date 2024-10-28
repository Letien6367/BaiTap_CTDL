// Le Minh Tien - 233026 - DH23TIN01 - xu li file  
// Lao Trong Duc - 232543 - DH23TIN01 - sua
// Le Thanh Dat - 232768 - DH23TIN01 - them
// Nguyen Chi Cong  - 232685 - DH23TIN01 - tim kiem 
// Duong Phuoc Duy  - 232831 - DH23TIN01 -  xóa
// Nguyen Duong Khanh - 232832 - DH23TIN01 - in danh sach có diem >= diem cu the 
// Trinh Gia Huy - 232661 -  DH23TIN01 - sap Xep
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Dinh nghia kieu du lieu
struct QLSV
{
    char maSV[10];
    char hoTen[30];
    char ngaySinh[10];
    char gioiTinh[5];
    float diemHocPhan;
};

// Dinh nghia ten file
#define filename "danh_sach_sinh_vien.txt"

typedef struct QLSV ElementType;

typedef struct Node
{
    ElementType Element;
    struct Node *Next; // dia chi cua phan tu tiep theo
    struct Node *Prev; // dia chi cua phan tu truoc
} Node;

typedef Node *PtrToNode;
typedef PtrToNode Position;
typedef PtrToNode List;

void Makenull_List(List *L);
int IsEmpty_List(List L);
int IsLast(Position P);

void Insert_List(ElementType X, Position P, List L);
void Delete_List(List L);
Position Header(List L);
Position First_List(List L);
Position End_List(List L);
Position Advance(Position P);
ElementType Retrieve(Position P);
void Read_List(List L);
void Write_List(List L);
void Save_List(List L);
void Them(List L);
void Sua(List L);
void Xoa(List L);
void Menu(List L);
void SapXepTangDan(List L);
void SapXepGiamDan(List L);
void TimKiemTheoMSSV(List L);
void XuatDiemLonHonX(List L);
int Kt_MSSV(List L, char maSV[10]);

/* MAIN PROGRAM */
int main()
{
    List L;
    Makenull_List(&L);
    Menu(L);
    return 0;
}

/* Cai dat cac ham*/
/*Tao 1 danh sach rong*/
void Makenull_List(List *L)
{
    *L = (Node *)malloc(sizeof(Node));
    if (*L == NULL)
    {
        printf("Khong du bo nho");
        exit(1);
    }
    (*L)->Next = NULL;
    (*L)->Prev = NULL;
}

/* Kiem tra danh sach rong? */
int IsEmpty_List(List L)
{
    return L->Next == NULL;
}

/* Kiem tra P co tro den phan tu cuoi cua ds khong? */
int IsLast(Position P)
{
    return P->Next == NULL;
}

/* Chen 1 phan tu vao danh sach */
void Insert_List(ElementType X, Position P, List L)
{
    Position TmpCell;
    TmpCell = (Node *)malloc(sizeof(Node));

    if (TmpCell == NULL)
    {
        printf("Khong du bo nho");
        exit(1);
    }
    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    TmpCell->Prev = P;
    if (P->Next != NULL)
        P->Next->Prev = TmpCell;
    P->Next = TmpCell;
}

/* Tim phan tu header */
Position Header(List L)
{
    return L;
}

/*Tim phan tu cuoi cung*/
Position End_List(List L)
{
    Position P;
    P = L;
    while (P->Next != NULL)
        P = P->Next;
    return P;
}
/* Tim phan tu dau tien */
Position First_List(List L)
{
    return L->Next;
}

/* Tim phan tu ke tiep */
Position Advance(Position P)
{
    return P->Next;
}

/* Tim gia tri cua 1 phan tu */
ElementType Retrieve(Position P)
{
    return P->Element;
}

/* Xoa danh sach */
void Delete_List(Position P, List *L)
{
    if (*L == NULL)
    {
        printf("Danh sach rong!");
    }
    else
    {
        if (P == *L)
            (*L) = (*L)->Next;
        else
            P->Prev->Next = P->Next;
        if (P->Next != NULL)
            P->Next->Prev = P->Prev;
        free(P);
    }
}

/* Nhap danh sach */
void Read_List(List L)
{
    int i, n;
    float diemhocphan;
    ElementType x;
    Position P;
    printf("So sinh vien trong danh sach = ");
    scanf("%d", &n);
    P = Header(L);
    i = 1;
    while (i <= n)
    {
        // Xoa bo nho dem
        fflush(stdin);
        printf("\nSinh vien thu %d = \n", i);
        printf(" Nhap ma sinh vien: ");
        gets(x.maSV);
        printf(" Nhap ho ten: ");
        gets(x.hoTen);
        printf(" Nhap ngay sinh: ");
        gets(x.ngaySinh);
        printf(" Nhap gioi tinh: ");
        gets(x.gioiTinh);
        do
        {
            printf(" Nhap diem hoc phan (0 - 10): ");
            scanf("%f", &diemhocphan);
        } while (diemhocphan < 0 || diemhocphan > 10);
        x.diemHocPhan = diemhocphan;
        Insert_List(x, P, L); // Chen x vao sau vi tri P
        P = P->Next;
        i++;
    }
    Save_List(L);
    system("cls");
}

/* In danh sach */
void Write_List(List L)
{
    // Mo file de doc
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Khong the mo file de ghi!");
        return;
    }
    Position P;
    if (!IsEmpty_List(L))
    {
        P = First_List(L);
        while (P != NULL)
        {
            // Doc tu file
            fscanf(file, "%9s - %[^-] - %9s - %4s - %f", P->Element.maSV, P->Element.hoTen, P->Element.ngaySinh, P->Element.gioiTinh, &P->Element.diemHocPhan);
            printf("\nMa sinh vien: %s", P->Element.maSV);
            printf("\nHo ten: %s", P->Element.hoTen);
            printf("\nNgay sinh: %s", P->Element.ngaySinh);
            printf("\nGioi tinh: %s", P->Element.gioiTinh);
            printf("\nDiem hoc phan: %.2f", P->Element.diemHocPhan);
            P = P->Next;
        }
    }
    else
        printf("List is empty!");
    printf("\n");
    fclose(file);
}

/* Luu danh sach vao file */
void Save_List(List L)
{
    // Mo file de ghi
    FILE *file = fopen(filename, "w");
    if (!file)
    {
        printf("Khong the mo file de ghi!");
        return;
    }
    Position P;
    if (!IsEmpty_List(L))
    {
        P = First_List(L);
        while (P != NULL)
        {
            // Ghi vao file
            fprintf(file, "%s - %s - %s - %s - %.2f\n", P->Element.maSV, P->Element.hoTen, P->Element.ngaySinh, P->Element.gioiTinh, P->Element.diemHocPhan);
            P = P->Next;
        }
    }
    fclose(file);
}

/*Kiem tra ma sinh vien co ton tai trong danh sach hay khong*/
int Kt_MSSV(List L, char maSV[10])
{
    Position P;
    P = First_List(L);
    if (IsEmpty_List(L))
    {
        return 0;
    }
    while (P != NULL)
    {
        if (strcmp(P->Element.maSV, maSV) == 0)
        {
            return 1;
        }
        P = P->Next;
    }
    return 0;
}
/* Them sinh vien */
void Them(List L)
{
    int i, n;
    float diemhocphan = 0;
    ElementType x;
    Position P;
    printf("So sinh vien can them vao danh sach: ");
    scanf("%d", &n);
    P = End_List(L);
    i = 1;
    while (i <= n)
    {
        // Xoa bo nho dem
        fflush(stdin);
        printf("\nSinh vien thu %d = \n", i);
        do
        {
            printf(" Nhap ma sinh vien: ");
            gets(x.maSV);
            if (Kt_MSSV(L, x.maSV) == 1)
            {
                printf("Ma sinh vien da ton tai. Vui long nhap lai.\n");
            }
        } while (Kt_MSSV(L, x.maSV) == 1);
        printf(" Nhap ho ten: ");
        gets(x.hoTen);
        printf(" Nhap ngay sinh: ");
        gets(x.ngaySinh);
        printf(" Nhap gioi tinh: ");
        gets(x.gioiTinh);
        do
        {
            printf(" Nhap diem hoc phan: ");
            scanf("%f", &diemhocphan);
            if (diemhocphan < 0 || diemhocphan > 10)
            {
                printf("Diem hoc phan khong hop le. Vui long nhap lai.\n");
            }
        } while (diemhocphan < 0 || diemhocphan > 10);
        x.diemHocPhan = diemhocphan;
        Insert_List(x, P, L); // Chen x vao sau vi tri P
        P = P->Next;
        i++;
    }
    printf("\nThem sinh vien thanh cong.\n");
    Save_List(L);
}
/* Sua thong tin sinh vien */
void Sua(List L)
{
    char maSV[10];
    Position P;
    ElementType x;
    P = First_List(L);
    do
    {
        printf("Nhap ma sinh vien can sua: ");
        gets(maSV);
        if (Kt_MSSV(L, maSV) == 0)
        {
            printf("Ma sinh vien khong ton tai. Vui long nhap lai.\n");
        }
    } while (Kt_MSSV(L, maSV) == 0);
    if (IsEmpty_List(L))
    {
        printf("Danh sach rong!\n");
        return;
    }
    while (P != NULL)
    {
        if (strcmp(P->Element.maSV, maSV) == 0)
        {
            // Xoa bo nho dem
            fflush(stdin);
            printf("\nSinh vien can sua = \n");
            do
            {
                printf(" Nhap ma sinh vien: ");
                gets(x.maSV);
                if (Kt_MSSV(L, x.maSV) == 1)
                {
                    printf("Ma sinh vien da ton tai. Vui long nhap lai.\n");
                }
            } while (Kt_MSSV(L, x.maSV) == 1);
            printf(" Nhap ho ten: ");
            gets(x.hoTen);
            printf(" Nhap ngay sinh: ");
            gets(x.ngaySinh);
            printf(" Nhap gioi tinh: ");
            gets(x.gioiTinh);
            do
            {
                printf(" Nhap diem hoc phan (0 - 10): ");
                scanf("%f", &x.diemHocPhan);
                if (x.diemHocPhan < 0 || x.diemHocPhan > 10)
                {
                    printf("Diem hoc phan khong hop le. Vui long nhap lai.\n");
                }
            } while (x.diemHocPhan < 0 || x.diemHocPhan > 10);
            P->Element = x;
            printf("\nSua thong tin sinh vien thanh cong.\n");
            break;
        }
        P = P->Next;
    }
    Save_List(L);
}
/* Xoa sinh vien */
void Xoa(List L)
{
    int count = 0;
    char maSV[10];
    Position P, TmpCell;
    P = First_List(L);
    if (!IsEmpty_List(L))
    {
        printf("Nhap ma sinh vien can xoa: ");
        gets(maSV);
        P = First_List(L);
        while (P != NULL)
        {
            if (strcmp(P->Element.maSV, maSV) == 0)
            {
                count++;
                Delete_List(P, &L);
                printf("\nXoa sinh vien thanh cong.\n");
                break;
            }
            P = P->Next;
        }
        if (count == 0)
        {
            printf("\nKhong tim thay sinh vien co ma sinh vien la %s.\n", maSV);
        }
    }
    else
        printf("List is empty!");

    Save_List(L);
}
/* Menu */
void Menu(List L)
{
    system("cls");
    int choice;
    do
    {
        printf("\n\nMenu:");
        printf("\n1. Them sinh vien");
        printf("\n2. Sua thong tin sinh vien");
        printf("\n3. Xoa sinh vien");
        printf("\n4. In danh sach sinh vien");
        printf("\n5. Sap xep danh sach tang dan theo diem");
        printf("\n6. Sap xep danh sach giam dan theo diem");
        printf("\n7. Tim kiem sinh vien theo MSSV");
        printf("\n8. Xuat danh sach sinh vien co diem >= X");
        printf("\n9. Thoat");
        printf("\nNhap lua chon cua ban: ");
        scanf("%d", &choice);
        system("cls");
        fflush(stdin);
        switch (choice)
        {
        case 1:
            system("cls");
            Them(L);
            break;
        case 2:
            system("cls");
            Sua(L);
            break;
        case 3:
            system("cls");
            Xoa(L);
            break;
        case 4:
            system("cls");
            Write_List(L);
            break;
        case 5:
            system("cls");
            printf("\nDanh sach sau khi sap xep tang dan theo diem hoc phan: \n");
            SapXepTangDan(L);
            Write_List(L);
            break;
        case 6:
            system("cls");
            printf("\nDanh sach sau khi sap xep giam dan theo diem hoc phan: \n");
            SapXepGiamDan(L);
            Write_List(L);
            break;
        case 7:
            system("cls");
            printf("\nTim kiem sinh vien theo MSSV: \n");
            TimKiemTheoMSSV(L);
            break;
        case 8:
            system("cls");
            XuatDiemLonHonX(L);
            break;
        case 9:
            system("cls");
            printf("\nThoat chuong trinh.\n");
            return;
        default:
            system("cls");
            printf("\nLua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 9);
}
/* Sap xep danh sach tang dan theo diem hoc phan */
void SapXepTangDan(List L)
{
    if (IsEmpty_List(L))
    {
        printf("Danh sach rong!\n");
        return;
    }
    Position i, j, min;
    ElementType temp;
    for (i = First_List(L); i->Next != NULL; i = i->Next)
    {
        min = i;
        for (j = i->Next; j != NULL; j = j->Next)
        {
            if (j->Element.diemHocPhan < min->Element.diemHocPhan)
            {
                min = j;
            }
        }
        if (min != i)
        {
            temp = i->Element;
            i->Element = min->Element;
            min->Element = temp;
        }
    }
    Save_List(L);
}
/* Sap xep danh sach giam dan theo diem hoc phan */
void SapXepGiamDan(List L)
{
    if (IsEmpty_List(L))
    {
        printf("Danh sach rong!\n");
        return;
    }
    Position i, j, max;
    ElementType temp;
    for (i = First_List(L); i->Next != NULL; i = i->Next)
    {
        max = i;
        for (j = i->Next; j != NULL; j = j->Next)
        {
            if (j->Element.diemHocPhan > max->Element.diemHocPhan)
            {
                max = j;
            }
        }
        if (max != i)
        {
            temp = i->Element;
            i->Element = max->Element;
            max->Element = temp;
        }
    }
    Save_List(L);
}
/* Tim kiem sinh vien theo MSSV */
void TimKiemTheoMSSV(List L)
{
    char maSV[10];
    int count = 0;
    Position P;
    P = First_List(L);
    if (IsEmpty_List(L))
    {
        printf("Danh sach rong!\n");
        return;
    }
    do
    {
        printf("Nhap ma sinh vien can tim: ");
        gets(maSV);
        if (Kt_MSSV(L, maSV) == 0)
        {
            printf("Ma sinh vien khong ton tai. Vui long nhap lai.\n");
        }
    } while (Kt_MSSV(L, maSV) == 0);
    while (P != NULL)
    {
        if (strcmp(P->Element.maSV, maSV) == 0)
        {
            count++;
            printf("\nMa sinh vien: %s", P->Element.maSV);
            printf("\nHo ten: %s", P->Element.hoTen);
            printf("\nNgay sinh: %s", P->Element.ngaySinh);
            printf("\nGioi tinh: %s", P->Element.gioiTinh);
            printf("\nDiem hoc phan: %.2f", P->Element.diemHocPhan);
            break;
        }
        P = P->Next;
    }
    if (count == 0)
    {
        printf("\nKhong tim thay sinh vien co ma sinh vien la %s.\n", maSV);
    }
}
/* Xuat danh sach sinh vien co diem >= X */
void XuatDiemLonHonX(List L)
{
    Position P;
    int x, count = 0;
    if (!IsEmpty_List(L))
    {
        do
        {
            printf("Nhap diem >= x (0-10) ð? t?m: ");
            scanf("%d", &x);
            if (x < 0 || x > 10)
            {
                printf("Diem hoc phan khong hop le. Vui long nhap lai.\n");
            }
        } while (x < 0 || x > 10);
        printf("Danh sach sinh vien co diem >= %d: \n", x);
        P = First_List(L);
        while (P != NULL)
        {
            if (P->Element.diemHocPhan >= x)
            {
                count++;
                printf("\nMa sinh vien: %s", P->Element.maSV);
                printf("\nHo ten: %s", P->Element.hoTen);
                printf("\nNgay sinh: %s", P->Element.ngaySinh);
                printf("\nGioi tinh: %s", P->Element.gioiTinh);
                printf("\nDiem hoc phan: %.2f", P->Element.diemHocPhan);
            }
            P = P->Next;
        }
        if (count == 0)
        {
            printf("\nKhong co sinh vien nao co diem >= %d.\n", x);
        }
    }
    else
        printf("List is empty!");
    printf("\n");
}
