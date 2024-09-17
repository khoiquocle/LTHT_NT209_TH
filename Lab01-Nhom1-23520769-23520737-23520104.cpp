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
	// Cach tinh so bu 2 
	return ~x + 1;
}

// 1.3
int getByte(int x, int n)
{
	    // Dịch phải 8 bit, sau đó and với 11
	return (x >> 8 * n) & 0xFF;

}

// 1.4
int getnbit(int x, int n)
{
	// Tao mask bằng cách dịch trái xong - 1 để lấy các bits cuối là 1
    int mask = (1 << n) - 1;
	return x & mask;
}

// 1.5
int mulpw2(int x, int n)
{
	 int shift = n >> 31;          // shift = -1 nếu n < 0, ngược lại là 0
    int abs_n = (n ^ shift) - shift;  // Tính giá trị tuyệt đối của n
    return (x << ((~shift) & abs_n)) >> (shift & abs_n);  // Dịch trái hoặc phải tùy theo giá trị n
}



// 2.1
int isSameSign(int x, int y)
{
      /*
    Ý tưởng: Để xét 2 số có cùng dấu, ta xét bit dấu của chúng, bằng cách dịch phải 31 lần để bit dấu nằm ở phải cùng , trái full 0.
    Thực hiện:
        -   Dịch phải 31 bit số thứ nhất
        -   Dịch phải 31 bit số thứ hai
        -   XNOR 2 kết quả lại với nhau
        -   Return 1 nếu cùng dấu, return 0 nếu khác dấu 
    

    */
    int temp1 = (  x >> 31 ) & 1 ; // dich phai 31 bit, luu lai bit dau
    int temp2 =  ( y >> 31 ) & 1; // de so sanh, &1 de chac chan cac bit dau = 0
    return !(temp1 ^ temp2); 
}

// 2.2
int is8x(int x)
{
    x=x<<29;   // Các số chia hết cho 8 đều có 3 bit cuối =0 nên ta sẽ dịch trái 29 bit để chỉ giữ 3 bit cuối trong số, vì các số chia hết cho 8 có 3 bit cuối là 0 nên lúc này số sau khi dịch trái sẽ bằng 0, ta dùng phũ định để xử lí vì ! các số khác 0 sẽ bằng 0 và !0 sẽ bằng 1
	return !x;
}

// 2.3

int isPositive(int x)
{
    int zero=!x;        //bài toán sẽ kiểm tra bit dấu để xác định, tuy nhiên số 0 có bit dấu =0 nhưng return kq=0 nên phải có 1 biến zero dùng !x để kiểm tra có phải số 0 hay không
    int signbit=x>>31;   //kiểm tra bit dấu bằng cách dịch phải 31 bit để lúc này số chỉ còn 1 bit dấu nằm ở trọng số thấp nhất, các bit còn lại sẽ=0, số đó sẽ lưu vào biến signbit
	return !(zero^signbit);// lúc này ta dùng lệnh XNOR để kiểm tra, nếu zero=1 =>return 0, ngược lại nếu zero=0, signbit=1 là số âm=> return 0, zero=0, signbit=0 => return 1
}

// 2.4
int isLess2n(int x, int y)
{
	 /*
    Ý tưởng: lấy x - 2 mũ n , nếu kết quả ra âm thì x < 2 mũ n và ngược lại ra dương 
    -> quy bài toán về kiểm tra số âm hay dương ( kiểm tra bit dấu bài 2.1 )
    Thực hiện:
        - Lấy số âm của 2 mũ n bằng cách bù 2
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