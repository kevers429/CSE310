//Kevin Shannon
//usage: ./p2 < file

#include <iostream>
#include <string.h>
#include <iomanip>
#include "prime.cc"
#include "defn.h"

using namespace std;

int indexOfCat(char* category, categories* apps, int size);
tree* newNode(app_info info);
tree* insertBST(tree* root, tree* key);
tree* deleteBST(tree* root, tree* target);
tree* minValueNode(tree* node);
int hashFunction(const char* name, int buckets);
hash_table_entry* insertHSH(tree*& node, hash_table_entry* head, int buckets);
hash_table_entry* findNode(hash_table_entry* hashList, const char* key, int buckets);
void printApp(app_info* app);
void printInOrder(tree* root);
bool isInPriceRange(tree* root, float lo, float hi);
bool isInAppRange(tree* root, char* lo, char* hi);
void printPriceRange(tree* root, float lo, float hi);
void printAppRange(tree* root, char* lo, char* hi);
void deleteLinked(hash_table_entry** head_ref, hash_table_entry** del_ref);

categories* catList;
hash_table_entry* hashList;
float size, price, f_hi, f_lo;
int numCategories, numApps, numCommands;
char category[CAT_NAME_LEN], app_name[APP_NAME_LEN], version[VERSION_LEN], units[UNIT_SIZE], commandName[10], subCommand[10];
char c_lo[CAT_NAME_LEN], c_hi[CAT_NAME_LEN];

int main() {
  cin >> numCategories;
  cin.ignore(1,'\n');
  catList = new categories[numCategories]; //dynamically allocate catlist based of number of categories
  for(int i = 0; i < numCategories; i++) {
    cin.getline(catList[i].category, CAT_NAME_LEN);
    catList[i].root = NULL; //initialize root to null
  }
  cin >> numApps;
  int hashSize = 2 * numApps + 1; //size that we want before the next largest prime
  while(!TestForPrime(hashSize)) {
    hashSize = hashSize + 2; //only bother checking odd numbers
  }
  hashList = new hash_table_entry[hashSize]; //dynamically allocate hashtable based on hashSize
  for(int i = 0; i < numApps; i++) {
    cin.ignore(1,'\n'); //clear buffer
    cin.getline(category, CAT_NAME_LEN);
    cin.getline(app_name, APP_NAME_LEN);
    cin >> version >> size >> units >> price;
    app_info tmpApp;
    strcpy(tmpApp.category, category); //copy the memory in the pointers to a new tmp app
    strcpy(tmpApp.app_name, app_name);
    strcpy(tmpApp.version, version);
    strcpy(tmpApp.units, units);
    tmpApp.size = size;
    tmpApp.price = price;
    tree* tmpNode = newNode(tmpApp); //pointer to a tempory node containing our tmp app
    int c = indexOfCat(category, catList, CAT_NAME_LEN); //find cat index
    catList[c].root = insertBST(catList[c].root, tmpNode); //insert the node into the BST
    int h = hashFunction(tmpNode->info.app_name, hashSize);
    hashList[h] = *(insertHSH(tmpNode, &hashList[h], hashSize)); //insert node into Hash Table
  }
  cin >> numCommands;
  for(int i = 0; i < numCommands; i++) {
    cin >> commandName;
    if(strcmp(commandName, "find") == 0) { //is it a find command?
      cin >> subCommand; //what do they want to find?
      if(strcmp(subCommand, "app") == 0) {
        (cin >> ws).getline(app_name, APP_NAME_LEN);
        hash_table_entry* node = findNode(hashList, app_name, hashSize); //find the given app in the hash table and point to it
        if(node != NULL) //print it if it exists
          printApp(&node->app_node->info);
        else
          cout << "Application not found" << endl;
      }
      else if(strcmp(subCommand, "category") == 0) {
        (cin >> ws).getline(category, CAT_NAME_LEN);
        int c = indexOfCat(category, catList, CAT_NAME_LEN); //find the category
        if(c != -1)
          printInOrder(catList[c].root); //it exists, print everything in order
        else
          cout << "Category not found" << endl;
      }
      else if(strcmp(subCommand, "price") == 0) {
        cin.ignore(100,'\n'); //no need to read anything else
        bool foundFree = false; //tracks wether there are any free apps yet in any category
        for(int i = 0; i < numCategories; i++) {
          foundFree = (isInPriceRange(catList[i].root, 0, 0) || foundFree);
          if(isInPriceRange(catList[i].root, 0, 0)) { //if there exists at least one app with price is 0
            cout << catList[i].category << endl;
            printPriceRange(catList[i].root, 0, 0); //print everything in category with price = 0
            cout << endl;
          }
        }
        if(!foundFree)
          cout << "No free applications found" << endl;
      }
      cout << endl;
    }
    else if(strcmp(commandName, "range") == 0) {
      cin >> category;
      cin >> subCommand;
      int c = indexOfCat(category, catList, CAT_NAME_LEN);
      if(strcmp(subCommand, "price") == 0) {
        cin >> f_lo >> f_hi; //set bounds
        if(c != -1) {
          if(isInPriceRange(catList[c].root, f_lo, f_hi))
            printPriceRange(catList[c].root, f_lo, f_hi); //print everything in price range
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
            printAppRange(catList[c].root, c_lo, c_hi); //print everything in name range
          else
            cout << "No applications found for given range" << endl;
        }
        else
          cout << "Category not found" << endl;
      }
      cout << endl;
    }
    else if(strcmp(commandName, "delete") == 0) {
      cin >> category;
      (cin >> ws).getline(app_name, APP_NAME_LEN);
      hash_table_entry* tableNode = findNode(hashList, app_name, hashSize);
      hash_table_entry* headNode = &hashList[hashFunction(app_name, hashSize)];
      if(tableNode != NULL) {
        deleteLinked(&headNode, &tableNode);
        int c = indexOfCat(category, catList, CAT_NAME_LEN);
        catList[c].root = deleteBST(catList[c].root, tableNode->app_node);
      }
      else
        cout << "Application not found; unable to delete" << endl;
    }
  }
  return 0;
}

int indexOfCat(char* category, categories* cats, int size) { //returns index in categories array of specified category, -1 if not found
  for(int i = 0; i < size; i++) {
    if(strcmp(cats[i].category, category) == 0)
      return i;
  }
  return -1;
}

tree* newNode(app_info info) { //returns a pointer to a new tree node containg specified app info
  tree* temp =  new tree;
  temp->info = info;
  temp->left = temp->right = NULL;
  return temp;
}

tree* insertBST(tree* node, tree* key) { //returns pointer to root of the tree with the node inserted
  if(node == NULL)
    return key;
  if(strcmp(key->info.app_name, node->info.app_name) < 0) //key < node
    node->left = insertBST(node->left, key);
  else if(strcmp(key->info.app_name, node->info.app_name) > 0) //key > node
    node->right = insertBST(node->right, key);
  return node;
}

tree* deleteBST(tree* root, tree* target) { //returns pointer to the position of the node that was deleted after deleting it
  if(root == NULL)
    return root;
  if(strcmp(target->info.app_name, root->info.app_name) < 0)
    root->left = deleteBST(root->left, target);
  else if(strcmp(target->info.app_name, root->info.app_name) > 0)
    root->right = deleteBST(root->right, target);
  else {
    if(root->left == NULL) {
      tree* temp = root;
      root = root->right;
      delete temp;
    }
    else if(root->right == NULL) {
      tree* temp = root;
      root = root->left;
      delete temp;
    }
    else {
      tree* temp = minValueNode(root->right);
      root->info = temp->info;
      root->right = deleteBST(root->right, target);
    }
  }
  return root;
}

tree* minValueNode(tree* node) { //returns smallest node in subtree
  tree* current = node;
  while (current->left != NULL)
    current = current->left;
  return current;
}

int hashFunction(const char* key, int buckets) { //returns index of key in the hashtable using a hash function
  int sum = 0;
  for(int i = 0; key[i] != '\0'; i++)
    sum = sum + key[i];
  return sum % buckets;
}

hash_table_entry* insertHSH(tree*& node, hash_table_entry* head, int buckets) { //inserts new element into the given hash table
  hash_table_entry* newNode = new hash_table_entry;
  hash_table_entry* current = head;
  strcpy(newNode->app_name, node->info.app_name);
  newNode->app_node = node;
  newNode->next = NULL;
  if(current->app_node == NULL) {
    head = newNode;
    return head;
  }
  while(current->next != NULL) {
    current = current->next;
  }
  current->next = newNode;
  return head;
}

hash_table_entry* findNode(hash_table_entry* hashList, const char* key, int buckets) { //return a pointer to a hash_table_entry with the desired key
  hash_table_entry* current = &hashList[hashFunction(key, buckets)];
  if(current->app_node == NULL)
    return NULL;
  while(current != NULL) {
    if(strcmp(current->app_node->info.app_name, key) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

void printApp(app_info* app) { //prints all info associated with an app
  cout << std::setw(10) << std::left << "category:" << app->category << endl;
  cout << std::setw(10) << std::left << "app name:" << app->app_name << endl;
  cout << std::setw(10) << std::left << "version:" << app->version << endl;
  cout << std::setw(10) << std::left << "size:" << app->size << endl;
  cout << std::setw(10) << std::left << "units:" << app->units  << endl;
  cout << std::setw(10) << std::left << "price:" << app->price << endl;
}

void printInOrder(tree* root) { //prints BST in order
  if(root == NULL)
    return;
  printInOrder(root->left);
  cout << root->info.app_name << endl;
  printInOrder(root->right);
}

bool isInPriceRange(tree* root, float lo, float hi) { //returns bool of whether there is an element with price between lo and hi
  bool found = false;
  if(root == NULL)
    return false;
  if(root->info.price >= lo && root->info.price <= hi)
    return true;
  found = isInPriceRange(root->left, lo, hi) || isInPriceRange(root->right, lo, hi);
  return found;
}

bool isInAppRange(tree* root, char* lo, char* hi) { //returns bool of whether there is an element with app name between lo and hi
  bool found = false;
  if(root == NULL)
    return false;
  if(strcmp(root->info.app_name, lo) > -1 && strcmp(root->info.app_name, hi) < 1)
    return true;
  found = isInAppRange(root->left, lo, hi) || isInAppRange(root->right, lo, hi);
  return found;
}

void printPriceRange(tree* root, float lo, float hi) { //prints BST in order if the price is within the range of lo and hi
  if(root == NULL)
    return;
  printPriceRange(root->left, lo, hi);
  if(root->info.price >= lo && root->info.price <= hi)
    cout << root->info.app_name << endl;
  printPriceRange(root->right, lo, hi);
}

void printAppRange(tree* root, char* lo, char* hi) { //prints BST in order if the app name is within the range of lo and hi
  if(root == NULL)
    return;
  printAppRange(root->left, lo, hi);
  if(strcmp(root->info.app_name, lo) > -1 && strcmp(root->info.app_name, hi) < 1)
    cout << root->info.app_name << endl;
  printAppRange(root->right, lo, hi);
}

void deleteLinked(hash_table_entry** head_ref, hash_table_entry** del_ref) { //removes element from the hashtable
  if(*head_ref == NULL)
    return;
  hash_table_entry* temp = *head_ref;
  if(head_ref == del_ref) {
    *head_ref = temp->next;
    delete temp;
    return;
  }
  for(int i = 0; temp != NULL && temp->next != *del_ref; i++)
    temp = temp->next;
  if(temp == NULL || temp->next == NULL)
    return;
  hash_table_entry* next = temp->next->next;
  delete temp->next;
  temp->next = next;
}
