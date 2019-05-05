#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Homework 5
// Submission by Kavin Agrawal
// Roll no 170040051
struct Node{
  Node *L, *R;
  char op;
  string value;
  Node(string v);
  Node(char op1, Node* L1, Node* R1);
  Node(istream& infile);
  string print();
  Node* deriv();
};

Node::Node(string v){                        // primitive constructor
  value = v;
  op = 'P';   // convention: 'P' in op denotes primitive formula.
  L = NULL;
  R = NULL;
}

Node::Node(char op1, Node* L1, Node* R1){  // recursive constructor
  value = "";
  op    = op1;
  L   = L1;
  R   = R1;
}

Node::Node(istream &infile){
  char c=infile.get();
  if((c >= '0' && c <= '9') ||     // is it a primitive formula?
     (c >= 'a' && c <= 'z') ||
     (c >= 'A' && c <= 'Z')){
    L=R=NULL; op='P'; value = c;
  }
  else if(c == '('){              // does it start a non-primitive formula?
    L = new Node(infile);            // recursively get the L formula
    op = infile.get();
    if(op=='c' || op=='s'){
    	R=NULL;
    }
    else{
        R = new Node(infile);
    }
    if(infile.get() != ')')
      cout << "No matching parenthesis.\n";
  }
  else cout << "Error in input.\n";
}

Node* Node::deriv(){
	Node* tem=new Node("");
	if(R==NULL && L==NULL){
		if(value=="x"){
			tem->value="1" ;
		}
		else{
			tem->value="0";
		}
	}
	else{
		if(op=='+'){
			tem->L=L->deriv();
			tem->op='+';
			tem->R=R->deriv();
		}
		else if(op=='-'){
			tem->L=L->deriv();
			tem->op='-';
			tem->R=R->deriv();
		}
		else if(op=='*'){
			tem->L=new Node('*',L->deriv(),R);
			tem->op='+';
			tem->R=new Node('*',L,R->deriv());
		}
		else if(op=='/'){
            tem->L=new Node('-',new Node('*',L->deriv(),R),new Node('*',L,R->deriv()));
            tem->op='/';
            tem->R=new Node('*',R,R);

		}
		else if(op=='s')
		{
		    tem->L=new Node('c',L,NULL);
		    tem->op='*';
		    tem->R=L->deriv();
		}
		else if(op=='c')
		{
		    tem->L=new Node("0");
		    tem->op='-';
		    tem->R=new Node('*',new Node('s',L,R),L->deriv());
		}
	}
	return tem;
}

string Node::print(){
	string text;
	if(L==NULL && R==NULL){
	    return value;
	}
	else{
	    text=text+"(";
	    text=text+L->print();
	    text=text+op;
	    if(op=='s'||op=='c'){
	        text=text+")";
	    }
	    else{
	        text=text+R->print();
	        text=text+")";
	    }
	}
	return text;
}

int main(){
	Node z(cin);
	cout << z.print() << endl;
	cout << z.deriv()->print() << endl;
}
