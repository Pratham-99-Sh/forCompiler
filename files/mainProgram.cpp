#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class car{
    public :
    string id;
    int x;
    int y;
    
    car(string i, int x, int y){
        this->id = i;
        this->x = x;
        this->y = y;
    }

    int dist() const{
        return x*x + y*y;
    }
};

class carCompare{
    public:
    bool operator()(const car A, const car B){
        return A.dist() < B.dist();
    }
};

bool distCompare(car A, car B){
        return A.dist() < B.dist();
    }

void printKNearestCars(vector<car> &cars, int k){
    priority_queue<car, vector<car>, carCompare> q(cars.begin(), cars.begin()+k);
    for(int i=k; i<cars.size(); i++){
        if(cars[i].dist() < q.top().dist()){
            q.pop();
            q.push(cars[i]);
        }
    }

    vector<car> output;
    while(!q.empty()){
        output.push_back(q.top());
        q.pop();
    }

    sort(output.begin(), output.end(), distCompare);

    for(auto c: output){
        cout << c.id << " " << c.dist() << endl;
    }
}

int main(){
    int n, k;
    cin >> n >> k;
    vector<car> cars;
    for(int i=0; i<n; i++){
        string id;
        int x, y;
        cin >> id >> x >> y;
        car c(id, x, y);
        cars.push_back(c);
    }
    printKNearestCars(cars, k);
    return 0;
}