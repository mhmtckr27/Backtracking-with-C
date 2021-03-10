#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>

#define PURPLE "mor"	//renk kodu 0
#define BLUE "mavi"		//renk kodu 1
#define YELLOW "sari"	//renk kodu 2
#define BLACK "siyah"	//renk kodu 3
#define GREEN "yesil"	//renk kodu 4
#define PINK "pembe"	//renk kodu 5
#define RED "kirmizi"	//renk kodu 6
#define ORANGE "turuncu"//renk kodu 7

#define MAX_COLORWORD_LENGTH 8

//matrisi yazdiran fonksiyon
void printMatrix(int** matrix, int N)
{
	int i; //dongu degiskeni
	int j; //dongu degiskeni

	//matrisin her bir hucresindeki rengi, soldan hizali sekilde ekrana yazdirma islemi yapilir.
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			if (matrix[i][j] == 0) {
				printf("%-10s", "mor");
			}
			else if (matrix[i][j] == 1) {
				printf("%-10s", "mavi");
			}
			else if (matrix[i][j] == 2) {
				printf("%-10s", "sari");
			}
			else if (matrix[i][j] == 3) {
				printf("%-10s", "siyah");
			}
			else if (matrix[i][j] == 4) {
				printf("%-10s", "yesil");
			}
			else if (matrix[i][j] == 5) {
				printf("%-10s", "pembe");
			}
			else if (matrix[i][j] == 6) {
				printf("%-10s", "kirmizi");
			}
			else if (matrix[i][j] == 7) {
				printf("%-10s", "turuncu");
			}
		}
		printf("\n");
	}
	printf("\n");
}

//matris satirini kaydirma islemini yapan fonksiyon
void shiftRow(int* row, int N)
{
	int temp; //gecici bir degisken, yer degistirme islemi yapilirken kullanilir
	int i; //dongu degiskeni

	//matrisin satirini bir birim kaydirma islemi
	temp = row[N - 1];
	for (i = N; i > 0; i--)
	{
		row[i] = row[i - 1];
	}
	row[0] = temp;
}


//rekursif olarak cagrilip matriste duzenlemeler yapan fonksiyon. 
void backTrack(int** matrix, int N, int rowIndex, int columnIndex, int printType, int* firstRowShiftCount)
{
	int k = 0; //mevcut satirin, kac kez kaydirildigi.(eger N kadar shift edilmesine ragmen sonuc alýnamadiysa onceki satiri kaydirmamiz gerektigini anlariz
	int t = 1; //mevcut satirdan kac onceki satira gitmemiz gerektigini bu degiskende tutariz
	int x = 0; //eger suanki satiri kaydirarak sonuc elde edemiyorsak gidecegimiz satir indisini bunda saklariz (rowIndex - t)

	//eger ilk satira kadar geldiysek
	if (rowIndex == 0)
	{
		//ilk satiri kaydiririz.
		shiftRow(matrix[0], N);
		(*firstRowShiftCount)++;

		//eger ilk satiri N kadar kaydirdiysak ve yine de sonuc alamadiysak, sonuc yoktur.
		if ((*firstRowShiftCount) == N)
		{
			printf("Sonuc yok.\n");
			exit(0);
		}
		return;
	}

	//mevcut satirin her bir sutunu icin
	while (columnIndex < N)
	{
		t = 1;
		//mevcut satirdan onceki satirlara, 0. satira kadar(0. satir dahil) bakariz
		while ((rowIndex - t) > -1)
		{
			//eger ayni renk varsa
			if (matrix[rowIndex - t][columnIndex] == matrix[rowIndex][columnIndex])
			{
				//mevcut satiri kaydiririz
				shiftRow(matrix[rowIndex], N);
				//yeni x hesaplanir
				x = rowIndex - t;
				//tekrar ust satirlara bakmamiz gerekecegi icin t'yi ilk degeri olan 1'e dondururuz
				t = 1;
				//kaydirma sayimizi tutan degiskeni arttiririz.
				k++;
				//tekrar ilk sutundan bakmaya baslariz cunku satir kaydirdigimiz icin ilk sutunlar ayni olmus olabilir
				columnIndex = 0;
			}
			//eger renkler ayni degilse
			else
			{
				//t'yi artirip daha ustteki satira bakariz
				t++;
			}
			//eger kaydirma sayimiz N'i gectiyse
			if (k > N)
			{
				//bu satiri kaydirarak sorun cozulmeyecek demektir. sorun yaratan satiri shift edip o satir icin bu fonksiyonu tekrar cagiririz.
				shiftRow(matrix[x], N);
				backTrack(matrix, N, x, columnIndex, printType, firstRowShiftCount);
			}
		}
		columnIndex++;
	}
	//eger son satirdaysak ve yukaridaki dis while dongusunden cikabildiysek, sonuc alinmis demektir. gerekli yazdirmalar yapilir.
	if (rowIndex == (N - 1))
	{
		//sonuc alindi
		if (printType == 0) {
			printMatrix(matrix, N);
		}
		printf("========================================================================================================\n");
		printf("Sonuc alindi.\n");
		printf("========================================================================================================\n");
		printMatrix(matrix, N);
		exit(0);
	}
	//eger ayrintili yazdirma istenmisse her adimda matrisin yazdirilmasi yapilir.
	if (printType == 0) {
		printMatrix(matrix, N);
	}
	//bu satir icin islemler tamamlandi, sonraki satir icin fonksiyon cagrilir.
	backTrack(matrix, N, rowIndex + 1, 0, printType, firstRowShiftCount);
}

int main()
{
	int N; //matrisin satir/sutun sayisini tutar
	int i; //dongu degiskeni
	int j; //dongu degiskeni
	int printType; //yazdirma tipini tutar
	int* firstRowShiftCount; //ilk satirin kac kez kaydirildigini tutan degisken
	int** matrix; //renk matrisi
	char color[MAX_COLORWORD_LENGTH]; //kullanicidan renk girdisi almak icin kullanilir.

	setlocale(LC_ALL, "Turkish");

	printf("2'den buyuk, 9'dan kucuk bir N sayisi giriniz (2 < N < 9): ");
	scanf("%d", &N);
	printf("Yazdirma tipini giriniz (0-Her adim icin yazdirma, 1-Sadece sonuc yazdirma): ");
	scanf("%d", &printType);
	
	//renk matrisine yer acilir
	matrix = (int**)calloc(N, sizeof(int*));
	for (i = 0; i < N; i++)
	{
		matrix[i] = (int*)calloc(N, sizeof(int));
	}

	/* debug icin kullanildi
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			matrix[i][j] = j;
		}
	}
	*/
	firstRowShiftCount = (int*)calloc(1, sizeof(int));
	//kullaniciya secebilecegi renkler verilir
	printf("\n%s-%s-%s-%s-%s-%s-%s-%s\n", RED, GREEN, BLUE, YELLOW, PURPLE, PINK, BLACK, ORANGE);
	printf("Yukaridaki renklerden %d tanesini secip kullanabilirsiniz.\n", N);

	//matrisin her bir hucresi icin kullanicidan renk girdisi alinir.
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%d. Satir %d. Sutun Rengini giriniz: ", i + 1, j + 1);
			int colorInt;
			//scanf("%d", &colorInt);
			//matrix[i][j] = colorInt;
			scanf("%s", color);
			if (strcmp(color, PURPLE) == 0)
			{
				matrix[i][j] = 0;
			}
			else if (strcmp(color, BLUE) == 0)
			{
				matrix[i][j] = 1;
			}
			else if (strcmp(color, YELLOW) == 0)
			{
				matrix[i][j] = 2;
			}
			else if (strcmp(color, BLACK) == 0)
			{
				matrix[i][j] = 3;
			}
			else if (strcmp(color, GREEN) == 0)
			{
				matrix[i][j] = 4;
			}
			else if (strcmp(color, PINK) == 0)
			{
				matrix[i][j] = 5;
			}
			else if (strcmp(color, RED) == 0)
			{
				matrix[i][j] = 6;
			}
			else if (strcmp(color, ORANGE) == 0)
			{
				matrix[i][j] = 7;
			}
			else
			{
				printf("Hatali giris yaptiniz. Cikiliyor..");
				return -1;
			}
		}
		printf("\n");
	}
	
	//ilk cikti olarak kullanicinin girdigi matris ekrana yazdirilir.
	printf("Girilen matris: \n");
	printMatrix(matrix, N);
	printf("========================================================================================================\n");

	//backtrack fonksiyonu cagrilir
	backTrack(matrix, N, 1, 0, printType, firstRowShiftCount);
	printMatrix(matrix, N);
	return 0;
}