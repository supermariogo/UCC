//! Utility class static methods.
/*!
 * \file CUtil.cpp
 *
 * This file contains the utility class static methods.
 */

#include "CUtil.h"
#include <algorithm>
#include <string.h>
#include <cstring>
#include <time.h>
#include <sstream>

#ifdef UNIX
#include <dirent.h>
#include <sys/stat.h>
#else
#include <direct.h>
#include <io.h>
#endif

/*!
 * Returns a string without leading/trailing spaces or tabs.
 *
 * \param str original string
 * \param mode trim mode (-1=left, 0=both, 1=right)
 *
 * \return trimmed string
 */
string CUtil::TrimString(const string &str, int mode)
{
    size_t idx;
    string str1 = str;
    if (mode <= 0)
    {
        idx = str1.find_first_not_of(" \t\n\r\f");
        if (idx != string::npos)
            str1 = str1.substr(idx);
        else
            str1 = "";
    }
    if (mode >= 0)
    {
        idx = str1.find_last_not_of(" \t\n\r\f");
        if (idx != string::npos)
            str1 = str1.substr(0, idx + 1);
        else
            str1 = "";
    }
    return str1;
}

/*!
 * Erases all strings specified by erasedstr in srcstr.
 *
 * \param srcstr original string
 * \param erasedstr substring to be erased
 *
 * \return modified string
 */
string CUtil::EraseString(const string &srcstr, const string &erasedstr)
{
    size_t idx = 0;
    string srcstr1 = srcstr;
    while ((idx = srcstr1.find(erasedstr, idx)) != string::npos)
    {
        srcstr1.erase(idx, erasedstr.length());
    }
    return srcstr1;
}

/*!
 * Returns a string in lower case.
 *
 * \param string_to_lower original string
 *
 * \return lower case string
 */
string CUtil::ToLower(const string &string_to_lower)
{
    string string_to_lower1 = string_to_lower;
    for (size_t i = 0; i < string_to_lower1.size(); i++)
    {
        string_to_lower1[i] = tolower(string_to_lower1[i]);
    }
    return string_to_lower1;
}

/*!
 * Checks whether the string passed is blank.
 *
 * \param str original string
 *
 * \return blank string?
 */
bool CUtil::CheckBlank(const string &str)
{
    string::size_type idx;
    idx = str.find_first_not_of("\n\t\r\f ");	// searches for chars other than specified
    if (idx != string::npos)
        return false;
    else
        return true;
}

/*!
 * Checks whether the string passed is an integer.
 *
 * \param str original string
 *
 * \return integer string?
 */
bool CUtil::IsInteger(const string &str)
{
    string str1 = TrimString(str);
    if (str1.find_first_not_of("0123456789") != string::npos)
        return false;
    else
        return true;
}

/*!
 * Finds the first appearance of each element of table's first value.
 *
 * \param target string
 * \param table map table
 * \param pos position of string
 * \param preLang previous language (for web languages)
 *
 * \return second value of the map
 */
size_t CUtil::FindStringsCaseInsensitive(const string &target, map<string, int> &table, size_t &pos, size_t preLang)
{
    string target1 = ToLower(target);
    size_t tmp_pos;
    pos = string::npos;
    size_t ret = INVALID_POSITION;
    for (map<string, int>::iterator iter = table.begin(); iter != table.end(); iter++)
    {
        tmp_pos = target1.find(iter->first);
        if (tmp_pos != string::npos && (pos == string::npos || pos > tmp_pos))
        {
            // handle special case "width=100%>"
            ret = iter->second;
            if ((ret == WEB_ASP_JSP_END && preLang != WEB_ASP_JSP_START) ||
                (ret == WEB_PHP_END && (preLang != WEB_PHP_START && preLang != WEB_PHP_START2)))
                ret = INVALID_POSITION;
            pos = tmp_pos;
        }
    }
    return ret;
}

/*!
 * Finds the position of the "target" char in "source" string.
 * Starting from "start_idx" but ignoring escape chars,
 * for example, '\n' is different from 'n' in "this is not nothing"
 *
 * \param source source string
 * \param target target character
 * \param start_idx index to start search
 * \param escape escape character to ignore
 *
 * \return position of target character
 */
size_t CUtil::FindCharAvoidEscape(const string &source, char target, size_t start_idx, char escape)
{
    size_t idx, i;
    if (start_idx >= source.length())
        return string::npos;
    idx = start_idx;
    while (idx < source.length())
    {
        idx = source.find(target, idx);
        if (idx == string::npos)
            return idx;

        for (i = 1; i <= idx; i ++)
        {
            // trace back to the previous char ex. "adfd\\\\"
            if (source[idx - i] != escape) break;
        }
        if (i % 2 != 0)
        {
            // case \\", avoid case something\"
            break;
        }
        idx++;
    }
    if (idx >= source.length())
        return string::npos;
    return idx;
}

/*!
 * Finds the keyword in the string starting from start to end.
 *
 * \param str string
 * \param keyword keyword to find
 * \param start starting index for search
 * \param end ending index for search
 * \param case_sensitive is case sensitive?
 *
 * \return index of keyword in string
 */
size_t CUtil::FindKeyword(const string &str, const string &keyword, size_t start, size_t end, bool case_sensitive)
{
#define SPECIAL_CHARS	" \t;[]()+/-*<>=,&~!^?:%{}|"
    size_t kw_length = keyword.length();
    size_t idx, i = start;
    string str1 = str;
    string keyword1 = keyword;
    if (end == TO_END_OF_STRING)
        end = str1.length() - 1;	// inclusive

    if (!case_sensitive)
    {
        str1 = CUtil::ToLower(str1);
        keyword1 = CUtil::ToLower(keyword1);
    }

    while (i <= end)
    {
        idx = str1.find(keyword1, i);
        if (idx != string::npos && idx + kw_length - 1 <= end)
        {
            if ((idx == 0 || strchr(SPECIAL_CHARS, str1[idx - 1]) != NULL) &&
                (idx + kw_length >= str1.length() ||
                 strchr(SPECIAL_CHARS, str1[idx + kw_length]) != NULL))
            {
                // the keyword stands alone or surrounded by special chars
                return idx;
            }
        }
        else
        {
            // cannot find the keyword in str
            break;
        }
        i = idx + 1;	// keyword found but not stands alone nor surrounded by special chars
    }

    return string::npos;	//not found
#undef SPECIAL_CHARS
}

/*!
 * Counts keywords in string.
 *
 * \param base string to search
 * \param container set of keywords
 * \param count number of keywords found
 * \param mode allowable leading/trailing character mode (1=exclude keywords surrounded by exclude characters, 2=include only keywords preceded by include1 characters and followed by include2 characters)
 * \param exclude list of characters that may not surround keywords found (if mode=1)
 * \param include1 list of characters that must precede keywords found (if mode=2)
 * \param include2 list of characters that must follow keywords found (if mode=2)
 * \param counter_container stores list of individual keyword counts (if specified)
 * \param case_sensitive language is case sensitive?
 */
void CUtil::CountTally(const string &base, StringVector &container, unsigned int &count, int mode, const string &exclude,
                       const string &include1, const string &include2, UIntVector* counter_container, bool case_sensitive)
{
    string::size_type idx;
    string base1;
    StringVector::iterator vit;
    UIntVector::iterator cit;
    unsigned int single_count = 0;
    base1 = " " + base + " ";

    if (counter_container)
        cit = counter_container->begin();

    if (case_sensitive == false)
    {
        base1 = CUtil::ToLower(base1);
        for (vit = container.begin(); vit != container.end(); vit++)
            (*vit) = CUtil::ToLower((*vit));
    }

    if (mode == 1)
    {
        // exclude mode
        for (vit = container.begin(); vit != container.end(); vit++)
        {
            idx = base1.find((*vit));
            while (idx != string::npos)
            {
                if ((exclude.find(base1[idx+((*vit).size())]) == string::npos) &&
                    (exclude.find(base1[idx-1]) == string::npos))
                {
                    count++;
                    single_count++;
                }
                idx = base1.find((*vit), idx + ((*vit).size()));
            }
            if (counter_container)
            {
                (*cit) += single_count;
                single_count = 0;
                cit++;
            }
        }
    }
    else if (mode == 2)
    {
        // include mode
        for (vit = container.begin(); vit != container.end(); vit++)
        {
            idx = base1.find((*vit));
            while (idx != string::npos)
            {
                if ((include1.find(base1[idx-1]) != string::npos) &&
                    (include2.find(base1[idx+((*vit).size())]) != string::npos))
                    count++;
                idx = base1.find((*vit), idx + ((*vit).size()));
            }
        }
    }
}

/*!
 * Extracts the filename (without path) from the filepath.
 * ex. abc\xyz.cpp --> xyz.cpp
 *
 * \param filepath file path
 *
 * \return file name
 */
string CUtil::ExtractFilename(const string &filepath)
{
    string filename = filepath;
    size_t idx = filename.find_last_of("\\");
    if (idx == string::npos)
        idx = filename.find_last_of("/");	// Unix
    if (idx != string::npos)
        return filename.substr(idx + 1);
    return filename;
}

/*!
 * For a given directory name, extract all the files from that directory as well as
 * from all its sub-directories and store the filenames in the fileList vector.
 *
 * \param folder folder to list
 * \param fileExtList list of file extensions to search
 * \param fileList list of files in folder
 * \param symLinks follow Unix links?
 *
 * \return path exists and is a directory
 */
bool CUtil::ListAllFiles(string &folder, StringVector &fileExtList, StringVector &fileList, bool symLinks)
{
    StringVector tmpList;
    string file;
    size_t i, n;

    folder = CUtil::TrimString(folder);

#ifdef UNIX
    // skip links if user specified
    struct stat inodeData;
    if (!symLinks && (lstat(folder.c_str(), &inodeData) < 0 || S_ISLNK(inodeData.st_mode)))
        return(false);
#endif

    // process folder
    if (!GetFileList(tmpList, folder, symLinks))
        return(false);

    // read through tmpList and get the names of all the files in the directory mentioned
    for (n = 0; n < tmpList.size(); n++)
    {
        file = tmpList.at(n);

        // if no-extension filtering, each file is pushed into the fileList
        if (fileExtList.at(0) == "*.*" || fileExtList.at(0) == "*")
            fileList.push_back(file);
        else
        {
            // for each extension, if file extension matches with the extension, the file is pushed into the fileList
            for (i = 0; i < fileExtList.size(); i++)
            {
                if (MatchFilename(ExtractFilename(file), fileExtList.at(i)))
                    fileList.push_back(file);
            }
        }
    }
    tmpList.clear();
    return(true);
}

/*!
 * For a given path, this method lists all files, directories and
 * sub-directories it contains and stores the filenames in the fileList vector.
 *
 * \param fileList list of files in folder
 * \param path folder's path to list
 * \param symLinks follow Unix links?
 *
 * \return path exists and is a directory
 */
bool CUtil::GetFileList(StringVector &fileList, const string &path, bool symLinks)
{
    string fullPath;
#ifdef UNIX
    DIR *dir;
    struct dirent *fileRead;
    struct stat inodeData;

    // opening the given path
    dir = opendir(path.c_str());

    // If the dir doesn't exist
    if (dir == NULL)
        return(false);

    // each file is processed until the last one
    while ((fileRead = readdir(dir)) != NULL)
    {
        // '.' & '..' are omitted
        if ((strcmp(fileRead->d_name, ".") != 0) && (strcmp(fileRead->d_name, "..") != 0))
        {
            // fullPath contains the path + the file name.
            fullPath = path + '/' + fileRead->d_name;
            if (symLinks)
            {
                if (stat(fullPath.c_str(), &inodeData) >= 0)
                {
                    // for each file, store the fullPath into the ofstream
                    if (!S_ISDIR(inodeData.st_mode))
                        fileList.push_back(fullPath);
                    else
                    {
                        // for each directory, its file list is obtained
                        GetFileList(fileList, fullPath, symLinks);
                    }
                }
            }
            else
            {
                if (lstat(fullPath.c_str(), &inodeData) >= 0)
                {
                    // for each file, store the fullPath into the ofstream
                    if (!S_ISLNK(inodeData.st_mode))
                    {
                        if (!S_ISDIR(inodeData.st_mode))
                            fileList.push_back(fullPath);
                        else
                        {
                            // for each directory, its file list is obtained
                            GetFileList(fileList, fullPath, symLinks);
                        }
                    }
                }
            }
        }
    }
    // close the directory
    closedir(dir);
#else
    struct _finddata_t c_file;
    ptrdiff_t hFile;
    string findPath = path + "\\*.*";

    // the first file is obtained
    hFile = _findfirst(findPath.c_str(), &c_file);

    // If the dir doesn't exist
    if (hFile == -1)
        return(false);

    // each file is processed until the last one
    while (_findnext(hFile, &c_file) == 0)
    {
        // for each file (not a directory (_A_SUBDIR), store its name into the fileList
        fullPath = path + "\\" + c_file.name;
        if (!(c_file.attrib & _A_SUBDIR))
            fileList.push_back(fullPath);
        else if ((strcmp(".", c_file.name) != 0) && (strcmp("..", c_file.name) != 0))
        {
            // for each directory, except '.' and '..', its file list is obtained
            GetFileList(fileList, fullPath, symLinks);
        }
    }
    // close the directory
    _findclose(hFile);
#endif
    return(true);
}

/*!
 * For a given filename, this method checks whether the file matches
 * a given match string containing wildcards (*) and placeholders (?).
 *
 * \param filename filename to be checked
 * \param matchstr string pattern to match
 *
 * \return filename matches pattern
 */
bool CUtil::MatchFilename(const string &filename, const string &matchstr)
{
    int i, j, k, f, m, fl, ml, s, e, sl, lim;

    fl = (int)filename.length();
    ml = (int)matchstr.length();
    if (ml == 0)
        return(fl == 0);
    if (fl == 0)
        return(false);

    f = 0;
    for (m = 0; m < ml; m++)
    {
        if (matchstr[m] == '?')
        {
            f++;
            if (f > fl)
                return(false);
            continue;
        }
        else if (matchstr[m] == '*')
        {
            // search for next non-wild card character
            s = m + 1;
            while (s < ml && matchstr[s] == '*')
                s++;
            if (s >= ml)
                break;
            e = s + 1;
            while (e < ml && matchstr[e] != '*')
                e++;
            sl = e - s;
            lim = fl - sl - f;
            if (e >= ml)
            {
                // check the end of the filename
                if (fl - f < sl)
                    return(false);
                for (j = fl - sl, k = s; j < fl; j++, k++)
                {
                    if (matchstr[k] != '?')
                    {
#ifdef UNIX
                        // case-sensitive match
                        if (matchstr[k] != filename[j])
                            break;
#else
                        // case-insensitive match
                        if (tolower(matchstr[k]) != tolower(filename[j]))
                            break;
#endif
                    }
                }
                return(j >= fl);
            }
            for (i = 0; i <= lim; i++)
            {
                for (j = f + i, k = s; j < f + i + sl; j++, k++)
                {
                    if (matchstr[k] != '?')
                    {
#ifdef UNIX
                        // case-sensitive match
                        if (matchstr[k] != filename[j])
                            break;
#else
                        // case-insensitive match
                        if (tolower(matchstr[k]) != tolower(filename[j]))
                            break;
#endif
                    }
                }
                if (j >= f + i + sl)
                {
                    f += i + sl;
                    break;
                }
            }
            if (i > lim)
                return(false);
            m = e - 1;
            continue;
        }
#ifdef UNIX
        // case-sensitive match
        if (matchstr[m] != filename[f])
            return(false);
#else
        // case-insensitive match
        if (tolower(matchstr[m]) != tolower(filename[f]))
            return(false);
#endif
        f++;
    }
    if (f < fl && matchstr[ml - 1] != '*')
        return(false);
    return(true);
}

/*!
 * For a given path, this method creates the specified directory path
 * including all required sub-directories.
 *
 * \param path path to create
 *
 * \return file status
 */
int CUtil::MkPath(const string &path)
{
    size_t i = 1;
    string tpath;
#ifdef UNIX
    struct stat st;
    if (stat(path.c_str(), &st) != 0)
    {
        while (i < path.size())
        {
            if (path[i] == '/')
            {
                tpath = path.substr(0, i);
                if (stat(tpath.c_str(), &st) != 0)
                {
                    if (mkdir(tpath.c_str(), 0777) != 0)
                        return 0;
                }
            }
            i++;
        }
        if (mkdir(path.c_str(), 0777) != 0)
            return 0;
    }
    string tempfile = path + "/___temp.dat";
#else
    if (_access(path.c_str(), 0) != 0)
    {
        while (i < path.size())
        {
            if ((path[i] == '\\' || path[i] == '/') && path[i-1] != ':')
            {
                tpath = path.substr(0, i);
                if (_access(tpath.c_str(), 0) != 0)
                {
                    if (_mkdir(tpath.c_str()) != 0)
                        return 0;
                }
            }
            i++;
        }
        if (_mkdir(path.c_str()) != 0)
            return 0;
    }
    string tempfile = path + "\\___temp.dat";
#endif

    // attempt to write a temporary file to the directory
    ofstream outfile;
    outfile.open(tempfile.c_str(), ofstream::out);
    outfile.close();
    if (outfile.fail())
    {
        // file could not be opened
        return 0;
    }
    else
    {
        // delete the temporary file
        remove(tempfile.c_str());
    }
    return 1;
}

/*!
 * Prints the standardized file header for all output files.
 *
 * \param pout output file stream
 * \param title custom title
 * \param cmd current command line string
 *
 * \return file status
 */
int CUtil::PrintFileHeader(ofstream &pout, const string &title, const string &cmd)
{
    string myOutput;
    time_t myTime;
    struct tm *myLocalTime;
    time(&myTime);
#if defined UNIX || defined MINGW
    myLocalTime = localtime(&myTime);
#else
    struct tm myLT;
    localtime_s(&myLT, &myTime);
    myLocalTime = &myLT;
#endif

    myOutput = "USC Unified CodeCount (UCC)";
    PrintFileHeaderLine(pout, myOutput);

    myOutput = "(c) Copyright 1998 - 2013 University of Southern California";
    PrintFileHeaderLine(pout, myOutput);
    pout << endl;

    myOutput = title;
    PrintFileHeaderLine(pout, myOutput);

    ostringstream s0;
    s0 << "Generated by UCC v." << PRODUCT_REVISION << " on " << myLocalTime->tm_mon + 1
    << " " << myLocalTime->tm_mday << " " << myLocalTime->tm_year + 1900;
    myOutput = s0.str();
    PrintFileHeaderLine(pout, myOutput);

    // print command line if given
    if (cmd.length() > 0)
    {
        myOutput = cmd;
        PrintFileHeaderLine(pout, myOutput);
    }
    pout << endl;

    return 1;
}

/*!
 * Prints a standardized file header header line.
 *
 * \param pout output file stream
 * \param line custom line
 *
 * \return file status
 */
int CUtil::PrintFileHeaderLine(ofstream &pout, const string &line)
{
    size_t i, mysize, lineLength = 100;
    string myOutput = line;

    mysize = myOutput.length();
    if (lineLength > mysize)
    {
        for (i = 0; i < (lineLength - mysize) / 2; i++)
        {
            myOutput.insert(0, " ");
            myOutput.append(" ");
        }
    }
    pout << myOutput << endl;

    return 1;
}

/*!
 * Removes extra text added after @@ by ClearCase.
 * The original implementation was provided by NGC.
 *
 * \param fileName file name
 *
 * \return modified file name
 */
string CUtil::ConvertClearCaseFile(const string &fileName)
{
    // remove @@ and anything after
    string fileName1 = fileName;
    size_t loc = fileName1.rfind("@@");
    if (loc == string::npos)
        return fileName1;
    else
        return fileName1.erase(loc);
}

/*!
 * Checks for line truncation.
 *
 * \param length length of current line
 * \param totalLength length of current SLOC
 * \param truncate allowable number of characters per SLOC
 * \param trunc_flag line truncated?
 *
 * \return size of string to keep after truncation
 */
size_t CUtil::TruncateLine(size_t length, size_t totalLength, size_t truncate, bool &trunc_flag)
{
    if (truncate == 0)
    {
        trunc_flag = false;
        return(length);
    }
    else if (totalLength >= truncate)
    {
        trunc_flag = true;
        return(0);
    }
    else if (totalLength + length <= truncate)
    {
        trunc_flag = false;
        return(length);
    }
    else
    {
        trunc_flag = true;
        return(truncate - totalLength);
    }
}

/*!
 * Clear redundant/unnecessary white spaces in a string.
 *
 * \param str string to be processed
 *
 * \return new string
 */
string CUtil::ClearRedundantSpaces(const string &str)
{
#define SPECIAL_CHARS " \t;[]()+/-*<>=,&~!^?:%{}|"
    size_t len = str.length();
    size_t idx = 0;
    size_t idx_new = 0;
    string str_new(len, '\0');

    for (idx = 0; idx < len; idx++)
    {
        if (str[idx] == ' ' || str[idx] == '\t')
        {
            if (idx == 0 || idx + 1 == len
                || strchr(SPECIAL_CHARS, str[idx - 1]) != NULL
                || strchr(SPECIAL_CHARS, str[idx + 1]) != NULL)
            {
                continue;
            }
        }
        if (str[idx] == '\t')
            str_new[idx_new++] = ' ';
        else
            str_new[idx_new++] = str[idx];
    }
    str_new.resize(idx_new);

    return str_new;
#undef SPECIAL_CHARS
}

/*!
 * Returns a string without smart quotes.
 *
 * \param str original string
 *
 * \return updated string
 */
string CUtil::ReplaceSmartQuotes(const string &str)
{
    string str1 = str;
    std::replace(str1.begin(), str1.end(), char(145), '\'');
    std::replace(str1.begin(), str1.end(), char(146), '\'');
    std::replace(str1.begin(), str1.end(), char(147), '\"');
    std::replace(str1.begin(), str1.end(), char(148), '\"');
    return str1;
}

int CUtil::CountNestedNum(string &combine){
    //"a==1&&b==1 return 2"
    int res=0;
    for(int i=0;i<combine.size();i++){
        if(combine[i]=='&')
            res++;
    }
    return res/2+1;
}

size_t CUtil::ConcatAndDup(string &cc4_valid_if, set<string> &nested_set){
    set<string>::iterator it;
    string temp;
    if(nested_set.count(cc4_valid_if) == 1){
        return CountNestedNum(cc4_valid_if);
    }

    for(it=nested_set.begin(); it!=nested_set.end(); it++){
        temp= *it;
        if(temp.find(cc4_valid_if)!= string::npos)
            return CountNestedNum(cc4_valid_if);
        if(cc4_valid_if.find(temp)!=string::npos)
            return CountNestedNum(temp);
    }

    return 0;
}

size_t CUtil::ConcatOrDup(set<string> &string_set){

    set<string>::iterator it;
    string temp;

    return 0;
}


size_t CUtil::NestedIfDup(string &cc4_valid_if, stack<string> &cc4_parent_stack, stack<set<string> > &cyclomatic_distinct_cond_stack, set<string> &nested_set){


    //cc4_valid_if && cc4_parent_stack.top()
    set<string> temp_set = cyclomatic_distinct_cond_stack.top();
    set<string>::iterator it;
    string parent = cc4_parent_stack.top();
    size_t dup_counter=0;

    if(cyclomatic_distinct_cond_stack.size()==1){
        string combine = parent + "&&" + cc4_valid_if;

        if(nested_set.find(combine)!=nested_set.end()){
            cout << "CC4 DEBUG: already counted the dup" << endl;
            return 0;

        }
        nested_set.insert(combine);
        cout << "CC4 DEBUG: insest " << combine << " to nested_set"<<endl;
        if(temp_set.find(combine)!=temp_set.end()){
            //can find a && dup, counter && number
            return CountNestedNum(combine);
        }
        return 0;


    }

    cyclomatic_distinct_cond_stack.pop();
    cc4_parent_stack.pop();
    string new_cc4_valid_if = parent+"&&"+cc4_valid_if;
    dup_counter = NestedIfDup(new_cc4_valid_if, cc4_parent_stack, cyclomatic_distinct_cond_stack, nested_set);
    cyclomatic_distinct_cond_stack.push(temp_set);
    cc4_parent_stack.push(parent);

    return dup_counter;
}


//CUtil::CountDistinctCond(line, cmplx_cyclomatic_list,cyclomatic_repeated_cond_cnt , 1, exclude, "", "", cyclomatic_distinct_cond_set, 0, casesensitive);

/*
(flag == 1)
(flag == true)
(flag)
(flag==true)
Shoule be same
*/

void CUtil::SemanticFormat(string &statement)
{
    size_t idx;
    string left;
    string right;
    string eq = "==", ne = "!=", eqT = "==1", eqF = "==0", concat_op_and = "&&", concat_op_or="||";

    int eq_len = eq.length();
    int ne_len = ne.length();
    int eq_pos = -1, ne_pos = -1;
    int tnum_len = string("1").length();
    int tstr_len = string("true").length();
    int fnum_len = string("0").length();
    int fstr_len = string("false").length();

    statement.erase(remove_if(statement.begin(), statement.end(), ::isspace), statement.end());

    // For loop handling: Currently "for" keyword is searched and upon encounter, is stripped from the statement
    // and the rest of the statement is recorded as a condition. We need to record specific condition within a
    // for loop, not the entire statement.
    if(statement.find(";", 0) != string::npos) {
    	int firstSC = statement.find(";", 0);
    	if(statement.find(";", firstSC + 1) != string::npos) {
    		int secondSC = statement.find(";", firstSC + 1);
    		if(firstSC != secondSC + 1) {
    			string condFOR = statement.substr(firstSC + 1, secondSC - firstSC - 1);
    			//distinct_cond_set.erase(it);
    			//it = distinct_cond_set.find(temp);
    			statement = condFOR;
    			//distinct_cond_set.insert(condFOR);
    		}
    	}
    }

    if(statement.find(concat_op_and) == string::npos && statement.find(concat_op_or) == string::npos){

        if(statement[0]=='!'){
            eq_pos = statement.find(eq);
            ne_pos = statement.find(ne);
            if(eq_pos != string::npos) {
                if(statement.substr(eq_pos + eq_len, tnum_len) == "1" || statement.substr(eq_pos + eq_len, tstr_len) == "true") {
                    statement = statement.substr(1, string::npos) += eqF;
                } else if(statement.substr(eq_pos + eq_len, fnum_len) == "0" || statement.substr(eq_pos + eq_len, fstr_len) == "false") {
                    statement = statement.substr(1, string::npos) += eqT;
                }
            } else if(ne_pos != string::npos) {
                if(statement.substr(ne_pos + ne_len, tnum_len) == "1" || statement.substr(ne_pos + ne_len, tstr_len) == "true") {
                    statement = statement.substr(1, string::npos) += eqT;
                } else if(statement.substr(ne_pos + ne_len, fnum_len) == "0" || statement.substr(ne_pos + ne_len, fstr_len) == "false") {
                    statement = statement.substr(1, string::npos) += eqF;
                }
            } else {
                statement = statement.substr(1, string::npos) += eqF;
            }
            return;
        }

        if (statement.find(eq) == string::npos && statement.find(ne) == string::npos){
            statement = statement + eqT;
            return ;
        }

        idx = statement.find(eq);
        if (idx != string::npos){

            left = statement.substr(0, idx);
            right = statement.substr(idx + eq_len, string::npos);

            if(left=="true" || left=="1") {
                statement = right + eqT;
            } else if(right=="true" || right=="1") {
                statement = left + eqT;
            }
            if(left=="false" || left=="0") {
                statement = right + eqF;
            } else if(right=="false" || right=="0"){
                statement = left + eqF;
            }
            return;
        }

        idx = statement.find(ne);
        if (idx != string::npos){

            left = statement.substr(0, idx);
            right = statement.substr(idx + ne_len, string::npos);

            if(left=="true" || left=="1") {
                statement = right + eqF;
            } else if (right=="true" || right=="1") {
                statement = left + eqF;
            }
            if(left=="false" || left=="0") {
                statement = right + eqT;
            } else if (right=="false" || right=="0"){
                statement = left + eqT;
            }
            return;
        }

    }else{
        // for &&
        if(statement.find(concat_op_and) != string::npos){
            string temp_statement = statement;
            statement = "";
            while(temp_statement.find(concat_op_and) != string::npos){
                idx = temp_statement.find(concat_op_and);
                left = temp_statement.substr(0, idx);
                right = temp_statement.substr(idx + concat_op_and.length(), string::npos);
                SemanticFormat(left);
                statement= statement + left + concat_op_and;
                temp_statement = temp_statement.substr(idx + concat_op_and.length(), string::npos);
            }
            SemanticFormat(right);
            statement = statement + right;
        }

        // for ||
        if(statement.find(concat_op_or) != string::npos){
            string temp_statement = statement;
            statement = "";
            while(temp_statement.find(concat_op_or) != string::npos){
                idx = temp_statement.find(concat_op_or);
                left = temp_statement.substr(0, idx);
                right = temp_statement.substr(idx + concat_op_or.length(), string::npos);
                SemanticFormat(left);
                statement= statement + left + concat_op_or;
                temp_statement = temp_statement.substr(idx + concat_op_or.length(), string::npos);
            }
            SemanticFormat(right);
            statement = statement + right;
        }

        return;
    }
}

void CUtil::SemanticDeduplicate(set<string> &distinct_cond_set)
{
    return;
}

void CUtil::CountDistinctCond(string &valid_statement, const string &base, StringVector &container, unsigned int &count, int mode, const string &exclude,
                              const string &include1, const string &include2, set<string> &distinct_cond_set, UIntVector* counter_container, bool case_sensitive)
{
    string::size_type idx, left_bracket_idx, right_bracket_idx;
    string base1;
    StringVector::iterator vit;
    UIntVector::iterator cit;
    unsigned int single_count = 0;
    base1 = " " + base + " ";



    if (counter_container)
        cit = counter_container->begin();

    if (case_sensitive == false)
    {
        base1 = CUtil::ToLower(base1);
        for (vit = container.begin(); vit != container.end(); vit++)
            (*vit) = CUtil::ToLower((*vit));
    }
    int index;
    if (mode == 1)
    {
        // exclude mode
        for (vit = container.begin(); vit != container.end(); vit++)
        {
            idx = base1.find((*vit));
            while (idx != string::npos)
            {
                if ((exclude.find(base1[idx+((*vit).size())]) == string::npos) &&
                    (exclude.find(base1[idx-1]) == string::npos))
                {
                    count++;
                    single_count++;
                    left_bracket_idx = base1.find("(", idx);
                    if (left_bracket_idx != string::npos)
                    {
                        index = left_bracket_idx + 1;
                        int level = 1;
                        while(index < base1.length() && level > 0)
                        {
                            if (base1[index] == '(') ++level;
                            if (base1[index] == ')') --level;
                            index++;
                        }
                        if (index < base1.length()){

                            string temp = base1.substr(left_bracket_idx+1, index - left_bracket_idx-2);
                            CUtil::SemanticFormat(temp);


                            // if || included, we insert all the statement split it by "||"
                            string temp_statement = temp;
                            string concat_op_or="||";
                            if(temp_statement.find(concat_op_or) != string::npos){
                                int idx;
                                string left;
                                string right;
                                while(temp_statement.find(concat_op_or) != string::npos){
                                    idx = temp_statement.find(concat_op_or);
                                    left = temp_statement.substr(0, idx);
                                    right = temp_statement.substr(idx + concat_op_or.length(), string::npos);
                                    distinct_cond_set.insert(left);
                                    temp_statement = temp_statement.substr(idx + concat_op_or.length(), string::npos);
                                }
                                distinct_cond_set.insert(right);
                            }else{
                                distinct_cond_set.insert(temp);
                            }
                            // but keep, because we need to push it into cc4 parent stack
                            valid_statement=temp;


                        }
                    }
                    else
                    {
                        index = idx + (*vit).size();
                    }
                }
                else
                {
                    index = idx + (*vit).size();
                }
                idx = base1.find((*vit), index);
            }
            if (counter_container)
            {
                (*cit) += single_count;
                single_count = 0;
                cit++;
            }
        }
    }
    else if (mode == 2)
    {
        // include mode
        for (vit = container.begin(); vit != container.end(); vit++)
        {
            idx = base1.find((*vit));
            while (idx != string::npos)
            {
                if ((include1.find(base1[idx-1]) != string::npos) &&
                    (include2.find(base1[idx+((*vit).size())]) != string::npos))
                    count++;
                idx = base1.find((*vit), idx + ((*vit).size()));
            }
        }
    }
}
