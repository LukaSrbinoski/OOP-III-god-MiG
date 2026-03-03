 #include <iostream>
#include <cstring>
using namespace std;

class QuizAttempt {
protected:
    char index[7];
public:
    QuizAttempt(const char *idx = "") {
        strncpy(index, idx, 6);
        index[6] = '\0';
    }

    virtual double score() const = 0;
    virtual void print() const = 0;

    virtual ~QuizAttempt() {}
};

class MCQuizAttempt : public QuizAttempt {
private:
    char correct[11];
    char student[11];

public:
    MCQuizAttempt(const char *idx, const char *c, const char *s)
        : QuizAttempt(idx) {
        strncpy(correct, c, 10);
        correct[10] = '\0';
        strncpy(student, s, 10);
        student[10] = '\0';
    }

    double score() const override {
        double points = 0;
        for (int i = 0; i < 10; i++)
            points += (student[i] == correct[i]) ? 1 : -0.25;
        return points;
    }

    void print() const override {
        double total = 0;
        for (int i = 0; i < 10; i++) {
            double pts = (student[i] == correct[i]) ? 1 : -0.25;
            total += pts;

            cout << i + 1 << ". Correct: " << correct[i]
                 << " Answer: " << student[i]
                 << " Points: " << pts << endl;
        }
        cout << "Total score: " << total << endl << endl;
    }
};

class TFQuizAttempt : public QuizAttempt {
private:
    bool correct[10];
    bool student[10];

public:
    TFQuizAttempt(const char *idx, const bool c[10], const bool s[10])
        : QuizAttempt(idx) {
        for (int i = 0; i < 10; i++) {
            correct[i] = c[i];
            student[i] = s[i];
        }
    }

    double score() const override {
        double points = 0;
        for (int i = 0; i < 10; i++)
            points += (student[i] == correct[i]) ? 1 : -0.5;
        return points;
    }

    void print() const override {
        double total = 0;
        for (int i = 0; i < 10; i++) {
            double pts = (student[i] == correct[i]) ? 1 : -0.5;
            total += pts;

            cout << i + 1 << ". Correct: "
                 << (correct[i] ? "True" : "False")
                 << " Answer: "
                 << (student[i] ? "Correct" : "False")
                 << " Points: " << pts << endl;
        }
        cout << "Total score: " << total << endl << endl;
    }
};

bool operator>=(const QuizAttempt &a, const QuizAttempt &b) {
    return a.score() >= b.score();
}

double averagePointsOfPassedStudents(QuizAttempt **attempts, int n) {
    double sum = 0;
    int count = 0;

    for (int i = 0; i < n; i++) {
        double s = attempts[i]->score();
        if (s >= 5.0) {
            sum += s;
            count++;
        }
    }

    if (count == 0) return 0;
    return sum / count;
}

QuizAttempt* readMCQuizAttempt() {
    char index[7];
    char correct[11];
    char student[11];

    cin >> index;
    cin >> correct;
    cin >> student;

    return new MCQuizAttempt(index, correct, student);
}

QuizAttempt* readTFQuizAttempt() {
    char index[7];
    bool correct[10];
    bool student[10];

    cin >> index;

    for (int i = 0; i < 10; i++)
        cin >> correct[i];

    for (int i = 0; i < 10; i++)
        cin >> student[i];

    return new TFQuizAttempt(index, correct, student);
}

int main() {
    int testCase;
    cin >> testCase;  // се чита, но не се користи

    int n;
    cin >> n;

    QuizAttempt **attempts = new QuizAttempt*[n];

    for (int i = 0; i < n; i++) {
        int type;
        cin >> type;

        if (type == 1)
            attempts[i] = readMCQuizAttempt();
        else
            attempts[i] = readTFQuizAttempt();
    }

    for (int i = 0; i < n; i++)
        attempts[i]->print();

    cout << "Average score of passed students is: "
         << averagePointsOfPassedStudents(attempts, n) << endl;

    for (int i = 0; i < n; i++)
        delete attempts[i];
    delete[] attempts;

    return 0;
}