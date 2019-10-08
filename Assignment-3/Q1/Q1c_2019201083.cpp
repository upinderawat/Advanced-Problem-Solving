#include <bits/stdc++.h>
#define MAX_SIZE 1<<20
// #define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#define DEBUG_MSG_ARG2(stra, strb) do { std::cout << stra << strb << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#define DEBUG_MSG_ARG2(stra, strb ) do { } while( false )
#endif

using namespace std;
int N, gap;
int sa[MAX_SIZE], pos[MAX_SIZE], lcp[MAX_SIZE];

void print_arr(int tmp[]){
	std::cout<<"sa: ";
	for(int i=0; i<N; i++) std::cout<<sa[i]<<" ";
	std::cout<<"\n";

	std::cout<<"tmp: ";
	for(int i=0; i<N; i++) std::cout<<tmp[i]<<" ";
    std::cout<<"\n";

	std::cout<<"pos: ";
	for(int i=0; i<N; i++) std::cout<<pos[i]<<" ";
	std::cout<<"\n";
    

}   
bool Cmp(int i, int j){
	if (pos[i] != pos[j]){
	    return pos[i] < pos[j];
	}
    i += gap;
    j += gap;
    return (i < N && j < N) ? pos[i] < pos[j] : i > j;
}

void build_suffix_arr(string S){
    int tmp[N]={0};
    for(int i=0; i<N; i++){
        sa[i] = i;
        pos[i] = S[i];
    }
    #ifdef DEBUG
        print_arr(tmp);
    #endif
    for (gap = 1;; gap *= 2)
    {
        DEBUG_MSG_ARG2("GAP: ",gap);
        std::sort(sa, sa + N, Cmp);
        for(int i=0; i<N-1; i++){
            tmp[i+1] = tmp[i] + Cmp(sa[i], sa[i + 1]);
        }
        for(int i=0; i<N; i++)
            pos[sa[i]] = tmp[i];
        #ifdef DEBUG
            print_arr(tmp);
        #endif
        if (tmp[N - 1] == N - 1) break;
    }
}

void build_LCP(string S){
    for (int i = 0, k = 0; i < N; ++i){
        if (pos[i] != N - 1){
            for (int j = sa[pos[i] + 1]; S[i + k] == S[j + k];)
                ++k;
            lcp[pos[i]] = k;
            if (k)--k;
        }
    }
}
int main(int argc, char const *argv[]){
	string S;
    int longest_pal_len = 0;
    int index = -1; 
    int S_size;
    string S_rev; 
    cin>>S_size;
    cin>>S;
    // S_size = S.size();
    S_rev = S;
    reverse(S_rev.begin(), S_rev.end());
    S_rev = S + "#" + S_rev;
    DEBUG_MSG(S_rev);
    N = S_rev.size();
	build_suffix_arr(S_rev);
    build_LCP(S_rev);
    // std::cout<<"sa: ";
    // for(int i=0 ; i< N; i++) std::cout<<sa[i]<<" ";
    // std::cout<<"\nlcp: ";
    // for(int i=0 ; i< N; i++) std::cout<<lcp[i]<<" ";
    // std::cout<<"\n";    
    for(int i=0; i< N-1; i++){
        if(lcp[i] > longest_pal_len and (sa[i] > S_size and sa[i+1] < S_size or sa[i] < S_size and sa[i+1] > S_size)){
            longest_pal_len = lcp[i];
            index = sa[i];
        }
    }
    // cout<<index<<"\n";
    // cout<<longest_pal_len;
    cout<<S_rev.substr(index, longest_pal_len)<<"\n";
    // }
    // long i;
    // for(i=0; i<N-1; i++){
    //     if(lcp[i] >= K){
    //         break;
    //     }
    // }
    // if(i==N){
    //     std::cout<<-1<<"\n";
    // }
    // else{
    //     std::cout<<lcp[i]<<"\n";
    // }
	return 0;
}