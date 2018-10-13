#include <iostream>
#include <string.h>
#include "defn.h"

using namespace std;

categories* appList;
float size, price;
int numCategories, numApps;
char category[CAT_NAME_LEN], app_name[APP_NAME_LEN], version[VERSION_LEN], units[UNIT_SIZE];

int main() {
  cin >> numCategories;
  cin.ignore(1,'\n');
  appList = new categories[numCategories];
  for(int i = 0; i < numCategories; i++) {
    cin.getline(appList[i].category, CAT_NAME_LEN);
    appList[i].root = new tree;
  }
  cin >> numApps;
  for(int i = 0; i < numApps; i++) {
    cin.ignore(1,'\n');
    cin.getline(category, CAT_NAME_LEN);
    cin.getline(app_name, APP_NAME_LEN);
    cin >> version >> size >> units >> price;
    app_info tmpApp;
    strcpy(tmpApp.category, category);
    strcpy(tmpApp.app_name, app_name);
    strcpy(tmpApp.version, version);
    strcpy(tmpApp.units, units);
    tmpApp.size = size;
    tmpApp.price = price;
  }
  return 0;
}
