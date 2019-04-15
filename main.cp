//  main.cpp
//  DataFrame
//
//  Created by Lane Quigley on 1/26/18.
//  Copyright © 2018 Lane Quigley. All rights reserved.
//

#include <iostream>

using namespace std;
//A Data Structure class that formats inputs into a table and allows for naming of each row and column.
class DataFrame {
protected:
    int** table;            //integers arragened into columns and rows
    int noRows, noCols;     // number of rows and columns in table
    char** colNames;        // the names of each column
    char** rowNames;        // the names of each row
    
public:
    //Constructors
    //Constructs an empty DataFrame class
    DataFrame ();
    //Constructs a DataFrame class with a specified number of rows and columns as well as names for each row/column
    DataFrame (int rows, int cols);
    
    //Output Method
    //outputs the dataframe to the console
    void display(){
    
        
        for(int i=0; i<noCols; i++){     //outputs the column names seperated by a comma
            if (i!=(noCols-1)){
                cout<<colNames[i]<<',';}
            else{
                cout<<colNames[i]<<endl;
            }
        }
        
        for(int i=0; i<noRows; i++){        //outputs the row names seperated by a comma
            if (i!=(noRows-1)){
                cout<<rowNames[i]<<',';}
            else{
                cout<<rowNames[i]<<endl;
            }
        }
        
       
        
        for (int i=0; i < noRows; i++) {      //outputs the dataframe table ie rows and columns
            for (int j=0; j < noCols; j++) {
                cout <<table[i][j] << " ";
            }
            cout << endl;
        }
    }
    //Setters
    //Assigns a specified name to the a specified row
    void setRowName(int row, char* name){
        rowNames[row]=name;
    }
    //Assigns a specified name to the a specified column
    void setColName(int col, char* name){
        colNames[col]=name;
    }
    //Get row i  Returns the desired row
    int* operator[] (int i){
        return table[i];
    }
    //Getters
    //Returns the char** containing row names
    char** getRowNames(){
        return rowNames;
    }
     //Returns the char** containing column names
    char** getColNames(){
        return colNames;
    }
    //Gives the number of rows in the dataframe
    int getNumberRows(){
        return noRows;
    }
     //Gives the number of columns in the dataframe
    int getNumberCols(){
        return noCols;
    }
    //Gives the int** containing the rows and columns
    int** getTable(){
        return table;
    }
    //Empties all the row names in the dataframe
    void emptyRowNames(){
        for (int i=0; i<noRows; i++){
            rowNames[i]= (char*)'\0';
        }
        
    }
    //Empties all the column names in the dataframe
    void emptyColNames(){
        for (int i=0; i<noCols; i++){
            colNames[i]= (char*)'\0';
        }
    }
    //Empties the rows and columns of the Dataframes table
    void emptyRowCols(){
        for(int i = 0; i<noRows; i++){
            setColName(i, (char *)"");
        }
        for(int i = 0; i<noCols; i++){
            setRowName(i, (char *)"");
        }
        
    }
   //Returns the specified columns in a new Dataframe
   DataFrame* getColumns(int* columns, int cLen){
     
       char** tempColNames;
       
        tempColNames = new char*[cLen];
        for(int i=0; i<cLen;i++){                   //fills tempColumnNames with the columns specified in the parameter
            
            tempColNames[i]  = colNames[columns[i]];
           
        }
       
       char** tempRow;
       tempRow=new char*[noRows];
       for(int i=0;i<noRows;i++){               //fills the rows with the same row names as the current datatframe
           tempRow[i]=rowNames[i];
       }
      
       int** newTable;
       
       newTable = new int*[noRows];             //Creates a new table adjusting the number of columns to the number given
       for (int i=0; i<noRows; i++){                //in the parameter
           newTable[i] = new int[cLen];
       }
       
       for (int i =0;i<noRows;i++){                 //fills the table with the same values for the rows and the specified
       for (int j=0; j<cLen; j++){                  //specified columns
           newTable[i][j] = table[i][columns[j]];
       }
       }
       DataFrame* newColumns = new DataFrame;       //Creates a new DataFrame object
       
       newColumns->table = newTable;                //each class variable for the new dataframe is initialized
       newColumns->noRows=noRows;
       newColumns->noCols=cLen;
       newColumns->colNames=tempColNames;
       newColumns->rowNames=tempRow;
     
        return newColumns ;
    }
    DataFrame* getRows(int* rows, int rLen){        //returns a new Dataframe object with specific rows from the object
                                                    // the method is called on
        char** tempRowNames;
        tempRowNames = new char*[rLen];
        
        for(int i=0; i<rLen;i++){               // fills new rows with the selected rows from the passed DataFrame
            tempRowNames[i]  = rowNames[rows[i]];
        }
        char** tempColumnNames;
        
        tempColumnNames = new char*[noCols];        //fills new columns with columns from the passed DataFrame
        for(int i=0;i<noCols;i++){
            tempColumnNames[i]= colNames[i];
        }
        
        int** newTable;
        
        newTable = new int*[rLen];          //creates a new table that has same number of columns and
        for (int i=0; i<rLen; i++){         //specified  number of rows
            newTable[i] = new int[noCols];
        }
        
        for (int i =0;i<rLen;i++){              //fills the new table with new rows and old columns
            for (int j=0; j<noCols; j++){
                newTable[i][j] = table[rows[i]][j];
            }
        }
        
        
        DataFrame* newRows = new DataFrame; //Creates a new dataframe class
        
        newRows->table = newTable;          //initializes the objects class variables
        newRows->noRows=rLen;
        newRows->noCols=noCols;
        newRows->colNames=tempColumnNames;
        newRows->rowNames=tempRowNames;
        
        return newRows;
        
    }
    DataFrame* getRowsCols(int* rows, int rLen, int* cols, int cLen){ //Allows user to specify what columns and
        char** tempRowNames;                                          //rows to access from a dataframe
      
        tempRowNames = new char*[rLen];
        for(int i=0; i<rLen;i++){                   //fills the new row names with the selected rows from the parameter
            tempRowNames[i]  = rowNames[rows[i]];
        }
        char** tempColNames;
        
        tempColNames = new char*[cLen];
        for(int i=0; i<cLen;i++){                   //fills the new column names with the selected columns from the
                                                    //parameters
            tempColNames[i]  = colNames[cols[i]];
        }
        
        int** newTable;
        
        newTable = new int*[rLen];              //creates a new table with the selected rows and columns
        for (int i=0; i<rLen; i++){
            newTable[i] = new int[cLen];
        }
        for (int i =0;i<rLen;i++){
            for (int j=0; j<cLen; j++){
                newTable[i][j] = table[rows[i]][cols[j]];
            }
        }
        
        DataFrame* newColRows = new DataFrame;      //creates a new dataframe
        
        newColRows->table = newTable;               //initializes class variables for new dataframe with selected rows
        newColRows->noRows=rLen;                    // and columns
        newColRows->noCols=cLen;
        newColRows->colNames=tempColNames;
        newColRows->rowNames=tempRowNames;
        
        return newColRows;
        
    }
    //Destructor
    //Deletes a dataframe object
    ~DataFrame(){
        delete table;
        delete colNames;
        delete rowNames;
    }
};
//Constructs a dataframe object
DataFrame::DataFrame(){
}
//Constructs a dataframe object with specified rows, columns, row names and column names
DataFrame::DataFrame(int row, int cols){

    table = new int*[row];          //Makes a table with specified number of rows and columns
    for (int i=0; i<row; i++){
        table[i] = new int[cols];
    }
    char c;
    int j=0;
    
    
    
    colNames = new char*[cols];         //creates a char* with correct number of column names
    for (int i=0; i<cols; i++){
        colNames[i]= new char[50];
    }
    
    rowNames = new char*[row];          //creates a char* with correct number of row names
    for (int i=0; i<row; i++){
        rowNames[i]= new char[50];
    }
    noRows = row;
    noCols = cols;
    
 
    
    for(int i=0; i<cols; i++){          //gets input from the file and inputs into colNames
        cin.get(c);
        j=0;
        
        do{
            colNames[i][j++]=c;
            cin.get(c);
        }while (((c!= ',')&&(c != '\n')));  //only assigns value to colNames if the character is not a , or \n
        colNames[i][j] = '\0';
        }
    
    
    for (int i=0; i < row; i++) {          //takes input from the file and adds it to rowNames
        cin.get(c);
        j = 0;
        
        do {
            rowNames[i][j++] = c;
            cin.get(c);
        } while (((c != ',') && (c != '\n'))); //only takes the input character when its not a , or \n
        rowNames[i][j] = '\0';
        }
    
    for (int i=0; i < row; i++){            //takes the input from the file and adds it to the DataFrames table
        for (int j=0; j < cols; j++){
            cin >> table[i][j];
        }
    }

    
    
    
}
int main() {
    freopen("input2.txt","r",stdin);  //this is how I was reading the file on my machine.
    // insert code here...
    int r,c;
    int selectC[3];
    int selectR[10];
    // Read the dataframe from input
    // First line: two numbers seperated by space;
    // first number is the number of rows (r) and
    // second number is the number of columns (c)
    cin >> r >> c;

    DataFrame* firstDF = new DataFrame(r,c);
    firstDF->display();
    
    // Read the column numbers that you want to extract
    for (int i=0; i < 3; i++)
    cin >> selectC[i];
  
  DataFrame* tempColumns = (*firstDF).getColumns(selectC, 3);
    (*tempColumns).display();
    
    // Change the row names of select rows
    (*tempColumns).setRowName(2, (char*)"Jack");
    (*tempColumns).setRowName(3, (char*)"Peter");
  
    (*tempColumns).display();
    
    // Read the row numbers that you want to extract
    for (int i=0; i < 10; i++)
      cin >> selectR[i];
   DataFrame* tempRows = (*firstDF).getRows(selectR, 10);
    (*tempRows).display();
  
    // Change the column names of selected columns
    (*tempRows).setColName(2, (char*)"Scores");
    (*tempRows).setColName(3, (char*)"Values");
    (*tempRows).display();
    
    DataFrame* tempColsRows = (*firstDF).getRowsCols(selectR, 10, selectC, 3);

    (*tempColsRows).display();
    
    delete tempRows;
    delete tempColumns;
    delete tempColsRows;
    // Sample Code for you and you must execute this
   DataFrame* myTable = new DataFrame(5,5);
    for (int i =0; i<5; i++){
        for (int j=0;j<5;j++){
       (*myTable).getTable()[i][j] = i*j;
           myTable->emptyRowCols();
        }
    }

    (*myTable).display();
    
    return 0;

}
