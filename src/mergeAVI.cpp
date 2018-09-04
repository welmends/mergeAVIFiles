
#include<iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

//Prototypes
string getStrFromCmd(const char* cmd);
vector<string> splitMovs(string allMovs);

int main(){
  string allMovs = getStrFromCmd("ls -d -rt -1 $PWD/avi/*.*");
  vector<string> splitedMovs = splitMovs(allMovs);

  Mat frame;
  VideoCapture vc;
  VideoWriter vw;
  vw.open("merged.avi",CV_FOURCC('M','J','P','G'),6,Size(352,240),true);

  for(int i=0; i<(int)splitedMovs.size(); i++){
    cout<<i+1<<"/"<<splitedMovs.size()<<endl;
    vc = VideoCapture(splitedMovs[i]);
    while(vc.read(frame)){
      vw.write(frame);
    }
  }
  vw.release();

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
