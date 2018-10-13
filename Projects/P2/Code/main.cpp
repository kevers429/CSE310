#include <iostream>
#include <string.h>
#include "defn.h"

using namespace std;

int indexOfCat(char* category, categories* apps, int size);
tree* newNode(app_info info);
tree* insert(tree* root, app_info key);

categories* catList;
float size, price;
int numCategories, numApps;
char category[CAT_NAME_LEN], app_name[APP_NAME_LEN], version[VERSION_LEN], units[UNIT_SIZE];

int main() {
  cin >> numCategories;
  cin.ignore(1,'\n');
  catList = new categories[numCategories];
  for(int i = 0; i < numCategories; i++) {
    cin.getline(catList[i].category, CAT_NAME_LEN);
    catList[i].root = NULL;
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
    catList[indexOfCat(category, catList, CAT_NAME_LEN)].root = insert(catList[indexOfCat(category, catList, CAT_NAME_LEN)].root, tmpApp);
  }
  return 0;
}

int indexOfCat(char* category, categories* cats, int size) {
  for(int i = 0; i < size; i++) {
    if(strcmp(cats[i].category, category) == 0)
      return i;
  }
  return -1;
}

tree* newNode(app_info info) {
  tree* temp =  new tree;
  temp->info = info;
  temp->left = temp->right = NULL;
  return temp;
}

tree* insert(tree* node, app_info key) {
  if(node == NULL)
    return newNode(key);
  if(strcmp(key.app_name, node->info.app_name) < 0)
    node->left = insert(node->left, key);
  else if(strcmp(key.app_name, node->info.app_name) > 0)
    node->right = insert(node->right, key);
  return node;
}
