
/*
 * TDDD86 Pattern Recognition
 * This program computes and plots all line segments involving 4 points
 * in a file using Qt.
 */

#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include "Point.h"
#include "unordered_map"


// constants
static const int SCENE_WIDTH = 512;
static const int SCENE_HEIGHT = 512;

void printMap(unordered_map<double, vector<Point> > &pointMap);
vector<pair<Point,Point>> sortLoop(int N,vector<Point> points);
void filter(unordered_map<double,vector<Point>>& pointMap);
vector<vector<Point>> lineFilter(unordered_map<double,vector<Point>>& pointMap);
vector<pair<Point,Point>> pairLines(vector<vector<Point>> &lines);
void render_points(QGraphicsScene* scene, const vector<Point>& points) {
    for(const auto& point : points) {
        point.draw(scene);
    }
}

void render_line(QGraphicsScene* scene, const Point& p1, const Point& p2) {
    p1.lineTo(scene, p2);
}

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // open file
    string filename = "input100.txt";
    ifstream input;
    input.open(filename);
    // the vector of points

    vector<Point> points;

    // read points from file
    int N;
    int x;
    int y;

    input >> N;

    for (int i = 0; i < N; ++i) {
        input >> x >> y;
        points.push_back(Point(x, y));
    }
    input.close();

    // setup graphical window
    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0, 0, SCENE_WIDTH, SCENE_HEIGHT);
    view->setScene(scene);
    // draw points to screen all at once
    render_points(scene, points);
    view->scale(1, -1); //screen y-axis is inverted
    view->resize(view->sizeHint());
    view->setWindowTitle("Brute Force Pattern Recognition");
    view->show();

    // sort points by natural order
    // makes finding endpoints of line segments easy
    sort(points.begin(), points.end());
    auto begin = chrono::high_resolution_clock::now();

    vector<pair<Point,Point>> pairs = sortLoop(N,points);//our code starts here

    for(auto pair : pairs){// goes through pairs and draws the lines

        render_line(scene, pair.first, pair.second);
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Computing line segments took "
         << std::chrono::duration_cast<chrono::milliseconds>(end - begin).count()
         << " milliseconds." << endl;

    return a.exec(); // start Qt event loop
}
vector<pair<Point,Point>> sortLoop(int N,vector<Point> points){// main algorithm loop
    unordered_map<double,vector<Point>> pointMap;// saved in unordered_map to speed up.
    double k;
    bool found;

    for (int i = 0; i < N; i++){// goes through every point and notes the points k-value against every other point
        Point p = points.at(i);
        for (int j = 0; j < N; j++){
            Point q = points.at(j);
            k = p.slopeTo(q);

        if(pointMap.count(k)){
            //check for double
            found = false;
            for (auto part : pointMap[k]){
                if (part.slopeTo(q) == -numeric_limits<double>::infinity()){
                    found = true;
                }

            }
            if(!found){
                pointMap[k].push_back(q);
            }



        }
        else{
            vector<Point> temp;
            temp.push_back(p);
            temp.push_back(q);
            pointMap.insert(make_pair(k,temp));
            }
        }
    }
filter(pointMap);

vector<vector<Point>> lines = lineFilter(pointMap);

vector<pair<Point,Point>> lineVector = pairLines(lines);

return lineVector;

}
void printMap(unordered_map<double,vector<Point>>& pointMap){
    vector<Point> vec;
    for(auto it = pointMap.begin() ; it!= pointMap.end() ; it++){
        cout << "KEY " << it->first << endl;
        vec = it->second;
        for(auto iti = vec.begin() ; iti != vec.end() ; iti++){
            cout << "Value " << *iti << endl;
        }
        cout << endl;
    }

}

void filter(unordered_map<double,vector<Point>>& pointMap){// removes points without lines.
    vector<Point> vec;
    for(auto it = pointMap.begin() ; it!= pointMap.end() ; ){
        vec = it->second;
        if (vec.size() > 3){
            ++it;
        }
        else{
            pointMap.erase(it++);
        }
    }
}

vector<vector<Point>> lineFilter(unordered_map<double, vector<Point> > &pointMap){// filters lines with same k-value but that are parallel
   vector<vector<Point>> result;// saves result in vector with vector of points for easy pair making
   for (auto mapKey : pointMap ){
        double k = mapKey.first;
        vector<Point> partition = mapKey.second;
        for (int i = 0 ; i < partition.size() ; i++){
            vector<Point> resultPart;
            Point p = partition.at(i);
            resultPart.push_back(p);
            for (int j = 0 ; j < partition.size() ; j++){
                if (k == p.slopeTo(partition.at(j))){
                    resultPart.push_back(partition.at(j));
                }
            }
            if (resultPart.size() > 3){
                result.push_back(resultPart);
            }

        }
    }
return result;
}


vector<pair<Point,Point>> pairLines(vector<vector<Point>> &lines){ // pairs line for linedrawing
        vector<pair<Point,Point>> pairs;

    for (int i = 0; i < lines.size(); i ++){
        Point max = lines.at(i).at(0);// line only need to be drawn from the minimum point of a line to the maximum point.
        Point min = lines.at(i).at(0);


        for (int j = 0; j < lines.at(i).size(); j++){


            if (lines.at(i).at(j) > max){
                max = lines.at(i).at(j);
            }
            if (lines.at(i).at(j) < min){
                min = lines.at(i).at(j);
            }
        }

    pair<Point,Point> res = make_pair(min,max);// makes a pair
    bool putValue = true;
    for (auto part : pairs){
        if (res.first.slopeTo(part.first) == -std::numeric_limits<double>::infinity()&& res.second.slopeTo(part.second) == -std::numeric_limits<double>::infinity()){
            // slopeto returns -infinity if used on itself, used here to find indentical entities.
            putValue = false;
        }
    }
    if (putValue){
        pairs.push_back(res);//saves pairs

    }


    }
return  pairs;
}
