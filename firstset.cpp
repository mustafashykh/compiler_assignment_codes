#include <string>
#include <iostream>

#define MAX_PRODUCTION_DEPT 10
#define MAX_PRODUCTIONS 10

using namespace std;

class FirstSet {
    public:
        string* productions;
        string* nonTerminals;
        string* transitionString;
        int numberofProductions;

        explicit FirstSet(string productionsList[], int num){
            numberofProductions = num;
            productions = productionsList;
            nonTerminals = new string[productionsList->length()];
            transitionString = new string[productionsList->length()];

            for(int i = 0 ; i < numberofProductions; i++){
                nonTerminals[i] = productions[i].at(0);
                transitionString[i] = productions[i].substr(3, productions[i].length());
            }
        }

        void printAll(){
            for(int i = 0; i < numberofProductions; i++){
                cout << nonTerminals[i] << "->" << transitionString[i] << "\n";
            }
        }

        static int frequency(const string& str, char ch){
            int count = 0;
            for (char i : str){
                if (i ==  ch){
                    ++ count;
                }
            }
            return count;
        }

        void evaluate(){
            int firstSetGrid[MAX_PRODUCTIONS][MAX_PRODUCTION_DEPT];
            int productionLevel = 0;
            for(int i = 0; i < numberofProductions; i++){
                int numberOfIndexes = frequency(transitionString[i], '|') + 1;
                int *indexes = getfirstSetIndexes(transitionString[i], numberOfIndexes);

//                for(int j = 0; j < numberOfIndexes; j++){
//                    cout << indexes[j];
//                }

                for(int x = productionLevel; x < numberofProductions; x++){
                    for(int y = 0; y < numberOfIndexes; y++){
                        firstSetGrid[x][y] = indexes[y];
                    }

                    for(int z = numberOfIndexes; z < MAX_PRODUCTION_DEPT; z++){
                        firstSetGrid[x][z] = -1;
                    }
                }

                productionLevel++;
            }
//            for(int i = 0 ; i < numberofProductions; i++){
//                cout << "\n[";
//                for (int j = 0; j < MAX_PRODUCTION_DEPT; j++){
//                    if(firstSetGrid[i][j] != -1){
//                        cout << firstSetGrid[i][j] << ",";
//                    }
//                }
//                cout << "]";
//            }


            for(int i = 0 ; i < numberofProductions; i++){
                cout << "\nfirst(" <<  nonTerminals[i] <<") {";
                for (int j = 0; j < MAX_PRODUCTION_DEPT; j++){
                    if(firstSetGrid[i][j] != -1){
                        if(isupper(transitionString[i].at(firstSetGrid[i][j]))){
                            getFirstSet(firstSetGrid, transitionString[i].at(firstSetGrid[i][j]));
                        }else{
                            cout << transitionString[i].at(firstSetGrid[i][j]) << ",";
                        }
                    }
                }
                cout << "}";
            }


        }

        void getFirstSet(int firstGridSet[MAX_PRODUCTIONS][MAX_PRODUCTION_DEPT], char ch){

            for(int i = 0; i < numberofProductions; i++){
                if((int)ch == (int)nonTerminals[i].at(0)){
                    for(int j = 0; j < MAX_PRODUCTION_DEPT; j++){
                        if(firstGridSet[i][j] != -1){
                            if(isupper(transitionString[i].at(firstGridSet[i][j]))){
                                getFirstSet(firstGridSet, transitionString[i].at(firstGridSet[i][j]));
                            }else{
                                cout << transitionString[i].at(firstGridSet[i][j]) << ",";
                            }
                        }
                    }
                }
            }
        }

        static int *getfirstSetIndexes(const string& str,int numOfIndexes){
            int *indexes = new int[numOfIndexes];

            indexes[0] = 0;
            for(int i = 1; i < numOfIndexes;){
                for(int j = 0; j < str.length(); j++){
                    if(str.at(j) == '|'){
                        indexes[i] = j+1;
                        i++;
                    }
                }
            }

            return indexes;
        }

};


int main()
{
    int numberOfProduction;

    cout << "Enter the number of productions\n";
    cin >> numberOfProduction;
    auto* productionStrings = new string[numberOfProduction];

    cout << "Enter the Production\n";
    for(int i = 0; i < numberOfProduction; i++){
        cin >> productionStrings[i];
    }

    auto *fs = new FirstSet(productionStrings, numberOfProduction);

    fs->evaluate();
    
}



// format of input

// A->ab|cA|B
// B->f|gh|i