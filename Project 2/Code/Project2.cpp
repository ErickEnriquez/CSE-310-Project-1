#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "defn.h"
//
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*function prototypes*/

/*milestone functions*/
std::ostream& operator<<(ostream& out, const app_info & data);//overload operator to print the appInfo
tree* makeNewNode(tree*, app_info);//makes a new tree node with given appInfo
tree* insert(tree*, tree*);//inserts a new tree node into the tree
int getCategoryIndex(categories*, char*, int);//gets the index of a the category 
void printTree(tree*);//prints all nodes in a tree given a root
void findCategory(categories*, char*, int);//finds a category and prints all the nodes in that tree
void findPrice(categories*, int, int&);//given a dynamic array of categories print all of the apps which are free for each category
void isFree(tree*, int&);//prints all of the nodes that have price == 0
bool TestForPrime(int);//will check if number given is a prime number
void printPriceRange(tree*, float, float, int&);//given 2 prices it will print the prices in between the 2 
void printStringRange(tree*, char*, char*, int&);//given 2 strings it will print the strings in that range
void range(categories*, char*, float, float, int, int&);//to get range based on price
void range(categories*, char*, char*, char*, int, int&);//to get range based of strings


/*full project*/
void insertIntoTable(hash_table_entry*, tree*, int);//inserts a app_name along with a tree* into a hash table   
void initializeTable(hash_table_entry*, int);//sets all of the next ptrs in hash table to be null				
void printAppName(tree*);//prints out a given nodes info														
tree* findApp_Name(hash_table_entry*, char*, int);//looks for a app inside of a hash table						
void printFindApp(tree*);//given a tree pointer we will output the app's info									
tree* deleteApp(hash_table_entry*, char*, char*, int, int, categories*);//will remove an app from a given tree and return a root to updated tree
tree* deleteFromTree(tree*, app_info);//will use this to remove from the BST
int stringToInt(char*);//converts a Cstring to it's ascii value													
int hashName(char*, int);//take a string and return what it hashes to											
int printChain(hash_table_entry*, int);//prints chain at hash table of given index								
tree* getRoot(char*, categories*, int);//gets the root of a node given a node in the BST		

// characteristics functions
int numbOfNodes(tree*);//return the number of nodes in tree
int treeHeight(tree*);//return the height of tree
void printInfo(tree*);//in order traversal of tree given root. and print out all info


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////																	WORKS!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
int main() {

	printf("Implement myAppStore here.\n\n");

	int numCategories, m, index, q;
	int count = 0;
	char* inputIn = new char[APP_NAME_LEN];//using this to read in every field since cin mixed getline kept messing up

	/*strings we will be using to read in queues*/
	string s1, s2, s3, s4, s5;


	app_info temp;//temp app_info struct to hold data before it gets inserted into the tree
	tree* ptr; // ptr for use in BST and Hash Table

	cin.getline(inputIn, APP_NAME_LEN, '\n');//read in the number of categories we will have 

	numCategories = atoi(inputIn);//convert the string to an integer
	categories* cat = new categories[numCategories];//an array for the total number of categories

	for (int i = 0; i < numCategories; i++) {
		cin.getline(cat[i].category, CAT_NAME_LEN, '\n');
		cat[i].root = NULL;
	}

	cin.getline(inputIn, APP_NAME_LEN, '\n');//read in the number of apps as a string
	m = atoi(inputIn);//convert string into integer

	int k = (2 * m) + 1;//make k first possible prime number after 2*m
	while (TestForPrime(k) == false) {
		k = k + 2;//add two to skip all even numbers
	}

	hash_table_entry* arr = new hash_table_entry[k];//make a new array of size k for hashing
	initializeTable(arr, k);//set all the elements inside of the hash table to be null

	for (int i = 0; i < m; i++) {
		cin.getline(temp.category, CAT_NAME_LEN, '\n');
		cin.getline(temp.app_name, 100, '\n');
		cin.getline(temp.version, 100, '\n');
		cin.getline(inputIn, 100, '\n');
		temp.size = atof(inputIn);
		cin.getline(temp.units, UNIT_SIZE, '\n');
		cin.getline(inputIn, 6, '\n');
		temp.price = atof(inputIn);
		index = getCategoryIndex(cat, temp.category, numCategories);
		ptr = makeNewNode(cat[index].root, temp);// take temp and make it into a node
		cat[index].root = insert(cat[index].root, ptr);// ptr to the data in the tree to be used by the hash table in final version
		insertIntoTable(arr, ptr, k);//insert all of the values into their respective hash tables
	}

	cin.getline(inputIn, 5, '\n');
	q = atoi(inputIn);
	while (q > 0) {
		count = 0; //reset count to 0 again
		std::getline(std::cin, s1, ' ');//read in the first word of the command
		if (s1 == "find") {
			std::getline(std::cin, s2, ' ');
			if (s2 == "app") {
				std::getline(std::cin, s3, '\n');//read in app name
				const char* intermed = s3.c_str();
				char* name = new char[100];
				strcpy(name, intermed);
				printAppName(findApp_Name(arr, name, k));// call print appName function
				free(name);
			}
			else if (s2 == "category") {
				std::getline(std::cin, s3, '\n');//read in category
				const char* intermed = s3.c_str();
				char* categoryName = new char[CAT_NAME_LEN];//allocate an array to hold category name
				strcpy(categoryName, intermed);//copy it in to dynamic array
				findCategory(cat, categoryName, numCategories);
				free(categoryName);

			}
			else if (s2 == "price") {
				std::getline(std::cin, s3, '\n');//read in free
				findPrice(cat, numCategories, count);//call findPrice function
			}
		}
		else if (s1 == "range") {

			std::getline(std::cin, s2, '\n');//read in the rest of the line until newline
			std::reverse(s2.begin(), s2.end());//reverse the string
			s5 = s2.substr(0, s2.find(" "));//get the high input
			reverse(s5.begin(), s5.end());//reverse it to put back in order
			s2.erase(0, s2.find(" ") + 1);//erase that substring from the whole line
			s4 = s2.substr(0, s2.find(" "));//get the low input
			reverse(s4.begin(), s4.end());//reverse it in correct order
			s2.erase(0, s2.find(" ") + 1);//erase the substring from whole line
			s3 = s2.substr(0, s2.find(" "));//either price or app
			reverse(s3.begin(), s3.end());//reverse it to read properly
			s2.erase(0, s2.find(" ") + 1);//erase substring from whole line
			reverse(s2.begin(), s2.end());//reverse the line and s2 now holds the category name
			if (s3 == "price") {

				char* categoryName = new char[CAT_NAME_LEN];
				const char* intermed = s2.c_str();//convert string to Cstring
				strcpy(categoryName, intermed);//copy intermed into category name
				intermed = s4.c_str();
				float low = atof(intermed);//low holds low value
				intermed = s5.c_str();
				float high = atof(intermed);//high holds high value
				range(cat, categoryName, low, high, numCategories, count);
				free(categoryName);

			}
			else if (s3 == "app") {
				char* categoryName = new char[CAT_NAME_LEN];
				char* low = new char[100];
				char* high = new char[100];
				const char* intermed = s2.c_str();
				strcpy(categoryName, intermed);
				intermed = s4.c_str();
				strcpy(low, intermed);
				intermed = s5.c_str();
				strcpy(high, intermed);
				range(cat, categoryName, low, high, numCategories, count);
				free(categoryName);
				free(low);
				free(high);
			}
		}
		else if (s1 == "delete") {//we have to delete from tree
			std::getline(cin, s2, '\n'); //read into the end of the line and store into s2;
			bool found = false;
			s3 = "";//initialize s3 to be empty
			const char* intermediate;
			while (found != true) {//check if we have finished reading in the line or we have found the category
				s3.append(s2.substr(0, s2.find(" ")));//read in s2 until we get to space and append it to s3
				s2.erase(0, s2.find(" "));//erase part of string from the entire line
				intermediate = s3.c_str();//have intermediate hold intermediate
				char* string = new char[100];
				strcpy(string, intermediate);
				if (getCategoryIndex(cat, string, numCategories) != -1) {//if it is not -1 then we have the category
					found = true;
				}
				else {//if the app isn't found
					s3.append(s2.substr(0, 1));//add the space character to s3
					s2.erase(0, 1);//cut the space from s3.
				}
				if (s2.empty() == true)
					break;
				delete string;//free memory of string pointer

				//now check and see if it is a substring category
			}
			if (found == true) {
				//once we have found the category
				s2.erase(0, 1);//delete the leading space in string;
				//s2 now holds the app_name
				intermediate = s3.c_str();//
				char* category = new char[100];// holds category
				char* app_name = new char[100];//will hold app_name
				strcpy(category, intermediate);//category* now holds correct category
				intermediate = s2.c_str();
				strcpy(app_name, intermediate);//app_name* now holds app_name			
				int position = getCategoryIndex(cat, category, numCategories);
				cat[position].root = deleteApp(arr, category, app_name, k, numCategories, cat);//call the delete app and remove the app from tree and hash table		
				//free dynamic memory
				delete category;
				delete app_name;

			}
			else {
				cout << "Category Not found\n";
			}
		}
		cout << "----------------------------------------------------\n";
		q--;
	}



	//Characteristics of data/////////////////////////////////////////

	//
	double loadFactor = double(m) / double(k);
	cout << "\n\nThe load factor of the table is\t" << loadFactor << "\n\n";

	//characteristics of trees
	for (int i = 0; i < numCategories; i++) {
		cout << cat[i].category << endl;//print out the category name
		if (cat[i].root != NULL)
			printInfo(cat[i].root);//print out needed info by doing in-order traversal
		else
			cout << "empty tree\n";
		cout << "------------------------------\n\n";
	}
	////////////////////////////////////////////////////////////////////

	delete[] cat;//free the dynamic array
	delete[] arr;//free dynamic array

	return 0;
}

/*overload the << operator in order to print out the app's information*/
std::ostream & operator<<(ostream & out, const app_info & data) {
	out << "Category : " << data.category << "\n";
	out << "App Name : " << data.app_name << "\n";
	out << "Version : " << data.version << "\n";
	out << "Size : " << data.size << " " << data.units << "\n";
	out << "Price : " << data.price << "\n\n";
	return out;
}

/*allocates a node and retruns it's address*/
tree* makeNewNode(tree* root, app_info data) {
	tree* newNode = new tree();//allocate a tree node
	newNode->info = data;
	newNode->left = NULL;
	newNode->right = NULL;
	return newNode;
}

/*goes through the tree and inserts a given node into the tree*/
tree* insert(tree* root, tree* data) {
	if (root == NULL) {//empty tree
		root = data;
	}
	else if (strcmp(data->info.app_name, root->info.app_name) <= 0) {
		root->left = insert(root->left, data);
	}
	else {
		root->right = insert(root->right, data);
	}
	return root;
}

/*checks the categories arr to see if it can find the index where that category is returns -1 if category isn't in array*/
int getCategoryIndex(categories* arr, char* data, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(arr[i].category, data) == 0)
			return i;
	}
	return -1;
}

/*function will add up all of the string values of a Cstring and give you the sum of all it's ascii values*/
int stringToInt(char * string) {
	int sum = 0;
	int i = 0;
	while (string[i] != '\0') {//while we havent gotten to the end of the string
		sum = sum + (int)string[i];
		i++;
	}
	return sum;
}

/*take a string and a value k and get an index to hash data to*/
int hashName(char * str, int  k) {
	int sum = stringToInt(str);//get ascii sum value of a string
	int index = sum % k;
	return index;
}

/*this function prints the tree given a root node*/
void printTree(tree* root) {
	if (root != NULL) {
		if (root->left != NULL) {
			printTree(root->left);
		}
		std::cout << root->info;
		if (root->right != NULL) {
			printTree(root->right);
		}

	}
	else {
		std::cout << "empty tree \n";
	}
}

/*function searches through the tree and looks to see if the category exists. and prints it if it does*/
void findCategory(categories* arr, char* data, int size) {
	int i = getCategoryIndex(arr, data, size);//find the index of the category in question
	if (i >= 0) {//if the index == -1 that means the category does not exist
		printTree(arr[i].root);//call the print tree function with the root of the index of the category
	}
	else {
		std::cout << "category not found\n";
	}
}

/* helper function that does in order traversal and checks if the app is free and prints it out if it does.
holds a count variable that will be used by the find price categories*/
void isFree(tree* root, int& count) {
	if (root != NULL) {
		if (root->left != NULL) {
			isFree(root->left, count);
		}
		if (root->info.price == 0) {
			std::cout << root->info;
			count++;
		}
		if (root->right != NULL) {
			isFree(root->right, count);
		}

	}
}

/*finds all of the apps in the array of categories that are free. if there are none it prints No apps found */
void findPrice(categories* arr, int size, int& count) {
	for (int i = 0; i < size; i++) {
		isFree(arr[i].root, count);
	}
	if (count == 0) {
		std::cout << "No apps found\n";
	}
}

/*helper function that find all of the apps that are in between low and high price for a given tree*/
void printPriceRange(tree * root, float low, float high, int& count) {
	if (root != NULL) {
		if (root->left != NULL) {
			printPriceRange(root->left, low, high, count);
		}
		if (root->info.price >= low && root->info.price <= high) {
			std::cout << root->info;
			count++;
		}
		if (root->right != NULL) {
			printPriceRange(root->right, low, high, count);
		}
	}
}

/*given a category and a low and high , and size it will print out all of the apps that are inside of that price range*/
void range(categories* arr, char* data, float low, float high, int size, int&count) {
	int i = getCategoryIndex(arr, data, size);
	if (i >= 0) {//if the category is inside of the categories array
		printPriceRange(arr[i].root, low, high, count);
	}
	if (count == 0) {
		cout << "No apps in given price range\n";
	}
}

/*helper function that does in order traversal of a tree and prints data that falls in range of high and low*/
void printStringRange(tree * root, char * low, char * high, int& count) {
	if (root != NULL) {
		if (root->left != NULL) {
			printStringRange(root->left, low, high, count);
		}
		if (strcmp(root->info.app_name, low) >= 0 && strcmp(root->info.app_name, high) <= 0) {
			std::cout << root->info;
			count++;
		}
		if (root->right != NULL) {
			printStringRange(root->right, low, high, count);
		}
	}
}

/*given a category goes through and gives all apps in given range of characters*/
void range(categories * arr, char* data, char* low, char* high, int size, int& count) {
	int index = getCategoryIndex(arr, data, size);
	if (index >= 0) {
		printStringRange(arr[index].root, low, high, count);
	}
	if (count == 0) {
		cout << "no apps found in given string range\n";
	}
}

/*checks too see if given value is a prime number*/
bool TestForPrime(int val) {
	int limit, factor = 2;

	limit = (long)(sqrtf((float)val) + 0.5f);
	while ((factor <= limit) && (val % factor))
		factor++;

	return(factor > limit);
}

/*inserts the pointer reference of the tree along with the app_name in a hash table using seperate chaining */
void insertIntoTable(hash_table_entry* table, tree* ptr, int  k) {
	int index = hashName(ptr->info.app_name, k);//get the hash position of the app_name
	hash_table_entry* temp = new hash_table_entry;//allocate a pointer of hash table entry
	strcpy(temp->app_name, ptr->info.app_name);//copy the app_name into temps member
	temp->app_node = ptr;//set temps app_node to tree ptr
	temp->next = NULL;//set temps next to null
	if (table[index].next == NULL) {//if we have an empty index
		table[index].next = temp;//set temp as head pointer
	}
	else {
		temp->next = table[index].next;// make temps next attach to the chains aleady in the tables index
		table[index].next = temp;//set head pointer to be temp
	}
}

/*sets all the next pointer in the hash table to be null*/
void initializeTable(hash_table_entry* table, int k) {
	for (int i = 0; i < k; i++) {
		table[i].next = NULL;
	}
}

/*looks in the hash table for an app and returns a tree* of app if found*/
tree* findApp_Name(hash_table_entry* table, char* key, int k) {
	int index = hashName(key, k);//find what position that app_name would hash to
	hash_table_entry* temp = table[index].next;//set out temp to start at head 
	while (temp != NULL) {//while we havent gotten to the end of the chain
		if (strcmp(temp->app_name, key) == 0)
			return temp->app_node;//return the pointer in the tree where the data is stored
		else
			temp = temp->next;//walk the temp pointer down the list
	}
	return NULL;//if we walked the list
}

/*will  print an app's info if given and print app not found otherwise*/
void printAppName(tree* ptr) {
	if (ptr == NULL) {//if the app does not exist
		cout << "app_not found\n";
	}
	else {
		cout << ptr->info;//print out the apps info
	}
}

/*removes an app froma hash table given a category, an app_name , and a size of the table k*/
tree* deleteApp(hash_table_entry* table, char* category, char* app_name, int k, int numCategories, categories* arr) {
	int index = hashName(app_name, k);//get the postition that the app_name would hash to
	hash_table_entry* temp = table[index].next;//set temp as the head of the list
	hash_table_entry* prev = temp;//set previous to head too
	bool found = false;
	if (table[index].next == NULL) {//empty chain
		cout << "Unable to delete App not found\n\n";
		return getRoot(category, arr, numCategories);//return the unchanged root 
	}
	if (strcmp(temp->app_name, app_name) == 0 && table[index].next != NULL) {//if the app is at the head of the chain
		//delete the app from the tree first
		tree* newRoot = deleteFromTree(getRoot(category, arr, numCategories), temp->app_node->info);
		//now we delete the app from the tree
		table[index].next = temp->next;//move the head to whatever the 2nd item is in the chain
		delete temp;
		temp = NULL;
		cout << "Successfully Deleted app\n";
		return newRoot;
	}
	else {
		while (temp != NULL && found == false) {
			if (strcmp(temp->app_name, app_name) == 0) {
				found = true;
			}
			else {
				prev = temp;//have prev be value before 
				temp = temp->next;//move the head pointer 1 spot forward
			}
		}
		if (found == true) {
			tree* newRoot = deleteFromTree(getRoot(category, arr, numCategories), temp->app_node->info);//delete node from tree and get new node
			// here we will delete the node from the hash table and from the bst as well
			//delete the app from the tree first

			//now we delte the app from the table
			prev->next = temp->next;// link previous node with the temp's next in table
			delete temp; //delete temp from table
			temp = NULL;//set temp to be null to remove dangling pointer
			cout << "Successfully Deleted app\n";
			return newRoot;//return the updated root
		}
		else if (found == false) {//if we are unable to find the app in the table then just return the same root. and don't change it 
			cout << "app_not found, unable to delete\n";
			return getRoot(category, arr, numCategories);
		}
	}
}

// deletes app from tree. returns a root to the updated tree 
tree* deleteFromTree(tree* root, app_info key) {
	if (root == NULL)
		return root;
	else if (strcmp(root->info.app_name, key.app_name) > 0)
		root->left = deleteFromTree(root->left, key);
	else if (strcmp(root->info.app_name, key.app_name) < 0)
		root->right = deleteFromTree(root->right, key);
	else {
		if (root->left == NULL && root->right == NULL) {//no children
			delete root;
			root = NULL;
			return root;
		}
		else if (root->left == NULL) {//only right child
			tree* temp = root;
			root = root->right;
			delete temp;
		}
		else if (root->right == NULL) {//only left child
			tree* temp = root;
			root = root->left;
			delete temp;
		}
		else {
			tree* temp = root->right;//make temp be the right child of the root
			while (temp->left != NULL) {//walk down until we find the successor of root i.e. it's in order successor
				temp = temp->left;
			}
			root->info = temp->info;//swap root's info with its successor
			root->right = deleteFromTree(root->right, temp->info);//call delete and look for the info we swapped to delete on next call
		}
	}
	return root;
}

/*prints chain at index of hashtable. used for debugging*/
int printChain(hash_table_entry* table, int index) {
	int count = 0;
	if (table[index].next == NULL) {
		cout << "empty tree\n";
	}
	else {
		hash_table_entry* temp = table[index].next;//set temp to be the head
		while (temp != NULL) {
			cout << temp->app_node->info;//print out the app's info
			temp = temp->next;//move the temp pointer along the chain
			count++;//increase the count by 1
		}
	}
	return count;
}

/*given a node of a BST return the root of the tree*/

tree* getRoot(char* category, categories* arr, int size) {
	for (int i = 0; i < size; i++) {
		if (strcmp(category, arr[i].category) == 0) {//check the data's category with the categories of the arr and return the root when found
			return arr[i].root;
		}
	}
	return NULL;
}

/*does in order traversal and return the number of nodes in tree*/
int numbOfNodes(tree* root) {
	int count = 1;
	if (root == NULL)
		return 0;//node is empty
	return (count + numbOfNodes(root->left) + numbOfNodes(root->right));//recursively add up the sum of all the nodes in the tree
}

/*returns the maximum height of tree*/
int treeHeight(tree* root) {
	if (root == NULL) {//walked down to the end of the tree
		return 0;//return 0 as we have gotten to the end of the tree
	}
	int leftH = treeHeight(root->left);//recursively call get height on left subtree
	int rightH = treeHeight(root->right);//recursively call get height on right subtree
	if (leftH > rightH)//find out which subtree is larger and return it's height +1
		return leftH + 1;
	else
		return rightH + 1;

}

/*in order traversal of tree and prints out relevant info about number of nodes in subtrees and height of subtrees*/
void printInfo(tree*root) {
	if (root->left != NULL) {
		printInfo(root->left);
	}
	cout << root->info << endl;//output the app info
	cout << "Number of nodes in left Tree " << numbOfNodes(root->left) << endl;//print out number of nodes in left subtree
	cout << "Number of nodes in right Tree " << numbOfNodes(root->right) << endl;//print out the number of nodes in right subtree
	cout << "Height of left-subtree " << treeHeight(root->left) << endl;//return the height of node's left tree
	cout << "Height of rightSubtree " << treeHeight(root->right) << endl;//return height of node's right subtree
	cout << "\n\n";
	if (root->right != NULL) {
		printInfo(root->right);
	}
}

