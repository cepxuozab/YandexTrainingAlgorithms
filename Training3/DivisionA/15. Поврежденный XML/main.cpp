#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

bool is_equal(const string& s, const pair<size_t, size_t>& s1, const pair<size_t, size_t>& s2) {
    if (s1.second - s1.first != s2.second - s2.first) {
        return false;
    }
    for (size_t i = 0; i <= s1.second - s1.first; i++) {
        if (s[i + s1.first] != s[i + s2.first]) {
            return false;
        }
    }
    return true;
}

void is_xml(const string& s) {
    stack<pair<size_t, size_t>> st;
    int opened = -1;
    int closed = -1;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            if (opened == -1 && closed == -1) {
                return;
            }
        }
        else {
            if (s[i] == '>') {
                if (opened == -1 && closed == -1) {
                    return;
                }
                if (opened != -1) {
                    st.push({ opened, i - 1 });
                    opened = -1;
                }
                if (closed != -1) {
                    if (st.empty() || !is_equal(s, st.top(), { closed, i - 1 })) {
                        return;
                    }
                    st.pop();
                    closed = -1;
                }
            }
            if (s[i] == '/') {
                if (opened == -1) {
                    return;
                }
                closed = i + 1;
                opened = -1;
            }
            if (s[i] == '<') {
                if (opened != -1 || closed != -1) {
                    return;
                }
                opened = i + 1;
            }
        }
    }
    if (!st.empty()) {
        return;
    }
    cout << s << '\n';
    exit(0);
}

int main() {
    string s;
    cin >> s;
    for (size_t i = 0; i < s.size(); i++) {
        char cur = s[i];
        s[i] = '<';
        is_xml(s);
        s[i] = '>';
        is_xml(s);
        s[i] = '/';
        is_xml(s);
        for (char x = 'a'; x <= 'z'; x++) {
            s[i] = x;
            is_xml(s);
        }
        s[i] = cur;
    }
}