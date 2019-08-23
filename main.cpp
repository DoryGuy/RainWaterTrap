//
//  main.cpp
//  RainWaterTrap
//
//  Created by Gary Powell on 8/23/19.
//  Copyright © 2019 Guest User. All rights reserved.
//

#include <array>
#include <algorithm>
#include <iostream>

#include <cassert>

// Solution is O(N) it uses minimal space
template<class T>
int getVolume (T const &elevation) {
    using std::min;
    
    int max_left_side(0);
    int max_right_side(0);
    int volume(0);
    
    auto left_side_iter(elevation.begin());
    auto right_side_iter(elevation.rbegin());
    
    while (left_side_iter <= (right_side_iter + 1).base()) {
        if (*left_side_iter < *right_side_iter) {
            if (*left_side_iter > max_left_side) {
                max_left_side = *left_side_iter;
            } else {
                auto height = *left_side_iter;
                volume += max_left_side - height;
            }
            ++left_side_iter;
        }
        else  {
            if (*right_side_iter > max_right_side) {
                max_right_side = *right_side_iter;
            } else {
                auto height = *right_side_iter;
                volume += max_right_side - height;
            }
            ++right_side_iter;
        }
    }
    return volume;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    using std::cout;
    using std::endl;
    using std::array;
    cout << "Hello, World!\n";
    
    array<int, 12> elevation{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    auto volume = getVolume(elevation);
    cout << "Volume Original Problem = " << volume << endl;
    assert(volume == 6);
    
    array<int, 12> sea_level_elevation{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    volume = getVolume(sea_level_elevation);
    cout << "Volume Sea level = " << volume << endl;
    assert(volume == 0);
    
    array<int, 12> mountain_elevation{0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0};
    volume = getVolume(mountain_elevation);
    cout << "Volume Mountain = " << volume << endl;
    assert(volume == 0);
    
    array<int, 12> valley_elevation{5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5};
    volume = getVolume(valley_elevation);
    cout << "Volume Valley = " << volume << endl;
    assert(volume == 30);
    
    array<int, 12> high_plains_elevation{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    volume = getVolume(high_plains_elevation);
    cout << "Volume High Plains = " << volume << endl;
    assert(volume == 0);
    
    return 0;
}
