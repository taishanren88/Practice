 #include <iostream>
#include <set>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;



#define MAX_TWEETS 10
 
struct Tweet
{
    Tweet(int userId, int timestamp)
        :m_userId(userId), m_timestamp(timestamp)
        {}
        
    int m_userId;
    int m_timestamp;
};


class User
{
public:
    User(int userId)
    :m_id(userId)
    { }
    void post(Tweet tweet)
    {
        // insert tweet to front of list
        m_tweets.push_front(tweet);
    }
    void follow(int id)
    {
        if (m_followees.find(id) == m_followees.end())
            m_followees.insert(id);
    }
    void unfollow(int id)
    {
        if (m_followees.find(id) != m_followees.end())
            m_followees.erase(id);
    }

    int m_id;
    list<Tweet> m_tweets; // tweets belonging to this person
    set<int> m_followees;
 
};

class Twitter {
public:

    /** Initialize your data structure here. */
    Twitter()
    :timestamp(0) {
        
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userId, int tweetId) {
        if (m_users.find(userId) == m_users.end())
            m_users[userId] = new User(userId);
        Tweet currentTweet(tweetId, timestamp++);
        m_users[userId]->post(currentTweet);
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userId) {
        vector<int> tolist;
         auto comp = [](Tweet x, Tweet y){ return x.m_timestamp > y.m_timestamp; };
         auto myset = set<Tweet,decltype(comp)>( comp );
         const auto& followees = m_users[userId]->m_followees;
         // Get 10 tweets from each followee
         for (const auto& followee : followees)
         {
               auto& tweets = m_users[followee]->m_tweets;
              if (tweets.size() < MAX_TWEETS)
                  myset.insert(tweets.begin(), tweets.end());
              else
                  myset.insert(tweets.begin(), next(tweets.begin(), MAX_TWEETS));
         }
         // also do the same for this user's tweets
         auto& currentUserTweets = m_users[userId]->m_tweets;
           if (currentUserTweets.size() < MAX_TWEETS)
                myset.insert(currentUserTweets.begin(), currentUserTweets.end());
            else
                myset.insert(currentUserTweets.begin(), next(currentUserTweets.begin(), MAX_TWEETS));
         // Sort the 10 tweets
        // Get the first 10
         auto itr = myset.begin();
        for (int i = 0; i < std::min(MAX_TWEETS, (int)myset.size()); i++, itr++)
             tolist.push_back(itr->m_userId);
         
        return tolist;
    }
    
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerId, int followeeId) {
        if (m_users.find(followeeId) == m_users.end() 
            || m_users.find(followerId) == m_users.end()
            || followerId == followeeId)
            return;

        m_users[followerId]->follow(followeeId);
    }
    
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerId, int followeeId) {
         if (m_users.find(followeeId) == m_users.end() 
            || m_users.find(followerId) == m_users.end()
            || followerId == followeeId)
            return;   
        m_users[followerId]->unfollow(followeeId);
    }
    map<int, User*> m_users;
        int timestamp;

    
};


int main()
{
    
}
