#include <iostream>
#include <string.h>
#include "prime.cc"
#include "defn.h"

using namespace std;

int indexOfCat(char* category, categories* apps, int size);
tree* newNode(app_info info);
tree* insertBST(tree* root, tree* key);
int hashFunction(char* name, int buckets);
void insertHSH(tree* node, hash_table_entry*& hashList, int buckets);

categories* catList;
hash_table_entry* hashList;
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
  int hashSize = 2 * numApps + 1;
  while(!TestForPrime(hashSize)) {
    hashSize = hashSize + 2;
  }
  hashList = new hash_table_entry[hashSize];
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
    tree* tmpNode = newNode(tmpApp);
    int c = indexOfCat(category, catList, CAT_NAME_LEN);
    catList[c].root = insertBST(catList[c].root, tmpNode);
    cout << c << endl;
    insertHSH(tmpNode, hashList, hashSize);
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

tree* insertBST(tree* node, tree* key) {
  if(node == NULL)
    return key;
  if(strcmp(key->info.app_name, node->info.app_name) < 0)
    node->left = insertBST(node->left, key);
  else if(strcmp(key->info.app_name, node->info.app_name) > 0)
    node->right = insertBST(node->right, key);
  return node;
}

int hashFunction(char* name, int buckets) {
  int sum = 0;
  for(int i = 0; name[i] != '\0'; i++)
    sum = sum + name[i];
  return sum % buckets;
}

void insertHSH(tree* node, hash_table_entry*& hashList, int buckets) {
  int i = hashFunction(node->info.app_name, buckets);
  hash_table_entry* current = &hashList[i];
  while(current->app_node != NULL) {
    current->next = new hash_table_entry;
    current = current->next;
  }
  strcpy(current->app_name, node->info.app_name);
  current->app_node = node;
  current->next = NULL;
}
