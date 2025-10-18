#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <vector>


#include "BinSearchTree.hpp"
#include "PriorityQueue.hpp"
#include "Scanner.hpp"
#include "utils.hpp"


int main(int argc, char *argv[]) {

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }

    const std::string dirName = std::string("input_output");
    const std::string inputFileName = std::string(argv[1]);
    const std::string inputFileBaseName = baseNameWithoutTxt(inputFileName);

    // build the path to the .tokens output file.
    const std::string wordTokensFileName = dirName + "/" + inputFileBaseName + ".tokens";
    const std::string wordFreqFileName = dirName + "/" + inputFileBaseName + ".freq";


    // The next several if-statement make sure that the input file, the directory exist
    // and that the output file is writeable.
     if( error_type status; (status = regularFileExistsAndIsAvailable(inputFileName)) != NO_ERROR )
        exitOnError(status, inputFileName);


    if (error_type status; (status = directoryExists(dirName)) != NO_ERROR )
        exitOnError(status, dirName);

    if (error_type status; (status = canOpenForWriting(wordTokensFileName)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);


    std::vector<std::string> words;
    namespace fs = std::filesystem;
    fs::path tokensFilePath(wordTokensFileName); // create a file system path using the output file.

    auto fileToWords = Scanner(inputFileName);
    if( error_type status; (status = fileToWords.tokenize(words)) != NO_ERROR)
	    exitOnError(status, inputFileName);

    if (error_type status; (status = writeVectorToFile(wordTokensFileName, words)) != NO_ERROR)
        exitOnError(status, wordTokensFileName);

    BinSearchTree bst;
    bst.bulkInsert(words);

    std::vector<std::pair<std::string, int >> wordCounts;
    bst.inorderCollect(wordCounts);

    int totalTokens = words.size();
    int uniqueWords = wordCounts.size();
    unsigned height = bst.height();
    int minfreq, maxfreq = 0;

    if (uniqueWords > 0) {
        minfreq = wordCounts.at(0).second;
        maxfreq = wordCounts.at(0).second;
        for (int i = 0; i < wordCounts.size(); i++) {
            if (wordCounts.at(i).second < minfreq)
                minfreq = wordCounts.at(i).second;
            if (wordCounts.at(i).second > maxfreq)
                maxfreq = wordCounts.at(i).second;
        }
    }

    std::cout << "BST height: " << height << "\n";
    std::cout << "BST unique words: " << uniqueWords << "\n";
    std::cout << "Total tokens: " << totalTokens << "\n";
    std::cout << "Min frequency: " << minfreq << "\n";
    std::cout << "Max frequency: " << maxfreq << "\n";

    std::vector<TreeNode*> nodes;
    for (int i = 0; i < wordCounts.size(); i++) {
        TreeNode* node = new  TreeNode(wordCounts.at(i).first);
        node->setCount(wordCounts.at(i).second);
        nodes.push_back(node);
    }
    PriorityQueue priority_queue(nodes);

    std::ofstream freqFile(wordFreqFileName);
    if (!freqFile)
        std::cout << "Error writing to " << wordFreqFileName << "\n";

    for (int i = 0; i < priority_queue.size(); i++) {
        TreeNode* node = nodes.at(i);
        freqFile << node->value() << " " << node->getCount() << "\n";
    }

    freqFile.close();



    return 0;
}
