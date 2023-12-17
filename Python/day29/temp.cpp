class FoodRatings {
public:

    unordered_map<string, map<int, set<string>, greater<int>>> food_t;
    unordered_map<string, pair<string, int>> ratings;

    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for(int i = 0; i < foods.size(); i++){
            this->ratings[foods[i]] = {cuisines[i], ratings[i]};
            food_t[cuisines[i]][ratings[i]].insert(foods[i]);
        }
        
    }
    
    void changeRating(string food, int newRating) {
        string cuisine = ratings[food].first;
        int rating = ratings[food].second;
        ratings[food].second = newRating;
        food_t[cuisine][rating].erase(food);
        if(food_t[cuisine][rating].empty())
            food_t[cuisine].erase(rating);
        food_t[cuisine][newRating].insert(food);
    }
    
    string highestRated(string cuisine) {
        return *(((food_t[cuisine].begin())->second).begin());
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */