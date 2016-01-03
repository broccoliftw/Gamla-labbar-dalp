#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;



int calculateProfit(int priceToBuy, int PriceToSell){

    return priceToBuy - PriceToSell;
}

int convertToSilver(int gold,int silver){

    return gold*100 + silver;
}

void printGold(int silver){

    cout << (to_string(silver/100) + "Gold " + to_string((silver % 100)) + "Silver");
}
int main(){

    vector <pair(int,int)> goodsToBuy;
    int answer;
    cout << "Add Goods to Buy?";
    cin >> answer;

    switch (answer){
    case "a":
        int n;
        int price;
        cout << "enter number of items";
        cin >> n;
        cout << "enter price per unit";
        cin price;
        goodsToBuy.push_back(make_pair(n,price));
    break;
    }


    return 0;

}
