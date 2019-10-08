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

int fn(int k){
    std::deque <int> q;
    int max_ele = INT_MIN;
    int i;
    for(i=0; i<k; i++){
        while((!q.empty()) and lcp[i] < lcp[q.back()])
            q.pop_back();
        q.push_back(i);
    }
    while(i< N){
        // std::cout<<lcp[q.front()]<<"\n";
        max_ele = std::max(lcp[q.front()], max_ele);
        while((!q.empty()) and q.front() <= i - k)
            q.pop_front();
        while((!q.empty()) and lcp[i] <= lcp[q.back()])
            q.pop_back();
        q.push_back(i); 
        i++;
    }
    // std::cout<<lcp[q.front()]<<"\n";
    max_ele = std::max(lcp[q.front()], max_ele);
    return max_ele;
}
int main(int argc, char const *argv[]){
    string S;
    int longest_pal_len = 0;
    int index = -1; 
    int k;
    cin>>N;
    cin>>k;
    cin>>S;
    // N = S.size();
    build_suffix_arr(S);
    build_LCP(S);
    // std::cout<<"sa: ";
    // for(int i=0 ; i< N; i++) std::cout<<sa[i]<<" ";
    // std::cout<<"\nlcp: ";
    // for(int i=0 ; i< N; i++) std::cout<<lcp[i]<<" ";
    // std::cout<<"\n";    
    int ans = fn(k-1); 
    (ans > 0) ? std::cout<<ans<<"\n": std::cout<<-1<<"\n";
    return 0;
}