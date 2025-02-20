tring findFirstSub(string s, string t) {
    unordered_map<char, int> charCounts;
    for (char c: t) {
        charCounts[c]++;
    }
    int left = 0;
    /*
    s:
    z z z a d o b e c  
    0 1 2 3 4 5 6 7 8. 
    
    t: "abc"
    
    z z z a d o b e c  
    left = 0, right = 0 charCounts:[a: 1 , b: 1, c:1] 
    */
    bool found = false;
    for (int right = 0; right < s.size(); right++){
        if (charCounts.find(s[right]) != charCounts.end()) { // exists
            found = true;
            charCounts[s[right]]--;
            if (charCounts[s[right]] == 0) {
                charCounts.erase(s[right]);
            }
            if (charCounts.size() == 0) {
                return s.substr(left, right - left + 1);
            }
        } else if (!found) {
            left = right + 1;
            
        }
    }
    return "";
}
