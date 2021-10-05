#include <gtest/gtest.h>
#include <vector>
#include "embedding.h"


double embA[20] = {-0.9166718150866153,0.43829227278389205,-0.6129205231425989,0.7738693110376684,-0.04456069156634124,0.8807831166061564,-0.8206278700342509,0.5013513447020947,0.8570578529268591,0.3906799520892723,0.6558968505921785,0.0011654760044317314,0.3008835791217257,-0.15983430198414705,-0.0693333837225647,-0.6526558237637923};
double embB[20] = {0.9210598583969818,0.42579710374854174,0.4036360259825613,0.030714658443632636,-0.885772459758438,-0.24727514094877123,0.7355606108008894,0.10546495518591437,-0.8023562184533268,-0.49625645997262624,-0.9207327565798142,-0.5815206606673406,0.9351907452001367,0.3172382122419557,0.003001769800845988,-0.922981014248552};
double embC[20] = {0.9210598583969818,0.42579710374854174,0.4036360259825613,0.030714658443632636,-0.885772459758438,-0.24727514094877123,0.7355606108008894,0.10546495518591437,-0.8023562184533268,-0.49625645997262624,-0.9207327565798142,-0.5815206606673406,0.9351907452001367,0.3172382122419557,0.003001769800845988,-0.922981014248552};

namespace proj1 {
namespace testing{

class EmbeddingTest : public ::testing::Test {
 protected:
  void SetUp() override {
    
	//double embC[20] = {0.9210598583969818,0.42579710374854174,0.4036360259825613,0.030714658443632636,-0.885772459758438,-0.24727514094877123,0.7355606108008894,0.10546495518591437,-0.8023562184533268,-0.49625645997262624,-0.9207327565798142,-0.5815206606673406,0.9351907452001367,0.3172382122419557,0.003001769800845988,-0.922981014248552};	
	emb_testA = new Embedding(20, embA);  
	emb_testB = new Embedding(20, embB);   
	emb_testC = new Embedding(20, embC);   
	embhA.push_back(emb_testA);
	embhB.push_back(emb_testB);
	embhC.push_back(emb_testC);
	embh_testA = new EmbeddingHolder(embhA);
	embh_testB = new EmbeddingHolder(embhB);
	embh_testC = new EmbeddingHolder(embhC);
  }
  Embedding* emb_testA;
  Embedding* emb_testB;
  Embedding* emb_testC;
  std::vector<Embedding*>embhA;
  std::vector<Embedding*>embhB;
  std::vector<Embedding*>embhC;
  EmbeddingHolder* embh_testA;
  EmbeddingHolder* embh_testB;
  EmbeddingHolder* embh_testC;
};

bool compare(Embedding* emb_test, double *data){
	double * tmp = emb_test->get_data();
	for(int i = 0; i<20; i++){
		if(tmp[i]!=data[i])return false;
	}
	return true;
}

TEST_F(EmbeddingTest, test_embdedding){
	double emb[20] = {-0.9166718150866153,0.43829227278389205,-0.6129205231425989,0.7738693110376684,-0.04456069156634124,0.8807831166061564,-0.8206278700342509,0.5013513447020947,0.8570578529268591,0.3906799520892723,0.6558968505921785,0.0011654760044317314,0.3008835791217257,-0.15983430198414705,-0.0693333837225647,-0.6526558237637923};
	EXPECT_EQ(true, compare(emb_testA, emb));
	EXPECT_EQ((*emb_testB) == (*emb_testC), true);
	EXPECT_EQ((*emb_testB) == (*emb_testA), false);
	EXPECT_EQ((*emb_testC) == (*emb_testA), false);
}

TEST_F(EmbeddingTest, test_embdeddingHolder){
	EXPECT_EQ((*embh_testB) == (*embh_testC), true);
	EXPECT_EQ((*embh_testB) == (*embh_testA), false);
	EXPECT_EQ((*embh_testC) == (*embh_testA), false);
}

} // namespace testing
} // namespace proj1

int main(int argc,char **argv){
  testing::InitGoogleTest(&argc,argv);
  return RUN_ALL_TESTS();
}
