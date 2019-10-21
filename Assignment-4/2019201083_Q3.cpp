#include <iostream>

#define MAX_BUFFER_SIZE 100

int get_len(const char* s){
	int i=0;
	while(s[++i] !='\0'); 
	return i;
}
struct node{
	const char* val;
	int len;//size of block
	struct node* next;
	node():next(nullptr){};
	node(const char* s): val(s), len(get_len(s)), next(nullptr){};
};
class StringBuilder{
	int size;//size of string
	node* head;
	node* tail;
public:
	StringBuilder(const char* s){
		head = new node(s);
		tail = head;
		size = head->len;
	}
	StringBuilder(StringBuilder& s){
		const char* str;
		// this->size = s.get_size();
		head = tail = nullptr;

		this->size = s.get_size();
		node* ptr = s.head;
		while(ptr!= nullptr){
			str = ptr->val;
			if(head == nullptr){
				head = new node(str);
				tail = head;
			}
			else{
				tail->next = new node(str);
				tail= tail->next;
			}
			ptr = ptr->next;
		} 
	}
	int get_size(){
		return this->size;
	}
	const char at(int);
	void append(StringBuilder);
	void append(const char* );

	int find(const char*);
	int* build_z();

	friend std::ostream &operator <<(std::ostream &out, const StringBuilder& s){
		for(node* tmp = s.head; tmp != nullptr; tmp = tmp->next){
			out<<(tmp->val);
		}
		out<<"\n";
		return out;
	}
	// void debug(){
	// 	std::cout<<this->size
	// }
};
const char StringBuilder::at(int i){
	if( i < 0 || i >= this->get_size()){
		std::cout<<"index out of bounds\n";
		return ' ';
	}
	node* ptr = this->head;
	while(ptr != nullptr && i >= ptr->len){
		i-= ptr->len;
		ptr = ptr->next;
	}
	return ptr->val[i];
}
void StringBuilder:: append(StringBuilder s){
		this->tail->next = s.head;
		this->tail = s.tail;
		this->size += s.size;
}
void StringBuilder:: append(const char* s){
	node* tmp = new node(s);
	tail->next = tmp;
	tail = tail->next;
	size += tail->len;
}
int StringBuilder::find(const char* p){
	int t_size=this->get_size();
	int p_size = get_len(p);

	StringBuilder s(p);
	s.append("$");
	s.append(*this);

	// std::cout<<p_size<<" "<<t_size;
	int *z = s.build_z();
	int k;
	for(int i=0; i<t_size; i++){
		k = z[i + p_size + 1];
		if(k == p_size){
			return i;
		}
	}
	return -1;
}
int* StringBuilder::build_z(){
	node* ptr;
	// int i=0;//string ptr
	// int j=0; block ptr
	int l=0, r=0;
	int* z= new int[this->get_size()];
	int n = this->get_size();
	//may use memset instead of loop,
	//used loop to avoid cstirng import
	for(int i=0; i<n; i++) z[i] = 0;		
		ptr = this->head;

	const char *str = ptr->val;
	int m = ptr->len;//block size
	for(int i=1,j=0; i< this->get_size(); i++, j++){
		if(m < j){
			ptr = ptr->next;
			m = ptr->len;
			str = ptr->val;
			j=0;
		}
		if(i <= r){
			//set start point of z, if possible
			z[i] = z[i-l] < (r - i + 1) ? z[i-l] : (r - i + 1);
		}
		while( ( i + z[i] < n ) and this->at(i + z[i]) == this->at(z[i])){
			z[i]++;
		}
		if(i + z[i] - 1 > r){
			l = i;
			r = i + z[i] - 1;
		}
	}
	return z;	
}

int main(int argc, char const *argv[]){
	StringBuilder s("upinder");
	s.append(s);
	// s.print_string();
	std::cout<<s;
	std::cout<<s.find("deru");
	// sp.print_string();
	// s.print_string();	
	// std::cout<<s.get_size()<<"\n";
	// for(int i=0; i<s.get_size(); i++)
	// 	std::cout<<s.at(i);
	// s.print_string();
	// int *z= s.build_z();
	// for(int i=0; i<s.get_size(); i++){
	// 	std::cout<<z[i]<<" ";
	// }
	return 0;
}