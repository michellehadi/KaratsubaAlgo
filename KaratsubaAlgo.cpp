
#include <bits/stdc++.h>

using namespace std;

class BigInt{
	string digits;
public:

	//Constructors:
	BigInt(unsigned long long n = 0);
	BigInt(string &);
	BigInt(const char *);
	BigInt(BigInt &);

	//Helper Functions:
	friend void divide_by_2(BigInt &a);
	friend bool Null(const BigInt &);
	friend int Length(const BigInt &);
	int operator[](const int)const;

			/* * * * Operator Overloading * * * */

	//Direct assignment
	BigInt &operator=(const BigInt &);

	//Post/Pre - Incrementation
	BigInt &operator++();
	BigInt operator++(int temp);
	BigInt &operator--();
	BigInt operator--(int temp);

	//Addition and Subtraction
	friend BigInt &operator+=(BigInt &, const BigInt &);
	friend BigInt operator+(const BigInt &, const BigInt &);
	friend BigInt operator-(const BigInt &, const BigInt &);
	friend BigInt &operator-=(BigInt &, const BigInt &);

	//Comparison operators
	friend bool operator==(const BigInt &, const BigInt &);
	friend bool operator!=(const BigInt &, const BigInt &);

	friend bool operator>(const BigInt &, const BigInt &);
	friend bool operator>=(const BigInt &, const BigInt &);
	friend bool operator<(const BigInt &, const BigInt &);
	friend bool operator<=(const BigInt &, const BigInt &);

	//Multiplication and Division
	friend BigInt &operator*=(BigInt &, const BigInt &);
	friend BigInt operator*(const BigInt &, const BigInt &);
	friend BigInt &operator/=(BigInt &, const BigInt &);
	friend BigInt operator/(const BigInt &, const BigInt &);

	//Modulo
	friend BigInt operator%(const BigInt &, const BigInt &);
	friend BigInt &operator%=(BigInt &, const BigInt &);

	//Power Function
	friend BigInt &operator^=(BigInt &,const BigInt &);
	friend BigInt operator^(BigInt &, const BigInt &);

	//Square Root Function
	friend BigInt sqrt(BigInt &a);

	//Read and Write
	friend ostream &operator<<(ostream &,const BigInt &);
	friend istream &operator>>(istream &, BigInt &);

	//Others
	friend BigInt NthCatalan(int n);
	friend BigInt NthFibonacci(int n);
	friend BigInt Factorial(int n);
};

BigInt::BigInt(string & s){
    try{
        digits = "";
        int n = s.size();
        for (int i = n - 1; i >= 0;i--){
            if(!isdigit(s[i]))
                throw("ERROR");
            digits.push_back(s[i] - '0');
        }
	}catch (const char* msg) {exit(0);}

}
BigInt::BigInt(unsigned long long nr){
	do{
		digits.push_back(nr % 10);
		nr /= 10;
	} while (nr);
}
BigInt::BigInt(const char *s){
	try{
        digits = "";
        for (int i = strlen(s) - 1; i >= 0;i--)
        {
            if(!isdigit(s[i]))
                throw("ERROR");
            digits.push_back(s[i] - '0');
        }
	} catch (const char* msg) {exit(0);}

}
BigInt::BigInt(BigInt & a){
	digits = a.digits;
}

bool Null(const BigInt& a){
	if(a.digits.size() == 1 && a.digits[0] == 0)
		return true;
	return false;
}
int Length(const BigInt & a){
	return a.digits.size();
}
int BigInt::operator[](const int index)const{
    try{
        if((int)digits.size() <= index || index < 0)
            throw("ERROR");
        return digits[index];
    }catch (const char* msg) {exit(0);}

}
bool operator==(const BigInt &a, const BigInt &b){
	return a.digits == b.digits;
}
bool operator!=(const BigInt & a,const BigInt &b){
	return !(a == b);
}
bool operator<(const BigInt&a,const BigInt&b){
	int n = Length(a), m = Length(b);
	if(n != m)
		return n < m;
	while(n--)
		if(a.digits[n] != b.digits[n])
			return a.digits[n] < b.digits[n];
	return false;
}
bool operator>(const BigInt&a,const BigInt&b){
	return b < a;
}
bool operator>=(const BigInt&a,const BigInt&b){
	return !(a < b);
}
bool operator<=(const BigInt&a,const BigInt&b){
	return !(a > b);
}

BigInt &BigInt::operator=(const BigInt &a){
	digits = a.digits;
	return *this;
}

BigInt &BigInt::operator++(){
	int i, n = digits.size();
	for (i = 0; i < n && digits[i] == 9;i++)
		digits[i] = 0;
	if(i == n)
		digits.push_back(1);
	else
		digits[i]++;
	return *this;
}
BigInt BigInt::operator++(int temp){
	BigInt aux;
	aux = *this;
	++(*this);
	return aux;
}

BigInt &BigInt::operator--(){
    try{
        if(digits[0] == 0 && digits.size() == 1)
            throw("UNDERFLOW");
        int i, n = digits.size();
        for (i = 0; digits[i] == 0 && i < n;i++)
            digits[i] = 9;
        digits[i]--;
        if(n > 1 && digits[n - 1] == 0)
            digits.pop_back();
        return *this;
    }catch (const char* msg) {exit(0);}

}
BigInt BigInt::operator--(int temp){
	BigInt aux;
	aux = *this;
	--(*this);
	return aux;
}

BigInt &operator+=(BigInt &a,const BigInt& b){
	int t = 0, s, i;
	int n = Length(a), m = Length(b);
	if(m > n)
		a.digits.append(m - n, 0);
	n = Length(a);
	for (i = 0; i < n;i++){
		if(i < m)
			s = (a.digits[i] + b.digits[i]) + t;
		else
			s = a.digits[i] + t;
		t = s / 10;
		a.digits[i] = (s % 10);
	}
	if(t)
		a.digits.push_back(t);
	return a;
}
BigInt operator+(const BigInt &a, const BigInt &b){
	BigInt temp;
	temp = a;
	temp += b;
	return temp;
}

BigInt &operator-=(BigInt&a,const BigInt &b){
    try{
        if(a < b)
            throw("UNDERFLOW");
        int n = Length(a), m = Length(b);
        int i, t = 0, s;
        for (i = 0; i < n;i++){
            if(i < m)
                s = a.digits[i] - b.digits[i]+ t;
            else
                s = a.digits[i]+ t;
            if(s < 0)
                s += 10,
                t = -1;
            else
                t = 0;
            a.digits[i] = s;
        }
        while(n > 1 && a.digits[n - 1] == 0)
            a.digits.pop_back(),
            n--;
        return a;
    }catch (const char* msg) {exit(0);}
}

BigInt operator-(const BigInt& a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp -= b;
	return temp;
}

BigInt &operator*=(BigInt &a, const BigInt &b)
{
	if(Null(a) || Null(b)){
		a = BigInt();
		return a;
	}
	int n = a.digits.size(), m = b.digits.size();
	vector<int> v(n + m, 0);
	for (int i = 0; i < n;i++)
		for (int j = 0; j < m;j++){
			v[i + j] += (a.digits[i] ) * (b.digits[j]);
		}
	n += m;
	a.digits.resize(v.size());
	for (int s, i = 0, t = 0; i < n; i++)
	{
		s = t + v[i];
		v[i] = s % 10;
		t = s / 10;
		a.digits[i] = v[i] ;
	}
	for (int i = n - 1; i >= 1 && !v[i];i--)
			a.digits.pop_back();
	return a;
}
BigInt operator*(const BigInt&a,const BigInt&b){
	BigInt temp;
	temp = a;
	temp *= b;
	return temp;
}

BigInt &operator/=(BigInt& a,const BigInt &b){
    try{
        if(Null(b))
            throw("Arithmetic Error: Division By 0");
        if(a < b){
            a = BigInt();
            return a;
        }
        if(a == b){
            a = BigInt(1);
            return a;
        }
        int i, lgcat = 0, cc;
        int n = Length(a);
        vector<int> cat(n, 0);
        BigInt t;
        for (i = n - 1; t * 10 + a.digits[i] < b;i--){
            t *= 10;
            t += a.digits[i] ;
        }
        for (; i >= 0; i--){
            t = t * 10 + a.digits[i];
            for (cc = 9; cc * b > t;cc--);
            t -= cc * b;
            cat[lgcat++] = cc;
        }
        a.digits.resize(cat.size());
        for (i = 0; i < lgcat;i++)
            a.digits[i] = cat[lgcat - i - 1];
        a.digits.resize(lgcat);
        return a;
    }catch (const char* msg) {exit(0);}
}

BigInt operator/(const BigInt &a,const BigInt &b){
	BigInt temp;
	temp = a;
	temp /= b;
	return temp;
}

BigInt &operator%=(BigInt& a,const BigInt &b){
    try{
        if(Null(b))
            throw("Arithmetic Error: Division By 0");
        if(a < b){
            a = BigInt();
            return a;
        }
        if(a == b){
            a = BigInt(1);
            return a;
        }
        int i, lgcat = 0, cc;
        int n = Length(a);
        vector<int> cat(n, 0);
        BigInt t;
        for (i = n - 1; t * 10 + a.digits[i] < b;i--){
            t *= 10;
            t += a.digits[i];
        }
        for (; i >= 0; i--){
            t = t * 10 + a.digits[i];
            for (cc = 9; cc * b > t;cc--);
            t -= cc * b;
            cat[lgcat++] = cc;
        }
        a = t;
        return a;
    }catch (const char* msg) {exit(0);}
}
BigInt operator%(const BigInt &a,BigInt &b){
	BigInt temp;
	temp = a;
	temp %= b;
	return temp;
}

BigInt &operator^=(BigInt & a,const BigInt & b){
	BigInt Exponent, Base(a);
	Exponent = b;
	a = 1;
	while(!Null(Exponent)){
		if(Exponent[0] & 1)
			a *= Base;
		Base *= Base;
		divide_by_2(Exponent);
	}
	return a;
}
BigInt operator^(BigInt & a,BigInt & b){
	BigInt temp(a);
	temp ^= b;
	return temp;
}

void divide_by_2(BigInt & a){
	int add = 0;
	for (int i = a.digits.size() - 1; i >= 0;i--){
		int digit = (a.digits[i] >> 1) + add;
		add = ((a.digits[i] & 1) * 5);
		a.digits[i] = digit;
	}
	while(a.digits.size() > 1 && !a.digits.back())
		a.digits.pop_back();
}

BigInt sqrt(BigInt & a){
	BigInt left(1), right(a), v(1), mid, prod;
	divide_by_2(right);
	while(left <= right){
		mid += left;
		mid += right;
		divide_by_2(mid);
		prod = (mid * mid);
		if(prod <= a){
			v = mid;
			++mid;
			left = mid;
		}
		else{
			--mid;
			right = mid;
		}
		mid = BigInt();
	}
	return v;
}

BigInt NthCatalan(int n){
	BigInt a(1),b;
	for (int i = 2; i <= n;i++)
		a *= i;
	b = a;
	for (int i = n + 1; i <= 2 * n;i++)
		b *= i;
	a *= a;
	a *= (n + 1);
	b /= a;
	return b;
}

BigInt NthFibonacci(int n){
	BigInt a(1), b(1), c;
	if(!n)
		return c;
	n--;
	while(n--){
		c = a + b;
		b = a;
		a = c;
	}
	return b;
}

BigInt Factorial(int n){
	BigInt f(1);
	for (int i = 2; i <= n;i++)
		f *= i;
	return f;
}

istream &operator>>(istream &in,BigInt&a){
    try{
        string s;
        in >> s;
        int n = s.size();
        for (int i = n - 1; i >= 0;i--){
            if(!isdigit(s[i]))
                throw("INVALID NUMBER");
            a.digits[n - i - 1] = s[i];
        }
        return in;
    }catch (const char* msg) {exit(0);}
}

ostream &operator<<(ostream &out,const BigInt &a){
	for (int i = a.digits.size() - 1; i >= 0;i--)
		cout << (short)a.digits[i];
	return cout;
}

// Function template
BigInt size_base10(BigInt n);
BigInt school_addition(BigInt x, BigInt y, BigInt b);
BigInt karatsuba(BigInt num1, BigInt num2, BigInt b);
BigInt to_dec(BigInt n, BigInt b);// 10,2 --> 111,2
BigInt from_dec(BigInt n, BigInt b); //3,2
BigInt ten("10");
BigInt zero("0");
BigInt two("2");

BigInt size_base10(BigInt n) // digits
{
    BigInt size("0");
    while(n != zero)
    {
        n = n / ten; //11 || 1 || 0
        size++; //1 || 2 || 3
    }
    return size;
}

BigInt module(BigInt num1, BigInt num2){
    BigInt result("0");

    if(num1 < num2)
        result = num1;
    else if(num1== num2)
        result = zero;
    else
        result = num1%num2;

    return result;
}

BigInt karatsuba(BigInt num1, BigInt num2,BigInt b) //10 111 2
{
    BigInt num1Size, num2Size, m("0"), m2 ("0"), high1 ("0"), low1 ("0"), high2 ("0"), low2 ("0");
    BigInt result1("0"), result2("0"), result3("0"), result4("0"), result("0");
    BigInt z0("0"), z1("0"), z2("0"), z11("0"), z12("0"), i ("0"),j ("0");

    if ((num1 < b) || (num2 < b))
    {
        result = num1*num2;
        return result;
    }

    num1Size = size_base10(num1); // 2
    num2Size = size_base10(num2); // 3

    /* calculates the size of the numbers(number of digits in the numbers) */
    if (num1Size <= num2Size) BigInt m = num1Size; //2
    else BigInt m = num2Size; //2

    m2 = m/two ; //1
    /* split the digit sequences in the middle */

    while(i<m2) //0<1
    {
        low1 += module(num1, ten) * (ten ^ i); //0
        num1 /= ten; //1
        i++; //1
    }

    while(num1!= zero && i<num1Size) //1 && 1 < 2
    {
        high1 +=  module(num1, ten) * (ten ^ j); //1
        num1 /= ten; //0
        i++; //2
        j++; //1
    }

    i= zero;
    while(i<m2) //0
    {
        low2 += module(num2, ten) * (ten ^ i); //0
        num2 /= ten; //11
        i++; // 1
    }

    j = zero;

    while(num2 != zero && i < num2Size) //11 && 1 || 1 && 2
    {
        high2 += module(num2, ten) * (ten ^ j); //1
        num2 /= ten; //1 || 0
        i++; //2 // 3
        j++; //1 // 2
    }

    z0 = karatsuba(low1, low2, b); //z0=low1*low2 -> karatsuba(0,1,2)

    z11 = low1 + high1;
    z12 = low2 + high2;
    z1 = karatsuba(z11,z12 ,b); //z1=(low1 + high1)*(low2 + high2)

    z2 = karatsuba(high1, high2,b); // z2= high1*high2
    // num1*num2 = z2*10^(m2 * 2) + (z1 - z2 - z0)*10^m2 + z0

    result1 = m2 * two;
    result2 = z2 * (ten ^ result1);
    result3 = z1 - z2 - z0;
    result4 = result3 * (ten ^ m2);
    result = result2 +  result4 + z0;
    return result;
}
BigInt school_addition(BigInt x, BigInt y,BigInt b) //10 111 2
{
    BigInt cary ("0"), temp("0"), y1("0"), res_num("0"), i("0");

    while(x != zero && y != zero)
    {
        temp = module(x, b) + module(y, b) + cary; //0+1 +0 = 1|| 1 + 1 + 0 = 2
        cary = temp / b; //0 || 1
        temp = module(temp, b);
        x /= ten; //1 || 0
        y /= ten; //11 || 1
        res_num += temp * (ten ^ i); //1 || 1
        i++; //1 || 2
    }

    while(x!=zero)
    {
        temp = module(x, b) + cary;
        cary = temp / b;
        temp = module(temp, b);
        x /= ten;
        res_num += temp * (ten ^ i);
        i++;
    }

    while(y != zero)
    {
        temp = module(y, b) + cary;//2
        cary = temp / b;//1
        temp = module(temp, b);
        y /= ten; //0
        res_num += temp * (ten ^ i); //1
        i++;//3
    }

    res_num += cary * (ten ^ i); //1001
    return res_num;
}

BigInt to_dec(BigInt n, BigInt b){
    BigInt i("0"), s("0");

    while(n > zero){
        s +=  module(n, ten) *  (b ^ i);
        n /= ten;
        i++;
    }

    return s;
}

BigInt from_dec(BigInt n, BigInt b) //3,2
{
    BigInt res("0"), k("0");

    while(n!=zero)
    {
        res += module(n, b) * (ten ^ k); //1 || 11
        n /= b; //1 || 0
        k++; //1 ||2
    }
    return res; //11
}


BigInt division(BigInt x,BigInt y,BigInt b)
{
    BigInt x1("0"), y1("0"), result("0"), ratio("0");

    x1 = to_dec(x,b); //2
    y1 = to_dec(y,b); // 7

    while(x1 > y1)
    {
        x1 -= y1; //5 || 3 ||1
        ratio++; //1 || 2 ||3
    }

    result = from_dec(ratio, b);
    return result; //3,2
}

int main()
{
    while(true){
        string s1, s2, sB;
        cin>>s1>>s2>>sB;

        BigInt I1(s1), I2(s2), B(sB), C_I1 ("0"), C_I2("0"), addition("0"), multi("0"), divide("0");

        C_I1 = to_dec(I1, B);
        C_I2 = to_dec(I2, B);

        addition = C_I1 + C_I2;
        multi = C_I1 * C_I2;
        divide = C_I1 / C_I2;

        addition = from_dec(addition, B);
        multi = from_dec(multi, B);
        divide = from_dec(divide, B);

        cout << addition << " " << multi << " " << divide << endl;
    }
return 0;
}
