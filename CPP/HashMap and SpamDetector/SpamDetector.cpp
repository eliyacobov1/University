#include <algorithm>
#include "HashMap.hpp"

char const COMA = ',';
string const spamIndication = "SPAM", nonSpamIndication = "NOT_SPAM",
argsError = "Usage: SpamDetector <database path>"
                         " <message path> <threshold>\n";

/**
 * Function that reads the database of a SpamDetector
 * and writes the data into the given HashMap
 * @param filePath The path to the Database file
 * @param errorIndicator if the file is corrupted,
 * will be set to ERROR_FAILURE error code
 * @param hashMap The given HashMap object which
 * the spam data is written to
 */
static void readDatabase(string filePath, int& errorIndicator, HashMap<string, int>& hashMap)
{
    ifstream myFile;
    myFile.open(filePath);

    //in case the program can't open the file
    if(!myFile.is_open())
    {
        errorIndicator = EXIT_FAILURE;
        return;
    }

    string csvLine;
    int elementCounter;

    //iterate through each line in the file
    while(getline(myFile, csvLine))
    {
        //if line starts with a coma, file is corrupted
        if(csvLine[0] == ',')
        {
            myFile.close();
            errorIndicator = EXIT_FAILURE;
            return;
        }

        //ignore the newline character at the end of the line
        if(csvLine[csvLine.length() - 1] == '\r' ||
           csvLine[csvLine.length() - 1] == '\n')
        {
            csvLine = csvLine.substr(0, csvLine.size()-1);
        }

        istringstream csvStream(csvLine);
        string csvElement;
        elementCounter = 0;

        string badCombo;
        int score = 0;

        //iterate through the values of the line (between the comas)
        while(getline(csvStream, csvElement, COMA))
        {
            elementCounter++;

            //if value contains more than on char, it is not
            //a single digit number and hence not a valid value.
            //also checks that there are no more than 2 elements
            //in a single line
            if(elementCounter > 2)
            {
                myFile.close();
                errorIndicator = EXIT_FAILURE;
                return;
            }

            if(elementCounter == 1)
            {
                badCombo = csvElement;
                //convert string to lower case letters
                transform(badCombo.begin(), badCombo.end(),
                        badCombo.begin(), ::tolower);
            }

            if(elementCounter == 2)
            {
                try
                {
                    score = std::stoi(csvElement);
                }
                //since invalid_argument and out_of_range can be thrown,
                //catch attempt is with the generic std::exception type
                catch (std::exception& e)
                {
                    myFile.close();
                    errorIndicator = EXIT_FAILURE;
                    return;
                }
            }
        }
        //in case the line holds less then two
        // values or of a negative score value
        if(elementCounter < 2 || score < 0)
        {
            myFile.close();
            errorIndicator = EXIT_FAILURE;
            return;
        }
        hashMap.insert(badCombo, score);
    }
myFile.close();
}

/**
 * Function to convert file's contents to a string variable
 * @param filePath The path of the file
 * @param errorIndicator Is set to EXIT_FAILURE code if file
 * can't be opened for whatever reason
 * @return String representation of the file's contents
 */
static string fileToString(string filePath, int& errorIndicator)
{
    ifstream myFile;
    myFile.open(filePath);

    //in case the program can't open the file
    if(!myFile.is_open())
    {
        errorIndicator = EXIT_FAILURE;
        return "";
    }

    string fileContent = "";
    string csvLine;

    //iterate through each line in the file
    while(getline(myFile, csvLine))
    {
        //replace newline characters with regular whitespace
        if(csvLine[csvLine.length() - 1] == '\n' ||
           csvLine[csvLine.length() - 1] == '\r')
        {
            csvLine[csvLine.length() - 1] = ' ';
        }

        //convert line string to lower case letters
        transform(csvLine.begin(), csvLine.end(),
                  csvLine.begin(), ::tolower);

        fileContent += csvLine;
    }
    myFile.close();
    return fileContent;
}

/**
 * The main program. Receives the paths of a Database file
 * , a text file and also a threshold that is represented by
 * an integer. The program will calculate the spam score for
 * the text according to the values given in the database and
 * their individual scores. The program will then output an informative
 * message indicating whether the  text file is considered as spam or not.
 */
int main(int argc, char *argv[])
{
    //in case of wrong argument
    //number sent to the program
    if(argc != 4)
    {
        cerr << argsError;
        return EXIT_FAILURE;
    }

    int threshold = 0;

    //in case threshold is not an integer, error is returned
    try
    {
        threshold = std::stoi(argv[3]);
    }
    //since invalid_argument and out_of_range can be thrown,
    //catch attempt is with the generic std::exception type
    catch (std::exception& e)
    {
        cerr << invalidError;
        return EXIT_FAILURE;
    }

    //in case threshold is non-positive
    if (threshold <= 0)
    {
        cerr << invalidError;
        return EXIT_FAILURE;
    }

    HashMap<string, int> Database;
    int errorIndicator = EXIT_SUCCESS;

    readDatabase(argv[1], errorIndicator, Database);

    //in case DB file is corrupted
    if(errorIndicator == EXIT_FAILURE)
    {
        cerr << invalidError;
        return EXIT_FAILURE;
    }
    //get the file's content as a string
    errorIndicator = EXIT_SUCCESS;
    string fileContent = fileToString(argv[2], errorIndicator);

    //in case the file could not be opened
    if(errorIndicator == EXIT_FAILURE)
    {
        cerr << invalidError;
        return EXIT_FAILURE;
    }

    int totalScore = 0;

    for(pair<string, int> badCombo : Database)
    {
        //for each bad combination, find the number of times
        //that it is present in the text increase the total
        //bad points by the corresponding amount
        int numberAppearances = 0;
        string ::size_type pos = 0;
        while((pos = fileContent.find(badCombo.first, pos))
              != string::npos)
        {
            numberAppearances++;
            pos += badCombo.first.size();
        }

        totalScore += numberAppearances * badCombo.second;
    }

    //print the appropriate message according to the findings
    if(totalScore >= threshold)
    {
        cout << spamIndication << std::endl;
    }
    else
    {
        cout << nonSpamIndication << std::endl;
    }

    return EXIT_SUCCESS;
}