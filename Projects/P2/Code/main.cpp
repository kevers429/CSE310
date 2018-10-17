#include <iostream>
#include <string.h>
#include <iomanip>
#include "prime.cc"
#include "defn.h"

using namespace std;

int indexOfCat(char* category, categories* apps, int size);
tree* newNode(app_info info);
tree* insertBST(tree* root, tree* key);
int hashFunction(const char* name, int buckets);
void insertHSH(tree*& node, hash_table_entry*& hashList, int buckets);
app_info* findNode(hash_table_entry* hashList, const char* key, int buckets);
void printApp(app_info* app);
void printInOrder(tree* root);
bool isInPriceRange(tree* root, float lo, float hi);
bool isInAppRange(tree* root, char* lo, char* hi);
void printPriceRange(tree* root, float lo, float hi);
void printAppRange(tree* root, char* lo, char* hi);

categories* catList;
hash_table_entry* hashList;
float size, price, f_hi, f_lo;
int numCategories, numApps, numCommands;
char category[CAT_NAME_LEN], app_name[APP_NAME_LEN], version[VERSION_LEN], units[UNIT_SIZE], commandName[10], subCommand[10];
char c_lo[CAT_NAME_LEN], c_hi[CAT_NAME_LEN];

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
    insertHSH(tmpNode, hashList, hashSize);
  }
  cin >> numCommands;
  for(int i = 0; i < numCommands; i++) {
    cin >> commandName;
    //cout << "the command is " << commandName << endl;
    if(strcmp(commandName, "find") == 0) {
      cin >> subCommand;
      if(strcmp(subCommand, "app") == 0) {
        (cin >> ws).getline(app_name, APP_NAME_LEN);
        app_info* app = findNode(hashList, app_name, hashSize);
        if(app != NULL)
          printApp(app);
        else
          cout << "Application not found" << endl;
      }
      else if(strcmp(subCommand, "category") == 0) {
        (cin >> ws).getline(category, CAT_NAME_LEN);
        int c = indexOfCat(category, catList, CAT_NAME_LEN);
        if(c != -1)
          printInOrder(catList[c].root);
        else
          cout << "Category not found" << endl;
      }
      else if(strcmp(subCommand, "price") == 0) {
        cin.ignore(100,'\n');
        bool foundFree = false;
        for(int i = 0; i < numCategories; i++) {
          foundFree = (isInPriceRange(catList[i].root, 0, 0) || foundFree);
          if(isInPriceRange(catList[i].root, 0, 0)) {
            cout << catList[i].category << endl;
            printPriceRange(catList[i].root, 0, 0);
            cout << endl;
          }
        }
        if(!foundFree)
          cout << "No free applications found" << endl;
      }
    }
    else if(strcmp(commandName, "range") == 0) {
      cin >> category;
      cin >> subCommand;
      //cout << "the subcommand is " << subCommand << endl;
      int c = indexOfCat(category, catList, CAT_NAME_LEN);
      if(strcmp(subCommand, "price") == 0) {
        cin >> f_lo >> f_hi;
        if(c != -1) {
          if(isInPriceRange(catList[c].root, f_lo, f_hi))
            printPriceRange(catList[c].root, f_lo, f_hi);
          else
            cout << "No applications found for given range" << endl;
        }
        else
          cout << "Category not found" << endl;
      }
      else if(strcmp(subCommand, "app") == 0) {
        cin >> c_lo >> c_hi;
        if(c != -1) {
          if(isInAppRange(catList[c].root, c_lo, c_hi))
            printAppRange(catList[c].root, c_lo, c_hi);
          else
            cout << "Category not found" << endl;
        }
        else
          cout << "Category not found" << endl;
      }
    }
    cout << endl;
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

int hashFunction(const char* key, int buckets) {
  int sum = 0;
  for(int i = 0; key[i] != '\0'; i++)
    sum = sum + key[i];
  return sum % buckets;
}

void insertHSH(tree*& node, hash_table_entry*& hashList, int buckets) {
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

app_info* findNode(hash_table_entry* hashList, const char* key, int buckets) {
  hash_table_entry* cur = &hashList[hashFunction(key, buckets)];
  while(cur->app_node != NULL) {
    if(strcmp(cur->app_node->info.app_name, key) == 0)
      return &cur->app_node->info;
    cur = cur->next;
  }
  return NULL;
}

void printApp(app_info* app) {
  cout << std::setw(10) << std::left << "category:" << app->category << endl;
  cout << std::setw(10) << std::left << "app name:" << app->app_name << endl;
  cout << std::setw(10) << std::left << "version:" << app->version << endl;
  cout << std::setw(10) << std::left << "size:" << app->size << endl;
  cout << std::setw(10) << std::left << "units:" << app->units  << endl;
  cout << std::setw(10) << std::left << "price:" << app->price << endl;
}

void printInOrder(tree* root) {
  if(root == NULL)
    return;
  printInOrder(root->left);
  cout << root->info.app_name << endl;
  printInOrder(root->right);
}

bool isInPriceRange(tree* root, float lo, float hi) {
  bool found = false;
  if(root == NULL)
    return false;
  if(root->info.price >= lo && root->info.price <= hi)
    return true;
  found = isInPriceRange(root->left, lo, hi) || isInPriceRange(root->right, lo, hi);
  return found;
}

bool isInAppRange(tree* root, char* lo, char* hi) {
  bool found = false;
  if(root == NULL)
    return false;
  if(strcmp(root->info.app_name, lo) > -1 && strcmp(root->info.app_name, hi) < 1)
    return true;
  found = isInAppRange(root->left, lo, hi) || isInAppRange(root->right, lo, hi);
  return found;
}

void printPriceRange(tree* root, float lo, float hi) {
  if(root == NULL)
    return;
  printPriceRange(root->left, lo, hi);
  if(root->info.price >= lo && root->info.price <= hi)
    cout << root->info.app_name << endl;
  printPriceRange(root->right, lo, hi);
}

void printAppRange(tree* root, char* lo, char* hi) {
  if(root == NULL)
    return;
  printAppRange(root->left, lo, hi);
  if(strcmp(root->info.app_name, lo) > -1 && strcmp(root->info.app_name, hi) < 1)
    cout << root->info.app_name << endl;
  printAppRange(root->right, lo, hi);
}
