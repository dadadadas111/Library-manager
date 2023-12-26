#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> 

#define MAX_SIZE 1000
typedef struct
{
    int id;
    char name[60], author[60], publisher[60];
    int publishYear, quantity;
    int borrow;
    char* studentId[100];
} book;


book books[MAX_SIZE];
int size = 0 ;


void readData();

void addBook();
void delBook();

void findBook();
int findById();
int findByName();
int findByAuthor();
int findByPublisher();
int findByPublishYear();

void displayLib();
void displayStudents();

void borrow_return();
void borrowBook();
void returnBook();

void sortBook();
void sortById();
void sortByName();
void sortByAuthor();
void sortByPublisher();
void sortByPublishYear();
void swapBook();
void swapNum();
void swapStr();


int main(){
	int option;
    while(1) 
    { 
        system("cls");
        printf("\n ***************QUAN LY SACH TRONG THU VIEN************  \n");
        printf("\n =========================MENU=========================  \n");
        printf("\n 1.Khoi tao danh sach. \n");
        printf("\n 2.Them mot cuon sach vao danh sach. \n");
        printf("\n 3.Xoa mot cuon sach khoi danh sach. \n");
        printf("\n 4.Tim kiem sach. \n");
        printf("\n 5.Xem danh sach. \n");
        printf("\n 6.Muon/tra sach. \n");
        printf("\n 7.Sap xep danh sach.	\n");
        printf("\n 8.Xem danh sach sinh vien dang muon sach.  \n");
        printf("\n 0.Thoat. \n");
        printf("\n ====================================================== \n");
        printf("Nhap chuc nang : ");
        scanf("%d", &option);
        system("cls");
        switch(option) 
        {
            case 1 :
                readData();
                break;
            case 2 :
                addBook();
                break;
            case 3 :
                delBook();
                break;
            case 4 :
                findBook();
                break;
            case 5 :
                displayLib();
                break;
            case 6 :
                borrow_return();
                break;
            case 7 :
            	sortBook();
            	break;
            case 8 :
            	displayStudents();
            	break;
            case 0 :
                printf(" Chuong trinh ket thuc. \n");
			    getch();
			    return 0;
            default :
                printf(" Khong co chuc nang nay \n");
			    printf(" Hay chon chuc nang khac trong menu \n");
			    printf(" Nhap phim bat ki \n");
			    getch();
			    break;
        }
    }    
    return 0;
}

void readData(){
	char filePath[100];
	printf("Nhap ten file: ");
	fflush(stdin);
	gets(filePath);
	FILE *p = fopen(filePath, "r");
	if (p == NULL){
		printf("Da xay ra loi khi mo file %s \n", filePath);
		getch();
		return;
	}
	char line[100];
	char *tmp;
	while (fgets(line, sizeof(line), p)){
    	tmp = strtok(line, ",");
    	if (tmp == NULL) break;
    	books[size].id = atoi(tmp);
    	tmp = strtok(NULL, ",");
    	strcpy(books[size].name, tmp);
    	tmp = strtok(NULL, ",");
    	strcpy(books[size].author, tmp);
    	tmp = strtok(NULL, ",");
    	strcpy(books[size].publisher, tmp);
    	tmp = strtok(NULL, ",");
    	books[size].publishYear = atoi(tmp);
    	tmp = strtok(NULL, ",");
    	books[size].quantity = atoi(tmp);
    	books[size].borrow = 0;
    	size++;
	}
	printf("Thao tac thanh cong!\n");
	getch();
	fclose(p) ;
}
void addBook(){
	book newBook;
	int i;
	start:
	printf("Nhap ma so sach: ");
    scanf("%d", &newBook.id);
    for ( i = 0; i< size; i++)
    	if (books[i].id == newBook.id) break;
    if (i != size){
    	system("cls");
    	printf("Ma so khong hop le.\n");
    	goto start;
	}
    printf("Nhap ten sach: ");
    fflush(stdin);
    gets(newBook.name);
    printf("Nhap ten tac gia: ");
    fflush(stdin);
    gets(newBook.author);
    printf("Nhap nha xuat ban: ");
    fflush(stdin);
    gets(newBook.publisher);
    printf("Nhap nam xuat ban: ");
    scanf("%d", &newBook.publishYear);
    printf("Nhap so luong sach: ");
    scanf("%d", &newBook.quantity);
    newBook.borrow = 0;
    books[size++] = newBook;
    printf("Thao tac thanh cong!\n");
    getch();
}
void delBook(){
	int id;
	printf("Nhap ma so sach can xoa: ");
	scanf("%d", &id );
	int i, j;
	for (i = 0; i < size; i++){
		if (books[i].id == id ){
			for(j = i; j< size; j++){
				books[j]= books[j+1];
			}
			break;
		}
	}
	if ( i == size){
		printf("Khong tim thay sach co ma so %d.\n", id);
	}
	else {
		printf("Thao tac thanh cong!\n");
		size--;
	}
	getch();
}
void findBook(){
	int option;
	int list[100];
	int len = 0;
	printf("\n1. Tim theo ma so\n");
	printf("\n2. Tim theo ten sach\n");
	printf("\n3. Tim theo tac gia\n");
	printf("\n4. Tim theo nha xuat ban\n");
	printf("\n5. Tim theo nam xuat ban\n");
	printf("\n0. Thoat\n");
	printf("\nNhap lua chon: ");
	scanf("%d", &option);
	switch(option){
		case 1:
			len = findById(list);
			break;
		case 2:
			len = findByName(list);
			break;
		case 3: 
			len = findByAuthor(list);
			break;
		case 4:
			len = findByPublisher(list);
			break;
		case 5:
			len = findByPublishYear(list);
			break;
		default :
            printf("Ket thuc thao tac. \n");
		    getch();
		    return;
	}
	printf("Danh sach tim kiem:\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So luong");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	int i;
	for (i = 0; i < len; i++){
		printf("%10d%30s%25s%20s%16d%15d/%d\n\n", books[list[i]].id, books[list[i]].name, books[list[i]].author, books[list[i]].publisher, books[list[i]].publishYear, books[list[i]].quantity- books[list[i]].borrow, books[list[i]].quantity);
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	getch();
}
int findById( int list[]){
	int id;
	printf("Nhap ma so sach: ");
	scanf("%d", &id);
	int i, j = 0;
	for (i = 0; i < size; i++){
		if (books[i].id == id)
			list[j++] = i;
	}
	return j;
}
int findByName( int list[]){
	char name[60];
	printf("Nhap ten sach: ");
	fflush(stdin);
	gets(name);
	int i, j= 0;
	for (i = 0; i < size; i++){
		if (strcmp(name, books[i].name) == 0)
			list[j++] = i;
	}
	return j;
}
int findByAuthor( int list[]){
	char author[60];
	printf("Nhap ten tac gia: ");
	fflush(stdin);
	gets(author);
	int i, j = 0;
	for (i = 0; i < size; i++){
		if (strcmp(author, books[i].author) == 0)
			list[j++] = i;
	}
	return j;
}
int findByPublisher( int list[]){
	char publisher[60];
	printf("Nhap ten nha xuat ban: ");
	fflush(stdin);
	gets(publisher);
	int i, j = 0;
	for (i = 0; i < size; i++){
		if (strcmp(publisher, books[i].publisher) == 0)
			list[j++] = i;
	}
	return j;
}
int findByPublishYear(int list[]){
	int year;
	printf("Nhap nam xuat ban: ");
	scanf("%d", &year);
	int i, j = 0;
	for (i = 0; i < size; i++){
		if (books[i].publishYear == year)
			list[j++] = i;
	}
	return j;
}


void displayLib(){
	printf("Danh sach hien tai:\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%25s%20s%20s%15s\n", "Ma so sach", "Ten sach", "Ten tac gia", "Nha xuat ban", "Nam xuat ban", "So luong");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	int i;
	for (i = 0; i < size; i++){
		printf("%10d%30s%25s%20s%16d%15d/%d\n\n", books[i].id, books[i].name, books[i].author, books[i].publisher, books[i].publishYear, books[i].quantity- books[i].borrow, books[i].quantity);
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	getch();
}
void displayStudents(){
	printf("Danh sach sinh vien dang muon sach:\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    printf("%10s%30s%30s\n", "Ma so sach", "Ten sach", "Ma so sinh vien");
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	int i, j;
	for (i = 0; i < size; i++){
		if (books[i].borrow){
			j = 0;
			while (j < books[i].borrow){
				printf("%10d%30s%30s\n\n", books[i].id, books[i].name, books[i].studentId[j++] );
			}
		}
			
	}
	printf("------------------------------------------------------------------------------------------------------------------------\n");
	printf("\nBan co muon luu file khong? (Y/N)\n");
	printf("Nhap thao tac: ");
	char option;
	scanf(" %c", &option);
	if (option == 'Y' || option == 'y'){
		FILE *p = fopen("sinh_vien.txt", "w");
		fprintf(p, "%10s%30s%30s\n", "Ma so sach", "Ten sach", "Ma so sinh vien");
		fprintf(p, "------------------------------------------------------------------------------------------------------------------------\n");
		int i, j;
		for (i = 0; i < size; i++){
			if (books[i].borrow){
				j = 0;
				while (j < books[i].borrow){
					fprintf(p, "%10d%30s%30s\n\n", books[i].id, books[i].name, books[i].studentId[j++] );
				}
			}	
		}
		fclose(p);
	}
	printf("\nThao tac thanh cong.\n");
	getch();
}
void borrow_return(){
	int option;
	printf("1.Muon sach.\n\n2.Tra sach.\n\n0.Thoat.\n");
	printf("\nNhap lua chon: ");
	scanf("%d", &option);
	switch (option){
		case 1:
			borrowBook();
			break;
		case 2:
			returnBook();
			break;
	}
	
	getch();
}
void borrowBook(){
	int bookId;
	int i;
	printf("Nhap ma so sach: ");
	scanf("%d", &bookId);
	for (i = 0; i< size; i++){
		if (books[i].id == bookId) break;
	}
	if (i == size || books[i].borrow == books[i].quantity){
		printf("Khong the muon sach nay.");
		return;
	}
	printf("Nhap ma so sinh vien: ");
	books[i].studentId[books[i].borrow] = (char*)malloc(10* sizeof(char));
	fflush(stdin);
	gets(books[i].studentId[books[i].borrow++]);
	printf("\nThao tac thanh cong.\n");
}
void returnBook(){
	char Id[10];
	int bookId;
	int i, j, k;
	printf("Nhap ma so sach: ");
	scanf("%d", &bookId);
	for (i = 0; i< size; i++){
		if (books[i].id == bookId) break;
	}
	if (i == size || books[i].borrow == 0){
		printf("Da xay ra loi.");
		return;
	}
	printf("Nhap ma so sinh vien: ");
	fflush(stdin);
	gets(Id);
	for ( j = 0; j < books[i].borrow; j++){
		if (strcmp(books[i].studentId[j], Id) == 0) break;
	}
	if (j == books[i].borrow) {
		printf("Sinh vien co ma so %s khong muon sach nay.", Id);
		return;
	}
	books[i].borrow--;
	for ( k = j; k < books[i].borrow; k++){
		strcpy(books[i].studentId[k],books[i].studentId[k+1]);
	}
	printf("\nThao tac thanh cong.\n");
}

void swapBook(book *a, book *b){
	swapNum(&a->id, &b->id);
	swapNum(&a->quantity, &b->quantity);
	swapNum(&a->borrow, &b->borrow);
	swapNum(&a->publishYear, &b->publishYear);
	
	swapStr(a->author, b->author);
	swapStr(a->name, b->name);
	swapStr(a->publisher, b->publisher);
}
void swapNum(int *a, int *b){
	int temp = *a;
	*a = *b;
	*b = temp;
}
void swapStr(char* a, char* b){
	char temp[60];
	strcpy(temp, a);
	strcpy(a, b);
	strcpy(b, temp);
}

void sortBook(){
	int option;
	printf("\n1. Sap xep theo ma so sach.\n");
	printf("\n2. Sap xep theo ten sach.\n");
	printf("\n3. Sap xep theo tac gia.\n");
	printf("\n4. Sap xep theo nha xuat ban.\n");
	printf("\n5. Sap xep theo nam xuat ban.\n");
	printf("\n0. Thoat.\n");
	printf("\nNhap lua chon: ");
	scanf("%d", &option);
	switch(option){
		case 1:
			sortById();
			break;
		case 2:
			sortByName();
			break;
		case 3:
			sortByAuthor();
			break;
		case 4:
			sortByPublisher();
			break;
		case 5:
			sortByPublishYear();
			break;
		default:
			printf("Ket thuc thao tac.\n");
			getch();
			return;
	}
	printf("Thao tac thanh cong.\n");
	getch();
}
void sortById(){
	int i, j;
	for (i =0; i< size-1; i++){
		int min_pos = i;
		for (j = i+1; j< size; j++){
			if (books[min_pos].id > books[j].id )
				min_pos = j;
		}
		swapBook( &books[min_pos], &books[i]);
	}
}
void sortByName(){
	int i, j;
	for (i =0; i< size-1; i++){
		int min_pos = i;
		for (j = i+1; j< size; j++){
			if (strcmp(books[min_pos].name , books[j].name) > 0 )
				min_pos = j;
		}
		swapBook( &books[min_pos], &books[i]);
	}
}
void sortByAuthor(){
	int i, j;
	for (i =0; i< size-1; i++){
		int min_pos = i;
		for (j = i+1; j< size; j++){
			if (strcmp(books[min_pos].author , books[j].author) > 0 )
				min_pos = j;
		}
		swapBook( &books[min_pos], &books[i]);
	}
}
void sortByPublisher(){
	int i, j;
	for (i =0; i< size-1; i++){
		int min_pos = i;
		for (j = i+1; j< size; j++){
			if (strcmp(books[min_pos].publisher , books[j].publisher) > 0 )
				min_pos = j;
		}
		swapBook( &books[min_pos], &books[i]);
	}
}
void sortByPublishYear(){
	int i, j;
	for (i =0; i< size-1; i++){
		int min_pos = i;
		for (j = i+1; j< size; j++){
			if (books[min_pos].publishYear > books[j].publishYear )
				min_pos = j;
		}
		swapBook( &books[min_pos], &books[i]);
	}
}

