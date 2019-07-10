/***************************************/
/* author: Chengsheng Mao	           */
/* version: 1.2	                       */
/***************************************/

#include<iostream>
#include<sstream>
#include <fstream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<string>
#include<time.h>
#include<sys/time.h>
#include<iomanip>
//#include<windows.h>

#include"point.h"
#include"rangetree.h"
#include"rangetreeFC.h"
#include"interval.h"
#include"intervaltree.h"
#include"indexrtFC.h"
#include"rangetree2d.h"
#include"itvtree.h"
#include"rtfc_eqkey.h"


using namespace std;

#define OPN 11

void queryproc(string datafile, vector<string>& queryfile);

int main(int argc, char** argv)
{
//    string filename = "./testdata/1.exons";
//    string queryfile = "./testdata/1.rnaseqs";

    string filename = argv[1];
    vector<string> queryfile;
    for(auto i=2;i<argc;i++)
        queryfile.push_back(argv[i]);
    
    for_each(queryfile.begin(),queryfile.end(),[](string s){cout<<s<<endl;});
        
        
	queryproc(filename, queryfile);

return 0;


}

// query the intervals in queryfile from the intervals in datafile
void queryproc(string datafile, vector<string>& queryfile)
{
	vector<Point> origin;
    vector<vector<Point>> querydata(queryfile.size());
    vector<string> outfile(queryfile.size());
    vector<ofstream> outfs(queryfile.size());
    vector<string> op= { "o","oi","d","di","si","s","f","fi","m","mi","e","p","pi" };
    
	origin = readfile(datafile);    
    for(auto i=0;i<queryfile.size();i++)
    {
        querydata[i] = readfile(queryfile[i]);
//        querydata[i].erase(querydata[i].begin(),querydata[i].begin()+100000);
        string outname=queryfile[i]+".res";
        outfs[i].open(outname.data());
        outfs[i]<<"#number of original data:"<<origin.size()<<endl;
        outfs[i]<<"#number of query data:"<<querydata[i].size()<<endl;
    }

timeval  c1, c2;
    
        
/*************rangetreeFC****************/
{    
	indexrtFC Tfc(origin);
	cout<<"\nBuilding indexrtFC for "<<datafile<<"..."<<endl;  //for rangetree FC
	gettimeofday(&c1,NULL);
	Tfc.buildtree();   //build rangetreeFC
	gettimeofday(&c2,NULL);
	unsigned long bt=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);

    for(auto ifl=0;ifl<queryfile.size();ifl++)
    {
        outfs[ifl]<<"RTFC build time:"<<bt<<endl;
        size_t q_size=querydata[ifl].size();       
        for(int j=0;j<OPN;j++)
        {
            unsigned long t=0;
            unsigned long n=0;
            vector<Point> result;
            cout<<op[j]<<" query for"<<queryfile[ifl]<<"..."<<endl;
            gettimeofday(&c1,NULL);
            for(int i=0;i<q_size;i++)
            {
                Point  from, to;
                Interval(querydata[ifl][i]).transform(op[j],from,to);
                Tfc.rangequery(from,to,result);
                n+=result.size();
            }
            gettimeofday(&c2,NULL);
            t=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);
            outfs[ifl]<<t<<','<<n<<endl;
        }
        outfs[ifl]<<endl;
    }
}
   
/*************rtfc_eqkey****************/
/*{    
	rtfc_eqkey Tfc(origin);
	cout<<"\nBuilding rtfc_eqkey for "<<datafile<<"..."<<endl;  //for rangetree FC
	gettimeofday(&c1,NULL);
	Tfc.buildtree();   //build rangetreeFC
	gettimeofday(&c2,NULL);
	unsigned long bt=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);

    for(auto ifl=0;ifl<queryfile.size();ifl++)
    {
        outfs[ifl]<<"rtfc_eqkey build time:"<<bt<<endl;
        size_t q_size=querydata[ifl].size();       
        for(int j=0;j<OPN;j++)
        {
            unsigned long t=0;
            unsigned long n=0;
            vector<Point> result;
            cout<<op[j]<<" query for"<<queryfile[ifl]<<"..."<<endl;
            gettimeofday(&c1,NULL);
            for(int i=0;i<q_size;i++)
            {
                Point  from, to;
                Interval(querydata[ifl][i]).transform(op[j],from,to);
                Tfc.rangequery(from,to,result);
                n+=result.size();
            }
            gettimeofday(&c2,NULL);
            t=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);
            outfs[ifl]<<t<<','<<n<<endl;
        }
        outfs[ifl]<<endl;
    }
}
*/
  
/*************rangetree**********/
{
	rangetree2d T(origin);
	cout<<"\nBuilding rangetree for "<<datafile<<"..."<<endl;  //for rangetree 
	gettimeofday(&c1,NULL);
	T.buildtree();   //build rangetree
	gettimeofday(&c2,NULL);
	unsigned long bt=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);

    for(auto ifl=0;ifl<queryfile.size();ifl++)
    {
        outfs[ifl]<<"2D-RT build time:"<<bt<<endl;
        size_t q_size=querydata[ifl].size();        
        for(int j=0;j<OPN;j++)
        {
            unsigned long t=0;
            unsigned long n=0;
            vector<Point> result;
            cout<<op[j]<<" query for"<<queryfile[ifl]<<"..."<<endl;
            gettimeofday(&c1,NULL);
            for(int i=0;i<q_size;i++)
            {
                Point  from, to;
                Interval(querydata[ifl][i]).transform(op[j],from,to);
                T.rangequery(from,to,result);
                n+=result.size();
            }
            gettimeofday(&c2,NULL);
            t=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);
            outfs[ifl]<<t<<','<<n<<endl;
        }
        outfs[ifl]<<endl;
    }
}
  
    /*************itvtree**********/
{
	itvtree iT;
	cout<<"\nBuilding itvtree for "<<datafile<<"..."<<endl;  //for rangetree FC
	gettimeofday(&c1,NULL);
	iT.buildtree(origin);    //build
	gettimeofday(&c2,NULL);
	unsigned long bt=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);

	typedef void (itvtree::*psearch)(itvtree::RB_Node* node, Interval i, \
                                          vector<Interval>& result) ;
	psearch search[]={&itvtree::search_o,&itvtree::search_oi, \
                        &itvtree::search_d,&itvtree::search_di, \
                        &itvtree::search_si,&itvtree::search_s, \
                        &itvtree::search_f,&itvtree::search_fi, \
                        &itvtree::search_m,&itvtree::search_mi, \
                        &itvtree::search_e,&itvtree::search_p,&itvtree::search_pi};

    for(auto ifl=0;ifl<queryfile.size();ifl++)
    {
        outfs[ifl]<<"IT build time:"<<bt<<endl;
        size_t q_size=querydata[ifl].size();
        for(int j=0;j<OPN;j++)
        {
            unsigned long t=0;
            unsigned long n=0;
            vector<Interval> result(0);
            cout<<op[j]<<" query for"<<queryfile[ifl]<<"..."<<endl;
            gettimeofday(&c1,NULL);
            for(int i=0;i<q_size;i++)
            {
                result.clear();
                Interval I(querydata[ifl][i]);
               (iT.*search[j])(iT.m_root, I, result);

                n+=result.size();
            }
            gettimeofday(&c2,NULL);
            t=1000000*(c2.tv_sec-c1.tv_sec)+(c2.tv_usec-c1.tv_usec);
            outfs[ifl]<<t<<','<<n<<endl;
        }
        outfs[ifl]<<endl;
    }
}
      
for(auto i=0;i<outfs.size();i++)
    outfs[i].close();

}
