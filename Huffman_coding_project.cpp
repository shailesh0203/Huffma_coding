
#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

class HuffmanCoder {
    unordered_map<char, string> encoder;
    unordered_map<string, char> decoder;

    struct Node {
        char data;
        int cost;
        Node* left;
        Node* right;

        Node(char data, int cost) : data(data), cost(cost), left(nullptr), right(nullptr) {}
    };

    struct CompareNode {
        bool operator()(Node* left, Node* right) {
            return left->cost > right->cost;
        }
    };

public:
    HuffmanCoder(const string& feeder) {
        unordered_map<char, int> fmap;

        for (char cc : feeder) {
            fmap[cc]++;
        }

        priority_queue<Node*, vector<Node*>, CompareNode> minHeap;

        for (auto& entry : fmap) {
            Node* node = new Node(entry.first, entry.second);
            minHeap.push(node);
        }

        while (minHeap.size() != 1) {
            Node* first = minHeap.top();
            minHeap.pop();
            Node* second = minHeap.top();
            minHeap.pop();

            Node* newNode = new Node('\0', first->cost + second->cost);
            newNode->left = first;
            newNode->right = second;

            minHeap.push(newNode);
        }

        Node* ft = minHeap.top();
        minHeap.pop();

        initEncoderDecoder(ft, "");
    }

    string encode(const string& source) {
        string ans;
        for (char ch : source) {
            ans += encoder[ch];
        }
        return ans;
    }

    string decode(const string& codedString) {
        string key;
        string ans;
        for (char ch : codedString) {
            key += ch;
            if (decoder.count(key)) {
                ans += decoder[key];
                key.clear();
            }
        }
        return ans;
    }

private:
    void initEncoderDecoder(Node* node, string osf) {
        if (node == nullptr) {
            return;
        }
        if (node->left == nullptr && node->right == nullptr) {
            encoder[node->data] = osf;
            decoder[osf] = node->data;
        }
        initEncoderDecoder(node->left, osf + "0");
        initEncoderDecoder(node->right, osf + "1");
    }
};
int main() {
    string str = "abbccda";
    HuffmanCoder hf(str);
    string cs = hf.encode(str);
    cout << cs << endl;
    string dc = hf.decode(cs);
    cout << dc << endl;

    return 0;
}
