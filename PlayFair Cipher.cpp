#include<iostream>
#include<cstring>
#include<limits>
using namespace std;

void cipher_key(char key[6][6], const string& userInput) 
{
    int index = 0;
    
    char charArray[userInput.length() + 1];
    strcpy(charArray, userInput.c_str());

    for (size_t i = 0; i < userInput.length(); ++i) 
        if (charArray[i] >= 'a' && charArray[i] <= 'z') 
            charArray[i] -= 32;
            

    for (char ch : charArray) 
    {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= '0' && ch <= '9')) 
        {
            bool found = false;
            for (int i = 0; i < index; ++i) 
            {
                if (key[i / 6][i % 6] == ch) 
                {
                    found = true;
                    break;
                }
            }
            if (!found && index < 36) 
            {
                key[index / 6][index % 6] = ch;
                index++;
            }
        }
    }

    char current_Ch = 'A';
    while (index < 36) {
        bool found = false;
        for (int i = 0; i < index; ++i) 
        {
            if (key[i / 6][i % 6] == current_Ch) 
            {
                found = true;
                break;
            }
        }
        if (!found && (current_Ch >= 'A' && current_Ch <= 'Z')) 
        {
            key[index / 6][index % 6] = current_Ch;
            index++;
        } else if (!found && (current_Ch >= '0' && current_Ch <= '9')) 
        {
            key[index / 6][index % 6] = current_Ch;
            index++;
        }
        current_Ch++;
        if (current_Ch == '[')
            current_Ch = '0';
    }
}

int main() {
    char key[6][6];
    
    cout << " Hello and Welcome :) " << endl;
    
    cout << "Enter an Encryption key: ";
    string user_key_Input;
    cin >> user_key_Input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    

    cipher_key(key, user_key_Input);
    
    cout <<endl<< "Enter your message: ";
    
    string input_message;
    getline(cin, input_message);
    
    string updated_message = input_message;

    for (size_t i = 0; i < updated_message.length(); ++i) 
    {  
        if (updated_message[i] == ' ') 
        {
            for (int j = i; j < updated_message.length() - 1; ++j) 
            {
                updated_message[j] = updated_message[j + 1];
            }
            updated_message.pop_back();
            i--;
        }
    }
    cout<<endl<<"Removing any spaces : "<<updated_message<<endl;
    
    for (size_t i = 0; i < updated_message.length(); ++i) 
    {  
        if (updated_message[i] >= 'a' && updated_message[i] <= 'z') 
        {
            updated_message[i] -= 32;
        }
    }
    cout<<endl<<"capitalizing every letter : "<<updated_message<<endl;


    for (int c = 0; c < updated_message.length() - 1; c++) 
    {
        if (updated_message[c] == updated_message[c + 1] && c%2 == 0)
        {
            updated_message.insert(c + 1, "X");
        }
    }
    cout<<endl<<"adding x between the doubles in letters : "<<updated_message<<endl;
    
    if (updated_message.length() % 2 != 0) 
    {
        updated_message += 'X';
    }
    cout<<endl<<"adding x at the end in case the Message has an odd number of characters : "<<updated_message<<endl;

    char *coded = new char[updated_message.length() + 1];

    cout<<endl<<"Message to be Encrypted : "; 
    int x = 0;
    while (x < updated_message.length())
    {
        char firstChar = updated_message[x];
        char secondChar = updated_message[x + 1];
        
        int firstRow, firstCol, secondRow, secondCol;
        for (int i = 0; i < 6; i++) 
        {
            for (int j = 0; j < 6; j++) 
            {
                if (key[i][j] == firstChar) 
                {
                    firstRow = i;
                    firstCol = j;
                }
                if (key[i][j] == secondChar) 
                {
                    secondRow = i;
                    secondCol = j;
                }
            }
        }
        cout<<firstChar<<secondChar<<"\t";
    
        if (firstRow == secondRow) 
        {
            coded[x] = key[firstRow][(firstCol + 1) % 6];
            coded[x + 1] = key[secondRow][(secondCol + 1) % 6];
        }
        else if (firstCol == secondCol)
        {
            coded[x] = key[(firstRow + 1) % 6][firstCol];
            coded[x + 1] = key[(secondRow + 1) % 6][secondCol];
        } 
        else 
        {
            coded[x] = key[firstRow][secondCol];
            coded[x + 1] = key[secondRow][firstCol];
        }   
        x += 2;
    }
    cout<<endl;

    cout <<endl<< "Encrypted message: ";
    for (int i = 0; i < x; ++i)
       cout << coded[i];
    
    cout << endl;

    delete[] coded;
   
   cout<<endl<<"The playfair cipher with the input key : "<<endl;
    
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
    
   
    return 0;
}
