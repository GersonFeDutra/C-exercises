/* Returns n-th power of integer x. */
int power(int x, int n)
{
    int p = 1;

    for (int i = 0; i < n; ++i)
        p *= x;

    return p;
}


unsigned bitoi(const char s[])
{
    unsigned x = 0;
    int i;

    // Encontra o primeiro bit i
    for (i = (s[0] == 'b' || s[0] == 'B'); s[i] != '1' && s[i] != '\0'; ++i)
        if (s[i] != '0')
            return 0;

	for (; s[i] != '\0'; ++i) {
        x <<= 1;
        if (s[i] == '1')
            x |= 01;
        else if (s[i] != '0')
            return 0;
    }

    return x;
}


#define BITS_LEN sizeof(int) * 8 + 1
void atobit(unsigned a, char bs[BITS_LEN])
{
    int i;
    for (i = 0; a != 0 && i < BITS_LEN; a >>= 1)
        bs[i++] = (a & 01) ? '1' : '0';

    bs[i--] = '\0';

    // O binário é escrito de forma invertida, então temos de refleti-lo.
	int j = 0;
    for (; j < i; --i, ++j) {
        char c = bs[j];
        bs[j] = bs[i];
        bs[i] = c;
    }
}


int atoi(const char s[])
{
    int i, n = 0;

    for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');

    return n;
}


int octoi(const char s[])
{
    int i = 0; // current digit
    int n; // string size
    int x = 0; // target integer
    int o = s[i] == 'o' || s[i] == 'O' || s[i] == '0'; // 0x offset.

    for (n = 0; s[n] != '\0'; n++); // Find the size of the string

    for (i = n - 1; i >= o; i--) {
        int v;
		if (s[i] >= '0' && s[i] < '8')
            v = s[i] - '0';
        else
            return -1;
        x += v * power(8, (n - o - 1) - (i - o));
	}

    return x;
}


int htoi(const char s[])
{
    int i; // current digit
    int n; // string size
    int x = 0; // target integer
    int o = 0; // 0x offset.

    if (s[i = 0] == '0') {
        if (s[++i] != 'X' && s[i] != 'x')
            return -1;
        o = 2;
        ++i;
    }

    for (n = 0; s[n] != '\0'; n++); // Find the size of the string

    for (i = n - 1; i >= o; i--) {
        int v;
		if (s[i] >= '0' && s[i] <= '9')
            v = s[i] - '0';
        else if (s[i] >= 'A' && s[i] <= 'F')
            v = 10 + s[i] - 'A';
        else if (s[i] >= 'a' && s[i] <= 'f')
            v = 10 + s[i] - 'a';
        else
            return -1;
        x += v * power(16, (n - o - 1) - (i - o));
	}

    return x;
}
