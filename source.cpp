//This program is used to identify the point if crossover for a dispersion relation.
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <getopt.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

using namespace std;
void parse_command_line(int argc, char **argv,string & filenamea,string &filenameb)
{
static struct option long_options[] = 
{
{"filenamea", required_argument,0,'a'},
{"filenameb",required_argument,0,'b'},
{0,0,0,0}
};
int option_index = 0;
char cc;
while ((cc=getopt_long(argc,argv,"a:b:",long_options,&option_index))!=-1){
switch(cc){
case 'a':     filenamea = optarg; break;
case 'b':     filenameb = optarg; break;
}
}
}
double stringConverTodouble(string str)
{
    istringstream iss(str);

    double  x;
    if(iss >> x) return x;
    return 0.0;
}
//function for switching string into double

int WavecarLines(char *filename)//读取WAVECAR行数
{
ifstream ReadFile;
int n=0;
string temp;
ReadFile.open(filename,ios::in);//ios::in 只读形式读取文件
if(ReadFile.fail())
{
return 0;
}
else 
{
while(getline(ReadFile,temp))
{
n++;
}
return n;
}
ReadFile.close();
}

int main(int argc,char** argv)
{

int x,s=0;
string filenamea,filenameb;
double coordinatecp[99999][3];
char filename1[512],filename2[512];
parse_command_line(argc,argv,filenamea,filenameb);
for(x=0;x<filenamea.length();x++)
filename1[x] = filenamea[x];
filename1[x]='\0';
for(x=0;x<filenamea.length();x++)
filename2[x] = filenameb[x];
filename2[x]='\0';
double FILE1[99999],FILE5[99999],REAL3[99999],REAL4[99999];
int theline;
ifstream file;
int LINES,n,i;
//char filename[512],filename2[512];
//cout<<"请输入文件名"<<endl;//输入文件名
//cin>>filename>>filename2;
file.open(filename1,ios::in);
if(file.fail())
{
cout<<"文件a不存在"<<endl;
file.close();
cin.get();
cin.get();
}
else
{
LINES=WavecarLines(filename1);//获取行数
string File[LINES];
string File2[LINES];
string Real1[LINES];
string buffer;
while(!file.eof())
{
{
getline(file,buffer,'(');//获取当前行的坐标数据
File[n]=buffer;//将数据存入数组
++n;
}
{
getline(file,buffer,',');//获取当前行的CG实部数据
Real1[s]=buffer;
++s;
}
{
getline(file,buffer,')');//获取当前行的CG虚部数据
File2[i]=buffer;
++i;
}
}
file.close();
ofstream in;
in.open("reala.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到reala.txt
in<<Real1[i]<<"\n";
in.close();
in.open("imaginarya.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到imaginarya.txt
in<<File2[i]<<"\n";
in.close();
in.open("coordinatea.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到coordinatea.txt
in<<File[i]<<"\n";
in.close();

//结束文件读取
for(i=0;i<LINES;++i)
FILE1[i] = stringConverTodouble(File2[i]);//string转double
for(i=0;i<LINES;++i)
REAL3[i] = stringConverTodouble(Real1[i]);//string转double
string coordinate[LINES][3];
vector<string> vStr;
  for(n=0;n<LINES;++n)
  {i=0;
  boost::split( vStr, File[n], boost::is_any_of( " " ), boost::token_compress_on );
  for( vector<string>::iterator it = vStr.begin(); it != vStr.end(); ++ it )
  {
    coordinate[n][i] = *it ;
    ++i;
  }
  }
  for(n=0;n<LINES;++n)
  {
  for(i=0;i<3;++i)
coordinatecp[n][i] = stringConverTodouble(coordinate[n][i]);
}
 //string转double
  //cout<<File[2]<<endl;
  //cout<<coordinate[2][2]<<endl;
}

//运算第二个文件
LINES=0;n=0;i=0;
file.open(filename2,ios::in);
if(file.fail())
{
cout<<"文件b不存在"<<endl;
file.close();
cin.get();
cin.get();
}
else
{
LINES=WavecarLines(filename2);//获取行数
string File3[LINES];
string File4[LINES];
string Real2[LINES];
string buffer2;
s=0;
while(!file.eof())
{
{
getline(file,buffer2,'(');//获取当前行的坐标数据
File3[n]=buffer2;//将数据存入数组
++n;
}
{
getline(file,buffer2,',');//获取当前行的实部数据
Real2[s]=buffer2;
++s;
}
{
getline(file,buffer2,')');//获取当前行的虚部数据
File4[i]=buffer2;
++i;}
}
theline=LINES;
file.close();//关闭读取的文件
ofstream in;
in.open("realb.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到realb.txt
in<<Real2[i]<<"\n";
in.close();
in.open("imaginaryb.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到imaginaryb.txt
in<<File4[i]<<"\n";
in.close();
in.open("coordinateb.txt",ios::trunc);
for(i=0;i<LINES;++i)//输出数据到coordinateb.txt
in<<File3[i]<<"\n";
in.close();
//结束文件读取
for(i=0;i<LINES;++i)
FILE5[i] = stringConverTodouble(File4[i]);//string转double
for(i=0;i<LINES;++i)
REAL4[i] = stringConverTodouble(Real2[i]);//string转double
}
//double coordinatefirst;
//coordinatefirst=cooriinatecp[2][1]*cooriinatecp[2][1];
double coordinateresult;
coordinateresult=coordinatecp[5][1]*coordinatecp[5][1];
//cout<<coordinateresult<<endl;
double resultreal=0,resultimaginary=0;
int m;
for(m=0;m<theline;++m)
{
resultreal=resultreal+(REAL3[m]*REAL4[m]+FILE1[m]*FILE5[m]);
}
for(m=0;m<theline;++m)
{
resultimaginary=resultimaginary+(-FILE1[m]*REAL4[m]+REAL3[m]*FILE5[m]);
}
//cout<<"实部结果为 "<<resultreal<<endl;
//cout<<"虚部结果为"<<resultimaginary<<endl;
cout<<"两点内积为:"<<'\n'<<resultreal<<" + "<<resultimaginary<<'i'<<endl;
return 0;
}


