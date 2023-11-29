#include <iostream>
#include <vector>
#include <climits>
using namespace std;
#define IOS ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

int sizeeee =0;

int advance(int a, int direction)
{
    if(direction > 0)
    {
        if(a<sizeeee) return a+1;
        else return 1;
    }
    else
    {
        if(a>1) return a-1;
        else return sizeeee;
    }
}

int advanceBy2(int a,int direction)
{   
    if(direction > 0)
    {
        if(a<sizeeee-1) return a+2;
        else if(a==sizeeee-1) return 1;
        else return 2;
    }
    else
    {
        if(a>2) return a-2;
        else if(a==2) return sizeeee;
        else return sizeeee-1;
    }
}

int retreat(int a, int &direction)
{
    direction *= -1;
    return advance(a, direction);
}

void solve()
{
    int n;
    cin>>n;
    int k; 
    cin>>k;
    vector<char> str(k);
    for(int i=0; i<k; i++) cin>>str[i];
    int turn = 1;
    int direction = 1;
    sizeeee = n;
    for(int i=0; i<k; i++)
    {
        if(str[i] == 'U') turn = advance(turn, direction);
        else if(str[i] == 'S') turn = advanceBy2(turn, direction);
        else if(str[i] == 'R') turn = retreat(turn, direction);
    }
    cout<<turn<<endl;
}

int main()
{   
    IOS
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}