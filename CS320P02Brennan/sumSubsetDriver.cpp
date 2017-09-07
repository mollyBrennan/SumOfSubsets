#include<iostream>
#include<list>

using namespace std;

int sum;

int setSum(const list<int> & x){ //function to total the sum of a set

	list<int> l = x;
	for (list<int>::iterator i = l.begin(); i != l.end(); i++){
		sum += *i;
	}
	return sum;
}

void sumSubs(list<int> originalList, int ssf, int mps, int total, list<int> &subList, list<list<int>> &tList){ //recursive call that finds subsets that sum to total
	int maxSum = mps;
	int sumSoFar = ssf;
	int t = total;

	int root; 
	list<int>og = originalList;
	list<int>::iterator it = og.begin();
	list<int>ogUpdate;

	if (og.begin() != og.end()){ //make sure to start at number that is less than the total sum looking for && *it <= t

		root = *it;//store root, then delete from original list
		//og.erase(it); make og a list without the first element dont return anything tho
		for (list<int>::iterator it = og.begin(); it != og.end(); it++){
			if (it != og.begin()){
				ogUpdate.push_back(*it);
			}
		}
		//create a new list 
		list<int> L = { 0, 1 }; //0 represents left branch of tree (do not add root to sum) - 1 represents right branch of tree (add root to sum)

		for (list<int>::iterator itr = L.begin(); itr != L.end(); itr++){
			if (*itr == 0){ //root not added 
				//ssf remains the same
				sumSoFar = ssf;
				maxSum = maxSum - root; // max sum does not include root

				if (sumSoFar >= maxSum || sumSoFar == t) //reached end of tree or found subset
				{
					if (sumSoFar == t){
						subList.sort(); //sort for printing purposes
						tList.push_back(subList); //Found Path so add to final listofLists
						subList.reverse(); //back to reverse order to keep recursive function working properly
					}
				}
				if (sumSoFar < total && maxSum >= total){ //in range, call recursion
					sumSubs(ogUpdate, sumSoFar, maxSum, t, subList, tList); //recursion
					if (subList.empty() != true) subList.pop_back(); //pop_back element to return so not lost
				}
				itr++; // dont need to go further down that tree path
			}
			if (*itr == 1){
				subList.push_back(root); // adds root to subset list
				sumSoFar = ssf + root; //sumSoFar includes root
				maxSum = maxSum + root;
				if (sumSoFar >= maxSum || sumSoFar == t) //reached end of tree or found subset
				{
					if (sumSoFar == t){ //found subset
						subList.sort(); //sort for printing purposes
						tList.push_back(subList); //Found Path, add to list of subsets
						subList.reverse(); //back to reverse order to keep recursive function working properly
					}
				}
				if (sumSoFar < total && maxSum >= total) //in range keep going
				{
					sumSubs(ogUpdate, sumSoFar, maxSum, t, subList, tList); //recursive call
					if (subList.empty() != true) subList.pop_back(); //pop_back element to return so not lost
				}
			}
		}//close for
	}//close if
}//close function
int printList(list<int> l){
	for (list<int>::iterator i = l.begin(); i != l.end(); i++){
		cout << *i << ", ";
	}
	return 0;
}

int printListList(list<list<int>> y){ //print list of lists
	int count = 1;
	for (list<list<int>>::iterator itr = y.begin(); itr != y.end(); itr++){
		cout << "A" << count << "= {";
		count++; //prints #of subsets ex. A1, A2
		for (list<int>::iterator itr2 = itr->begin(); itr2 != itr->end(); itr2++){
			itr2++;
			if (itr2 == itr->end()){ //last element special case
				itr2--;
				cout << *itr2 << "}";
			}
			else{
				itr2--;
				cout << *itr2 << ", ";
			}
		}
		cout << endl;
	}
	return 0;
}


bool isValid(list<int> v, int t){ //tests to see if the sum of subsets can be calculated
	if (setSum(v) < t){ //sum is too small to equal total
		return false;
	}
	else //sum can equal total
	{
		return true;
	}
}


int main(){
	//SPECS:
	/*original list is backwards sorted list given terminated with 0
	ssf = 0
	mps = setSum of original List
	total = total sum looking for 
	fList will be the subset that adds to total that needs to be returned
*/
	list<int> userSet;
	int userNum;
	int userTotal;
	list<int> emptySubList = {};
	list<list<int>> emptylol = {};

	cout << "Please enter a finite set of integers: (0 to quit): ";
	cin >> userNum;
	while (userNum != 0){//terminated by 0
	userSet.push_back(userNum);
	cin >> userNum;
	}
	cout << "Please enter a integer total: ";
	cin>>userTotal;
	
	userSet.sort(); //sorts input list
	userSet.unique();//no repeats
	userSet.reverse(); //reverses input list

	sumSubs(userSet, 0, setSum(userSet),userTotal,emptySubList, emptylol );

	//static testing
	//list <int> test1 = {30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	//sumSubs(test1, 0, setSum(test1), 7, emptySubList, emptylol);
	

	if (isValid(userSet, userTotal) == true && emptylol.begin() != emptylol.end()){ //if it is possible to find sum and at least one possible subset is found
		printListList(emptylol);
	}
	else{ cout << "(none)" << endl; }


	return 0;
}