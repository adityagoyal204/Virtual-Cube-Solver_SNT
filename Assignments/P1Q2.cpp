#include <bits/stdc++.h>
#include<iterator>
typedef long long int ll;
#define ld long double
#define pb push_back

using namespace std;


#define sz(a) int((a).size())
#define all(c) c.begin(), c.end()
#define tr(c, i) for (typeof (c).begin() i = c.begin(); i != c.end(); i++)
#define present(c, x)(c.find(x) != c.end())
#define cpresent(c, x)(find(all(c), x) != c.end())


typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef pair<double,double> pd;
typedef vector<ll> vll;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<vector<ll> > vvll;
typedef vector<vector<pll> > vvpll;
typedef vector<pll> vpll;
typedef vector<pi> vpi;
#define fi(i,a,b) for(ll i = (a); i < (b); i++)
#define fr(i,a,b) for(ll i = (a); i >=(b); i--)
#define dbg(x) cout<<#x<<"="<<x<<endl
#define mp make_pair
#define pb push_back
#define inp(arr,z) for(int i=0; i<z; i++)cin>>arr[i]

const int MOD = 1e9+7;
const ld PI = acos(-1);
const ld EPS = 1e-9;
const ll INF = 1e18;

int fexp(int a, int b,int m){int ans = 1;while(b){if(b&1)ans=(ans*a)%m; b/=2;a=(a*a)%m;}return ans;}
int inverse(int a, int p){return fexp(a, p-2,p);} 


void solve(){

    ll n;
    cin>>n ;
    vpi vec ;
    vpi ans ;


    for (int i=0;i<n;i++){

        int x,y ;
        cin>>x>>y ;
        vec.pb(mp(x,y));

    }

    //cout<<vec[0].second;

    sort(vec.begin(),vec.end());  // sorted wrt to the first element of the pair

    int j ;
    
        if(vec[1].second>vec[0].second && vec[1].first <=vec[0].second){

            ans.pb(mp(vec[0].first , vec[1].second));
            j=0;

        }
         
        else if (vec[1].second<=vec[0].second) {

            ans.pb(mp(vec[0].first , vec[0].second));
            j=0;
        } 

        else if (vec[1].first >vec[0].second){
               
            ans.pb(mp(vec[0].first , vec[0].second));
            ans.pb(mp(vec[1].first , vec[1].second));
            j=1 ;

        }

        //initialised the ans vector
    

        for (int i=2;i<n;i++){

           if (vec[i].second > ans[j].second  && vec[i].first <= ans[j].second){

               ans[j].second=vec[i].second ;

    }

           else if (vec[i].first > ans[j].second){

               ans.pb(mp(vec[i].first, vec[i].second));
               j++ ;

           }
        }

        cout<<ans.size()<<"\n";


        for (int i=0;i<ans.size();i++)
              cout<<ans[i].first<<" "<<ans[i].second<<"\n";
            
       
    return;
}
	
int main(){

	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int TC = 1,t = 0;
	//cin >> TC;
	while(t++ < TC){
		// cout << "Case #" << t << ": "; // For Google CodeJam and Kickstart
		solve();
		//cout << "\n";
	}

	// cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n";

	return 0; 
}
