#include <iostream>

using namespace std;

class RyoBuilder {
private:
    string m_name1Opt = "name1 default";
    string m_name2Opt = "name2 default";
    string m_name3Req;

public:
    RyoBuilder(string name3Req) : m_name3Req(name3Req) {}
    static RyoBuilder& create(string name3Req) {
        cout << "RyoBuilder::create: name3Req " << name3Req << endl;
        RyoBuilder *ryoBuilder = new RyoBuilder(name3Req);
        return *ryoBuilder;
    }

    RyoBuilder& name1Opt(string name1Opt) {
        cout << "RyoBuilder::name1Opt: name1Opt " << name1Opt << endl;
        m_name1Opt = name1Opt;
        return *this;
    }

    RyoBuilder& name2Opt(string name2Opt) {
        cout << "RyoBuilder::name2Opt: name2Opt " << name2Opt << endl;
        m_name2Opt = name2Opt;
        return *this;
    }

    void print() {
        cout << "m_name1Opt = " << m_name1Opt  << endl;
        cout << "m_name2Opt = " << m_name2Opt << endl;
        cout << "m_name3Req = " << m_name3Req << endl;
    }

};

int main()
{
    RyoBuilder ryoBuilder = RyoBuilder::create("name3Req")
                            .name2Opt("name2Opt");
    ryoBuilder.print();
}
