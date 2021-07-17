#include <iostream>
#include <queue>
#include <unordered_map>
#include <string>

struct Node{
    public: char c_Alpha;
    public: std::unordered_map<char, Node*>* op_Map;
    public: Node(char c_Alpha){
        this->c_Alpha  = c_Alpha;
        op_Map = new std::unordered_map<char, Node*>();
    }

    public: ~Node(){
        delete op_Map;
    };
};

class PreTree{
    public: Node* op_Root;
    public: PreTree(){
        op_Root = new Node('\0');
    }

    public: ~PreTree(){
        std::queue<Node*> o_Qu;
        o_Qu.push(op_Root);

        while(o_Qu.empty() == false){
            Node* op_Fir = o_Qu.front();
            o_Qu.pop();
            for(auto op_Item = op_Fir->op_Map->begin();
                op_Item != op_Fir->op_Map->end(); op_Item++){
                o_Qu.push(op_Item->second);
            }
            delete op_Fir;
        }
    }

    public: Node* fn_Search(Node* op_Curr, char c_NexAlpha){
        Node* op_Re = nullptr;
        auto op_NextOb = op_Curr->op_Map->find (c_NexAlpha);
        if(op_NextOb != op_Curr->op_Map->end()){// COM: Hitting
            op_Re = op_NextOb->second;
        }

        return op_Re;
    }

    public: void fn_Build(std::string s_Msg, Node* o_CurrNode){
        for(int i_Ct =0; i_Ct < s_Msg.length(); i_Ct++){
            Node* op_Tmp = fn_Search(o_CurrNode, s_Msg[i_Ct]);
            if(op_Tmp != nullptr){
                o_CurrNode = op_Tmp;
                continue;
            }
            else{
                op_Tmp = new Node(s_Msg[i_Ct]);
                o_CurrNode->op_Map->insert(std::pair<char, Node*>(s_Msg[i_Ct], op_Tmp));
                o_CurrNode = op_Tmp;
            }
        }
    }

    public: void fn_ShowResult(){
        std::queue<Node*> o_Qu;
        o_Qu.push(op_Root);

        while(o_Qu.empty() == false){
            Node* op_Fir = o_Qu.front();
            o_Qu.pop();
            std::cout<< op_Fir->c_Alpha << " ";
            for(auto op_Item = op_Fir->op_Map->begin();
                op_Item != op_Fir->op_Map->end(); op_Item++){
                o_Qu.push(op_Item->second);
            }
        }
    }
};

int main(){
    PreTree o_PTree;
    o_PTree.fn_Build("in", o_PTree.op_Root);
    o_PTree.fn_Build("ina", o_PTree.op_Root);
    o_PTree.fn_Build("the", o_PTree.op_Root);

    o_PTree.fn_ShowResult();
    return 0;
}
