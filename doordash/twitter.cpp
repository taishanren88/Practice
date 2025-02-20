#include <iostream>
#include <vector>
#include <set> // sorted map
#include <unordered_map> // hash set
using namespace std;


static long gTimeStamp = 0;
static const int maxTweets = 10;
class Twitter {
public:

    struct Tweet {
        Tweet(int aUserId, int aTweetId) {
            userId = aUserId;
            tweetId = aTweetId;
            timestamp = gTimeStamp;
        }

        int userId;
        int tweetId;
        long timestamp;
    };
    /** Initialize your data structure here. */
    Twitter() {
        gTimeStamp = 0;
        // Map user id -> tweets
        // Map user id -> follows Ids
        // Order by timestamp
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        userTweets[userId].push_back(Tweet(userId, tweetId));
        gTimeStamp++;
    }
    
    void addIn(vector<Tweet>& results, vector<Tweet>& toadd) {
        for (auto& tweet : toadd) {
            results.push_back(tweet);
        }
    }
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<Tweet> tweetsForUser = getTweets(userId);
        vector<Tweet> tweetResults;
        addIn(tweetResults, tweetsForUser);
        auto followsSorted = follows[userId];
        for (auto& followsId : followsSorted) {
            vector<Tweet> followsTweets = getTweets(followsId);
            addIn(tweetResults, followsTweets);
        }

        sort(tweetResults.begin(), tweetResults.end(), [](Tweet& a, Tweet& b) {
            return a.timestamp > b.timestamp;
        });
        vector<int> finalResults;
        int finalSize = 0;
        for (auto& tweet: tweetResults) {
            finalResults.push_back(tweet.tweetId);
            finalSize ++;
            if (finalSize == maxTweets) {
                break;
            }
        }
        return finalResults;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            follows[followerId].insert(followeeId);
        }
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
        auto& followsSorted = follows[followerId];
        if (followsSorted.find(followeeId) != followsSorted.end()) {
            followsSorted.erase(followeeId);
        }
    }

    vector<Tweet> getTweets(int userId) {
        vector<Tweet> tweetsGot;
        auto& tweetsForUser = userTweets[userId];
        int i = tweetsForUser.size() -1; 
        while (i >= 0 && tweetsGot.size() < 10) {
            tweetsGot.push_back(tweetsForUser[i]);
            i--;
        }
        return tweetsGot;
    }

    unordered_map<int, set<int> > follows;
    unordered_map<int, vector<Tweet> > userTweets;
};


int main() {
    Twitter twitter;
    twitter.postTweet(1, 5);
    auto result = twitter.getNewsFeed(1);
    auto tweetsForUser1 = twitter.getTweets(1);
    assert(tweetsForUser1.size() == 1 && tweetsForUser1[0].tweetId == 5);
    assert(result.size() == 1 && result[0] == 5);

    twitter.follow(1, 2);
    twitter.postTweet(2,6);
    auto user1TweetIds = twitter.getNewsFeed(1);
    assert(user1TweetIds.size() == 2 && user1TweetIds [0]==  6 &&user1TweetIds [1] == 5);

    twitter.unfollow(1,2);
    user1TweetIds = twitter.getNewsFeed(1);
    assert(user1TweetIds.size() == 1 &&user1TweetIds [0] == 5);
    for (int i = 0; i < 10; i++) {
        twitter.postTweet(2,10 + i);
    }

    user1TweetIds = twitter.getNewsFeed(1);
    assert(user1TweetIds.size() == 1 &&user1TweetIds [0] == 5);

    twitter.follow(1, 2);
    user1TweetIds = twitter.getNewsFeed(1);
    assert(user1TweetIds.size() == 10 && user1TweetIds.back() == 10);

    Twitter twitter2;
    twitter2.postTweet(1, 5);
    twitter2.follow(1,1);
    user1TweetIds = twitter2.getNewsFeed(1);
    assert(user1TweetIds.size() == 1);
}