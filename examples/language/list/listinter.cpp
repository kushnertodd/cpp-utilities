#include <vector>
#include <map>
#include <string>
#include <stdio.h>
using namespace std;

typedef vector<int> int_list;
typedef int_list::iterator int_list_iter;
typedef map<int, int> int_map;
typedef int_map::const_iterator int_map_iter;

class ListIntersect {
  private: int_list myList1;
  private: int_list myList2;
  public: ListIntersect(int_list list1, int_list list2) {
    myList1 = list1;
    myList2 = list2;
  }
  public: void set_intersect(int_list& result) {
    int_map join;
    for (int_list_iter iter = myList1.begin(); iter != myList1.end(); iter++) {
      join[*iter] = 1;
    }
    for (int_list_iter iter = myList2.begin(); iter != myList2.end(); iter++) {
      if (join.find(*iter) != join.end()) 
        join[*iter]++;
    }
    for (int_map_iter iter = join.begin(); iter != join.end(); iter++) {
      printf("results: (%d,%d)\n", iter->first, iter->second);
      if (iter->second > 1) {
        printf(" adding (%d,%d)\n", iter->first, iter->second);
        result.push_back(iter->first);
      }
    }
  }
  void printList(string message, int_list list) {
    printf("%s\n", message.c_str());
    for (int_list_iter iter = list.begin(); iter != list.end(); iter++) 
      printf("  %d\n", *iter);
  }
};
int main(int argc, char **argv) {
	const int list1_arr[] = {5, 3, 9, 4, 5};
	int_list list1 (list1_arr, list1_arr + sizeof(list1_arr) / sizeof(list1_arr[0]) );
	const int list2_arr[] = {7, 5, 2, 4, 1};
	int_list list2 (list2_arr, list2_arr + sizeof(list2_arr) / sizeof(list2_arr[0]) );
	ListIntersect *list_inter = new ListIntersect(list1, list2);
	int_list result;
	list_inter->set_intersect(result);
	list_inter->printList("list1:", list1);
	list_inter->printList("list2:", list2);
	list_inter->printList("result:", result);
}
