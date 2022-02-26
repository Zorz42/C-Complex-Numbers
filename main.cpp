#include <iostream>
#include <math.h>

#define CONST_E 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003059921817413596629043572900334295260595630738132328627943490763233829880753195251019011573834187
#define CONST_PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097

struct Complex {
    double real, imag;
    
    Complex() : real(0), imag(0) {}
    Complex(int a) : real(a), imag(0) {}
    Complex(double a) : real(a), imag(0) {}
};

std::ostream& operator<<(std::ostream& os, const Complex& complex) {
    std::cout << complex.real << " + " << complex.imag << "i";
    return os;
}

bool operator==(const Complex& a, const Complex& b) {
    return a.real == b.real && a.imag == b.imag;
}

/*
 (a + bi) + (c + di)
 a + c + i(b + d)
 */

Complex operator+(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real + b.real;
    result.imag = a.imag + b.imag;
    return result;
}

/*
 (a + bi) - (c + di)
 a - c + i(b - d)
 */

Complex operator-(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real - b.real;
    result.imag = a.imag - b.imag;
    return result;
}

/*
 (a + bi)(c + di)
 ac - bd + i(bc + ad)
 */

Complex operator*(const Complex& a, const Complex& b) {
    Complex result;
    result.real = a.real * b.real - a.imag * b.imag;
    result.imag = a.imag * b.real + a.real * b.imag;
    return result;
}

/*
 (br + bi * i)(rr + ri * i) = ar + ai * i
 br * rr - bi * ri + i * (rr * bi + br * ri) = ar + ai * i
 
 br * rr - bi * ri = ar
 ri = (br * rr - ar) / bi
 
 rr * bi + br * ri = ai
 rr * bi + br * (br * rr - ar) / bi = ai
 rr * bi + br * br * rr / bi = ai + br * ar / bi
 rr = (ai + br * ar / bi) / (bi + br * br / bi)
 */

Complex operator/(const Complex& a, const Complex& b) {
    Complex result;
    result.real = (a.imag + b.real * a.real / b.imag) / (b.imag + b.real * b.real / b.imag);
    result.imag = (b.real * result.real - a.real) / b.imag;
    return result;
}

/*
 tan(ang) = ai / ar
 ang = tan^-1(ai / ar)
 
 rad = sqrt(ar * ar + ai * ai)
 
 ar + ai * i = rad * e^(i * ang) = e^(ln(rad) + i * ang)
 (ar + ai * i)^(br + bi * i) = e^(ln(rad) + i * ang)(br + bi * i)
 e^( ln(rad) * br - bi * ang + i*( ang * br + bi * ln(rad) ) )
 e^( ln(rad) * br - bi * ang ) * (cos( ang * br + bi * ln(rad) ) + i * sin(ang * br + bi * ln(rad)))
 
 real = e^(ln(rad) * br - bi * ang) * cos(ang * br + bi * ln(rad))
 imag = e^(ln(rad) * br - bi * ang) * sin(ang * br + bi * ln(rad))
 
 */

Complex operator^(const Complex& a, const Complex& b) {
    Complex result;
    double ang = atan(a.imag / a.real);
    double rad = sqrt(a.real * a.real + a.imag * a.imag);
    result.real = pow(CONST_E, log(rad) * b.real - b.imag * ang) * cos(ang * b.real + b.imag * log(rad));
    result.imag = pow(CONST_E, log(rad) * b.real - b.imag * ang) * sin(ang * b.real + b.imag * log(rad));
    result.real = round(result.real * 10e10) / 10e10;
    result.imag = round(result.imag * 10e10) / 10e10; // anything over 10 digits is rounding error
    return result;
}

int main(int argc, const char * argv[]) {
    // the known constant
    Complex i;
    i.imag = 1;
    
    // the i test
    std::cout << 5 + 10*i << std::endl;
    
    // addition and subtraction test
    std::cout << (5 + 10*i) + (6 + 7*i) - (6 + 7*i) << std::endl;
    
    // multiplication and division test
    std::cout << (5 + 10*i) * (6 + 7*i) / (6 + 7*i) << std::endl;
    
    // the famous eulers identity e^(i*pi) = -1
    std::cout << ((CONST_E) ^ (i * CONST_PI)) << std::endl;
    
    // regular numbers power
    std::cout << ((5 + 0*i) ^ (3 + 0*i)) << std::endl;
    
    return 0;
}
