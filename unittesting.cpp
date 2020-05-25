#include "acutest.h"
#include "functions.h"

void test_mediana(void){
    TEST_CHECK_(mediana({1,2,3,4,5,6,7,8,9,10},10)==5.5,"mediana({1,2,3,4,5,6,7,8,9,10},10)==5.5");
    TEST_CHECK_(mediana({1,3,5,7,9,12,13},7)==7,"mediana({1,3,5,7,9,12,13},7)==7");
    TEST_CHECK_(mediana({1,2},2)==1.5,"mediana({1,2},2)==1.5");
    TEST_CHECK_(mediana({1},1)==1,"mediana({1},1)==1");
}

TEST_LIST = {
    {"double mediana(vector<int>, int);",test_mediana},{0}
};
