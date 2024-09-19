#include <stdio.h>

void PrintBits(unsigned int x)
{
	int i;
	for (i = 8 * sizeof(x) - 1; i >= 0; i--)
	{
		(x & (1 << i)) ? putchar('1') : putchar('0');
	}
	printf("\n");
}
void PrintBitsOfByte(unsigned int x)
{
	int i;
	for (i = 7; i >= 0; i--)
	{
		(x & (1 << i)) ? putchar('1') : putchar('0');
	}
	printf("\n");
}

// 1.1
int bitAnd(int x, int y)
{
	//PrintBits(x);
	//PrintBits(y);
	return ~(~x | ~y);
}

// 1.2
int negative(int x)
{
	/*	Ý tưởng: Để chuyển một số thành số bù 2, ta đảo tất cả các bit lại và cộng thêm 1
		Thực hiện: Đảo bit thành bù 1: ~x
		Cộng thêm 1 để thành bù 2: ~x + 1	*/
	return ~x + 1;
}

// 1.3
int getByte(int x, int n)
{
	    /*Ý tưởng: Muốn lấy những bit cuối thì mình and với các bit 1 
		Thực hiện: 
		Bước 1: Do 1 byte = 8 bit, nên ta cần dịch phải n thêm 3 bit : n << 3
		Bước 2: Tiếp theo, ta dịch trái x qua n byte để tận dụng 2 byte cuối cùng
		Bước 3: Cuối cùng, lấy giá trị đó and với 0xFF là 2 byte 1, vì cái gì and 1 cũng là 1
			*/
	return x >> (n << 3) & 0xFF;

}

// 1.4
int getnbit(int x, int n)
{
	/*	Ý tưởng: Tạo mask bằng cách dịch trái, sao đó and với các bit 1. Tương tự câu 1.3 
		Cách làm:  
		Bước 1: Đầu tiên, ta đảo 0, để ra được -1, tiếp theo dịch phải n. Mục đích của việc này là để các bit có trọng số cao là 1, và n bit trọng số thấp sẽ là 0.
		Bước 2: Đảo lại, thì các bit trọng số thấp là 0, còn bit trọng số cao sẽ là 1. Mục đích để and đi và ta sẽ lấy được các bit cuối 
		Bước 3: And với mask đó để ra kết quả.
*/
	int mask = ~(~0 << n);
	return x & mask;
}
// 1.5
int mulpw2(int x, int n)
{
	 int shift = n >> 31;          // Tạo một biến shift để xác định giá trị của n có âm hay không. Nếu n âm, giá trị shift sẽ là -1, còn nếu n dương thì shift là 0.
    int abs_n = (n ^ shift) + (~shift + 1);  // Tạo một biến abs_n, là giá trị tuyệt đối của n. Cách tính giá trị tuyệt đối: Nếu n dương, shift = 0, nên abs_n = n ^ 0 - 0 = n.
											//Nếu n âm, shift = -1, n ^ -1 là phép XOR với tất cả các bit của n, tạo ra giá trị bù 1 của n, sau đó trừ đi -1, sẽ cho kết quả là giá trị tuyệt đối của n.
    return (x << ((~shift) & abs_n)) >> (shift & abs_n);  // Dịch trái hoặc phải tùy theo giá trị n
}



// 2.1
int isSameSign(int x, int y)
{
      /*
    Ý tưởng: Để xét 2 số có cùng dấu, ta xét bit dấu của chúng, bằng cách dịch phải 31 lần để bit dấu nằm ở phải cùng , phía bên trái toàn là số 0.
    Thực hiện:
        -   Dịch phải 31 bit số thứ nhất
        -   Dịch phải 31 bit số thứ hai
        -   XNOR 2 kết quả lại với nhau
        -   Return 1 nếu cùng dấu, return 0 nếu khác dấu.
    */
    int temp1 = (  x >> 31 ) & 1 ; // dịch phải 31 bit, luu lại bit dấu để so sánh
    int temp2 =  ( y >> 31 ) & 1; // "&1" để chắc chắn các bit dấu = 0
    return !(temp1 ^ temp2); // xnor 2 bit dấu để xem có cùng dấu ko 
}

// 2.2
int is8x(int x)
{
  // Vì các số chia hết cho 8 đều có 3 bit trọng số thấp là 0 nên ta 
  // x&7 để lấy 3 bit trọng số thấp để xét
  // Các số không chia hết cho 8 khi ta !x sẽ =0 và ngược lại các số chia hết 
  // cho 8 sau khi lấy 3 bit sẽ còn là số 0 nên !x sẽ =1
	return !(x&7);
}

// 2.3
int isPositive(int x)
{
int zero=!x;        	//bài toán sẽ kiểm tra bit dấu để xác định, tuy nhiên số 0 có bit dấu =0
int signbit=x>>31; 		//nhưng return kq=0 nên phải có 1 biến zero dùng !x để kiểm tra có phải số 0 hay không
 return !(zero^signbit);//kiểm tra bit dấu bằng cách dịch phải 31 bit để lúc này số chỉ còn 1 bit dấu nằm ở trọng số thấp nhất, các bit còn lại sẽ=0, số đó sẽ lưu vào biến signbit
						// lúc này ta dùng lệnh XNOR để kiểm tra, nếu zero=1 =>return 0, ngược lại nếu zero=0, signbit=1 là số âm=> return 0, zero=0, signbit=0 => return 1
}

// 2.4
int isLess2n(int x, int y)
{
	 /*
    Ý tưởng: lấy x - (2 mũ n) , nếu kết quả ra âm thì x < 2 mũ n và ngược lại thì ra dương 
    -> quy bài toán về kiểm tra số âm hay dương ( kiểm tra bit dấu bài 2.1 )
    Thực hiện:
        - Lấy số âm của (2 mũ n) bằng cách bù 2 
        - Lấy x + bù 2 của 2 mũ n
        - Trả về bit dấu
    */
    int temp = ~(1 << y)+1 ; 
    int result = x + temp;
    return (result>>31)&1 ;
}

int main()
{
	int score = 0;
	printf("Your evaluation result:");
	printf("\n1.1 bitAnd");
	if (bitAnd(3, -9) == (3 & -9))
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	printf("\n1.2 negative");
	if (negative(0) == 0 && negative(9) == -9 && negative(-5) == 5)
	{
		printf("\tPass.");
		score += 1;
	}
	else
		printf("\tFailed.");

	//1.3
	printf("\n1.3 getByte");
	if (getByte(8, 0) == 8 && getByte(0x11223344, 1) == 0x33)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n1.4 getnbit");
	if (getnbit(0, 0) == 0 && getnbit(31, 3) == 7 && getnbit(16, 4) == 0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");
	//1.5
	printf("\n1.5 mulpw2");
	if (mulpw2(10, -1) == 5 && mulpw2(15, -2) == 3 && mulpw2(32, -4) == 2)
	{
		if (mulpw2(10, 1) == 20 && mulpw2(50, 2) == 200)
		{
			printf("\tAdvanced Pass.");
			score += 4;
		}
		else
		{
			printf("\tPass.");
			score += 3;
		}
	}
	else
		printf("\tFailed.");

	printf("\n2.1 isSameSign");
	if (isSameSign(4, 2) == 1 && isSameSign(13, -4) == 0 && isSameSign(0, 10) == 1)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n2.2 is8x");
	if (is8x(16) == 1 && is8x(3) == 0 && is8x(0) == 1)
	{
		printf("\tPass.");
		score += 2;
	}
	else
		printf("\tFailed.");

	printf("\n2.3 isPositive");
	if (isPositive(10) == 1 && isPositive(-5) == 0 && isPositive(0) == 0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n2.4 isLess2n");
	if (isLess2n(12, 4) == 1 && isLess2n(8, 3) == 0 && isLess2n(15, 2) == 0)
	{
		printf("\tPass.");
		score += 3;
	}
	else
		printf("\tFailed.");

	printf("\n--- FINAL RESULT ---");
	printf("\nScore: %.1f", (float)score / 2);
	if (score < 5)
		printf("\nTrouble when solving these problems? Contact your instructor to get some hints :)");
	else
	{
		if (score < 8)
			printf("\nNice work. But try harder.");
		else
		{
			if (score >= 10)
				printf("\nExcellent. We found a master in bit-wise operations :D");
			else
				printf("\nYou're almost there. Think more carefully in failed problems.");
		}
	}

	printf("\n\n\n");
}
