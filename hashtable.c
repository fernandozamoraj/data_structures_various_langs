#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
   Hashtable implementation
   requirements
   1. Hold any data type (void *)
   2. 
*/

/*
  Reduce MAX_SIZE to lower number than items
  to test collisions
*/
#define MAX_SIZE 1000  
#define DATA void

//In reality this shouldbe separate from Node
//key and data should be should in a KeyValue pair
//and and a node should contain that as nested struct
typedef struct Node{
  char* key;
  DATA* data; 
  struct Node* next;
} Node_t;

/*
  http://www.cse.yorku.ca/~oz/hash.html
*/
unsigned long hash(unsigned char* str);

int getHash(char* str);

void displayTableInt(Node_t* hashTable[]);
void displayTableString(Node_t* hashTable[]);

void put(char* key, DATA* data, Node_t* hashTable[]);

Node_t* get(char* key, Node_t* hashTable[]);

void initHashTable(Node_t* hashTable[]);

void deleteList(Node_t* list);

void deleteTable(Node_t* hashTable[]);

/*
   --------List Functions---------------
*/

Node_t* createLink();

Node_t* findNode(char* key, Node_t* list);

Node_t* addNode(char* key, DATA* data, Node_t* list);

Node_t* getTail(Node_t* list);

void displayListInt(Node_t* list);

void putInt(char* key, int val, Node_t* hashTable[]){
  
  int* newVal = malloc(sizeof(val));
  *newVal = val;
  
  put(key, newVal, hashTable);
}

void putString(char* key, const char* str, Node_t* hashTable[]){
  char* newVal = strdup(str);
  put(key, newVal, hashTable);
}

void incrementCount(char* key, Node_t* hashTable[]){
   Node_t* node = get(key, hashTable);
  
  if(node != NULL){
    int* val = node->data;
    putInt(key, ++(*val), hashTable);
  }
  else{
    putInt(key, 1, hashTable);
  }
}

Node_t** createTable(){
  Node_t**  hashTable = malloc(sizeof(Node_t*) * MAX_SIZE);
  
  initHashTable(hashTable);
  
  return hashTable;
}

void testWithInts(){
   //Create array of Node_t pointers
  Node_t** hashTable = createTable();
  
  printf("\n\nTest with ints....");
  putInt("dog", 1, hashTable);
  putInt("cat", 2, hashTable);
  putInt("horse", 3, hashTable);
  putInt("bird", 4, hashTable);
  putInt("lion", 5, hashTable);
  putInt("tiger", 5, hashTable);
  putInt("zebra", 6, hashTable);
  putInt("dog", 7, hashTable);
  putInt("zebra", 8, hashTable);
  
  //update zebra
  //by updating it's count
  incrementCount("zebra", hashTable);
  
  //notice that gazelle does not exist
  incrementCount("gazelle", hashTable);
 
  
  if(get("Rhino", hashTable) == NULL){
    printf("\nRhino test PASSED..");
  }
  
  displayTableInt(hashTable);
  deleteTable(hashTable);
}

void testWithWords(){
  char* words[] = {"the", "cat", "was", "from", "a", "planet", "called", "mars", "and", 
                   "pluto", "was", "from", "a", "planet", "called", "pluto"};
  Node_t* hashTable = createTable();
  
  printf("\n\n******TEST WITH WORDS**********");
  for(int i=0;i<16;i++){
    incrementCount(words[i], hashTable);
  }
  
  displayTableInt(hashTable);
  
  deleteTable(hashTable);
                   
  printf("\n\n******END OF TEST WITH WORDS**********");                 
}

void testWithStrings(){
   //Create array of Node_t pointers
  Node_t**  hashTable = createTable();
  
  printf("\n\nTest with strings....");
  putString("dog", "bone", hashTable);
  putString("cat", "toy", hashTable);
  putString("horse", "hay", hashTable);
  putString("bird", "feed", hashTable);
  putString("cat", "yarn", hashTable); //for collision
  
  Node_t* item = get("bird", hashTable);

  displayTableString(hashTable);
  deleteTable(hashTable);
}

int main(void) {
  
  testWithInts();
  testWithStrings();
  testWithWords();
  
  return 0;
}

/*
   ----------Hashtable Functions----------------

*/
int getHash(char* str){
  return hash(str) % MAX_SIZE;
}

unsigned long hash(unsigned char* str){
  unsigned long hash = 5381;
  int c;
  
  while(c = *str++){
    hash = ((hash << 5) + hash) + c;
  }
  
  return hash;
}

void put(char* key, DATA* data, Node_t* hashTable[]){
  int hashIndex = getHash(key);
  
  Node_t* list = hashTable[hashIndex];
  
  printf("\nPutting %s at %d", key, hashIndex);
  
  if(list == NULL){
    hashTable[hashIndex] = createLink();
    hashTable[hashIndex]->key = strdup(key);
    hashTable[hashIndex]->data = data;
  }
  else{  //collision
    
    printf("\nFound collision with %s", key);
    
    Node_t* node = findNode(key, list);
    
    if(node == NULL){
      
      printf("\nAdding node for %s", key);
      node = addNode(key, data, list);
    }
    else{

      //free the node data since it is being replaced with new
      //allocated data
      free(node->data);
      node->data = data;
    }
  }
}

Node_t* get(char* key, Node_t* hashTable[]){
  int hashIndex = getHash(key);
  
  Node_t* list = hashTable[hashIndex];
  
  //if the hash function works correctly this
  //will always be true because of hash % MAX_SIZE
  if(list != NULL){  
    
    Node_t* node = findNode(key, list);
    
    if(node == NULL){
      printf("\n%s not found: ", key);
      return NULL;
    }
    else{
      printf("\nFound %s at %d", key, hashIndex);
      return node;
    }
  }
  
  return NULL;
}

void initHashTable(Node_t* hashTable[]){
  for(int i=0; i<MAX_SIZE; i++){
    hashTable[i] = NULL;
  }
}

void displayTableInt(Node_t* hashTable[]){
  
  printf("\n\n****HASHTABLE****");
  for(int i = 0; i < MAX_SIZE; i++){
    Node_t* head = hashTable[i];
    
    if(head != NULL){
      displayListInt(head);
    }
  }
}

void displayTableString(Node_t* hashTable[]){
  
  printf("\n\n****HASHTABLE****");
  for(int i = 0; i < MAX_SIZE; i++){
    Node_t* head = hashTable[i];
    
    if(head != NULL){
      displayListString(head);
    }
  }
}


void deleteTable(Node_t* hashTable[]){
  
  printf("\n\n****DELETING HASHTABLE****");
    
  for(int i = 0; i < MAX_SIZE; i++){
    deleteList(hashTable[i]);
  }
  
  printf("\nDeleting hashtable...");
  free(hashTable);
}
/*
  -------List functions----------

*/
Node_t* createLink(){
  Node_t* newLink = malloc(sizeof(Node_t));
  
  if(newLink != NULL){
    newLink->next = NULL;
    newLink->data = NULL; 
  }
  
  return newLink;
}

Node_t* findNode(char* key, Node_t* list){
  
  Node_t* temp = list;
  
  while(temp != NULL){
    if(strcmp(key, temp->key) == 0){
      return temp;
    }
    temp = temp->next;
  }
  
  return temp;
}

Node_t* addNode(char* key, DATA* data, Node_t* list){
  Node_t* node = createLink();
  Node_t* tail = NULL;
  
  node->key = strdup(key);
  node->data = data;
  
  tail = getTail(list);
  tail->next = node;
  
  return node;
}

Node_t* getTail(Node_t* list){
  
  Node_t* temp = list;
  Node_t* tail = list;
  
  if(temp != NULL){
    while(tail->next != NULL){
      tail = tail->next;
    }  
  }
  
  return tail;
}

void displayListInt(Node_t* list){
  Node_t* temp = list;
  int *value = 0;
  
  while(temp != NULL){
    value = temp->data;
    printf("\n%d %s", *value, temp->key);
    temp = temp->next;
  }
}

void displayListString(Node_t* list){
  Node_t* temp = list;
  char *value;
  
  while(temp != NULL){
    value = temp->data;
    printf("\n%s %s", value, temp->key);
    temp = temp->next;
  }
}

void deleteList(Node_t* list){
  
  Node_t* temp = list;
  Node_t* next = list;
  
  while(temp != NULL){
    next = temp->next;
  
    printf("\nDeleting %s...", temp->key);
    free(temp->key);
    free(temp->data);
    free(temp);

    temp = next;
  }
}

