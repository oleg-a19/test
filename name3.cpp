#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;


class Person {
public:
    Person (const string first_name, const string last_name, const int birth) {
        m[birth] = {first_name, last_name};
        bd = birth;
    }
    vector<string> last_change(int year) const {
        vector<string> b(2);
            for (const auto& [key, val] : m) {
                if (year >= key) {
                    if (!val[0].empty()) {
                        b[0] = val[0];
                    }
                    if (!val[1].empty()) {
                        b[1] = val[1];
                    }
                }
            }
        return b;
    }
    vector<string> history_names(int year, int a) const {
        vector<string> n1, n2;
        if (a == 0) {
            for (const auto& [key, val] : m) {
                if (year >= key && !val[0].empty()) {
                    n1.push_back(val[0]);
                }
            }
            return n1;
        } else if (a == 1) {
            for ( auto& [key, val] : m) {
                if (year >= key && !val[1].empty()) {
                    n2.push_back(val[1]);
                }
            }
            return n2;
        }
    }

    void ChangeFirstName(int year, const string& first_name)  {
        if (year >= bd) {
            name1[0] = first_name;
            if (m.count(year) == 0) m[year] = name1;
            else m[year][0] = first_name;
        }
    }
    void ChangeLastName(int year, const string& last_name)  {
        if (year >= bd) {
            name2[1] = last_name;
            if (m.count(year) == 0) m[year] = name2;
            else m[year][1] = last_name;
        }
    }
    string GetFullName(const int year) const {
        string s;
        if (year < bd) return "No person";
        vector<string> v = last_change(year);
        if (v[0].empty() && v[1].empty()) s = "Incognito";
        else if (!v[0].empty() && v[1].empty()) s = v[0] + " with unknown last name";
        else if (v[0].empty() && !v[1].empty()) s = v[1] + " with unknown first name";
        else s = v[0] + " " + v[1];
        return s;
    }
    string GetFullNameWithHistory(const int year) const {
    // получить все имена и фамилии по состоянию на конец года year
        if (year < bd) return "No person";
        string s;
        vector<string> n1, n2;
        vector<string> v = last_change(year);
        n1 = history_names(year, 0);
        n2 = history_names(year, 1);

        reverse(n1.begin(), n1.end());
        reverse(n2.begin(), n2.end());

        while (n1.size() != 0 && n1[0] == v[0]) n1.erase(n1.begin());
        while (n2.size() != 0 && n2[0] == v[1]) n2.erase(n2.begin());

        if (v[0].empty() && v[1].empty()) s = "Incognito";
        else if (!v[0].empty() && v[1].empty()) {
            if (n1.size() == 0) s = v[0] + " with unknown last name";
            else {
                s = v[0] + " (";
                for (const auto& i : n1) {
                    if (i == n1[n1.size()-1]) s += i;
                    else s+=i+", ";
                }
                s += ") with unknown last name";
            }
        }
        else if (v[0].empty() && !v[1].empty()) {
            if (n2.size() == 0) s = v[1] + " with unknown first name";
            else {
                s = v[1] + " (";
                for (const auto& i : n2) {
                    if (i == n2[n2.size()-1]) s += i;
                    else s+=i+", ";
                }
                s += ") with unknown first name";
            }
        } else {
            if (n1.size() == 0 && n2.size() == 0) {
                s = v[0] + " " + v[1];
            } else if (n1.size() == 0 && n2.size() != 0) {
                s = v[0] + " " + v[1] + " (";
                for (const auto& i : n2) {
                    if (i == n2[n2.size()-1]) s += i;
                    else s+=i+", ";
                }
                s += ")";
            } else if (n1.size() != 0 && n2.size() == 0) {
                s = v[0] + " (";
                for (const auto& i : n1) {
                    if (i == n1[n1.size()-1]) s += i;
                    else s += i+", ";
                }
                s += ") " + v[1];
            } else {
                s = v[0] + " (";
                for (const auto& i : n1) {
                    if (i == n1[n1.size()-1]) s += i;
                    else s+=i+", ";
                }
                s += ") ";
                s += v[1] + " (";
                for (const auto& i : n2) {
                    if (i == n2[n2.size()-1]) s += i;
                    else s+=i+", ";
                }
                s += ")";
            }
        }
        return s;
    }
private:
    vector<string> name1 = vector<string>(2);
    vector<string> name2 = vector<string>(2);
    map<int, vector<string>> m;
    int bd;
};

int main() {
  Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  person.ChangeFirstName(1965, "Appolinaria");
  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
