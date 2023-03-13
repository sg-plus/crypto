#include<iostream>
#include<fstream>
#include<string>
#include<cstring>
#include<sys/time.h>
#include<pbc/pbc.h>

using namespace std;

int main(){
	ifstream in("/home/sg/code/graduate/pbc-0.5.14/param/a.param");
	string param;
	while(!in.eof()){
		string temp;
		getline(in,temp);
		temp += "\n";
		param += temp;
	}
	//cout<<param<<endl;

	char cParam[1024];
	strcpy(cParam,param.c_str());
	pairing_t pairing;
	element_t P,Q,K,a,tP,tQ,tK;

	//初始化为A类型曲线的配对
	pairing_init_set_buf(pairing,cParam,param.size());
	//初始化成对应群元素
	element_init_G1(P,pairing);
	element_init_G2(Q,pairing);
	element_init_GT(K,pairing);
	element_init_G1(tP,pairing);
	element_init_G2(tQ,pairing);
	element_init_GT(tK,pairing);
	element_init_Zr(a,pairing);
	//随机选取元素值
	element_random(P);
	element_random(Q);
	element_random(a);
	//进行1000次不同运算，并记录所需时间
	timeval t1,t2;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次点乘运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		element_mul_zn(tP,P,a);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次双线性配对运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		pairing_apply(K,P,Q,pairing);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;
	gettimeofday(&t1,nullptr);
	cout<<"--------------1000次幂乘运算-----------------"<<endl;
	cout<<"起始时间："<<"\n"<<t1.tv_sec<<"秒"<<t1.tv_usec<<"微秒"<<endl;
	for(int i=0;i<1000;++i){
		element_pow_zn(tK,K,a);
	}
	gettimeofday(&t2,nullptr);
	cout<<"结束时间："<<"\n"<<t2.tv_sec<<"秒"<<t2.tv_usec<<"微秒"<<endl;
	
	//输出
	//element_snprint(cParam,1024,K);
	//cout<<cParam<<endl;
	//清除内存
	element_clear(P);
	element_clear(Q);
	element_clear(K);
	element_clear(tP);
	element_clear(tQ);
	element_clear(tK);
	element_clear(a);
	pairing_clear(pairing);

	return 0;
}
