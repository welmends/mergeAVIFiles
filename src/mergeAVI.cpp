#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

//Prototypes
string getStrFromCmd(const char* cmd);
vector<string> splitMovs(string allMovs);

int main(){
  //Input
  string precaution = getStrFromCmd("[ -d ./avi_in ] && echo 'avi_in found' || echo 'avi_in not found'");
  cout<<endl<<"----------------------------------------------------------------------------------"<<endl<<endl;
  if(precaution == "avi_in not found\n"){
    system("mkdir -p avi_in");
    cerr<<"OUTPUT: You must put your avi files into avi_in folder"<<endl<<endl;
    exit(0);
  }
  precaution = getStrFromCmd("ls avi_in/ -F |grep -v / | wc -l");
  if(precaution == "0\n"){
    cerr<<"OUTPUT: There are 0 files in avi_in"<<endl<<endl;
    exit(0);
  }

  //Split avi files directories
  string allMovs = getStrFromCmd("ls -d -rt -1 $PWD/avi_in/*.*");
  vector<string> splitedMovs = splitMovs(allMovs);

  //Merging
  cout<<"OUTPUT: Merging avi files..."<<endl<<endl;
  Mat frame;
  VideoCapture vc;
  VideoWriter vw;
  vw.open("avi_out/merged.avi",CV_FOURCC('M','J','P','G'),6,Size(352,240),true);

  for(int i=0; i<(int)splitedMovs.size(); i++){
    cout<<i+1<<"/"<<splitedMovs.size()<<endl;
    vc = VideoCapture(splitedMovs[i]);
    while(vc.read(frame)){
      vw.write(frame);
    }
  }
  vw.release();
  cout<<endl<<"OUTPUT: All files were merged!"<<endl<<endl;

  return 0;
}

string getStrFromCmd(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL){
                result += buffer;
            }
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}
vector<string> splitMovs(string allMovs){
  vector<string> splitedMovs;
  string line;
  stringstream ss(allMovs);
  while(getline(ss,line,'\n')){
    splitedMovs.push_back(line);
  }
  return splitedMovs;
}
