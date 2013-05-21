#include<string>
#include<vector>
using std::string;
using std::vector;
class ImageDithering {
public:
  int count(string dithered, vector<string> screen);
};

int ImageDithering::count(string dithered, vector<string> screen) {
  bool dithered_map[26] = {false};
  for (int i=0; i<26; ++i) {
    dithered_map[i] = false;
  }
  for (int i=0; i<dithered.length(); ++i) {
    dithered_map[dithered[i]-'A'] = true;
  }
  int cnt =0;
  for (int i=0; i<screen.size(); ++i) {
    for (int j=0; j<screen[i].length(); ++j) {
      if(dithered_map[screen[i][j]-'A']) {
        ++cnt;
      }
    }
  }
  return cnt;
}

