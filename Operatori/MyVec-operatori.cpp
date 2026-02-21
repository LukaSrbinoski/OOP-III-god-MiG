#include <iostream>
#include <cmath>
using namespace std;

class vector {
    float x, y, z;

    void copy(const vector& original) {
        this->x = original.x;
        this->y = original.y;
        this->z = original.z;
    }

public:
    vector(float x = 1, float y = 1, float z = 1) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    vector(const vector &other) {
        copy(other);
    }

    vector& operator=(const vector& original) {
        if (this != &original) this->copy(original);
        return *this;
    }

    ~vector() {}

    float operator~() const {
        return sqrtf(x * x + y * y + z * z);
    }

    vector operator+() const {
        return *this;
    }

    vector operator-() const {
        return vector(-x, -y, -z);
    }

    bool operator==(const vector& other) const {
        return this->x == other.x && this->y == other.y && this->z == other.z;
    }

    bool operator!=(const vector& other) const {
        return !(*this == other);
    }

    bool operator<(const vector& other) const {
        if (this->x < other.x) return true;
        if (this->x > other.x) return false;
        if (this->y < other.y) return true;
        if (this->y > other.y) return false;
        return this->z < other.z;
    }

    bool operator>(const vector& other) const {
        return !(*this < other);
    }

    bool operator<=(const vector& other) const {
        return *this < other || *this == other;
    }

    bool operator>=(const vector& other) const {
        return !(*this <= other);
    }

    float operator[](int index) const {
        switch (index) {
            case 0: return this->x;
            case 1: return this->y;
            case 2: return this->z;
            default: return -1;
        }
    }

    vector operator*(float number) const {
        return vector(this->x * number, this->y * number, this->z * number);
    }

    vector operator+(const vector &other) const {
        return vector(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    vector operator-(const vector& other) const {
        return vector(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    vector& operator++() {
        this->x += 1;
        this->y += 1;
        this->z += 1;
        return *this;
    }

    vector& operator--() {
        this->x -= 1;
        this->y -= 1;
        this->z -= 1;
        return *this;
    }

    vector operator++(int) {
        vector temp(*this);
        this->x += 1;
        this->y += 1;
        this->z += 1;
        return temp;
    }

    vector operator--(int) {
        vector temp(*this);
        this->x -= 1;
        this->y -= 1;
        this->z -= 1;
        return temp;
    }

    friend ostream& operator<<(ostream& o, const vector& v) {
        o << "(" << v.x << "," << v.y << "," << v.z << ")";
        return o;
    }

    friend istream& operator>>(istream& o, vector& v) {
        o >> v.x >> v.y >> v.z;
        return o;
    }
};

int main() {
    vector a(2, 3, 4);
    vector b(1, -2, 0);

    cout << "a = " << a << '\n';
    cout << "b = " << b << '\n';

    cout << "\n--- Basic arithmetic ---\n";
    cout << "a + b = " << (a + b) << '\n';
    cout << "a - b = " << (a - b) << '\n';
    cout << "a * 3 = " << (a * 3) << '\n';

    cout << "\n--- Unary operators ---\n";
    cout << "a=+b " << (+a) << '\n';
    cout << "b=-a " << (-b) << '\n';

    cout << "\n--- Increment / Decrement ---\n";
    vector c = a;
    cout << "c = " << c << '\n';
    cout << "++c = " << (++c) << '\n';
    cout << "c++ = " << (c++) << "   after: " << c << '\n';
    cout << "--c = " << (--c) << '\n';
    cout << "c-- = " << (c--) << "   after: " << c << '\n';

    cout << "\n--- Comparison ---\n";
    cout << "a == b: " << (a == b) << '\n';
    cout << "a != b: " << (a != b) << '\n';
    cout << "a < b : " << (a < b)  << '\n';
    cout << "a > b : " << (a > b)  << '\n';

    cout << "\n--- Indexing ---\n";
    cout << "a[0] = " << a[0] << '\n';
    cout << "a[1] = " << a[1] << '\n';
    cout << "a[2] = " << a[2] << '\n';

    cout << "\n--- Length (module) ---\n";
    cout << "~a = " << ~a << '\n';
    cout << "~b = " << ~b << '\n';


}

