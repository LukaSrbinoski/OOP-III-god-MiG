#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;

class User {
private:
    char username[50];
    char company[50];
    int positionLevel;
public:
    User(const char* u = "", const char* c = "", int p = 1) {
        strcpy(username, u);
        strcpy(company, c);
        positionLevel = p;
    }

    const char* getUsername() const { return username; }
    const char* getCompany() const { return company; }
    int getPositionLevel() const { return positionLevel; }

    friend ostream& operator<<(ostream& out, const User& u) {
        out << "Username: " << u.username << " Company name: " << u.company << " Position: " << u.positionLevel;
        return out;
    }

    friend istream& operator>>(istream& in, User& u) {
        in >> u.username >> u.company >> u.positionLevel;
        return in;
    }
};

class Group {
protected:
    User* members;
    int size;
    char name[50];

public:
    Group(const char* n = "") {
        members = nullptr;
        size = 0;
        strcpy(name, n);
    }

    Group(const Group& g) {
        size = g.size;
        strcpy(name, g.name);
        members = new User[size];
        for (int i = 0; i < size; i++)
            members[i] = g.members[i];
    }

    Group& operator=(const Group& g) {
        if (this != &g) {
            delete[] members;
            size = g.size;
            strcpy(name, g.name);
            members = new User[size];
            for (int i = 0; i < size; i++)
                members[i] = g.members[i];
        }
        return *this;
    }

    virtual ~Group() {
        delete[] members;
    }

    virtual void addMember(User& u) {
        for (int i = 0; i < size; i++)
            if (strcmp(members[i].getUsername(), u.getUsername()) == 0)
                return;

        User* temp = new User[size + 1];
        for (int i = 0; i < size; i++)
            temp[i] = members[i];
        temp[size] = u;
        delete[] members;
        members = temp;
        size++;
    }

    virtual double rating() const {
        if (size == 0) return 0;
        double sum = 0;
        for (int i = 0; i < size; i++)
            sum += members[i].getPositionLevel();
        double avg = sum / size;
        return (10 - avg) * size / 100.0;
    }

    friend ostream& operator<<(ostream& out, const Group& g) {
        out << "Group: " << g.name << endl;
        out << "Members: " << g.size << endl;
        out << "Rating: " << fixed << setprecision(5) << g.rating() << endl;
        out << "Members list: " << endl;
        for (int i = 0; i < g.size; i++)
            out << i+1 << ". " << g.members[i] << endl;
        return out;
    }
};

class PrivateGroup : public Group {
private:
    static int capacity;
    static constexpr double coefficient = 0.8;

public:
    PrivateGroup(const char* n = "") : Group(n) {}

    static void setCapacity(int c) { capacity = c; }

    void addMember(User& u) override {
        if (size >= capacity) return;
        Group::addMember(u);
    }

    double rating() const override {
        if (size == 0) return 0;
        double sum = 0;
        for (int i = 0; i < size; i++)
            sum += members[i].getPositionLevel();
        double avg = sum / size;
        return (10 - avg) * ((double)size / capacity) * coefficient;
    }

    friend ostream& operator<<(ostream& out, const PrivateGroup& g) {
        out << "Group: " << g.name << endl;
        out << "Members: " << g.size << endl;
        out << "Rating: " << fixed << setprecision(5) << g.rating() << endl;
        out << "Members list: " << endl;
        for (int i = 0; i < g.size; i++)
            out << i+1 << ". " << g.members[i] << endl;
        return out;
    }
};

int PrivateGroup::capacity = 10;

int main() {
    cout << "INTEGRATION TEST" << endl;
    int nGroups;
    cin >> nGroups;
    char name[50];
    Group** groups = new Group*[nGroups];

    for (int i = 0; i < nGroups; i++) {
        int type;
        cin >> type >> name;
        int nUsers;
        cin >> nUsers;

        if (type == 1) groups[i] = new Group(name);
        else groups[i] = new PrivateGroup(name);

        for (int j = 0; j < nUsers; j++) {
            User u;
            cin >> u;
            groups[i]->addMember(u);
        }
    }

    cout << "BEFORE CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; i++)
        cout << *groups[i];

    PrivateGroup::setCapacity(15);

    cout << "AFTER CHANGE OF PRIVATE GROUP COEFFICIENT" << endl;
    for (int i = 0; i < nGroups; i++)
        cout << *groups[i];

    for (int i = 0; i < nGroups; i++) delete groups[i];
    delete[] groups;
}