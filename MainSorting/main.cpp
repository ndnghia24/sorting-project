#include "mainlib.h"
#include "sortingAlgorithms.h"

void GenerateData(int a[], int n, int dataType);

int main(int argc, char* argv[]) {

    map<string, int> sortBucket = {
        {"selection-sort",1},
        {"insertion-sort",2},
        {"bubble-sort",3},
        {"heap-sort",4},
        {"merge-sort",5},
        {"quick-sort",6},
        {"radix-sort",7},
        {"shaker-sort",8},
        {"shell-sort",9},
        {"counting-sort",10},
        {"flash-sort",11}
    };

    map<int, void(*) (int*, int, unsigned long long&)> mapFunction = {
        {1,selection_sort},
        {2,insertion_sort},
        {3,bubble_sort},
        {4,heap_sort},
        {5,merge_sort},
        //this function has different parameters from others 
        //{6,quick_sort},  
        {7,radix_sort},
        {8,shaker_sort},
        {9,shell_sort},
        {10,counting_sort},
        {11,flash_sort}
    };

    map<string, int> inputOrderBucket = {
        {"-rand",1},
        {"-nsorted",2},
        {"-sorted",3},
        {"-rev",4}
    };

    map<string, int> outputBucket = {
        {"-time",1},
        {"-comp",2},
        {"-both",3}
    };

    /* ALL FUNCTION HERE BASE ON ARGUMENTS FROM COMMAND LINE CALL */
    // the number of arguments pass to cmd must be 5 or 6
    if (argc > 6 || argc < 5) {
        cout << "Invalid Input\n";
        system("pause");
        return -1;
    }

    // vector to hold the agrv value
    vector<string> argvVector;
    for (int i = 0; i < argc; i++) {
        argvVector.push_back(argv[i]);
    }

    cout << ">> ";
    for (int i = 0; i < argc; i++) {
        cout << argvVector[i] << " \n"[i == argc - 1];
    }

    cout << "\n--Time in milisecond--\n";

    if (argvVector[1].compare("-a") == 0) {
        // Algorith mode
        cout << "\nALGORITHM MODE" << endl;
        // using algorithm variable to store the sorting algorithm
        int algorithm = sortBucket[argvVector[2]];
        // checking the input
        if (algorithm == 0) {
            cout << "Sorting algorithm not found\n";
            system("pause");
            return -1;
        }

        if (argc == 5) {
            // To do
            if (IsNumber(argvVector[3])) {
                // COMMAND 3 - DONE
                // [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
                // Run a sorting algorithm on ALL data arrangements of a specified size
                // checking the input

                if (outputBucket[argvVector[4]] == 0) {
                    cout << "Output parameters not found\n";
                    system("pause");
                    return -1;
                }

                vector<pair<unsigned long long, unsigned long long>> CompareandDuration;
                int inputSize = stoi(argvVector[3]);
                int outputParams = (outputBucket[argvVector[4]]);
                
                cout << "Algorithm: " << argvVector[2] << endl;
                cout << "Input size: " << argvVector[3] << endl << endl;
                // To do generate data and loop 4 times
                // 
                //int inputSize = stoi(argvVector[3]);

                for (int i = 0; i <= 3; i++)
                {
                    int* arrayData = new int[inputSize];
                    GenerateData(arrayData, inputSize, i);
                    writeArrayData(arrayData, inputSize, "input_" + to_string(i + 1) + ".txt");

                    unsigned long long compareCount = 0;

                    {
                        auto start = chrono::high_resolution_clock::now();
                        if (algorithm == 6)
                            quick_sort(arrayData, compareCount, 0, inputSize - 1);
                        else
                            mapFunction[sortBucket[argvVector[2]]](arrayData, inputSize, compareCount);
                        auto end = chrono::high_resolution_clock::now();

                        auto time = chrono::duration_cast<chrono::microseconds>(end - start);

                        CompareandDuration.push_back(make_pair(compareCount, time.count()));
                    }

                    delete[] arrayData;

                    cout << "Input order: " << displayOrderName(i + 1) << endl;

                    cout << "--------------------------" << endl;
                    if (outputParams == 1 || outputParams == 3)
                        cout << "Running time (in millisecond): " << CompareandDuration[i].second/1000.0 << endl;
                    if (outputParams == 2 || outputParams == 3)   
                        cout << "Comparisions                 : " << CompareandDuration[i].first << endl << endl;
                }

                // To do print the result
                // WriteData(CompareandDuration, outputParams, to_string(size));
                CompareandDuration.clear();

            }
            else {
                //  COMMAND 1 - DONE
                // [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
                //  Run a sorting algorithm on the given input data
                ifstream fin(argvVector[3]);
                if (fin.fail()) {
                    cout << "File doesn't exist\n";
                    system("pause");
                    return -1;
                }
                 
                int inputSize;
                fin >> inputSize;
                int* arrayData = new int[inputSize];
                int outputParams = outputBucket[argvVector[4]];

                // if the file is not the same as the given format 
                // this program might crash
                for (int i = 0; i < inputSize; i++) {
                    fin >> arrayData[i];
                }

                cout << "Algorithm : " << argvVector[2] << endl;
                cout << "Input File: " << argvVector[3] << endl;
                cout << "Input Size: " << inputSize << endl;
                cout << "------------------------------------" << endl;

                unsigned long long compareCount = 0;

                vector<pair<unsigned long long, unsigned long long >> CompareandDuration;
                if (algorithm == 6)
                {
                    auto start = chrono::high_resolution_clock::now();
                    quick_sort(arrayData, compareCount, 0, inputSize - 1);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
                    CompareandDuration.push_back(make_pair(compareCount, time.count()));
                }
                else
                {
                    auto start = chrono::high_resolution_clock::now();
                    mapFunction[algorithm](arrayData, inputSize, compareCount);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);

                    CompareandDuration.push_back(make_pair(compareCount, time.count()));
                }

                // To do print the result
                if (outputParams == 1 || outputParams == 3)
                    cout << "Running time : " << CompareandDuration[0].second/1000.0 << endl;
                if (outputParams == 2 || outputParams == 3)   
                    cout << "Comparisions : " << CompareandDuration[0].first << endl << endl;
                cout << endl;
                writeArrayData(arrayData, inputSize, "output.txt");
            }
        }
        else {
            // COMMAND 2 - DONE
            // : [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
            // Run a sorting algorithm on the data generated automatically with specified size and order
            if (!IsNumber(argvVector[3])) {
                cout << "Input size is not a number\n";
                system("pause");
                return -1;
            }
            if (inputOrderBucket[argvVector[4]] == 0) {
                cout << "Input order input is invalid\n";
                system("pause");
                return -1;
            }
            if (outputBucket[argvVector[5]] == 0) {
                cout << "Output order input is invalid\n";
                system("pause");
                return -1;
            }

            // generate data for sorting 
            int outputParams = (outputBucket[argvVector[5]]);
            int inputOrder = (inputOrderBucket[argvVector[4]]);
            int inputSize = stoi(argvVector[3]);

            cout << "Algorithm : " << argvVector[2] << endl;
            cout << "Input size: " << inputSize << endl;
            cout << "Input order: " << argvVector[4] << endl;
            cout << "------------------------------------" << endl;

            int* arrayData = new int[inputSize];
            GenerateData(arrayData, inputSize, inputOrder - 1);
            writeArrayData(arrayData, inputSize, "input.txt");

            unsigned long long compareCount = 0;
            vector<pair<unsigned long long
                , unsigned long long
                >> CompareandDuration;

            if (algorithm == 6)
            {
                auto start = chrono::high_resolution_clock::now();
                quick_sort(arrayData, compareCount, 0, inputSize - 1);
                auto end = chrono::high_resolution_clock::now();

                auto time = chrono::duration_cast<chrono::microseconds>(end - start);

                CompareandDuration.push_back(make_pair(compareCount, time.count()));
            }
            else
            {
                auto start = chrono::high_resolution_clock::now();
                mapFunction[algorithm](arrayData, inputSize, compareCount);
                auto end = chrono::high_resolution_clock::now();

                auto time = chrono::duration_cast<chrono::microseconds>(end - start);

                CompareandDuration.push_back(make_pair(compareCount, time.count()));
            }

            // To do print the result
            if (outputParams == 1 || outputParams == 3)
                cout << "Running time : " << CompareandDuration[0].second/1000.0 << endl;
            if (outputParams == 2 || outputParams == 3)
                cout << "Comparisions : " << CompareandDuration[0].first << endl << endl;
            cout << endl;
            writeArrayData(arrayData, inputSize, "output.txt");
        }

    }
    else if (argvVector[1].compare("-c") == 0) {
        // Compare mode

        // checking the input
        if (sortBucket[argvVector[2]] == 0 || sortBucket[argvVector[3]] == 0) {
            cout << "Sorting algorithm not found\n";
            system("pause");
            return -1;
        }

        cout << "\nCOMPARE MODE" << endl;
        cout << "Algorithm: " << argvVector[2] << " | " << argvVector[3] << endl;

        if (argc == 5) {

            // COMMAND 4 - DONE
            // [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]
            // Run two sorting algorithms on the given input.
            // Checking the input
            ifstream fin(argvVector[4]);
            
            if (fin.fail()) {
                cout << "File doesn't exist\n";
                system("pause");
                return -1;
            }

            // store 2 sorting algorithm

            int algorithm[2] = {
                sortBucket[argvVector[2]],
                sortBucket[argvVector[3]]
            };

            unsigned long long compareCount;
            vector<pair<unsigned long long
                , unsigned long long
                >> CompareandDuration;

            // File processing
            int inputSize;
            fin >> inputSize;
            int* arrayData = new int[inputSize];
            for (int i = 0; i < inputSize; i++)
            {
                fin >> arrayData[i];
            }
            fin.close();
            // End file processing

            cout << "Input file: " << argvVector[4] << endl;
            cout << "Input size: " << inputSize << endl;
            cout << "--------------------------" << endl;


            for (int i = 0; i <= 1; i++) {
                    
                // clone arr from original file's array
                int* tempArr = new int[inputSize];
                for (int i = 0; i < inputSize; i++)
                {
                    tempArr[i] = arrayData[i];
                }
                                    
                compareCount = 0;

                if (algorithm[i] == 6)
                {
                    auto start = chrono::high_resolution_clock::now();
                    quick_sort(tempArr, compareCount, 0, inputSize - 1);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
                    CompareandDuration.push_back(make_pair(compareCount, time.count()));

                }
                else
                {
                    auto start = chrono::high_resolution_clock::now();
                    mapFunction[algorithm[i]](tempArr, inputSize, compareCount);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
                    CompareandDuration.push_back(make_pair(compareCount, time.count()));
                }

                delete[]tempArr;
            }
            delete[] arrayData;

            // To do print result

            cout << "Running time: " << setw(10) << CompareandDuration[0].second/1000.0 << " | " << setw(10) << CompareandDuration[1].second/1000.0 << endl;
            cout << "Comparisions: " << setw(10) << CompareandDuration[0].first << " | " << setw(10) << CompareandDuration[1].first << endl; 
            cout << endl;
        }
        else {

            // COMMAND 5 - DONE
            // [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
            //Run two sorting algorithms on the data generated automatically.
            // Checking the input 
            if (!IsNumber(argvVector[4])) {
                cout << "Input size is not a number\n";
                system("pause");
                return -1;
            }
            if (inputOrderBucket[argvVector[5]] == 0) {
                cout << "Input order input is invalid\n";
                system("pause");
                return -1;
            }

            int algorithm[2] = {
                sortBucket[argvVector[2]],
                sortBucket[argvVector[3]]
            };

            unsigned long long compareCount;
            vector<pair<unsigned long long
                , unsigned long long
                >> CompareandDuration;       

            // Genarate data
            int inputSize = stoi(argvVector[4]);
            int inputOrder = (inputOrderBucket[argvVector[5]]);

            int* arrayData = new int[inputSize];
            GenerateData(arrayData, inputSize, inputOrder - 1);
            writeArrayData(arrayData, inputSize, "input.txt");

            cout << "Input size: " << inputSize << endl;
            cout << "Input order: " << argvVector[5] << endl;
            cout << "--------------------------" << endl;

            for (int i = 0; i < 2; i++) {

                // clone arr from arrayData
                int* tempArr = new int[inputSize];
                for (int i = 0; i < inputSize; i++)
                {
                    tempArr[i] = arrayData[i];
                }                    
                    
                compareCount = 0;

                if (algorithm[i] == 6)
                {
                    auto start = chrono::high_resolution_clock::now();
                    quick_sort(tempArr, compareCount, 0, inputSize - 1);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
                    CompareandDuration.push_back(make_pair(compareCount, time.count()));

                }
                else
                {
                    auto start = chrono::high_resolution_clock::now();
                    mapFunction[algorithm[i]](tempArr, inputSize, compareCount);
                    auto end = chrono::high_resolution_clock::now();

                    auto time = chrono::duration_cast<chrono::microseconds>(end - start);
                    CompareandDuration.push_back(make_pair(compareCount, time.count()));
                }

                delete[]tempArr;
            }
            delete[] arrayData;

            // To do print result
            cout << "Running time: " << setw(10) << CompareandDuration[0].second/1000.0 << " | " << setw(10) << CompareandDuration[1].second/1000.0 << endl;
            cout << "Comparisions: " << setw(10) << CompareandDuration[0].first  << " | " << setw(10) << CompareandDuration[1].first << endl;
            cout << endl;
        }

    }
    else {
    cout << "Invalid Input\n";
        system("pause");
        return -1;
    }

    system("pause");
    return 1;
}