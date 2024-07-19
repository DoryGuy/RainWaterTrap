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

// trying some simple concept code.
template<typename T>
concept HasValueType = requires { typename T::value_type; };

template<typename T>
concept Has_cbegin = requires(T t) {  t.cbegin(); };

template<typename T>
concept Has_crbegin = requires(T t) { t.crbegin(); };

// Solution is O(N) it uses minimal space
template<class T>
requires HasValueType<T> && Has_cbegin<T> && Has_crbegin<T>
consteval T::value_type getVolume (T const &elevation) {
    if (elevation.empty() ) {
        return 0;
    }
    typename T::value_type  max_left_side(0);
    typename T::value_type  max_right_side(0);
    typename T::value_type  volume(0);
    
    auto left_side_iter(elevation.cbegin());
    auto right_side_iter(elevation.crbegin());
    
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

int main() {
    // insert code here...
    using std::cout;
    using std::endl;
    using std::array;
    
    static constexpr array<int, 12> elevation{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    // The next line will fail to compile because of not satisfying the concepts for getVolume
    // static constexpr int elevation[] = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
    
    auto volume = getVolume(elevation);
    cout << "Volume Original Problem = " << volume << endl;
    assert(volume == 6);
    
    static constexpr array<int, 12> sea_level_elevation{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    volume = getVolume(sea_level_elevation);
    cout << "Volume Sea level = " << volume << endl;
    assert(volume == 0);
    
    static constexpr array<int, 12> mountain_elevation{0, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 0};
    volume = getVolume(mountain_elevation);
    cout << "Volume Mountain = " << volume << endl;
    assert(volume == 0);
    
    static constexpr array<int, 12> valley_elevation{5, 4, 3, 2, 1, 0, 0, 1, 2, 3, 4, 5};
    volume = getVolume(valley_elevation);
    cout << "Volume Valley = " << volume << endl;
    assert(volume == 30);
    
    static constexpr array<int, 12> high_plains_elevation{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5};
    volume = getVolume(high_plains_elevation);
    cout << "Volume High Plains = " << volume << endl;
    assert(volume == 0);
    
    static constexpr array<int, 0> empty_container{};
    volume = getVolume(empty_container);
    cout << "Volume Empty Container = " << volume << endl;
    assert(volume == 0);

    static constexpr array<int, 1> one_element_container{1};
    volume = getVolume(one_element_container);
    cout << "Volume One element Container = " << volume << endl;
    assert(volume == 0);

    static constexpr array<int, 2> two_element_container{1, 1};
    volume = getVolume(two_element_container);
    cout << "Volume Two element Container = " << volume << endl;
    assert(volume == 0);
    
    static constexpr array<int, 3> three_element_container{1, 0, 1};
    volume = getVolume(three_element_container);
    cout << "Volume Three element Container = " << volume << endl;
    assert(volume == 1);
    
    return 0;
}
