/*We have defined our own markup language HRML. In HRML, each element consists of a starting and ending tag, and there are attributes associated with each tag. Only starting tags can have attributes. We can call an attribute by referencing the tag, followed by a tilde, '~' and the name of the attribute. The tags may also be nested.

The opening tags follow the format:

<tag-name attribute1-name = "value1" attribute2-name = "value2" ...>

The closing tags follow the format:

</tag-name>

For example:

<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>

The attributes are referenced as:

tag1~value  
tag1.tag2~name

You are given the source code in HRML format consisting of  N lines. You have to answer Q queries. Each query asks you to print the value of the attribute specified. Print "Not Found!" if there isn't any such attribute.

Input Format

The first line consists of two space separated integers, N and Q. N specifies the number of lines in the HRML source program. Q specifies the number of queries.

The following N lines consist of either an opening tag with zero or more attributes or a closing tag.There is a space after the tag-name, attribute-name, '=' and value.There is no space after the last value. If there are no attributes there is no space after tag name.

Q queries follow. Each query consists of string that references an attribute in the source program.More formally, each query is of the form  tag1.tag2.tag3.......tagn ~attr - name where m>= 1 and
tag1,tag2,tag3..........tagn are valid tags in the input.

Constraints
1 <= N<=20
1< = Q <= 20

Each line in the source program contains, at max,200 characters.
Every reference to the attributes in the Q queries contains at max 200 characters.
All tag names are unique and the HRML source program is logically correct.
A tag can have no attributes as well.

Output Format

Print the value of the attribute for each query. Print "Not Found!" without quotes if there is no such attribute in the source program.

Sample Input

4 3
<tag1 value = "HelloWorld">
<tag2 name = "Name1">
</tag2>
</tag1>
tag1.tag2~name
tag1~name
tag1~value

Sample Output

Name1
Not Found!
HelloWorld

*/
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;


map<string,int> index;
void map_path(string* paths, int N)
{
    queue<string> path;
    for (int i = 0; i < N; i++)
    {
        if (paths[i][1] != '/')
        {
            string ctag;
            int k = 1;
            while (paths[i][k] != ' ' && paths[i][k] != '>')
            {
                ctag += paths[i][k];
                k++;
            }
            path.push(ctag);
            string i_path;
            int j = path.size();
            while (j)
            {
                i_path += path.front();
                j != 1 ? i_path+='.' : i_path+="";
                path.push(path.front());
                path.pop();
                j--;
            }
            index.insert(make_pair(i_path,i));
        }
        else
        {
           int j = path.size()-1;
           while (j--)
            {
               path.push(path.front());
               path.pop();
            }
            if (path.size() > 0) path.pop();
        }
    }
}

// Extracting the attribute name from the given query string and determining if the query path is valid
bool interQ(int& tag_i, string& attname, const string& query, int& tag_size)
{
    int i = query.size()-1;
    while (query[i] != '~') {
        if (query[i] == '.'){
            cout << "Not Found!" << endl;
            return false;
        }
        attname = query[i] + attname;
        i--;
    }
    if (index.count(query.substr(0,i)) == 0)
    {
        return false;
    }
    tag_i = index.at(query.substr(0,i));
    i--;
    while (i >= 0 && query[i] != '.')
    {
        tag_size++;
        i--;
    }
    return true;
}

// if the query path is valid then it will be passed to this function to determine if there is a matching attribute and return its value if so
void ansQ(const int& tag_i, const string& attname, const string* lines, string& value, const int& tag_size) {
    string line = lines[tag_i];
    int length = line.size();
    bool isName = false;
    string curAtt  = "";
    bool isValue = false;
    
    for (int j = tag_size+1; j < length; j++){
        char c = line[j];
        if (c == ' ' && !isValue){
            isName = !isName;
            if (curAtt == attname) {
                j+=4;
                while (line[j] != '"') {
                    value += line[j];
                    j++;
                }
                return;
            }
            curAtt = "";
            continue;
        }
        if (isName) {
            if (c == '"') {
                isName = !isName;
                isValue = !isValue;
                continue;
            }
            curAtt += c;
        }
        if (c == '"') {
            isValue = !isValue;
        }
    }
    value = "Not Found!";
}


int main() {
    int N;
    int Q;
    cin >> N;
    cin >> Q;
    cin.ignore();

    string lines[N];
    string queries[Q];

    for (int i = 0; i < N; i++) {
        string line;
        getline(cin, line);
        lines[i] = line;
    }
    map_path(lines,N);
    string query;
    int tag_i;
    string attName;
    string value;
    int tag_size = 0;
    for (int i = 0; i < Q; i++) {
        getline(cin, query);
        attName = "";
        tag_size = 0;
        bool validQ = interQ(tag_i, attName, query, tag_size);
        if (validQ) {
            value = "";
            ansQ(tag_i, attName, lines, value, tag_size);
            cout << value << endl;           
        }
        else 
        {
            cout << "Not Found!" << endl;
        }
    }
    return 0;
}
