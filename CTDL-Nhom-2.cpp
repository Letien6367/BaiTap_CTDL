// Le Minh Tien - 233026 - DH23TIN01 - sap xep  
// Lao Trong Duc - 232026 - DH23TIN01 - sua
// Le Thanh Dat - 232026 - DH23TIN01 - them
// Nguyen Chi Cong  - 232026 - DH23TIN01 - tim kiem 
// Duong Phuoc Duy  - 232026 - DH23TIN01 -  x�a
// Nguyen Duong Khanh - 233026 - DH23TIN01 - in danh sach c� diem >= diem cu the 
// Trinh Gia Huy - 232026 -  DH23TIN01 -  
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
void Delete_All_List(List L);
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
