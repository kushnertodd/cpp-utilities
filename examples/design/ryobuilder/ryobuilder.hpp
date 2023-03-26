#include <stdio>

class RyoBuilder {
  string m_name1Opt = "name1 default";
  string m_name2Opt = "name2 default;
  string m_name3Req;

  RyoBuilder(string name3Req) : m_name3Req(name3Req) {}
  RyoBuilder& create(string name3Req) {
    RyoBuilder ryoBuilder(name3Req);
    return ryoBuilder;
  }

  RyoBuilder& name1Opt(string name1Opt) { 
    m_name1Opt = name1Opt;
  }

  RyoBuilder& name1Opt(string name1Opt) { 
    m_name1Opt = name1Opt;
  }

};
